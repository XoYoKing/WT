// VSSSubsysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "VSSSubsysDlg.h"
#include "PlatSDK_TestDlg.h"

// VSSSubsysDlg dialog

VSSSubsysDlg* g_dlgVSSSubsys = NULL;
CDlgPlayBack* g_dlgPlayBack = NULL;
CDlgPreview*  g_dlgPreview = NULL;

int g_iMainType;					///< ��ǰ���ڱ��

IMPLEMENT_DYNAMIC(VSSSubsysDlg, CDialog)

VSSSubsysDlg::VSSSubsysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VSSSubsysDlg::IDD, pParent)
{

}

VSSSubsysDlg::~VSSSubsysDlg()
{
}



void VSSSubsysDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_VSSREC_TREE, m_TabTree);
}

BEGIN_MESSAGE_MAP(VSSSubsysDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &VSSSubsysDlg::OnBnClickedButtonPreview)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &VSSSubsysDlg::OnBnClickedButtonPlayback)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// VSSSubsysDlg message handlers

BOOL VSSSubsysDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    g_dlgVSSSubsys = this;
    
    CRect rect;
    CRect VssArea;
    GetDlgItem(IDC_TAB_VSSREC_TREE)->GetClientRect(&rect);
    VssArea.left = rect.right+20 ;

    GetClientRect(&rect);
    VssArea.top = rect.top+4;
    VssArea.bottom = rect.bottom-10;
    VssArea.right = rect.right;

    g_dlgPreview = new CDlgPreview;
    g_dlgPreview->Create(IDD_DLG_PREVIEW, this); ///����Ԥ������
    g_dlgPreview->MoveWindow(&VssArea,TRUE);
    g_dlgPreview->ShowWindow(SW_SHOW);

    g_dlgPlayBack = new CDlgPlayBack;
    g_dlgPlayBack->Create(IDD_DLG_PLAYBACK, this); ///�����طŽ���
    g_dlgPlayBack->MoveWindow(&VssArea,TRUE);
    g_dlgPlayBack->ShowWindow(SW_HIDE);

    g_dlgPreview->InitPreviewDisplay();
    g_iMainType = 0;
    g_dlgPlayBack->InitPlayBackDisplay();

    InitControlsPara();
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void VSSSubsysDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

// ACSSubsysDlg message handlers
void VSSSubsysDlg::InitControlsPara()
{
    m_TabTree.AddPage(_T("��ص�"), &m_CamTree, IDD_DLG_CAMTREE);
    m_TabTree.AddPage(_T("IO"), &m_IoTree, IDD_DLG_IOTREE);
    m_TabTree.AddPage(_T("�Խ�"), &m_TalkTree, IDD_DLG_ALMAREARTREE);
    m_TabTree.AddPage(_T("�û�"), &m_UserTree, IDD_DLG_ALMHOSTTREE);
    m_TabTree.Show();

    m_CamTree.QueryCamResource();
    m_IoTree.QueryIoResource();
    m_TalkTree.QueryTalkResource();
    m_UserTree.QueryUserResource();
}

void VSSSubsysDlg::OnBnClickedButtonPreview()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (g_iMainType != PREVIEW_T)
    {
        g_dlgPlayBack->ShowWindow(SW_HIDE);  //sz 
        g_dlgPreview->ShowWindow(SW_SHOW);
        g_iMainType = PREVIEW_T;
    }
}

void VSSSubsysDlg::OnBnClickedButtonPlayback()
{
    if (g_iMainType != PLAY_BACK_T)
    {
        g_iMainType = PLAY_BACK_T;
        g_dlgPreview->ShowWindow(SW_HIDE);             //���ص�Ԥ���Ի���
        g_dlgPlayBack->ShowWindow(SW_SHOW);  //sz 
    }
}
