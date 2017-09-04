#pragma once


// CDlgPlayBackWin 对话框

class CDlgPlayBackWin : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayBackWin)

public:
	CDlgPlayBackWin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlayBackWin();

// 对话框数据
	enum { IDD = IDD_DLG_PLAYBACKWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iSubPlayBackWndIndex;
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    void OnStopPlayBack();

    void DrawOutputBorder(BOOL IsFocus);
};
