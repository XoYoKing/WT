// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "PlatSDK_Test.h"
#include "DlgLogin.h"

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

    int GetIniFileInt(const char* szAppName,const char* szKeyName,int nDef,const char* szFileName = "DefCfg.ini")
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
}

// CDlgLogin dialog

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
    ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT_PORT, &CDlgLogin::OnEnChangeEditPort)
END_MESSAGE_MAP()


// CDlgLogin message handlers

BOOL CDlgLogin::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    GetDlgItem(IDC_IPADDRESS1)->SetWindowText(_T("10.33.27.217")); /*测试平台:(1)10.33.25.174  (2)172.10.27.121 (3)10.22.35.22*/
    GetDlgItem(IDC_EDIT_PORT)->SetWindowText(_T("443"));
    GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(_T("admin"));
    
    int nCodeVersion = GetIniFileInt("APP","CodeVersion",625);
    if(nCodeVersion <= 624)
    {
        GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T("Abc123"));    
    }
    else if(nCodeVersion > 624)
    {
        GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T("Abc123++"));
    }

	/*测试平台:(1)10.33.25.174  (2)172.10.27.121 (3)10.22.35.22*/
    GetDlgItem(IDC_IPADDRESS1)->SetWindowText(_T("110.80.12.205")); 
    GetDlgItem(IDC_EDIT_PORT)->SetWindowText(_T("8089"));
    GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(_T("admin"));
    GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T("Admin123"));

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CString strTemp;
    GetDlgItem(IDC_IPADDRESS1)->GetWindowText(strcmsIP);
       
    GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strTemp);
    cmsPort = atoi(strTemp.GetBuffer(0));

    GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(m_username);
    GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(m_password);
    OnOK();
}

void CDlgLogin::OnEnChangeEditPort()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
