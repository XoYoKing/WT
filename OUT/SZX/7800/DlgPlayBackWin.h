#pragma once


// CDlgPlayBackWin �Ի���

class CDlgPlayBackWin : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayBackWin)

public:
	CDlgPlayBackWin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPlayBackWin();

// �Ի�������
	enum { IDD = IDD_DLG_PLAYBACKWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    int m_iSubPlayBackWndIndex;
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    void OnStopPlayBack();

    void DrawOutputBorder(BOOL IsFocus);
};
