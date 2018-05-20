// PVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVDlg.h"
#include "afxdialogex.h"
#include "PVBOMDlg.h"
#include "PVPurchaseOrderDlg.h"
 

IMPLEMENT_DYNAMIC(CPVDlg, CDialog)

CPVDlg::CPVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPVDlg::IDD, pParent)
    , m_strPN(_T(""))
{
   m_select_type = 0;
   m_oldColorRow = -1;
   m_curColorRow = -1;
   m_curCol = -1;
   m_curRow = -1;
}

CPVDlg::~CPVDlg()
{
}

void CPVDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_ITEM_MASTER, m_button_item_master);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Text(pDX, IDC_EDIT1, m_strPN);
 
}


BEGIN_MESSAGE_MAP(CPVDlg, CDialog)
	 
    ON_BN_CLICKED(IDOK, &CPVDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_ITEM_MASTER, &CPVDlg::OnBnClickedItemMaster)
    ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPVDlg::OnNMRClickList1)
    ON_WM_SIZE()
//    ON_BN_CLICKED(IDC_BUTTON, &CPVDlg::OnBnClickedButton)
//    ON_EN_KILLFOCUS(IDC_EDIT1, &CPVDlg::OnEnKillfocusEdit1)
    ON_COMMAND(ID_PV_BOM, &CPVDlg::OnPvBom)
    ON_BN_CLICKED(IDC_VENDOR, &CPVDlg::OnBnClickedVendor)
    ON_BN_CLICKED(IDC_PO, &CPVDlg::OnBnClickedPo)
    ON_UPDATE_COMMAND_UI(ID_PV_BOM, &CPVDlg::OnUpdatePvBom)
    ON_COMMAND(ID_PV_PO, &CPVDlg::OnPvPo)
    ON_UPDATE_COMMAND_UI(ID_PV_PO, &CPVDlg::OnUpdatePvPo)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CPVDlg message handlers

BOOL CPVDlg::OnInitDialog(){
 CDialog::OnInitDialog();

 CRect ViewRect;
 GetClientRect(&ViewRect);

 if (m_data_list.GetSafeHwnd())
 {
     m_data_list.MoveWindow(CRect(130,40,ViewRect.Width(),ViewRect.Height()),TRUE);
 }
  if (m_select_type == 0)                                                                           
  {    
      pn_table.Initial_Data();
      Load_DataToList();  
  }
 

 
return TRUE;
}
 
 void CPVDlg::Load_DataToList(){
        
     if (m_select_type == 0)
     {
         while(m_data_list.DeleteColumn(0));
         m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
         m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));
         m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
         m_data_list.InsertColumn(1, _T("P/N"), 140, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(2, _T("Type"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(3, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(4, _T("Detail"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(5, _T("Rev"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(6, _T("Stat"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(7, _T("Cur.Cost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

         CString  strTemp;
         m_data_list.DeleteAllItems();
         for (int row = 0;row<(int)pn_table.pv_Table_PN.size();row++)
         {
             strTemp.Format(_T("%d"),row+1);
             m_data_list.InsertItem(row,strTemp);
             strTemp=pn_table.pv_Table_PN.at(row).PNPartNumber;
             m_data_list.SetItemText(row,1,strTemp);
             strTemp=pn_table.pv_Table_PN.at(row).PNType;
             m_data_list.SetItemText(row,2,strTemp);
             strTemp=pn_table.pv_Table_PN.at(row).PNTitle;
             m_data_list.SetItemText(row,3,strTemp); 
             strTemp=pn_table.pv_Table_PN.at(row).PNDetail;
             m_data_list.SetItemText(row,4,strTemp);  
             strTemp=pn_table.pv_Table_PN.at(row).PNRevision;
             m_data_list.SetItemText(row,5,strTemp); 
             strTemp=pn_table.pv_Table_PN.at(row).PNStatus;
             m_data_list.SetItemText(row,6,strTemp); 
             strTemp.Format(_T("%0.2f"),pn_table.pv_Table_PN.at(row).PNCurrentCost);
             m_data_list.SetItemText(row,7,strTemp); 
         }
     }
     else  if(m_select_type == 1)
     {
       
         while(m_data_list.DeleteColumn(0));
         m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
         m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
         m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
         m_data_list.InsertColumn(1, _T("Vendor"), 140, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(2, _T("Address"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(3, _T("Phone1"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(4, _T("Phone2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(5, _T("Fax"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(6, _T("CustAcct"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(7, _T("Contact1"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(8, _T("Contact2"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString); 

        CString  strTemp;
        m_data_list.DeleteAllItems();
        for (int row = 0;row<(int)pn_table.m_dataset_vendor.size();row++)
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
     else  if (m_select_type == 2)
     {
         while(m_data_list.DeleteColumn(0));
         m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
         m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
         m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
         m_data_list.InsertColumn(1, _T("#PO"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(2, _T("Vendor"), 140, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(3, _T("Total"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(4, _T("Date Issued"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(5, _T("Date Closed"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(6, _T("Date Reqd"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(7, _T("Buyer"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(8, _T("EngrContact"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
         m_data_list.InsertColumn(9, _T("Ship To"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

         CString  strTemp;
         m_data_list.DeleteAllItems();
         float Total = 0 ;
         int row = 0;
         for (;row<(int)pn_table.m_dataset_po.size();row++)
         {
             strTemp.Format(_T("%d"),row+1);
             m_data_list.InsertItem(row,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMNumber;
             m_data_list.SetItemText(row,1,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMSupplier;
             m_data_list.SetItemText(row,2,strTemp);

             Total += pn_table.m_dataset_po.at(row).POMTotalCost;
             strTemp.Format(_T("%0.1f"),pn_table.m_dataset_po.at(row).POMTotalCost) ;
             m_data_list.SetItemText(row,3,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMDatePrinted;
             m_data_list.SetItemText(row,4,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMDateClosed;
             m_data_list.SetItemText(row,5,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMDateReq;
             m_data_list.SetItemText(row,6,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMFromBuyer;
             m_data_list.SetItemText(row,7,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMEngrgContact;
             m_data_list.SetItemText(row,8,strTemp);

             strTemp = pn_table.m_dataset_po.at(row).POMShipTo;
             strTemp.Replace('\r',',');
             strTemp.Replace('\n',' ');
             m_data_list.SetItemText(row,9,strTemp);
            
         }
         strTemp.Format(_T("%d"),row+1);
         m_data_list.InsertItem(row,strTemp);
         strTemp=_T("Total :");
         m_data_list.SetItemText(row,1,strTemp);


         strTemp.Format(_T("%0.2f"),Total);
         m_data_list.SetItemText(row,3,strTemp);
         m_data_list.SetItemBkColor(row,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);
     }
       
     
 }

 void CPVDlg::Search_PN_List(){
   /* pn_table.Search_Data_ByPN(m_strPN);
    Load_DataToList();*/

 }

void CPVDlg::OnBnClickedOk()
{
    
}

void CPVDlg::OnBnClickedItemMaster()
{
     if (m_select_type != 0)
     {
         m_select_type = 0;
        
         pn_table.Initial_Data();
         Load_DataToList();
     }
    
}


void CPVDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: Add your control notification handler code here

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


    if (1==lCol)
    {
     
        /*     CMenu menu;
        menu.LoadMenu(IDR_PVMENU);
        CMenu *pmenu=menu.GetSubMenu(0);
        CPoint point;
        GetCursorPos(&point);
        pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);*/

    }
    else{
        return;
    }
    *pResult = 0;

    
}


void CPVDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    if (nType==SIZE_RESTORED)
    {

        CRect ViewRect;
        GetClientRect(&ViewRect);

        if (m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(130,40,ViewRect.Width(),ViewRect.Height()),TRUE);
        }
       
    }
    // TODO: Add your message handler code here
}

 
 
//void CPVDlg::OnBnClickedButton()
//{
//    if (m_select_type == 0)
//    {
//        UpdateData(TRUE);
//        Search_PN_List();
//    }
//    
//}


BOOL CPVDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if(pMsg->message == WM_KEYDOWN  )
    {
        if(pMsg->wParam == VK_RETURN)
        {
            CWnd *temp_focus=GetFocus();	//Maurice require ,click enter and the cursor still in this edit or combobox.
            GetDlgItem(IDC_EDIT1_TEST)->SetFocus();
            temp_focus->SetFocus();

            return 1;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}


//void CPVDlg::OnEnKillfocusEdit1()
//{
//      OnBnClickedButton();
//}


void CPVDlg::OnPvBom()
{
    if (m_select_type != 0)
    {
        return;
    }
    CPVBOMDlg pvbomdlg;
    pvbomdlg.m_PN_ID = pn_table.pv_Table_PN.at(m_curRow).PNID;
    pvbomdlg.DoModal();  
}


void CPVDlg::OnBnClickedVendor()
{
    if (m_select_type != 1)
    {
        m_select_type = 1;
       
      //  pn_table.Initial_Vendor();
        Load_DataToList();
    }
}


void CPVDlg::OnBnClickedPo()
{
    if (m_select_type != 2)
    {
        m_select_type = 2;
       
//         pn_table.Initial_PO();
//         Load_DataToList();
    }
}


void CPVDlg::OnUpdatePvBom(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_select_type == 0);
}


void CPVDlg::OnPvPo()
{
      if (m_select_type != 2)
      {
            return ;
      }
      CPVPurchaseOrderDlg dlg;
      pn_table.m_POMID = pn_table.m_dataset_po.at(m_curRow).POMID;
      dlg.DoModal();
}


void CPVDlg::OnUpdatePvPo(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_select_type == 2);
}


void CPVDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: Add your control notification handler code here

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
           if (m_select_type == 0)
           {
               CPVBOMDlg pvbomdlg;
               pvbomdlg.m_PN_ID = pn_table.pv_Table_PN.at(m_curRow).PNID;
               pvbomdlg.DoModal(); 
           }
           else if (m_select_type == 2)
           {
               CPVPurchaseOrderDlg dlg;
               pn_table.m_POMID = pn_table.m_dataset_po.at(m_curRow).POMID;
               dlg.DoModal();
           }

   /*     CMenu menu;
        menu.LoadMenu(IDR_PVMENU);
        CMenu *pmenu=menu.GetSubMenu(0);
        CPoint point;
        GetCursorPos(&point);
        pmenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN ,point.x,point.y,this);*/

    }
    else{
        return;
    }

    *pResult = 0;
}
