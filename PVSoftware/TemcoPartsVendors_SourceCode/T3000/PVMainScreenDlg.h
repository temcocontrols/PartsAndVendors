#pragma once
#include "PVItemMasterDlg.h"
#include "afxwin.h"
#include "PVVendorDlg.h"
#include "PVPODlg.h"
#include "PVBuildDlg.h"
#include "PVBuyDlg.h"

#include "afxbutton.h"
#include "PVDatabase.h"
#include "CustomerDlg.h"
#include "NewPNDlg.h"
#include "PVLoginWindow.h"
#include "BuildHistoryDlg.h"
#include "SSplitter.h"
// CPVMainScreenDlg dialog

class CPVMainScreenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVMainScreenDlg)

public:
	CPVMainScreenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVMainScreenDlg();

// Dialog Data
	enum { IDD = IDD_PV_MAIN_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void Initial_all_dialogs();
    void Switch_Windows();
public:
int m_select_type;
CPVItemMasterDlg *m_PVIMaster;
CPVVendorDlg   *m_PVVendor;
CPVPODlg *m_PVPO;
CPVBuildDlg *m_PvBuild;
CPVBuyDlg *m_PvBuy;
CCustomerDlg *m_pvCustomer;
CBuildHistoryDlg *m_pvBuildHistory;
//CPVLoginWindow *m_pvLoginWindow;
afx_msg void OnBnClickedItemMaster();
afx_msg void OnSize(UINT nType, int cx, int cy);
CStatic m_view_static;
//afx_msg void OnPnNewpn();
afx_msg void OnBnClickedVendor();
afx_msg void OnBnClickedPo();

afx_msg void OnBnClickedPo2();
afx_msg void OnBnClickedBuy();

afx_msg void OnSettingUnitsofmeasure();
afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
afx_msg void OnSettingImportbom();
afx_msg void OnSettingExit();
afx_msg void OnBnClickedWarehouse();
//CMFCButton m_button_IM;
afx_msg void OnSettingCurrencies();
 


Table_PN PVDatabase;
afx_msg void OnBnClickedCustomers();
afx_msg void OnSettingDatasync();
afx_msg void OnBnClickedItemMaiinpage();
afx_msg void OnPaint();
CMFCButton m_HomeButton;
CMFCButton m_ItemMasterButton;
CMFCButton m_CustomerButton;
CMFCButton m_BuyButton;
CMFCButton m_VendorButton;
CMFCButton m_PoButton;
CMFCButton m_BuildButton;
//CBrush m_brBK;
//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
afx_msg void OnSettingImportbom34077();
afx_msg void OnSettingDbconfig();
 
};
