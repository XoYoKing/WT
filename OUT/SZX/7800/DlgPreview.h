#pragma once
#include "afxwin.h"

// CDlgPreview �Ի���

class CDlgPreview : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreview)

public:
	CDlgPreview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPreview();

// �Ի�������
	enum { IDD = IDD_DLG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

    // �˳�ʱ��ע����Ԥ��
    void Fini();

    int m_iPreviewLeft;                 ///< Ԥ���������߽�
    int m_iPreviewTop;                  ///< Ԥ���Ķ�
    int m_iPreviewRight;                ///< Ԥ�����ұ߽�

    int m_iCurWndNum;					///< ��ǰ������

    int m_iPTZSpeed;
    int m_iPresetIndex;

    CRect m_rectPreviewBG;              ///< Ԥ����
    CComboBox m_comboWinNum;
    bool  m_bTvWall;                    ///��ǰ�Ƿ�Ԥ����ǽ�ɹ�
    int   m_iTvWallId;                  ///����ǽid

    map<int,int> m_mapWinIndexPreviewHandle;//���ں�Ԥ�������ӳ��
    HIK_STREAM_TYPE m_nStream;
    afx_msg void OnCbnSelchangeComboStreamtype();
    CComboBox m_nStreamType;
};
