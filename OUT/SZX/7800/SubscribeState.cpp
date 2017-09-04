// SubscribeState.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "SubscribeState.h"
#include "PlatSDK_TestDlg.h"


// CSubscribeState dialog

IMPLEMENT_DYNAMIC(CSubscribeState, CDialog)

CSubscribeState::CSubscribeState(CWnd* pParent /*=NULL*/)
	: CDialog(CSubscribeState::IDD, pParent)
{
    m_Index = 0;
}

CSubscribeState::~CSubscribeState()
{
}

void CSubscribeState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CSubscribeState, CDialog)
END_MESSAGE_MAP()

CString  ConvResType2Str(int iResType)
{
    CString  strTmp = "未知";
    if (PLAT_DEVICE_ENCODER == iResType)
    {
        strTmp = "编码设备";
    }
    else if (PLAT_DEVICE_ACCESS == iResType)
    {
        strTmp = "门禁主机";
    }
    else if (PLAT_DEVICE_PATROL == iResType)
    {
        strTmp = "巡查主机";
    }
    else if (PLAT_DEVICE_ALARM_HOST == iResType)
    {
        strTmp = "报警主机";
    }
    else if (PLAT_RES_CAMERA == iResType)
    {
        strTmp = "监控点";
    }
    else if (PLAT_RES_IO == iResType)
    {
        strTmp = "IO";
    }
    else if (PLAT_RES_DEFENCE_AREA == iResType)
    {
        strTmp = "防区";
    }
    else if (PLAT_RES_DOOR == iResType)
    {
        strTmp = "门禁点";
    }
    return strTmp;
}

CString  ConvState2Str(int iState)
{
    CString  strTmp;
    if (PLAT_STATUS_UNKNOW == iState)
    {
        strTmp = "未知";
    }
    else  if (PLAT_STATUS_NORMAL == iState)
    {
        strTmp = "默认状态/防区未被旁路等";
    }
    else  if (PLAT_STATUS_DEFENCE == iState)
    {
        strTmp = "布防";
    }
    else  if (PLAT_STATUS_DISDEFENCE == iState)
    {
        strTmp = "撤防";
    }
    else  if (PLAT_STATUS_BYPASS == iState)
    {
        strTmp = "旁路";
    }
    else  if (PLAT_STATUS_ACOPEN == iState)
    {
        strTmp = "开门";
    }
    else  if (PLAT_STATUS_ACCLOSE == iState)
    {
        strTmp = "关门";
    }
    else  if (PLAT_STATUS_RELEASE == iState)
    {
        strTmp = "常开";
    }
    else  if (PLAT_STATUS_LOCK == iState)
    {
        strTmp = "常闭";
    }
    else  if (PLAT_STATUS_IOOPEN == iState)
    {
        strTmp = "打开";
    }
    else  if (PLAT_STATUS_IOCLOSE == iState)
    {
        strTmp = "关闭";
    }
    else  if (PLAT_STATUS_ONLINE == iState)
    {
        strTmp = "在线";
    }
    else  if (PLAT_STATUS_OFFLINE == iState)
    {
        strTmp = "离线";
    }
    return strTmp;
}

void CALLBACK fStateCallback(int iResourceid, int iResourceType, int  iResourceState, const char* csStateDesc, void* pUser)
{
    if(PLAT_DEVICE_DECODER == iResourceType)
    {
        return;
    }
    CPlatSDK_TestDlg *pDlg = (CPlatSDK_TestDlg*)pUser;
    EnterCriticalSection(&pDlg->m_sctStateList);
    if(pDlg->m_SubScrState.m_Index > 399)
    {
        pDlg->m_SubScrState.m_ListCtrl.DeleteItem(0);
        pDlg->m_SubScrState.m_Index--;
    }

    CString csTmp;
    csTmp.Format("%d", iResourceid);
    pDlg->m_SubScrState.m_ListCtrl.InsertItem(pDlg->m_SubScrState.m_Index, csTmp, 0);
    csTmp = ConvResType2Str(iResourceType);
    pDlg->m_SubScrState.m_ListCtrl.SetItemText(pDlg->m_SubScrState.m_Index, 1, csTmp);
    csTmp = csStateDesc;
    pDlg->m_SubScrState.m_ListCtrl.SetItemText(pDlg->m_SubScrState.m_Index, 2, csTmp);
    csTmp = ConvState2Str(iResourceState);
    pDlg->m_SubScrState.m_ListCtrl.SetItemText(pDlg->m_SubScrState.m_Index, 3, csTmp);

    pDlg->m_SubScrState.m_Index++;
    LeaveCriticalSection(&pDlg->m_sctStateList);
    return;
}

// CSubscribeState message handlers
BOOL CSubscribeState::OnInitDialog()
{
    CDialog::OnInitDialog();

    DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_ListCtrl.SetExtendedStyle(dwStyle); //设置扩展风格

    m_ListCtrl.InsertColumn(0, "资源ID",LVCFMT_LEFT,100,-1);
    m_ListCtrl.InsertColumn(1, "资源类型",LVCFMT_LEFT,200,-1);
    m_ListCtrl.InsertColumn(2, "名称", LVCFMT_LEFT, 150, -1);
    m_ListCtrl.InsertColumn(3, "状态", LVCFMT_LEFT, 100, -1);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}