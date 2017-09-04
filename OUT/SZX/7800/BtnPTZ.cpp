// BtnPTZ.cpp : implementation file
//

#include "stdafx.h"
#include "BtnPTZ.h"
//#include "VSSSubsysDlg.h"

//extern VSSSubsysDlg* g_dlgVSSSubsys;

// CBtnPTZ

IMPLEMENT_DYNAMIC(CBtnPTZ, CButton)

CBtnPTZ::CBtnPTZ()
{

}

CBtnPTZ::~CBtnPTZ()
{
}


BEGIN_MESSAGE_MAP(CBtnPTZ, CButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CBtnPTZ message handlers



void CBtnPTZ::OnLButtonDown(UINT nFlags, CPoint point)
{
    ::PostMessage(GetParent()->GetParent()->GetSafeHwnd(), WM_PTZ, (WPARAM)GetDlgCtrlID(), (LPARAM)1);

    CButton::OnLButtonDown(nFlags, point);
}

void CBtnPTZ::OnLButtonUp(UINT nFlags, CPoint point)
{
    ::PostMessage(GetParent()->GetParent()->GetSafeHwnd(), WM_PTZ, (WPARAM)GetDlgCtrlID(), (LPARAM)0);

    CButton::OnLButtonUp(nFlags, point);
}
