// CamTree.cpp : 实现文件
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "CamTree.h"
#include "DlgPreview.h"
#include "VSSSubsysDlg.h"
#include "DlgPlayBack.h"


// CCamTree 对话框
extern VSSSubsysDlg* g_dlgVSSSubsys;
extern CDlgPreview* g_dlgPreview;
extern CDlgPlayBack* g_dlgPlayBack;
extern int g_iMainType;					///< 当前窗口标记

map<int,std::string> g_mapCam_ID_indexcode;   //camera ID和indexcode的映射

IMPLEMENT_DYNAMIC(CCamTree, CDialog)

CCamTree::CCamTree(CWnd* pParent /*=NULL*/)
	: CDialog(CCamTree::IDD, pParent)
{
m_strIoFctName = "";
}

CCamTree::~CCamTree()
{
}

void CCamTree::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_CAM, m_CamTreeCtrl);
}


BEGIN_MESSAGE_MAP(CCamTree, CDialog)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_CAM, &CCamTree::OnNMDblclkTree)
    ON_NOTIFY(NM_CLICK, IDC_TREE_CAM, &CCamTree::OnNMClickTree)
//    ON_NOTIFY(NM_RCLICK, IDC_TREE_CAM, &CCamTree::OnNMRClickTree1)
//     ON_COMMAND(ID_TREE_PREVIEW, &CCamTree::OnTreePreview)
//     ON_COMMAND(ID_TREE_QUERY, &CCamTree::OnTreeQuery)
END_MESSAGE_MAP()


// CCamTree 消息处理程序

void CCamTree::OnNMDblclkTree(NMHDR *, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    HTREEITEM hNode = m_CamTreeCtrl.GetSelectedItem();
    if (NULL == hNode || g_iMainType != PREVIEW_T)//it works to double click device tree only while preview
    {
        return;
    }
    int iItemData = m_CamTreeCtrl.GetItemData(hNode);
    int iId = iItemData >> 8;
    int iType = iItemData & 0x000000FF;
    CString csTemp = m_CamTreeCtrl.GetItemText(hNode);
    switch (iType)
    {
    case 0:
    case 1:
    case 2:
        if (csTemp.Find('+') == 0)
            csTemp.Replace('+', '-');
        else
            csTemp.Replace('-', '+');
        m_CamTreeCtrl.SetItemText(hNode, csTemp);
        break;
    case 3:
        ::PostMessage(g_dlgPreview->GetSafeHwnd(),WM_STARTPLAY,(WPARAM)iId, (LPARAM)0);
        break;
    }
    *pResult = 0;
}

// 
void CCamTree::OnNMClickTree(NMHDR *, LRESULT *pResult)
{

    CPoint pt(0,0);
    GetCursorPos(&pt);

    CRect rect(0,0,0,0);
    ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_CAM)->GetWindowRect(&rect);
    ScreenToClient(&rect);

    pt.x = pt.x-rect.left;
    pt.y = pt.y-rect.top;

    UINT uFlags = 0;
    HTREEITEM hSelect = m_CamTreeCtrl.HitTest(pt,&uFlags);
    if (hSelect == NULL)
    {
        return;
    }
//     BOOL bLogined = FALSE;
//     DWORD dwNoteData = m_CamTreeCtrl.GetItemData(hSelect);
// 
// 
//     // TODO: Add your control notification handler code here
//     HTREEITEM hNode = m_CamTreeCtrl.GetSelectedItem();
    int iItemData = m_CamTreeCtrl.GetItemData(hSelect);
    int iId = iItemData >> 8;
    int iType = iItemData & 0x000000FF;
 //   CString csTemp = m_CamTreeCtrl.GetItemText(hNode);
     switch (iType)
     {
//     case 0:
//     case 1:
//     case 2:
//         if (csTemp.Find('+') == 0)
//             csTemp.Replace('+', '-');
//         else
//             csTemp.Replace('-', '+');
//         m_CamTreeCtrl.SetItemText(hNode, csTemp);
//         break;
    case 3:
        ::PostMessage(g_dlgPlayBack->GetSafeHwnd(),WM_SELECTPLAYBACKCID,(WPARAM)iId, (LPARAM)0);
        break;
    }
    *pResult = 0;
}


HTREEITEM CCamTree::FindCamTreeItem(HTREEITEM item, int iData)
{
    if (item == NULL)
        return NULL;

    HTREEITEM hFound;
    while (item)
    {
        if (item != TVI_ROOT)
            if ((PtrToInt(m_CamTreeCtrl.GetItemData(item))) == iData)
                return item;

        HTREEITEM hChild = m_CamTreeCtrl.GetChildItem(item);
        if (hChild)
        {
            hFound = FindCamTreeItem(hChild, iData);
            if (hFound)
                return hFound;
        }

        if (item != TVI_ROOT)
            item = m_CamTreeCtrl.GetNextSiblingItem(item);
        else
            break;
    }

    return NULL;
}


void CCamTree::QueryCamResource()
{
    int iErrNum = 0;
    
    int nCellSize = HIK_MAX_SIZE_RES_CELL;
    HikCellInfo* pCellList = new (std::nothrow) HikCellInfo[nCellSize];
    if(pCellList == NULL)
    {
        return;
    }
    
    if (HikPt_GetResCellList(pCellList,nCellSize,HIK_WBS_OPCODE_PLAYVIEW,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK && pCellList != NULL)
    {
        for(int nCellIndex=0; nCellIndex<nCellSize; ++nCellIndex)
        {
            int Id = pCellList[nCellIndex].nId;
            CString Name = pCellList[nCellIndex].szCellName;
            int high = pCellList[nCellIndex].nParentId;
            HTREEITEM hParent = FindCamTreeItem(TVI_ROOT, (high << 8) + 0);
            HTREEITEM hItem = m_CamTreeCtrl.InsertItem( Name, (hParent == NULL ? TVI_ROOT : hParent), 0);
            m_CamTreeCtrl.SetItemData(hItem, (Id << 8) + 0);
            
            int nCameraSize = HIK_MAX_SIZE_RES_CAMERA;
            HikCameraInfo* pCameraList = new (std::nothrow) HikCameraInfo[nCameraSize];
            if(pCameraList == NULL)
            {
                continue;
            }

            if(HikPt_GetCameraListByCellId(pCameraList,nCameraSize,pCellList[nCellIndex].nId,HIK_WBS_OPCODE_PLAYVIEW) == HIKPT_E_OK && pCameraList != NULL)
            {
                for(int nIndex=0; nIndex<nCameraSize; ++nIndex)
                {
                    int Id = pCameraList[nIndex].nCamId;
                    CString Name = pCameraList[nIndex].szCameraName;
                    int high = pCameraList[nIndex].nCellId;
                    HTREEITEM hParent = FindCamTreeItem(TVI_ROOT, (high << 8) + 0);
                    HTREEITEM hItem = m_CamTreeCtrl.InsertItem(Name, 2 , 2 , (hParent == NULL ? TVI_ROOT : hParent));
                    m_CamTreeCtrl.SetItemData(hItem, (Id << 8) + 3);
                    g_mapCam_ID_indexcode[Id] = pCameraList[nIndex].szIndexCode;
                }
            }

            if(pCameraList != NULL)
            {
                delete [] pCameraList;
                pCameraList = NULL;
            }
        }
    }
    else
    {
        iErrNum = HikPt_GetLastError();
    }

    if(pCellList != NULL)
    {
        delete [] pCellList;
        pCellList = NULL;
    }

    CWnd *pWnd = theApp.GetMainWnd();
    if(0 != iErrNum && pWnd && pWnd->m_hWnd)
        ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&m_strIoFctName, (LPARAM)iErrNum);

    HTREEITEM hRootItem = m_CamTreeCtrl.GetRootItem();
    if(m_CamTreeCtrl.ItemHasChildren(hRootItem))
    {
        m_CamTreeCtrl.Expand(hRootItem,TVE_EXPAND);
    }
}


BOOL CCamTree::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ImgList.Create(16, 16, ILC_COLOR32|ILC_MASK, 1, 1);
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CELL));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_AREA));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAM));

    m_CamTreeCtrl.SetImageList(&m_ImgList, TVSIL_NORMAL);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}