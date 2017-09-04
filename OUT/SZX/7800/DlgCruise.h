#pragma once
#include "afxcmn.h"
#include "ComboListCtrl.h"


// CDlgCruise 对话框

class CDlgCruise : public CDialog
{
    DECLARE_DYNAMIC(CDlgCruise)

public:
    CDlgCruise(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlgCruise();

    // 对话框数据
    enum { IDD = IDD_DLG_CRUISE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    CComboListCtrl m_ListCruise;

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnAdd();
    afx_msg void OnBnClickedBtnDel();
    afx_msg void OnBnClickedBtnOK();
    afx_msg void OnBnClickedBtnCancel();

    BOOL ValidateParam();
    void InitCtrl();
    LRESULT StartCruise(WPARAM wparam, LPARAM lparam);
    LRESULT StopCruise(WPARAM wparam, LPARAM lparam);
};
