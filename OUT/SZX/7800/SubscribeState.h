#pragma once


// CSubscribeState dialog

class CSubscribeState : public CDialog
{
	DECLARE_DYNAMIC(CSubscribeState)

public:
	CSubscribeState(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubscribeState();

// Dialog Data
	enum { IDD = IDD_DLG_SUBSCRIBESTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_ListCtrl;
    int m_Index;
    virtual BOOL OnInitDialog();
};
