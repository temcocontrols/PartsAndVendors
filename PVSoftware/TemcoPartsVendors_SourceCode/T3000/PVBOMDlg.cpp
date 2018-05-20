// PVBOMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVBOMDlg.h"
#include "afxdialogex.h"
#include "AddBOMPLDlg.h"

// CPVBOMDlg dialog

IMPLEMENT_DYNAMIC(CPVBOMDlg, CDialogEx)

CPVBOMDlg::CPVBOMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVBOMDlg::IDD, pParent)
{
    TotalPrice = 0.0;
    m_curRow = -1;
    m_curCol = -1;
}

CPVBOMDlg::~CPVBOMDlg()
{
}

void CPVBOMDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(CPVBOMDlg, CDialogEx)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CPVBOMDlg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPVBOMDlg::OnBnClickedButtonDelete)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVBOMDlg::OnNMClickList1)

    ON_MESSAGE(WM_LIST_ITEM_CHANGED,Change_List_Item)

    ON_BN_CLICKED(IDC_UPDATE_ASSEMBLY_COST, &CPVBOMDlg::OnBnClickedUpdateAssemblyCost)
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPVBOMDlg::OnNMRClickList1)
    ON_COMMAND(ID_PV_BOM, &CPVBOMDlg::OnPvBom)
	ON_BN_CLICKED(IDC_SAVE_BOMLIST, &CPVBOMDlg::OnBnClickedSaveBomlist)
END_MESSAGE_MAP()


// CPVBOMDlg message handlers


BOOL CPVBOMDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();



    
    pn_table.m_PNID = m_PN_ID;
    pn_table.Initial_BomData();

    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Item"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Qty"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Type"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Detail"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Cur/AssyMFExCost"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("Cur/AssyMFCost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9, _T("Vendor"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(10, _T("Vendor P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(11, _T("VendorDesc"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(12, _T("Refence"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(13, _T("Mfr"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(14, _T("Mfr P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(15, _T("Brand"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_data_list.InsertColumn(16, _T("Footprint"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    g_hwnd_now = this->m_hWnd;  
    Initial_List();

    this->SetWindowTextW(Title);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPVBOMDlg::Set_PN(int PN_ID){
    m_PN_ID = PN_ID;
}

void CPVBOMDlg::Initial_List(){
    CString  strTemp;
    m_data_list.DeleteAllItems();

    int i=0;
    for (;i<(int)pn_table.m_bomdataset.size();i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);
        //strTemp.Format(_T("%d"),pn_table.m_bomdataset.at(i).Item);
        m_data_list.SetItemText(i,1,strTemp);
        strTemp.Format(_T("%d"),pn_table.m_bomdataset.at(i).Qty);
        m_data_list.SetItemText(i,2,strTemp);
        m_data_list.SetItemText(i,3,pn_table.m_bomdataset.at(i).PN);
        m_data_list.SetItemText(i,4,pn_table.m_bomdataset.at(i).Type);
        m_data_list.SetItemText(i,5,pn_table.m_bomdataset.at(i).Title);
        m_data_list.SetItemText(i,6,pn_table.m_bomdataset.at(i).Detail);
        strTemp.Format(_T("%0.2f"),pn_table.m_bomdataset.at(i).MFExtCost);
        TotalPrice+= pn_table.m_bomdataset.at(i).MFExtCost;
        m_data_list.SetItemText(i,7,strTemp);
        strTemp.Format(_T("%0.3f"),pn_table.m_bomdataset.at(i).MFCost);
        m_data_list.SetItemText(i,8,strTemp);
        m_data_list.SetItemText(i,9,pn_table.m_bomdataset.at(i).Vendor);
        m_data_list.SetItemText(i,10,pn_table.m_bomdataset.at(i).Vendor_PN);
        m_data_list.SetItemText(i,11,pn_table.m_bomdataset.at(i).Vendor_Desc);
        m_data_list.SetItemText(i,13,pn_table.m_bomdataset.at(i).Mfr);
        m_data_list.SetItemText(i,14,pn_table.m_bomdataset.at(i).Mfr_PN);
        m_data_list.SetItemText(i,12,pn_table.m_bomdataset.at(i).Reference);
		m_data_list.SetItemText(i,15,pn_table.m_bomdataset.at(i).Brand);
		m_data_list.SetItemText(i,16,pn_table.m_bomdataset.at(i).FootPrint);
    }
    strTemp.Format(_T("%d"),i+1);
    m_data_list.InsertItem(i,strTemp);
    strTemp=_T("Total Price:");
    m_data_list.SetItemText(i,1,strTemp);


    strTemp.Format(_T("%0.2f"),TotalPrice);
    m_data_list.SetItemText(i,7,strTemp);
    m_data_list.SetItemBkColor(i,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);
}

void CPVBOMDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if (nType==SIZE_RESTORED)
    {

        CRect ViewRect;
        GetClientRect(&ViewRect);

        if (m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(0,30,ViewRect.Width(),ViewRect.Height()),TRUE);

        }

    }
     
}


void CPVBOMDlg::OnBnClickedButtonAdd()
{
    CAddBOMPLDlg dlg;
    pn_table.Initial_Data ();
    dlg.m_message_handle = this->m_hWnd;
    dlg.DoModal (); 
}


LRESULT CPVBOMDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if (message  == WM_MESSAGE_FRESH_BOM)
    {
        BOM_PartList addItem;

        addItem.PLPartID =(int)wParam;
        addItem.PLListID = m_PN_ID;
        addItem.PLItem = pn_table.m_bomdataset.size()+1;
        addItem.PLQty =L"1";
        pn_table.Insert_PL (addItem);

        pn_table.m_PNID = m_PN_ID;
        pn_table.Initial_BomData();
        Initial_List();
    }
    if (message  == WM_MESSAGE_FRESH_BOMLIST)
    {
        pn_table.m_PNID = m_PN_ID;
        pn_table.Initial_BomData();
        Initial_List();
    }
    return CDialogEx::WindowProc(message, wParam, lParam);
}


void CPVBOMDlg::OnBnClickedButtonDelete()
{
          BOM_PartList bom_item;
          bom_item.PLID = pn_table.m_bomdataset.at(m_curRow).PLID;
          BOOL result = pn_table.Delete_PL (bom_item);
          PostMessage (WM_MESSAGE_FRESH_BOMLIST,0,0);
}
     

void CPVBOMDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
    if (lCol == 1)
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
    if(lRow>pn_table.m_bomdataset.size())
    {
        /*CNewPNDlg dlg;
        dlg.m_new_item = 2;
        dlg.m_item = pn_table.pv_Table_PN.at(m_curRow);
        dlg.DoModal();*/
             return  ;
             

       // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }

    
                                                       
        
   

     

    *pResult = 0;
}
LRESULT CPVBOMDlg::Change_List_Item(WPARAM wParam,LPARAM lParam)
{   

    
    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;
    CString strQty = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
    if (Changed_SubItem == 2)//Qty
    {
        BOM_PartList BomItem;
        BomItem.PLID = pn_table.m_bomdataset.at(Changed_Item).PLID;
        BomItem.PLQty = strQty;

        if (pn_table.Update_PL (BomItem))
        {
            PostMessage (WM_MESSAGE_FRESH_BOMLIST,0,0);
        }
         


    }
    return 0;
}

void CPVBOMDlg::OnBnClickedUpdateAssemblyCost()
{
      pn_table.Update_PartPrice (m_PN_ID,TotalPrice);

}


void CPVBOMDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
  
    if(lRow<pn_table.m_bomdataset.size())
    {
        CMenu menu;
        menu.LoadMenu(IDR_PVMENU);
        CMenu *pmenu=menu.GetSubMenu(0);
        CPoint point;
        GetCursorPos(&point);
        pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);  
    }
    *pResult = 0;
  
}


void CPVBOMDlg::OnPvBom()
{
    CPVBOMDlg pvbomdlg;
    pvbomdlg.m_PN_ID = pn_table.m_bomdataset.at(m_curRow).PLID;
    CString Title;
    Title.Format (_T("Bom List:%s"),pn_table.m_bomdataset.at(m_curRow).PN);
    pvbomdlg.Title = Title;
   
    pvbomdlg.DoModal(); 
}


void CPVBOMDlg::OnBnClickedSaveBomlist()
{
     CString DirtoryPath = g_strExePth + "BOM\\";
	 CreateDirectory(DirtoryPath);
	 CString StrFilePath = DirtoryPath+m_strPNumber+".BOM";
	 CStdioFile WriteFile;
	 if (WriteFile.Open(StrFilePath.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate ))
	 {
		 CString StrContect ;
		 StrContect.Format(L"Item_Number	Quantity	Part_Reference	Name	PCB_Footprint	Description	Brand_Vendor	part_number\n");
	     WriteFile.WriteString(StrContect);
		 for (int row=0;row <m_data_list.GetRowCount()-1;row++)
	     {
			 CString Item_Number=    m_data_list.GetItemText(row,1);
			 CString Quantity=    	 m_data_list.GetItemText(row,2);
			 CString Part_Reference=    	 m_data_list.GetItemText(row,12);
			CString Name=    	 m_data_list.GetItemText(row,5);
			CString PCB_Footprint=    	 m_data_list.GetItemText(row,16);
			CString Description=    	 m_data_list.GetItemText(row,6);
			CString Brand_Vendor=    	 m_data_list.GetItemText(row,15);
			CString part_number=    	 m_data_list.GetItemText(row,3);
			 StrContect.Format(_T("%s	%s	%s	%s	%s	%s	%s	%s\n"),
			 Item_Number,Quantity,Part_Reference,Name,PCB_Footprint,Description,Brand_Vendor,part_number
			 );
			 WriteFile.WriteString(StrContect);
	     }
	 } 
	 else
	 {
	    AfxMessageBox(L"Create file error!");
		return;
	 }
	 CString ShowMessage;
	  ShowMessage.Format(_T("Save OK,File is in %s"),DirtoryPath);
	 AfxMessageBox(ShowMessage);

	
}
