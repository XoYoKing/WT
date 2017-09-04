// DlgTalk.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgTalk.h"


// CDlgTalk 对话框

IMPLEMENT_DYNAMIC(CDlgTalk, CDialog)

CDlgTalk::CDlgTalk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTalk::IDD, pParent)
{

}

CDlgTalk::~CDlgTalk()
{
}

void CDlgTalk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTalk, CDialog)
    ON_BN_CLICKED(IDOK, &CDlgTalk::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTalk 消息处理程序

void CDlgTalk::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    m_nChannel = GetDlgItemInt(IDC_EDIT_TALKCHANNEL);
    OnOK();
}
