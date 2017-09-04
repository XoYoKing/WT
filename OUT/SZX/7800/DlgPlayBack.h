#pragma once

#include "DlgPlayBackWin.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "ProEx.h"
#include "SearchResultParser.h"

// CDlgPlayBack 对话框

class CDlgPlayBack : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayBack)

public:
	CDlgPlayBack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlayBack();

// 对话框数据
	enum { IDD = IDD_DLG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    int m_iPlaybackLeft;
    int m_iPlaybackTop;
    int m_iPlaybackRight;
    int m_iPlaybackBottom;

    int m_iCurPlaybcakWndIndex;                 ///< 当前回放窗口索引
    int m_iCurPlaybackCID;

    CRect m_rectPlaybackBG;              ///< 预览区

    int m_iDownLoadpos;
    int m_iCurDownHandle;

    RECORD_SEARCH_RESULT_MAP m_records;

    void __InitComboBox();
    void InitPlayBackDisplay(void);
    BOOL InitChildWindow(void);
    BOOL InitWindowLayout(void);
    void InitPlaybackRect();
    void ArrangeOutputs(int iNumber);

    LRESULT OnDrawPlayBackBorder(WPARAM wparam, LPARAM lparam);
    LRESULT OnFocus(WPARAM wparam, LPARAM lparam);
    LRESULT OnStopPlayBack(WPARAM wparam, LPARAM lparam);
    LRESULT OnSetPlayBackCID(WPARAM wparam, LPARAM lparam);

    CComboBox m_comboStoreType;
    CButton m_check_PlanRecord;
    CButton m_check_MoveRecord;
    CButton m_check_ManualRecord;
    CButton m_check_AlarmRecord;
    CTime m_ctBeginDay;
    CTime m_ctBeginTime;
    CTime m_ctEndDay;
    CTime m_ctEndTime;
    CTime m_ctOrientateDay;
    CTime m_ctOrientateTime;

    afx_msg void OnBnClickedButtonQueryreocrd();
    afx_msg void OnBnClickedButtonStartplay();


    map<int,std::string> m_mapFileHandleCID; //cameraID和查询结果的映射
    map<int,int> m_mapWinIndexPlayBackHandle;//窗口和预览句柄的映射
    HPR_Mutex m_LockWinPlayBackHandle;

    map<int,int> m_mapDownLoadHandleCID;//窗口和下载取流句柄的映射
    map<int,HANDLE> m_mapDownLoadStream2File; //下载取流句柄和下载文件句柄的映射

    map<int,int> m_mapWinIndexPlayBackCID;   //窗口和cameraID的映射
    afx_msg void OnBnClickedButtonPause();
    afx_msg void OnBnClickedButtonPlaybackfast();
    afx_msg void OnBnClickedButtonPlaybackslow();
    afx_msg void OnBnClickedButtonOrientate();
    afx_msg void OnBnClickedButtonContinue();
    afx_msg void OnBnClickedButtonStartdownload();
    afx_msg void OnBnClickedButtonStopdownload();
    CProEx m_DownLoadProgress;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    void Fini();

    //回放下载取流回调
    static void __stdcall PBDownloadStreamCallBack(long lSession, int iStreamType, const char* data, int dataLen, void* pUser);
    void OnDealDownloadStream(long lSession, int iStreamType, const char* data, int dataLen);
    afx_msg void OnBnClickedButtonSnapshot();
    //拍照回调
    static void __stdcall SnapCallback(long lSession,int nErr,const char* data,void* pUser);
};
