#pragma once
#include "afxcmn.h"
#include "ComboListCtrl.h"


// CDlgCruise �Ի���

class CDlgCruise : public CDialog
{
    DECLARE_DYNAMIC(CDlgCruise)

public:
    CDlgCruise(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CDlgCruise();

    // �Ի�������
    enum { IDD = IDD_DLG_CRUISE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
