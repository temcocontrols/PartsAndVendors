// PVItemMasterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVItemMasterDlg.h"
#include "afxdialogex.h"
#include "PVBOMDlg.h"
#include "NewPNDlg.h"
#include "PartVendorQuotationDlg.h"
#include "AssyTreeDlg.h"
#include "OrderInformationSearchDlg.h"
IMPLEMENT_DYNAMIC(CPVItemMasterDlg, CDialogEx)

CPVItemMasterDlg::CPVItemMasterDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVItemMasterDlg::IDD, pParent)
    , m_strPN(_T(""))
    , m_strType(_T(""))
{
    m_curRow = -1;
    m_curCol = -1;
    m_oldColorRow = -1;
    m_curColorRow = -1;
    PartWindow = NULL;
    PartQuatationWindow = NULL;



}

CPVItemMasterDlg::~CPVItemMasterDlg()
{
    delete PartWindow;
    PartWindow = NULL;
    delete PartQuatationWindow;
    PartQuatationWindow = NULL;
	m_currentpagenumber = 1;
}

void CPVItemMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_data_list);
	DDX_Text(pDX, IDC_EDIT_PN, m_strPN);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
	DDX_Control(pDX, IDC_COMBO_NUMBER, m_combox_pagenumber);
}


BEGIN_MESSAGE_MAP(CPVItemMasterDlg, CDialogEx)
    ON_BN_CLICKED(IDC_SEARCH, &CPVItemMasterDlg::OnBnClickedSearch)
    ON_WM_SIZE()
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPVItemMasterDlg::OnNMRClickList1)
    ON_COMMAND(ID_PARTS_CHECKBOM, &CPVItemMasterDlg::OnPartsCheckbom)
    ON_COMMAND(ID_PARTS_COPYNEWITEM, &CPVItemMasterDlg::OnPartsCopynewitem)
    ON_COMMAND(ID_PN_NEWPN, &CPVItemMasterDlg::OnPnNewpn)
    ON_COMMAND(ID_PARTS_OPEN, &CPVItemMasterDlg::OnPartsOpen)
    ON_COMMAND(ID_PARTS_DELETEITEM, &CPVItemMasterDlg::OnPartsDeleteitem)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVItemMasterDlg::OnNMDblclkList1)
    ON_COMMAND(ID_PARTS_MAINTAINVENDOR, &CPVItemMasterDlg::OnPartsMaintainvendor)
//    ON_NOTIFY(HDN_ITEMCLICK, 0, &CPVItemMasterDlg::OnHdnItemclickList1)
    ON_COMMAND(ID_PARTS_SHOWASSBLYTREE, &CPVItemMasterDlg::OnPartsShowassblytree)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVItemMasterDlg::OnNMClickList1)
	ON_COMMAND(ID_MAINTAINITEM_DELETESELECTEDITEMS, &CPVItemMasterDlg::OnMaintainitemDeleteselecteditems)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPVItemMasterDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_PARTS_SHOWPOHISTORY, &CPVItemMasterDlg::OnPartsShowpohistory)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CPVItemMasterDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CPVItemMasterDlg::OnBnClickedButtonDown)
	ON_COMMAND(ID_PARTS_EXPORTDATA, &CPVItemMasterDlg::OnPartsExportdata)
	ON_CBN_SELCHANGE(IDC_COMBO_NUMBER, &CPVItemMasterDlg::OnCbnSelchangeComboNumber)
END_MESSAGE_MAP()


// CPVItemMasterDlg message handlers


BOOL CPVItemMasterDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
	GetDlgItem(IDC_COMBO_NUMBER)->SetWindowTextW(L"20");
	m_combox_pagenumber.SetCurSel(0);
	m_currentpagenumber = 1;
	m_num=0;
	m_select=1;
	m_havevendor = 2;
	m_isorded = 3;
	m_pn=4;
	m_type=5;
	m_title=6;
	m_detail=7;
	m_rev=8;
	m_stat=9;
	m_cost=10;
	m_brand_vendor = 11;
	m_catalog=12;
	m_power=13;
	m_voltage=14;
	m_tolerance=15;
	m_part_type=16;
	m_schematic_part=17;
	m_allegro_footprint=18;
	m_solidworks=19;
    while(m_data_list.DeleteColumn(0));
    m_data_list.ModifyStyle(0, LVS_REPORT|LVS_SHOWSELALWAYS);

    //m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));

    m_data_list.InsertColumn(m_num, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
	m_data_list.InsertColumn(m_select, _T(""), 25, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_havevendor, _T("Have Vendor"), 80, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_isorded, _T("Orded"), 60, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_pn, _T("P/N"), 140, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_type, _T("Type"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_title, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_detail, _T("Detail"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_rev, _T("Rev"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_stat, _T("Stat"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_cost, _T("Cur.Cost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	
	m_data_list.InsertColumn(m_brand_vendor, _T("Brand Vendor"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_catalog, _T("Catalog"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	
	m_data_list.InsertColumn(m_power, _T("Power"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_voltage, _T("Voltage"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

	m_data_list.InsertColumn(m_tolerance, _T("Tolerance"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_part_type, _T("Part Type"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

	m_data_list.InsertColumn(m_schematic_part, _T("Schematic Part"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(m_allegro_footprint, _T("Allegro Footprint"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

	m_data_list.InsertColumn(m_solidworks, _T("Solidworks"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

    CRect ViewRect;
    GetClientRect(&ViewRect);
    // CRect listRect;
    //m_data_list.GetClientRect(&listRect);
 //   if (m_data_list.GetSafeHwnd())
 //   {
 //       m_data_list.MoveWindow(CRect(0,30/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
 //   }
	//pn_table.Search_Data_ByPN(m_strPN,m_strType,TRUE);

	//Load_DataToList();
    
    return TRUE;   
}
void CPVItemMasterDlg::ShowData()
{
	if (IsWindowVisible())
	{
		CString PageNumber;
		GetDlgItem(IDC_COMBO_NUMBER)->GetWindowTextW(PageNumber);
		if (PageNumber.GetLength()<=0)
		{
			PageNumber = L"20";
		}
		CString strcurrentpage;
		strcurrentpage.Format(_T("%d"), m_currentpagenumber);
		pn_table.Search_Data_ByPN(m_strPN,m_strType, PageNumber, strcurrentpage);

		Load_DataToList();
	}
}

void CPVItemMasterDlg::Load_DataToList()
{

    // pn_table.Initial_Data();
    CString  strTemp;
	GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(L"Loading Data......");
   // m_data_list.DeleteAllItems();
	if (m_data_list.GetRowCount()<(int)pn_table.pv_Table_PN.size())
	{
	    for (int row =m_data_list.GetRowCount();row <(int) pn_table.pv_Table_PN.size();row ++)
	    {
		   m_data_list.InsertItem(row,L"");
	    }	
	}
	else
	{
		for (int row =0;row <m_data_list.GetRowCount()-(int) pn_table.pv_Table_PN.size();row ++)
		{
			m_data_list.DeleteItem(0);
		}	
	}
    for (int row = 0; row<(int)pn_table.pv_Table_PN.size(); row++)
    {
	    if (row%2 == 0)
	    {
			GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(L"Loading Data..");
	    } 
		else if (row %3 ==0 )
		{
		    GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(L"Loading Data...");
		}
	    else
	    {
		   GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(L"Loading Data.....");
	    }
        strTemp.Format(_T("%d"),row+1);
        m_data_list.SetItemText(row,m_num,strTemp);
		m_data_list.SetCellChecked(row, m_havevendor, pn_table.pv_Table_PN.at(row).Is_HaveVendor);
		m_data_list.SetCellChecked(row, m_isorded, pn_table.pv_Table_PN.at(row).Is_Ordered);
        strTemp=pn_table.pv_Table_PN.at(row).PNPartNumber;
        m_data_list.SetItemText(row,m_pn,strTemp);
        strTemp=pn_table.pv_Table_PN.at(row).PNType;
        m_data_list.SetItemText(row,m_type,strTemp);
        strTemp=pn_table.pv_Table_PN.at(row).PNTitle;
        m_data_list.SetItemText(row,m_title,strTemp);
        strTemp=pn_table.pv_Table_PN.at(row).PNDetail;
        m_data_list.SetItemText(row,m_detail,strTemp);
        strTemp=pn_table.pv_Table_PN.at(row).PNRevision;
        m_data_list.SetItemText(row,m_rev,strTemp);
        strTemp=pn_table.pv_Table_PN.at(row).PNStatus;
        m_data_list.SetItemText(row,m_stat,strTemp);
        strTemp.Format(_T("%0.3f"),pn_table.pv_Table_PN.at(row).PNCurrentCost);
        m_data_list.SetItemText(row,m_cost,strTemp);

		strTemp=pn_table.pv_Table_PN.at(row).Brand_Vendor;
		m_data_list.SetItemText(row,m_brand_vendor,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Catalog;
		m_data_list.SetItemText(row,m_catalog,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Power;
		m_data_list.SetItemText(row,m_power,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Voltage;
		m_data_list.SetItemText(row,m_voltage,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Tolerance;
		m_data_list.SetItemText(row,m_tolerance,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Part_type;
		m_data_list.SetItemText(row,m_part_type,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Schematic_part;
		m_data_list.SetItemText(row,m_schematic_part,strTemp);

		strTemp=pn_table.pv_Table_PN.at(row).Allegro_footprint;
		m_data_list.SetItemText(row,m_allegro_footprint,strTemp);
		strTemp=pn_table.pv_Table_PN.at(row).Solidworks;
		m_data_list.SetItemText(row,m_solidworks,strTemp);


    }
	GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(L"");
	strTemp.Format(_T("Records=%d"),pn_table.pv_Table_PN.size());
	GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowTextW(strTemp);
}

void CPVItemMasterDlg::OnBnClickedSearch()
{
    UpdateData(TRUE);
    m_strPN.TrimLeft ();
    m_strPN.TrimRight ();
    m_strType.TrimLeft ();
    m_strType.TrimRight ();
    if (m_strType.CompareNoCase (_T("All"))==0)
    {
        m_strType = _T("");
    }              //  m_strType
   /* pn_table.Search_ALLPN(m_strPN);
	Load_DataToList();*/
	ShowData();
}


void CPVItemMasterDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (nType==SIZE_RESTORED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);
        //CRect listRect;
        // m_data_list.GetClientRect(&listRect);
        if (m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(0,30/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
        }

    }
    // TODO: Add your message handler code here
}


void CPVItemMasterDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


    if (TRUE)
    {

        CMenu menu;
        menu.LoadMenu(IDR_MENU_PV_MAIN);
        CMenu *pmenu=menu.GetSubMenu(0);
        CPoint point;
        GetCursorPos(&point);
        pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);

    }
    else
    {
        return;
    }
    *pResult = 0;

}


void CPVItemMasterDlg::OnPartsCheckbom()
{
    CPVBOMDlg pvbomdlg;
    pvbomdlg.m_PN_ID = pn_table.pv_Table_PN.at(m_curRow).PNID;
	pvbomdlg.m_strPNumber =pn_table.pv_Table_PN.at(m_curRow).PNPartNumber;
    CString Title;
    Title.Format (_T("Bom List:%s"),pn_table.pv_Table_PN.at(m_curRow).PNPartNumber);
    pvbomdlg.Title = Title;
    // pvbomdlg.SetWindowTextW(Title);
    pvbomdlg.DoModal();
}


void CPVItemMasterDlg::OnPartsCopynewitem()
{
    if (m_curRow<pn_table.pv_Table_PN.size())
    {
        CNewPNDlg dlg;
        dlg.m_new_item = 1;
        dlg.m_item = pn_table.pv_Table_PN.at(m_curRow);
        dlg.m_saveCloseWindow = TRUE;
        dlg.DoModal();
    }

}


void CPVItemMasterDlg::OnPnNewpn()
{
    CNewPNDlg dlg;
    dlg.m_new_item = 0;
    dlg.m_saveCloseWindow = TRUE;
    dlg.DoModal();
}


void CPVItemMasterDlg::OnPartsOpen()
{
    if(m_curRow<pn_table.pv_Table_PN.size())
    {
		if (PartWindow==NULL)
		{
			PartWindow=new CNewPNDlg;
			PartWindow->Create(IDD_PV_NEW_PN, this);
			PartWindow->m_hParentWnd = this->m_hWnd;
		}
		 
		PartWindow->m_new_item = 2;
		PartWindow->m_item = pn_table.pv_Table_PN.at(m_curRow);
		PartWindow->ShowWindow (TRUE);
    }
}
void CPVItemMasterDlg::OnPartsDeleteitem()
{
    int PNID = pn_table.pv_Table_PN.at(m_curRow).PNID;
    pn_table.Delete_ByPN(PNID);
    pn_table.Initial_Data();
    m_data_list.DeleteItem(m_curRow);
    // Load_DataToList();
}


void CPVItemMasterDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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

    FreshAllWindows ();
    *pResult = 0;
}


void CPVItemMasterDlg::OnPartsMaintainvendor()
{
    CPartVendorQuotationDlg dlg;
    dlg.m_PN_ID = pn_table.pv_Table_PN.at(m_curRow).PNID;
    CString Title;
    Title.Format (_T("Part's Quatation List:%s"),pn_table.pv_Table_PN.at(m_curRow).PNPartNumber);

    dlg.Title = Title;
    if (dlg.DoModal () == IDOK)
    {
        PN_Struct  update_item = pn_table.pv_Table_PN.at(m_curRow); //  / dlg.m_datasector.BuyAs
        pn_table.Initial_UN ();
        int convert_unit = -1;
        for (int i = 0; i<pn_table.m_dataset_UN.size (); i++)
        {
            if (pn_table.m_dataset_UN.at(i).UNPurchUnits.CompareNoCase(dlg.m_datasector.BuyAs) == 0)
            {
                convert_unit =   pn_table.m_dataset_UN.at(i).UNConvUnits;
                update_item.PNCurrentCost = dlg.m_datasector.Cost/convert_unit;
                pn_table.Update_ByPN (update_item);
				/* pn_table.Initial_Data ();
				Load_DataToList ();*/
				//pn_table.Search_ALLPN(m_strPN);
				//Load_DataToList();
				ShowData();
                break;
            }
        }



    }


}
 
//void CPVItemMasterDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//    LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//    // TODO: Add your control notification handler code here
//
//
//    CString temp_cstring;
//    long lRow,lCol;
//    m_data_list.Set_Edit(true);
//    DWORD dwPos=GetMessagePos();
//    //Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
//    CPoint point( LOWORD(dwPos), HIWORD(dwPos));
//    m_data_list.ScreenToClient(&point);
//    LVHITTESTINFO lvinfo;
//    lvinfo.pt=point;
//    lvinfo.flags=LVHT_ABOVE;
//    int nItem=m_data_list.SubItemHitTest(&lvinfo);
//
//    lRow = lvinfo.iItem;
//    lCol = lvinfo.iSubItem;
//
//    m_curRow=lRow;
//    m_curCol=lCol;
//    if(lRow>m_data_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
//        return;
//    if(lRow<0)
//        return;
//    CString New_CString;
//    CString temp_task_info;
//
//    CString temp1;
//    CStringArray temparray;
//
//      if (m_curCol == 1)
//      {
//         LPRECT rect;
//         m_data_list.GetItemRect (m_curCol,rect,0);
//      }
//
//    *pResult = 0;
//}



void CPVItemMasterDlg::OnPartsShowassblytree()
{
    int PNID = pn_table.pv_Table_PN.at(m_curRow).PNID;
    CAssyTreeDlg dlg;
    dlg.m_PNID =  PNID;
    dlg.PNName = pn_table.pv_Table_PN.at(m_curRow).PNPartNumber;
    CString Title;
    Title.Format (_T("Assy Tree List For %s"),pn_table.pv_Table_PN.at(m_curRow).PNPartNumber);
    dlg.m_title = Title;
    dlg.DoModal ();
}


void CPVItemMasterDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	if (lCol!=m_select)
	{
    //	 FreshAllWindows ();
	}
	if (m_curRow < pn_table.pv_Table_PN.size ())
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

     m_data_list.SetFocus ();

    *pResult = 0;
}

void CPVItemMasterDlg::FreshAllWindows ()
{
    if (m_curRow < pn_table.pv_Table_PN.size ())
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
		if (PartWindow==NULL)
		{
			PartWindow=new CNewPNDlg;
			PartWindow->Create(IDD_PV_NEW_PN, this);
			PartWindow->m_hParentWnd = this->m_hWnd;
		}

	/*	if (PartQuatationWindow == NULL)
		{
			PartQuatationWindow = new CPartVendorQuotationDlg;
			PartQuatationWindow->Create (CPartVendorQuotationDlg::IDD,this);
			PartQuatationWindow->m_hParentWnd = this->m_hWnd;
		}*/

         PartWindow->m_hParentWnd = this->m_hWnd;
       
        if(m_curRow<pn_table.pv_Table_PN.size())
        {

            PartWindow->m_new_item = 2;
            PartWindow->m_item = pn_table.pv_Table_PN.at(m_curRow);
            PartWindow->m_index = m_curRow;
            
            if (!PartWindow->IsWindowVisible ())
            {
                PartWindow->ShowWindow (TRUE);
                ::PostMessageA (PartWindow->m_hWnd,WM_MESSAGE_FRESH_PN_DETAIL,0,0);
            }
            else
            {
                ::PostMessageA (PartWindow->m_hWnd,WM_MESSAGE_FRESH_PN_DETAIL,0,0);
            }

           /* PartQuatationWindow->m_PN_ID = pn_table.pv_Table_PN.at(m_curRow).PNID;
            if (!PartQuatationWindow->IsWindowVisible ())
            {
                PartQuatationWindow->ShowWindow (TRUE);
                ::PostMessageA (PartQuatationWindow->m_hWnd,WM_MESSAGE_ITEM_VENDORS_LIST,0,0);
            }                                                                                           
            else
            {
                ::PostMessageA (PartQuatationWindow->m_hWnd,WM_MESSAGE_ITEM_VENDORS_LIST,0,0);
            }*/

        }

    }
}

LRESULT CPVItemMasterDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if (message == WM_MESSAGE_ITEM_MASTER)
    {
        // pn_table.Search_Data_ByPN(m_strPN,m_strType);
        Load_DataToList();
    }

    if (message == WM_MESSAGE_ITEM_RELOAD_ALLDATA)
    {
		/* pn_table.Search_Data_ByPN(m_strPN,m_strType);
		 Load_DataToList();*/
		ShowData();
    }
    return CDialogEx::WindowProc(message, wParam, lParam);
}


BOOL CPVItemMasterDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if(pMsg->message==WM_KEYDOWN)
    {
        if(GetFocus()->GetDlgCtrlID() == IDC_LIST1)
        {

           
            switch(pMsg->wParam)
            {
            case VK_UP:
            {
                if (m_curRow < pn_table.pv_Table_PN.size ())
                {
                    m_curRow--;
                }
                else
                {
                    m_curRow =pn_table.pv_Table_PN.size ()-1;
                }
                FreshAllWindows ();
            }
            break;

            case VK_DOWN:
            {
                if (m_curRow < pn_table.pv_Table_PN.size ())
                {
                    m_curRow++;
                }
                else
                {
                    m_curRow =0;
                }

                FreshAllWindows ();
            }
            break;
            }



            return TRUE;
        }

        if (pMsg->wParam ==VK_RETURN)
        {
             OnBnClickedSearch();
             return TRUE;
        }
    }

   

    return CDialogEx::PreTranslateMessage(pMsg);
}


void CPVItemMasterDlg::OnMaintainitemDeleteselecteditems()
{
   vector<int> m_vecPNID;
   vector<int> m_vecRow;
   //获取选择的行的PNID
   for (int row = 0;row<m_data_list.GetRowCount();row++)
   {
		if (m_data_list.GetCellChecked(row,m_select))
		{
		    int PNID = pn_table.pv_Table_PN.at(row).PNID;
			m_vecPNID.push_back(PNID);
			m_vecRow.push_back(row);
		}
   }
	//删除选择行的PNID
	for (int i=0;i<(int)m_vecPNID.size();i++)
	{
		pn_table.Delete_ByPN(m_vecPNID.at(i));
		pn_table.pv_Table_PN.erase(pn_table.pv_Table_PN.begin()+m_vecRow.at(i));
		
	}
    for (int row =0 ;row<(int)m_vecRow.size();row++)
    {
	    m_data_list.DeleteItem(m_vecRow.at(row)-row);
    }
	//pn_table.Search_ALLPN(m_strPN);
	// Load_DataToList();
}


void CPVItemMasterDlg::OnBnClickedButtonDelete()
{
	 OnMaintainitemDeleteselecteditems();
}

void CPVItemMasterDlg::OnPartsShowpohistory()
{
	COrderInformationSearchDlg dlg;
	dlg.m_partname = pn_table.pv_Table_PN.at(m_curRow).PNPartNumber;
	dlg.type = 1;
	dlg.DoModal();
}


void CPVItemMasterDlg::OnBnClickedButtonUp()
{
	 if (m_currentpagenumber>1)
	 {
		 --m_currentpagenumber;
		 ShowData();
	 }
	
}


void CPVItemMasterDlg::OnBnClickedButtonDown()
{
	if (pn_table.pv_Table_PN.size()<=0)
	{
		--m_currentpagenumber;
		//return;
	}
	else
	{
		m_currentpagenumber++;
	}
	
	ShowData();

}

#include "excel9.h"
void CPVItemMasterDlg::OnPartsExportdata()
{
 
		CString filename = g_strExePth+L"PVExportData.csv";
		CStdioFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CString str = _T("HaveVendor,Orded,PN,Type,Title,Detail,COst,BrandVendor,Catalog,Power,\
			Voltage,Tolerance,PartType,SchematicPart,AllegroFootPrint,Solidworks\n");
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
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(1)), _variant_t(L"HaveVendor"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(2)), _variant_t(L"Ordered"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(3)), _variant_t(L"PN"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(4)), _variant_t(L"Type"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(5)), _variant_t(L"Title"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(6)), _variant_t(L"Detail"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(7)), _variant_t(L"Cost"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(8)), _variant_t(L"BrandVendor"));

		range.SetItem(_variant_t((long)(1)), _variant_t((long)(9)), _variant_t(L"Catalog"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(10)), _variant_t(L"Power"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(11)), _variant_t(L"Voltage"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(12)), _variant_t(L"Tolerance"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(13)), _variant_t(L"PartType"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(14)), _variant_t(L"SchematicPart"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(15)), _variant_t(L"AllegroFootPrint"));
		range.SetItem(_variant_t((long)(1)), _variant_t((long)(16)), _variant_t(L"Solidworks"));

		int RowNumber = 1;
		for (std::vector<PN_Struct>::iterator itor = pn_table.pv_Table_PN.begin(); itor != pn_table.pv_Table_PN.end(); itor++)
		{
			++RowNumber;
			CString StrTemp;
			if (itor->Is_HaveVendor)
			{
				StrTemp = L"TRUE";
			}
			else
			{
				StrTemp = L"FALSE";
			}
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(1)), _variant_t(StrTemp));
			 
			if (itor->Is_Ordered)
			{
				StrTemp = L"TRUE";
			}
			else
			{
				StrTemp = L"FALSE";
			}
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(2)), _variant_t(StrTemp));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(3)), _variant_t(itor->PNPartNumber));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(4)), _variant_t(itor->PNType));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(5)), _variant_t(itor->PNTitle));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(6)), _variant_t(itor->PNDetail));
		 
			StrTemp.Format(_T("%0.3f"), itor->PNCurrentCost);
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(7)), _variant_t(StrTemp));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(8)), _variant_t(itor->Brand_Vendor));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(9)), _variant_t(itor->Catalog));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(10)), _variant_t(itor->Power));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(11)), _variant_t(itor->Voltage));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(12)), _variant_t(itor->Tolerance));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(13)), _variant_t(itor->Part_type));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(14)), _variant_t(itor->Schematic_part));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(15)), _variant_t(itor->Allegro_footprint));
			range.SetItem(_variant_t((long)(RowNumber)), _variant_t((long)(16)), _variant_t(itor->Solidworks));

		}
		app.SetVisible(true);
		range.ReleaseDispatch();
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		app.ReleaseDispatch();


	 
}


void CPVItemMasterDlg::OnCbnSelchangeComboNumber()
{
	ShowData();
}
