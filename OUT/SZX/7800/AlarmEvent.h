#pragma once
#include "AlarmType.h"

// CAlarmEvent dialog

class CAlarmEvent : public CDialog
{
	DECLARE_DYNAMIC(CAlarmEvent)

public:
	CAlarmEvent(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlarmEvent();

// Dialog Data
	enum { IDD = IDD_DLG_ALARMEVENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()    

public:
    CListCtrl m_ListCtrl;
    AlarmType m_AlmType;
    int m_Index;
    virtual BOOL OnInitDialog();
};
