#pragma once

class CWTBasic
{
public:
	CWTBasic(void);
	~CWTBasic(void);
	
private:
	CString m_strFilePathIn;
	CString m_strFilePathOut;
public:
	CString m_strFilePathLOG;
	CString m_strFileLOG;
	CString m_strFileFFMPEG;
	
	CString m_strCMS_ServerIP;
	int m_iCMS_Port;
	CString m_strCMS_UserName;
	CString m_strCMS_PassWord;
	
public:
	BOOL isServiceInit();
	CString GetSettingString(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpFileName);
	BOOL init();
	CString GetAppPath();
	BOOL IsFileExist(CString strFileName);
	void CreateAllDirectories(CString strDir);
	BOOL IsDirectoryExist(CString strPath,BOOL bCreate);
	BOOL RunBAT(CString strFileBAT);
	void SaveLog(CString strTAG1,CString strTAG2,CString strLog);
	CString getFilePathIn(int iOrderID);
	CString getFilePathOut(int iOrderID);
};
