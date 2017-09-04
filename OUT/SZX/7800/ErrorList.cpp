// ErrorList.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "ErrorList.h"


// CErrorList dialog

IMPLEMENT_DYNAMIC(CErrorList, CDialog)

CErrorList::CErrorList(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorList::IDD, pParent)
{
    m_index = 0;
}

CErrorList::~CErrorList()
{
}

void CErrorList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListError);
}


BEGIN_MESSAGE_MAP(CErrorList, CDialog)
END_MESSAGE_MAP()


// CErrorList message handlers

void CErrorList::InsertLog(const char * oper, int errorcode)
{
    CTime time = CTime::GetCurrentTime();
    CString date = time.Format("%Y-%m-%d %H:%M:%S");
    m_ListError.InsertItem(m_index, date, 0);
    m_ListError.SetItemText(m_index, 1, oper);

    CString error;
    switch(errorcode)
    {
    case 0:
        error = "�޴���";
        break;
    case 1:
        error = "�û�������";
        break;
    case 2:
        error = "�������";
        break;
    case 3:
        error = "��������";
        break;
    case 4:
        error = "�豸����Ӧ";
        break;
    case 5:
        error = "�����쳣";
        break;
    case 6:
        error = "�û��Ѿ���¼";
        break;
    case 7:
        error = "δ֪ԭ��";
        break;
    case 8:
        error = "�û����Ʋ�Ψһ";
        break;
    case 9:
        error = "�û��Ѿ�����";
        break;
    case 10:
        error = "�û�δ����";
        break;
    case 11:
        error = "�û���Ȩ��";
        break;
    case 12:
        error = "û�г�ʼ��";
        break;
    case 13:
        error = "��ý�������ʧ��";
        break;
    case 14:
        error = "�޴��û��ỰID";
        break;
    case 15:
        error = "�Ҳ�����Դ";
        break;
    case 16:
        error = "��ѯ¼���ļ�ʧ��";
        break;
    case 17:
        error = "��ָ�����";
        break;   
    case 18:
        error = "��ȡ������Ϣʧ��";
        break;
    case 19:
        error = "��ȡ������Ϣʧ��";
        break;
    case 20:
        error = "��ȡ�����豸��Ϣʧ��";
        break;
    case 21:
        error = "��ȡ����ͷ��Ϣʧ��";
        break;
    case 22:
        error = "��ȡIO�豸��Ϣʧ��";
        break;
    case 23:
        error = "��ȡ�豸������Ϣʧ��";
        break;
    case 24:
        error = "��ȡ�豸ͨ����Ϣʧ��";
        break;
    case 25:
        error = "��ȡ��Ա��Ϣʧ��";
        break;
    case 26:
        error = "��ȡ�Ž��豸��Ϣʧ��";
        break;
    case 27:
        error = "��ȡ�Ž�����Ϣʧ��";
        break;
    case 28:
        error = "��ȡ����Ϣʧ��";
        break;
    case 29:
        error = "��ȡ������������Ϣʧ��";
        break;
    case 30:
        error = "��ȡDAG��������Ϣʧ��";
        break;
    case 31:
        error = "��ȡ״̬ʧ��";
        break;
    case 32:
        error = "DAG����ʧ��";
        break;
    case 33:
        error = "DAG����ʧ��";
        break;
    case 34:
        error = "������ѯ��Դʧ��";
        break;
    default:
        break;
    }

    m_ListError.SetItemText(m_index, 2, error);

    error.Format("%d", errorcode);

    m_ListError.SetItemText(m_index, 3, error);
    int   nCount   =   m_ListError.GetItemCount();   
    if   (nCount   >   0)   
        m_ListError.EnsureVisible(nCount-1,   FALSE);   
    m_index++;
    return;
}

// CErrorList message handlers

BOOL CErrorList::OnInitDialog()
{
    CDialog::OnInitDialog();

    DWORD dwStyle = m_ListError.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    m_ListError.SetExtendedStyle(dwStyle); //������չ���

    m_ListError.InsertColumn(0, "ʱ��",LVCFMT_LEFT,200,-1);
    m_ListError.InsertColumn(1, "����",LVCFMT_LEFT,200,-1);
    m_ListError.InsertColumn(2, "���", LVCFMT_LEFT, 200, -1);
    m_ListError.InsertColumn(3, "������", LVCFMT_LEFT, 80, -1);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
