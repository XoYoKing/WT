// DlgCruise.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgCruise.h"

extern int g_iCurWndIndex;                 ///< ��ǰ��������

extern map<int,std::string> g_mapWinIndexPreviewCID;   //���ں�cameraID��ӳ��

// CDlgCruise �Ի���

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


// CDlgCruise ��Ϣ�������

BOOL CDlgCruise::OnInitDialog()
{
    CDialog::OnInitDialog();

    InitCtrl();

    return TRUE;
}

void CDlgCruise::InitCtrl()
{
    m_ListCruise.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    //��ʼ����¼�б�
    m_ListCruise.InsertColumn(0,_T("Ԥ�õ����"),LVCFMT_LEFT,100,-1);
    m_ListCruise.InsertColumn(1,_T("ͣ��ʱ��(��)"),LVCFMT_LEFT,100,-1);
    m_ListCruise.InsertColumn(2,_T("Ѳ���ٶ�"),LVCFMT_LEFT,100,-1);
}

void CDlgCruise::OnBnClickedBtnAdd()
{
    int iCount = m_ListCruise.GetItemCount();
    if(iCount >= 32)
    {
        return;
    }

    // �����µ��б����ʼ��
    CString strTemp = _T("");
    strTemp.Format(_T("%d"),iCount+1);
    m_ListCruise.InsertItem(iCount,strTemp);
    m_ListCruise.SetItemText(iCount,1,_T("2"));
    m_ListCruise.SetItemText(iCount,2,_T("30"));
}

void CDlgCruise::OnBnClickedBtnDel()
{
    // ɾ��ѡ�е��б���
    POSITION SelPos = m_ListCruise.GetFirstSelectedItemPosition();
    int iSelIndex = m_ListCruise.GetNextSelectedItem(SelPos);

    // ���б���ɾ��Ԥ�õ�
    m_ListCruise.DeleteItem(iSelIndex);

    // �����б���״̬����ɾ������ť״̬
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

    // �жϲ����Ƿ���Ч
    if(ValidateParam() == FALSE)
    {
        return;
    }

    HikCruiseInfo* pHeader = NULL, *pNext = NULL;

    // ��ȡ��ǰ�б�����
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
    if(iCount > 0) // ����б�Ϊ��
    {
        for(int i= 0; i < iCount; i++)
        {
            // Ѳ��ʱ���Ƿ���Ч
            iTime = atoi(m_ListCruise.GetItemText(i,1));
            if(iTime < 1 || iTime > 128)
            {
                MessageBox(_T("ͣ��ʱ����1-128֮�䣡"));
                return FALSE;
            }

            // Ѳ���ٶ��Ƿ���Ч
            iSpeed = atoi(m_ListCruise.GetItemText(i,2));
            if(iSpeed < 1 || iSpeed > 40)
            {
                MessageBox(_T("Ѳ���ٶ���1-40֮�䣡"));
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
