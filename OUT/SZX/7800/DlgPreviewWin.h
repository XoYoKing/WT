#pragma once

// CDlgPreviewWin 对话框

class CDlgPreviewWin : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreviewWin)

public:
	CDlgPreviewWin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPreviewWin();

// 对话框数据
	enum { IDD = IDD_DLG_PREVIEWWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iSubWndIndex;     ///< 子窗口索引

    void DrawOutputBorder(BOOL IsFocus);
    void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnStopplay();
    afx_msg void OnStartTvWall();
    afx_msg void OnStopTvWall();
};
