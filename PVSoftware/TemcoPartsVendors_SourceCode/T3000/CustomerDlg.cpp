// CustomerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "CustomerDlg.h"
#include "afxdialogex.h"


// CCustomerDlg dialog

IMPLEMENT_DYNAMIC(CCustomerDlg, CDialogEx)

CCustomerDlg::CCustomerDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CCustomerDlg::IDD, pParent)
{

	//  m_CustomerName = _T("");
	//  m_CustomerAddress = _T("");
	m_StrCustomerName = _T("");
	m_StrCustomerAddress = _T("");
	m_StrCustomerNotes = _T("");
	m_StrCONName1 = _T("");
	m_StrCONPhone1 = _T("");
	m_StrCONEmail1 = _T("");
	m_StrCONEmail2 = _T("");
	m_StrCONFax = _T("");
	m_StrCustomerWebAddress = _T("");
	m_StrShipmentAddress = _T("");
	m_StrAccount = _T("");
	m_StrAccountCode = _T("");
	m_StrAccountFedID = _T("");
	m_StrAccountLocalID = _T("");
	m_StrCONName2 = _T("");
	m_StrCONPhone2 = _T("");
	m_StrAccountTerms = _T("");

	m_curRow = 0;
	m_curCol = 0;

	m_oldColorRow  = -1;
	m_curColorRow  = -1;
	m_StrSearchData = _T("");


	m_hide_show = FALSE;
}

CCustomerDlg::~CCustomerDlg()
{
}

void CCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_CUSTOMERNAME, m_StrCustomerName);
	DDX_Text(pDX, IDC_EDIT_CUADDRESS, m_StrCustomerAddress);
	DDX_Text(pDX, IDC_EDIT_CUNOTES, m_StrCustomerNotes);
	DDX_Text(pDX, IDC_EDIT_CNAME1, m_StrCONName1);
	DDX_Text(pDX, IDC_EDIT_CPHONE1, m_StrCONPhone1);
	DDX_Text(pDX, IDC_EDIT_EAMIL1, m_StrCONEmail1);
	DDX_Text(pDX, IDC_EDIT_EMAIL2, m_StrCONEmail2);
	DDX_Text(pDX, IDC_EDIT_FAX, m_StrCONFax);
	DDX_Text(pDX, IDC_EDIT_CUWEB, m_StrCustomerWebAddress);
	DDX_Text(pDX, IDC_EDIT_CUSHIPMENTADDRESS, m_StrShipmentAddress);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT2, m_StrAccount);
	DDX_Text(pDX, IDC_EDIT_CODE2, m_StrAccountCode);
	DDX_Text(pDX, IDC_EDIT_FEDID2, m_StrAccountFedID);
	DDX_Text(pDX, IDC_EDIT_LOCALID2, m_StrAccountLocalID);
	DDX_Text(pDX, IDC_EDIT_NAME2, m_StrCONName2);
	DDX_Text(pDX, IDC_EDIT_PHONE2, m_StrCONPhone2);
	DDX_Text(pDX, IDC_EDIT_TERMS2, m_StrAccountTerms);
	DDX_Control(pDX, IDC_LIST1, m_data_list);
	DDX_Text(pDX, IDC_EDIT_SEARCHDATA, m_StrSearchData);
	DDX_Control(pDX, IDC_CUSTOMERNAME, m_Combox_CustomerName);
}


BEGIN_MESSAGE_MAP(CCustomerDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CCustomerDlg::OnBnClickedOk)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_SHOW_HIDE, &CCustomerDlg::OnBnClickedShowHide)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CCustomerDlg::OnNMClickList1)
	ON_CBN_SELCHANGE(IDC_CUSTOMERNAME, &CCustomerDlg::OnCbnSelchangeCustomername)
	ON_BN_CLICKED(IDC_ADD, &CCustomerDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CCustomerDlg message handlers


void CCustomerDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	pn_table.Search_Customers(m_StrSearchData);
	m_curRow = 0;
	LoadData2List();
	m_Current_Customer = pn_table.m_dataset_Customer.at(m_curRow);
	DataBound();
}


void CCustomerDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    if(nType == SIZE_RESTORED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);

        if(m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(370, 50, ViewRect.Width(), ViewRect.Height() - 10), TRUE);
        }
    }
}


void CCustomerDlg::OnBnClickedShowHide()
{
	if(m_hide_show)
	{
		m_hide_show = FALSE;
		    GetDlgItem(IDC_STATIC_SALES_INFORMATION)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CUSTOMERNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_ADDR)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CUADDRESS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_WEB)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CUWEB)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CONTACTS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_NAME1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_PHONE1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EMAIL1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CNAME1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CPHONE1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_EAMIL1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_NAME2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_PHONE2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EMAIL2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_NAME2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_PHONE2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_EMAIL2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_FAX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_FAX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_ACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_ACCOUNT_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_TERMS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_ACCOUNT2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_TERMS2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CODE2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_FEDTAXID)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LOADID)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_FEDID2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LOCALID2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SHIPADDRESS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CUSHIPMENTADDRESS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_NOTES)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CUNOTES)->ShowWindow(SW_SHOW);
			CRect ViewRect;
			GetClientRect(&ViewRect);

			if(m_data_list.GetSafeHwnd())
			{
				m_data_list.MoveWindow(CRect(370, 50, ViewRect.Width(), ViewRect.Height() - 10), TRUE);
			}
			
	}
	else
	{
		GetDlgItem(IDC_STATIC_SALES_INFORMATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CUSTOMERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ADDR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CUADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_WEB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CUWEB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CONTACTS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NAME1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PHONE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_EMAIL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CNAME1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CPHONE1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_EAMIL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NAME2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PHONE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_EMAIL2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_NAME2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PHONE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_EMAIL2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FAX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_FAX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ACCOUNT_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TERMS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ACCOUNT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TERMS2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CODE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FEDTAXID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LOADID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_FEDID2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LOCALID2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SHIPADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CUSHIPMENTADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NOTES)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CUNOTES)->ShowWindow(SW_HIDE);
		m_hide_show = TRUE;


		CRect ViewRect;
		GetClientRect(&ViewRect);

		if(m_data_list.GetSafeHwnd())
		{
			m_data_list.MoveWindow(CRect(0, 50, ViewRect.Width(), ViewRect.Height() - 10), TRUE);
		}
	}
}

void CCustomerDlg::DataBound()
{
    m_StrCustomerName = m_Current_Customer.CUCustomer;
    m_StrCustomerAddress = m_Current_Customer.CUAddress;
    m_StrCustomerNotes = m_Current_Customer.CUNotes;
    m_StrCONName1 = m_Current_Customer.CUContact1;
    m_StrCONName2 = m_Current_Customer.CUContact2;
    m_StrCONPhone2 = m_Current_Customer.CUPhone2;
    m_StrCONPhone1 = m_Current_Customer.CUPhone1;
    m_StrCONEmail1 = m_Current_Customer.CUEmail1;
    m_StrCONEmail2 = m_Current_Customer.CUEmail2;
    m_StrCONFax = m_Current_Customer.CUFax;
    m_StrCustomerWebAddress = m_Current_Customer.CUWeb;
    m_StrShipmentAddress = m_Current_Customer.CUShipAddress;
    m_StrAccount = m_Current_Customer.CUAccount;
    m_StrAccountCode = m_Current_Customer.CUCode;
    m_StrAccountFedID = m_Current_Customer.CUFedTaxID;
    m_StrAccountLocalID = m_Current_Customer.CUStateTaxID;
    m_StrAccountTerms = m_Current_Customer.CUTerms;

    UpdateData(FALSE);
}


BOOL CCustomerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_data_list.ModifyStyle(0, LVS_SINGLESEL | LVS_REPORT | LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  | LVS_EX_GRIDLINES & (~LVS_EX_FULLROWSELECT)); //Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Client"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Address"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Web"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Contact1"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Phone1"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Email1"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Contact2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("Phone2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9, _T("Email2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(10, _T("Notes"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);


    g_hwnd_now = this->m_hWnd;

    CRect ViewRect;
    GetClientRect(&ViewRect);

    if(m_data_list.GetSafeHwnd())
    {
        m_data_list.MoveWindow(CRect(370, 50, ViewRect.Width(), ViewRect.Height() - 10), TRUE);
    }

    
   


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomerDlg::ShowData()
{
   if (pn_table.m_dataset_Customer.size()<1&&IsWindowVisible())
   {
	   pn_table.Search_Customers(m_StrSearchData);

	   LoadData2List();

	   if (pn_table.m_dataset_Customer.size()>0)
	   {
		   m_Current_Customer = pn_table.m_dataset_Customer.at(m_curRow);
		   DataBound();
	   }
   }
	
}

void CCustomerDlg::LoadData2List()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
	m_Combox_CustomerName.ResetContent();
    for (int i = 0 ; i < (int) pn_table.m_dataset_Customer.size(); i++)
    {
        strTemp.Format(_T("%d"), i + 1);
        m_data_list.InsertItem(i, strTemp);
        m_data_list.SetItemText(i, 1, pn_table.m_dataset_Customer.at(i).CUCustomer);
		m_Combox_CustomerName.AddString(pn_table.m_dataset_Customer.at(i).CUCustomer);
        m_data_list.SetItemText(i, 2, pn_table.m_dataset_Customer.at(i).CUAddress);
        m_data_list.SetItemText(i, 3, pn_table.m_dataset_Customer.at(i).CUWeb);
        m_data_list.SetItemText(i, 4, pn_table.m_dataset_Customer.at(i).CUContact1);
        m_data_list.SetItemText(i, 5, pn_table.m_dataset_Customer.at(i).CUPhone1);
        m_data_list.SetItemText(i, 6, pn_table.m_dataset_Customer.at(i).CUEmail1);
        m_data_list.SetItemText(i, 7, pn_table.m_dataset_Customer.at(i).CUContact2);
        m_data_list.SetItemText(i, 8, pn_table.m_dataset_Customer.at(i).CUPhone2);
        m_data_list.SetItemText(i, 9, pn_table.m_dataset_Customer.at(i).CUEmail2);
        m_data_list.SetItemText(i, 10, pn_table.m_dataset_Customer.at(i).CUNotes);
    }
}

void CCustomerDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    CString temp_cstring;
    long lRow, lCol;
    m_data_list.Set_Edit(true);
    DWORD dwPos = GetMessagePos(); //Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
    CPoint point(LOWORD(dwPos), HIWORD(dwPos));
    m_data_list.ScreenToClient(&point);
    LVHITTESTINFO lvinfo;
    lvinfo.pt = point;
    lvinfo.flags = LVHT_ABOVE;
    int nItem = m_data_list.SubItemHitTest(&lvinfo);

    lRow = lvinfo.iItem;
    lCol = lvinfo.iSubItem;

    m_curRow = lRow;
    m_curCol = lCol;

    if(lRow > m_data_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
        return;

    if(lRow < 0)
        return;




    if(lRow < pn_table.m_dataset_Customer.size())
    {


        m_oldColorRow = m_curColorRow;
        m_curColorRow = m_curRow;


        if(m_curColorRow != -1)
        {
            m_data_list.SetItemBkColor(m_curColorRow, -1, LIST_ITEM_SELECTED);
        }

        if(m_oldColorRow != -1)
        {
            m_data_list.SetItemBkColor(m_oldColorRow, -1, RGB(255, 255, 255));
        }

		m_Current_Customer = pn_table.m_dataset_Customer.at(m_curRow);

        DataBound();
        return  ;


        // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }
    *pResult = 0;
}


void CCustomerDlg::OnCbnSelchangeCustomername()
{
	m_curRow = m_Combox_CustomerName.GetCurSel();

	m_Current_Customer = pn_table.m_dataset_Customer.at(m_curRow);

	DataBound();
}

#include "PVNewClientDlg.h"

void CCustomerDlg::OnBnClickedAdd()
{
	CPVNewClientDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CString StrNewClient = dlg.m_strNewClient;
		CU_Struct TempStruct;
		TempStruct.CUCustomer = StrNewClient;
		if(!pn_table.Insert_CU(TempStruct))
		{
			AfxMessageBox(L"Insert Fail(Exsit or exceptions)");
			return;
		}

		pn_table.Search_Customers(m_StrSearchData);
		LoadData2List();
	}
	// TODO: Add your control notification handler code here
}
