
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")


#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <map>
#include <afxdisp.h>        // MFC Automation classes


//QueryResource类型定义
#define _CONTROLUNIT    0x00    // 控制中心
#define _REGION         0x01    // 区域
#define _DEVICE         0x02    // 编码器
#define _CAMERA         0x03    // 摄像头
#define _ALARMIN        0x04    // 报警输入
#define _ALARMOUT       0x05    // 报警输出
#define _RECORDFILE     0x06    // 录像文件
#define  _ACDEVICE     0x07   //门禁主机
#define  _ACDOOR     0x08   //门禁点
#define  _ALMHOST     0x09   //报警主机
#define  _ALMAREA     0x0A   //防区


#define PREVIEW_T			0				///< 预览项
#define PLAY_BACK_T			1				///< 回放项


#define OUTPUT_INTERVAL		2				///< 窗体间缝隙宽度
#define MAX_OUTPUTS			300				///< 最大窗体数
#define MAX_PLAYBACKWND		4				///< 最大回放窗体数
#define BOULDER             0              ///<边框大小


#define WM_LASTERROR			WM_USER + 100
#define WM_DRAWBORDER           WM_USER + 101
#define WM_FOCUS                WM_USER + 102
#define WM_STARTPLAY		    WM_USER + 103
#define WM_STOPPLAY			    WM_USER + 104
#define WM_STOPPLAYBACK		    WM_USER + 105
#define WM_SELECTPLAYBACKCID	WM_USER + 106
#define WM_CAPPIC               WM_USER + 107
#define WM_STARTRECORD          WM_USER + 108
#define WM_STOPRECORD           WM_USER + 109

#define WM_PTZ				    WM_USER + 110
#define WM_STARTCRUISE          WM_USER + 111
#define WM_STOPCRUISE           WM_USER + 112
#define WM_PTZ_LOCK             WM_USER + 113
#define WM_PTZ_UNLOCK           WM_USER + 114
#define WM_CHGSTREAM            WM_USER + 115
#define WM_STARTTVWALL          WM_USER + 116
#define WM_STOPTVWALL           WM_USER + 117

#include "HikPlatformSDK.h"
#include "stringoperdef.h"
#include "CrashAPI.h"
#include "include/HPR/HPR_Hpr.h"
#include "include/HPR/HPR_Utils.h"
#include "include/hpr/HPR_Guard.h"
#include "math.h"
#include "PlatSDK_TestLog.h "
#include <hlog/logger.h>
#include <language/MultiLanDefine.h>


#pragma comment(lib,"lib/HikPlatformSDK.lib")
#pragma comment(lib,"lib/CrashAPI.lib")
#pragma comment(lib,"lib/hlog.lib")
#pragma comment(lib,"lib/hpr.lib")

using namespace std;

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxwin.h>

//#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#define CWinAppEx CWinApp










#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


