// AlmArea.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "TalkTree.h"

CString  CTalkTree::g_strAreaFctName = "";
// CAlmArea dialog

IMPLEMENT_DYNAMIC(CTalkTree, CDialog)

CTalkTree::CTalkTree(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkTree::IDD, pParent)
{

}

CTalkTree::~CTalkTree()
{
}

void CTalkTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_ALMAREA, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CTalkTree, CDialog)
    ON_NOTIFY(NM_RCLICK, IDC_TREE_ALMAREA, &CTalkTree::OnNMRClickTreeAlmarea)
END_MESSAGE_MAP()


// CAlmArea message handlers
HTREEITEM CTalkTree::FindTalkTreeItem(HTREEITEM item, int iData)
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
            hFound = FindTalkTreeItem(hChild, iData);
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


void CTalkTree::QueryTalkResource()
{   
    int iErrNum = 0;
    int nCellSize = HIK_MAX_SIZE_RES_CELL;
    HikCellInfo* pCellList = new (std::nothrow) HikCellInfo[nCellSize];
    if(pCellList == NULL)
    {
        return;
    }

    if (HikPt_GetResCellList(pCellList,nCellSize,HIK_WBS_OPCODE_TALKCHANNEL,HIK_RS_CELL_PARENT_ID_ALL) == HIKPT_E_OK && pCellList != NULL)
    {  
        for(int nCellIndex=0; nCellIndex<nCellSize; ++nCellIndex)
        {
            int Id = pCellList[nCellIndex].nId;
            CString Name = pCellList[nCellIndex].szCellName;
            int high = pCellList[nCellIndex].nParentId;
            HTREEITEM hParent = FindTalkTreeItem(TVI_ROOT, (high << 8) + 0);
            HTREEITEM hItem = m_TreeCtrl.InsertItem( Name, (hParent == NULL ? TVI_ROOT : hParent), 0);
            m_TreeCtrl.SetItemData(hItem, (Id << 8) + 0);

            int nTalkChanSize = HIK_MAX_SIZE_RES_TALK_CAHNEL;
            HikTalkChannel* pTalkChanList = new (std::nothrow) HikTalkChannel[nTalkChanSize];
            if(pTalkChanList == NULL)
            {
                continue;
            }

            if(HikPt_GetTalkChannelListByCellId(pTalkChanList,nTalkChanSize,pCellList[nCellIndex].nId) == HIKPT_E_OK && pTalkChanList != NULL)
            {
                for(int nIndex=0; nIndex<nTalkChanSize; ++nIndex)
                {
                    int Id = pTalkChanList[nIndex].nTalkId;
                    CString Name = pTalkChanList[nIndex].szTalkName;
                    int high = pTalkChanList[nIndex].nCellId;
                    HTREEITEM hParent = FindTalkTreeItem(TVI_ROOT, (high << 8) + 0);
                    HTREEITEM hItem = m_TreeCtrl.InsertItem(Name, 2 , 2 , (hParent == NULL ? TVI_ROOT : hParent));
                    m_TreeCtrl.SetItemData(hItem, (Id << 8) + 3);
                }
            }

            if(pTalkChanList != NULL)
            {
                delete [] pTalkChanList;
                pTalkChanList = NULL;
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
        ::PostMessage(pWnd->m_hWnd, WM_LASTERROR, (WPARAM)&g_strAreaFctName, (LPARAM)iErrNum);

    HTREEITEM hRootItem = m_TreeCtrl.GetRootItem();
    if(m_TreeCtrl.ItemHasChildren(hRootItem))
    {
        m_TreeCtrl.Expand(hRootItem,TVE_EXPAND);
    }
}

BOOL CTalkTree::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ImgList.Create(16, 16, ILC_COLOR32|ILC_MASK, 1, 1);
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CELL));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_AREA));
    m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ALMAREA));

    m_TreeCtrl.SetImageList(&m_ImgList, TVSIL_NORMAL);
    // TODO:  Add extra initialization here

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CTalkTree::OnNMRClickTreeAlmarea(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;
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
        CMenu menu;
        menu.CreatePopupMenu();
        menu.AppendMenu(MF_STRING,1,"打开对讲");        
        menu.AppendMenu(MF_STRING,2,"关闭对讲");
        int iCmd = menu.TrackPopupMenu(TPM_RIGHTBUTTON| TPM_RETURNCMD, point.x, point.y, this);

        HTREEITEM hNode = m_TreeCtrl.GetSelectedItem();
        int iItemData = m_TreeCtrl.GetItemData(hNode);
        int iId = iItemData >> 8;

        switch(iCmd)
        {
        case 1:                     
            {
                if (HikPt_StartTalk(iId) == 0)
                {
                    AfxMessageBox("开启对讲成功");
                }
                else
                {
                    AfxMessageBox("开启对讲失败");
                }
            }
            break;
        case 2:                    
            {
                if (HikPt_StopTalk(iId) == 0)
                {
                    AfxMessageBox("停止对讲成功");
                }
                else
                {
                    AfxMessageBox("停止对讲失败");
                }
            }
            break;
        default:
            break;
        }
    }
}
