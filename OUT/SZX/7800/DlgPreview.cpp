// DlgPreview.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgPreview.h"
#include "PTZDlg.h"
#include "DlgPreviewWin.h"

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

    int GetIniFileInt(const char* szAppName,const char* szKeyName,int nDef,const char* szFileName)
    {
        std::string szPath;
        if(szFileName != NULL && szAppName != NULL && szKeyName != NULL)
        {
            szPath.append(GetAppPath());
            szPath.append(szFileName);
        }
        else
        {
            return nDef;
        }
        return ::GetPrivateProfileInt(szAppName,szKeyName,nDef,szPath.c_str());
    }

    std::string GetIniFileString(const char* szAppName,const char* szKeyName,const char* szDef,const char* szFileName)
    {
        char szBuff[1024] = {0};
        std::string szPath;
        if(szFileName != NULL && szAppName != NULL && szKeyName != NULL)
        {
            szPath.append(GetAppPath());
            szPath.append(szFileName);
        }
        else
        {   
        }
        if(szDef == NULL)
        {
            szDef = "";
        }
        ::GetPrivateProfileString(szAppName,szKeyName,szDef,szBuff,_countof(szBuff)-1,szPath.c_str());
        return szBuff;
    }
}


CDlgPreviewWin  g_dlgPreviewWin[MAX_OUTPUTS];
CPTZDlg         g_dlgPTZ;

int g_iCurWndIndex;                 ///< 当前窗口索引

map<int,std::string> g_mapWinIndexPreviewCID;   //窗口和cameraID的映射

extern map<int,std::string> g_mapCam_ID_indexcode;   //camera ID和indexcode的映射
// CDlgPreview 对话框

IMPLEMENT_DYNAMIC(CDlgPreview, CDialog)

CDlgPreview::CDlgPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreview::IDD, pParent)
    , m_iPTZSpeed(1)
    , m_iPresetIndex(0)
    , m_bTvWall(FALSE)
    , m_iTvWallId(0)
{
    m_nStream = main_stream;
}

CDlgPreview::~CDlgPreview()
{
}

void CDlgPreview::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_WNDNUM, m_comboWinNum);
    DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_nStreamType);
}


BEGIN_MESSAGE_MAP(CDlgPreview, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO_WNDNUM, &CDlgPreview::OnCbnSelchangeComboWndnum)
    ON_MESSAGE(WM_DRAWBORDER,OnDrawPreviewBorder)
    ON_MESSAGE(WM_FOCUS, OnFocus)
    ON_MESSAGE(WM_STARTPLAY, OnStartPlay)
    ON_MESSAGE(WM_STOPPLAY, OnStopPlay)
    ON_MESSAGE(WM_STARTTVWALL, OnStartTvWall)
    ON_MESSAGE(WM_STOPTVWALL, OnStopTvWall)
    ON_MESSAGE(WM_PTZ, OnMsgPTZ)
    ON_MESSAGE(WM_CAPPIC, OnMsgCAPPIC)
    ON_MESSAGE(WM_STARTRECORD, OnMsgStartRecord)
    ON_MESSAGE(WM_STOPRECORD, OnMsgStopRecord)
    ON_MESSAGE(WM_PTZ_LOCK, OnMsgPTZLock)
    ON_MESSAGE(WM_PTZ_UNLOCK, OnMsgPTZUnlock)
    ON_CBN_SELCHANGE(IDC_COMBO_STREAMTYPE, &CDlgPreview::OnCbnSelchangeComboStreamtype)
END_MESSAGE_MAP()


/** @fn BOOL InitPreviewDisplay(void)
*  @brief 初始化预览子对话框
*  @return void
*/
void CDlgPreview::InitPreviewDisplay(void)
{
    InitChildWindow();
    InitWindowLayout();
    InitPreviewRect();
    __InitComboBox();
    UpdateData(FALSE);
}

// CDlgPreview 消息处理程序

void CDlgPreview::__InitComboBox()
{
    m_comboWinNum.ResetContent();
    CString strTemp;
    
    if (GetIniFileInt("PREVIEW", "PerformTest", 0, "PlatSdkCfg.ini") == 0)
    {
        for(int i=1; i<=4; i++)
        {
            strTemp.Format("%d", i*i);
            m_comboWinNum.AddString(strTemp);
        }
    }
    else
    {
        for(int i=1; i<=15; i++)
        {
            strTemp.Format("%d", i*i);
            m_comboWinNum.AddString(strTemp);
        }
    }
    m_comboWinNum.SetCurSel(1);

    m_nStreamType.ResetContent();
    m_nStreamType.AddString("主码流");
    m_nStreamType.AddString("子码流");
    m_nStreamType.AddString("第三码流");
    m_nStreamType.SetCurSel(0);

}

/** @fn BOOL InitWindowLayout(void)
*  @brief 初始化主窗口布局位置
*  @return 成功:TRUE;
*/
BOOL CDlgPreview::InitWindowLayout(void)
{
    CRect rect;
    int ix, iy, iWidth, iHeight;
    ix = iy = iWidth = iHeight = 0;
    GetClientRect(&rect);
    m_iPreviewLeft = rect.left;
    m_iPreviewTop = rect.top;
    return TRUE;
}

/** @fn BOOL InitChildWindow(void)
*  @brief 初始化子对话框
*  @return 成功:TRUE
*/
BOOL CDlgPreview::InitChildWindow(void)
{
    for (int i = 0; i < MAX_OUTPUTS; i++)
    {
        g_dlgPreviewWin[i].m_iSubWndIndex = i;    ///< 子窗口(预览窗口)索引
        g_dlgPreviewWin[i].Create(IDD_DLG_PREVIEWWIN, this);//创建一个窗口
    }
    g_dlgPTZ.Create(IDD_DLG_PTZ,this);
    return TRUE;
}

/** @fn void InitPreviewRect()
*  @brief 初始化预览区
*  @return void
*/
void CDlgPreview::InitPreviewRect(void)
{
    CRect rc;
    GetClientRect(rc);
    m_rectPreviewBG.top = m_iPreviewTop;
    m_rectPreviewBG.left = m_iPreviewLeft;
    m_rectPreviewBG.right = rc.right - 200;
    m_iPreviewRight =  m_rectPreviewBG.right;
    m_rectPreviewBG.bottom = rc.bottom-5;
    GetDlgItem(IDC_STATIC_PREVIEWBG)->MoveWindow(&m_rectPreviewBG, TRUE);//改变指定窗口的位置和大小.对顶窗口来说,位置和大小取决于屏幕的左上角;对子窗口来说,位置和大小取决于父窗口客户区的左上角.
    m_iCurWndNum = 4; //初始化4分屏
    
    ArrangeOutputs(m_iCurWndNum);
    m_comboWinNum.SetCurSel(1);
    m_nStreamType.SetCurSel(0);

    g_dlgPTZ.MoveWindow(m_iPreviewRight+10,m_iPreviewTop,180,400,TRUE);
    g_dlgPTZ.ShowWindow(SW_SHOW); 
    g_dlgPTZ.InitComBox();
}

/** @fn void ArrangeOutputs(int iNumber)
*  @brief 预览子窗体布局
*  @para iNumber: 子窗体个数
*  @return void
*/
void CDlgPreview::ArrangeOutputs(int iNumber)
{
    int i = 0;
    int iSqrtNum = 0;	//sqrt value of window number
    int iWidth = 0;		//each child window width
    int iHeight = 0;	//each child window height
    int ileft = 0;		//the x-coordinate of the upper-left corner of the child window
    int itop = 0;		//the y-coordinate of the upper-left corner of the child window
    for (i = 0; i < MAX_OUTPUTS; i++)
    {
        g_dlgPreviewWin[i].ShowWindow(SW_HIDE);
    }
    iSqrtNum = (int)sqrt((double)iNumber);	//算出是几乘几画面
    iWidth = (m_rectPreviewBG.Width() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
    iHeight = (m_rectPreviewBG.Height() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
    for (i = 0; i < iNumber; i++)
    {
        ileft = m_iPreviewLeft + (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL);
        itop = m_iPreviewTop + (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL);
        g_dlgPreviewWin[i].MoveWindow(ileft, itop, iWidth, iHeight, TRUE);
        g_dlgPreviewWin[i].ShowWindow(SW_SHOW);
    }

}

void CDlgPreview::OnCbnSelchangeComboWndnum()
{
    int iIndex = m_comboWinNum.GetCurSel();
    m_iCurWndNum = (int)pow(double(iIndex+1), 2);
    ArrangeOutputs(m_iCurWndNum);
    GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
}

void CDlgPreview::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialog::OnPaint()
}

LRESULT CDlgPreview::OnDrawPreviewBorder(WPARAM wparam, LPARAM lparam)
{
    int playType = lparam;
    if (playType == PREVIEW_T)
    {    
        for (int i = 0 ; i<m_iCurWndNum; i++)
        {
            if (g_iCurWndIndex == i)
            {
                g_dlgPreviewWin[i].DrawOutputBorder(TRUE);
            }
            else
            {
                g_dlgPreviewWin[i].DrawOutputBorder(FALSE);
            }
        }
    }
    return 0;
}

LRESULT CDlgPreview::OnFocus(WPARAM wparam, LPARAM lparam)
{
    g_iCurWndIndex = lparam;
    for (int i = 0 ; i<MAX_OUTPUTS; i++)
    {
        if (g_iCurWndIndex == i)
        {
            g_dlgPreviewWin[i].DrawOutputBorder(TRUE);
        }
        else
        {
            g_dlgPreviewWin[i].DrawOutputBorder(FALSE);
        }
    }
    return 0;
}

/*************************************************
*    Function:         OnStartPlay
*    Description:     播放实时视频
*    Input:          wparam 监控点ID
*    Output:           无
*    Return:         无
*************************************************/ 
LRESULT CDlgPreview::OnStartPlay(WPARAM wparam, LPARAM lparam)
{
    int iCameraID = (WPARAM)wparam;
    int streamhandle;

    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            if (HikPt_StopPlayView(hstream) == 0)
            {
                hstream = -1;
                m_mapWinIndexPreviewHandle.erase(g_iCurWndIndex);
                g_mapWinIndexPreviewCID.erase(g_iCurWndIndex);
            }
            else
            {
                PLAT_ERROR("HikPt_StopPlayView failed! LastError= %d",HikPt_GetLastError());
                return -1;
            }
        }
    }
    Invalidate();
 
    map<int ,std::string>::iterator ptrCam = g_mapCam_ID_indexcode.find(iCameraID);
    if (ptrCam != g_mapCam_ID_indexcode.end())
    {
        HWND hWnd = NULL;
        if (GetIniFileInt("PREVIEW", "OnlyStream", 0, "PlatSdkCfg.ini") == 0)
        {
            hWnd = g_dlgPreviewWin[g_iCurWndIndex].m_hWnd;
        }
        else
        {
            hWnd = NULL;
        }

        //预览实时视频
        streamhandle = HikPt_StartPlayView(ptrCam->second.c_str(), hWnd, PreviewStreamCallback, this, m_nStream);
        //m_ErrorListDlg.InsertLog("HikPt_StartPlayView",HikPt_GetLastError());

        if(streamhandle >= 0)
        {
            m_mapWinIndexPreviewHandle.insert(pair<int ,int>(g_iCurWndIndex, streamhandle));
            g_mapWinIndexPreviewCID.insert(pair<int ,std::string>(g_iCurWndIndex, ptrCam->second));
        }
        else
        { 
            PLAT_ERROR("HikPt_StartPlayView failed! iCameraID=%d,LastError= %d",iCameraID,HikPt_GetLastError());
        }
        g_iCurWndIndex++;
    }

    return 0;
}

/*************************************************
*    Function:         OnStopPlay
*    Description:     处理预览窗口关闭预览消息
*    Input:          wparam  预览窗口控件ID
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPreview::OnStopPlay(WPARAM wparam, LPARAM lparam)
{
    int g_iCurWndIndex = (int)lparam;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            if (HikPt_StopPlayView(hstream) == 0)
            {
                hstream = -1;
                m_mapWinIndexPreviewHandle.erase(g_iCurWndIndex);
                g_mapWinIndexPreviewCID.erase(g_iCurWndIndex);
            }
            else
            {
                return -1;
            }
        }
    }
    Invalidate();
    return 0;
}

/*************************************************
*    Function:         OnStartTvWall
*    Description:      开始预览上墙
*    Input:          wparam  预览窗口控件ID
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPreview::OnStartTvWall(WPARAM wparam, LPARAM lparam)
{
    if (m_bTvWall)
    {
        AfxMessageBox("已开启预览上墙");
        Invalidate();
        return 0;
    }

    int nTvwallSize = 10;
    HikTvwallInfo* pTvwallInfo = new (std::nothrow) HikTvwallInfo[nTvwallSize];
    if (pTvwallInfo != NULL)
    {
        int nRet = HikPt_GetTvwallList(pTvwallInfo, nTvwallSize);
        if (nRet == HIKPT_E_OK && pTvwallInfo != NULL)
        {
            if (nTvwallSize > 0)
            {
                m_iTvWallId = pTvwallInfo[0].iTvwallId;       //获取电视墙id
            }
        }

        delete [] pTvwallInfo;
        pTvwallInfo = NULL;
    }

    int g_iCurWndIndex = (int)lparam;
    int streamhandle = 0;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            int iWndId = GetIniFileInt("TEST", "WndId", 1, "PlatSdkCfg.ini");       //获取上墙窗口id
            std::string CamIndex = GetIniFileString("TEST", "CamIndex", "33010800001310000161", "PlatSdkCfg.ini");      //监控点编号
            streamhandle = HikPt_StartPreviewToWall(m_iTvWallId, iWndId, CamIndex.c_str());
            if (streamhandle != 0)
            {
                PREVIEW_ERROR("HikPt_StartPreviewToWall failed! iTvWallId=[%d], iWndId=[%d], CamIndex=[%s]", m_iTvWallId, iWndId, CamIndex.c_str());
                AfxMessageBox("开始预览上墙失败");
                return -1;
            }

            m_bTvWall = TRUE;
            AfxMessageBox("开始预览上墙成功");
        }
    }
    Invalidate();
    return 0;
}

/*************************************************
*    Function:         OnStartTvWall
*    Description:      开始预览上墙
*    Input:          wparam  预览窗口控件ID
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPreview::OnStopTvWall(WPARAM wparam, LPARAM lparam)
{
    if (!m_bTvWall)
    {
        AfxMessageBox("预览上墙未开启");
        Invalidate();
        return 0;
    }

    int g_iCurWndIndex = (int)lparam;
    int streamhandle = 0;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)
        {
            int iWndId = GetIniFileInt("TEST", "WndId", 1, "PlatSdkCfg.ini");
            streamhandle = HikPt_StopPreviewToWall(m_iTvWallId, iWndId);//测试预览上墙
            if (streamhandle != 0)
            {
                PREVIEW_ERROR("HikPt_StopPreviewToWall failed! iTvWallId=[%d], iWndId=[%d]", m_iTvWallId, iWndId);
                AfxMessageBox("停止预览上墙失败");
                return -1;
            }

            m_bTvWall = FALSE;
            AfxMessageBox("停止预览上墙成功");
        }
    }
    Invalidate();
    return 0;
}


void CDlgPreview::Fini()
{
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.begin();
    while (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //关闭正在播放的
        {
            HikPt_StopPlayView(hstream);
        }
        ptr++;
    }
    m_mapWinIndexPreviewHandle.clear();
    g_mapWinIndexPreviewCID.clear();
}

int CDlgPreview::__ConverPTZcommand(int BtnID)
{
    int iCmd;
    switch (BtnID)
    {
    case IDC_BTN_PTZ_UP:
        iCmd = PLAT_TILT_UP;
        break;
    case IDC_BTN_PTZ_DOWN:
        iCmd = PLAT_TILT_DOWN;
        break;
    case IDC_BTN_PTZ_LEFT:
        iCmd = PLAT_PAN_LEFT;
        break;
    case IDC_BTN_PTZ_RIGHT:
        iCmd = PLAT_PAN_RIGHT;
        break;
    case IDC_BTN_PTZ_UPLEFT:
        iCmd = PLAT_UP_LEFT;
        break;
    case IDC_BTN_PTZ_UPRIGHT:
        iCmd = PLAT_UP_RIGHT;
        break;
    case IDC_BTN_PTZ_DOWNLEFT:
        iCmd = PLAT_DOWN_LEFT;
        break;
    case IDC_BTN_PTZ_DOWNRIGHT:
        iCmd = PLAT_DOWN_RIGHT;
        break;
    case IDC_BTN_PTZ_AUTOSCAN:
        iCmd = 29;
        break;
    case IDC_BTN_PTZ_ZOOMIN:
        iCmd = PLAT_ZOOM_IN;
        break;
    case IDC_BTN_PTZ_ZOOMOUT:
        iCmd = PLAT_ZOOM_OUT;
        break;
    case IDC_BTN_PTZ_FOCUSNEAR:
        iCmd = PLAT_FOCUS_NEAR;
        break;
    case IDC_BTN_PTZ_FOCUSFAR:
        iCmd = PLAT_FOCUS_FAR;
        break;
    case IDC_BTN_PTZ_IRISOPEN:
        iCmd = PLAT_IRIS_OPEN;
        break;
    case IDC_BTN_PTZ_IRISCLOSE:
        iCmd = PLAT_IRIS_CLOSE;
        break;
    case IDC_BTN_PTZ_GOTOPRESET:
        iCmd = PLAT_GOTO_PRESET;
        break;
    case IDC_BTN_PTZ_SETPRESET:
        iCmd = PLAT_SET_PRESET;
        break;
    case IDC_BTN_PTZ_CLEPRESET:
        iCmd = PLAT_CLE_PRESET;
        break;
    default:
        return 0;
    }
    return iCmd;
}

/*************************************************
*    Function:         OnMsgPTZ
*    Description:     处理云台消息
*    Input:          wparam  控件ID  lparam 云台速度或预置点信息
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPreview::OnMsgPTZ(WPARAM wparam, LPARAM lparam)
{
    int iBtnID = (int)wparam;
    int action = (int)lparam;
    std::string cameraID;
    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        cameraID = ptr->second;
    }

    int iCommand = __ConverPTZcommand(iBtnID);
    switch (iCommand)
    {
    case PLAT_TILT_UP:
    case PLAT_TILT_DOWN:
    case PLAT_PAN_LEFT:
    case PLAT_PAN_RIGHT:
    case PLAT_UP_LEFT:
    case PLAT_UP_RIGHT:
    case PLAT_DOWN_LEFT:
    case PLAT_DOWN_RIGHT:
    case PLAT_ZOOM_IN:
    case PLAT_ZOOM_OUT:
    case PLAT_FOCUS_NEAR:
    case PLAT_FOCUS_FAR:
    case PLAT_IRIS_OPEN:
    case PLAT_IRIS_CLOSE:
    case PLAT_PAN_AUTO:
        HikPt_PtzControl(cameraID.c_str(), iCommand, action, 0, m_iPTZSpeed);
        break;
    case PLAT_GOTO_PRESET:
    case PLAT_SET_PRESET:
    case PLAT_CLE_PRESET:
        HikPt_PtzControl(cameraID.c_str(), iCommand, action, m_iPresetIndex, m_iPTZSpeed);
        break;
    default:
        return 0;
    }
    return 0;
}

/*************************************************
*    Function:         OnMsgPTZ
*    Description:     处理云台消息
*    Input:          wparam  控件ID  lparam 云台速度或预置点信息
*    Output:           无
*    Return:         无
*************************************************/
LRESULT CDlgPreview::OnMsgCAPPIC(WPARAM wparam, LPARAM lparam)
{
    int streamhandle = -1;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        streamhandle = ptr->second;
    }
    else
    {
        AfxMessageBox("抓图失败");
        return 0;
    }
    
    //预览抓图参数
    HikSnapParam SnapParam;
    //图片类型(0~JPG  1~BMP)
    SnapParam.nPicType = 0;
    //抓图类型(0~单张  1~多张)
    SnapParam.nSnapType = 0;
    //连续抓图模式(0~按时间  1~按帧)
    SnapParam.nMultiType = 0;
    //抓图时间间隔(1~1毫秒  2~2毫秒  3~3毫秒  4~4毫秒  5~5毫秒)
    SnapParam.nSpanTime = 1;
    //连续抓图张数(3~3张  4~4张  5~5张  6~6张)
    SnapParam.nSnapCount = 0;
    //图片质量
    SnapParam.Quality = 80;
    strcpy(SnapParam.szSaveFolder, "");
    //抓图模式(0~自动  1~手动)
    SnapParam.lOpenFlag = 0;
    //生成图片的名称格式(1~{监控点名称}_{时间}  2_{时间}  3_{时间}_{监控点名称})
    SnapParam.nFormatType = 1;

    //抓图成功后自动打开
    if(HikPt_PreviewSnapShot(streamhandle,&SnapParam, SnapCallback, this) == 0)
    {
        Sleep(50);    //防止出现抓图尚未成功即打开的现象        [guchen 20120309]
        //ShellExecute(this->m_hWnd, "open", strFileName,NULL ,NULL, SW_MAXIMIZE);
        return 1;
    }
    return 0;
}

//拍照回调
void __stdcall CDlgPreview::SnapCallback(long lSession,int nErr,const char* data,void* pUser)
{
    CDlgPreview* pThis = static_cast<CDlgPreview*>(pUser);
    if(pThis != NULL)
    {
        //拍照回调
        CString szInfo;
        szInfo.Format("抓图成功,保存路径：%s",data);
        pThis->MessageBox(szInfo);
    }
}


LRESULT CDlgPreview::OnMsgStartRecord(WPARAM wparam, LPARAM lparam)
{
    int streamhandle = -1;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        streamhandle = ptr->second;
    }
    else
    {
        AfxMessageBox("开始本地录像失败");
        return 0;
    }
   
    HikRecordCfgParam CfgParam;
    memset(&CfgParam, 0 , sizeof(CfgParam));
    strcpy(CfgParam.szFolder, GetAppPath());
    //strcpy(CfgParam.szFolder, "AA///BB//S");
    CfgParam.dwTimes = 5 * 60;

    if (HikPt_StartRecord(streamhandle,&CfgParam,PreviewRecordEndCallback,this) != HIKPT_E_OK)
    {
        CString szInfo;
        szInfo.Format("本地录像失败");
        MessageBox(szInfo);
    }
    return 0;
}

void __stdcall CDlgPreview::PreviewRecordEndCallback(long lSession,int nErr,const char* data,void* pUser)
{   
    CDlgPreview* pThis = static_cast<CDlgPreview*>(pUser);
    if(pUser != NULL)
    {
        //预览紧急录像结束
        CString szInfo;
        szInfo.Format("预览录像结束,保存路径：%s",data);
        pThis->MessageBox(szInfo);
    }
}

void __stdcall CDlgPreview::PreviewStreamCallback(long lSession, int iStreamType, const char* data, int dataLen, void* pUser)
{
    CDlgPreview* pThis = static_cast<CDlgPreview*>(pUser);
    if (pThis != NULL)
    {
    }
}

LRESULT CDlgPreview::OnMsgStopRecord(WPARAM wparam, LPARAM lparam)
{
    int streamhandle = -1;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        streamhandle = ptr->second;
    }
    else
    {
        AfxMessageBox("开始本地录像失败");
        return 0;
    }

    HikPt_StopRecord(streamhandle);
    return 0;
}

LRESULT CDlgPreview::OnMsgPTZLock(WPARAM wparam, LPARAM lparam)
{
    std::string cameraID;
    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        cameraID = ptr->second;
        int nRet = HikPt_PtzLock(cameraID.c_str(),60); //单位为1分钟
        if(nRet != 0)
        {   
            CString szInfo;
            szInfo.Format("监控点(%s)云台锁定失败",cameraID.c_str());
            MessageBox(szInfo);
        }
        else
        {
            CString szInfo;
            szInfo.Format("监控点(%s)云台锁定成功，锁定时间为1分钟",cameraID.c_str());
            MessageBox(szInfo);
        }
    }

    return 0;
}

LRESULT CDlgPreview::OnMsgPTZUnlock(WPARAM wparam, LPARAM lparam)
{   
    std::string cameraID;
    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        cameraID = ptr->second;
        int nRet = HikPt_PtzUnLock(cameraID.c_str()); 
        if(nRet != 0)
        {   
            CString szInfo;
            szInfo.Format("监控点(%s)云台解锁失败",cameraID.c_str());
            MessageBox(szInfo);
        }
        else
        {
            CString szInfo;
            szInfo.Format("监控点(%s)云台解锁成功",cameraID.c_str());
            MessageBox(szInfo);
        }
    }

    return 0;
}

void CDlgPreview::OnCbnSelchangeComboStreamtype()
{
    // TODO: 在此添加控件通知处理程序代码
    int iIndex = m_nStreamType.GetCurSel();
    switch(iIndex+1)
    {
    case 1:
        m_nStream = main_stream;
        break;
    case 2:
        m_nStream = sub_stream;
        break;
    case 3:
        m_nStream = third_stream;
        break;
    default:
        break;
    }
}
