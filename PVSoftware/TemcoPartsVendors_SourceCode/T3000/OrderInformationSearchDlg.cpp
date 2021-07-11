// OrderInformationSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OrderInformationSearchDlg.h"
#include "afxdialogex.h"
#include "T3000.h"

#define _OI_NO 0
#define _OI_PONUMBER 1
#define _OI_Supplier 2
#define _OI_Buyer 3
#define _OI_EngrgContact 4
#define _OI_TotalCost 5
#define _OI_PN 6
#define _OI_Description 7
#define _OI_Received 8
#define _OI_Cost 9
#define _OI_Qty 10
#define _OI_Unit 11
#define _OI_Extension 12


IMPLEMENT_DYNAMIC(COrderInformationSearchDlg, CDialogEx)

COrderInformationSearchDlg::COrderInformationSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PV_ORDER_INFORMAtION_SEARCH, pParent)
	, m_Vendor(_T(""))
	, m_partname(_T(""))
{
	type = 0;
}

COrderInformationSearchDlg::~COrderInformationSearchDlg()
{
}

void COrderInformationSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VENDORNAME, m_Vendor);
	DDX_Text(pDX, IDC_EDIT_PARTNAME, m_partname);
	DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(COrderInformationSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &COrderInformationSearchDlg::OnBnClickedButtonSearch)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COrderInformationSearchDlg message handlers


BOOL COrderInformationSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_data_list.ModifyStyle(0, LVS_SINGLESEL | LVS_REPORT | LVS_SHOWSELALWAYS);
	m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle() | LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
	m_data_list.InsertColumn(_OI_NO, _T("NO"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
	m_data_list.InsertColumn(_OI_PONUMBER, _T("PONumber"), 180, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Supplier, _T("Supplier"), 250, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Buyer, _T("Buyer"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_EngrgContact, _T("EngrgContact"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_TotalCost, _T("TotalCost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_PN, _T("PN"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Description, _T("Description"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Cost, _T("Cost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Qty, _T("Qty"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Extension, _T("Extension"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Received, _T("Received"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(_OI_Unit, _T("Unit"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	CRect ViewRect;
	GetClientRect(&ViewRect);
	if (m_data_list.GetSafeHwnd())
	{
		if (type == 0)
		{
			m_data_list.MoveWindow(CRect(0, 30, ViewRect.Width(), ViewRect.Height()), TRUE);
		}
		else
		{
			m_data_list.MoveWindow(CRect(0, 0, ViewRect.Width(), ViewRect.Height()), TRUE);
		}


	}
	if (type != 0)
	{
		GetDlgItem(IDC_STATIC_VENDORS)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_VENDORS2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VENDORNAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_PARTNAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(FALSE);
	 }
	else
	{
		GetDlgItem(IDC_STATIC_VENDORS)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_VENDORS2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VENDORNAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_PARTNAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->ShowWindow(TRUE);
	}
    OnBnClickedButtonSearch();
	 

	return TRUE;  
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COrderInformationSearchDlg::OnBnClickedButtonSearch()
{
	if (type == 0)
	{
		UpdateData(TRUE);
	}
	
	pn_table.Search_OrderInformation(m_Vendor, m_partname);

	CString  strTemp;
	m_data_list.DeleteAllItems();

	int i = 0;
	for (; i < (int)pn_table.m_dataset_SearchPO.size(); i++)
	{
		strTemp.Format(_T("%d"), i + 1);
		m_data_list.InsertItem(i, strTemp);

		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POMNumber);
		m_data_list.SetItemText(i, _OI_PONUMBER, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POMSupplier);
		m_data_list.SetItemText(i, _OI_Supplier, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POMFromBuyer);
		m_data_list.SetItemText(i, _OI_Buyer, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POMEngrgContact);
		m_data_list.SetItemText(i, _OI_EngrgContact, strTemp);
		strTemp.Format(_T("%0.2f"), pn_table.m_dataset_SearchPO.at(i).POMTotalCost);
		m_data_list.SetItemText(i, _OI_TotalCost, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POPart);
		m_data_list.SetItemText(i, _OI_PN, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).PODescription);
		m_data_list.SetItemText(i, _OI_Description, strTemp);
		strTemp.Format(_T("%0.3f"), pn_table.m_dataset_SearchPO.at(i).POCost);
		m_data_list.SetItemText(i, _OI_Cost, strTemp);
		strTemp.Format(_T("%0.1f"), pn_table.m_dataset_SearchPO.at(i).POQty);
		m_data_list.SetItemText(i, _OI_Qty, strTemp);
		strTemp.Format(_T("%0.1f %s"), pn_table.m_dataset_SearchPO.at(i).POExtension, pn_table.m_dataset_SearchPO.at(i).CURCurrencyChar);
		m_data_list.SetItemText(i, _OI_Extension, strTemp);
		strTemp.Format(_T("%0.1f"), pn_table.m_dataset_SearchPO.at(i).POReceived);
		m_data_list.SetItemText(i, _OI_Received, strTemp);
		strTemp.Format(_T("%s"), pn_table.m_dataset_SearchPO.at(i).POPurchUnits);
		m_data_list.SetItemText(i, _OI_Unit, strTemp);
	}

}


void COrderInformationSearchDlg::OnSize(UINT nType, int cx, int cy)
{
 
	CDialogEx::OnSize(nType, cx, cy);
	if (nType == SIZE_RESTORED)
	{

		CRect ViewRect;
		GetClientRect(&ViewRect);
		if (m_data_list.GetSafeHwnd())
		{
			if (type == 0)
			{
				m_data_list.MoveWindow(CRect(0, 30, ViewRect.Width(), ViewRect.Height()), TRUE);
			}
			else
			{
				m_data_list.MoveWindow(CRect(0, 0, ViewRect.Width(), ViewRect.Height()), TRUE);
			}
			

		}
		
		

	}
	// TODO: Add your message handler code here
}
