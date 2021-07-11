 
 

#include "stdafx.h"
#include "T3000.h"
 
#include "MainFrm.h"
#include "T3000Doc.h"

#include "T3000view.h"
 

#include "global_variable_extern.h"
#include "globle_function.h"
 
















#include "excel9.h"






#include "gloab_define.h"
 


#include "PVDlg.h"

#include "bado/BADO.h"

 #include "PVMainScreenDlg.h"
bool b_create_status = false;
const TCHAR c_strCfgFileName[] = _T("config.txt");				
 
extern tree_product	m_product_isp_auto_flash;
#pragma region Fance Test
//For Test
// 在没有鼠标和键盘消息的时候 就启用自动刷新 treeview,如果有就 不要刷新，因为如果正在刷新，客户肯能就无法第一时间读到自己想要的数据;

bool start_record_time = true;	//开启计时，如果用户一段时间无键盘和鼠标左键操作就开启自动刷新;
unsigned long time_click = 0;
 
bool enable_show_debug_window = false; 
 
HANDLE hwait_write_thread = NULL;
 
HANDLE hStartEvent; // thread start event
extern int isp_product_id;
vector <MSG> My_Receive_msg;
#define WM_CREATE_STATUSBAR WM_USER + 638
#define  WM_REFRESH_TREEVIEW_MAP WM_USER + 2008
HANDLE hDeal_thread;
DWORD nThreadID_Do;
 
extern bool m_is_remote_device ;
  
 

CCriticalSection MyCriticalSection;

bool b_pause_refresh_tree = false;
char local_network_ip[255];
CString local_enthernet_ip;
int m_MainHotKeyID[14] = 
{
	3001,
	3002,
	3003,
	3004,
	3005,
	3006,
	3007,
	3008,
	3009,
	3010,
	3011,
	3012,
	3013
};

//End for Test
void CALLBACK Listen(SOCKET s, int ServerPort, const char *ClientIP);
#pragma endregion 
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

// #define _CRTDBG_MAP_ALLOC
// #include "stdlib.h"
// #include "crtdbg.h"
 

 
#pragma comment(lib, "Version.lib")

// #include "productDB/ProInterface.h"
// #pragma comment(lib,"productDB/ProductDBdll.lib")


#ifdef _DEBUG
#define new DEBUG_NEW


#endif
// CMainFrame
#define REFRESH_TIMER	1
#define REFRESH_TIMER_VALUE	 35000
#define ID_NODEFAULTMAINBUILDING_MSG 8000
#define SCAN_TIMER 2
#define MONITOR_MOUSE_KEYBOARD_TIMER 3
#define SAVE_PRODYCT_STATUS  4

#define MESSAGE_INFORMATION_DEAL 5

const UINT WM_HTTPDOWNLOAD_THREAD_FINISHED = WM_APP + 100;
CEvent g_killMultiReadEvent;

volatile HANDLE Read_Mutex=NULL;
 
//BOOL g_bPauseMultiRead=FALSE;
BOOL m_active_key_mouse = FALSE;
//tree0412
#if 0//原有
#define TVINSERV_BUILDING 		{tvInsert.item.iImage=0;tvInsert.item.iSelectedImage=0;}
#define TVINSERV_FLOOR	 			{tvInsert.item.iImage=0;tvInsert.item.iSelectedImage=0;}
#define TVINSERV_ROOM				{tvInsert.item.iImage=1;tvInsert.item.iSelectedImage=1;}
#define TVINSERV_TSTAT 			{tvInsert.item.iImage=2;tvInsert.item.iSelectedImage=2;}
#define TVINSERV_LED 				{tvInsert.item.iImage=3;tvInsert.item.iSelectedImage=3;}
#define TVINSERV_NET_WORK		{tvInsert.item.iImage=5;tvInsert.item.iSelectedImage=5;}
#define TVINSERV_SOLAR				{tvInsert.item.iImage=5;tvInsert.item.iSelectedImage=5;}
#define TVINSERV_CMFIVE			{tvInsert.item.iImage=4;tvInsert.item.iSelectedImage=4;} //CM5
#define TVINSERV_MINIPANEL		{tvInsert.item.iImage=7;tvInsert.item.iSelectedImage=7;} //MiniPanel
#endif

//tree0412
#if 1
#define TVINSERV_BUILDING 		    {tvInsert.item.iImage=0; tvInsert.item.iSelectedImage=0;}
#define TVINSERV_FLOOR	 			{tvInsert.item.iImage=0; tvInsert.item.iSelectedImage=0;}
#define TVINSERV_ROOM				{tvInsert.item.iImage=2; tvInsert.item.iSelectedImage=2;}
#define TVINSERV_TSTAT 			    {tvInsert.item.iImage=6; tvInsert.item.iSelectedImage=6;}
#define TVINSERV_LED 				{tvInsert.item.iImage=8; tvInsert.item.iSelectedImage=8;}//TSTAT6&7
#define TVINSERV_NET_WORK		    {tvInsert.item.iImage=12;tvInsert.item.iSelectedImage=12;}
#define TVINSERV_SOLAR				{tvInsert.item.iImage=12;tvInsert.item.iSelectedImage=12;}
#define TVINSERV_CMFIVE			    {tvInsert.item.iImage=10;tvInsert.item.iSelectedImage=10;} //CM5
#define TVINSERV_MINIPANEL		    {tvInsert.item.iImage=14;tvInsert.item.iSelectedImage=14;} //MiniPanel
#define TVINSERV_LC				    {tvInsert.item.iImage=16;tvInsert.item.iSelectedImage=16;} //Lightingcontroller
#define TVINSERV_TSTAT6			    {tvInsert.item.iImage=18;tvInsert.item.iSelectedImage=18;}//tstat6
#define TVINSERV_CO2			    {tvInsert.item.iImage=20;tvInsert.item.iSelectedImage=20;}//CO2
#define TVINSERV_CS3000             {tvInsert.item.iImage=22;tvInsert.item.iSelectedImage=22;}//cs3000
#endif

#define ITEM_MASK				TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
 
 
 
	ON_WM_CREATE()
 
 
	ON_WM_TIMER()
	ON_WM_DESTROY()
 
	ON_WM_SIZING()
	ON_WM_PAINT()
 
 
    
	ON_WM_COPYDATA()
	 
  ON_WM_MOVE()
  ON_COMMAND(ID_PVTEST_PV, &CMainFrame::OnPvtestPv)  //ID_PVTEST_PV
  ON_COMMAND(ID_PVTEST_PV1, &CMainFrame::OnPvtestPv1)
  END_MESSAGE_MAP()

static UINT indicators[] =
{
	//ID_SEPARATOR,           // status line indicator
	ID_RW_INFO,
	ID_BUILDING_INFO,
	ID_PROTOCOL_INFO,
	IDS_SHOW_RESULTS,

};

unsigned short tempchange[512];
int index_Count=0;
 
 
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
   
 
    m_pvmainwindowdlg = NULL;
 
}


CMainFrame::~CMainFrame()
{
 
	 

    if (m_pvmainwindowdlg != NULL)
    {
        delete m_pvmainwindowdlg;
        m_pvmainwindowdlg = NULL;
    }


}
 
void getLocalIp(void)
{
	WSADATA wsaData;
	char name[155];
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
	{
		if(gethostname(name,sizeof(name)) == 0)
		{
			struct hostent* phe = gethostbyname(name);
			if (0 == phe)
			{
				return;
			}
			for (int i = 0; phe->h_addr_list[i] != 0; ++i)
			{
				struct in_addr addr;
				memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
				TRACE("IP %d:%s\n",i+1,inet_ntoa(addr));
			}
		} 
		WSACleanup( );
	}
}

    
 
//CMyStatusbarCtrl * statusbar = NULL;
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	 
	OnApplicationLook(theApp.m_nAppLook);
 	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
 	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	 



	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	CMFCToolBar::SetSizes(CSize(32,32),CSize(32,32));
	CMFCToolBar::SetMenuSizes(CSize(32,32),CSize(24,24));

	UINT uiToolbarHotID;
	UINT uiToolbarColdID;
	UINT uiMenuID;
 

	uiToolbarHotID =  IDB_BITMAP7 ;
	uiToolbarColdID = IDB_BITMAP7 ;
	uiMenuID =	IDB_BITMAP_BACNET_MENU_BIT ;// 



	 


	///////////////////////////////////////////////////////////////////////////////////

	 
	BOOL bNameValid;

	//////////////////////////////////////////////////////////////////////////////////
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	//m_wndToolBar.SetWindowText(strToolBarName);

	
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);


	if (!m_wndStatusBar.Create(this)||!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
 	
	
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	 

	
	EnableDocking(CBRS_ALIGN_ANY);	
	
	DockPane(&m_wndMenuBar);
 
	
	 
 
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	
	m_wndStatusBar.SetPaneInfo(0,ID_RW_INFO,SBPS_NOBORDERS,   300);
   // int index = m_wndStatusBar.CommandToIndex(ID_BUILDING_INFO);	
	m_wndStatusBar.SetPaneInfo(1,ID_BUILDING_INFO,SBPS_NOBORDERS, 300);
	m_wndStatusBar.SetPaneInfo(2,ID_PROTOCOL_INFO,SBPS_STRETCH | SBPS_NOBORDERS , 0);
	m_wndStatusBar.SetPaneInfo(3,IDS_SHOW_RESULTS,SBPS_NOBORDERS , 1000);
 	m_wndStatusBar.EnablePaneDoubleClick ();



	
	MainFram_hwd = this->m_hWnd;

 
    

 


        
   //if (m_pvmainwindowdlg == NULL)
   // {
   //     m_pvmainwindowdlg = new CPVMainScreenDlg;
   //     m_pvmainwindowdlg->Create(IDD_PV_MAIN_SCREEN, this);
   //     m_pvmainwindowdlg->ShowWindow (TRUE);
   //   
   // } 

 
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}
void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}
	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnCheckBuildingBar()
{
	 

}
void CMainFrame::OnUpdateCheckBuildingBar(CCmdUI* pCmdUI)
{ 
}
void CMainFrame::OnCheckIOPane()
{
}
void CMainFrame::OnUpdateCheckIOPane(CCmdUI* pCmdUI)
{

}
 

 

 
 
  
BOOL CMainFrame::ValidAddress(CString sAddress,UINT& n1,UINT& n2,UINT& n3,UINT& n4)
{
	int nPos;
	CString sTemp=sAddress;
	n1=_wtoi(sTemp);
	nPos=sTemp.Find(_T("."));
	if(nPos==-1) return false;
	sTemp=sTemp.Mid(nPos+1);
	n2=_wtoi(sTemp);
	nPos=sTemp.Find(_T("."));
	if(nPos==-1) return false;
	sTemp=sTemp.Mid(nPos+1);
	n3=_wtoi(sTemp);
	nPos=sTemp.Find(_T("."));
	if(nPos==-1) return false;
	sTemp=sTemp.Mid(nPos+1);
	n4=_wtoi(sTemp);
	if(n1<0 ||n1>255) return false;
	if(n2<0 ||n2>255) return false;
	if(n3<0 ||n3>255) return false;
	if(n4<0 ||n4>255) return false;
	return true;
}

//删除数据库中 重叠的device.;
void CMainFrame::DeleteConflictInDB()
{
	bool find_conflict = false;
	int temp_item_count = (int)m_product.size();
	CBADO bado;
	bado.SetDBPath(g_strCurBuildingDatabasefilePath);
	bado.OnInitADOConn(); 

	for (int i=0;i<temp_item_count;i++)
	{
		for (int j=i+1;j<temp_item_count;j++)
		{
			if(m_product.at(i).serial_number == m_product.at(j).serial_number)
			{
				find_conflict = true;
				 
				CString mtemp_serial_number;
				CString strSql;
				mtemp_serial_number.Format(_T("%u"),m_product.at(i).serial_number);
				try
				{
					strSql.Format(_T("delete  from ALL_NODE where Serial_ID ='%s'"), mtemp_serial_number);
					bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
				}
				catch(_com_error *e)
				{
					//AfxMessageBox(e->ErrorMessage());
				}
 

				break;
			}
		}
	}
	bado.CloseConn();
	if(find_conflict)
		 PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);
}
 
void CMainFrame::OnFileOpen()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("Open configuration file."));
}
 

 
 

void CMainFrame::OnConnect()
{
 
}
void CMainFrame::OnDisconnect()
{
	 

}
 
void CMainFrame::CheckConnectFailure(const CString& strIP) // 检查失败的原因，并给出详细的提示信息
{
	USES_CONVERSION;
	LPCSTR szIP = W2A(strIP);
	DWORD dwIP = inet_addr(szIP);

	IN_ADDR ia;
	ia.S_un.S_addr = dwIP;

	//////////////////////////////////////////////////////////////////////////
	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if(res != 0)
		return;

	hostent* pHostent = gethostbyname(hostname); 
	if(pHostent==NULL) 
		return;

	hostent& he = *pHostent;
	sockaddr_in sa; 

	memcpy(&sa.sin_addr.s_addr, he.h_addr_list[0],he.h_length); 

	//return   inet_ntoa(sa.sin_addr); 
	CString strHostIP;
	strHostIP.Format(_T("%d.%d.%d.%d"), sa.sin_addr.S_un.S_un_b.s_b1,sa.sin_addr.S_un.S_un_b.s_b2,sa.sin_addr.S_un.S_un_b.s_b3,sa.sin_addr.S_un.S_un_b.s_b4);
	//AfxMessageBox(strIP);

	// 是否是同一子网
	if ( ia.S_un.S_un_b.s_b1 == sa.sin_addr.S_un.S_un_b.s_b1 &&
		ia.S_un.S_un_b.s_b2 == sa.sin_addr.S_un.S_un_b.s_b2 &&
		ia.S_un.S_un_b.s_b3 == sa.sin_addr.S_un.S_un_b.s_b3 
		)
	{// 是同一子网，但是连接不上，那么提示检查设备连接
		CString strTip;
		strTip.Format(_T("Can not set up the connection with %s, please check its IP address and net cable. "), strIP);
		AfxMessageBox(strTip);
	}
	else
	{
		CString strTip;
		strTip.Format(_T("Your host IP is %s, and NC' IP is %s. They are not in same sub net, please reset your IP address. "),strHostIP, strIP);
		AfxMessageBox(strTip);
	}
	

}

 
void CMainFrame::OnScanDevice()
{

	if(m_subNetLst.size()<=0)
	{
		AfxMessageBox(_T("Please Select a main building first."));
		return;
	}
	m_bScanFinished=FALSE;
	m_bScanALL=FALSE;
	g_bPauseMultiRead=TRUE;
    m_nStyle=3;
    Invalidate();
 
	
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	 
	CFrameWndEx::OnTimer(nIDEvent);
}
 
void CMainFrame::SetPaneConnectionPrompt(CString strInfo)
{
	SetPaneString(2,strInfo);
}
 
 
 



CString CMainFrame::GetDeviceClassName(int nClassID)
{
	CString strClassName;
	switch(nClassID)
	{
	case 2:strClassName=g_strTstat5a;break;
	case 1:strClassName=g_strTstat5b;break;
	case 3:strClassName=g_strTstat5b;break;
	case 4:strClassName=g_strTstat5c;break;
	case 12:strClassName=g_strTstat5d;break;
	case PM_NC:strClassName=g_strnetWork;break;
	case NET_WORK_OR485_PRODUCT_MODEL:strClassName=g_strOR485;break;
	case 17: strClassName=g_strTstat5f;break;
	case 18:strClassName=g_strTstat5g;break;
	case 16:strClassName=g_strTstat5e;break;
	case 19:strClassName=g_strTstat5h;break;
	case 7:strClassName=g_strTstat7;break;
	case 6:strClassName=g_strTstat6;break;
	case 13:
	case 14:break;
	default:strClassName=g_strTstat5a;break;
	}

	return strClassName;
}


void CMainFrame::OnMBP()
{
 
}
 
 
   

 

LRESULT CMainFrame::OnFreshStatusBar(WPARAM wParam, LPARAM lParam)
{
//pStatusBar->SetPaneText(nIndext,str.GetString());
	status_info*  pinfoStatusbar;
	pinfoStatusbar=(status_info*)wParam;
	//pinfoStatusbar.nIndex=nIndext;
//	infoStatusbar.strInfoText=str;
	m_wndStatusBar.SetPaneText(pinfoStatusbar->nIndex,pinfoStatusbar->strInfoText);


	return 1;
}


void CMainFrame::OnDestroy()
{
 

	 
	CFrameWndEx::OnDestroy();
	// TODO: Add your message handler code here
}
 
 
 
void CMainFrame::OnUserMannageMentUpdate(CCmdUI *pCmdUI)
{
	if(g_UserLevel==0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CMainFrame::GetIONanme()
{
	try
	{

	 
			/*_ConnectionPtr m_ConTmp;
			_RecordsetPtr m_RsTmp;
			m_ConTmp.CreateInstance("ADODB.Connection");
			m_RsTmp.CreateInstance("ADODB.Recordset");
			m_ConTmp->Open(g_strDatabasefilepath.GetString(),"","",adModeUnknown);
*/

		CBADO bado;
		bado.SetDBPath(g_strCurBuildingDatabasefilePath);
		bado.OnInitADOConn(); 

			CString strSerial;
			strSerial.Format(_T("%d"),g_selected_serialnumber);
			strSerial.Trim();
			CString strsql;
			strsql.Format(_T("select * from IONAME where SERIAL_ID = '%s'"),strSerial);
			//m_RsTmp->Open((_variant_t)strsql,_variant_t((IDispatch *)m_ConTmp,true),adOpenStatic,adLockOptimistic,adCmdText);	
			  bado.m_pRecordset=bado.OpenRecordset(strsql);
			if(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)
			{	
				CString str_temp;
				str_temp.Empty();
				_variant_t temp_variant;
			
				temp_variant=bado.m_pRecordset->GetCollect("SENSORNAME");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Internal Sensor");
				g_strSensorName=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT1");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 1");
				g_strInName1=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT2");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 2");
				g_strInName2=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT3");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 3");
				g_strInName3=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT4");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 4");
				g_strInName4=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT5");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 5");
				g_strInName5=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT6");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 6");
				g_strInName6=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT7");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 7");
				g_strInName7=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT8");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Input 8");
				g_strInName8=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("INPUT9");
			//	temp_variant=m_RsTmp->GetCollect("Humidity Sensor");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Humidity Sensor");
				g_strInHumName=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT1");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 1");
				g_strOutName1=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT2");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 2");
				g_strOutName2=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT3");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 3");
				g_strOutName3=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT4");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 4");
				g_strOutName4=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT5");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 5");
				g_strOutName5=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT6");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 6");
				g_strOutName6=str_temp;

				temp_variant=bado.m_pRecordset->GetCollect("OUTPUT7");
				if(temp_variant.vt!=VT_NULL)
					str_temp=temp_variant;
				else
					str_temp=_T("Output 7");
				g_strOutName7=str_temp;

				g_strInHumName = _T("Humidity Sensor");
				g_strInCO2=_T("CO2 Sensor");
				g_strLightingSensor=_T("Lighting Sensor");
			}
			else
			{
				g_strSensorName =_T("Internal Temp Sensor");
				g_strInName1=_T("Input 1");
				g_strInName2=_T("Input 2");
				g_strInName3=_T("Input 3");
				g_strInName4=_T("Input 4");
				g_strInName5=_T("Input 5");
				g_strInName6=_T("Input 6");
				g_strInName7=_T("Input 7");
				g_strInName8=_T("Input 8");
				g_strLightingSensor=_T("Lighting Sensor");
				g_strInHumName = _T("Humidity Sensor");
				 g_strInCO2=_T("CO2 Sensor");

				g_strOutName1=_T("Output 1");
				g_strOutName2=_T("Output 2");
				g_strOutName3=_T("Output 3");
				g_strOutName4=_T("Output 4");
				g_strOutName5=_T("Output 5");
				g_strOutName6=_T("Output 6");
				g_strOutName7=_T("Output 7");
				g_strOutName8=_T("Output 8");


			}
			bado.CloseRecordset();
			bado.CloseConn();
			/*if(m_RsTmp->State) 
				m_RsTmp->Close(); 
			if(m_ConTmp->State)
				m_ConTmp->Close();	*/

	}
	catch (...)
	{

	}



}
 
void CMainFrame::OnHelp()
{
 

}
 

 
 


 

 
//////////////////////////////////////////////////////////////////////////
// for record last time tree control node click result

// 

// write current click result to register table of windows.
const CString strRegRoot = _T("Software\\Temco T3000 Application\\T3000\\TreeNodeRecord\\");
		    
const CString strSubnetRegEntry = _T("Subnet");
const CString strSubnetRegEntryValid = _T("SubnetValid");
const CString strFloorRegEntry = _T("Floor");
const CString strFloorRegEntryValid = _T("FloorValid");
const CString strRoomRegEntry = _T("Room");
const CString strRoomRegEntryValid = _T("RoomValid");
const CString strDeviceRegEntry = _T("Device");
const CString strDeviceRegEntryValid = _T("DeviceValid");


const CString c_strFileVersionPath = _T("Software\\Temco T3000 Application\\T3000\\FileVersion\\");



void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFrameWndEx::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
}

#include "CM5/mygdiplus.h"
void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	 


	// TODO: Add your message handler code here
	// Do not call CFrameWndEx::OnPaint() for painting messages
}
 
  

 

 


void CMainFrame::OnDatabasePv()
{

 
       CPVDlg dlg;
       dlg.DoModal();
  
    

	
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default
	int nSize = pCopyDataStruct->cbData;// = (strMsg.GetLength()+1)*sizeof(TCHAR); //(lstrlen(szBuffer)+1)*sizeof(TCHAR);
	//pCopyDataStruct->lpData =  (LPVOID)(LPCTSTR)strMsg;
	CString strMsg = CString(LPCTSTR(pCopyDataStruct->lpData));

	//CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_INFO);
	//pList->AddString(strMsg);
	CString show_info;
	show_info.Format(_T("Ping - "));
	show_info = show_info + strMsg;
	SetPaneString(BAC_SHOW_MISSION_RESULTS,show_info);
	//UpdateStatusInfo(strMsg, FALSE);
	//UpdateData(TRUE);
	return CFrameWndEx::OnCopyData(pWnd, pCopyDataStruct);
	/*return CDialog::OnCopyData(pWnd, pCopyDataStruct);*/
}





void CMainFrame::OnUpdateStatusBar(CCmdUI *pCmdUI){
	pCmdUI->Enable(TRUE);

}
 
  
  

 
#define CLOSE_HANDLE(handle) \
	do \
	 { \
	 CloseHandle(handle); \
	 handle = NULL; \
} while (FALSE)
 
void CMainFrame::HandleThreadErrorWithLastError(UINT nIDError, DWORD dwLastError)
{
	//Form the error string to report
	CString sError;
	if (dwLastError)
		sError.Format(_T("%d"), dwLastError);
	else
		sError.Format(_T("%d"), ::GetLastError());
	AfxFormatString1(m_sError, nIDError, sError);

	//Delete the file being downloaded to if it is present
	m_FileToWrite.Close();
	::DeleteFile(m_sFileToDownloadInto);

	//PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED, 1);
}

void CMainFrame::HandleThreadError(UINT nIDError)
{
	m_sError.LoadString(nIDError);
	//PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED, 1);
}

void CALLBACK CMainFrame  ::_OnStatusCallBack(HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus, 
	LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
	//Convert from the SDK C world to the C++ world
	CMainFrame  * pDlg = (CMainFrame  *) dwContext;
	ASSERT(pDlg);
	ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CMainFrame  )));
	//pDlg->OnStatusCallBack(hInternet, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
}

void CMainFrame  ::OnStatusCallBack(HINTERNET /*hInternet*/, DWORD dwInternetStatus, 
	LPVOID lpvStatusInformation, DWORD /*dwStatusInformationLength*/)
{
	switch (dwInternetStatus)
	{
	case INTERNET_STATUS_RESOLVING_NAME:
		{
			//SetStatus(IDS_HTTPDOWNLOAD_RESOLVING_NAME, (LPCTSTR) lpvStatusInformation);
			break;
		}
	case INTERNET_STATUS_NAME_RESOLVED:
		{
			//SetStatus(IDS_HTTPDOWNLOAD_RESOLVED_NAME, (LPCTSTR) lpvStatusInformation);
			break;
		}
	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		{
			//SetStatus(IDS_HTTPDOWNLOAD_CONNECTING, (LPCTSTR) lpvStatusInformation);
			break;
		}
	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		{
			//SetStatus(IDS_HTTPDOWNLOAD_CONNECTED, (LPCTSTR) lpvStatusInformation);
			break;
		}
	case INTERNET_STATUS_REDIRECT:
		{
			//SetStatus(IDS_HTTPDOWNLOAD_REDIRECTING, (LPCTSTR) lpvStatusInformation);
			break;
		}
	default:
		{
			break;
		}
	}
}
   
void CMainFrame::OnUpdateControlInputs(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlOutputs(CCmdUI *pCmdUI)
{
 
}


void CMainFrame::OnUpdateControlVariables(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlPrograms(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlScreens(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlControllers(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlWeekly(CCmdUI *pCmdUI)
{
 
}


void CMainFrame::OnUpdateControlAnnualroutines(CCmdUI *pCmdUI)
{ 
}


void CMainFrame::OnUpdateControlMonitors(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlAlarmLog(CCmdUI *pCmdUI)
{
	 
}

 
void CMainFrame::OnUpdateControlTstat(CCmdUI *pCmdUI)
{
	 
}


void CMainFrame::OnUpdateControlSettings(CCmdUI *pCmdUI)
{
	 
}


BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: Add your message handler code here and/or call default   IDH_TOPIC_TBS_COVER_EDITOR
 
	return CFrameWndEx::OnHelpInfo(pHelpInfo);
}
 


void CMainFrame::OnToolRegistersmaintenancesystem()
{
         //维护寄存器列表管理的 一个应用程序
         //它能够维护所以产品的寄存器
        // 它的所有的功能列表
        /*
        1>用户管理
        2>密码修改
        3>项目管理
        4>寄存器信息修改
        5>产品的添加
        */
         CString strHistotyFile=g_strExePth+_T("RegisterListManager.exe");
       ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMainFrame::OnToolTipNotify(UINT id,NMHDR *Pnmhdr,LRESULT *pResult)
{

	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *) Pnmhdr;
	UINT_PTR nID = Pnmhdr->idFrom - 1;

	 
		return true;

}


void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	// TODO: Add your specialized code here and/or call the base class 
	//根据菜单或者工具栏命令ID加载自己的串,否则调用基类函数   
	if( nID == ID_CONTROL_INPUTS)  
	{  
		rMessage = _T("ID_CONTROL_INPUTS")  ;  
		return;  
	}  
	else if( nID == ID_CONTROL_OUTPUTS )  
	{  
		rMessage = _T("ID_CONTROL_OUTPUTS")  ;  
		return;  
	}  


	return CFrameWndEx::GetMessageString(nID, rMessage);
}


INT_PTR CMainFrame::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: Add your specialized code here and/or call the base class

	//return CFrameWndEx::OnToolHitTest(point, pTI);


	CString adoStr;
	static CString strText;  
	INT_PTR hInt = CFrameWndEx::OnToolHitTest(point,pTI);//先调用基类函数,再修改串.   ;
	strText = pTI->lpszText;  

	if(pTI->uId == ID_CONTROL_INPUTS )  
	{  
		adoStr = _T("test111");

	}  
	strText = adoStr + strText; //重新组合成: New(Ctrl+N)形式.   

	//基类中会释放这个指针pTI->lpszText,但是由于我们要修改这个串,   
	//所以原来的空间不一定够,所以要释放掉原来的,并重新申请,   
	int len = strText.GetLength()*sizeof(TCHAR);  
	TCHAR *pBuf =(TCHAR*)malloc(len+10);  
	memset(pBuf,0,len+10);  
	_tcscpy_s(pBuf,strText.GetLength()+2,strText);  
	free(pTI->lpszText);   
	pTI->lpszText = pBuf;  

	return hInt;  

}

 
 


void CMainFrame::OnMove(int x, int y)
{
    CFrameWndEx::OnMove(x, y);

    // TODO: Add your message handler code here
//     if(b_create_status)
//     {
//         CRect temprec;
//         m_wndStatusBar.GetWindowRect(&temprec);
// 
//          statusbar->SetWindowPos(&wndTop,temprec.left,temprec.top,temprec.Width(),temprec.Height(),SWP_NOACTIVATE | SWP_SHOWWINDOW );
//     }
}

#include "PVDlg.h"

void CMainFrame::OnPvtestPv()
{
   CPVDlg dlg;
   dlg.DoModal();
}



void CMainFrame::OnPvtestPv1()
{
   
  /*  if (m_pvmainwindowdlg == NULL)
    {
        m_pvmainwindowdlg = new CPVMainScreenDlg;
        m_pvmainwindowdlg->Create(IDD_PV_MAIN_SCREEN, this);
        m_pvmainwindowdlg->ShowWindow (TRUE);
      
    }*/
  
  if (!m_pvmainwindowdlg->IsWindowVisible ())
  {
        m_pvmainwindowdlg->ShowWindow (TRUE);
  }
//     CPVDlg dlg;
//     dlg.DoModal();
}
