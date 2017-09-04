#pragma once
#include "ACDoorTree.h"
#include "ACDevice.h"
#include "TabSheet.h"
#include "PersonDlg.h"
#include "DlgCardList.h"


// ACSSubsysDlg dialog

class ACSSubsysDlg : public CDialog
{
	DECLARE_DYNAMIC(ACSSubsysDlg)

public:
	ACSSubsysDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ACSSubsysDlg();

// Dialog Data
	enum { IDD = IDD_DLG_ACS_SUBSYS };

protected:
    void InitControlsPara();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CTabSheet m_TabTree;
    CACDoorTree  m_DoorTreeDlg;
    CACDevice  m_ACDevDlg;

    CTabSheet m_TabList;
    CPersonDlg  m_PersonDlg;
    CDlgCardList  m_CardDlg;
    virtual BOOL OnInitDialog();

};
