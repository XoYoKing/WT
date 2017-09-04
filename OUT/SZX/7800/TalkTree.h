#pragma once


// CAlmArea dialog

class CTalkTree : public CDialog
{
	DECLARE_DYNAMIC(CTalkTree)

public:
	CTalkTree(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTalkTree();

// Dialog Data
	enum { IDD = IDD_DLG_ALMAREARTREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CTreeCtrl  m_TreeCtrl;
    CImageList  m_ImgList;
    static CString  g_strAreaFctName;
    HTREEITEM FindTalkTreeItem(HTREEITEM item, int iData);
    void QueryTalkResource();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMRClickTreeAlmarea(NMHDR *pNMHDR, LRESULT *pResult);
};
