#pragma once


// CDlgLogin dialog

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLogin();

    CString strcmsIP;
    int cmsPort;
    CString m_username;
    CString m_password;

// Dialog Data
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

    BOOL OnInitDialog();
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnChangeEditPort();
};
