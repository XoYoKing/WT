// DlgPreview.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgPreview.h"
#include "PTZDlg.h"
#include "DlgPreviewWin.h"

namespace
{
    /**@fn         <GetAppPath>
    *@brief        <��ȡ��ǰģ�����ڵ�Ŀ¼>
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

int g_iCurWndIndex;                 ///< ��ǰ��������

map<int,std::string> g_mapWinIndexPreviewCID;   //���ں�cameraID��ӳ��

extern map<int,std::string> g_mapCam_ID_indexcode;   //camera ID��indexcode��ӳ��
// CDlgPreview �Ի���

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
*  @brief ��ʼ��Ԥ���ӶԻ���
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

// CDlgPreview ��Ϣ�������

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
    m_nStreamType.AddString("������");
    m_nStreamType.AddString("������");
    m_nStreamType.AddString("��������");
    m_nStreamType.SetCurSel(0);

}

/** @fn BOOL InitWindowLayout(void)
*  @brief ��ʼ�������ڲ���λ��
*  @return �ɹ�:TRUE;
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
*  @brief ��ʼ���ӶԻ���
*  @return �ɹ�:TRUE
*/
BOOL CDlgPreview::InitChildWindow(void)
{
    for (int i = 0; i < MAX_OUTPUTS; i++)
    {
        g_dlgPreviewWin[i].m_iSubWndIndex = i;    ///< �Ӵ���(Ԥ������)����
        g_dlgPreviewWin[i].Create(IDD_DLG_PREVIEWWIN, this);//����һ������
    }
    g_dlgPTZ.Create(IDD_DLG_PTZ,this);
    return TRUE;
}

/** @fn void InitPreviewRect()
*  @brief ��ʼ��Ԥ����
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
    GetDlgItem(IDC_STATIC_PREVIEWBG)->MoveWindow(&m_rectPreviewBG, TRUE);//�ı�ָ�����ڵ�λ�úʹ�С.�Զ�������˵,λ�úʹ�Сȡ������Ļ�����Ͻ�;���Ӵ�����˵,λ�úʹ�Сȡ���ڸ����ڿͻ��������Ͻ�.
    m_iCurWndNum = 4; //��ʼ��4����
    
    ArrangeOutputs(m_iCurWndNum);
    m_comboWinNum.SetCurSel(1);
    m_nStreamType.SetCurSel(0);

    g_dlgPTZ.MoveWindow(m_iPreviewRight+10,m_iPreviewTop,180,400,TRUE);
    g_dlgPTZ.ShowWindow(SW_SHOW); 
    g_dlgPTZ.InitComBox();
}

/** @fn void ArrangeOutputs(int iNumber)
*  @brief Ԥ���Ӵ��岼��
*  @para iNumber: �Ӵ������
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
    iSqrtNum = (int)sqrt((double)iNumber);	//����Ǽ��˼�����
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
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
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
*    Description:     ����ʵʱ��Ƶ
*    Input:          wparam ��ص�ID
*    Output:           ��
*    Return:         ��
*************************************************/ 
LRESULT CDlgPreview::OnStartPlay(WPARAM wparam, LPARAM lparam)
{
    int iCameraID = (WPARAM)wparam;
    int streamhandle;

    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //�ر����ڲ��ŵ�
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

        //Ԥ��ʵʱ��Ƶ
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
*    Description:     ����Ԥ�����ڹر�Ԥ����Ϣ
*    Input:          wparam  Ԥ�����ڿؼ�ID
*    Output:           ��
*    Return:         ��
*************************************************/
LRESULT CDlgPreview::OnStopPlay(WPARAM wparam, LPARAM lparam)
{
    int g_iCurWndIndex = (int)lparam;
    map<int ,int>::iterator ptr = m_mapWinIndexPreviewHandle.find(g_iCurWndIndex);
    if (ptr != m_mapWinIndexPreviewHandle.end())
    {
        int hstream = ptr->second;
        if (hstream >= 0)    //�ر����ڲ��ŵ�
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
*    Description:      ��ʼԤ����ǽ
*    Input:          wparam  Ԥ�����ڿؼ�ID
*    Output:           ��
*    Return:         ��
*************************************************/
LRESULT CDlgPreview::OnStartTvWall(WPARAM wparam, LPARAM lparam)
{
    if (m_bTvWall)
    {
        AfxMessageBox("�ѿ���Ԥ����ǽ");
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
                m_iTvWallId = pTvwallInfo[0].iTvwallId;       //��ȡ����ǽid
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
            int iWndId = GetIniFileInt("TEST", "WndId", 1, "PlatSdkCfg.ini");       //��ȡ��ǽ����id
            std::string CamIndex = GetIniFileString("TEST", "CamIndex", "33010800001310000161", "PlatSdkCfg.ini");      //��ص���
            streamhandle = HikPt_StartPreviewToWall(m_iTvWallId, iWndId, CamIndex.c_str());
            if (streamhandle != 0)
            {
                PREVIEW_ERROR("HikPt_StartPreviewToWall failed! iTvWallId=[%d], iWndId=[%d], CamIndex=[%s]", m_iTvWallId, iWndId, CamIndex.c_str());
                AfxMessageBox("��ʼԤ����ǽʧ��");
                return -1;
            }

            m_bTvWall = TRUE;
            AfxMessageBox("��ʼԤ����ǽ�ɹ�");
        }
    }
    Invalidate();
    return 0;
}

/*************************************************
*    Function:         OnStartTvWall
*    Description:      ��ʼԤ����ǽ
*    Input:          wparam  Ԥ�����ڿؼ�ID
*    Output:           ��
*    Return:         ��
*************************************************/
LRESULT CDlgPreview::OnStopTvWall(WPARAM wparam, LPARAM lparam)
{
    if (!m_bTvWall)
    {
        AfxMessageBox("Ԥ����ǽδ����");
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
            streamhandle = HikPt_StopPreviewToWall(m_iTvWallId, iWndId);//����Ԥ����ǽ
            if (streamhandle != 0)
            {
                PREVIEW_ERROR("HikPt_StopPreviewToWall failed! iTvWallId=[%d], iWndId=[%d]", m_iTvWallId, iWndId);
                AfxMessageBox("ֹͣԤ����ǽʧ��");
                return -1;
            }

            m_bTvWall = FALSE;
            AfxMessageBox("ֹͣԤ����ǽ�ɹ�");
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
        if (hstream >= 0)    //�ر����ڲ��ŵ�
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
*    Description:     ������̨��Ϣ
*    Input:          wparam  �ؼ�ID  lparam ��̨�ٶȻ�Ԥ�õ���Ϣ
*    Output:           ��
*    Return:         ��
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
*    Description:     ������̨��Ϣ
*    Input:          wparam  �ؼ�ID  lparam ��̨�ٶȻ�Ԥ�õ���Ϣ
*    Output:           ��
*    Return:         ��
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
        AfxMessageBox("ץͼʧ��");
        return 0;
    }
    
    //Ԥ��ץͼ����
    HikSnapParam SnapParam;
    //ͼƬ����(0~JPG  1~BMP)
    SnapParam.nPicType = 0;
    //ץͼ����(0~����  1~����)
    SnapParam.nSnapType = 0;
    //����ץͼģʽ(0~��ʱ��  1~��֡)
    SnapParam.nMultiType = 0;
    //ץͼʱ����(1~1����  2~2����  3~3����  4~4����  5~5����)
    SnapParam.nSpanTime = 1;
    //����ץͼ����(3~3��  4~4��  5~5��  6~6��)
    SnapParam.nSnapCount = 0;
    //ͼƬ����
    SnapParam.Quality = 80;
    strcpy(SnapParam.szSaveFolder, "");
    //ץͼģʽ(0~�Զ�  1~�ֶ�)
    SnapParam.lOpenFlag = 0;
    //����ͼƬ�����Ƹ�ʽ(1~{��ص�����}_{ʱ��}  2_{ʱ��}  3_{ʱ��}_{��ص�����})
    SnapParam.nFormatType = 1;

    //ץͼ�ɹ����Զ���
    if(HikPt_PreviewSnapShot(streamhandle,&SnapParam, SnapCallback, this) == 0)
    {
        Sleep(50);    //��ֹ����ץͼ��δ�ɹ����򿪵�����        [guchen 20120309]
        //ShellExecute(this->m_hWnd, "open", strFileName,NULL ,NULL, SW_MAXIMIZE);
        return 1;
    }
    return 0;
}

//���ջص�
void __stdcall CDlgPreview::SnapCallback(long lSession,int nErr,const char* data,void* pUser)
{
    CDlgPreview* pThis = static_cast<CDlgPreview*>(pUser);
    if(pThis != NULL)
    {
        //���ջص�
        CString szInfo;
        szInfo.Format("ץͼ�ɹ�,����·����%s",data);
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
        AfxMessageBox("��ʼ����¼��ʧ��");
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
        szInfo.Format("����¼��ʧ��");
        MessageBox(szInfo);
    }
    return 0;
}

void __stdcall CDlgPreview::PreviewRecordEndCallback(long lSession,int nErr,const char* data,void* pUser)
{   
    CDlgPreview* pThis = static_cast<CDlgPreview*>(pUser);
    if(pUser != NULL)
    {
        //Ԥ������¼�����
        CString szInfo;
        szInfo.Format("Ԥ��¼�����,����·����%s",data);
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
        AfxMessageBox("��ʼ����¼��ʧ��");
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
        int nRet = HikPt_PtzLock(cameraID.c_str(),60); //��λΪ1����
        if(nRet != 0)
        {   
            CString szInfo;
            szInfo.Format("��ص�(%s)��̨����ʧ��",cameraID.c_str());
            MessageBox(szInfo);
        }
        else
        {
            CString szInfo;
            szInfo.Format("��ص�(%s)��̨�����ɹ�������ʱ��Ϊ1����",cameraID.c_str());
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
            szInfo.Format("��ص�(%s)��̨����ʧ��",cameraID.c_str());
            MessageBox(szInfo);
        }
        else
        {
            CString szInfo;
            szInfo.Format("��ص�(%s)��̨�����ɹ�",cameraID.c_str());
            MessageBox(szInfo);
        }
    }

    return 0;
}

void CDlgPreview::OnCbnSelchangeComboStreamtype()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
