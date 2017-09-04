// DlgPlayBackWin.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgPlayBackWin.h"
#include "DlgPlayBack.h"

// CDlgPlayBackWin 对话框

IMPLEMENT_DYNAMIC(CDlgPlayBackWin, CDialog)

CDlgPlayBackWin::CDlgPlayBackWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayBackWin::IDD, pParent)
    ,m_iSubPlayBackWndIndex(0)
{

}

CDlgPlayBackWin::~CDlgPlayBackWin()

{
}

void CDlgPlayBackWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPlayBackWin, CDialog)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_STOPPLAYBACK, &CDlgPlayBackWin::OnStopPlayBack)
END_MESSAGE_MAP()


// CDlgPlayBackWin 消息处理程序

void CDlgPlayBackWin::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialog::OnPaint()
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_DRAWBORDER,(WPARAM)GetDlgCtrlID(), (LPARAM)PLAY_BACK_T);
}

void CDlgPlayBackWin::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_FOCUS,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubPlayBackWndIndex);

    CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPlayBackWin::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CMenu pMenu;

    if (!pMenu.LoadMenu(IDR_MENU_PLAYBACK))
    {
        return;
    }
    ClientToScreen(&point);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);	

    CDialog::OnRButtonDown(nFlags, point);
}


void CDlgPlayBackWin::DrawOutputBorder(BOOL IsFocus)
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

    rc.top -= 0;
    rc.left -= 0;
    rc.right += 0;
    rc.bottom += 0;

    CDC *pDC = this->GetDC();
    ASSERT(pDC);

    pDC->SelectStockObject(NULL_BRUSH);
    pOldPen = pDC->SelectObject(&pPen);
    pDC->Rectangle(&rc);

    rc.DeflateRect(1, 1, 1, 1);
    pDC->FillSolidRect(&rc, RGB(40, 40, 40));
    if (pOldPen)
    {
        pDC->SelectObject(pOldPen);
    }
    ReleaseDC(pDC);
}

void CDlgPlayBackWin::OnStopPlayBack()
{
    ::PostMessage(GetParent()->GetSafeHwnd(),WM_STOPPLAYBACK,(WPARAM)GetDlgCtrlID(), (LPARAM)m_iSubPlayBackWndIndex);
}
