// PVLinkVendorsItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVLinkVendorsItemDlg.h"
#include "afxdialogex.h"


// CPVLinkVendorsItemDlg dialog

IMPLEMENT_DYNAMIC(CPVLinkVendorsItemDlg, CDialogEx)

CPVLinkVendorsItemDlg::CPVLinkVendorsItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVLinkVendorsItemDlg::IDD, pParent)
    , m_StrVendorName(_T(""))
    , m_StrVendorCode(_T(""))
{
    m_oldColorRow = -1;
    m_curColorRow = -1;
       m_curRow = -1;
       m_curCol = -1;
}

CPVLinkVendorsItemDlg::~CPVLinkVendorsItemDlg()
{
}

void CPVLinkVendorsItemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_VENDOR_NAME, m_StrVendorName);
    DDX_Text(pDX, IDC_EDIT_VENDOR_CODE, m_StrVendorCode);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(CPVLinkVendorsItemDlg, CDialogEx)
    ON_BN_CLICKED(IDC_SEARCH, &CPVLinkVendorsItemDlg::OnBnClickedSearch)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVLinkVendorsItemDlg::OnNMDblclkList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVLinkVendorsItemDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPVLinkVendorsItemDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CPVLinkVendorsItemDlg message handlers


BOOL CPVLinkVendorsItemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    while(m_data_list.DeleteColumn(0));
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Vendor Name"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Code"), 150, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Contact"),150, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Phone"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    pn_table.Search_Vendors (m_StrVendorName);
    Load_DataToList(); 

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPVLinkVendorsItemDlg::Load_DataToList ()
{             
    CString  strTemp;
     m_data_list.DeleteAllItems();
    for (int row=0;row<(int)pn_table.m_dataset_vendor.size();row++)
    {
        strTemp.Format(_T("%d"),row+1);
        m_data_list.InsertItem(row,strTemp);
        strTemp=pn_table.m_dataset_vendor.at(row).SUSupplier;
        m_data_list.SetItemText(row,1,strTemp);
        strTemp=pn_table.m_dataset_vendor.at(row).SUCode;
        m_data_list.SetItemText(row,2,strTemp);
        strTemp=pn_table.m_dataset_vendor.at(row).SUContact1;
        m_data_list.SetItemText(row,3,strTemp);
        strTemp=pn_table.m_dataset_vendor.at(row).SUPhone1;
        m_data_list.SetItemText(row,4,strTemp);
    }
}


void CPVLinkVendorsItemDlg::OnBnClickedSearch()
{
        UpdateData (TRUE);
		 
        pn_table.Search_Vendor(m_StrVendorName);
        Load_DataToList();
}


void CPVLinkVendorsItemDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    CString temp_cstring;
    long lRow,lCol;
    m_data_list.Set_Edit(true);
    DWORD dwPos=GetMessagePos();//Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
    CPoint point( LOWORD(dwPos), HIWORD(dwPos));
    m_data_list.ScreenToClient(&point);
    LVHITTESTINFO lvinfo;
    lvinfo.pt=point;
    lvinfo.flags=LVHT_ABOVE;
    int nItem=m_data_list.SubItemHitTest(&lvinfo);

    lRow = lvinfo.iItem;
    lCol = lvinfo.iSubItem;

    m_curRow=lRow;
    m_curCol=lCol;
    if(lRow>m_data_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
        return;
    if(lRow<0)
        return;

    if(lRow<pn_table.m_dataset_vendor.size())
    {
        /*CNewPNDlg dlg;
        dlg.m_new_item = 2;
        dlg.m_item = pn_table.pv_Table_PN.at(m_curRow);
        dlg.DoModal();*/
        if (lCol == 0)
        {
            m_data_list.SetItemBkColor(lRow,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);
        }
        ::PostMessage (m_message_handle,WM_MESSAGE_ADD_VENDORS_ITEM,pn_table.m_dataset_vendor.at(m_curRow).SUID,0);
    }
    
    *pResult = 0;
}


void CPVLinkVendorsItemDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    CString temp_cstring;
    long lRow,lCol;
    m_data_list.Set_Edit(true);
    DWORD dwPos=GetMessagePos();
    //Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
    CPoint point( LOWORD(dwPos), HIWORD(dwPos));
    m_data_list.ScreenToClient(&point);
    LVHITTESTINFO lvinfo;
    lvinfo.pt=point;
    lvinfo.flags=LVHT_ABOVE;
    int nItem=m_data_list.SubItemHitTest(&lvinfo);

    lRow = lvinfo.iItem;
    lCol = lvinfo.iSubItem;
 
    m_curRow=lRow;

    m_curCol=lCol;
    if(lRow>m_data_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
        return;
    if(lRow<0)
        return;
    CString New_CString;
    CString temp_task_info;

    CString temp1;
    CStringArray temparray;

    if (lCol == 0)
    {

        m_oldColorRow = m_curColorRow;
        m_curColorRow = m_curRow;


        if (m_curColorRow != -1)
        {
            m_data_list.SetItemBkColor (m_curColorRow,-1,LIST_ITEM_SELECTED);
        }

        if (m_oldColorRow != -1)
        {
            m_data_list.SetItemBkColor (m_oldColorRow,-1,RGB(255,255,255));
        }

    }


    *pResult = 0;
}

#include "PVDetailedVendorDlg.h"
void CPVLinkVendorsItemDlg::OnBnClickedButtonAdd()
{
	CPVDetailedVendorDlg dlg;
	dlg.m_isCreate = TRUE;
	dlg.DoModal ();
	pn_table.Search_Vendors (m_StrVendorName);
	Load_DataToList(); 
}
