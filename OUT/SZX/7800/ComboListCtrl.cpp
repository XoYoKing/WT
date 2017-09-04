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
#include "ComboListCtrl.h"
#include "InPlaceCombo.h"
#include "InPlaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#endif

//#defines
#define FIRST_COLUMN                0
#define MIN_COLUMN_WIDTH            10
#define MAX_DROP_DOWN_ITEM_COUNT    10

CComboListCtrl::CComboListCtrl()
{
    m_iColumnCounts = 0;
    m_ComboSupportColumnsList.RemoveAll();
    m_ReadOnlyColumnsList.RemoveAll();
    m_strValidEditCtrlChars.Empty();
    m_dwEditCtrlStyle = ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LEFT | ES_NOHIDESEL | ES_NUMBER;  //yxn20091123
    m_dwDropDownCtrlStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
    m_pInPlaceEdit = NULL;

    for (int iIndex = 0; iIndex < MAX_LISTCTRL_COLUMNS; iIndex++)
    {
        m_modeColumn[iIndex] = MODE_READONLY;
    }
}

CComboListCtrl::~CComboListCtrl()
{
    try
    {
        CInPlaceCombo::DeleteInstance();
        CInPlaceEdit::DeleteInstance();
    }
    catch(...)
    {
    }

    m_pInPlaceEdit = NULL;
}


//lint -save -e648
// Overflow in computing constant for operation: 'unsigned sub.'
BEGIN_MESSAGE_MAP(CComboListCtrl, CListCtrl)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEWHEEL()
    ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginLabelEdit)
END_MESSAGE_MAP()
//lint -restore

CInPlaceCombo* CComboListCtrl::ShowInPlaceList(int iRowIndex, int iColumnIndex, CStringList& rComboItemsList, 
                                               CString strCurSelecetion /*= ""*/, int iSel /*= -1*/)
{
    // The returned obPointer should not be saved
    
    // Make sure that the item is visible
    if (!EnsureVisible(iRowIndex, TRUE))
    {
        return NULL;
    }

    // Make sure that iColumnIndex is valid 
    CHeaderCtrl* pHeader = static_cast<CHeaderCtrl*> (GetDlgItem(FIRST_COLUMN));

    int iColumnCount = pHeader->GetItemCount();

    if (iColumnIndex >= iColumnCount || GetColumnWidth(iColumnIndex) < MIN_COLUMN_WIDTH) 
    {
        return NULL;
    }

    // Calculate the rectangle specifications for the combo box
    CRect obCellRect(0, 0, 0, 0);
    CalculateCellRect(iColumnIndex, iRowIndex, obCellRect);

    int iHeight = obCellRect.Height();  
    int iCount = (int )rComboItemsList.GetCount();

    iCount = (iCount < MAX_DROP_DOWN_ITEM_COUNT) ? 
        iCount + MAX_DROP_DOWN_ITEM_COUNT : (MAX_DROP_DOWN_ITEM_COUNT + 1); 

    obCellRect.bottom += iHeight * iCount; 

    // Create the in place combobox
    CInPlaceCombo* pInPlaceCombo = CInPlaceCombo::GetInstance();
    pInPlaceCombo->ShowComboCtrl(m_dwDropDownCtrlStyle, obCellRect, this, 0, iRowIndex, iColumnIndex, &rComboItemsList, 
                                 strCurSelecetion, iSel);
    
    return pInPlaceCombo;
}

CInPlaceEdit* CComboListCtrl::ShowInPlaceEdit(int iRowIndex, int iColumnIndex, CString& rstrCurSelection)
{
    // Create an in-place edit control
    CInPlaceEdit* pInPlaceEdit = CInPlaceEdit::GetInstance();
        
    CRect obCellRect(0, 0, 0, 0);
    CalculateCellRect(iColumnIndex, iRowIndex, obCellRect);
            
    pInPlaceEdit->ShowEditCtrl(m_dwEditCtrlStyle, obCellRect, this, 0,
                               iRowIndex, iColumnIndex,
                               m_strValidChars[iColumnIndex], rstrCurSelection);

    return pInPlaceEdit;
}

void CComboListCtrl::OnHScroll(UINT iSBCode, UINT iPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this)
    {
        SetFocus();
    }

    CListCtrl::OnHScroll(iSBCode, iPos, pScrollBar);
}

void CComboListCtrl::OnVScroll(UINT iSBCode, UINT iPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this)
    {
        SetFocus();
    }

    CListCtrl::OnVScroll(iSBCode, iPos, pScrollBar);
}

void CComboListCtrl::OnLButtonUp(UINT iFlags, CPoint obPoint) 
{
    int iColumnIndex = -1;
    int iRowIndex = -1;

    // Get the current column and row
    if (!HitTestEx(obPoint, &iRowIndex, &iColumnIndex))
    {
        return;
    }

    CListCtrl::OnLButtonUp(iFlags, obPoint);
    
    // If column is not read only then
    // If the SHIFT or CTRL key is down call the base class
    // Check the high bit of GetKeyState to determine whether SHIFT or CTRL key is down
    if ((GetKeyState(VK_SHIFT) & 0x80) || (GetKeyState(VK_CONTROL) & 0x80))
    {
        return;
    }

    // Get the current selection before creating the in place combo box
    CString strCurSelection = GetItemText(iRowIndex, iColumnIndex);
    
    if (-1 != iRowIndex)
    {
        UINT flag = LVIS_FOCUSED;
        
        if ((GetItemState(iRowIndex, flag ) & flag) == flag)
        {
            // Add check for LVS_EDITLABELS
            if (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS)
            {
                // If combo box is supported
                // Create and show the in place combo box
                if (IsCombo(iColumnIndex))
                {
                    CStringList obComboItemsList;
                                        
                    GetParent()->SendMessage(WM_SET_ITEMS, (WPARAM)iColumnIndex, (LPARAM)&obComboItemsList); 

                    // GetParent()->GetParent()->GetParent()->SendMessage(WM_SET_ITEMS, (WPARAM)iColumnIndex, (LPARAM)&obComboItemsList);  // yxn20090819
                    
                    CInPlaceCombo* pInPlaceComboBox = ShowInPlaceList(iRowIndex, iColumnIndex, obComboItemsList, strCurSelection);
                    //ASSERT(pInPlaceComboBox); 
                    if (NULL == pInPlaceComboBox)
                    {
                        return;
                    }
                    
                    // Set the selection to previous selection
                    pInPlaceComboBox->SelectString(-1, strCurSelection);
                }
                // If combo box is not read only
                // Create and show the in place edit control
                else if (!IsReadOnly(iColumnIndex))
                {
                    if (m_pInPlaceEdit)
                    {
                        CInPlaceEdit::DeleteInstance();
                    }
                    m_pInPlaceEdit = ShowInPlaceEdit(iRowIndex, iColumnIndex, strCurSelection);

                }
            }
        }
    }  
}

bool CComboListCtrl::HitTestEx(CPoint &obPoint, int* pRowIndex, int* pColumnIndex) const
{
    if (!pRowIndex || !pColumnIndex)
    {
        return false;
    }

    // Get the row index
    *pRowIndex = HitTest(obPoint, NULL);

    if (pColumnIndex)
    {
        *pColumnIndex = 0;
    }

    // Make sure that the ListView is in LVS_REPORT
    if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
    {
        return false;
    }

    // Get the number of columns
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);

    int iColumnCount = pHeader->GetItemCount();

    // Get bounding rect of item and check whether obPoint falls in it.
    CRect obCellRect;
    GetItemRect(*pRowIndex, &obCellRect, LVIR_BOUNDS);
    
    if (obCellRect.PtInRect(obPoint))
    {
        // Now find the column
        for (*pColumnIndex = 0; *pColumnIndex < iColumnCount; (*pColumnIndex)++)
        {
            int iColWidth = GetColumnWidth(*pColumnIndex);
            
            if (obPoint.x >= obCellRect.left && obPoint.x <= (obCellRect.left + iColWidth))
            {
                return true;
            }
            obCellRect.left += iColWidth;
        }
    }
    return false;
}

void CComboListCtrl::SetComboColumns(int iColumnIndex, bool bSet /*= true*/)
{
    // If the Column Index is not present && Set flag is false
    // Then do nothing 
    // If the Column Index is present && Set flag is true
    // Then do nothing
    POSITION Pos = m_ComboSupportColumnsList.Find(iColumnIndex);

    // If the Column Index is not present && Set flag is true
    // Then Add to list
    if ((NULL == Pos) && bSet) 
    {
        m_ComboSupportColumnsList.AddTail(iColumnIndex); 
    }

    // If the Column Index is present && Set flag is false
    // Then Remove from list
    if ((NULL != Pos) && !bSet) 
    {
        m_ComboSupportColumnsList.RemoveAt(Pos); 
    }
}

void CComboListCtrl::SetReadOnlyColumns(int iColumnIndex, bool bSet /*= true*/)
{
    // If the Column Index is not present && Set flag is false
    // Then do nothing 
    // If the Column Index is present && Set flag is true
    // Then do nothing
    POSITION Pos = m_ReadOnlyColumnsList.Find(iColumnIndex);

    // If the Column Index is not present && Set flag is true
    // Then Add to list
    if ((NULL == Pos) && bSet) 
    {
        m_ReadOnlyColumnsList.AddTail(iColumnIndex);
    }

    // If the Column Index is present && Set flag is false
    // Then Remove from list
    if ((NULL != Pos) && !bSet) 
    {
        m_ReadOnlyColumnsList.RemoveAt(Pos);
    }
}

bool CComboListCtrl::IsReadOnly(int iColumnIndex)
{
    if (m_ReadOnlyColumnsList.Find(iColumnIndex))
    {
        return true;
    }
    
    return false;
}

bool CComboListCtrl::IsCombo(int iColumnIndex)
{
    if (m_ComboSupportColumnsList.Find(iColumnIndex))
    {
        return true;
    }

    return false;
}

void CComboListCtrl::CalculateCellRect(int iColumnIndex, int iRowIndex, CRect& robCellRect)
{
    GetItemRect(iRowIndex, &robCellRect, LVIR_BOUNDS);
    
    CRect rcClient;
    GetClientRect(&rcClient);

    if (robCellRect.right > rcClient.right)
    {
        robCellRect.right = rcClient.right;
    }

    ScrollToView(iColumnIndex, robCellRect);
}

void CComboListCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

    SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, pDispInfo->item.pszText);

    GetParent()->SendMessage(WM_VALIDATE, GetDlgCtrlID(), (LPARAM)pDispInfo);
    
    *pResult = 0;
}

void CComboListCtrl::SetValidEditCtrlCharacters(CString &rstrValidCharacters)
{
    m_strValidEditCtrlChars = rstrValidCharacters;
}

void CComboListCtrl::SetColumnValidEditCtrlCharacters(CString &rstrValidCharacters,int column)
{
    if(column>MAX_LISTCTRL_COLUMNS-1)
        return;
    if(column == -1)
    {
        for(int i=0;i<MAX_LISTCTRL_COLUMNS;i++)
        {
            m_strValidChars[i] = rstrValidCharacters;
        }
    }
    else
        m_strValidChars[column] = rstrValidCharacters;
}

void CComboListCtrl::EnableHScroll(bool bEnable /*= true*/)
{
    if (bEnable)
    {
        m_dwDropDownCtrlStyle |= WS_HSCROLL;
    }
    else
    {
        m_dwDropDownCtrlStyle &= ~WS_HSCROLL;
    }    
}

void CComboListCtrl::EnableVScroll(bool bEnable /*= true*/)
{
    if (bEnable)
    {
        m_dwDropDownCtrlStyle |= WS_VSCROLL;
    }
    else
    {
        m_dwDropDownCtrlStyle &= ~WS_VSCROLL;
    }
}

void CComboListCtrl::ScrollToView(int iColumnIndex, /*int iOffSet, */CRect& robCellRect)
{
    CRect rcClient;
    GetClientRect(&rcClient);

    int iColumnWidth = GetColumnWidth(iColumnIndex);

    int iOffSet = 0;
    for (int iIndex_ = 0; iIndex_ < iColumnIndex; iIndex_++)
    {
        iOffSet += GetColumnWidth(iIndex_);
    }

    CSize obScrollSize(0, 0);

    if (((iOffSet + robCellRect.left) < rcClient.left) || 
        ((iOffSet + robCellRect.left) > rcClient.right))
    {
        obScrollSize.cx = iOffSet + robCellRect.left;
    }
    else if ((iOffSet + robCellRect.left + iColumnWidth) > rcClient.right)
    {
        obScrollSize.cx = iOffSet + robCellRect.left + iColumnWidth - rcClient.right;
    }

    Scroll(obScrollSize);
    robCellRect.left -= obScrollSize.cx;
    
    robCellRect.left += iOffSet;
    robCellRect.right = robCellRect.left + iColumnWidth;
}

void CComboListCtrl::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    if (IsReadOnly(pDispInfo->item.iSubItem))
    {
        *pResult = 1;
        return;
    }

    *pResult = 0;
}

int CComboListCtrl::InsertColumn(int nCol,LPCTSTR lpszColumnHeading,int nFormat ,int nWidth,int nSubItem)
{
    m_iColumnCounts++;
    return CListCtrl::InsertColumn( nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}

int CComboListCtrl::GetColumnCounts()
{
    return m_iColumnCounts;
}

void CComboListCtrl::DeleteAllColumn()
{
    for(int i=0;i<m_iColumnCounts;i++)
    {
        DeleteColumn(0);
    }
}

LRESULT CComboListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message==WM_VSCROLL||message==WM_HSCROLL)
    {
        WORD sbCode=LOWORD(wParam);
        if(sbCode==SB_THUMBTRACK
            ||sbCode==SB_THUMBPOSITION)
        {
            SCROLLINFO siv={0};
            siv.cbSize=sizeof(SCROLLINFO);
            siv.fMask=SIF_ALL;
            SCROLLINFO sih=siv;
            int nPos=HIWORD(wParam);
            CRect rcClient;
            GetClientRect(&rcClient);
            GetScrollInfo(SB_VERT,&siv);
            GetScrollInfo(SB_HORZ,&sih);
            SIZE sizeAll;
            if(sih.nPage==0) 
                sizeAll.cx=rcClient.right;
            else
                sizeAll.cx=rcClient.right*(sih.nMax+1)/ static_cast<int>(sih.nPage) ;
            if(siv.nPage==0)
                sizeAll.cy=rcClient.bottom;
            else
                sizeAll.cy=rcClient.bottom*(siv.nMax+1)/ static_cast<int>(siv.nPage) ;

            SIZE size={0,0};
            if(WM_VSCROLL==message)
            {
                size.cx=sizeAll.cx*sih.nPos/(sih.nMax+1);
                size.cy=sizeAll.cy*(nPos-siv.nPos)/(siv.nMax+1);
            }else
            {
                size.cx=sizeAll.cx*(nPos-sih.nPos)/(sih.nMax+1);
                size.cy=sizeAll.cy*siv.nPos/(siv.nMax+1);
            }

            Scroll(size);

            if (GetFocus() != this)
            {
                SetFocus();
            }

            return 1;
        }
    }
    return CListCtrl::WindowProc(message, wParam, lParam);
}

int CComboListCtrl::GetFirstVisableItem()
{
    CRect clientRC;
    GetClientRect(&clientRC);
    CRect itemRC;
    int iCount = GetItemCount();
    for (int i = 0; i < iCount; i++)
    {
        GetItemRect(i,itemRC,LVIR_BOUNDS);
        if (itemRC.top>= clientRC.top && itemRC.bottom <= clientRC.bottom)
        {
            return i;
        }
    }
    return -1;
}

BOOL CComboListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
    if (GetFocus() != this)
    {
        SetFocus();
    }

    return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}
