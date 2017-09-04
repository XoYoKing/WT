#pragma once
#include "afxcmn.h"


// CCamTree 对话框

class CCamTree : public CDialog
{
	DECLARE_DYNAMIC(CCamTree)

public:
	CCamTree(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCamTree();

// 对话框数据
	enum { IDD = IDD_DLG_CAMTREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
    CImageList m_ImgList;
    afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickTree(NMHDR *, LRESULT *pResult);
//    afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTreePreview();
    afx_msg void OnTreeQuery();
    HTREEITEM FindCamTreeItem(HTREEITEM item, int iData);
    
    virtual BOOL OnInitDialog();
    CTreeCtrl m_CamTreeCtrl;
    CString  m_strIoFctName ;
public:
    void QueryCamResource();
};
