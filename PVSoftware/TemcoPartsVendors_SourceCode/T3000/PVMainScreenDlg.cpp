// PVMainScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVMainScreenDlg.h"
#include "afxdialogex.h"
#include <climits>
#include <ciso646>
#include "NewPNDlg.h"
#include "PartVendorQuotationDlg.h"

 HBITMAP 	hBitmap_default_bmp;
// CPVMainScreenDlg dialog

IMPLEMENT_DYNAMIC(CPVMainScreenDlg, CDialogEx)

CPVMainScreenDlg::CPVMainScreenDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVMainScreenDlg::IDD, pParent)
{
    m_select_type = -1;
    m_PVIMaster= NULL;
    m_PVVendor= NULL;
    m_PVPO = NULL;
    m_PvBuild = NULL;
    m_PvBuy = NULL;
	m_pvCustomer = NULL;
	/*m_pvLoginWindow = NULL;*/
}

CPVMainScreenDlg::~CPVMainScreenDlg()
{
}

void CPVMainScreenDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_LIST_VIEW, m_view_static);
    // DDX_Control(pDX, IDC_SPLITTERBUTTON, m_splitterbutton);
    //  DDX_Control(pDX, IDC_ITEM_MASTER, m_button_IM);
    DDX_Control(pDX, IDC_ITEM_MAIINPAGE, m_HomeButton);
    DDX_Control(pDX, IDC_ITEM_MASTER, m_ItemMasterButton);
    DDX_Control(pDX, IDC_CUSTOMERS, m_CustomerButton);
    DDX_Control(pDX, IDC_BUY, m_BuyButton);
    DDX_Control(pDX, IDC_VENDOR, m_VendorButton);
    DDX_Control(pDX, IDC_PO, m_PoButton);
    DDX_Control(pDX, IDC_PO2, m_BuildButton);
 
}


BEGIN_MESSAGE_MAP(CPVMainScreenDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ITEM_MASTER, &CPVMainScreenDlg::OnBnClickedItemMaster)
    ON_WM_SIZE()
    //ON_COMMAND(ID_PN_NEWPN, &CPVMainScreenDlg::OnPnNewpn)
    ON_BN_CLICKED(IDC_VENDOR, &CPVMainScreenDlg::OnBnClickedVendor)
    ON_BN_CLICKED(IDC_PO, &CPVMainScreenDlg::OnBnClickedPo)

    /*   ON_COMMAND(ID_PARTS_MAINTAINVENDOR, &CPVMainScreenDlg::OnPartsMaintainvendor)*/
    ON_BN_CLICKED(IDC_PO2, &CPVMainScreenDlg::OnBnClickedPo2)
    ON_BN_CLICKED(IDC_BUY, &CPVMainScreenDlg::OnBnClickedBuy)
    ON_COMMAND(ID_SETTING_UNITSOFMEASURE, &CPVMainScreenDlg::OnSettingUnitsofmeasure)
    ON_WM_SYSCOMMAND()
    ON_COMMAND(ID_SETTING_IMPORTBOM, &CPVMainScreenDlg::OnSettingImportbom)
    ON_COMMAND(ID_SETTING_EXIT, &CPVMainScreenDlg::OnSettingExit)
    ON_BN_CLICKED(IDC_WAREHOUSE, &CPVMainScreenDlg::OnBnClickedWarehouse)
    ON_COMMAND(ID_SETTING_CURRENCIES, &CPVMainScreenDlg::OnSettingCurrencies)
    
	ON_BN_CLICKED(IDC_CUSTOMERS, &CPVMainScreenDlg::OnBnClickedCustomers)
	ON_COMMAND(ID_SETTING_DATASYNC, &CPVMainScreenDlg::OnSettingDatasync)
	ON_BN_CLICKED(IDC_ITEM_MAIINPAGE, &CPVMainScreenDlg::OnBnClickedItemMaiinpage)
	ON_WM_PAINT()
//ON_WM_CTLCOLOR()
ON_COMMAND(ID_SETTING_IMPORTBOM34077, &CPVMainScreenDlg::OnSettingImportbom34077)
ON_COMMAND(ID_SETTING_DBCONFIG, &CPVMainScreenDlg::OnSettingDbconfig)
END_MESSAGE_MAP()


// CPVMainScreenDlg message handlers


BOOL CPVMainScreenDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CRect ViewRect;
    GetClientRect(&ViewRect);

    if (m_view_static.GetSafeHwnd())
    {
        m_view_static.MoveWindow(CRect(60,0,ViewRect.Width(),ViewRect.Height()),TRUE);
    }

  //Initial_all_dialogs();
  //Switch_Windows();


//     CString g_configfile_path=g_strExePth+_T("T3000_config.ini");
//     CString strTemp= g_strExePth + _T("Database\\PV\\PV.mdb");
//     CString path;
//     GetPrivateProfileString(_T("PartsVendors"),_T("PVDB"),strTemp,path.GetBuffer (MAX_PATH),MAX_PATH,g_configfile_path);
//     path.ReleaseBuffer ();



    CString StrTitle;
    StrTitle.Format (_T("Temco Part&Vendor(Window Client) Rev1.9.1(2018421)"));
    SetWindowText (StrTitle);
   
    MoveWindow (0,0,ViewRect.Width ()-230,ViewRect.Height ());
      
//m_HomeButton.SetFaceColor(RGB(66,92,251));
// 	if (m_pvLoginWindow == NULL)
// 	{
// 		m_pvLoginWindow = new CPVLoginWindow;
// 
// 		if (!m_pvLoginWindow->Create(IDD_DIALOG_BACKGOURD,this))
// 		{
// 			return  FALSE;
// 		}
// 	}

// 	CRect rcWnd;
// 	CWnd* pWnd = GetDlgItem(IDC_STATIC_LIST_VIEW);
// 	pWnd->GetWindowRect(rcWnd);
// 	ScreenToClient(rcWnd);
// 
// 	m_pvLoginWindow->MoveWindow(&rcWnd);
// 
// 	m_pvLoginWindow->ShowWindow(SW_SHOW);
// 	
// 	m_HomeButton.EnableWindow(FALSE);

	 hBitmap_default_bmp =(HBITMAP)LoadImage(AfxGetInstanceHandle(),  
		MAKEINTRESOURCE(IDB_BITMAP_PVLOGO),  
		IMAGE_BITMAP,0,0,  
		LR_LOADMAP3DCOLORS); 
	
    return TRUE;

}
void CPVMainScreenDlg::Initial_all_dialogs()
{
    //ItemMaster
    if ((m_PVIMaster==NULL)&&(m_select_type == 0))
    {
        m_PVIMaster = new CPVItemMasterDlg;
        if (!m_PVIMaster->Create(CPVItemMasterDlg::IDD,this))
        {
            return;
        }
    }
    if ((m_PVVendor==NULL)&&(m_select_type == 1))
    {
        m_PVVendor = new CPVVendorDlg;
        if (!m_PVVendor->Create(CPVVendorDlg::IDD,this))
        {
            return;
        }
    }
    
	if ((m_PVPO==NULL)&&(m_select_type == 2))
    {
        m_PVPO = new CPVPODlg;
        if (!m_PVPO->Create(CPVPODlg::IDD,this))
        {
            return;
        }
    }
 
	if ((m_pvBuildHistory==NULL)&&(m_select_type == 3))
    {
        m_pvBuildHistory = new CBuildHistoryDlg;
        if (!m_pvBuildHistory->Create(CBuildHistoryDlg::IDD,this))
        {
            return;
        }
    }
   
	if ((m_PvBuy==NULL)&&(m_select_type == 4))
    {
        m_PvBuy = new CPVBuyDlg;
        if (!m_PvBuy->Create (CPVBuyDlg::IDD,this))
        {
            return;
        }
    }
	 
	if ((m_pvCustomer==NULL)&&(m_select_type == 5))
	{
		m_pvCustomer = new CCustomerDlg;

		if (!m_pvCustomer->Create(CCustomerDlg::IDD,this))
		{
			return ;
		}
	}


}
void CPVMainScreenDlg::Switch_Windows()
{
    CRect rcWnd;
    CWnd* pWnd = GetDlgItem(IDC_STATIC_LIST_VIEW);
    pWnd->GetWindowRect(rcWnd);
    ScreenToClient(rcWnd);
	if (m_select_type == -1)
	{
	   // m_pvLoginWindow->ShowWindow(SW_SHOW);
	    if (m_PVIMaster)
	    {
		   m_PVIMaster->ShowWindow(SW_HIDE);
	    }
		if (m_PVVendor)
		{
		m_PVVendor->ShowWindow(SW_HIDE);
		}
		if (m_PVPO)
		{
		m_PVPO->ShowWindow(SW_HIDE);
		}
		if (m_pvBuildHistory)
		{
		m_pvBuildHistory->ShowWindow (SW_HIDE);
		}
		if (m_PvBuy)
		{
		m_PvBuy->ShowWindow (SW_HIDE);
		}
		if (m_pvCustomer)
		{
		m_pvCustomer->ShowWindow(SW_HIDE);
		}
		
		//m_pvLoginWindow->MoveWindow(&rcWnd);

		m_HomeButton.EnableWindow(FALSE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(TRUE);
	}
    else if (m_select_type == 0)
    {
	    //m_pvLoginWindow->ShowWindow(SW_HIDE);
		if (m_PVIMaster)
        {m_PVIMaster->ShowWindow(SW_SHOW);
			
		m_PVIMaster->ShowData();
        g_hwnd_now = m_PVIMaster->m_hWnd;
        }
		if (m_PVVendor){
		   m_PVVendor->ShowWindow(SW_HIDE);
		}
     if (m_PVPO)
     {m_PVPO->ShowWindow(SW_HIDE);}
     if (m_pvBuildHistory){ m_pvBuildHistory->ShowWindow (SW_HIDE);}
       	if (m_PvBuy){  m_PvBuy->ShowWindow (SW_HIDE);}
      if (m_pvCustomer)
      {
	  m_pvCustomer->ShowWindow(SW_HIDE);
      }
		
        //m_PVIMaster->pn_table.Initial_Data();
        // m_PVIMaster->Load_DataToList();

        m_PVIMaster->MoveWindow(&rcWnd);

		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(FALSE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(TRUE);

    }
    else if (m_select_type == 1)
    {
	  if (m_PVIMaster){ m_PVIMaster->ShowWindow(SW_HIDE);}
    
       if (m_PVPO)
       {
	    m_PVPO->ShowWindow(SW_HIDE);
       }
       if (m_pvBuildHistory)
       {
	    m_pvBuildHistory->ShowWindow (SW_HIDE);
       }
		if (m_PvBuy)
		{
		 m_PvBuy->ShowWindow (SW_HIDE);
		}
        if (m_pvCustomer)
        {
		m_pvCustomer->ShowWindow(SW_HIDE);
        }
       
       
		if (m_PVVendor)
		{
			m_PVVendor->ShowWindow(SW_SHOW);
			m_PVVendor->ShowData();
			m_PVVendor->MoveWindow(&rcWnd);
            g_hwnd_now = m_PVVendor->m_hWnd;
		}
        


		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(FALSE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(TRUE);
    }
    else if (m_select_type == 2)
    {
	  
        if (m_PVIMaster)
        {
		m_PVIMaster->ShowWindow(SW_HIDE);
        }
        if (m_PVVendor)
        {
		m_PVVendor->ShowWindow(SW_HIDE);
        }
        if (m_pvBuildHistory)
        {
		 m_pvBuildHistory->ShowWindow (SW_HIDE);
        }
        if (m_PvBuy)
        {
		   m_PvBuy->ShowWindow (SW_HIDE);
        }
         if (m_pvCustomer)
         {
		 m_pvCustomer->ShowWindow(SW_HIDE);
         }
		

		if (m_PVPO)
		{
			m_PVPO->ShowWindow(SW_SHOW);
			m_PVPO->ShowData();
			m_PVPO->MoveWindow(&rcWnd);
             g_hwnd_now = m_PVPO->m_hWnd;
		}
       

		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(FALSE);
		m_BuildButton.EnableWindow(TRUE);

    }
    else if (m_select_type == 3)
    {
	     
        
		if (m_PVPO)
		{
		m_PVPO->ShowWindow(SW_HIDE );
		}
       
		if (m_PVIMaster)
		{
		 m_PVIMaster->ShowWindow(SW_HIDE);
		}
       
		if (m_PVVendor)
		{
		 m_PVVendor->ShowWindow(SW_HIDE);
		}
    
		if (m_PvBuy)
		{
		    m_PvBuy->ShowWindow (SW_HIDE);
		}
       
		if (m_pvBuildHistory)
		{
		 m_pvBuildHistory->ShowWindow (SW_SHOW);
		  m_pvBuildHistory->MoveWindow(&rcWnd);
          // g_hwnd_now = m_pvBuildHistory->m_hWnd;
		}
	
		if (m_pvCustomer)
		{
			m_pvCustomer->ShowWindow(SW_HIDE);
		}
      


		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(FALSE);

    }
    else if (m_select_type == 4)
    {
	 //m_pvLoginWindow->ShowWindow(SW_HIDE);
	 if (m_PVPO)
	 {
	  m_PVPO->ShowWindow(SW_HIDE );
	 }
       
		if (m_PVIMaster)
		{
		 m_PVIMaster->ShowWindow(SW_HIDE);
		}
       
		if (m_PVVendor)
		{
		 m_PVVendor->ShowWindow(SW_HIDE);
		}
       
		if (m_pvBuildHistory)
		{
		  m_pvBuildHistory->ShowWindow (SW_HIDE);
		}
      
		if (m_pvCustomer)
		{
		m_pvCustomer->ShowWindow(SW_HIDE);
		}
		if (m_PvBuy)
		{
			m_PvBuy->ShowWindow (SW_SHOW);
			m_PvBuy->MoveWindow(&rcWnd);
              g_hwnd_now = m_PvBuy->m_hWnd;
		}

        

		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(TRUE);
		m_BuyButton.EnableWindow(FALSE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(TRUE);


    }
	else if (m_select_type == 5)
	{
	   if (m_PVPO)
	   {
	   m_PVPO->ShowWindow(SW_HIDE );
	   }
		
		if (m_PVIMaster)
		{
		m_PVIMaster->ShowWindow(SW_HIDE);
		}
		
		if (m_PVVendor)
		{
		m_PVVendor->ShowWindow(SW_HIDE);
		}
		
		if (m_pvBuildHistory)
		{
		m_pvBuildHistory->ShowWindow (SW_HIDE);
		}
		
		if (m_PvBuy)
		{
			m_PvBuy->ShowWindow (SW_HIDE);
		}
	
		if (m_pvCustomer)
		{
			m_pvCustomer->ShowWindow(SW_SHOW);
			m_pvCustomer->MoveWindow(&rcWnd);
			m_pvCustomer->ShowData();
            g_hwnd_now = m_pvCustomer->m_hWnd;
		}
		


		m_HomeButton.EnableWindow(TRUE);
		m_ItemMasterButton.EnableWindow(TRUE);
		m_CustomerButton.EnableWindow(FALSE);
		m_BuyButton.EnableWindow(TRUE);
		m_VendorButton.EnableWindow(TRUE);
		m_PoButton.EnableWindow(TRUE);
		m_BuildButton.EnableWindow(TRUE);


	}
 
     if ((m_PVIMaster)&&(!m_PVIMaster->IsWindowVisible ()))
    {
        if ((m_PVIMaster->PartWindow)&&(m_PVIMaster->PartWindow->IsWindowVisible ()))
        {
            m_PVIMaster->PartWindow->ShowWindow (FALSE);
        }
        if((m_PVIMaster->PartQuatationWindow)&& (m_PVIMaster->PartQuatationWindow->IsWindowVisible()))
        {
            m_PVIMaster->PartQuatationWindow->ShowWindow (FALSE);
        }

    } 
}

void CPVMainScreenDlg::OnBnClickedItemMaster()
{
    if (m_select_type != 0)
    {
        m_select_type = 0;
		Initial_all_dialogs();
        Switch_Windows() ;
    }
}
void CPVMainScreenDlg::OnBnClickedVendor()
{
    if (m_select_type != 1)
    {
        m_select_type = 1;
		Initial_all_dialogs();
        Switch_Windows();
    }
}
void CPVMainScreenDlg::OnBnClickedPo()
{
    if (m_select_type != 2)
    {
        m_select_type = 2;
			Initial_all_dialogs();
        Switch_Windows();
    }
}
void CPVMainScreenDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (nType == SIZE_MAXIMIZED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);

         if (m_view_static.GetSafeHwnd())
        {
            CRect ButtonRect;
            m_HomeButton.GetClientRect(&ButtonRect)   ;
            int width =   ButtonRect.Width()+5;
            m_view_static.MoveWindow(CRect(width,0,ViewRect.Width(),ViewRect.Height()),TRUE);
            CRect rcWnd;
            CWnd* pWnd = GetDlgItem(IDC_STATIC_LIST_VIEW);
            pWnd->GetWindowRect(rcWnd);
            ScreenToClient(rcWnd);
		 
			if (m_PVIMaster)
			{
				m_PVIMaster->MoveWindow(&rcWnd);
			}
			if (m_PVVendor)
			{
				m_PVVendor->MoveWindow(&rcWnd);
			}
			if (m_PVPO)
			{
				m_PVPO->MoveWindow(&rcWnd);
			}
			if (m_pvBuildHistory)
			{
				m_pvBuildHistory->MoveWindow (&rcWnd);
			}
			if (m_PvBuy)
			{
				m_PvBuy->MoveWindow (&rcWnd);
			}
			if (m_pvCustomer)
			{
				m_pvCustomer->MoveWindow(&rcWnd);
			}
        }
    }
    if (nType==SIZE_RESTORED)
    {

        CRect ViewRect;
        GetClientRect(&ViewRect);

        if (m_view_static.GetSafeHwnd())
        {
            CRect ButtonRect;
            m_HomeButton.GetClientRect(&ButtonRect)   ;
             int width =   ButtonRect.Width()+5;
            m_view_static.MoveWindow(CRect(width,0,ViewRect.Width(),ViewRect.Height()),TRUE);
            CRect rcWnd;
            CWnd* pWnd = GetDlgItem(IDC_STATIC_LIST_VIEW);
            pWnd->GetWindowRect(rcWnd);
            ScreenToClient(rcWnd);
			/*  m_PVIMaster->MoveWindow(&rcWnd);
			m_PVVendor->MoveWindow(&rcWnd);
			m_PVPO->MoveWindow(&rcWnd);
			m_PvBuild->MoveWindow (&rcWnd);
			m_PvBuy->MoveWindow (&rcWnd);
			m_pvCustomer->MoveWindow(&rcWnd);*/
			if (m_PVIMaster)
			{
				m_PVIMaster->MoveWindow(&rcWnd);
			}
			if (m_PVVendor)
			{
				m_PVVendor->MoveWindow(&rcWnd);
			}
			if (m_PVPO)
			{
				m_PVPO->MoveWindow(&rcWnd);
			}
			if (m_pvBuildHistory)
			{
				m_pvBuildHistory->MoveWindow (&rcWnd);
			}
			if (m_PvBuy)
			{
				m_PvBuy->MoveWindow (&rcWnd);
			}
			if (m_pvCustomer)
			{
				m_pvCustomer->MoveWindow(&rcWnd);
			}
        }

    }

}
           #include "BuildHistoryDlg.h"
void CPVMainScreenDlg::OnBnClickedPo2()
{
   if (m_select_type != 3)
    {
    m_select_type = 3;
    Initial_all_dialogs();
    Switch_Windows();
    }
   /*CBuildHistoryDlg dlg;
   dlg.DoModal();*/
}


void CPVMainScreenDlg::OnBnClickedBuy()
{
    if (m_select_type != 4)
    {
        m_select_type = 4;
	    Initial_all_dialogs();
        Switch_Windows();
    }
}

#include "PVUnitMeasureDlg.h"
void CPVMainScreenDlg::OnSettingUnitsofmeasure()
{
    CPVUnitMeasureDlg dlg;
    dlg.DoModal ();
 
}


void CPVMainScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    
    CDialogEx::OnSysCommand(nID, lParam);
}


#include "PVImportBOMDlg.h"
void CPVMainScreenDlg::OnSettingImportbom()
{
    CPVImportBOMDlg dlg;
    dlg.DoModal ();
}


void CPVMainScreenDlg::OnSettingExit()
{
    //CDialogEx::OnOK();
}

#include "NewPNDlg.h"
void CPVMainScreenDlg::OnBnClickedWarehouse()
{
    CNewPNDlg dlg;
    dlg.m_new_item = 0;
    dlg.m_saveCloseWindow = TRUE;
    dlg.DoModal();
}

#include "PVCurrenciesDlg.h"
void CPVMainScreenDlg::OnSettingCurrencies()
{
     CPVCurrenciesDlg dlg;
     dlg.DoModal ();
}


 


void CPVMainScreenDlg::OnBnClickedCustomers()
{
	if (m_select_type != 5)
	{
		m_select_type = 5;
			Initial_all_dialogs();
		Switch_Windows();
	}
}

#include "DebugMessageDlg.h"
void CPVMainScreenDlg::OnSettingDatasync()
{
	CDebugMessageDlg dlg;
	dlg.DoModal();
	
}


void CPVMainScreenDlg::OnBnClickedItemMaiinpage()
{
	if (m_select_type != -1)
	{
		m_select_type = -1;
		Switch_Windows();
	}
}


void CPVMainScreenDlg::OnPaint()
{
	 
	   CPaintDC   dc(this);   
	   CRect   rect;   
	   GetClientRect(&rect);   
	   CDC   dcMem;   
	   dcMem.CreateCompatibleDC(&dc);   
	   CBitmap   bmpBackground;   
	   bmpBackground.LoadBitmap(IDB_BITMAP_PVLOGO);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
	   //被我命名成了IDB_Bg，因而我这句就是bmpBackground.LoadBitmap(IDB_Bg);  

	   BITMAP   bitmap;   
	   bmpBackground.GetBitmap(&bitmap);   
	   CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	   dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		   bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
}


//HBRUSH CPVMainScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  Change any attributes of the DC here
//	if (pWnd == this)
//	{
//		 return m_brBK;
//	}
//	// TODO:  Return a different brush if the default is not desired
//	return hbr;
//}


void CPVMainScreenDlg::OnSettingImportbom34077()
{
    CString strHistotyFile=g_strExePth+_T("Read.exe");
    ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
}

#include "DBConfigDlg.h"
void CPVMainScreenDlg::OnSettingDbconfig()
{
     CDBConfigDlg dlg;
     dlg.DoModal();
}
