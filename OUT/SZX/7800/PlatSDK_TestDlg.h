
// PlatSDK_TestDlg.h : header file
//

#pragma once

#include "TabSheet.h"
#include "VSSSubsysDlg.h"
#include "ErrorList.h"
#include "AlarmEvent.h"
#include "QueryResult.h"
#include "WTOrder.h"

// CPlatSDK_TestDlg dialog
class CPlatSDK_TestDlg : public CDialog
{
// Construction
public:
	CPlatSDK_TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PLATSDK_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
    

	// Generated message map functions
    void InitControlsPara();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CTabSheet m_TabSubsystem;
    VSSSubsysDlg  m_VSSSubsysDlg;
    CTabSheet m_TabList;
    CErrorList m_ErrorListDlg;
    CAlarmEvent m_AlmEvtInfo;

    CRITICAL_SECTION m_sctAlrEvent;//¶©ÔÄÊÂ¼þËø
    CRITICAL_SECTION m_sctStateList;//¶©ÔÄ×´Ì¬Ëø

    afx_msg void OnDestroy();
    LRESULT OnMsgGetLastError(WPARAM wparam, LPARAM lparam);
    afx_msg void OnBnClickedButtonClearlist();
    afx_msg void OnBnClickedButtonQueryHistoryAlarmlog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonQueryGpsInfo();
    std::string m_szGPSInfo;

//WT Add Start
public:
	CWTOrder m_Order;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//WT Add End
	afx_msg void OnClose();
};
