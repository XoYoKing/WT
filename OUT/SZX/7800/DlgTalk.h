#pragma once


// CDlgTalk �Ի���

class CDlgTalk : public CDialog
{
	DECLARE_DYNAMIC(CDlgTalk)

public:
	CDlgTalk(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTalk();

// �Ի�������
	enum { IDD = IDD_DLG_TALK };

    int m_nChannel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
};
