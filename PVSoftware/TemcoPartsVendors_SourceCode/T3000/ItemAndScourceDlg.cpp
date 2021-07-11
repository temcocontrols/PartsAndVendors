// ItemAndScourceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "ItemAndScourceDlg.h"
#include "afxdialogex.h"


// CItemAndScourceDlg dialog

IMPLEMENT_DYNAMIC(CItemAndScourceDlg, CDialogEx)

CItemAndScourceDlg::CItemAndScourceDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CItemAndScourceDlg::IDD, pParent)
{

    m_KeyWord = _T("");
    m_oldColorRow = -1;
    m_curColorRow = -1;
    m_curRow = -1;
    m_curCol = -1;
}

CItemAndScourceDlg::~CItemAndScourceDlg()
{
}

void CItemAndScourceDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SEARCH_LABEL, m_Label_Search);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    /*   DDX_Control(pDX, IDC_LIST2, m_select_data);*/
    DDX_Text(pDX, IDC_EDIT_SEARCH, m_KeyWord);
}


BEGIN_MESSAGE_MAP(CItemAndScourceDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CItemAndScourceDlg::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDOK, &CItemAndScourceDlg::OnBnClickedOk)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CItemAndScourceDlg::OnNMClickList1)
END_MESSAGE_MAP()



BOOL CItemAndScourceDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_Label_Search.SetWindowTextW(_T("PN,Title,Detail,Vendor>>"));
    m_Label_Search.textColor(RGB(0,0,0));
    m_Label_Search.setFont(30,15,NULL,_T("Arial"));

    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 40, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    //CString PartName;
    //CString PartTitle;
    //CString PartDetail;
    //CString Type;
    //CString VendorName;
    //CString VendorPN;
    //CString BuyAs;
    //CString Vendor_Description;
    //CString LeadTime;
    //int AtLevel;
    //float Cost;
    //CString Notes;
    m_data_list.InsertColumn(1, _T("Select"), 80, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Type"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Detail"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Vendor"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Vendor P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("Vendor Description"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9, _T("Buy AS"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(10, _T("Lead Time"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(11, _T("MOQ"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(12, _T("Unit Price"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    g_hwnd_now = this->m_hWnd;

   pn_table.Search_All_Parts_Vendors (m_KeyWord);
   LoadData2List ();
    return TRUE;
}
void CItemAndScourceDlg::LoadData2List ()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();

    for (int i=0; i<pn_table.m_dataset_PartsVendors.size(); i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);
        m_data_list.SetItemText(i,2,pn_table.m_dataset_PartsVendors.at(i).PartName);
        m_data_list.SetItemText(i,3,pn_table.m_dataset_PartsVendors.at(i).Type);
        m_data_list.SetItemText(i,4,pn_table.m_dataset_PartsVendors.at(i).PartTitle);
        m_data_list.SetItemText(i,5,pn_table.m_dataset_PartsVendors.at(i).PartDetail);
        m_data_list.SetItemText(i,6,pn_table.m_dataset_PartsVendors.at(i).VendorName);
        m_data_list.SetItemText(i,7,pn_table.m_dataset_PartsVendors.at(i).VendorPN);
        m_data_list.SetItemText(i,8,pn_table.m_dataset_PartsVendors.at(i).Vendor_Description);
        m_data_list.SetItemText(i,9,pn_table.m_dataset_PartsVendors.at(i).BuyAs);
        m_data_list.SetItemText(i,10,pn_table.m_dataset_PartsVendors.at(i).LeadTime);
        strTemp.Format (_T("%d"),pn_table.m_dataset_PartsVendors.at(i).AtLevel);
        m_data_list.SetItemText(i,11,strTemp);
        strTemp.Format (_T("%0.3f"),pn_table.m_dataset_PartsVendors.at(i).Cost);
        m_data_list.SetItemText(i,12,strTemp);

    }

}

void CItemAndScourceDlg::OnBnClickedButtonSearch()
{
    UpdateData (TRUE);
    pn_table.Search_All_Parts_Vendors (m_KeyWord);
    LoadData2List ();
}


void CItemAndScourceDlg::OnBnClickedOk()
{
    m_dataset_selector.clear ();
    for (int i = 0 ; i< m_data_list.GetRowCount (); i++)
    {

        BOOL Is_Select = m_data_list.GetCellChecked (i,1);
        if (Is_Select)
        {
            m_dataset_selector.push_back (pn_table.m_dataset_PartsVendors.at(i));
        }
    }



    CDialogEx::OnOK();
}


void CItemAndScourceDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
