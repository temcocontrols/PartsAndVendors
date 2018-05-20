// PVPODlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVPODlg.h"
#include "afxdialogex.h"
#include "PVPurchaseOrderDlg.h"
#include "QPrint.h"
// CPVPODlg dialog

IMPLEMENT_DYNAMIC(CPVPODlg, CDialogEx)

CPVPODlg::CPVPODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVPODlg::IDD, pParent)
    , m_strPO(_T(""))
    , m_strVendorName(_T(""))
{
      
      m_curRow = -1;
      m_oldColorRow = -1;
      m_curColorRow = -1;
}

CPVPODlg::~CPVPODlg()
{
}

void CPVPODlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Text(pDX, IDC_EDIT_PO, m_strPO);
    DDX_Text(pDX, IDC_EDIT_VENDOR_NAME, m_strVendorName);
}


BEGIN_MESSAGE_MAP(CPVPODlg, CDialogEx)
    ON_WM_SIZE()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPVPODlg::OnNMDblclkList1)
    ON_BN_CLICKED(IDC_DEL_ORDERS, &CPVPODlg::OnBnClickedDelOrders)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVPODlg::OnNMClickList1)
    ON_BN_CLICKED(IDOK, &CPVPODlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CPVPODlg message handlers
BOOL CPVPODlg::OnInitDialog(){
    CDialogEx::OnInitDialog();

    CRect ViewRect;
    GetClientRect(&ViewRect);
//     CRect listRect;
//     m_data_list.GetClientRect(&listRect);
    if (m_data_list.GetSafeHwnd())
    {
        m_data_list.MoveWindow(CRect(0,120/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
    }

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
    m_data_list.InsertColumn(9, _T("Ship To"), 220, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(10, _T("Select"), 60, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByDigit);

    g_hwnd_now = this->m_hWnd;



   

   return TRUE;
}
void CPVPODlg::ShowData()
{
   if (PO_NEEDFRESH||(pn_table.m_dataset_po.size()<1&&IsWindowVisible()))
   {
	   PO_NEEDFRESH = FALSE;
	   pn_table.Search_POM(m_strPO,m_strVendorName);
	   Load_DataToList();
   }

}
void CPVPODlg::Load_DataToList(){
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
       // m_data_list.InsertItem(row,strTemp);
        strTemp=_T("Total :");
       // m_data_list.SetItemText(row,1,strTemp);


        strTemp.Format(_T("%0.2f"),Total);
       // m_data_list.SetItemText(row,3,strTemp);
       // m_data_list.SetItemBkColor(row,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);
}

void CPVPODlg::OnSize(UINT nType, int cx, int cy)
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
            m_data_list.MoveWindow(CRect(0,50/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
        }
    }
    // TODO: Add your message handler code here
}

void CPVPODlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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
    //if (lCol == 0)
    //{

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

        CPVPurchaseOrderDlg dlg;
        pn_table.m_POMID = pn_table.m_dataset_po.at(m_curRow).POMID;
        dlg.DoModal();

 /*   }
    if (1==lCol)
    {
        CPVPurchaseOrderDlg dlg;
        dlg.pn_table.m_POMID = pn_table.m_dataset_po.at(m_curRow).POMID;
        dlg.DoModal();
    }*/
    *pResult = 0;
}


void CPVPODlg::OnBnClickedDelOrders()
{
    UpdateData (TRUE);
   for (int i = 0;i<m_data_list.GetRowCount ();i++)
   {
        bool is_select =   (bool)m_data_list.GetCellChecked (i,10);
        if (is_select == true)
        {
			CStringArray ntemparray;
			CString strPO = pn_table.m_dataset_po.at(i).POMNumber;
			SplitCStringA(ntemparray, strPO, _T("-"));
			pn_table.DeletePONumber(ntemparray[0], ntemparray[1]);
           pn_table.Delete_PO (pn_table.m_dataset_po.at(i));
		   

		  
        }
   }

   pn_table.Search_POM (m_strPO,m_strVendorName);
   Load_DataToList ();
    
}


void CPVPODlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


void CPVPODlg::OnBnClickedOk()
{

    UpdateData (TRUE);
    pn_table.Search_POM (m_strPO,m_strVendorName);
    Load_DataToList ();
}
