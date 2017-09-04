/*******************************************************************************
    Author                        : Aravindan Premkumar
    Unregistered Copyright 2003    : Aravindan Premkumar
    All Rights Reserved
    
    This piece of code does not have any registered copyright and is free to be 
    used as necessary. The user is free to modify as per the requirements. As a
    fellow developer, all that I expect and request for is to be given the 
    credit for intially developing this reusable code by not removing my name as 
    the author.
*******************************************************************************/

#if !defined(AFX_INPLACEEDIT_H__175AEDFF_731E_4721_8399_DE406A465861__INCLUDED_)
#define AFX_INPLACEEDIT_H__175AEDFF_731E_4721_8399_DE406A465861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CInPlaceEdit : public CEdit
{

public:
    
// Implementation
    
    // Returns the instance of the class
    static CInPlaceEdit* GetInstance(); 

    // Deletes the instance of the class
    static void DeleteInstance(); 

    // Creates the Windows edit control and attaches it to the object
    // Shows the edit ctrl
    BOOL ShowEditCtrl(DWORD dwStyle, const RECT& rCellRect, CWnd* pParentWnd, 
                      UINT uiResourceID, int iRowIndex, int iColumnIndex,
                      CString& strValidChars, CString& rstrCurSelection);

    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);

protected:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

private:
    CInPlaceEdit();
    virtual ~CInPlaceEdit();

    // Index of the item in the list control
    int m_iRowIndex;

    // Index of the subitem in the list control
    int m_iColumnIndex;

    // To indicate whether ESC key was pressed
    BOOL m_bESC;
    
    // Valid characters
    CString m_strValidChars;

    // Singleton instance
    static CInPlaceEdit* m_pInPlaceEdit;

    // Previous string value in the edit control
    CString m_strWindowText;
protected:
    virtual void PreSubclassWindow();
public:
};

#endif
