
// PlatSDK_Test.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "wtbasic.h"

// CPlatSDK_TestApp:
// See PlatSDK_Test.cpp for the implementation of this class
//

class CPlatSDK_TestApp : public CWinAppEx
{
public:
	CPlatSDK_TestApp();

// Overrides
	public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();

    bool IsSupportMultiInstance();

private:
        HANDLE m_hMutex;
        BOOL SetRunningFlag();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
	CWTBasic m_Basic;
};

extern CPlatSDK_TestApp theApp;