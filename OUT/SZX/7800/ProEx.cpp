// ProEx.cpp : implementation file
//

#include "stdafx.h"
#include "ProEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProEx
CProEx::CProEx()
{
	m_lastpos=0;
	m_steplength=0;
	m_nsteps=1;
	m_max=100;
	m_min=0;
	m_backColor=0x00ff00ff;

}
CProEx::~CProEx()
{
}

BEGIN_MESSAGE_MAP(CProEx, CProgressCtrl)
	//{{AFX_MSG_MAP(ProEx)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProEx message handlers
//设置颜色
void CProEx::SetColor(COLORREF start,COLORREF end,COLORREF BackColor,COLORREF FontColor)
{	
    GetClientRect(&m_rect);

	int mr=GetRValue(end)-GetRValue(start);
	int mg=GetGValue(end)-GetGValue(start);
	int mb=GetBValue(end)-GetBValue(start);
	if((mr|mr|mg)==0)
	{
		mr=GetRValue(start);
		mg=GetGValue(start);
		mb=GetBValue(start);
	}
	//保存没像素对应的长度
	m_scale.r=1.0*mr/m_rect.Width();
	m_scale.g=1.0*mg/m_rect.Width();
	m_scale.b=1.0*mb/m_rect.Width();
	
	//保存初始颜色
	m_color.Set(start);
	m_backColor=BackColor;//背景色
	m_fontColor=FontColor;
}
//设置步长
void CProEx::SetProStep(int step)
{

		GetClientRect(&m_rect);
        m_steplength=1.0*m_rect.Width()/(m_max-m_min)*step;
    	m_nsteps=step;
}

//设置范围和步长
void CProEx::SetProRange(int min,int max,int step)
{
	if(min>=max)return;

	m_max=max;
	m_min=min;
	m_lastpos=m_min;
	m_increase=1.0*100/(m_max-m_min);

    SetProStep(step);

	m_scale.r*=m_steplength;
	m_scale.g*=m_steplength;
    m_scale.b*=m_steplength;
	
}
//增加
void CProEx::StepProIt()
{
	m_lastpos+=m_nsteps;
	SetProPos(m_lastpos);
}
//设置位置
void CProEx::SetProPos(int pos)
{
	if(pos>m_max||pos<m_min||m_min>=m_max)
		return;

	    CDC mdc;
	    CBitmap nbmp,*old;
		CDC *pDC=GetDC();
		

		mdc.CreateCompatibleDC(pDC);
        nbmp.CreateCompatibleBitmap(pDC,m_rect.Width(),m_rect.Height());
		old=mdc.SelectObject(&nbmp);

	
	    DrawProEx(m_lastpos,&mdc);
	    DrawPercent(m_lastpos,&mdc);
		

	
		pDC->BitBlt(0,0,m_rect.Width(),m_rect.Height(),&mdc,0,0,SRCCOPY);

		ReleaseDC(pDC);

		nbmp.DeleteObject();
		mdc.SelectObject(old);
	    mdc.DeleteDC();

        m_lastpos=pos;
}


//画条目
void CProEx::DrawProEx(int position,CDC*pDC)
{	
	   pDC->FillSolidRect(m_rect,m_backColor);

	   BYTE R=m_color.r,G=m_color.g,B=m_color.b;
	   CRect rect;
	   CBrush brush,*old;
	   double curpos=0;

		for(int index=0;index<=position;index++)	
		{
          brush.CreateSolidBrush(RGB(R,G,B));
		  R+=	(BYTE)m_scale.r;
		  G+=	(BYTE)m_scale.g;
		  B+=	(BYTE)m_scale.b;
		
	     old=pDC->SelectObject(&brush);
	 	 
		 rect.SetRect((int)(curpos),0,(int)(curpos+m_steplength+0.5),m_rect.Height());
		 
	     pDC->FillRect(&rect,&brush);
		 pDC->SelectObject(old);
	  	 brush.DeleteObject();

		 curpos+=m_steplength;
		}
}
//显示百分比
void CProEx::DrawPercent(int position,CDC*pDC)
{
		CString str;
		int precent=(int)(m_increase*position+1);
		str.Format("%d%%",precent>100?100:precent);
		pDC->SetTextColor(m_fontColor);
	    int mode=pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(str,m_rect,DT_CENTER);

		pDC->SetBkMode(mode);
}

//刷新时重绘
BOOL CProEx::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
		 
	if(m_lastpos!=m_min)
	{
	    DrawProEx(m_lastpos,pDC);
	    DrawPercent(m_lastpos,pDC);	

	}
	  
	 return true;
}

//重新开始
void CProEx::ReStart()
{
	m_lastpos=m_min;
}
//===============================

