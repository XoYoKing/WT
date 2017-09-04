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
    //������ɫ��Ϣ
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
        void SetProStep(int step);///���ò���
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

	BYTE m_nsteps;// ��¼����
	double m_steplength;//��¼ÿ��ʵ�ʳ�
	double m_increase;

    int m_max;//��¼����
	int m_min;//��¼����
	
	int m_lastpos;//��¼�ϴν�����λ��


	CRect m_rect;//��¼�������ľ���

	SColor<BYTE>m_color;//����ԭʼ��ɫ
	SColor<double>m_scale;//������ɫ����
	COLORREF m_backColor;//����ɫ
	COLORREF m_fontColor;//������ɫ



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
