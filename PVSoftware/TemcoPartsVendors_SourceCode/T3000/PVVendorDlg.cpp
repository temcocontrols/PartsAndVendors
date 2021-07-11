// PVVendorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVVendorDlg.h"
#include "afxdialogex.h"
#include "PVDetailedVendorDlg.h"

// CPVVendorDlg dialog

IMPLEMENT_DYNAMIC(CPVVendorDlg, CDialogEx)

CPVVendorDlg::CPVVendorDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVVendorDlg::IDD, pParent)
    , m_strVendorName(_T(""))
{
    m_oldColorRow = -1;
    m_curColorRow = -1;

    m_curRow = -1;
    m_curCol = -1;
}

CPVVendorDlg::~CPVVendorDlg()
{
}

void CPVVendorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Text(pDX, IDC_EDIT_VENDOR_NAME, m_strVendorName);
}


BEGIN_MESSAGE_MAP(CPVVendorDlg, CDialogEx)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BUTTON_NEW, &CPVVendorDlg::OnBnClickedButtonNew)
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPVVendorDlg::OnNMRClickList1)
    ON_COMMAND(ID_VENDORS_MAINTAINVENDORS, &CPVVendorDlg::OnVendorsMaintainvendors)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CPVVendorDlg::OnBnClickedButtonDel)
    ON_COMMAND(ID_VENDORS_DELETEVENDOR, &CPVVendorDlg::OnVendorsDeletevendor)
    ON_COMMAND(ID_VENDORS_NEWVENDOR, &CPVVendorDlg::OnVendorsNewvendor)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVVendorDlg::OnNMClickList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVVendorDlg::OnNMDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CPVVendorDlg::OnBnClickedButtonChange)
    ON_BN_CLICKED(IDOK, &CPVVendorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PO, &CPVVendorDlg::OnBnClickedButtonShowPo)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_VENDOR_PRICE, &CPVVendorDlg::OnBnClickedButtonEditVendorPrice)
END_MESSAGE_MAP()


// CPVVendorDlg message handlers
BOOL CPVVendorDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CRect ViewRect;
    GetClientRect(&ViewRect);
    //CRect listRect;
    // m_data_list.GetClientRect(&listRect);
    if (m_data_list.GetSafeHwnd())
    {
        m_data_list.MoveWindow(CRect(0,50/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
    }
    while(m_data_list.DeleteColumn(0));
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Vendor"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Address"), 300, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Phone1"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Phone2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Fax"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("CustAcct"), 150, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Contact1"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("Contact2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    



    return TRUE;

}
void  CPVVendorDlg::ShowData()
{
   if (pn_table.m_dataset_vendor.size()<1&&IsWindowVisible())
   {
	   pn_table.Search_Vendor(m_strVendorName);
	   Load_DataToList ();
   }
	
}
void CPVVendorDlg::Load_DataToList()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
    for (int row = 0; row<(int)pn_table.m_dataset_vendor.size(); row++)
    {
        strTemp.Format(_T("%d"),row+1);
        m_data_list.InsertItem(row,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUSupplier;
        m_data_list.SetItemText(row,1,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUAddress;
        strTemp.Replace('\r',',');
        strTemp.Replace('\n',' ');
        m_data_list.SetItemText(row,2,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUPhone1;
        m_data_list.SetItemText(row,3,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUPhone2;
        m_data_list.SetItemText(row,4,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUFAX;
        m_data_list.SetItemText(row,5,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUAccount;
        m_data_list.SetItemText(row,6,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUContact1;
        m_data_list.SetItemText(row,7,strTemp);
        strTemp = pn_table.m_dataset_vendor.at(row).SUContact2;
        m_data_list.SetItemText(row,8,strTemp);
    }
}

void CPVVendorDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (nType==SIZE_RESTORED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);
        //         CRect listRect;
        //         m_data_list.GetClientRect(&listRect);
        if (m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(0,30/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
        }
    }
    // TODO: Add your message handler code here
}


void CPVVendorDlg::OnBnClickedButtonNew()
{
    CPVDetailedVendorDlg dlg;
    dlg.m_isCreate = TRUE;
    dlg.DoModal ();
    pn_table.Search_Vendor(m_strVendorName);
    Load_DataToList ();
}


void CPVVendorDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
    CString New_CString;
    CString temp_task_info;

    CString temp1;
    CStringArray temparray;

    if (1==lCol)
    {
        CMenu menu;
        menu.LoadMenu(IDR_MENU_PV_VENDOR);
        CMenu *pmenu=menu.GetSubMenu(0);
        CPoint point;
        GetCursorPos(&point);
        pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);
    }
    *pResult = 0;
}
 
void CPVVendorDlg::OnVendorsMaintainvendors()
{
    CPVDetailedVendorDlg dlg;
    dlg.m_isCreate = FALSE;
    dlg.m_SuItem = pn_table.m_dataset_vendor.at(m_curRow);
    dlg.DoModal ();
 pn_table.Search_Vendor(m_strVendorName);
    Load_DataToList ();
}


void CPVVendorDlg::OnBnClickedButtonDel()
{
    pn_table.Delete_Vendor (pn_table.m_dataset_vendor.at(m_curRow));
    pn_table.Search_Vendor(m_strVendorName);
    Load_DataToList ();
}


void CPVVendorDlg::OnVendorsDeletevendor()
{
    pn_table.Delete_Vendor (pn_table.m_dataset_vendor.at(m_curRow));
   pn_table.Search_Vendor(m_strVendorName);
    Load_DataToList ();
}


void CPVVendorDlg::OnVendorsNewvendor()
{
    CPVDetailedVendorDlg dlg;
    dlg.m_isCreate = TRUE;
    dlg.DoModal ();
  pn_table.Search_Vendor(m_strVendorName);
    Load_DataToList ();
}


void CPVVendorDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

//     if (lCol == 0)
//     {

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

/*    }*/


    *pResult = 0;
}


void CPVVendorDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: Add your control notification handler code here
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


    if (m_curRow <pn_table.m_dataset_vendor.size () )
    {

//         m_oldColorRow = m_curColorRow;
//         m_curColorRow = m_curRow;
// 
// 
//         if (m_curColorRow != -1)
//         {
//             m_data_list.SetItemBkColor (m_curColorRow,-1,LIST_ITEM_SELECTED);
//         }
// 
//         if (m_oldColorRow != -1)
//         {
//             m_data_list.SetItemBkColor (m_oldColorRow,-1,RGB(255,255,255));
//         }

        CPVDetailedVendorDlg dlg;
        dlg.m_isCreate = FALSE;
        dlg.m_SuItem = pn_table.m_dataset_vendor.at(m_curRow);
        if (IDOK == dlg.DoModal ())
        {
               pn_table.Search_Vendor(m_strVendorName);
               Load_DataToList ();

        }
      //  dlg.DoModal ();

    }


    

    *pResult = 0;
}


void CPVVendorDlg::OnBnClickedButtonChange()
{
	if(pn_table.m_dataset_vendor.size()<=0)
	{
		return;
	}
    CPVDetailedVendorDlg dlg;
    dlg.m_isCreate = FALSE;
    dlg.m_SuItem = pn_table.m_dataset_vendor.at(m_curRow);
    if(IDOK == dlg.DoModal ())
    {
        pn_table.Search_Vendor(m_strVendorName);

        Load_DataToList ();
    }
}


void CPVVendorDlg::OnBnClickedOk()
{
    UpdateData (TRUE);
    pn_table.Search_Vendor(m_strVendorName);

    Load_DataToList ();
}
#include "OrderInformationSearchDlg.h"

void CPVVendorDlg::OnBnClickedButtonShowPo()
{
	COrderInformationSearchDlg dlg;
	dlg.m_Vendor = pn_table.m_dataset_vendor.at(m_curRow).SUSupplier;
	dlg.type = 1;
	dlg.DoModal();
}

#include "excel9.h"
void CPVVendorDlg::OnBnClickedButtonEditVendorPrice()
{
	CString strFilter;
	CString strFilename;
	_Application app;
	Workbooks books;
	_Workbook book;
	Worksheets sheets;
	_Worksheet sheet;
	Range range;
	Range rgMyRge1, rgMyRge2;
	COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	Sleep(2000);
	if (!app.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("Create Excel false!"));
		return;
	}
	//遍历所有行  
	strFilename = g_strExePth + _T("PVExportData.xls");
	books.AttachDispatch(app.GetWorkbooks());
	book.AttachDispatch(books.Add(_variant_t(strFilename)));
	sheets.AttachDispatch(book.GetWorksheets());
	sheet.AttachDispatch(sheets.GetItem(_variant_t("Sheet1")));
	range.AttachDispatch(sheet.GetCells()); 
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(1)), _variant_t(L"VendorName"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(2)), _variant_t(L"Address"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(3)), _variant_t(L"Phone1"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(4)), _variant_t(L"Phone2"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(5)), _variant_t(L"Fax"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(6)), _variant_t(L"Account"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(7)), _variant_t(L"Contact1"));
	range.SetItem(_variant_t((long)(1)), _variant_t((long)(8)), _variant_t(L"Contact2"));
	int RowNumber = 1;
	for (std::vector<SU_Struct>::iterator itor = pn_table.m_dataset_vendor.begin(); itor != pn_table.m_dataset_vendor.end(); itor++)
	{
		++RowNumber;
		 
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(1)), _variant_t(itor->SUSupplier));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(2)), _variant_t(itor->SUAddress));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(3)), _variant_t(itor->SUPhone1));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(4)), _variant_t(itor->SUPhone2));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(5)), _variant_t(itor->SUFAX));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(6)), _variant_t(itor->SUAccount));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(7)), _variant_t(itor->SUContact1));
		range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(8)), _variant_t(itor->SUContact2));
	 
	}
	app.SetVisible(true);
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();



	 
}
