#pragma once
#include "afxwin.h"

// CDlgPreview 对话框

class CDlgPreview : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreview)

public:
	CDlgPreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPreview();

// 对话框数据
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    void OnPaint();
    void InitPreviewDisplay(void);
    BOOL InitChildWindow(void);
    BOOL InitWindowLayout(void);
    void InitPreviewRect(void);
    void ArrangeOutputs(int iNumber);

    afx_msg void OnCbnSelchangeComboWndnum();
    LRESULT OnDrawPreviewBorder(WPARAM wparam, LPARAM lparam);
    LRESULT OnFocus(WPARAM wparam, LPARAM lparam);
    LRESULT OnStartPlay(WPARAM wparam, LPARAM lparam);
    LRESULT OnStopPlay(WPARAM wparam, LPARAM lparam);
    LRESULT OnStartTvWall(WPARAM wparam, LPARAM lparam);
    LRESULT OnStopTvWall(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgPTZ(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgCAPPIC(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgStartRecord(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgStopRecord(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgPTZLock(WPARAM wparam, LPARAM lparam);
    LRESULT OnMsgPTZUnlock(WPARAM wparam, LPARAM lparam);
    int  __ConverPTZcommand(int BtnID);
    void __InitComboBox();
    static void __stdcall SnapCallback(long lSession,int nErr,const char* data,void* pUser);
    static void __stdcall PreviewRecordEndCallback(long lSession,int nErr,const char* data,void* pUser);
    static void __stdcall PreviewStreamCallback(long lSession, int iStreamType, const char* data, int dataLen, void* pUser);

    // 退出时关注所有预览
    void Fini();

    int m_iPreviewLeft;                 ///< 预览区域的左边界
    int m_iPreviewTop;                  ///< 预览的顶
    int m_iPreviewRight;                ///< 预览的右边界

    int m_iCurWndNum;					///< 当前窗口数

    int m_iPTZSpeed;
    int m_iPresetIndex;

    CRect m_rectPreviewBG;              ///< 预览区
    CComboBox m_comboWinNum;
    bool  m_bTvWall;                    ///当前是否预览上墙成功
    int   m_iTvWallId;                  ///电视墙id

    map<int,int> m_mapWinIndexPreviewHandle;//窗口和预览句柄的映射
    HIK_STREAM_TYPE m_nStream;
    afx_msg void OnCbnSelchangeComboStreamtype();
    CComboBox m_nStreamType;
};
