// PVBuildDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVBuildDlg.h"
#include "afxdialogex.h"

// CPVBuildDlg dialog

IMPLEMENT_DYNAMIC(CPVBuildDlg, CDialogEx)

CPVBuildDlg::CPVBuildDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVBuildDlg::IDD, pParent)
    , m_number_units(0)
{

    m_strTitle = _T("");
    m_strPN = _T("");
    m_strDetail = _T("");
    m_curRow = -1;
    m_curCol = -1;
    m_oldColorRow = -1;
    m_curColorRow = -1;
}

CPVBuildDlg::~CPVBuildDlg()
{
}

void CPVBuildDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
    DDX_Text(pDX, IDC_EDIT_PN, m_strPN);
    DDX_Text(pDX, IDC_EDIT_DETAIL, m_strDetail);
    DDX_Text(pDX, IDC_EDIT_NUMBER, m_number_units);
}


BEGIN_MESSAGE_MAP(CPVBuildDlg, CDialogEx)
    ON_BN_CLICKED(IDC_ITEM_PN, &CPVBuildDlg::OnBnClickedItemPn)


    ON_BN_CLICKED(IDC_BUILD_LIST_BUTTON, &CPVBuildDlg::OnBnClickedBuildListButton)
    ON_WM_SIZE()
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVBuildDlg::OnNMClickList1)
    ON_BN_CLICKED(IDC_REDUCE_STOCK, &CPVBuildDlg::OnBnClickedReduceStock)
    ON_BN_CLICKED(IDC_RESTOCK, &CPVBuildDlg::OnBnClickedRestock)
END_MESSAGE_MAP()


// CPVBuildDlg message handlers


BOOL CPVBuildDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    //  PNQty
    m_data_list.InsertColumn(1, _T("Item"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Qty"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Need Qty"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Item Stock"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("To Buy"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

    m_data_list.InsertColumn(6, _T("P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Assy P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("Type"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(10, _T("Detail"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(11, _T("Total Price"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(12, _T("Unit Price"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(13, _T("Vendor"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(14, _T("Vendor P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(15, _T("VendorDesc"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(16, _T("Mfr"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(17, _T("Mfr P/N"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
   

    g_hwnd_now = this->m_hWnd;

    CRect ViewRect;
    GetClientRect(&ViewRect);

    if (m_data_list.GetSafeHwnd())
    {
        m_data_list.MoveWindow(CRect(360,30,ViewRect.Width(),ViewRect.Height()-10),TRUE);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

#include "AddBOMPLDlg.h"
void CPVBuildDlg::OnBnClickedItemPn()
{
    CAddBOMPLDlg dlg;
    dlg.open_type = 1;
    pn_table.Load_Assembly_Data();
    dlg.m_message_handle = this->m_hWnd;
    dlg.DoModal ();
}

LRESULT CPVBuildDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message  == WM_MESSAGE_FRESH_BOM)
    {
        m_PN_ID =  (int)wParam;
        pn_table.Search_PNID (m_PN_ID);
        if ( pn_table.pv_Table_PN.size()>0)
        {
            m_strDetail = pn_table.pv_Table_PN.at(0).PNDetail;
            m_strPN = pn_table.pv_Table_PN.at(0).PNPartNumber;
            m_strTitle = pn_table.pv_Table_PN.at(0).PNTitle;

            UpdateData (FALSE);
        }



    }

    return CDialogEx::WindowProc(message, wParam, lParam);
}
void CPVBuildDlg::Initial_List()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
    TotalPrice = 0;
    int i=0;
    for (; i<(int)pn_table.m_buydataset.size(); i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);
        strTemp.Format(_T("%d"),pn_table.m_buydataset.at(i).Item);
        strTemp.Format(_T("%d"),i+1);
        m_data_list.SetItemText(i,1,strTemp);
        strTemp.Format(_T("%d"),pn_table.m_buydataset.at(i).Qty);
        m_data_list.SetItemText(i,2,strTemp);
        m_data_list.SetItemText(i,6,pn_table.m_buydataset.at(i).PN);
        m_data_list.SetItemText(i,7,pn_table.m_buydataset.at(i).ParentStrPN);
        m_data_list.SetItemText(i,8,pn_table.m_buydataset.at(i).Type);
        m_data_list.SetItemText(i,9,pn_table.m_buydataset.at(i).Title);
        m_data_list.SetItemText(i,10,pn_table.m_buydataset.at(i).Detail);

        strTemp.Format(_T("%0.3f"),pn_table.m_buydataset.at(i).MFCost);
        m_data_list.SetItemText(i,12,strTemp);
        m_data_list.SetItemText(i,13,pn_table.m_buydataset.at(i).Vendor);
        m_data_list.SetItemText(i,14,pn_table.m_buydataset.at(i).Vendor_PN);
        m_data_list.SetItemText(i,15,pn_table.m_buydataset.at(i).Vendor_Desc);
        m_data_list.SetItemText(i,16,pn_table.m_buydataset.at(i).Mfr);
        m_data_list.SetItemText(i,17,pn_table.m_buydataset.at(i).Mfr_PN);

        strTemp.Format (_T("%d"),pn_table.m_buydataset.at(i).Qty*m_number_units);

        m_data_list.SetItemText(i,3,strTemp);

        strTemp.Format (_T("%d"),pn_table.m_buydataset.at(i).PNStock);

        m_data_list.SetItemText(i,4,strTemp);

        int tobuy =     pn_table.m_buydataset.at(i).Qty*m_number_units -  pn_table.m_buydataset.at(i).PNStock;
        if (tobuy > 0)
        {
            strTemp.Format (_T("%d"),tobuy);
        }
        else
        {
            strTemp=_T("0");
        }

        m_data_list.SetItemText(i,5,strTemp);

        float money = pn_table.m_buydataset.at(i).MFCost*m_number_units*pn_table.m_buydataset.at(i).Qty;
        strTemp.Format(_T("%0.2f"),money);

        TotalPrice+= money;
        m_data_list.SetItemText(i,11,strTemp);


    }
    strTemp.Format(_T("%d"),i+1);
    m_data_list.InsertItem(i,strTemp);
    strTemp=_T("Total Price:");
    m_data_list.SetItemText(i,1,strTemp);

    strTemp.Format(_T("%0.2f"),TotalPrice);
    m_data_list.SetItemText(i,11,strTemp);
    m_data_list.SetItemBkColor(i,-1,LIST_ITEM_DEFAULT_BKCOLOR_GRAY);
}

void CPVBuildDlg::OnBnClickedBuildListButton()
{
    /* pn_table.m_PNID = m_PN_ID;
     pn_table.Initial_BomData();
     UpdateData (TRUE);*/
    /* UpdateData (TRUE);
    pn_table.Build_AssemblyData (m_PN_ID,m_strPN);
    Initial_List();*/



    UpdateData (TRUE);
	if (m_strPN.IsEmpty()||m_PN_ID<=0)
	{
		return;
	}
	 
    pn_table.Build_AssemblyData (m_PN_ID,m_strPN);
    for (int i=0; i<pn_table.m_bomdataset.size (); i++)
    {
        PList_Struct temp_struct = pn_table.m_bomdataset.at(i);
        BOOL is_in_list = FALSE;
        int index = -1;
        for (vector<PList_Struct>::iterator iter = pn_table.m_buydataset.begin (); iter!=pn_table.m_buydataset.end(); iter++)
        {
            if (iter->PLID == temp_struct.PLID)
            {
                is_in_list = TRUE;
                index =   iter - pn_table.m_buydataset.begin ();
                break;
            }
        }
        if (!is_in_list)    //不存在--加入列表
        {


            int tobuy = temp_struct.Qty*m_number_units  -  temp_struct.PNStock;   //
            if (tobuy < 0)
            {
                tobuy = 0;
            }
            temp_struct.tobuy = tobuy;
            temp_struct.TotalQty= temp_struct.Qty*m_number_units;
            temp_struct.OrderQty = tobuy;
            temp_struct.MFExtCost = temp_struct.vendorPrice * temp_struct.OrderQty;
            pn_table.m_buydataset.push_back (temp_struct);

        }
        else   //存在，把数量加进去
        {

            int tobuy = pn_table.m_buydataset.at(index).TotalQty + temp_struct.Qty*m_number_units -  pn_table.m_buydataset.at(index).PNStock;
            if (tobuy < 0)
            {
                tobuy = 0;
            }
            pn_table.m_buydataset.at(index).tobuy = tobuy;
            pn_table.m_buydataset.at(index).TotalQty += temp_struct.Qty*m_number_units;
            pn_table.m_buydataset.at(index).OrderQty = tobuy;
            pn_table.m_buydataset.at(index).MFExtCost = pn_table.m_buydataset.at(index).vendorPrice * pn_table.m_buydataset.at(index).OrderQty;



        }

    }


    //LoadData2BuyList();
    Initial_List();
}


void CPVBuildDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    if (nType==SIZE_RESTORED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);

        if (m_data_list.GetSafeHwnd())
        {
            m_data_list.MoveWindow(CRect(430,30,ViewRect.Width(),ViewRect.Height()-10),TRUE);
        }
    }
}


void CPVBuildDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


    *pResult = 0;
}


void CPVBuildDlg::OnBnClickedReduceStock()
{

    PN_Struct pntemp;
    for (int row = 0; row<m_data_list.GetRowCount (); row ++)
    {
        pntemp.PNPartNumber = L"";
        pntemp.Stock = 0;
        pntemp.PNPartNumber = m_data_list.GetItemText (row,6);
        pntemp.Stock = _wtoi (m_data_list.GetItemText (row,3));
        pn_table.Reduce_ItemStock (pntemp);
    }
}

void CPVBuildDlg::OnBnClickedRestock()
{
    PN_Struct pntemp;
    for (int row = 0; row<m_data_list.GetRowCount (); row ++)
    {
        pntemp.PNPartNumber = m_data_list.GetItemText (row,6);
        pntemp.Stock = _wtoi (m_data_list.GetItemText (row,3));
        pn_table.Add_ItemStock(pntemp);
    }
}
