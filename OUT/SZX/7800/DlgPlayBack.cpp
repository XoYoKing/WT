// DlgPlayBack.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgPlayBack.h"
#include "QueryResult.h"

namespace
{
    /**@fn         <GetAppPath>
    *@brief        <获取当前模块所在的目录>
    *@return      return  char*
    */
    const char* GetAppPath()
    {
        static char Apppath[1024] = {0};
        if(Apppath[0] == 0)
        {
            HMODULE hModule = NULL;
            if( ::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,(const char*)GetAppPath,&hModule) )//lint !e611
            {
                ::GetModuleFileNameA(hModule,Apppath,sizeof(Apppath) - 1);
                int len = static_cast<int>(strlen(Apppath));
                for (int i = len - 1;i >= 0;--i)
                {
                    if(Apppath[i] == '\\')
                    {
                        Apppath[i + 1] = 0;
                        break;
                    }
                }
            }
        }
        return Apppath;
    }
}

CDlgPlayBackWin g_PlaybackWin[4];//创建4个回放窗口
// CDlgPlayBack 对话框
extern CQueryResult g_QueryResult;

extern map<int,std::string> g_mapCam_ID_indexcode;   //camera ID和indexcode的映射

IMPLEMENT_DYNAMIC(CDlgPlayBack, CDialog)

CDlgPlayBack::CDlgPlayBack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayBack::IDD, pParent)
    ,m_ctBeginDay(0)
    ,m_ctBeginTime(0)
    ,m_ctEndDay(0)
    ,m_ctEndTime(0)
    ,m_ctOrientateDay(0)
    ,m_ctOrientateTime(0)
    ,m_iCurPlaybcakWndIndex(0)
    ,m_iCurPlaybackCID(0)
    ,m_iDownLoadpos(0)
    ,m_iCurDownHandle(0)
{

}

CDlgPlayBack::~CDlgPlayBack()
{
}

void CDlgPlayBack::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_STORETYPE, m_comboStoreType);
    DDX_Control(pDX, IDC_CHECK_PlANRECORD, m_check_PlanRecord);
    DDX_Control(pDX, IDC_CHECK_MOVERECORD, m_check_MoveRecord);
    DDX_Control(pDX, IDC_CHECK_MANUALRECORD, m_check_ManualRecord);
    DDX_Control(pDX, IDC_CHECK_ALARMRECORD, m_check_AlarmRecord);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGINDAY, m_ctBeginDay);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGINTIME, m_ctBeginTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDDAY, m_ctEndDay);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDTIME, m_ctEndTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ORIENTATEDAY, m_ctOrientateDay);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ORIENTATETIME, m_ctOrientateTime);
    DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_DownLoadProgress);
}


BEGIN_MESSAGE_MAP(CDlgPlayBack, CDialog)
    ON_MESSAGE(WM_DRAWBORDER,OnDrawPlayBackBorder)
    ON_MESSAGE(WM_FOCUS, OnFocus)
    ON_MESSAGE(WM_STOPPLAYBACK, OnStopPlayBack)
    ON_MESSAGE(WM_SELECTPLAYBACKCID,OnSetPlayBackCID)
    //     ON_MESSAGE(WM_STARTPLAY, OnStartPlay)
    //     ON_MESSAGE(WM_STOPPLAY, OnStopPlay)
    ON_BN_CLICKED(IDC_BUTTON_QUERYREOCRD, &CDlgPlayBack::OnBnClickedButtonQueryreocrd)
    ON_BN_CLICKED(IDC_BUTTON_STARTPLAY, &CDlgPlayBack::OnBnClickedButtonStartplay)
    ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDlgPlayBack::OnBnClickedButtonPause)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACKFAST, &CDlgPlayBack::OnBnClickedButtonPlaybackfast)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACKSLOW, &CDlgPlayBack::OnBnClickedButtonPlaybackslow)
    ON_BN_CLICKED(IDC_BUTTON_ORIENTATE, &CDlgPlayBack::OnBnClickedButtonOrientate)
    ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CDlgPlayBack::OnBnClickedButtonContinue)
    ON_BN_CLICKED(IDC_BUTTON_STARTDOWNLOAD, &CDlgPlayBack::OnBnClickedButtonStartdownload)
    ON_BN_CLICKED(IDC_BUTTON_STOPDOWNLOAD, &CDlgPlayBack::OnBnClickedButtonStopdownload)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &CDlgPlayBack::OnBnClickedButtonSnapshot)
END_MESSAGE_MAP()


// CDlgPlayBack 消息处理程序
/** @fn BOOL InitPlayBackDisplay(void)
*  @brief 初始化回放子对话框
*  @return 成功:TRUE
*/
void CDlgPlayBack::InitPlayBackDisplay(void)
{
    InitChildWindow();
    InitWindowLayout();
    InitPlaybackRect();
    __InitComboBox();
    UpdateData(FALSE);
}

void CDlgPlayBack::__InitComboBox()
{
    m_comboStoreType.ShowWindow(SW_HIDE);
    m_comboStoreType.ResetContent();
    m_comboStoreType.AddString("1_设备");
    m_comboStoreType.AddString("2_PCNVR");
    m_comboStoreType.AddString("3_NVR");
    m_comboStoreType.AddString("4_CVR");
    m_comboStoreType.SetCurSel(0);

    m_check_PlanRecord.SetCheck(BST_CHECKED);
    m_check_MoveRecord.SetCheck(BST_CHECKED);
    m_check_ManualRecord.SetCheck(BST_CHECKED);
    m_check_AlarmRecord.SetCheck(BST_CHECKED);

    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_ctBeginDay = timeStart;
    m_ctBeginTime = timeStart;
    m_ctEndDay = timeStop;
    m_ctEndTime = timeStop;
    m_ctOrientateDay = timeCur;
    m_ctOrientateTime = timeCur;

    m_DownLoadProgress.SetColor(RGB(200,128,0),RGB(12,128,120),RGB(0,200,10),RGB(255,255,255));
    m_DownLoadProgress.SetProRange(0,100,1);
    m_DownLoadProgress.SetProPos(0);
}

// CDlgPlayBack 消息处理程序
/** @fn BOOL InitChildWindow(void)
*  @brief 初始化子对话框
*  @return 成功:TRUE
*/
BOOL CDlgPlayBack::InitChildWindow(void)
{
    for (int i = 0; i < 4; i++)
    {
        g_PlaybackWin[i].m_iSubPlayBackWndIndex = i;    ///< 子窗口(预览窗口)索引
        g_PlaybackWin[i].Create(IDD_DLG_PLAYBACKWIN, this);//创建一个窗口
    }
    return TRUE;
}

/** @fn BOOL InitWindowLayout(void)
*  @brief 初始化主窗口布局位置
*  @return 成功:TRUE;
*/
BOOL CDlgPlayBack::InitWindowLayout(void)
{
    CRect rect;
    int ix, iy, iWidth, iHeight;
    ix = iy = iWidth = iHeight = 0;
    GetClientRect(&rect);
    m_iPlaybackLeft = rect.left ;
    m_iPlaybackTop = rect.top;
    //GetDlgItem(IDC_BUTTON_PLAYBACKFAST)->GetClientRect(&rect);
    GetDlgItem(IDC_BUTTON_PLAYBACKFAST)->GetWindowRect(&rect);//获取控件相对于屏幕的位置
    ScreenToClient(rect);//转化为对话框上的相对位置

    m_iPlaybackRight = rect.left-50;

    return TRUE;
}

/** @fn void InitPreviewRect()
*  @brief 初始化回放区
*  @return void
*/
void CDlgPlayBack::InitPlaybackRect(void)
{
    CRect rc;
    GetClientRect(rc);
    m_rectPlaybackBG.top = m_iPlaybackTop;
    m_rectPlaybackBG.left = m_iPlaybackLeft;
    m_rectPlaybackBG.right = m_iPlaybackRight;
    m_rectPlaybackBG.bottom = rc.bottom-5 ;
    GetDlgItem(IDC_STATIC_PLAYBACKBG)->MoveWindow(&m_rectPlaybackBG, TRUE);//改变指定窗口的位置和大小.对顶窗口来说,位置和大小取决于屏幕的左上角;对子窗口来说,位置和大小取决于父窗口客户区的左上角.
    ArrangeOutputs(4);
}

/** @fn void ArrangeOutputs(int iNumber)
*  @brief 预览子窗体布局
*  @para iNumber: 子窗体个数
*  @return void
*/
void CDlgPlayBack::ArrangeOutputs(int iNumber)
{
    int i = 0;
    int iSqrtNum = 0;	//sqrt value of window number
    int iWidth = 0;		//each child window width
    int iHeight = 0;	//each child window height
    int ileft = 0;		//the x-coordinate of the upper-left corner of the child window
    int itop = 0;		//the y-coordinate of the upper-left corner of the child window
    for (i = 0; i < MAX_PLAYBACKWND; i++)
    {
        g_PlaybackWin[i].ShowWindow(SW_HIDE);
    }
    iSqrtNum = (int)sqrt((double)iNumber);	//算出是几乘几画面
    iWidth = (m_rectPlaybackBG.Width() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
    iHeight = (m_rectPlaybackBG.Height() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
    for (i = 0; i < iNumber; i++)
    {
        ileft = m_iPlaybackLeft + (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL);
        itop = m_iPlaybackTop + (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL);
        g_PlaybackWin[i].MoveWindow(ileft, itop, iWidth, iHeight, TRUE);
        g_PlaybackWin[i].ShowWindow(SW_SHOW);
    }
}

LRESULT CDlgPlayBack::OnDrawPlayBackBorder(WPARAM wparam, LPARAM lparam)
{
    for (int i = 0 ; i<4; i++)
    {
        if (m_iCurPlaybcakWndIndex == i)
        {
            g_PlaybackWin[i].DrawOutputBorder(TRUE);
        }
        else
        {
            g_PlaybackWin[i].DrawOutputBorder(FALSE);
        }
    }
    return 0;
}

LRESULT CDlgPlayBack::OnFocus(WPARAM wparam, LPARAM lparam)
{
    m_iCurPlaybcakWndIndex = lparam;
    for (int i = 0 ; i<4; i++)
    {
        if (m_iCurPlaybcakWndIndex == i)
        {
            g_PlaybackWin[i].DrawOutputBorder(TRUE);
        }
        else
        {
            g_PlaybackWin[i].DrawOutputBorder(FALSE);
        }
    }
    return 0;
}
void CDlgPlayBack::OnBnClickedButtonQueryreocrd()
{
    UpdateData(TRUE);

    int iStoreType = m_comboStoreType.GetCurSel();
    int iLocationType = iStoreType+1;//1-设备，2-PCNVR，3-NVR，4-CVR
    int iRtnFileNum = 0;
    int iRecordType = 0;
    if ( m_check_PlanRecord.GetCheck() == BST_CHECKED)
    {
        iRecordType|=HIK_RECTYPE_PLAN;
    }
    if ( m_check_MoveRecord.GetCheck() == BST_CHECKED)
    {
        iRecordType|=HIK_RECTYPE_MOVE;
    }
    if ( m_check_AlarmRecord.GetCheck() == BST_CHECKED)
    {
        iRecordType|=HIK_RECTYPE_ALARM;
    }
    if ( m_check_ManualRecord.GetCheck() == BST_CHECKED)
    {
        iRecordType|=HIK_RECTYPE_MANUAL;
    }

    CTime absTimeFrom(m_ctBeginDay.GetYear(),m_ctBeginDay.GetMonth(),m_ctBeginDay.GetDay(),m_ctBeginTime.GetHour(),m_ctBeginTime.GetMinute(),m_ctBeginTime.GetSecond());
    CTime absTimeTo(m_ctEndDay.GetYear(),m_ctEndDay.GetMonth(),m_ctEndDay.GetDay(),m_ctEndTime.GetHour(),m_ctEndTime.GetMinute(),m_ctEndTime.GetSecond());

    map<int ,std::string>::iterator ptrCam = g_mapCam_ID_indexcode.find(m_iCurPlaybackCID);
    if (ptrCam != g_mapCam_ID_indexcode.end())
    {
        char szXML[PLAT_RECORD_RESULT_XML_BUFFER_SIZE] = {0};
        int iFileHanlde = HikPt_QueryRecord(ptrCam->second.c_str(),__int64(absTimeFrom.GetTime()),__int64(absTimeTo.GetTime()),szXML,PLAT_RECORD_RESULT_XML_BUFFER_SIZE,iRecordType);
        if (szXML != NULL)
        {
			MessageBox(szXML);
            std::string strXML = szXML;
            CSearchResultParser::Parse(strXML, m_records);
            m_mapFileHandleCID.insert(pair<int,std::string>(m_iCurPlaybackCID, strXML));
            g_QueryResult.InsertQueryResult(m_records, m_records.size());
            //提示
            CString szInfo;
            szInfo.Format("监控点(%s)查询录像成功,请进行录像回放",ptrCam->second.c_str());
            MessageBox(szInfo);
        }
        HikPt_CloseQueryRecord(iFileHanlde);
    }

}

void CDlgPlayBack::OnBnClickedButtonStartplay()
{
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            if (HikPt_StopPlayBack(hstream) == 0)
            {
                hstream = -1;
                m_mapWinIndexPlayBackHandle.erase(m_iCurPlaybcakWndIndex);
                m_mapWinIndexPlayBackCID.erase(m_iCurPlaybcakWndIndex);
            }
            else
            {
                return;
            }
        }
    }

    map<int ,std::string>::iterator ptrHandle = m_mapFileHandleCID.find(m_iCurPlaybackCID);

    if (ptrHandle != m_mapFileHandleCID.end())
    {
        long hStream = HikPt_StartPlayBack((g_PlaybackWin[m_iCurPlaybcakWndIndex].m_hWnd), ptrHandle->second.c_str(), -1, -1, NULL, NULL);
        if (hStream == -1)
        {
            PLAT_ERROR("start Plat_VSS_PlayBack failed lastError=%d",HikPt_GetLastError());
            MessageBox("录像回放失败");
        }
        else
        {
            m_mapWinIndexPlayBackHandle.insert(pair<int,int>(m_iCurPlaybcakWndIndex,hStream));
            m_mapWinIndexPlayBackCID.insert(pair<int,int>(m_iCurPlaybcakWndIndex,m_iCurPlaybackCID));
        }
        m_iCurPlaybcakWndIndex++;
    }
}

/*************************************************
*    Function:         OnStopPlay
*    Description:     处理回放窗口关闭回放消息
*    Input:          wparam  回放窗口控件ID
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPlayBack::OnStopPlayBack(WPARAM wparam, LPARAM lparam)
{
    int m_iCurPlaybcakWndIndex = (int)lparam;
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            if (HikPt_StopPlayBack(hstream) == 0)
            {
                m_mapWinIndexPlayBackHandle.erase(m_iCurPlaybcakWndIndex);
                m_mapWinIndexPlayBackCID.erase(m_iCurPlaybcakWndIndex);
            }
            else
            {
                PLAT_ERROR("Plat_VSS_StopPlayBack failed LastError=%d",HikPt_GetLastError());
            }
        }
    }

    Invalidate();
    return 0;
}

void CDlgPlayBack::Fini()
{
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.begin();
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            HikPt_StopPlayBack(hstream);
        }
        ptr++;
    }
    m_mapWinIndexPlayBackHandle.clear();
    m_mapWinIndexPlayBackCID.clear();
}

LRESULT CDlgPlayBack::OnSetPlayBackCID(WPARAM wparam, LPARAM lparam)
{
    m_iCurPlaybackCID = (int)wparam;
    return 0;
}

void CDlgPlayBack::OnBnClickedButtonPause()
{
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            if (HikPt_PlayBackControl(hstream,PLAY_PAUSE,0) == 0)
            {
                PLAT_ERROR("PLAY_PAUSE Success");
            }
            else
            {
                PLAT_ERROR("PLAY_PAUSE failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
}
void CDlgPlayBack::OnBnClickedButtonContinue()
{
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            if (HikPt_PlayBackControl(hstream,PLAY_START,0) == 0)
            {
                PLAT_ERROR("PLAY_CONTINUE Success");
            }
            else
            {
                PLAT_ERROR("PLAY_CONTINUE failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
}

void CDlgPlayBack::OnBnClickedButtonPlaybackfast()
{
    HPR_Guard lock(&m_LockWinPlayBackHandle);
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            if (HikPt_PlayBackControl(hstream,PLAY_FAST, 2) == 0)
            {
                PLAT_ERROR("PLAY_FAST Success");
            }
            else
            {
                PLAT_ERROR("PLAY_FAST failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
}

void CDlgPlayBack::OnBnClickedButtonPlaybackslow()
{
    HPR_Guard lock(&m_LockWinPlayBackHandle);
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            if (HikPt_PlayBackControl(hstream,PLAY_SLOW, -2) == 0)
            {
                PLAT_ERROR("PLAY_SLOW Success");
            }
            else
            {
                PLAT_ERROR("PLAY_SLOW failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
}

void CDlgPlayBack::OnBnClickedButtonOrientate()
{
    UpdateData(TRUE);
    CTime OrientateTime(m_ctOrientateDay.GetYear(),m_ctOrientateDay.GetMonth(),m_ctOrientateDay.GetDay(),m_ctOrientateTime.GetHour(),m_ctOrientateTime.GetMinute(),m_ctOrientateTime.GetSecond());

    HPR_Guard lock(&m_LockWinPlayBackHandle);
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            if (HikPt_PlayBackControl(hstream,PLAY_OFFSET,__int64(OrientateTime.GetTime())) == 0)
            {
                PLAT_ERROR("PLAY_FAST Success");
            }
            else
            {
                PLAT_ERROR("PLAY_FAST failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
}


void CDlgPlayBack::OnBnClickedButtonStartdownload()
{
    CString strFileName;
    CString szFilterFDlg = "mp4 (*.mp4)|*.mp4|所有文件 (*.*)|*.*||";

    CFileDialog fileDlg(FALSE, NULL, strFileName,OFN_OVERWRITEPROMPT,szFilterFDlg, NULL); 

    if(fileDlg.DoModal() == IDOK)
    {
        strFileName = fileDlg.GetPathName();
    }
    else
    {
        return;
    }

    strFileName = strFileName + ".mp4";

    HPR_Guard lock(&m_LockWinPlayBackHandle);
    map<int ,int>::iterator ptr = m_mapDownLoadHandleCID.find(m_iCurPlaybackCID);
    if (ptr != m_mapDownLoadHandleCID.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            PLAT_ERROR("Plat_VSS_GetFilePercent failed");
            MessageBox(_T("录像正在下载中，请先停止下载"));
        }
    }
    else
    {   
        map<int ,std::string>::iterator ptrHandle = m_mapFileHandleCID.find(m_iCurPlaybackCID);
        if (ptrHandle != m_mapFileHandleCID.end())
        {
            long hStream = HikPt_StartDownloadRecord(ptrHandle->second.c_str(), -1, -1, PBDownloadStreamCallBack, this);
            if (hStream == -1)
            {
                PLAT_ERROR("HikPt_StartDownloadRecord failed lastError=%d",HikPt_GetLastError());
            }
            else
            {
                m_mapDownLoadHandleCID.insert(pair<int,int>(m_iCurPlaybackCID,hStream));
                if(m_mapDownLoadStream2File.find(hStream) == m_mapDownLoadStream2File.end())
                {
                    //创建文件
                    HANDLE hFile = CreateFile(strFileName,          // name of the write
                        GENERIC_WRITE,          // open for writing
                        0,                      // do not share
                        NULL,                   // default security
                        CREATE_ALWAYS,          // overwrite existing
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attr. template

                    if (hFile == INVALID_HANDLE_VALUE) 
                    {   
                        PLAT_ERROR("CreateFile('%s') failed, GetLastError = %d",strFileName,GetLastError());
                        return;
                    }

                    m_mapDownLoadStream2File[hStream] = hFile;
                }
                
                CString szInfo;
                szInfo.Format("录像(%s)开始下载",strFileName);
                MessageBox(szInfo);
            }
        }
    }
}

//回放取流回调
void __stdcall CDlgPlayBack::PBDownloadStreamCallBack(long lSession, int iStreamType, const char* data, int dataLen, void* pUser)
{
    CDlgPlayBack* pThis = static_cast<CDlgPlayBack*>(pUser);
    if(pThis != NULL)
    {
        //码流数据处理
        pThis->OnDealDownloadStream(lSession,iStreamType,data,dataLen);
    } 
}

void CDlgPlayBack::OnDealDownloadStream(long lSession, int iStreamType, const char* data, int dataLen)
{   
    if(iStreamType == PBDT_FORWARD)
    {
        PLAT_INFO("Session = %d, Start recv download stream");
    }
    else if(iStreamType == PBDT_DATA)
    {
        if(m_mapDownLoadStream2File.find(lSession) != m_mapDownLoadStream2File.end())
        {   
            HANDLE hFile = m_mapDownLoadStream2File[lSession];
            DWORD dwSize = SetFilePointer(m_mapDownLoadStream2File[lSession], 0, NULL, FILE_END);
            if (dwSize == INVALID_SET_FILE_POINTER)
            {
                return;
            }
            
            DWORD dwRead = 0;
            if(FALSE == ::WriteFile(hFile,data,dataLen,&dwRead,NULL))
            {
                return;
            }
        }
    }
    else if(iStreamType == PBDT_END)
    {
        if(m_mapDownLoadStream2File.find(lSession) != m_mapDownLoadStream2File.end())
        {
            HANDLE& hFile = m_mapDownLoadStream2File[lSession];
            if(hFile != INVALID_HANDLE_VALUE)
            {
                CloseHandle(hFile);
                hFile = INVALID_HANDLE_VALUE;
            }
            m_mapDownLoadStream2File.erase(lSession);
        }
    }
}

void CDlgPlayBack::OnBnClickedButtonStopdownload()
{
    map<int ,int>::iterator ptr = m_mapDownLoadHandleCID.find(m_iCurPlaybackCID);
    if (ptr != m_mapDownLoadHandleCID.end())
    {
        int downloadhandle = ptr->second;
        int nRet = HikPt_StopDownloadRecord(downloadhandle);
        if(nRet == 0)
        {
            if(m_mapDownLoadStream2File.find(downloadhandle) != m_mapDownLoadStream2File.end())
            {
                HANDLE& hFile = m_mapDownLoadStream2File[downloadhandle];
                if(hFile != INVALID_HANDLE_VALUE)
                {
                    CloseHandle(hFile);
                    hFile = INVALID_HANDLE_VALUE;
                }
                m_mapDownLoadStream2File.erase(downloadhandle);
            }
            m_mapDownLoadHandleCID.erase(m_iCurPlaybackCID);
        }
        else
        {
            MessageBox(_T("停止下载失败"));
        }
    }
    m_DownLoadProgress.SetProPos(0);
}

void CDlgPlayBack::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    //m_iDownLoadpos = Plat_VSS_GetFilePercent(m_iCurDownHandle);
    if (m_iDownLoadpos == -1)
    {
        PLAT_ERROR("Plat_VSS_GetFilePercent failed");
        return;
    }
    m_DownLoadProgress.SetProPos(m_iDownLoadpos);
    if(m_iDownLoadpos>100)KillTimer(1);
    CDialog::OnTimer(nIDEvent);
}

void CDlgPlayBack::OnBnClickedButtonSnapshot()
{   
    map<int ,int>::iterator ptr = m_mapWinIndexPlayBackHandle.find(m_iCurPlaybcakWndIndex);
    if (ptr != m_mapWinIndexPlayBackHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {   
            HikSnapParam SnapParam;

            SnapParam.nPicType = 0;
            SnapParam.nSnapType = 0;
            SnapParam.nMultiType = 0;
            SnapParam.nSpanTime = 0;
            SnapParam.nSnapCount = 0;
            SnapParam.Quality = 100;
            strcpy(SnapParam.szSaveFolder, GetAppPath());

            if (HikPt_PlaybackSnapShot(hstream,&SnapParam,SnapCallback,this) == 0)
            {   
                //抓图成功
                
            }
            else
            {
                PLAT_ERROR("HikPt_PlaybackSnapShot failed LastError=%d",HikPt_GetLastError());
            }
        }
    }
    else
    {
        MessageBox("请先选中一个要抓图的窗口");
    }
}

//拍照回调
void __stdcall CDlgPlayBack::SnapCallback(long lSession,int nErr,const char* data,void* pUser)
{
    CDlgPlayBack* pThis = static_cast<CDlgPlayBack*>(pUser);
    if(pThis != NULL)
    {
        //拍照回调
        CString szInfo;
        szInfo.Format("抓图成功,保存路径：%s",data);
        pThis->MessageBox(szInfo);
    }
}

