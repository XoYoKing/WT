// QueryResult.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "QueryResult.h"



// CQueryResult 对话框

IMPLEMENT_DYNAMIC(CQueryResult, CDialog)

CQueryResult::CQueryResult(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryResult::IDD, pParent)
{

}

CQueryResult::~CQueryResult()
{
}

void CQueryResult::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_QUERYRESULT, m_lCtrlQueryResult);
}


BEGIN_MESSAGE_MAP(CQueryResult, CDialog)
END_MESSAGE_MAP()



BOOL CQueryResult::OnInitDialog()
{
    CDialog::OnInitDialog();

    DWORD dwStyle = m_lCtrlQueryResult.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_lCtrlQueryResult.SetExtendedStyle(dwStyle); //设置扩展风格

    m_lCtrlQueryResult.InsertColumn(0, "开始时间",LVCFMT_LEFT,200,-1);
    m_lCtrlQueryResult.InsertColumn(1, "结束时间",LVCFMT_LEFT,200,-1);
    m_lCtrlQueryResult.InsertColumn(2, "录像类型",LVCFMT_LEFT, 200, -1);
    m_lCtrlQueryResult.InsertColumn(3, "片段长度",LVCFMT_LEFT, 200, -1);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

std::string TimetToString(time_t t)
{
    std::string str;
    tm ltm;
    errno_t err = localtime_s(&ltm, &t);
    if (0 == err)
    {
        char buffer[256] = {0};
        strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", &ltm);
        str = buffer;
    }
    return str;
}

void CQueryResult::InsertQueryResult(RECORD_SEARCH_RESULT_MAP& pQueryResult,int iFileNum)
{
    CString cstmp;
    int i = 0;
    for (RECORD_SEARCH_RESULT_MAP::iterator iter = pQueryResult.begin(); iter != pQueryResult.end(); iter++)
    {
        std::string strBegin = TimetToString(iter->second.stBrief.tBegin);
        std::string strEnd = TimetToString(iter->second.stBrief.tEnd);

        m_lCtrlQueryResult.InsertItem(i,strBegin.c_str(),0);
        m_lCtrlQueryResult.SetItemText(i,1,strEnd.c_str());
       
        switch(iter->second.stBrief.recordType)
        {
        case 1:
            cstmp = "计划录像";
            break;
        case 2:
            cstmp = "移动侦测录像";
            break;
        case 4:
            cstmp = "告警录像";
            break;
        case 16:
            cstmp = "手动录像";
            break;
        default:
            cstmp = "未知类型";
            break;
        }
        m_lCtrlQueryResult.SetItemText(i,2,cstmp);


        LONG64 dwFileSize = iter->second.mediaDataLen;
        if (dwFileSize / 1024 == 0)
        {
            cstmp.Format("%d",dwFileSize);
        }
        else if (dwFileSize / 1024 > 0 && dwFileSize / (1024*1024) == 0)
        {
            cstmp.Format("%dKB",dwFileSize / 1024);
        }
        else
        {
            cstmp.Format("%dMB",dwFileSize / 1024/1024);//different from hard disk capacity, files need tranformation
        }
        m_lCtrlQueryResult.SetItemText(i,3,cstmp);
        i++;
    }
}
