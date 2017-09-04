#pragma once
#include "TabSheet.h"
#include "TalkTree.h"
#include "UserTree.h"
#include "IOTree.h"
#include "CamTree.h"
#include "afxwin.h"
#include "DlgPlayBack.h"
#include "DlgPlayBackWin.h" 
#include "DlgPreview.h"
#include "DlgPreviewWin.h"

// VSSSubsysDlg dialog

class VSSSubsysDlg : public CDialog
{
	DECLARE_DYNAMIC(VSSSubsysDlg)

public:
	VSSSubsysDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VSSSubsysDlg();

// Dialog Data
	enum { IDD = IDD_DLG_VSS_SUBSYS };

protected:
    void InitControlsPara();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CTabSheet   m_TabTree;
    CIOTree     m_IoTree;
    CCamTree    m_CamTree;
    CTalkTree   m_TalkTree;
    CUserTree   m_UserTree;
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonPreview();
    afx_msg void OnBnClickedButtonPlayback();
    afx_msg void OnPaint();
};


