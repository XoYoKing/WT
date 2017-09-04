
// PlatSDK_Test.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "PlatSDK_TestDlg.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_iLoginHandle;

namespace
{
    /**@fn         <GetAppPath>
    *@brief        <获取当前模块所在的目录>
    *@return      return  char*
    */
    const char* GetAppPath()
    {
        static char Apppath[1024] = {0};
        if(Apppath[0] == 0)
        {
            HMODULE hModule = NULL;
            if( ::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,(const char*)GetAppPath,&hModule) )//lint !e611
            {
                ::GetModuleFileNameA(hModule,Apppath,sizeof(Apppath) - 1);
                int len = static_cast<int>(strlen(Apppath));
                for (int i = len - 1;i >= 0;--i)
                {
                    if(Apppath[i] == '\\')
                    {
                        Apppath[i + 1] = 0;
                        break;
                    }
                }
            }
        }
        return Apppath;
    }

    int GetIniFileInt(const char* szAppName,const char* szKeyName,int nDef,const char* szFileName)
    {
        std::string szPath;
        if(szFileName != NULL && szAppName != NULL && szKeyName != NULL)
        {
            szPath.append(GetAppPath());
            szPath.append(szFileName);
        }
        else
        {
            return nDef;
        }
        return ::GetPrivateProfileInt(szAppName,szKeyName,nDef,szPath.c_str());
    }

    void SeparateString(const char* pStr,std::vector<std::string>& vecResult,char chKey)
    {
        if(pStr == NULL || pStr[0] == 0)
        {
            return ;
        }

        std::string tmp = pStr;
        if( tmp.at(tmp.length() - 1) != chKey )
        {
            tmp += chKey;
        }
        size_t beginIndex = 0;
        static const size_t npos = size_t(-1);
        size_t indexCh1a = tmp.find(chKey,beginIndex);

        std::string tmpBuf;

        while(indexCh1a != npos)
        {
            int len = static_cast<int>(indexCh1a - beginIndex);
            if(len > 0)
            {
                tmpBuf.clear();
                tmpBuf.append(tmp.c_str() + beginIndex,static_cast<size_t>(len));
                vecResult.push_back(tmpBuf);
            }
            beginIndex = ++indexCh1a;
            indexCh1a = tmp.find(chKey,beginIndex);
        }
    }
}

// CPlatSDK_TestApp

BEGIN_MESSAGE_MAP(CPlatSDK_TestApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPlatSDK_TestApp construction

CPlatSDK_TestApp::CPlatSDK_TestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPlatSDK_TestApp object

CPlatSDK_TestApp theApp;


// CPlatSDK_TestApp initialization

BOOL CPlatSDK_TestApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    if ( !m_Basic.init() )
	{
		return FALSE;
	}

    if (FALSE == IsSupportMultiInstance())
    {
        return FALSE;
    }

    int nRetVal = -1;
    nRetVal = HikPt_Init();
    //CDlgLogin dlgLogin;
    int iRet = -1;

    //AfxMessageBox("hello");
    //std::vector<std::string> vec;
    //LPSTR szCmdLine = GetCommandLine();
    //SeparateString(szCmdLine, vec, ' ');
    //if (vec.size() == 5)
    //{
    //    dlgLogin.strcmsIP = vec[1].c_str();
    //    dlgLogin.cmsPort = atoi(vec[2].c_str());
    //    dlgLogin.m_username = vec[3].c_str();
    //    dlgLogin.m_password = vec[4].c_str();
    //}
    CString strcmsIP=_T("110.80.12.205");
    int cmsPort=443;
    CString m_username=_T("admin");
    CString m_password=_T("Admin12345");


    // 1 表示用于性能测试工具  0表示用于平台SDK Demo
    if (GetIniFileInt("APP", "IsSupportMultiInstance", 0, "PlatSdkCfg.ini") == 0 )
    {
        do 
        {
            //if (IDOK == dlgLogin.DoModal())
            //{
                HikLoginInfo _loginInfo = {0};
                //strncpy_s(_loginInfo.szServerUrl, _countof(_loginInfo.szServerUrl), dlgLogin.strcmsIP.GetBuffer(0), _TRUNCATE);
                //_loginInfo.uServerPort = dlgLogin.cmsPort;
                //strncpy_s(_loginInfo.szUserName, _countof(_loginInfo.szUserName), dlgLogin.m_username.GetBuffer(0), _TRUNCATE);
                //strncpy_s(_loginInfo.szPassword, _countof(_loginInfo.szPassword), dlgLogin.m_password.GetBuffer(0), _TRUNCATE);
                strncpy_s(_loginInfo.szServerUrl, _countof(_loginInfo.szServerUrl), strcmsIP.GetBuffer(0), _TRUNCATE);
                _loginInfo.uServerPort = cmsPort;
                strncpy_s(_loginInfo.szUserName, _countof(_loginInfo.szUserName), m_username.GetBuffer(0), _TRUNCATE);
                strncpy_s(_loginInfo.szPassword, _countof(_loginInfo.szPassword), m_password.GetBuffer(0), _TRUNCATE);
                iRet = HikPt_Login(&_loginInfo);
                if (iRet != 0)
                {   
                    CString szInfo;
                    szInfo.Format("用户登录失败,错误码：%d,错误详情：%s",_loginInfo.nErrCode,_loginInfo.szErrInfo);
                    AfxMessageBox(szInfo);
                }
            //}
            //else
            //{
            //    HikPt_Uninit();
            //    return FALSE;
            //}

        } while (iRet != 0);

        CPlatSDK_TestDlg dlg;
        m_pMainWnd = &dlg;
        INT_PTR nResponse = dlg.DoModal();
        if (nResponse == IDOK)
        {
            // TODO: Place code here to handle when the dialog is
            //  dismissed with OK
        }
        else if (nResponse == IDCANCEL)
        {
            // TODO: Place code here to handle when the dialog is
            //  dismissed with Cancel
        }
    }
    else
    {
        HikLoginInfo _loginInfo = {0};
        //strncpy_s(_loginInfo.szServerUrl, _countof(_loginInfo.szServerUrl), dlgLogin.strcmsIP.GetBuffer(0), _TRUNCATE);
        //_loginInfo.uServerPort = dlgLogin.cmsPort;
        //strncpy_s(_loginInfo.szUserName, _countof(_loginInfo.szUserName), dlgLogin.m_username.GetBuffer(0), _TRUNCATE);
        //strncpy_s(_loginInfo.szPassword, _countof(_loginInfo.szPassword), dlgLogin.m_password.GetBuffer(0), _TRUNCATE);
        strncpy_s(_loginInfo.szServerUrl, _countof(_loginInfo.szServerUrl), strcmsIP.GetBuffer(0), _TRUNCATE);
        _loginInfo.uServerPort = cmsPort;
        strncpy_s(_loginInfo.szUserName, _countof(_loginInfo.szUserName), m_username.GetBuffer(0), _TRUNCATE);
        strncpy_s(_loginInfo.szPassword, _countof(_loginInfo.szPassword), m_password.GetBuffer(0), _TRUNCATE);
        time_t nBegTime = time(NULL);
        iRet = HikPt_Login(&_loginInfo);
        if (iRet != 0)
        {
            CLIENT_ERROR("用户[%s] 登录平台[%s:%d]失败,错误码：%d,错误详情：%s", _loginInfo.szUserName, _loginInfo.szServerUrl, _loginInfo.uServerPort, _loginInfo.nErrCode,_loginInfo.szErrInfo);
            HikPt_Uninit();
            return FALSE;
        }
        
        time_t nSpan = time(NULL) - nBegTime;
        CLIENT_INFO("用户[%s] 登录平台[%s:%d] 成功, 耗时[%d]秒", _loginInfo.szUserName, _loginInfo.szServerUrl, _loginInfo.uServerPort, nSpan);
    }

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

bool CPlatSDK_TestApp::IsSupportMultiInstance()
{
    //通过配置文件PlatSdkCfg.ini检查是否支持多实例运行APP  1表示支持多实例运行APP
    if (GetIniFileInt("APP", "IsSupportMultiInstance", 0, "PlatSdkCfg.ini") == 0)
    {
        if (FALSE == SetRunningFlag())
        {
            return false;
        }
    }
    else
    {
        // TODO
    }

    return true;
}

int CPlatSDK_TestApp::ExitInstance()
{
    //HikPt_Uninit();

    return CWinAppEx::ExitInstance();
}

BOOL CPlatSDK_TestApp::SetRunningFlag()
{
    m_hMutex = CreateMutex(NULL, FALSE, "Global\\PlatSDK_Test");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        //AfxMessageBox("PlatSDK_Test已经运行!");
        return FALSE;
    }
    return TRUE;
}