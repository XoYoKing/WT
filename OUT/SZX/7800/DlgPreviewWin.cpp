// DlgPreview.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgPreviewWin.h"
#include "VSSSubsysDlg.h"

extern VSSSubsysDlg* g_dlgVSSSubsys;

// CDlgPreviewWin 对话框

IMPLEMENT_DYNAMIC(CDlgPreviewWin, CDialog)

CDlgPreviewWin::CDlgPreviewWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreviewWin::IDD, pParent)
{

}

CDlgPreviewWin::~CDlgPreviewWin()
{
}

void CDlgPreviewWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPreviewWin, CDialog)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_STOPPLAY, &CDlgPreviewWin::OnStopplay)
    ON_COMMAND(ID_STARTTVWALL, &CDlgPreviewWin::OnStartTvWall)
    ON_COMMAND(ID_STOPTVWALL, &CDlgPreviewWin::OnStopTvWall)

END_MESSAGE_MAP()



void CDlgPreviewWin::DrawOutputBorder(BOOL IsFocus)
{
    if (!IsWindowVisible())
    {
        return;
    }
    CPen *pOldPen = NULL;
    CPen pPen;
    CRect rc(0,0,0,0);

    this->GetWindowRect(&rc);
    this->ScreenToClient(&rc);

    if (IsFocus)
    {
        pPen.CreatePen(PS_SOLID, 2, RGB(0,255,0));
    }
    else
    {
        pPen.CreatePen(PS_SOLID, 2, RGB(125, 125, 116));
    }

     rc.top += 0;
     rc.left += 0;
    rc.right += 0;
    rc.bottom += 0;

    CClientDC dc(this);
    //CDC *pDC = this->GetDC();
    //ASSERT(pDC);

    dc.SelectStockObject(NULL_BRUSH);
    pOldPen = dc.SelectObject(&pPen);
    dc.Rectangle(&rc);
    // dc.FrameRect(&rc, CBrush::FromHandle( (HBRUSH)GetStockObject(BLACK_BRUSH)));
    rc.DeflateRect(1, 1, 1, 1);
    dc.FillSolidRect(&rc, RGB(40, 40, 40));
    if (pOldPen)
    {
        dc.SelectObject(pOldPen);
    }
    //ReleaseDC(pDC);
}
void CDlgPreviewWin::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialog::OnPaint()
     ::PostMessage(GetParent()->GetSafeHwnd(),WM_DRAWBORDER,(WPARAM)GetDlgCtrlID(), (LPARAM)0);

}

void CDlgPreviewWin::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_FOCUS,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubWndIndex);
    CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPreviewWin::OnRButtonDown(UINT nFlags, CPoint point)
{
    CMenu pMenu;

    if (!pMenu.LoadMenu(IDR_MENU_PREVIEW))
    {
        return;
    }
    ClientToScreen(&point);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);	


    CDialog::OnRButtonDown(nFlags, point);
}

void CDlgPreviewWin::OnStopplay()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STOPPLAY,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubWndIndex);
}

void CDlgPreviewWin::OnStartTvWall()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STARTTVWALL,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubWndIndex);
}

void CDlgPreviewWin::OnStopTvWall()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STOPTVWALL,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubWndIndex);
}
