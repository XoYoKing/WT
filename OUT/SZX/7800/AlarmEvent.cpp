// AlarmEvent.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "AlarmEvent.h"
#include "PlatSDK_TestDlg.h"


// CAlarmEvent dialog

IMPLEMENT_DYNAMIC(CAlarmEvent, CDialog)

CAlarmEvent::CAlarmEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmEvent::IDD, pParent)
{
    m_Index = 0;
}

CAlarmEvent::~CAlarmEvent()
{
}

void CAlarmEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CAlarmEvent, CDialog)
END_MESSAGE_MAP()

void CALLBACK AlarmCallback (const ALARMINFO* pAlrInfo, void *pUser)
{

    if (NULL == pAlrInfo)
    {
        return;
    }

    ALARMINFO Subscribe = *pAlrInfo;

    CPlatSDK_TestDlg *pDlg = (CPlatSDK_TestDlg*)pUser;
    EnterCriticalSection(&pDlg->m_sctAlrEvent);
    if(pDlg->m_AlmEvtInfo.m_Index > 399)
    {
        int j = pDlg->m_AlmEvtInfo.m_ListCtrl.GetItemCount();
        pDlg->m_AlmEvtInfo.m_ListCtrl.DeleteItem(0);
        pDlg->m_AlmEvtInfo.m_Index--;
    }
    //static int i = 0;
    CString csTmp;
    csTmp.Format("%d", Subscribe.iEventId);
    pDlg->m_AlmEvtInfo.m_ListCtrl.InsertItem(pDlg->m_AlmEvtInfo.m_Index, csTmp, 0);
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 1, Subscribe.csEventDesc);
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 2, Subscribe.alarmObjName);

    if(Subscribe.iAlarmLevel == 0)
    {
        csTmp = "低";
    }
    else if (Subscribe.iAlarmLevel == 1)
    {
        csTmp = "中";
    }
    else if (Subscribe.iAlarmLevel)
    {
        csTmp = "高";
    }
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 3, csTmp);
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 4, Subscribe.alarmStarttime);
   
    if (0 == Subscribe.iAlarmStatus)
    {
        csTmp = "瞬时报警";
    }
    else if(Subscribe.iAlarmStatus == 1)
    {
        csTmp = "报警开始";
    }
    else if (Subscribe.iAlarmStatus == 2)
    {
        csTmp = "报警停止";
    }
    else if (Subscribe.iAlarmStatus == 3)
    {
        csTmp = "报警暂停";
    }
    else
    {
        csTmp = "报警更新";
    }
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 5, csTmp);
    csTmp.Format("%s", Subscribe.csLogId);
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 6, csTmp);
    csTmp.Format("%s", Subscribe.csPicUrl);
    pDlg->m_AlmEvtInfo.m_ListCtrl.SetItemText(pDlg->m_AlmEvtInfo.m_Index, 7, csTmp);
    pDlg->m_AlmEvtInfo.m_Index++;
    LeaveCriticalSection(&pDlg->m_sctAlrEvent);
    return;
}

// CAlarmEvent message handlers

BOOL CAlarmEvent::OnInitDialog()
{
    CDialog::OnInitDialog();

    DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_ListCtrl.SetExtendedStyle(dwStyle); //设置扩展风格

    m_ListCtrl.InsertColumn(0, "事件ID",LVCFMT_LEFT,50,-1);
    m_ListCtrl.InsertColumn(1, "报警描述",LVCFMT_LEFT,200,-1);
    m_ListCtrl.InsertColumn(2, "报警类型", LVCFMT_LEFT, 100, -1);
    m_ListCtrl.InsertColumn(3, "报警等级", LVCFMT_LEFT, 80, -1);
    m_ListCtrl.InsertColumn(4, "报警时间", LVCFMT_LEFT, 150, -1);
    m_ListCtrl.InsertColumn(5, "报警状态", LVCFMT_LEFT, 80, -1);
    m_ListCtrl.InsertColumn(6, "报警标识", LVCFMT_LEFT, 100, -1);
    m_ListCtrl.InsertColumn(7, "图片URL", LVCFMT_LEFT, 150, -1);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

