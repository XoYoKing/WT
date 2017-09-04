// PTZDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "PTZDlg.h"
#include "VSSSubsysDlg.h"
#include "DlgPreview.h"

extern VSSSubsysDlg* g_dlgVSSSubsys;
// CPTZDlg 对话框
extern CDlgPreview*  g_dlgPreview ;

IMPLEMENT_DYNAMIC(CPTZDlg, CDialog)

CPTZDlg::CPTZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTZDlg::IDD, pParent)
{

}

CPTZDlg::~CPTZDlg()
{
}

void CPTZDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_PTZ_UP, m_btnPTZ_up);
    DDX_Control(pDX, IDC_BTN_PTZ_RIGHT, m_btnPTZ_right);
    DDX_Control(pDX, IDC_BTN_PTZ_DOWN, m_btnPTZ_down);
    DDX_Control(pDX, IDC_BTN_PTZ_LEFT, m_btnPTZ_left);
    DDX_Control(pDX, IDC_BTN_PTZ_UPLEFT, m_btnPTZ_upleft);
    DDX_Control(pDX, IDC_BTN_PTZ_DOWNLEFT, m_btnPTZ_leftdown);
    DDX_Control(pDX, IDC_BTN_PTZ_UPRIGHT, m_btnPTZ_rightup);
    DDX_Control(pDX, IDC_BTN_PTZ_DOWNRIGHT, m_btnPTZ_rightdown);
    DDX_Control(pDX, IDC_BTN_PTZ_ZOOMIN, m_btnPTZ_ZoomIn);
    DDX_Control(pDX, IDC_BTN_PTZ_ZOOMOUT, m_btnPTZ_ZoomOut);
    DDX_Control(pDX, IDC_BTN_PTZ_FOCUSNEAR, m_btnPTZ_FocusNear);
    DDX_Control(pDX, IDC_BTN_PTZ_FOCUSFAR, m_btnPTZ_FocusFar);
    DDX_Control(pDX, IDC_BTN_PTZ_IRISCLOSE, m_btnPTZ_IrisClose);
    DDX_Control(pDX, IDC_BTN_PTZ_IRISOPEN, m_btnPTZ_IrisOpen);
    DDX_Control(pDX, IDC_BTN_PTZ_AUTOSCAN, m_btnPTZ_AutoScan);
    DDX_Control(pDX, IDC_BTN_PTZ_SETPRESET, m_btnPTZ_SetPreset);
    DDX_Control(pDX, IDC_BTN_PTZ_CLEPRESET, m_btnPTZ_ClePreset);
    DDX_Control(pDX, IDC_BTN_PTZ_GOTOPRESET, m_btnPTZ_GotoPreset);
    DDX_Control(pDX, IDC_COMBO_PTZSPEED, m_iCombo_PtzSpeed);
    DDX_Control(pDX, IDC_COMBO_PTZPRESET, m_iCombo_PresetIndex);
}


BEGIN_MESSAGE_MAP(CPTZDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO_PTZSPEED, &CPTZDlg::OnCbnSelchangeComboPtzspeed)
    ON_CBN_SELCHANGE(IDC_COMBO_PTZPRESET, &CPTZDlg::OnCbnSelchangeComboPtzpreset)
    ON_BN_CLICKED(IDC_BTN_PTZ_CRUISE, &CPTZDlg::OnBnClickedBtnPtzCruise)
    ON_COMMAND(ID_CRUISE_CONFIG, &CPTZDlg::OnCruiseConfig)
    ON_COMMAND(ID_CRUISE_START, &CPTZDlg::OnCruiseStart)
    ON_COMMAND(ID_CRUISE_STOP, &CPTZDlg::OnCruiseStop)
    ON_BN_CLICKED(IDC_BTN_CAPPIC, &CPTZDlg::OnBnClickedBtnCappic)
    ON_BN_CLICKED(IDC_BTN_STARTRECORD, &CPTZDlg::OnBnClickedBtnStartrecord)
    ON_BN_CLICKED(IDC_BTN_PTZ_STOPRECORD, &CPTZDlg::OnBnClickedBtnPtzStoprecord)
    ON_BN_CLICKED(IDC_BTN_PTZ_LOCK, &CPTZDlg::OnBnClickedBtnPtzLock)
    ON_BN_CLICKED(IDC_BTN_PTZ_UNLOCK, &CPTZDlg::OnBnClickedBtnPtzUnlock)
END_MESSAGE_MAP()


// CPTZDlg 消息处理程序


void CPTZDlg::InitComBox()
{
    m_iCombo_PtzSpeed.ResetContent();
    CString strTemp;
    for(int i=1;i<=7;i++)
    {
        strTemp.Format("%d",i);
        m_iCombo_PtzSpeed.AddString(strTemp);
    }
    m_iCombo_PtzSpeed.SetCurSel(0);
    m_iCombo_PresetIndex.ResetContent();
    for(int i=1;i<=255;i++)
    {
        strTemp.Format("%d",i);
        m_iCombo_PresetIndex.AddString(strTemp);
    }
    m_iCombo_PresetIndex.SetCurSel(0);
    
    m_CruiseDlg.Create(IDD_DLG_CRUISE,this);
}



void CPTZDlg::OnCbnSelchangeComboPtzspeed()
{
    g_dlgPreview->m_iPTZSpeed = m_iCombo_PtzSpeed.GetCurSel()+1;
}

void CPTZDlg::OnCbnSelchangeComboPtzpreset()
{
    g_dlgPreview->m_iPresetIndex = m_iCombo_PresetIndex.GetCurSel()+1;
}

void CPTZDlg::OnBnClickedBtnPtzCruise()
{
    CMenu pMenu;

    if (!pMenu.LoadMenu(IDR_MENU_CRUISE))
    {
        return;
    }
    CRect rc;
    GetDlgItem(IDC_BTN_PTZ_CRUISE)->GetWindowRect(&rc);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, rc.left,rc.bottom, this);
}

void CPTZDlg::OnCruiseConfig()
{
    m_CruiseDlg.ShowWindow(TRUE);
}

void CPTZDlg::OnCruiseStart()
{
    ::PostMessage(m_CruiseDlg.GetSafeHwnd(),WM_STARTCRUISE,NULL,NULL);
}

void CPTZDlg::OnCruiseStop()
{
    ::PostMessage(m_CruiseDlg.GetSafeHwnd(),WM_STOPCRUISE,NULL,NULL);
}
void CPTZDlg::OnBnClickedBtnCappic()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_CAPPIC,NULL,NULL);
}

void CPTZDlg::OnBnClickedBtnStartrecord()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STARTRECORD,NULL,NULL);
}

void CPTZDlg::OnBnClickedBtnPtzStoprecord()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STOPRECORD,NULL,NULL);
}



void CPTZDlg::OnBnClickedBtnPtzLock()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_PTZ_LOCK,NULL,NULL);
}

void CPTZDlg::OnBnClickedBtnPtzUnlock()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_PTZ_UNLOCK,NULL,NULL);
}
