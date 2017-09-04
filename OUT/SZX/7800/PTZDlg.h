#pragma once

#include "BtnPTZ.h"
#include "afxwin.h"
#include "DlgCruise.h"
// CPTZDlg 对话框

class CPTZDlg : public CDialog
{
	DECLARE_DYNAMIC(CPTZDlg)

public:
	CPTZDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPTZDlg();

// 对话框数据
	enum { IDD = IDD_DLG_PTZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CBtnPTZ m_btnPTZ_up;
    CBtnPTZ m_btnPTZ_right;
    CBtnPTZ m_btnPTZ_down;
    CBtnPTZ m_btnPTZ_left;
    CBtnPTZ m_btnPTZ_upleft;
    CBtnPTZ m_btnPTZ_leftdown;
    CBtnPTZ m_btnPTZ_rightup;
    CBtnPTZ m_btnPTZ_rightdown;
    CBtnPTZ m_btnPTZ_ZoomIn;
    CBtnPTZ m_btnPTZ_ZoomOut;
    CBtnPTZ m_btnPTZ_FocusNear;
    CBtnPTZ m_btnPTZ_FocusFar;
    CBtnPTZ m_btnPTZ_IrisClose;
    CBtnPTZ m_btnPTZ_IrisOpen;
    CBtnPTZ m_btnPTZ_AutoScan;
    CBtnPTZ m_btnPTZ_SetPreset;
    CBtnPTZ m_btnPTZ_ClePreset;
    CBtnPTZ m_btnPTZ_GotoPreset;
    afx_msg void OnCbnSelchangeComboPtzspeed();
    CComboBox m_iCombo_PtzSpeed;
    CComboBox m_iCombo_PresetIndex;
    void InitComBox();
    afx_msg void OnCbnSelchangeComboPtzpreset();
    afx_msg void OnBnClickedBtnPtzCruise();
    afx_msg void OnCruiseConfig();
    afx_msg void OnCruiseStart();
    afx_msg void OnCruiseStop();

    CDlgCruise m_CruiseDlg;
    afx_msg void OnBnClickedBtnCappic();
    afx_msg void OnBnClickedBtnStartrecord();
    afx_msg void OnBnClickedBtnPtzStoprecord();
    afx_msg void OnBnClickedBtnPtzLock();
    afx_msg void OnBnClickedBtnPtzUnlock();
};
