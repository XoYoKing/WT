#pragma once
#include "wtordervideo.h"

class CWTOrder
{
public:
	CWTOrder(void);
	~CWTOrder(void);
	
public:
	CArray<CWTOrderVideo,CWTOrderVideo> m_aVideo;
	long m_lTimeStart;
	long m_lTimeEnd;
	CString m_strCameraIndexCode;
	int m_iOrderID;
	long m_lTimeNULL;

public:
	void Clear();
	void DoTimer();
	BOOL GetVideoToDownload();
	BOOL HaveVideo();
	void PostNoVideo();
	BOOL StartDownload();
	BOOL isStopDownload();
	void DoDownLoadFinish();
	int getOrderStatus();
	BOOL updateOrderStatus();
	void PostHaveSendGood();
	BOOL isVideoOK();
};
