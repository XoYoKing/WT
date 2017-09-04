#pragma once


// CErrorList dialog

class CErrorList : public CDialog
{
	DECLARE_DYNAMIC(CErrorList)

public:
	CErrorList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CErrorList();

// Dialog Data
	enum { IDD = IDD_DLG_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_ListError;
    int m_index;
    void InsertLog(const char * oper, int errorcode);
    virtual BOOL OnInitDialog();
    afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
