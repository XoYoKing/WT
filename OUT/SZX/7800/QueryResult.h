#pragma once
#include "afxcmn.h"
#include "SearchResultParser.h"

// CQueryResult �Ի���

class CQueryResult : public CDialog
{
	DECLARE_DYNAMIC(CQueryResult)

public:
	CQueryResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQueryResult();

// �Ի�������
	enum { IDD = IDD_DLG_QUERYRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_lCtrlQueryResult;
    BOOL OnInitDialog();
    void InsertQueryResult(RECORD_SEARCH_RESULT_MAP& pQueryResult,int iFileNum);
};
