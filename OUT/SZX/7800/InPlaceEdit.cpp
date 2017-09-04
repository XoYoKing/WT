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

#include "stdafx.h"
#include "InPlaceEdit.h"

#define CTRL_C    0x3
#define CTRL_V    0x16
#define CTRL_X    0x18

CInPlaceEdit* CInPlaceEdit::m_pInPlaceEdit = NULL;

CInPlaceEdit::CInPlaceEdit()
{
    m_iRowIndex= -1;
    m_iColumnIndex = -1;
    m_bESC = FALSE;
    m_strValidChars.Empty();
}

CInPlaceEdit::~CInPlaceEdit()
{
}

BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
    ON_WM_KILLFOCUS()
    ON_WM_CHAR()
    ON_WM_CREATE()
    ON_MESSAGE(WM_PASTE, OnPaste)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd) 
{
    CEdit::OnKillFocus(pNewWnd);

    // Get the text in the edit ctrl
    CString strEdit;
    GetWindowText(strEdit);

    // Send Notification to parent of edit ctrl
    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;  //lint !e648

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = m_iRowIndex;
    dispinfo.item.iSubItem = m_iColumnIndex;
    dispinfo.item.pszText = m_bESC ? LPTSTR((LPCTSTR)m_strWindowText) : LPTSTR((LPCTSTR)strEdit);
    dispinfo.item.cchTextMax = m_bESC ? m_strWindowText.GetLength() : strEdit.GetLength();
    
    GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);

    PostMessage(WM_CLOSE);
}

void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
     if ((m_strValidChars.IsEmpty()) || ((-1 != m_strValidChars.Find(static_cast<TCHAR> (nChar))) || 
        (nChar == VK_BACK) || (nChar == CTRL_C) || (nChar == CTRL_V) || (nChar == CTRL_X)))
    {
        CEdit::OnChar(nChar, nRepCnt, nFlags);
    }
    else
    {
        return;
    }
}

BOOL CInPlaceEdit::PreTranslateMessage(MSG* pMsg) 
{
    if (WM_KEYDOWN == pMsg->message && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
    {
        if (VK_ESCAPE == pMsg->wParam)
        {
            m_bESC = TRUE;
        }

        GetParent()->SetFocus();
        return TRUE;
    }

    return CEdit::PreTranslateMessage(pMsg);
}

int CInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
        return -1;
    // Set the proper font
    CFont* pFont = GetParent()->GetFont();
    SetFont(pFont);

    ShowWindow(SW_SHOW);
    SetWindowText(m_strWindowText);
    SetSel(0, -1);
    SetLimitText(3);
    SetFocus();

    return 0;
}

CInPlaceEdit* CInPlaceEdit::GetInstance()
{
    if(m_pInPlaceEdit == NULL)
    {
        m_pInPlaceEdit = new CInPlaceEdit;
    }
    return m_pInPlaceEdit;
}

void CInPlaceEdit::DeleteInstance()
{
    delete m_pInPlaceEdit;
    m_pInPlaceEdit = NULL;
}

BOOL CInPlaceEdit::ShowEditCtrl(DWORD dwStyle, const RECT &rCellRect, CWnd* pParentWnd,
                                UINT uiResourceID, int iRowIndex, int iColumnIndex,
                                CString& strValidChars, CString& rstrCurSelection)
{
    m_iRowIndex = iRowIndex;
    m_iColumnIndex = iColumnIndex;
    m_strValidChars = strValidChars;
    m_strWindowText = rstrCurSelection;
    m_bESC = FALSE;

    if (NULL == m_pInPlaceEdit->m_hWnd) 
    {
        return m_pInPlaceEdit->Create(dwStyle, rCellRect, pParentWnd, uiResourceID); 
    }    

    return TRUE;
}

void CInPlaceEdit::PreSubclassWindow()
{
    CEdit::PreSubclassWindow();
}

// ���ε�ճ������
LRESULT CInPlaceEdit::OnPaste(WPARAM  /*pParam*/, LPARAM /*lParam*/)
{
    return FALSE;
}