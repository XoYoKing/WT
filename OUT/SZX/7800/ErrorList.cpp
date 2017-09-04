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
        error = "无错误";
        break;
    case 1:
        error = "用户不存在";
        break;
    case 2:
        error = "密码错误";
        break;
    case 3:
        error = "参数错误";
        break;
    case 4:
        error = "设备无响应";
        break;
    case 5:
        error = "网络异常";
        break;
    case 6:
        error = "用户已经登录";
        break;
    case 7:
        error = "未知原因";
        break;
    case 8:
        error = "用户名称不唯一";
        break;
    case 9:
        error = "用户已经过期";
        break;
    case 10:
        error = "用户未激活";
        break;
    case 11:
        error = "用户无权限";
        break;
    case 12:
        error = "没有初始化";
        break;
    case 13:
        error = "流媒体库启动失败";
        break;
    case 14:
        error = "无此用户会话ID";
        break;
    case 15:
        error = "找不到资源";
        break;
    case 16:
        error = "查询录像文件失败";
        break;
    case 17:
        error = "空指针操作";
        break;   
    case 18:
        error = "获取中心信息失败";
        break;
    case 19:
        error = "获取区域信息失败";
        break;
    case 20:
        error = "获取编码设备信息失败";
        break;
    case 21:
        error = "获取摄像头信息失败";
        break;
    case 22:
        error = "获取IO设备信息失败";
        break;
    case 23:
        error = "获取设备主机信息失败";
        break;
    case 24:
        error = "获取设备通道信息失败";
        break;
    case 25:
        error = "获取人员信息失败";
        break;
    case 26:
        error = "获取门禁设备信息失败";
        break;
    case 27:
        error = "获取门禁点信息失败";
        break;
    case 28:
        error = "获取卡信息失败";
        break;
    case 29:
        error = "获取报警服务器信息失败";
        break;
    case 30:
        error = "获取DAG服务器信息失败";
        break;
    case 31:
        error = "获取状态失败";
        break;
    case 32:
        error = "DAG连接失败";
        break;
    case 33:
        error = "DAG控制失败";
        break;
    case 34:
        error = "创建查询资源失败";
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
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_ListError.SetExtendedStyle(dwStyle); //设置扩展风格

    m_ListError.InsertColumn(0, "时间",LVCFMT_LEFT,200,-1);
    m_ListError.InsertColumn(1, "操作",LVCFMT_LEFT,200,-1);
    m_ListError.InsertColumn(2, "结果", LVCFMT_LEFT, 200, -1);
    m_ListError.InsertColumn(3, "错误码", LVCFMT_LEFT, 80, -1);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
