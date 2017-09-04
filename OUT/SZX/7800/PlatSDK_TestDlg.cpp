
// PlatSDK_TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "PlatSDK_TestDlg.h"
#include "DlgPreview.h"
#include "DlgPlayBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CDlgPreview* g_dlgPreview;
extern CDlgPlayBack* g_dlgPlayBack;

CQueryResult g_QueryResult;

void CALLBACK AlarmCallback (const ALARMINFO* pAlrInfo, void *pUser);

void CALLBACK GPSReceiveCallback (int nMsgId,int lParam,const char* szInfo,void* pUser)
{
    if ( szInfo[0] == '\0')
    {
        return;
    }
    CPlatSDK_TestDlg *pDlg = (CPlatSDK_TestDlg*)pUser;
    EnterCriticalSection(&pDlg->m_sctAlrEvent);
    pDlg->m_szGPSInfo = szInfo;
    LeaveCriticalSection(&pDlg->m_sctAlrEvent);
    return;
}

void CALLBACK AlarmCallbackEventCB(const ALARMINFO* pAlrInfo, void* pUser)
{
    const void* p = pAlrInfo;
    return;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPlatSDK_TestDlg dialog
CPlatSDK_TestDlg::CPlatSDK_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlatSDK_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_szGPSInfo.clear();
}

void CPlatSDK_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_PLATSUBSYS, m_TabSubsystem);
    DDX_Control(pDX, IDC_TAB_COMMON, m_TabList);
}

BEGIN_MESSAGE_MAP(CPlatSDK_TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_DESTROY()
    ON_MESSAGE(WM_LASTERROR, OnMsgGetLastError)
    ON_BN_CLICKED(IDC_BUTTON_CLEARLIST, &CPlatSDK_TestDlg::OnBnClickedButtonClearlist)
    ON_BN_CLICKED(IDC_BUTTON_QUERY_HISTORY_ALARMLOG, &CPlatSDK_TestDlg::OnBnClickedButtonQueryHistoryAlarmlog)
    ON_BN_CLICKED(IDOK, &CPlatSDK_TestDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_QUERY_GPS_INFO, &CPlatSDK_TestDlg::OnBnClickedButtonQueryGpsInfo)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPlatSDK_TestDlg message handlers

//WT Add Start
#define TIMER_FOR_NEW_RECORD 9001
//测试
#define TIMES_FOR_NEW_RECORD 1000*60
//#define TIMES_FOR_NEW_RECORD 1000*6

//定时器
//启动
//SetTimer(TIMER_FOR_NEW_RECORD,TIMES_FOR_NEW_RECORD,(TIMERPROC)TimerProcFor);//用回调函数处理，此时对话框的消息处理函数不再处理。
//关闭
//KillTimer(TIMER_FOR_NEW_RECORD);  
void CPlatSDK_TestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	theApp.m_Basic.SaveLog(_T("CPlatSDK_TestDlg"),_T("OnTimer"),_T("Start-时间到，检测是否有新录像需要下载!"));
	
	m_Order.DoTimer();
	double dTimeMinute=(GetTickCount()-m_Order.m_lTimeNULL)*1.0/(1000.0*60.0);
	CString strLog=_T("");
	strLog.Format("[Check]====================%f====================",dTimeMinute);
	theApp.m_Basic.SaveLog(_T("CPlatSDK_TestDlg"),_T("OnTimer"),strLog);

	if ( dTimeMinute>30 )
	{
		theApp.m_Basic.SaveLog(_T("CPlatSDK_TestDlg"),_T("OnTimer"),_T("[Check]====================关闭===================="));
		//关闭
		//::PostMessage(AfxGetMainWnd()->m_hWnd,WM_SYSCOMMAND,SC_CLOSE,NULL);  
		this->SendMessage(WM_CLOSE);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPlatSDK_TestDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	double dTimeMinute=(GetTickCount()-m_Order.m_lTimeNULL)*1.0/(1000.0*60.0);
	CString strLog=_T("");
	strLog.Format("[Check]====================%f====================",dTimeMinute);
	theApp.m_Basic.SaveLog(_T("CPlatSDK_TestDlg"),_T("OnTimer"),strLog);

	if ( dTimeMinute>29 )
	{
		theApp.m_Basic.SaveLog(_T("CPlatSDK_TestDlg"),_T("OnTimer"),_T("[Check]====================重启===================="));
		//重启1
		////::PostMessage(AfxGetMainWnd()->m_hWnd,WM_SYSCOMMAND,SC_CLOSE,NULL);  
		////获取exe程序当前路径  
		//extern CPlatSDK_TestApp theApp;  
		//TCHAR szAppName[MAX_PATH];  
		//:: GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);  
		//CString strAppFullName;  
		//strAppFullName.Format(_T("%s"),szAppName);  
		////重启程序  
		//STARTUPINFO StartInfo;  
		//PROCESS_INFORMATION procStruct;  
		//memset(&StartInfo, 0, sizeof(STARTUPINFO));  
		//StartInfo.cb = sizeof(STARTUPINFO);  
		//::CreateProcess(  
		//	(LPCTSTR)strAppFullName,  
		//	NULL,  
		//	NULL,  
		//	NULL,  
		//	FALSE,  
		//	NORMAL_PRIORITY_CLASS,  
		//	NULL,  
		//	NULL,  
		//	&StartInfo,  
		//	&procStruct);

		//重启2
		TCHAR szAppName[MAX_PATH];
		:: GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);  
		CString strAppFullName;  
		strAppFullName.Format(_T("%s"),szAppName);  
		strAppFullName.Replace(_T(".exe"),_T(".bat"));
		theApp.m_Basic.RunBAT(strAppFullName);
	}

	CDialog::OnClose();
}
//WT Add End

BOOL CPlatSDK_TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    CrashAPI_Init();
	// TODO: Add extra initialization here
    InitControlsPara();
   // hlog_init("PlatSDKTest", TRUE);

	//WT Add Start
	m_Order.Clear();
	SetTimer(TIMER_FOR_NEW_RECORD,TIMES_FOR_NEW_RECORD,NULL);//用回调函数处理，此时对话框的消息处理函数不再处理。
	m_Order.DoTimer();
	//WT Add End

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlatSDK_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlatSDK_TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlatSDK_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPlatSDK_TestDlg::InitControlsPara()
{
// #ifdef _DEBUG
//     VLDSetReportOptions(VLD_OPT_REPORT_TO_FILE, L"leak.txt");
//     VLDGlobalEnable();
// #endif

    InitializeCriticalSection(&m_sctAlrEvent);
    m_TabSubsystem.AddPage(_T("视频子系统"), &m_VSSSubsysDlg, IDD_DLG_VSS_SUBSYS);   
    m_TabSubsystem.Show();

    m_TabList.AddPage(_T("日志错误信息"), &m_ErrorListDlg, IDD_DLG_ERROR);
    m_TabList.AddPage(_T("录像查询结果"), &g_QueryResult, IDD_DLG_QUERYRESULT);
    m_TabList.AddPage(_T("实时报警事件"), &m_AlmEvtInfo, IDD_DLG_ALARMEVENT);
    m_TabList.Show();

    HikPt_StartRecvRealAlarmEvent(AlarmCallback, this);
    HikPt_StartGPSReceive(GPSReceiveCallback ,this);

    unsigned int uiVersion = HikPt_GetVersion();
    CString  csTemp;
    csTemp.Format("V%d.%d.%d.%d", (0xf0000000 & uiVersion)>>28, (0x0f000000 & uiVersion)>>24,\
        (0x00f00000 & uiVersion)>>20, (0x000fffff & uiVersion));//%.d,0x0000ff & dwVersion,build NO. do not expose
    GetDlgItem(IDC_STATIC_SDK_VERSION)->SetWindowText(csTemp);
}

/*************************************************
*    Function:         OnDestroy
*    Description:     销毁操作
*    Input:          无
*    Output:           无
*    Return:         无
*************************************************/
void CPlatSDK_TestDlg::OnDestroy()
{
    g_dlgPreview->Fini();
    g_dlgPlayBack->Fini();

    HikPt_StopRecvRealAlarmEvent();
    HikPt_StopGPSReceive();

    HikPt_Logout();
    HikPt_Uninit();
    CrashAPI_Uninit();

    DeleteCriticalSection(&m_sctAlrEvent);

// #ifdef _DEBUG
//     VLDReportLeaks();
// #endif
    CDialog::OnDestroy();

    // TODO: Add your message handler code here
}

LRESULT CPlatSDK_TestDlg::OnMsgGetLastError(WPARAM wparam, LPARAM lparam)
{
    CString * FctName = (CString *)wparam;
    int iError = (int)lparam;
    m_ErrorListDlg.InsertLog(*FctName, iError);
    return 0;
}

void CPlatSDK_TestDlg::OnBnClickedButtonClearlist()
{
    // TODO: Add your control notification handler code here
    if (0 == m_TabList.m_nCurrentPage)
    {
        m_ErrorListDlg.m_ListError.DeleteAllItems();
        m_ErrorListDlg.m_index = 0;
    }
    else if (1 == m_TabList.m_nCurrentPage)
    {
        EnterCriticalSection(&m_sctAlrEvent);
        m_AlmEvtInfo.m_ListCtrl.DeleteAllItems();
        m_AlmEvtInfo.m_Index = 0;
        LeaveCriticalSection(&m_sctAlrEvent);
    }
}

template<class T>
void freelist(const T* pList)
{
    const T* pDel = pList;
    const T* pTmp = pDel;
    while (NULL != pTmp)
    {
        pDel =  pDel->pNext;
        delete pTmp;
        pTmp = pDel;
    }
}

void CPlatSDK_TestDlg::OnBnClickedButtonQueryHistoryAlarmlog()
{
    //分页信息
    HikPAGEINFO stPageInfo = {0};
    stPageInfo.iCurPage = 1;
    stPageInfo.iPageSize = 10;

    /*查询告警参数*/
    HIKSEARCHALARMLOGPARAM stSearchParam = {0};
    //发生时间
    CTime time = CTime::GetCurrentTime();
    CString dateStart = time.Format("%Y-%m-%d 00:00:00");
    CString dateEnd = time.Format("%Y-%m-%d 23:59:59");
    strncpy_s(stSearchParam.sBeginTime, _countof(stSearchParam.sBeginTime), dateStart.GetBuffer(), _TRUNCATE);
    strncpy_s(stSearchParam.sEndTime, _countof(stSearchParam.sEndTime), dateEnd.GetBuffer(), _TRUNCATE);
    //strncpy(stSearchParam.sBeginTime, "2016-03-10 00:00:00", strlen("2016-03-10 00:00:00"));
    //strncpy(stSearchParam.sEndTime, "2016-03-10 23:00:00", strlen("2016-03-10 00:00:00"));

    //确认状态(0:表示全部  1:表示未确认 2:表示已确认)
    stSearchParam.iConfirmState = 0;

    //告警级别(0:无  1:高  2:中  3:低)
    stSearchParam.pLevels = new(std::nothrow)int [3];
    if (NULL != stSearchParam.pLevels)
    {
        stSearchParam.pLevels[0] = 1;
        stSearchParam.pLevels[1] = 2;
        stSearchParam.pLevels[2] = 3;
        stSearchParam.nLevelNum = 3;
    }

    //告警类型
    stSearchParam.pEventTypes = new(std::nothrow)int [6];
    if (NULL != stSearchParam.pEventTypes)
    {
        stSearchParam.pEventTypes[0] = Hik_AlarmEventType_LOSE;
        stSearchParam.pEventTypes[1] = Hik_AlarmEventType_COVER;
        stSearchParam.pEventTypes[2] = Hik_AlarmEventType_MD;
        stSearchParam.pEventTypes[3] = Hik_AlarmEventType_VIDEO_PIR;
        stSearchParam.pEventTypes[4] = Hik_AlarmEventType_VIDEO_WIRELESS;
        stSearchParam.pEventTypes[5] = Hik_AlarmEventType_VIDEO_CALLHELP;
        stSearchParam.nEventTypeNum = 6;
    }

    //排序方式(0:升序  1:降序)
    stSearchParam.iSortType = 0;
    //排序字段名称
    //strncpy_s(stSearchParam.szSortName, _countof(stSearchParam.szSortName), "abc", _TRUNCATE);

    int nListSize = 0;
    pHIKSEARCHALARMLOGRESULT pEventList = new (std::nothrow) HIKSEARCHALARMLOGRESULT[stPageInfo.iPageSize];
    int nRet = HikPt_QueryHistoryAlarmEvent(&stSearchParam,&stPageInfo,pEventList, nListSize);
    if(nRet == 0)
    {
        CString szInfo;
        szInfo.Format("历史告警查询成功，日志条数(%d)",stPageInfo.iPageSize);
        MessageBox(szInfo);
    }
    else
    {
        CString szInfo;
        szInfo.Format("历史告警查询失败");
        MessageBox(szInfo);
    }

    if (NULL != pEventList)
    {
        delete [] pEventList;
    }

    if(NULL != stSearchParam.pTarget)
    {
        freelist<HIKRESOURCE_LIST>(stSearchParam.pTarget);
    }
    if (NULL != stSearchParam.pEventTypes)
    {
        delete []stSearchParam.pEventTypes;
    }
    if (NULL != stSearchParam.pLevels)
    {
        delete []stSearchParam.pLevels;
    }
}

void CPlatSDK_TestDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    OnOK();
}

void CPlatSDK_TestDlg::OnBnClickedButtonQueryGpsInfo()
{
    if (m_szGPSInfo.empty())
    {
        CString szInfo;
        szInfo.Format("GPS信息接收失败");
        MessageBox(szInfo);
    }
    else
    {
        CString szInfo;
        szInfo.Format("GPS信息 %s",m_szGPSInfo.c_str());
        MessageBox(szInfo);
    }
}