
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

 
 
 
 
//#include "TStatScanner.h"
/*
#define	ID_BUILDING_INFO	100
#define	ID_RW_INFO			101
#define	ID_PROTOCOL_INFO	102
*/
#include "globle_function.h"
//#include "CM5/DialogCM5.h"  //CM5
 

 
#include "bado/BADO.h"
//#include "Class/MulitithreadSocket.h"
// #include "MBP.h"
// #include "MbPoll.h"
 
 


const int DLG_T3000_VIEW = 0;
const int DLG_NETWORKCONTROL_VIEW = 1;
const int DLG_GRAPGIC_VIEW = 2;
const int DLG_TRENDLOG_VIEW =3;
const int DLG_DIALOGCM5_VIEW = 4;

const int DLG_DIALOGMINIPANEL_VIEW = 6;
const int DLG_AIRQUALITY_VIEW = 7;
const int DLG_LIGHTINGCONTROLLER_VIEW = 8;
const int DLG_HUMCHAMBER = 9;
const int DLG_CO2_VIEW = 10;
const int DLG_CO2_NET_VIEW=11;
const int DLG_BACNET_VIEW = 12;
//T3-Serials
const int DLG_DIALOGT3_VIEW = 5;
const int DLG_DIALOGT38I13O_VIEW=13;
const int DLG_DIALOGT332AI_VIEW=14;
const int DLG_DIALOGT38AI8AO=15;
const int DLG_DIALOGT36CT=16;
const int DLG_DIALOGT3PT10=17;
const int DLG_DIALOG_PRESSURE_SENSOR=18;
const int DLG_DIALOG_DEFAULT_BUILDING = 19;
const int DLG_DIALOG_TEMP_HUMSENSOR = 20;
const int DLG_DIALOG_DEFAULT_T3000_VIEW = 21;
const int DLG_DIALOG_T3_INPUTS_VIEW =22;
const int DLG_DIALOG_T3_OUTPUTS_VIEW =23;
const int DLG_DIALOG_CUSTOM_VIEW = 24;
const int DLG_DIALOG_TSTAT_INPUT_VIEW=25;
const int DLG_DIALOG_TSTAT_OUTPUT_VIEW = 26;
const int NUMVIEWS = 27;


extern int g_gloab_bac_comport;
  class CPVMainScreenDlg;
const int REGISTER_USE_ZIGBEE_485 = 640;
union UNION_INPUT_NAME{
	unsigned short reg_value[4];
	unsigned char char_name[8];
};

typedef struct _com_port_tree
{//for vector
	HTREEITEM building_item;//building name
	HTREEITEM serial_port_item;	//floor name
	HTREEITEM each_port_item;	//floor name
	CString strComPortName;
}com_port_tree;


typedef struct _tree_floor///////////////////////////////////////////////////////////////////////////////
{//for vector
	HTREEITEM building_item;//building name
	HTREEITEM floor_item;	//floor name
	CString strFloorName;
}tree_floor;///////////////////////////////////////////////////////////////////////////////
typedef struct _tree_room///////////////////////////////////////////////////////////////////////////////
{//for vector
	HTREEITEM building_item;//building name
	HTREEITEM floor_item;	//floor name
	HTREEITEM room_item;	//Room name
	CString strFloorName;
	CString strRoomName;
}tree_room;///////////////////////////////////////////////////////////////////////////////

typedef struct _background_infor_TAG
{
	HTREEITEM building_item;//building name
	CString Screen_name;
	CString Background_Bmp;
	CString building_name;
}background_infor;

typedef struct _BUILDING_TAG
{
	HTREEITEM hbuilding_item;
	HANDLE hCommunication;
	CString strBuildingName;//sub building name
	CString strProtocol;
	CString strIp;
	CString strComPort;
	CString strIpPort;
	CString strBaudRate;
	CString strMainBuildingname;
	CString strConnectionType;
}Building_info;

typedef struct _tree_product//////////////////////
{//for vector 
	//every product leaf of the leaf
	Building_info  BuildingInfo;
	HTREEITEM product_item;//product name 
	unsigned int serial_number;//the id of product ;Modbus protocol need
	int product_class_id;//maybe 1 is Tstat;2 is led;3 is minipanel;and others
	int baudrate;
	int product_id;
	float software_version;
	float hardware_version;
	int nEPsize;
	CString strImgPathName;
	int protocol;
	unsigned int ncomport;
	bool status;
	bool status_last_time[3];
	CString NetworkCard_Address;
	CString NameShowOnTree;
    CString Custom;
	unsigned int note_parent_serial_number;
	unsigned char panel_number;
	unsigned int object_instance;
	
}tree_product;///////////////////////////////////////////////////////////////////////////////

//

typedef struct _binary_search_result
{
	int id;//the id of product ;Modbus protocol need
	int product_class_id;//7 product model
	int baudrate;
	unsigned int serialnumber;//0,1,2,3
	float hardware_version;//8
	float software_version;
	int nEPsize;
	
}binary_search_result;

 
class CMainFrame : public CFrameWndEx
{	
private:
	 
	BOOL m_bDialogOpen;
//	LONG OnDlgClose(UINT wParam, LONG lParam);
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
 
	void OnToolFresh();
	void OnToolRefreshLeftTreee();
 
//	CMulitithreadSocket m_wskServer;
	BOOL m_bServer;
public:

    CView * m_pViews[NUMVIEWS];
    UINT m_nCurView;    
 
 
	CString					m_strCfgFilePath;
public://for scan
	int m_nScanType;
	CString m_strsubNetSelectedScan;
 	HANDLE m_hCurCommunication;
    BOOL m_bScanFinished;
	BOOL m_bScanALL;
	vector <CString> m_vector_comport;
	BOOL m_frist_start;
// Attributes
public:
	 
	int						m_nIpPort;
	CString				m_strIP;
	int						m_nBaudrate;
	int					m_building_com_port;
	CString				g_strIpAdress;
	vector<Building_info>	m_subNetLst;
	vector<CString>			m_buildingLst;
	 vector<CString> m_szComs;
     //vector <HTREEITEM> m_rootLst;//for every building name
	//HTREEITEM treem[20];
	vector <com_port_tree> m_comportlist;
	vector <tree_floor>		m_floorLst;//for every building name
	vector <tree_room>		m_roomLst;//for every room name	
	vector <background_infor> m_backgroundLst;
	vector <tree_product>	m_product;//for every product leaf
// 	_ConnectionPtr				m_pCon;//for ado connection
// 	_RecordsetPtr				m_pRs;//for ado 
	 
    tree_product m_current_tree_node ;
    tree_product m_lasttime_tree_node;
	CString m_strCurSubBuldingName;
	Building_info m_CurSubBuldingInfo;
	CString m_strCurMainBuildingName;
	int m_nCurSubBuildingIndex;
	//
public://scan
	

public:

// Operations
public:
	CMFCStatusBar& GetStatusBar ()
	{
	return m_wndStatusBar;
	}
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	 CMFCMenuBar				m_wndMenuBar;
	CMFCToolBar				m_wndToolBar;

 
	//CMFCToolBarImages		m_UserImages;
public: 
	 
	CMFCStatusBar			m_wndStatusBar;
		

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	//afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnUpdateCheckBuildingBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckIOPane(CCmdUI* pCmdUI);
	afx_msg void OnScanDevice();
 
	afx_msg void OnHelp();
	
	 
	afx_msg LRESULT OnFreshStatusBar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUserMannageMentUpdate(CCmdUI *pCmdUI);
 
	 
 
	 
	 
	DECLARE_MESSAGE_MAP()

public:
	BOOL  CheckDeviceStatus(int refresh_com);
 
 
	void OnMBP();
	 
	void OnFileOpen();
 
 
	void OnConnect();
	void OnDisconnect();

 
 

	void OnCheckBuildingBar();
	 
 
 
	void OnCheckIOPane();
 
	void DeleteConflictInDB();
	void SwitchToGraphicView();
	void SetPaneConnectionPrompt(CString strInfo);
	void OnHTreeItemSeletedChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//void OnHTreeItemKeyDownChanged(NMHDR* pNMHDR, LRESULT* pResult);
	void OnHTreeItemEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	LRESULT OnHTreeItemBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	void  OnHTreeItemClick(NMHDR *pNMHDR, LRESULT *pResult);
	void  OnHTreeMessageSeletedChanged(NMHDR *pNMHDR, LRESULT *pResult);
			
			//BOOL ValidAddress(CString sAddress);
	BOOL ValidAddress(CString sAddress,UINT& n1,UINT& n2,UINT& n3,UINT& n4);
	 
	void CheckConnectFailure(const CString& strIP);// ���ʧ�ܵ�ԭ�򣬲�������ϸ����ʾ��Ϣ
	afx_msg void OnTimer(UINT_PTR nIDEvent);
 
 

	//scan funtion:


	afx_msg void OnDestroy();
 
 
 
	void GetIONanme();
	 
 

 
 
protected:
 
public:
  

 
	//void InitTreeNodeConn();
	void GetAllTreeItems( HTREEITEM hItem, vector<HTREEITEM>& szTreeItems  );
	//void EnableRefreshTreeView(BOOL bEnable);
	void DoFreshAll();
	//void RefreshTreeView();

	LRESULT  CMainFrame::RefreshTreeViewMap(WPARAM wParam, LPARAM lParam);
	LRESULT  CMainFrame::Message_Scan_Product(WPARAM wParam,LPARAM lParam);
	// suspend refresh tree view thread, when flash or other operation need read or write large data by Modbus.
	void SuspendRefreshThread();
	void ContinueRefreshThread();
	CString GetDeviceClassName(int nClassID);
	CString GetScreenName(int nSerialNumber, int nModbusID);
protected:


	// for record tree node 
	//void SaveTreeNodeRecordToReg(HTREEITEM& htiCurSel);
	//BOOL WriteValueToReg(CRegKey& reg, HTREEITEM& htiItem);
	//void SelectTreeNodeFromRecord();
	HTREEITEM GetLastSelNodeFromRecord(CRegKey& reg, HTREEITEM& htiRoot);
	HTREEITEM SearchItemByName(HTREEITEM& htiRoot, const CString& strItemName);
	BOOL ImportDataBaseForFirstRun();
	CString GetCurrentFileVersion();
	CString ReadFileVersionFromRegister(CRegKey& reg);
//protected://lsc20111213�޸�
public:
	BOOL m_bEnableRefreshTreeView;
 

	CString						m_strCurSelNodeName;  // ��¼��ǰ������ڵ��name
	BOOL m_isCM5;
	BOOL m_isMiniPanel;
	//HTREEITEM				m_htiCurSel;  // ��¼��ǰ������ڵ�
	CString						m_strFileVersion;

	void EnableMyToolBarButton(int nIndex, int nID, BOOL bEnable);
public:
//	afx_msg void OnDatabaseTemcoproducts();

	void ReadExcel();

	unsigned short tempchange[512];//for tstat6
	unsigned short temptstat6[512];
	unsigned short nFlag;
	
	void Tstat6_func();
	void JudgeTstat6dbExist(CString strtable,CString strsql);
	void Updata_db_tstat6(unsigned short imodel);
	BOOL FistWdb;
	//afx_msg void OnFileIsptool();
	void JudgeTstat6SliderExist(CString strtable,CString strsql);
	void UpdataSlider(int Flag);
	void ReadSlider();

	UINT FlagSerialNumber;
	void Treestatus();
 
 //   static DWORD WINAPI ConnectToTreeNode(LPVOID);
	afx_msg void OnDatabaseIonameconfig();
	 
	afx_msg void OnViewCommunicatetraffic();
	afx_msg void OnToolIsptoolforone();
 
	 
	bool mbPollDlgOpen;
protected:
	//afx_msg LRESULT OnMbpollClosed(WPARAM wParam, LPARAM lParam);
public:
	CString					m_strPingIP;	
 
	
	 
 
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnPaint();
 
 
	afx_msg void OnDatabasePv();
 
  
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
 
	UINT m_nStyle;
	 
	afx_msg void OnUpdateStatusBar(CCmdUI *pCmdUI);
 
 
	
	 
public:
	CString m_sURLToDownload;
	CString m_sFileToDownloadInto;
	CString m_sUserName;
	CString m_sPassword;
	CString       m_sError;
	CString       m_sServer; 
	CString       m_sObject; 
	CString       m_sFilename;
	INTERNET_PORT m_nPort;
	DWORD         m_dwServiceType;
	HINTERNET     m_hInternetSession;
	HINTERNET     m_hHttpConnection;
	HINTERNET     m_hHttpFile;
 
	BOOL          m_bSafeToClose;
	CFile         m_FileToWrite;
	//CWinThread*   m_pThread;
     int  m_lastinterface;
	CString      m_file_firmware_Time;
 
public:
 
 
	static void CALLBACK _OnStatusCallBack(HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus, 
		LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
	void OnStatusCallBack(HINTERNET hInternet, DWORD dwInternetStatus, 
		LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
	 
	void HandleThreadErrorWithLastError(UINT nIDError, DWORD dwLastError=0);
	void HandleThreadError(UINT nIDError);
 
 
 
 
 
 
	afx_msg void OnControlSettings();
	afx_msg void OnUpdateControlInputs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlOutputs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlVariables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlPrograms(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlScreens(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlControllers(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlWeekly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlAnnualroutines(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlMonitors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlAlarmLog(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlTstat(CCmdUI *pCmdUI);
	afx_msg void OnUpdateControlSettings(CCmdUI *pCmdUI);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	 
   // afx_msg void OnToolProductsregistersmaintenance();
    afx_msg void OnToolRegistersmaintenancesystem();
 
 	virtual void GetMessageString(UINT nID, CString& rMessage) const;
		afx_msg BOOL  OnToolTipNotify(UINT id,NMHDR *Pnmhdr,LRESULT *pResult);
		virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
        afx_msg void OnMove(int x, int y);
        afx_msg void OnPvtestPv();
        afx_msg void OnPvtestPv1();

         CPVMainScreenDlg *m_pvmainwindowdlg;  
};
