#pragma once


// CAlmHost dialog

class CUserTree : public CDialog
{
	DECLARE_DYNAMIC(CUserTree)

public:
	CUserTree(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserTree();

// Dialog Data
	enum { IDD = IDD_DLG_ALMHOSTTREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CTreeCtrl  m_TreeCtrl;
    CImageList  m_ImgList;
    static CString  g_strAHFctName;
    HTREEITEM FindUserTreeItem(HTREEITEM item, int iData);
    void QueryUserResource();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMRClickTreeAlmhost(NMHDR *pNMHDR, LRESULT *pResult);
    CString  StateConvStr(int iDoorState);
};
