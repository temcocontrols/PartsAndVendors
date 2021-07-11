
// T3000.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "T3000.h"
#include "MainFrm.h"
 
#include "T3000Doc.h"
#include "T3000View.h"




#include "iniFile.h"
#include "afxinet.h"

#include "bado/BADO.h"


const int g_versionNO=20150605;
//CString const CurrentT3000Version=_T("2014.12.24");
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "global_variable.h"
ULONG_PTR g_gdiplusToken;
BEGIN_MESSAGE_MAP(CT3000App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CT3000App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE_CONFIG, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_VERSIONHISTORY,OnVersionInfo)
END_MESSAGE_MAP()	
// CT3000App construction 
CT3000App::CT3000App()
{
//	try
///	{
		m_bHiColorIcons = TRUE;
		CurrentT3000Version=_T(" 2015.07.28");

//		m_pvmainwindowdlg = NULL;
//	}
// 	catch (...)
// 	{
// 		
// 		AfxMessageBox(_T("1111"));
// 	}
m_lastinterface=19;
}
// The one and only CT3000App object
CT3000App theApp;
 
BOOL CT3000App::user_login()
{
	BOOL bRet=FALSE;
	 
	if(g_buser_log_in==false)
		return false;
	return true;
}
// CT3000App initialization
BOOL CT3000App::RegisterOcx(LPCTSTR   OcxFileName)
{
	LPCTSTR   pszDllName   =   OcxFileName   ;     //ActiveX控件的路径及文件名       
	HINSTANCE   hLib   =   LoadLibrary(pszDllName);   //装载ActiveX控件   
	if   (hLib   <   (HINSTANCE)HINSTANCE_ERROR)   
	{   
		return   FALSE;   
	}   
	FARPROC   lpDllEntryPoint;     
	lpDllEntryPoint   =   GetProcAddress(hLib,(LPCSTR)(_T("DllRegisterServer")));   //获取注册函数DllRegisterServer地址   
	if(lpDllEntryPoint!=NULL)       //调用注册函数DllRegisterServer   
	{   
		if(FAILED((*lpDllEntryPoint)()))   
		{//   AfxMessageBox(_T("false"));
			FreeLibrary(hLib);   
			return   FALSE;   
			
		}   
		return   TRUE;   
	}   
	else   
	{
	//	AfxMessageBox(_T("false"));
			return   FALSE;


	}
	
}
 


BOOL CT3000App::InitInstance()
{
	//TODO: call AfxInitRichEdit2() to initialize richedit2 library.

	if(!AfxInitRichEdit())
	{
		AfxMessageBox(IDS_INIT_RICHEDIT_ERROR);//
		return FALSE;//
	}
	//AfxInitRichEdit2();
	if(!AfxInitRichEdit2())
	{
		AfxMessageBox(IDS_INIT_RICHEDIT_ERROR);//
		return FALSE;//
	}


 	CPVMainScreenDlg dlg;
 	dlg.DoModal();
 
	 
 return 0;

		 

 


	 



		CWinAppEx::InitInstance();
	 


		if(!AfxInitRichEdit())
		{
			AfxMessageBox(IDS_INIT_RICHEDIT_ERROR);//
			return FALSE;//
		}
		//AfxInitRichEdit2();
		if(!AfxInitRichEdit2())
		{
			AfxMessageBox(IDS_INIT_RICHEDIT_ERROR);//
			return FALSE;//
		}
		if (!AfxSocketInit())//
		{
			AfxMessageBox(IDP_SOCKETS_INIT_FAILED);//
			return FALSE;//
		}
	 
		AfxEnableControlContainer();
		//CString T3000_Rev;
		//	T3000_Rev=getURLContext(_T("www.temcocontrols.com/ftp/software/T3000_Version.txt"));
		SetRegistryKey(_T("Temco T3000 Application"));//
		LoadStdProfileSettings();  // Load standard INI file options (including MRU)//
		InitContextMenuManager();
		InitKeyboardManager();

		InitTooltipManager();
		CMFCToolTipInfo ttParams;
		ttParams.m_bVislManagerTheme = TRUE;
		theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
			RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams); 
		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(
			IDR_MAINFRAME,
			RUNTIME_CLASS(CT3000Doc),
			RUNTIME_CLASS(CMainFrame),       // main SDI frame window
			RUNTIME_CLASS(CT3000View));


		if (!pDocTemplate)
			return FALSE;

		AddDocTemplate(pDocTemplate);
		// Parse command line for standard shell commands, DDE, file open
		CCommandLineInfo cmdInfo;	
		ParseCommandLine(cmdInfo);

		//cmdInfo.m_nShellCommand   =   CCommandLineInfo::FileNothing; //lsc


		// Dispatch commands specified on the command line.  Will return FALSE if
		// app was launched with /RegServer, /Register, /Unregserver or /Unregister.

		if (!ProcessShellCommand(cmdInfo))
			return FALSE;


		CString strTile;
		strTile.Format(_T("T3000 Building Automation System"));
		strTile+=CurrentT3000Version;
		m_pMainWnd->SetWindowText(strTile);//
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();

	 
		 
	return TRUE;
}

 
// CAboutDlg dialog used for App About




class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// App command to run the dialog
void CT3000App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CT3000App customization load/save methods

void CT3000App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CT3000App::LoadCustomState()
{
}

void CT3000App::SaveCustomState()
{
}

void CAboutDlg::OnBnClickedButton1()
{
	
	CString m_strWebLinker;
	m_strWebLinker.Format(_T("mailto:alex@temcocontrols.com?subject=feedback to temco &body=please add the attachment in the \n%sT3000.log "),g_strExePth);
	try{
          ShellExecute(GetSafeHwnd(), NULL,m_strWebLinker,   NULL, NULL,   SW_SHOWNORMAL);
	}
	catch(...)
	{
		AfxMessageBox(_T("Error:Can't find the email client in your pc!"));
	}
	
}
int CT3000App::ExitInstance()
{
	 
 
	return CWinAppEx::ExitInstance();
}

void CT3000App::OnVersionInfo()
{
	CString strHistotyFile=g_strExePth+_T("history.txt");
	ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
}

BOOL CT3000App::haveRegister()
{
	if (m_maxClients == 0)
		return FALSE;
	else 
		return TRUE;
}

CString CT3000App::GetModulePath()
{
	wchar_t path[MAX_PATH];
	GetModuleFileName(NULL,path,MAX_PATH);
	return CString(path);
}

int CT3000App::GetSoftInstallDays()
{
	CFileStatus fileStatus;
	CTime curTime;
	CString strPath;
	CTimeSpan timeSpan;

	curTime=CTime::GetCurrentTime();
	strPath=GetModulePath();

	strPath=strPath.Left(strPath.ReverseFind(_T('\\'))+1);
	strPath+=_T("T3000_Rev2.5.0.99.exe");

//	strPath+=_T("T3000.exe");
	CFile::GetStatus(strPath,fileStatus);

	//timeSpan=curTime-fileStatus.m_ctime;
	timeSpan=curTime-fileStatus.m_mtime;//这个是修改时间，不论你CUT，COPY都不会修改的

	return (int)timeSpan.GetDays();
}

void CT3000App::WriteNumber( CRegKey& key,CStringW valueName,DWORD value )
{
	key.SetDWORDValue(valueName,value);
}

BOOL CT3000App::ReadNameber( CRegKey& key,CStringW valueName,DWORD& value )
{
	DWORD s;
	if (key.QueryDWORDValue(valueName,s) == ERROR_SUCCESS)
	{
		value = s;
		return TRUE;
	}else
	{
		return FALSE;
	}
}

void CT3000App::Judgestore()
{
	HKEY hKEY;
	LPCTSTR data_Set = _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\");//_T("Software\\Microsoft\\");//
	long ret0 = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set,0,KEY_READ,&hKEY);
	if (ret0!=ERROR_SUCCESS)
	{
		return;
	}

	LPBYTE  owner_Get = new BYTE[80];
	DWORD type_1 = REG_SZ;
	DWORD cbData_1 = 80;

	long ret1 = ::RegQueryValueEx(hKEY,_T("maxClients"),NULL,&type_1,owner_Get,&cbData_1);
	if (ret1!=ERROR_SUCCESS)
	{
		CRegKey key;
		key.Create(HKEY_LOCAL_MACHINE,data_Set);
		WriteNumber(key,_T("maxClients"),4315);

	}
	long ret2 = ::RegQueryValueEx(hKEY,_T("Regvalue"),NULL,&type_1,owner_Get,&cbData_1);
	if (ret2!=ERROR_SUCCESS)
	{
		CRegKey key;
		key.Create(HKEY_LOCAL_MACHINE,data_Set);
		WriteNumber(key,_T("Regvalue"),100);
	}
	delete[] owner_Get;
	::RegCloseKey(hKEY);
}

void CT3000App::ReadREG()
{
	CRegKey key;
	LPCTSTR data_Set = _T("Software\\Microsoft\\Windows NT\\CurrentVersion");//_T("Software\\Microsoft\\");//
	key.Open(HKEY_LOCAL_MACHINE,data_Set);
	ReadNameber(key,_T("maxClients"),m_maxClients);
	ReadNameber(key,_T("Regvalue"),password);
	if (password != 100)
	{
		WriteNumber(key,_T("Regvalue"),100);
		password =100;
	}
	if (m_maxClients !=4315&&m_maxClients!=0)
	{
		WriteNumber(key,_T("maxClients"),4315);
		m_maxClients = 15;

	}else if (m_maxClients == 0)
	{
		m_maxClients = 0;
	}else 
	{
		m_maxClients = m_maxClients - 4300;
		if (m_maxClients>password)
		{
			m_maxClients = 0;
		}
	}
}

 

 

void CAboutDlg::OnBnClickedOk()
{
// TODO: Add your control notification handler code here
CDialog::OnOK();
}
