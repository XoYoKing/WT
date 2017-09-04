// DlgCruise.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgCruise.h"

extern int g_iCurWndIndex;                 ///< 当前窗口索引

extern map<int,std::string> g_mapWinIndexPreviewCID;   //窗口和cameraID的映射

// CDlgCruise 对话框

IMPLEMENT_DYNAMIC(CDlgCruise, CDialog)

CDlgCruise::CDlgCruise(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCruise::IDD, pParent)
{

}

CDlgCruise::~CDlgCruise()
{
}

void CDlgCruise::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CRUISE, m_ListCruise);
}



BEGIN_MESSAGE_MAP(CDlgCruise, CDialog)
    ON_BN_CLICKED(IDC_BTN_ADD, &CDlgCruise::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_DEL, &CDlgCruise::OnBnClickedBtnDel)
    ON_BN_CLICKED(IDC_BTN_OK, &CDlgCruise::OnBnClickedBtnOK)
    ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgCruise::OnBnClickedBtnCancel)
    ON_MESSAGE(WM_STARTCRUISE,StartCruise)
    ON_MESSAGE(WM_STOPCRUISE,StopCruise)
END_MESSAGE_MAP()


// CDlgCruise 消息处理程序

BOOL CDlgCruise::OnInitDialog()
{
    CDialog::OnInitDialog();

    InitCtrl();

    return TRUE;
}

void CDlgCruise::InitCtrl()
{
    m_ListCruise.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    //初始化记录列表
    m_ListCruise.InsertColumn(0,_T("预置点序号"),LVCFMT_LEFT,100,-1);
    m_ListCruise.InsertColumn(1,_T("停留时间(秒)"),LVCFMT_LEFT,100,-1);
    m_ListCruise.InsertColumn(2,_T("巡航速度"),LVCFMT_LEFT,100,-1);
}

void CDlgCruise::OnBnClickedBtnAdd()
{
    int iCount = m_ListCruise.GetItemCount();
    if(iCount >= 32)
    {
        return;
    }

    // 插入新的列表项并初始化
    CString strTemp = _T("");
    strTemp.Format(_T("%d"),iCount+1);
    m_ListCruise.InsertItem(iCount,strTemp);
    m_ListCruise.SetItemText(iCount,1,_T("2"));
    m_ListCruise.SetItemText(iCount,2,_T("30"));
}

void CDlgCruise::OnBnClickedBtnDel()
{
    // 删除选中的列表项
    POSITION SelPos = m_ListCruise.GetFirstSelectedItemPosition();
    int iSelIndex = m_ListCruise.GetNextSelectedItem(SelPos);

    // 从列表中删除预置点
    m_ListCruise.DeleteItem(iSelIndex);

    // 设置列表项状态及“删除”按钮状态
    int iCount = m_ListCruise.GetItemCount();
    if (iCount > 0)
    {
        for(int i = iSelIndex;i <iCount; i++)
        {
            CString strTemp;
            strTemp.Format(_T("%d"),i+1);
            m_ListCruise.SetItemText(i,0,strTemp);
        }

        m_ListCruise.SetFocus();
        if (0 == iSelIndex)
        {
            iSelIndex = 1;
        }
        m_ListCruise.SetItemState(iSelIndex - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
    }
}

void CDlgCruise::OnBnClickedBtnOK()
{
    if (FALSE == UpdateData(TRUE))
    {
        return;
    }

    // 判断参数是否有效
    if(ValidateParam() == FALSE)
    {
        return;
    }

    HikCruiseInfo* pHeader = NULL, *pNext = NULL;

    // 获取当前列表项数
    int iCount = m_ListCruise.GetItemCount();
    if(iCount >= 0)
    {
        for(int i= 0; i < iCount; i++)
        {

            HikCruiseInfo* struCruiseRet = new(std::nothrow)HikCruiseInfo;
            if(struCruiseRet == NULL)
            {
                return;
            }
            memset(struCruiseRet,0,sizeof(HikCruiseInfo));
            struCruiseRet->pNext = NULL;

            struCruiseRet->nPresetNo = i + 1;
            struCruiseRet->nDwell = atoi(m_ListCruise.GetItemText(i,1));
            struCruiseRet->nSpeed = atoi(m_ListCruise.GetItemText(i,2));
            
            if(pHeader == NULL)
            {
                pHeader = struCruiseRet;
            }
            else
            {
                if(pNext != NULL)
                {
                    pNext->pNext = struCruiseRet;
                }
            }
            pNext = struCruiseRet;
        }
    }

    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        std::string CameraID = ptr->second;
        HikPt_SetCruiseInfo(CameraID.c_str(), 1, pHeader);
    }

    CDialog::OnOK();
}

void CDlgCruise::OnBnClickedBtnCancel()
{
    CDialog::OnCancel();
}

BOOL CDlgCruise::ValidateParam()
{
    int iTime = 0,iSpeed = 0;
    int iCount = m_ListCruise.GetItemCount();
    if(iCount > 0) // 如果列表不为空
    {
        for(int i= 0; i < iCount; i++)
        {
            // 巡航时间是否有效
            iTime = atoi(m_ListCruise.GetItemText(i,1));
            if(iTime < 1 || iTime > 128)
            {
                MessageBox(_T("停留时间在1-128之间！"));
                return FALSE;
            }

            // 巡航速度是否有效
            iSpeed = atoi(m_ListCruise.GetItemText(i,2));
            if(iSpeed < 1 || iSpeed > 40)
            {
                MessageBox(_T("巡航速度在1-40之间！"));
                return FALSE;
            }
        }
    }

    return TRUE;
}

LRESULT CDlgCruise::StartCruise(WPARAM wparam, LPARAM lparam)
{
    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        std::string CameraID = ptr->second;
        if (HikPt_PtzControl(CameraID.c_str(), PLAT_RUN_SEQ ,0, 1, 0) != 0)
        {
            PLAT_ERROR("Plat_VSS_ControlCamera,PLAT_RUN_SEQ failed! last error = %d",HikPt_GetLastError());
        }
    }
     return 0;
}

LRESULT CDlgCruise::StopCruise(WPARAM wparam, LPARAM lparam)
{
    map<int,std::string>::iterator ptr = g_mapWinIndexPreviewCID.find(g_iCurWndIndex);
    if (ptr != g_mapWinIndexPreviewCID.end())
    {
        std::string CameraID = ptr->second;
        if(HikPt_PtzControl(CameraID.c_str(), PLAT_STOP_SEQ ,1, 1, 0) != 0)
        {
            PLAT_ERROR("Plat_VSS_ControlCamera,PLAT_RUN_SEQ failed! last error = %d",HikPt_GetLastError());
        }
    }
    return 0;
}
