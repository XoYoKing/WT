// IOTree.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "IOTree.h"

CString  CIOTree::g_strIoFctName = "";
// CIOTree dialog

IMPLEMENT_DYNAMIC(CIOTree, CDialog)

CIOTree::CIOTree(CWnd* pParent /*=NULL*/)
	: CDialog(CIOTree::IDD, pParent)
{

}

CIOTree::~CIOTree()
{
}

void CIOTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_IO, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CIOTree, CDialog)
    ON_NOTIFY(NM_RCLICK, IDC_TREE_IO, &CIOTree::OnNMRClickTreeIo)
END_MESSAGE_MAP()


// CIOTree message handlers

HTREEITEM CIOTree::FindIoTreeItem(HTREEITEM item, int iData)
{
    if (item == NULL)
        return NULL;

    HTREEITEM hFound;
    while (item)
    {
        if (item != TVI_ROOT)
            if ((PtrToInt(m_TreeCtrl.GetItemData(item))) == iData)
                return item;

        HTREEITEM hChild = m_TreeCtrl.GetChildItem(item);
        if (hChild)
        {
            hFound = FindIoTreeItem(hChild, iData);
            if (hFound)
                return hFound;
        }

        if (item != TVI_ROOT)
            item = m_TreeCtrl.GetNextSiblingItem(item);
        else
            break;
    }

    return NULL;
}


void CIOTree::QueryIoResource()
{   
    int iErrNum = 0;
    int nCellSize = HIK_MAX_SIZE_RES_CELL;
    HikCellInfo* pCellList = new (std::nothrow) HikCellInfo[nCellSize];
    if(pCellList == NULL)
    {
        return;
    }

    if (HikPt_GetResCellList(pCellList,nCellSize,HIK_WBS_OPCODE_IO,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK && pCellList != NULL)
    {  
        for(int nCellIndex=0; nCellIndex<nCellSize; ++nCellIndex)
        {
            int Id = pCellList[nCellIndex].nId;
            CString Name = pCellList[nCellIndex].szCellName;
            int high = pCellList[nCellIndex].nParentId;
            HTREEITEM hParent = FindIoTreeItem(TVI_ROOT, (high << 8) + 0);
            HTREEITEM hItem = m_TreeCtrl.InsertItem( Name, (hParent == NULL ? TVI_ROOT : hParent), 0);
            m_TreeCtrl.SetItemData(hItem, (Id << 8) + 0);

            int nIoSize = HIK_MAX_SIZE_RES_IO;
            HikIOInfo* pIoList = new (std::nothrow) HikIOInfo[nIoSize];
            if(pIoList == NULL)
            {
                continue;
            }

            if(HikPt_GetIOListByCellId(pIoList,nIoSize,pCellList[nCellIndex].nId) == HIKPT_E_OK && pIoList != NULL)
            {
                for(int nIndex=0; nIndex<nIoSize; ++nIndex)
                {
                    int Id = pIoList[nIndex].nId;
                    CString Name = pIoList[nIndex].szIoName;
                    int high = pIoList[nIndex].nCellId;
                    HTREEITEM hParent = FindIoTreeItem(TVI_ROOT, (high << 8) + 0);
                    HTREEITEM hItem = m_TreeCtrl.InsertItem(Name, 2 , 2 , (hParent == NULL ? TVI_ROOT : hParent));
                    m_TreeCtrl.SetItemData(hItem, (Id << 8) + 3);
                }
            }

            if(pIoList != NULL)
            {
                delete [] pIoList;
                pIoList = NULL;
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
        ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&g_strIoFctName, (LPARAM)iErrNum);


    HTREEITEM hRootItem = m_TreeCtrl.GetRootItem();
    if(m_TreeCtrl.ItemHasChildren(hRootItem))
    {
        m_TreeCtrl.Expand(hRootItem,TVE_EXPAND);
    }

}


BOOL CIOTree::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ImgList.Create(16, 16, ILC_COLOR32|ILC_MASK, 1, 1);
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CELL));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_AREA));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_IOOUT));

    m_TreeCtrl.SetImageList(&m_ImgList, TVSIL_NORMAL);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

CString CIOTree::StateConvStr(int iDoorState)
{
    CString  strState = "未知";
    if (PLAT_STATUS_IOOPEN == iDoorState)
    {
        strState = "打开";
    }
    else if (PLAT_STATUS_IOCLOSE == iDoorState)
    {
        strState = "关闭";
    }

    return strState;
}
void CIOTree::OnNMRClickTreeIo(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;

    return;
    /*
    int iState = -1;
    int iErrNum = 0;
    CPoint point;
    GetCursorPos(&point);
    CPoint pointInTree = point;
    m_TreeCtrl.ScreenToClient(&pointInTree);


    HTREEITEM item;
    UINT flag = TVHT_ONITEM;

    item = m_TreeCtrl.HitTest(pointInTree, &flag);

    if(item != NULL)
    {
        m_TreeCtrl.SelectItem(item);

        HTREEITEM hNode = m_TreeCtrl.GetSelectedItem();
        int iItemData = m_TreeCtrl.GetItemData(hNode);
        if (_ALARMOUT != iItemData % 256 )
            return;

        int iId = iItemData >> 8;

        CMenu menu;
        menu.CreatePopupMenu();
        menu.AppendMenu(MF_STRING,1,"获取状态");
        menu.AppendMenu(MF_STRING,2,"打开");
        menu.AppendMenu(MF_STRING,3,"关闭");
        int iCmd = menu.TrackPopupMenu(TPM_RIGHTBUTTON| TPM_RETURNCMD, point.x, point.y, this);
        
        switch( iCmd)
        {
        case 1:                     //刷新
            if (-1 == Plat_VSS_GetAlarmState(g_iLoginHandle, iId, (int)PLAT_RES_IO, &iState))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("获取状态失败");
            }
            else
            {
                CString  strState = StateConvStr(iState);
                CString  DoorName = m_TreeCtrl.GetItemText(hNode);
                int pos1 = 0, pos2 = 0;
                pos2 = DoorName.Find('(', pos1);
                if (-1 == pos2)
                {
                    DoorName = DoorName + "(" + strState+  ")";
                }
                else
                {
                    DoorName = DoorName.Mid(pos1, pos2 - pos1);
                    DoorName = DoorName + "(" + strState+  ")";
                }
                m_TreeCtrl.SetItemText(hNode, DoorName);
            }
            break;
        case 2:                    //打开
            if (-1 == Plat_VSS_AlarmControl(g_iLoginHandle, iId, (int)PLAT_VSS_CMD_IOOPEN))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("打开失败");
            }
            else
            {
                iErrNum= 0;
            }
            break;
        case 3:     //关闭         
            if (-1 == Plat_VSS_AlarmControl(g_iLoginHandle, iId, (int)PLAT_VSS_CMD_IOCLOSE))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("关闭失败");
            }
            else
            {
                iErrNum = 0;
            }
            break;
        default:
            return;
        }

        if (1 == iCmd)
        {
            g_strIoFctName = "Plat_VSS_GetAlarmState";
        }
        if (2== iCmd || 3==iCmd || 4==iCmd)
        {
            g_strIoFctName = "Plat_VSS_AlarmControl";
        }

        CWnd *pWnd = theApp.GetMainWnd();
        if (pWnd && pWnd->m_hWnd)
        {
            ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&g_strIoFctName, (LPARAM)iErrNum);
        }

    }
    */
}
