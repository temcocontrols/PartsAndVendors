// PVPurchaseOrderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVPurchaseOrderDlg.h"
#include "afxdialogex.h"


// CPVPurchaseOrderDlg dialog

IMPLEMENT_DYNAMIC(CPVPurchaseOrderDlg, CDialogEx)

CPVPurchaseOrderDlg::CPVPurchaseOrderDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVPurchaseOrderDlg::IDD, pParent)
{
    m_curRow  = 0 ;
    m_curCol  = 0 ;
    m_oldColorRow = -1;
    m_curColorRow = -1;
}

CPVPurchaseOrderDlg::~CPVPurchaseOrderDlg()
{
}

void CPVPurchaseOrderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Control(pDX, IDC_RICHEDIT_TO, m_RichEdit_TO);
    DDX_Control(pDX, IDC_RICHEDI_TERMS, m_RichEdit_Terms);
    DDX_Control(pDX, IDC_RICHEDIT_DATE, m_RichEdit_Date);
    DDX_Control(pDX, IDC_RICHEDIT_DATE_REQUIRED, m_RichEdit_Date_Required);
    DDX_Control(pDX, IDC_RICHEDIT_FOB, m_RichEdit_Fob);
    DDX_Control(pDX, IDC_RICHEDIT_SHIPPING_METHOD, m_RichEdit_Shipping_Method);
    DDX_Control(pDX, IDC_RICHEDIT_SHIPPING_TO, m_RichEdit_SHIP_TO);
    DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_static_account);
    DDX_Control(pDX, IDC_STATIC_ATTN, m_static_attn);
    DDX_Control(pDX, IDC_STATIC_BUYER, m_static_buyer);
    DDX_Control(pDX, IDC_STATIC_PHONE, m_static_phone);
    DDX_Control(pDX, IDC_STATIC_TECH_CONTECT, m_static_contect);
    DDX_Control(pDX, IDC_PURCHASE_DATE, m_static_purchase_date);
    DDX_Control(pDX, IDC_STATIC_PO, m_static_po);
}


BEGIN_MESSAGE_MAP(CPVPurchaseOrderDlg, CDialogEx)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVPurchaseOrderDlg::OnNMClickList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVPurchaseOrderDlg::OnNMDblclkList1)
    ON_MESSAGE(WM_LIST_ITEM_CHANGED,Change_Item_List)
    ON_BN_CLICKED(IDC_BUTTON_PRINT_EXCEL, &CPVPurchaseOrderDlg::OnBnClickedButtonPrintExcel)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CPVPurchaseOrderDlg::OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CPVPurchaseOrderDlg message handlers

BOOL CPVPurchaseOrderDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

     pn_table.Search_PO();
     pn_table.Search_PO_Part();

    m_static_po.SetWindowText(L"Purchase Order:");
    m_static_po.setFont(30,20,NULL,_T("Arial"));

    m_static_purchase_date.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMNumber);
    m_static_purchase_date.setFont(30,10,NULL,_T("Arial"));

    m_RichEdit_TO.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMSupplier+"\n"+pn_table.m_dataset_purchaseorder.at(0).POMAddress);
    m_RichEdit_TO.SetFontName(_T("Arial"));
    m_RichEdit_TO.SetFontSize(15);
    m_RichEdit_TO.SetReadOnly(TRUE);

    m_static_phone.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMSupplier_Phone);
    m_static_phone.setFont(15,10,NULL,_T("Arial"));

    m_static_attn.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMAttnTo);
    m_static_attn.setFont(15,10,NULL,_T("Arial"));
    m_static_account.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMAccount);
    m_static_account.setFont(15,10,NULL,_T("Arial"));

    m_RichEdit_SHIP_TO.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMShipTo);
    m_RichEdit_SHIP_TO.SetFontName(_T("Arial"));
    m_RichEdit_SHIP_TO.SetFontSize(15);
    m_RichEdit_SHIP_TO.SetReadOnly(FALSE);

    m_static_buyer.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMFromBuyer);
    m_static_buyer.setFont(15,10,NULL,_T("Arial"));

    m_static_contect.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMEngrgContact);
    m_static_contect.setFont(15,10,NULL,_T("Arial"));

    m_RichEdit_Date_Required.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMDateReq);
    m_RichEdit_Date_Required.SetFontName(_T("Arial"));
    m_RichEdit_Date_Required.SetFontSize(12);
    m_RichEdit_Date_Required.SetReadOnly(FALSE);

    m_RichEdit_Fob.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMFOB);
    m_RichEdit_Fob.SetFontName(_T("Arial"));
    m_RichEdit_Fob.SetFontSize(12);
    m_RichEdit_Fob.SetReadOnly(FALSE);

    m_RichEdit_Shipping_Method.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMShipMethod);
    m_RichEdit_Shipping_Method.SetFontName(_T("Arial"));
    m_RichEdit_Shipping_Method.SetFontSize(12);
    m_RichEdit_Shipping_Method.SetReadOnly(FALSE);

    m_RichEdit_Terms.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMTerms);
    m_RichEdit_Terms.SetFontName(_T("Arial"));
    m_RichEdit_Terms.SetFontSize(12);
    m_RichEdit_Terms.SetReadOnly(FALSE);

    m_RichEdit_Date.SetWindowText(pn_table.m_dataset_purchaseorder.at(0).POMDatePrinted);
    m_RichEdit_Date.SetFontName(_T("Arial"));
    m_RichEdit_Date.SetFontSize(12);
    m_RichEdit_Date.SetReadOnly(FALSE);

    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("Item"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("P/N"), 180, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Description"), 250, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Cost"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Order Qty"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Buy Units"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Extension"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Qty Reveived"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8,_T("ReceivedAll"),80,ListCtrlEx::CheckBox,LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9,_T("NOTE"),80,ListCtrlEx::CheckBox,LVCFMT_CENTER, ListCtrlEx::SortByString);
    LoadData2List();
    return TRUE;
    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPVPurchaseOrderDlg::LoadData2List ()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
    int row = 0;
    float total_float = 0;
    for (; row<(int)pn_table.m_dataset_ppo.size(); row++)
    {
        strTemp.Format(_T("%d"),row+1);
        m_data_list.InsertItem(row,strTemp);
        strTemp=pn_table.m_dataset_ppo.at(row).PN;
        m_data_list.SetItemText(row,1,strTemp);
        strTemp=pn_table.m_dataset_ppo.at(row).Descrition;
        m_data_list.SetItemText(row,2,strTemp);
        strTemp.Format(_T("%0.4f"),pn_table.m_dataset_ppo.at(row).POCost);
        m_data_list.SetItemText(row,3,strTemp);
        strTemp.Format(_T("%0.2f"),pn_table.m_dataset_ppo.at(row).Qty);
        m_data_list.SetItemText(row,4,strTemp);
        strTemp=pn_table.m_dataset_ppo.at(row).Buy_As;
        m_data_list.SetItemText(row,5,strTemp);

        total_float+=pn_table.m_dataset_ppo.at(row).POExtension;
        strTemp.Format(_T("%0.2f"),pn_table.m_dataset_ppo.at(row).POExtension);
        m_data_list.SetItemText(row,6,strTemp);

        strTemp.Format (_T("%0.2f"),pn_table.m_dataset_ppo.at(row).RvcdQty);
        m_data_list.SetItemText(row,7,strTemp);
       
        m_data_list.SetItemText(row,7,pn_table.m_dataset_ppo.at(row).StrNote);

        if (pn_table.m_dataset_ppo.at(row).RvcdAll == -1)
        {
            m_data_list.SetCellChecked (row,8,TRUE);
        }
        else
        {
            m_data_list.SetCellChecked (row,8,FALSE);
        }

    }
    strTemp.Format(_T("%d"),row+1);
    m_data_list.InsertItem(row,strTemp);
    strTemp=_T("Total :");
    m_data_list.SetItemText(row,1,strTemp);


    strTemp.Format(_T("%0.2f"),total_float);
    m_data_list.SetItemText(row,6,strTemp);
    m_data_list.SetItemBkColor(row,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);


    g_hwnd_now = this->m_hWnd;
}

void CPVPurchaseOrderDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
        return;

    }

    if(lRow<pn_table.m_dataset_ppo.size())
    {
        PO_Part_Struct Change_Item= pn_table.m_dataset_ppo.at(lRow);
        Change_Item.RvcdAll = 0;
        if (lCol == 8)//Qty
        {
            BOOL Click = m_data_list.GetCellChecked (lRow,lCol);
            if (Click==0)
            {
                Change_Item.RvcdAll = -1;
                Change_Item.RvcdQty = Change_Item.Qty;
            }
            else
            {
                Change_Item.RvcdAll = 0;

            }
        }
        pn_table.Update_PO_Part (Change_Item);
        pn_table.Search_PO_Part ();
        LoadData2List ();
        return  ;
        // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }
    *pResult = 0;
}


void CPVPurchaseOrderDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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

    if(lRow<pn_table.m_dataset_ppo.size())
    {
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
        if (lCol == 1)//Qty
        {
            //  m_data_list.SetCellChecked (lRow,lCol,TRUE);
            /*   for (int i = 0 ;i< (int) m_data_list.GetRowCount ()-1;i++)
               {
                   if (lRow != i)
                   {
                       m_data_list.SetCellChecked (i,lCol,FALSE);
                   }


               }*/



        }

        return  ;


        // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }
    *pResult = 0;
}

LRESULT CPVPurchaseOrderDlg::Change_Item_List(WPARAM wParam,LPARAM lParam)
{

    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;
    int AddressValue = -1;
    CString temp_task_info;
    temp_task_info = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
    PO_Part_Struct Change_Item= pn_table.m_dataset_ppo.at(Changed_Item);
    int StockChanged = -1;
    if (Changed_SubItem == 4)
    {
        Change_Item.Qty  = _wtof (temp_task_info);

        Change_Item.POExtension = Change_Item.POCost * Change_Item.Qty;

    }
    if (Changed_SubItem == 3)
    {
        Change_Item.POCost  = _wtof (temp_task_info);

        Change_Item.POExtension = Change_Item.POCost * Change_Item.Qty;

    }
    if (Changed_SubItem == 7)
    {
        Change_Item.RvcdQty =  _wtof (temp_task_info);
        StockChanged = (Change_Item.RvcdQty - pn_table.m_dataset_ppo.at(Changed_Item).RvcdQty) * Change_Item.UnitCov;
        if ( Change_Item.Qty -Change_Item.RvcdQty < 0.1 )
        {
            Change_Item.RvcdAll = -1;
        }
        else
        {
            Change_Item.RvcdAll = 0;
        }
    }
    if (Changed_SubItem == 8)
    {
        Change_Item.StrNote = temp_task_info;
       
    }

    pn_table.Update_PO_Part (Change_Item);
    pn_table.Search_PO_Part ();
    LoadData2List ();

    if (StockChanged >0)
    {
       PN_Struct temp;
       temp.PNPartNumber =   pn_table.m_dataset_ppo.at(Changed_Item).PN;
       temp.Stock = StockChanged;
       pn_table.Add_ItemStock (temp);
     //  temp.PNPartNumber =  
    }
    return 0;
}


void CPVPurchaseOrderDlg::OnBnClickedButtonPrintExcel()
{

}


void CPVPurchaseOrderDlg::OnBnClickedButtonPrint()
{
	CString g_configfile_path = g_strExePth + _T("T3000_config.ini");
	WritePrivateProfileStringW(L"PVDBSETTING", L"PONUMBER", pn_table.m_dataset_purchaseorder.at(0).POMNumber, g_configfile_path);
	CString strHistotyFile = g_strExePth + _T("PVReporter.exe");
	ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
}
