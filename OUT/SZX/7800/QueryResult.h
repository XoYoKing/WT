#pragma once
#include "afxcmn.h"
#include "SearchResultParser.h"

// CQueryResult 对话框

class CQueryResult : public CDialog
{
	DECLARE_DYNAMIC(CQueryResult)

public:
	CQueryResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryResult();

// 对话框数据
	enum { IDD = IDD_DLG_QUERYRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_lCtrlQueryResult;
    BOOL OnInitDialog();
    void InsertQueryResult(RECORD_SEARCH_RESULT_MAP& pQueryResult,int iFileNum);
};
