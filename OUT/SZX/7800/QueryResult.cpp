// QueryResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "QueryResult.h"



// CQueryResult �Ի���

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
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    m_lCtrlQueryResult.SetExtendedStyle(dwStyle); //������չ���

    m_lCtrlQueryResult.InsertColumn(0, "��ʼʱ��",LVCFMT_LEFT,200,-1);
    m_lCtrlQueryResult.InsertColumn(1, "����ʱ��",LVCFMT_LEFT,200,-1);
    m_lCtrlQueryResult.InsertColumn(2, "¼������",LVCFMT_LEFT, 200, -1);
    m_lCtrlQueryResult.InsertColumn(3, "Ƭ�γ���",LVCFMT_LEFT, 200, -1);
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
            cstmp = "�ƻ�¼��";
            break;
        case 2:
            cstmp = "�ƶ����¼��";
            break;
        case 4:
            cstmp = "�澯¼��";
            break;
        case 16:
            cstmp = "�ֶ�¼��";
            break;
        default:
            cstmp = "δ֪����";
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
