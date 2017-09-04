#pragma once

class CWTOrderVideo
{
public:
	CWTOrderVideo(void);
	~CWTOrderVideo(void);
	
public:
	long m_lTimeStart;
	long m_lTimeEnd;
	CString m_strCameraIndexCode;
	int m_iOrderID;
	//map<int,HANDLE> m_mapDownLoadStream2File; //����ȡ������������ļ������ӳ��
	//long m_lDataLen;
	
public:
	void Clear();
	CString GetFileIn();
	CString GetFileOut();
	CString GetFileOutTXT();
	BOOL HaveVideo();
	BOOL StartDownload();
	static void __stdcall PBDownloadStreamCallBack(long lSession, int iStreamType, const char* data, int dataLen, void* pUser);
    void OnDealDownloadStream(long lSession, int iStreamType, const char* data, int dataLen);
    void DownloadFinish(long lSession, int iStreamType, const char* data, int dataLen);
	BOOL isStopDownload();
	BOOL ConvertVideo();
	BOOL SaveVideToDB();
	BOOL isVideoOK();
	int QueryCount(CString strSQL);
};
