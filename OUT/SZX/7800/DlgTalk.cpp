// DlgTalk.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgTalk.h"


// CDlgTalk �Ի���

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


// CDlgTalk ��Ϣ�������

void CDlgTalk::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_nChannel = GetDlgItemInt(IDC_EDIT_TALKCHANNEL);
    OnOK();
}
