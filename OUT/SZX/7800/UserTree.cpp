// AlmHost.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "UserTree.h"

CString  CUserTree::g_strAHFctName = "";
// CAlmHost dialog

IMPLEMENT_DYNAMIC(CUserTree, CDialog)

CUserTree::CUserTree(CWnd* pParent /*=NULL*/)
	: CDialog(CUserTree::IDD, pParent)
{

}

CUserTree::~CUserTree()
{
}

void CUserTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_ALMHOST, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CUserTree, CDialog)
    ON_NOTIFY(NM_RCLICK, IDC_TREE_ALMHOST, &CUserTree::OnNMRClickTreeAlmhost)
END_MESSAGE_MAP()


// CAlmHost message handlers
HTREEITEM CUserTree::FindUserTreeItem(HTREEITEM item, int iData)
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
            hFound = FindUserTreeItem(hChild, iData);
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


void CUserTree::QueryUserResource()
{
    CWnd *pWnd = theApp.GetMainWnd();

    int iErrNum = 0;
    int nCellSize = HIK_MAX_SIZE_RES_CELL;
    HikUserOrg* pUserCellList = new (std::nothrow) HikUserOrg[nCellSize];
    if(pUserCellList == NULL)
    {
        return;
    }

    if (HikPt_GetUserCellList(pUserCellList,nCellSize,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK && pUserCellList != NULL)
    {  
        for(int nCellIndex=0; nCellIndex<nCellSize; ++nCellIndex)
        {
            int Id = pUserCellList[nCellIndex].nID;
            CString Name = pUserCellList[nCellIndex].szOrgName;
            int high = pUserCellList[nCellIndex].nParentID;
            HTREEITEM hParent = FindUserTreeItem(TVI_ROOT, (high << 8) + 0);
            HTREEITEM hItem = m_TreeCtrl.InsertItem( Name, (hParent == NULL ? TVI_ROOT : hParent), 0);
            m_TreeCtrl.SetItemData(hItem, (Id << 8) + 0);

            int nUserSize = HIK_MAX_SIZE_RES_USER;
            HikPlatformUser* pUserList = new (std::nothrow) HikPlatformUser[nUserSize];
            if(pUserList == NULL)
            {
                continue;
            }

            if(HikPt_GetUserListByCellId(pUserList,nUserSize,pUserCellList[nCellIndex].nID) == HIKPT_E_OK && pUserList != NULL)
            {
                for(int nIndex=0; nIndex<nUserSize; ++nIndex)
                {
                    int Id = pUserList[nIndex].nId;
                    CString Name = pUserList[nIndex].szName;
                    int high = pUserList[nIndex].nCellID;
                    HTREEITEM hParent = FindUserTreeItem(TVI_ROOT, (high << 8) + 0);
                    HTREEITEM hItem = m_TreeCtrl.InsertItem(Name, 1 , 1 , (hParent == NULL ? TVI_ROOT : hParent));
                    m_TreeCtrl.SetItemData(hItem, (Id << 8) + 3);
                }
            }

            if(pUserList != NULL)
            {
                delete [] pUserList;
                pUserList = NULL;
            }
        }
    }
    else
    {
        iErrNum = HikPt_GetLastError();
    }

    if(pUserCellList != NULL)
    {
        delete [] pUserCellList;
        pUserCellList = NULL;
    }

    if(0 != iErrNum && pWnd && pWnd->m_hWnd)
        ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&g_strAHFctName, (LPARAM)iErrNum);


    HTREEITEM hRootItem = m_TreeCtrl.GetRootItem();
    if(m_TreeCtrl.ItemHasChildren(hRootItem))
    {
        m_TreeCtrl.Expand(hRootItem,TVE_EXPAND);
    }
}

CString  CUserTree::StateConvStr(int iDoorState)
{
    CString  strState = "Î´Öª";
    if (PLAT_STATUS_DEFENCE == iDoorState)
    {
        strState = "²¼·À";
    }
    else if (PLAT_STATUS_DISDEFENCE == iDoorState)
    {
        strState = "³··À";
    }

    return strState;
}

BOOL CUserTree::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ImgList.Create(16, 16, ILC_COLOR32|ILC_MASK, 1, 1);
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CELL));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ALMHOST));

    m_TreeCtrl.SetImageList(&m_ImgList, TVSIL_NORMAL);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserTree::OnNMRClickTreeAlmhost(NMHDR *pNMHDR, LRESULT *pResult)
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
        if (_ALMHOST != iItemData % 256 )
            return;

        int iId = iItemData >> 8;

        CMenu menu;
        menu.CreatePopupMenu();
        menu.AppendMenu(MF_STRING,1,"»ñÈ¡×´Ì¬");
        menu.AppendMenu(MF_STRING,2,"²¼·À");
        menu.AppendMenu(MF_STRING,3,"³··À");
        int iCmd = menu.TrackPopupMenu(TPM_RIGHTBUTTON| TPM_RETURNCMD, point.x, point.y, this);

        switch( iCmd)
        {
        case 1:                     //Ë¢ÐÂ
            if (-1 == Plat_VSS_GetAlarmState(g_iLoginHandle, iId, (int)PLAT_DEVICE_ALARM_HOST, &iState))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("»ñÈ¡×´Ì¬Ê§°Ü");
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
        case 2:                    //²¼·À
            if (-1 == Plat_VSS_AlarmControl(g_iLoginHandle, iId, (int)PLAT_VSS_CMD_ALMHOST_DEFENCE))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("²¼·ÀÊ§°Ü");
            }
            else
            {
                iErrNum= 0;
            }
            break;
        case 3:     //³··À       
            if (-1 == Plat_VSS_AlarmControl(g_iLoginHandle, iId, (int)PLAT_VSS_CMD_ALMHOST_DISDEFENCE))
            {
                iErrNum = Plat_GetLastError();
                AfxMessageBox("³··ÀÊ§°Ü");
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
            g_strAHFctName = "Plat_VSS_GetAlarmState";
        }
        if (2== iCmd || 3==iCmd || 4==iCmd)
        {
            g_strAHFctName = "Plat_VSS_AlarmControl";
        }

        CWnd *pWnd = theApp.GetMainWnd();
        if (pWnd && pWnd->m_hWnd)
        {
            ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&g_strAHFctName, (LPARAM)iErrNum);
        }

    }
    */
}
