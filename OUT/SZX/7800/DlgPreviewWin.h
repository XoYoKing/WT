#pragma once

// CDlgPreviewWin �Ի���

class CDlgPreviewWin : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreviewWin)

public:
	CDlgPreviewWin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPreviewWin();

// �Ի�������
	enum { IDD = IDD_DLG_PREVIEWWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    int m_iSubWndIndex;     ///< �Ӵ�������

    void DrawOutputBorder(BOOL IsFocus);
    void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnStopplay();
    afx_msg void OnStartTvWall();
    afx_msg void OnStopTvWall();
};
