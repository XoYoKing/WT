#if !defined(AFX_PROEX_H__58E4C891_2856_45EC_A4CC_D247F6957F7B__INCLUDED_)
#define AFX_PROEX_H__58E4C891_2856_45EC_A4CC_D247F6957F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProEx.h : header file
//
template<class Type>
struct SColor
{
    Type r;
    Type g;
    Type b;
    SColor()
    {
        r=0;g=0;b=0;	
    }
    SColor(BYTE cr,BYTE cg,BYTE cb)
    {
        r=cr;
        g=cg;
        b=cb;	
    }
    //保存颜色信息
    void Set(COLORREF color)
    {
        r=GetRValue(color);
        g=GetGValue(color);
        b=GetBValue(color);
    }
};
/////////////////////////////////////////////////////////////////////////////
// ProEx window
class CProEx : public CProgressCtrl
{
// Construction
public:
	CProEx();

// Attributes
public:

// Operations
public:
        void SetProStep(int step);///设置步长
        void SetProPos(int pos);//
		void SetProRange(int min=0,int max=100,int step=1);
		void SetColor(COLORREF start,COLORREF end,
			COLORREF BackColor=0x00ffffff,COLORREF FontColor=0x00ffffff);
		void StepProIt();
		void ReStart();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProEx();

	// Generated message map functions
protected:

	BYTE m_nsteps;// 记录步长
	double m_steplength;//记录每步实际长
	double m_increase;

    int m_max;//记录上限
	int m_min;//记录下限
	
	int m_lastpos;//记录上次进度条位置


	CRect m_rect;//记录进度条的矩形

	SColor<BYTE>m_color;//保存原始颜色
	SColor<double>m_scale;//保存颜色比列
	COLORREF m_backColor;//背景色
	COLORREF m_fontColor;//字体颜色



private:
	void DrawProEx(int position,CDC*pDC);
	void DrawPercent(int position,CDC*pDC);
	//{{AFX_MSG(ProEx)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROEX_H__58E4C891_2856_45EC_A4CC_D247F6957F7B__INCLUDED_)
