#pragma once


// CIOTree dialog

class CIOTree : public CDialog
{
	DECLARE_DYNAMIC(CIOTree)

public:
	CIOTree(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIOTree();

// Dialog Data
	enum { IDD = IDD_DLG_IOTREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CTreeCtrl  m_TreeCtrl;
    CImageList  m_ImgList;
    static CString  g_strIoFctName;
    HTREEITEM FindIoTreeItem(HTREEITEM item, int iData);
    void QueryIoResource();
    virtual BOOL OnInitDialog();
    CString  StateConvStr(int iDoorState);
    afx_msg void OnNMRClickTreeIo(NMHDR *pNMHDR, LRESULT *pResult);
};
