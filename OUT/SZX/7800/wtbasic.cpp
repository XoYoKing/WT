#include "StdAfx.h"
#include "PlatSDK_Test.h"
#include "WTBasic.h"

CWTBasic::CWTBasic(void)
{
}

CWTBasic::~CWTBasic(void)
{
}

BOOL CWTBasic::isServiceInit()
{
	return TRUE;
}

BOOL CWTBasic::init()
{
    m_strFilePathLOG.Format(_T("%sLog\\"),GetAppPath());
	if ( !IsDirectoryExist(m_strFilePathLOG,TRUE) )
	{
		theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),_T("无法找到日志目录！"));
		return FALSE;
	}
	CTime tmCUR=CTime::GetCurrentTime();
	m_strFileLOG.Format(_T("%s%s.TXT"),m_strFilePathLOG,tmCUR.Format(_T("%Y%m%d_%H%M%S")));

	m_strFilePathIn = GetSettingString("PATH","DOWN_IN",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),m_strFilePathIn);
	if ( !IsDirectoryExist(m_strFilePathIn,TRUE) )
	{
		return FALSE;
	}

	m_strFilePathOut = GetSettingString("PATH","DOWN_OUT",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),m_strFilePathOut);
	if ( !IsDirectoryExist(m_strFilePathOut,TRUE) )
	{
		return FALSE;
	}

	m_strFileFFMPEG = GetSettingString("PATH","FFMPEG_PATH",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),m_strFileFFMPEG);
	if ( !IsFileExist(m_strFileFFMPEG) )
	{
		return FALSE;
	}
	
	//CString m_strCMS_ServerIP;
	m_strCMS_ServerIP = GetSettingString("CMS_SERVER","CMS_ServerIP",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init-m_strCMS_ServerIP="),m_strCMS_ServerIP);
	if ( m_strCMS_ServerIP.IsEmpty() )
	{
		return FALSE;
	}
	//int m_iCMS_Port;
	CString strCMS_ServerPort = GetSettingString("CMS_SERVER","CMS_ServerPort",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init-strCMS_ServerPort="),strCMS_ServerPort);
	if ( strCMS_ServerPort.IsEmpty() )
	{
		return FALSE;
	}
	m_iCMS_Port=atoi(strCMS_ServerPort);
	//CString m_strCMS_UserName;
	m_strCMS_UserName = GetSettingString("CMS_SERVER","CMS_UserName",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init-m_strCMS_UserName="),m_strCMS_UserName);
	if ( m_strCMS_UserName.IsEmpty() )
	{
		return FALSE;
	}
	//CString m_strCMS_PassWord;
	m_strCMS_PassWord = GetSettingString("CMS_SERVER","CMS_PassWord",".\\Config.ini"); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init-m_strCMS_PassWord="),m_strCMS_PassWord);
	if ( m_strCMS_PassWord.IsEmpty() )
	{
		return FALSE;
	}
	
	CString strFileBAT=_T("");
	strFileBAT.Format(_T("%s%s.BAT"),theApp.m_Basic.m_strFilePathLOG,tmCUR.Format(_T("%Y%m%d_%H%M%S")));
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),strFileBAT);

	FILE * fp;
	fp = fopen(strFileBAT,"a");
	if(fp)
	{
		CString strValueBAT=_T("del *.bat");
		strValueBAT.Format(_T("del %s*.BAT"),theApp.m_Basic.m_strFilePathLOG);
		theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("init"),strValueBAT);
		fprintf(fp,"%s",strValueBAT);
		fclose(fp);
		theApp.m_Basic.RunBAT(strFileBAT);
	}
	
    return TRUE;
}

CString CWTBasic::GetSettingString(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpFileName)
{
	CString strTemp = _T(""); 
	::GetPrivateProfileString(lpAppName,lpKeyName,"", strTemp.GetBuffer(MAX_PATH), MAX_PATH,lpFileName); 
	theApp.m_Basic.SaveLog(_T("CWTBasic"),_T("GetSettingString"),strTemp);
	strTemp.ReleaseBuffer(-1);
	return strTemp;
}

CString CWTBasic::GetAppPath()
{
	CString strFilePath;
	::GetModuleFileName(NULL, strFilePath.GetBuffer(_MAX_PATH), _MAX_PATH);
	strFilePath.ReleaseBuffer(-1);
	
	int iPos = strFilePath.ReverseFind(_T('\\'));
	if (iPos == -1) 
	{
		ASSERT(FALSE);
		strFilePath.Empty();
		return strFilePath;
	}

	strFilePath = strFilePath.Left(iPos + 1);
	return strFilePath;
}

BOOL CWTBasic::IsFileExist(CString strFileName)
{
	BOOL bReturn=FALSE;
	CFileFind finder;
	bReturn=finder.FindFile(strFileName);
	return bReturn;
}

void CWTBasic::CreateAllDirectories(CString strDir)
{
	//remove ending / if exists
	if(strDir.Right(1)=="\\")
		strDir=strDir.Left(strDir.GetLength()-1); 

	// base case . . .if directory exists
	if(GetFileAttributes(strDir)!=-1) 
		return;

	// recursive call, one less directory
	int nFound = strDir.ReverseFind('\\');
	CreateAllDirectories(strDir.Left(nFound)); 

	// actual work
	CreateDirectory(strDir,NULL); 
}

BOOL CWTBasic::IsDirectoryExist(CString strPath,BOOL bCreate)
{
	BOOL bReturn=FALSE;
	bReturn=IsFileExist(strPath);
	if ( bReturn )
	{
		return bReturn;
	}
	if ( bCreate )
	{
		CreateAllDirectories(strPath);
	}
	bReturn=IsFileExist(strPath);
	if ( bReturn )
	{
		return bReturn;
	}
	if ( strPath.Right(1).CompareNoCase(_T("\\"))!=0 )
	{
		strPath+=_T("\\");
	}
	else
	{
		strPath=strPath.Left(strPath.GetLength()-1);
	}
	bReturn=IsFileExist(strPath);
	if ( bReturn )
	{
		return bReturn;
	}
	if ( bCreate )
	{
		CreateAllDirectories(strPath);
	}
	bReturn=IsFileExist(strPath);
	return bReturn;
}

BOOL CWTBasic::RunBAT(CString strFileBAT)
{
	try
	{
		ShellExecute(NULL,"open",strFileBAT,NULL,NULL,SW_HIDE);
		SaveLog(_T("CWTBasic"),_T("RunBAT"),strFileBAT);
	}
	catch(...)
	{
		SaveLog(_T("CWTBasic"),_T("RunBAT"),_T("Catch RunBAT..."));
		return FALSE;
	}
	return TRUE;
}

void CWTBasic::SaveLog(CString strTAG1,CString strTAG2,CString strLog)
{
	//*/
	//if ( strTAG1.CompareNoCase(_T("CWTOrderVideo"))!=0 )
	{
		//return;
	}
	CTime tmCUR=CTime::GetCurrentTime();
	CString strValue=_T("");
	strValue.Format(_T("%8s %s-%s-%s\r"),tmCUR.Format(_T("%Y-%m-%d %H:%M:%S")),strTAG1,strTAG2,strLog);
	FILE * fp;
	fp = fopen(m_strFileLOG,"a");
	if(fp)
	{
		fprintf(fp,"%s",strValue);
		fclose(fp);
	}
	//*/
}

CString CWTBasic::getFilePathIn(int iOrderID)
{
	CString strPath=_T("");
	strPath.Format(_T("%s\\%d"),m_strFilePathIn,iOrderID);
	if ( !IsDirectoryExist(strPath,TRUE) )
	{
		strPath.Format(_T("%s\\%d\\"),m_strFilePathIn,iOrderID);
		if ( !IsDirectoryExist(strPath,TRUE) )
		{
		}
		strPath.Format(_T("%s\\%d"),m_strFilePathIn,iOrderID);
	}
	return strPath;
}
CString CWTBasic::getFilePathOut(int iOrderID)
{
	CString strPath=_T("");
	strPath.Format(_T("%s\\%d"),m_strFilePathOut,iOrderID);
	if ( !IsDirectoryExist(strPath,TRUE) )
	{
		strPath.Format(_T("%s\\%d\\"),m_strFilePathOut,iOrderID);
		if ( !IsDirectoryExist(strPath,TRUE) )
		{
		}
		strPath.Format(_T("%s\\%d"),m_strFilePathOut,iOrderID);
	}
	return strPath;
}
