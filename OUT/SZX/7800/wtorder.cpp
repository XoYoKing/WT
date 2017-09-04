#include "StdAfx.h"
#include "PlatSDK_Test.h"
#include "WTOrder.h"
#include "WTHttpClient.h"

#include<winsock2.h>
#include"mysql.h"
#pragma comment( lib, "libmysql.lib");

//测试
#define MAX_SECOND_OF_VIDEO 60*30
//#define MAX_SECOND_OF_VIDEO 30

CWTOrder::CWTOrder(void)
{
	m_lTimeNULL=GetTickCount();
	Clear();
}

CWTOrder::~CWTOrder(void)
{
}

void CWTOrder::Clear()
{
	m_aVideo.RemoveAll();

	m_lTimeStart=-1;
	m_lTimeEnd=-1;
	m_strCameraIndexCode=_T("");
	m_strCameraIndexCode.Empty();
	m_iOrderID=-1;
}
void CWTOrder::DoTimer()
{
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("Start-检测是否有新录像需要下载!"));
	if ( !isStopDownload() )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("End-上一订单下载还未停止"));
		return;
	}
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("Start-获取需要下载订单!"));
	if ( !GetVideoToDownload() )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("End-获取需要下载订单失败"));
		return;
	}
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("Start-启动下载!"));
	if ( !StartDownload() )
	{		
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("DoTimer"),_T("End-启动下载失败"));
		return;
	}
}

BOOL CWTOrder::GetVideoToDownload()
{
	BOOL bReturn=FALSE;
	if ( !theApp.m_Basic.isServiceInit() )
	{
		return bReturn;
	}
	Clear();
	
	//连接数据库
	MYSQL m_sqlCon;  
	mysql_init(&m_sqlCon);    
	if(!mysql_real_connect(&m_sqlCon,"192.168.1.106","root","www.lagou.org","tuyunwxdb_new",4406,NULL,0))    
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),_T("连接数据库失败!"));  
		CString e=mysql_error(&m_sqlCon);
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),e);  
		return bReturn;  
	}  
	else  
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),_T("连接数据库成功!"));  
		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");  
	}  
	//查询
	MYSQL_RES *m_result;
	MYSQL_ROW row; 
	CString strSQL=_T(""); 
	CString data[4];  
	strSQL.Format("select a.start_time,a.end_time,b.code_7800,a.id from wp_tuyun_camera_order a,wp_tuyun_camera b where a.pay_status=1 and a.order_status=1 and a.camera_id = b.id"); 
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strSQL);  
	mysql_query(&m_sqlCon,strSQL);  	  
	m_result=mysql_use_result(&m_sqlCon);  
	if (NULL == m_result)//如果为空则返回
	{ 
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),_T("数据库查询结果为空!"));  
		return bReturn;  
	}
	if ( row=mysql_fetch_row(m_result) )  
	{
		m_lTimeNULL=GetTickCount();

		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),_T("获取数据!"));  

		//获取数据  	  
		data[0]=row[0];  
		data[1]=row[1];  
		data[2]=row[2];  
		data[3]=row[3];  
		
		m_lTimeStart=_ttol(data[0]);
		m_lTimeEnd=_ttol(data[1]);
		m_strCameraIndexCode=data[2];
		m_iOrderID=_ttoi(data[3]);
		
		//测试
		//if ( MAX_SECOND_OF_VIDEO<60 )
		//{
		//	m_lTimeStart=CTime(2017,3,24,1,0,0).GetTime();
		//	m_lTimeEnd=m_lTimeStart+90;
		//}

		if ( HaveVideo() )
		{
			long lStart=m_lTimeStart;
			long lEnd=lStart+MAX_SECOND_OF_VIDEO;
			BOOL bStop=FALSE;
			CString strLog=_T("");

			strLog.Format(_T("m_iOrderID=%d,m_strCameraIndexCode=%s"),m_iOrderID,m_strCameraIndexCode);
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strLog);
			strLog.Format(_T("m_lTimeStart=%ld,%s"),m_lTimeStart,CTime(m_lTimeStart).Format(_T("%Y-%m-%d %H:%M:%S")));
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strLog);
			while ( m_lTimeStart<m_lTimeEnd && lStart<=m_lTimeEnd && lEnd<=m_lTimeEnd )
			{
				CWTOrderVideo theOrderVideo1;
				theOrderVideo1.m_lTimeStart=lStart;
				theOrderVideo1.m_lTimeEnd=lEnd;
				theOrderVideo1.m_strCameraIndexCode=m_strCameraIndexCode;
				theOrderVideo1.m_iOrderID=m_iOrderID;
				m_aVideo.Add(theOrderVideo1);
				strLog.Format(_T("%ld,%ld"),theOrderVideo1.m_lTimeStart,theOrderVideo1.m_lTimeEnd);
				theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strLog);

				lStart=lEnd;
				lEnd=lStart+MAX_SECOND_OF_VIDEO;
			}
			if ( lStart<m_lTimeEnd && lEnd>m_lTimeEnd )
			{
				CWTOrderVideo theOrderVideo2;
				theOrderVideo2.m_lTimeStart=lStart;
				theOrderVideo2.m_lTimeEnd=m_lTimeEnd;
				theOrderVideo2.m_strCameraIndexCode=m_strCameraIndexCode;
				theOrderVideo2.m_iOrderID=m_iOrderID;
				m_aVideo.Add(theOrderVideo2);
				strLog.Format(_T("%ld,%ld"),theOrderVideo2.m_lTimeStart,theOrderVideo2.m_lTimeEnd);
				theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strLog);
			}
			strLog.Format(_T("m_lTimeEnd=%ld,%s"),m_lTimeEnd,CTime(m_lTimeEnd).Format(_T("%Y-%m-%d %H:%M:%S")));
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("GetVideoToDownload"),strLog);

			if ( m_aVideo.GetCount()>0 ) bReturn=TRUE;
		}
		else
		{
			PostNoVideo();
		}
	}  
	mysql_free_result(m_result);  
	mysql_close(&m_sqlCon);//关闭Mysql连接

	return bReturn;
}

BOOL CWTOrder::HaveVideo()
{
	if ( !theApp.m_Basic.isServiceInit() )
	{
		return FALSE;
	}	
	int iRecordType = 0;
    iRecordType|=HIK_RECTYPE_PLAN;
	iRecordType|=HIK_RECTYPE_MOVE;
	iRecordType|=HIK_RECTYPE_ALARM;
	iRecordType|=HIK_RECTYPE_MANUAL;

	CTime absTimeFrom(m_lTimeStart);
	CTime absTimeTo(m_lTimeEnd);

	CString strLog=_T("");
	strLog.Format(_T("m_iOrderID=%d,m_strCameraIndexCode=%s"),m_iOrderID,m_strCameraIndexCode);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);
	strLog.Format(_T("m_lTimeStart=%ld,%s"),m_lTimeStart,CTime(m_lTimeStart).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);
	strLog.Format(_T("m_lTimeEnd=%ld,%s"),m_lTimeEnd,CTime(m_lTimeEnd).Format(_T("%Y-%m-%d %H:%M:%S")));
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);

	char szXML[PLAT_RECORD_RESULT_XML_BUFFER_SIZE] = {0};
	int iFileHanlde=-1;
	int iCount=3;
	while ( iFileHanlde==-1 && iCount>0 )
	{
		iFileHanlde = HikPt_QueryRecord(m_strCameraIndexCode,__int64(absTimeFrom.GetTime()),__int64(absTimeTo.GetTime()),szXML,PLAT_RECORD_RESULT_XML_BUFFER_SIZE,iRecordType);
		strLog.Format(_T("iFileHanlde=%d,iCount=%d"),iFileHanlde,iCount);
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);
		if ( iFileHanlde==-1 )
		{
			strLog.Format(_T("HikPt_QueryRecord return -1 %d"),iCount);
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);
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
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),strLog);
		return FALSE;		
	}
	if (szXML == NULL)
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),_T("szXML == NULL"));
		return FALSE;		
	}
	HikPt_CloseQueryRecord(iFileHanlde);
	CString strXML=_T("");
	strXML.Format(_T("%s"),szXML);	
	theApp.m_Basic.SaveLog(_T("CWTOrderVideo"),_T("HaveVideo"),szXML);
	if ( strXML.Find(_T("<SegmentCount>"))<0 && strXML.Find(_T("</SegmentCount>"))<0 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),_T("no SegmentCount"));
		return FALSE;		
	}
	if ( strXML.Find(_T("<SegmentCount>0</SegmentCount>"))>0 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),_T("Find <SegmentCount>0</SegmentCount>"));
		return FALSE;		
	}
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("HaveVideo"),_T("end"));
	return TRUE;
}

void CWTOrder::PostNoVideo()
{
	CWTHttpClient theHttpClient;
	string strResponse;
	CString strUrl=_T("http://fashion.ybxin.net/tuyunwx/index.php?s=/addon/Tuzhen/Admin/handleTuyunCameraOrderFromAutoDownload.html");
	CString strPostData=_T("");
	strPostData.Format(_T("id=%d&order_status=3&msg=未找到相应时段的录像"),m_iOrderID);
	int iPost=theHttpClient.HttpPost(strUrl,strPostData,strResponse);

	CString strLog=_T("");
	strLog.Format(_T("strUrl=%s"),strUrl);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostNoVideo"),strLog);
	strLog.Format(_T("strPostData=%s"),strPostData);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostNoVideo"),strLog);
	strLog.Format(_T("iPost=%d"),iPost);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostNoVideo"),strLog);
	strLog.Format(_T("strResponse=%s"),strResponse.c_str());
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostNoVideo"),strLog);
}

BOOL CWTOrder::StartDownload()
{
	int iCount=m_aVideo.GetSize();
	if (iCount<1)
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("StartDownload"),_T("没有需要下载的录像！"));
		return FALSE;
	}
	CString strLog=_T("");
	strLog.Format(_T("iCount=%d"),iCount);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("StartDownload"),strLog);
	int i=0;
	int iCountDownOK=0;
	for ( i=0;i<iCount;i++ )
	{
		CWTOrderVideo theOrderVideo=m_aVideo.GetAt(i);
		if ( theOrderVideo.StartDownload() )
		{
			iCountDownOK++;
		}
	}
	if ( iCountDownOK==0 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("StartDownload"),_T("下载失败！"));
		return FALSE;
	}
	return TRUE;
}

BOOL CWTOrder::isStopDownload()
{
	if ( !theApp.m_Basic.isServiceInit() )
	{
		return FALSE;
	}
	int i=0;
	int iCount=m_aVideo.GetSize();
	CString strLog=_T("");
	strLog.Format(_T("iCount=%d"),iCount);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("isStopDownload"),strLog);
	if (iCount<1)
	{
		return TRUE;
	}
	for ( i=0;i<iCount;i++ )
	{
		CWTOrderVideo theOrderVideo=m_aVideo.GetAt(i);
		if ( !theOrderVideo.isStopDownload() )
		{
			strLog.Format(_T("i=%d"),i);
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("isStopDownload"),strLog);
			m_lTimeNULL=GetTickCount();
			return FALSE;
		}
	}
	DoDownLoadFinish();
	return TRUE;
}

void CWTOrder::DoDownLoadFinish()
{
	updateOrderStatus();
}

int CWTOrder::getOrderStatus()
{
	int iOrderStatus=-1;
	
	MYSQL m_sqlCon;  
	mysql_init(&m_sqlCon);    
	if(!mysql_real_connect(&m_sqlCon,"192.168.1.106","root","www.lagou.org","tuyunwxdb_new",4406,NULL,0))    
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),_T("连接数据库失败!"));  
		CString e=mysql_error(&m_sqlCon);  
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),e);  
		return iOrderStatus;  
	}  
	else  
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),_T("连接数据库成功!"));  
		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");
	}  
	//查询
	MYSQL_RES *m_result;
	MYSQL_ROW row; 
	CString strSQL=_T("");//SQl语句  	  
	strSQL.Format("select order_status from wp_tuyun_camera_order where id=%d",m_iOrderID); //sql操作语句
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),strSQL);  
	mysql_query(&m_sqlCon,strSQL);  	  
	m_result=mysql_use_result(&m_sqlCon);  
	if (NULL == m_result)//如果为空则返回
	{ 
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),_T("数据库查询结果为空!"));  
		return FALSE;  
	}
	if ( row=mysql_fetch_row(m_result) )  
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),_T("获取数据!"));  
  	  
		CString data=row[0];  
		
		iOrderStatus=_ttoi(data);
	}  
	mysql_free_result(m_result);  
	mysql_close(&m_sqlCon);//关闭Mysql连接

	CString strLog=_T("");
	strLog.Format(_T("iOrderStatus=%d"),iOrderStatus);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("getOrderStatus"),strLog);

	return iOrderStatus;
}

BOOL CWTOrder::updateOrderStatus()
{
	if ( getOrderStatus()==2 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),_T("getOrderStatus=2"));
		return TRUE;
	}
	if ( !isVideoOK() )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),_T("isVideoOK=false"));
		return FALSE;
	}
	MYSQL m_sqlCon;  
	mysql_init(&m_sqlCon);    
	if(!mysql_real_connect(&m_sqlCon,"192.168.1.106","root","www.lagou.org","tuyunwxdb_new",4406,NULL,0))    
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),_T("连接数据库失败!"));  
		CString e=mysql_error(&m_sqlCon);
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),e);  
		return FALSE;  
	}  
	else  
	{    
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),_T("连接数据库成功!"));  
		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");
	}
	
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),_T("更新数据"));  
	CString strSQL=_T("");
	strSQL.Format("update wp_tuyun_camera_order  set order_status=2 where id=%d",m_iOrderID); //sql操作语句

	CString strLog=_T("");
	strLog.Format("更新数据:%s",strSQL);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("updateOrderStatus"),strLog);

	mysql_real_query(&m_sqlCon, strSQL,strSQL.GetLength());
	mysql_close(&m_sqlCon);//关闭Mysql连接

	//if ( getOrderStatus()==2 )
	{
		PostHaveSendGood();
	}
	return TRUE;
}
void CWTOrder::PostHaveSendGood()
{
	/*/
	if ( getOrderStatus()!=2 )
	{
		theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostHaveSendGood"),_T("getOrderStatus!=2"));
		return ;
	}
	//*/
	CWTHttpClient theHttpClient;
	string strResponse;
	CString strUrl=_T("http://fashion.ybxin.net/tuyunwx/index.php?s=/addon/Tuzhen/Admin/handleTuyunCameraOrderFromAutoDownload.html");
	CString strPostData=_T("");
	strPostData.Format(_T("id=%d&order_status=2"),m_iOrderID);
	int iPost=theHttpClient.HttpPost(strUrl,strPostData,strResponse);

	CString strLog=_T("");
	strLog.Format(_T("strUrl=%s"),strUrl);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostHaveSendGood"),strLog);
	strLog.Format(_T("strPostData=%s"),strPostData);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostHaveSendGood"),strLog);
	strLog.Format(_T("iPost=%d"),iPost);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostHaveSendGood"),strLog);
	strLog.Format(_T("strResponse=%s"),strResponse.c_str());
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("PostHaveSendGood"),strLog);

	int iCount=m_aVideo.GetSize();
	int i=0;
	for ( i=0;i<iCount;i++ )
	{
		CWTOrderVideo theOrderVideo=m_aVideo.GetAt(i);
		theOrderVideo.SaveVideToDB();
	}
}

BOOL CWTOrder::isVideoOK()
{
	int iCount=m_aVideo.GetSize();
	int i=0;

	CString strLog=_T("");
	strLog.Format("Video Count:%d",iCount);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("isVideoOK"),strLog);

	for ( i=0;i<iCount;i++ )
	{
		CWTOrderVideo theOrderVideo=m_aVideo.GetAt(i);
		if ( !theOrderVideo.isVideoOK() )
		{
			strLog.Format("FALSE--->Video not ok:%d",i);
			theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("isVideoOK"),strLog);
			return FALSE;
		}
	}

	strLog.Format("TRUE--->Video is ok:%d",i);
	theApp.m_Basic.SaveLog(_T("CWTOrder"),_T("isVideoOK"),strLog);
	return TRUE;
}