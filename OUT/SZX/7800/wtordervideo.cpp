#include "StdAfx.h"
#include "PBTypes.h"
#include "PlatSDK_Test.h"
#include "WTOrderVideo.h"

#include<winsock2.h>
#include"mysql.h"
#pragma comment( lib, "libmysql.lib");

map<int,HANDLE> m_mapDownLoadStream2File; //下载取流句柄和下载文件句柄的映射
long m_lDataLen;
long m_lTimeLastUpdateData;

CWTOrderVideo::CWTOrderVideo(void)
{
	Clear();
}

CWTOrderVideo::~CWTOrderVideo(void)
{
}

void CWTOrderVideo::Clear()
{
	m_lTimeStart=-1;
	m_lTimeEnd=-1;
	m_strCameraIndexCode=_T("");
	m_strCameraIndexCode.Empty();
	m_iOrderID=-1;
	m_lDataLen=0;
	m_lTimeLastUpdateData=GetTickCount();
}

CString CWTOrderVideo::GetFileIn()
{
	CString strFile=_T("");
	strFile.Format(_T("%s\\%s_%ld_%ld.mp4"),theApp.m_Basic.getFilePathIn(m_iOrderID),m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	return strFile;
}
CString CWTOrderVideo::GetFileOut()
{
	CString strFile=_T("");
	strFile.Format(_T("%s\\%s_%ld_%ld.mp4"),theApp.m_Basic.getFilePathOut(m_iOrderID),m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	return strFile;
}
CString CWTOrderVideo::GetFileOutTXT()
{
	CString strFile=_T("");
	strFile.Format(_T("%s\\%s_%ld_%ld.txt"),theApp.m_Basic.getFilePathOut(m_iOrderID),m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	return strFile;
}
BOOL CWTOrderVideo::HaveVideo()
{
	int iRecordType = 0;
    iRecordType|=HIK_RECTYPE_PLAN;
	iRecordType|=HIK_RECTYPE_MOVE;
	iRecordType|=HIK_RECTYPE_ALARM;
	iRecordType|=HIK_RECTYPE_MANUAL;

	CTime absTimeFrom(m_lTimeStart);
	CTime absTimeTo(m_lTimeEnd);

	CString strLog=_T("");
	strLog.Format(_T("m_iOrderID=%d,m_strCameraIndexCode=%s"),m_iOrderID,m_strCameraIndexCode);
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);
	strLog.Format(_T("m_lTimeStart=%ld,%s"),m_lTimeStart,CTime(m_lTimeStart).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);
	strLog.Format(_T("m_lTimeEnd=%ld,%s"),m_lTimeEnd,CTime(m_lTimeEnd).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);

	char szXML[PLAT_RECORD_RESULT_XML_BUFFER_SIZE] = {0};
	int iFileHanlde=-1;
	int iCount=3;
	while ( iFileHanlde==-1 && iCount>0 )
	{
		iFileHanlde = HikPt_QueryRecord(m_strCameraIndexCode,__int64(absTimeFrom.GetTime()),__int64(absTimeTo.GetTime()),szXML,PLAT_RECORD_RESULT_XML_BUFFER_SIZE,iRecordType);
		strLog.Format(_T("iFileHanlde=%d,iCount=%d"),iFileHanlde,iCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);
		if ( iFileHanlde==-1 )
		{
			strLog.Format(_T("HikPt_QueryRecord return -1 %d"),iCount);
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);
			iCount--;
		}
		else
		{
			iCount=-1;
		}
	}
	if ( iFileHanlde==-1 )
	{
		strLog.Format(_T("HikPt_QueryRecord return -1 %d"),iCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),strLog);
		return FALSE;		
	}
	if (szXML == NULL)
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),_T("szXML == NULL"));
		return FALSE;		
	}
	HikPt_CloseQueryRecord(iFileHanlde);
	CString strXML=_T("");
	strXML.Format(_T("%s"),szXML);
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),szXML);
	if ( strXML.Find(_T("<SegmentCount>"))<0 && strXML.Find(_T("</SegmentCount>"))<0 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),_T("no SegmentCount"));
		return FALSE;		
	}
	if ( strXML.Find(_T("<SegmentCount>0</SegmentCount>"))>0 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),_T("Find <SegmentCount>0</SegmentCount>"));
		return FALSE;		
	}
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),_T("end"));
	return TRUE;
}
BOOL CWTOrderVideo::StartDownload()
{
	CString strLog=_T("");
	if ( isStopDownload() )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),_T("isStopDownload "));
		return TRUE;
	}
	CString strFileName=GetFileIn();
	if ( theApp.m_Basic.IsFileExist(strFileName) )
	{
		strLog.Format(_T("exist %s"),strFileName);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
		ConvertVideo();
		return TRUE;
	}
	int iRecordType = 0;
    iRecordType|=HIK_RECTYPE_PLAN;
	iRecordType|=HIK_RECTYPE_MOVE;
	iRecordType|=HIK_RECTYPE_ALARM;
	iRecordType|=HIK_RECTYPE_MANUAL;
	char szXML[PLAT_RECORD_RESULT_XML_BUFFER_SIZE] = {0};

	CTime absTimeFrom(m_lTimeStart);
	CTime absTimeTo(m_lTimeEnd);

	strLog.Format(_T("m_iOrderID=%d,m_strCameraIndexCode=%s"),m_iOrderID,m_strCameraIndexCode);
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
	strLog.Format(_T("m_lTimeStart=%ld,%s"),m_lTimeStart,CTime(m_lTimeStart).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
	strLog.Format(_T("m_lTimeEnd=%ld,%s"),m_lTimeEnd,CTime(m_lTimeEnd).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);

	int iFileHanlde=-1;
	int iCount=3;
	while ( iFileHanlde==-1 && iCount>0 )
	{
		iFileHanlde = HikPt_QueryRecord(m_strCameraIndexCode,__int64(absTimeFrom.GetTime()),__int64(absTimeTo.GetTime()),szXML,PLAT_RECORD_RESULT_XML_BUFFER_SIZE,iRecordType);
		strLog.Format(_T("iFileHanlde=%d,iCount=%d"),iFileHanlde,iCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
		if ( iFileHanlde==-1 )
		{
			strLog.Format(_T("HikPt_QueryRecord return -1 %d"),iCount);
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
			iCount--;
		}
		else
		{
			iCount=-1;
		}
	}
	if ( iFileHanlde==-1 )
	{
		strLog.Format(_T("HikPt_QueryRecord return -1 %d"),iCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
		return FALSE;		
	}
	if (szXML != NULL)
	{
		std::string strXML_STD = szXML;		
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),szXML);

		CString strXML=_T("");
		strXML.Format(_T("%s"),szXML);
		if ( strXML.Find(_T("<SegmentCount>"))<0 && strXML.Find(_T("</SegmentCount>"))<0 )
		{
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),_T("no SegmentCount"));
			return FALSE;		
		}
		if ( strXML.Find(_T("<SegmentCount>0</SegmentCount>"))>0 )
		{
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),_T("Find <SegmentCount>0</SegmentCount>"));
			return FALSE;		
		}
		
		m_lDataLen=0;
		m_lTimeLastUpdateData=GetTickCount();
		long lSession = HikPt_StartDownloadRecord(strXML_STD.c_str(),__int64(absTimeFrom.GetTime()),__int64(absTimeTo.GetTime()), PBDownloadStreamCallBack, this);
		CString strLog=_T("");
		strLog.Format("lSession=%d",lSession);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);

		if (lSession == -1)
		{
			PLAT_ERROR("HikPt_StartDownloadRecord failed lastError=%d",HikPt_GetLastError());
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),_T("HikPt_StartDownloadRecord failed lastError"));
			HikPt_CloseQueryRecord(iFileHanlde);
			m_lDataLen=-999;
			m_lTimeLastUpdateData=GetTickCount();
			return FALSE;
		}
		else
		{
			strLog.Format("录像(%s)开始下载",strFileName);
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),strLog);
			HikPt_CloseQueryRecord(iFileHanlde);
			return TRUE;
		}
	}
	else
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("StartDownload"),_T("HikPt_QueryRecord return null"));
		return FALSE;		
	}
	return TRUE;
}

//回放取流回调
void __stdcall CWTOrderVideo::PBDownloadStreamCallBack(long lSession, int iStreamType, const char* data, int dataLen, void* pUser)
{
    CWTOrderVideo* pThis = static_cast<CWTOrderVideo*>(pUser);
    if(pThis != NULL)
    {
        pThis->OnDealDownloadStream(lSession,iStreamType,data,dataLen);
    } 
}


void CWTOrderVideo::OnDealDownloadStream(long lSession, int iStreamType, const char* data, int dataLen)
{   
	CString strLog=_T("");

    if(iStreamType == PBDT_FORWARD)
    {
		//*/
		m_lDataLen=0;
		m_lTimeLastUpdateData=GetTickCount();
		if(m_mapDownLoadStream2File.find(lSession) == m_mapDownLoadStream2File.end())
		{
			m_lDataLen=1;
			m_lTimeLastUpdateData=GetTickCount();
			CString strFileName=GetFileIn();
			strLog.Format("lSession=%d,dataLen=%d,m_iDataLen=%ld,CreateFile:%s",lSession,dataLen,m_lDataLen,strFileName);
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),strLog);
			//创建文件
			HANDLE hFile = CreateFile(strFileName,          // name of the write
				GENERIC_WRITE,          // open for writing
				0,                      // do not share
				NULL,                   // default security
				CREATE_ALWAYS,          // overwrite existing
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template

			if (hFile == INVALID_HANDLE_VALUE) 
			{   
				strLog.Format("CreateFile('%s') failed, GetLastError = %d",strFileName,GetLastError());
				theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),strLog);
				return ;
			}
			m_mapDownLoadStream2File[lSession] = hFile;
		}
		//*/
    }
    else if(iStreamType == PBDT_DATA)
    {
		m_lDataLen+=dataLen;
		m_lTimeLastUpdateData=GetTickCount();
		double dMB=m_lDataLen*1.0/(1024.0*1024.0);
		strLog.Format("lSession=%d,dataLen=%d,m_iDataLen=%ld,下载：%.2fMB",lSession,dataLen,m_lDataLen,dMB);
		//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),strLog);

		//*/
        if(m_mapDownLoadStream2File.find(lSession) != m_mapDownLoadStream2File.end())
        {   
			HANDLE hFile = m_mapDownLoadStream2File[lSession];
			if(hFile != INVALID_HANDLE_VALUE)
			{
				//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),_T("0"));
				DWORD dwSize = SetFilePointer(hFile, 0, NULL, FILE_END);
				if (dwSize == INVALID_SET_FILE_POINTER)
				{
					//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),_T("1"));
					return;
				}
	            
				//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),_T("2"));
				DWORD dwRead = 0;
				if(FALSE == ::WriteFile(hFile,data,dataLen,&dwRead,NULL))
				{
					//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),_T("3"));
					return;
				}
			}
        }
		//*/
		//theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("OnDealDownloadStream"),strLog);
    }
    else if(iStreamType == PBDT_END)
    {
		DownloadFinish(lSession, iStreamType,data, dataLen);
    }
}

void CWTOrderVideo::DownloadFinish(long lSession, int iStreamType, const char* data, int dataLen)
{ 
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("DownloadFinish"),_T("0"));
	int nRet = HikPt_StopDownloadRecord(lSession);
	if(nRet == 0)
	{
		HANDLE hFile = m_mapDownLoadStream2File[lSession];
		if(hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
			m_lDataLen=-1;
			m_lTimeLastUpdateData=GetTickCount();
			//ConvertVideo();
		}
		m_mapDownLoadStream2File.erase(lSession);
	}
	else
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("DownloadFinish"),_T("停止下载失败"));
	}
	m_lDataLen=-1;
	m_lTimeLastUpdateData=GetTickCount();
}

BOOL CWTOrderVideo::isStopDownload()
{
	if ( !HaveVideo() )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("true-->HaveVideo==false"));
		return TRUE;
	}
	if ( theApp.m_Basic.IsFileExist(GetFileIn()) && theApp.m_Basic.IsFileExist(GetFileOut()) )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("true-->exist file"));
		return TRUE;
	}
	if ( m_lDataLen==-1 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("true-->m_lDataLen==-1"));
		return TRUE;
	}
	if ( m_lDataLen==-999 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("true-->m_lDataLen==-999"));
		return TRUE;
	}
	if ( m_lDataLen>=0 )
	{
		double dTimeMinute=(GetTickCount()-m_lTimeLastUpdateData)*1.0/(1000.0*60.0);
		if ( dTimeMinute>1 )
		{
			//超时
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("下载超时--->dTimeMinute>1"));
		}
		else
		{
			theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("false--->m_lDataLen>0"));
			return FALSE;
		}
	}
	if ( theApp.m_Basic.IsFileExist(GetFileIn()) && !theApp.m_Basic.IsFileExist(GetFileOut()) )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("false--->no out file"));
		ConvertVideo();
		return FALSE;
	}
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isStopDownload"),_T("fals"));
	return FALSE;
}
BOOL CWTOrderVideo::ConvertVideo()
{
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),_T("0"));
	CString strFileIn=GetFileIn();
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strFileIn);
	if ( !theApp.m_Basic.IsFileExist(strFileIn) )
	{
		return FALSE;
	}
	CString strFileOut=GetFileOut();
	CString strFileOutTXT=GetFileOutTXT();
	if ( theApp.m_Basic.IsFileExist(strFileOut) )//start
	{
		if ( theApp.m_Basic.IsFileExist(strFileOutTXT) )//in process
		{
			return FALSE;
		}
		else//end
		{
			SaveVideToDB();
			return TRUE;
		}
	}
	
	CTime tmCUR=CTime::GetCurrentTime();
	/*/
	CString strFileBAT_DEL=_T("");
	strFileBAT_DEL.Format(_T("%s%s.BAT"),theApp.m_Basic.m_strFilePathLOG,tmCUR.Format(_T("%Y%m%d_%H%M%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strFileBAT_DEL);

	FILE * fp_DEL;
	fp_DEL = fopen(strFileBAT_DEL,"a");
	if(fp_DEL)
	{
		CString strValueBAT=_T("del *.bat");
		strValueBAT.Format(_T("del %s*.BAT"),theApp.m_Basic.m_strFilePathLOG);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strValueBAT);
		fprintf(fp_DEL,"%s",strValueBAT);
		fclose(fp_DEL);
		theApp.m_Basic.RunBAT(strFileBAT_DEL);
	}
	//*/
	CString strFileBAT=_T("");
	//strFileBAT.Format(_T("%s%s_%s_%ld_%ld.BAT"),theApp.m_Basic.m_strFilePathLOG,tmCUR.Format(_T("%Y%m%d_%H%M%S")),m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	strFileBAT.Format(_T("%s%s_%s_%ld_%ld.BAT"),theApp.m_Basic.m_strFilePathLOG,tmCUR.Format(_T("%Y%m%d")),m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strFileBAT);
	if ( theApp.m_Basic.IsFileExist(strFileBAT) )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),_T("strFileBAT have Exist!"));
		return FALSE;
	}
	FILE * fp;
	fp = fopen(strFileBAT,"a");
	if(fp)
	{
		CString strValueBAT=_T("");
		strValueBAT.Format(_T("dir >%s"),strFileOutTXT);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strValueBAT);
		fprintf(fp,"%s",strValueBAT);

		strValueBAT.Format(_T("\n%s -i %s -vcodec libx264 %s"),theApp.m_Basic.m_strFileFFMPEG,strFileIn,strFileOut);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strValueBAT);
		fprintf(fp,"%s",strValueBAT);

		strValueBAT.Format(_T("\ndel %s"),strFileOutTXT);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("ConvertVideo"),strValueBAT);
		fprintf(fp,"%s",strValueBAT);
		fclose(fp);
		theApp.m_Basic.RunBAT(strFileBAT);
	}
	return TRUE;
}

BOOL CWTOrderVideo::SaveVideToDB()
{
	CString _filename=_T("");
	int _video_length=-1;
	long _create_time=-1;
	long _start_time=-1;
	long _end_time=-1;
	int _order_id=-1;	

	_filename.Format(_T("%d\\\\%s_%ld_%ld.mp4"),m_iOrderID,m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	_start_time=m_lTimeStart;
	_end_time=m_lTimeEnd;
	_video_length=(m_lTimeEnd-m_lTimeStart)/60;
	_order_id=m_iOrderID;
	
	CString strLog=_T("");
	//_filename=_T("");
	CString strFileIn=GetFileIn();
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strFileIn);
	if ( !theApp.m_Basic.IsFileExist(strFileIn) )
	{
		strLog.Format("下载失败:[%s]不存在",strFileIn);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	CString strFileOut=GetFileOut();
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strFileOut);
	if ( !theApp.m_Basic.IsFileExist(strFileOut) )
	{
		strLog.Format("转码失败:[%s]不存在",strFileOut);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	//_video_length=-1;
	if ( _video_length<0 )
	{
		strLog.Format("下载失败:_video_length=%d",_video_length);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	//_create_time=-1;
	CTime curTime=CTime::GetCurrentTime();
	_create_time=curTime.GetTime();
	if ( _create_time<0 )
	{
		strLog.Format("下载失败:_create_time=%ld",_create_time);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	//_start_time=-1;
	if ( _start_time<0 )
	{
		strLog.Format("下载失败:_start_time=%ld",_start_time);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	//_end_time=-1;
	if ( _end_time<0 )
	{
		strLog.Format("下载失败:_end_time=%ld",_end_time);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}
	//_order_id=-1;
	if ( _order_id<0 )
	{
		strLog.Format("下载失败:_order_id=%d",_order_id);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return FALSE;
	}

	CString strSQL=_T("");
	strSQL.Format("select filename,video_length,start,end,order_id from wp_tuyun_video where filename=\'%s\' and video_length=%d and start=%ld and end=%ld and order_id=\'%d\'",_filename,_video_length, _start_time, _end_time,_order_id); 

	int iQueryCount=QueryCount(strSQL);
	if ( iQueryCount>0 )
	{
		strLog.Format("TRUE-->记录已存在:iQueryCount=%d",iQueryCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);
		return TRUE;
	}

	MYSQL m_sqlCon;  
	mysql_init(&m_sqlCon);    
	if(!mysql_real_connect(&m_sqlCon,"192.168.1.106","root","www.lagou.org","tuyunwxdb_new",4406,NULL,0))    
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),_T("连接数据库失败!"));  
		CString e=mysql_error(&m_sqlCon); 
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),e);  
		return FALSE;  
	}  
	else  
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),_T("连接数据库成功!"));  
		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");
	}
	
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),_T("插入数据"));  
	strSQL.Format("insert into wp_tuyun_video(filename,video_length,create_time,start,end,order_id) value(\'%s\', %d, %ld, %ld, %ld, \'%d\')",_filename,_video_length, _create_time, _start_time, _end_time,_order_id); //sql操作语句
	strLog.Format("插入数据:%s",strSQL);
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("SaveVideToDB"),strLog);

	mysql_real_query(&m_sqlCon, strSQL,strSQL.GetLength());
	mysql_close(&m_sqlCon);//关闭Mysql连接

	return TRUE;
}

BOOL CWTOrderVideo::isVideoOK()
{
	CString strLog=_T("");
	//_filename=_T("");
	CString strFileIn=GetFileIn();
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strFileIn);
	if ( !theApp.m_Basic.IsFileExist(strFileIn) )
	{
		strLog.Format("FALSE-->下载失败:[%s]不存在",strFileIn);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}
	CString strFileOut=GetFileOut();
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strFileOut);
	if ( !theApp.m_Basic.IsFileExist(strFileOut) )
	{
		strLog.Format("FALSE-->转码失败:[%s]不存在",strFileOut);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}

	CString _filename=_T("");
	int _video_length=-1;
	long _start_time=-1;
	long _end_time=-1;
	int _order_id=-1;	

	_filename.Format(_T("%d\\\\%s_%ld_%ld.mp4"),m_iOrderID,m_strCameraIndexCode,m_lTimeStart,m_lTimeEnd);
	_start_time=m_lTimeStart;
	_end_time=m_lTimeEnd;
	_video_length=(m_lTimeEnd-m_lTimeStart)/60;
	_order_id=m_iOrderID;
	
	//_video_length=-1;
	if ( _video_length<0 )
	{
		strLog.Format("FALSE-->下载失败:_video_length=%d",_video_length);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}
	//_start_time=-1;
	if ( _start_time<0 )
	{
		strLog.Format("FALSE-->下载失败:_start_time=%ld",_start_time);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}
	//_end_time=-1;
	if ( _end_time<0 )
	{
		strLog.Format("FALSE-->下载失败:_end_time=%ld",_end_time);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}
	//_order_id=-1;
	if ( _order_id<0 )
	{
		strLog.Format("FALSE-->下载失败:_order_id=%d",_order_id);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		return FALSE;
	}

	CString strSQL=_T("");
	strSQL.Format("select filename,video_length,start,end,order_id from wp_tuyun_video where filename=\'%s\' and video_length=%d and start=%ld and end=%ld and order_id=\'%d\'",_filename,_video_length, _start_time, _end_time,_order_id); 

	int iQueryCount=QueryCount(strSQL);
	if ( iQueryCount<1 )
	{
		strLog.Format("FALSE-->下载失败:iQueryCount=%d",iQueryCount);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
		SaveVideToDB();
		return FALSE;
	}
		
	strLog.Format("TRUE-->iQueryCount=%d",iQueryCount);	
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("isVideoOK"),strLog);
	return TRUE;
}

int CWTOrderVideo::QueryCount(CString strSQL)
{
	int iCount=0;
	//连接数据库
	MYSQL m_sqlCon;  
	mysql_init(&m_sqlCon);    
	if(!mysql_real_connect(&m_sqlCon,"192.168.1.106","root","www.lagou.org","tuyunwxdb_new",4406,NULL,0))    
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),_T("连接数据库失败!"));  
		CString e=mysql_error(&m_sqlCon);
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),e);  
		return -1;  
	}  
	else  
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),_T("连接数据库成功!"));  
		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");  
	}  
	//查询
	MYSQL_RES *m_result;
	MYSQL_ROW row; 
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),strSQL);  
	mysql_query(&m_sqlCon,strSQL);  	  
	m_result=mysql_use_result(&m_sqlCon);  
	if (NULL == m_result)//如果为空则返回
	{ 
		theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),_T("数据库查询结果为空!"));  
		return -1;  
	}
	iCount=0;
	if ( row=mysql_fetch_row(m_result) )  
	{
		iCount++;
	}  
	mysql_free_result(m_result);  

	mysql_close(&m_sqlCon);//关闭Mysql连接

	CString strLog=_T("");
	strLog.Format("iCount=%d",iCount);	
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("QueryCount"),strLog);
	return iCount;
}