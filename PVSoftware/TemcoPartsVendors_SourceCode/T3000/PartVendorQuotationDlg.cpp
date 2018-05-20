// PartVendorQuotationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PartVendorQuotationDlg.h"
#include "afxdialogex.h"
#include "PVLinkVendorsItemDlg.h"
#include "PriceBreaksDlg.h"
// CPartVendorQuotationDlg dialog

IMPLEMENT_DYNAMIC(CPartVendorQuotationDlg, CDialogEx)

CPartVendorQuotationDlg::CPartVendorQuotationDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPartVendorQuotationDlg::IDD, pParent)
{
    m_curRow = -1;
    m_curCol = -1;
    m_oldColorRow = -1;
    m_curColorRow = -1;
    m_hParentWnd = NULL;
}

CPartVendorQuotationDlg::~CPartVendorQuotationDlg()
{
}

void CPartVendorQuotationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(CPartVendorQuotationDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CPartVendorQuotationDlg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPartVendorQuotationDlg::OnBnClickedButtonDelete)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPartVendorQuotationDlg::OnNMClickList1)
    ON_MESSAGE(WM_LIST_ITEM_CHANGED,Change_List_Item)
    ON_BN_CLICKED(IDC_BUTTON_EDIT_VENDOR_PRICE, &CPartVendorQuotationDlg::OnBnClickedButtonEditVendorPrice)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPartVendorQuotationDlg::OnNMDblclkList1)
    ON_BN_CLICKED(IDC_UPDATE_ASSEMBLY_COST, &CPartVendorQuotationDlg::OnBnClickedUpdateAssemblyCost)
    ON_BN_CLICKED(IDOK, &CPartVendorQuotationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPartVendorQuotationDlg message handlers


BOOL CPartVendorQuotationDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    pn_table.SearchVendors_BasedOnItem (m_PN_ID);

    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Vendor"), 150, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Cost"), 60, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("AtLevel"), 0, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Primary"), 50, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("VendorP/N"), 0, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("BuyAs"), 100, ListCtrlEx::ComboBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(8, _T("VendorDesc"), 200, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(9, _T("Notes"), 200, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Lead Time"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    g_hwnd_now = this->m_hWnd;
   this->SetWindowTextW(Title);
    pn_table.Initial_UN ();
    Initial_List();

    
    //::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    
   // CRect ViewRect;
    //GetClientRect(&ViewRect);

    int width = GetSystemMetrics ( SM_CXSCREEN ); 
    int height= GetSystemMetrics ( SM_CYSCREEN );
    CRect ViewRect;
    GetClientRect(&ViewRect);

    MoveWindow (width-ViewRect.Width (),height-ViewRect.Height (),ViewRect.Width (),ViewRect.Height ());
     
    //this->MoveWindow()
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
void CPartVendorQuotationDlg::Initial_List()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();

    int i=0;
    for (; i<(int)pn_table.m_dataset_VendorInfor_Part.size(); i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).VendorName);
        m_data_list.SetItemText(i,1,strTemp);

        strTemp.Format(_T("%0.3f"),pn_table.m_dataset_VendorInfor_Part.at(i).Cost);
        m_data_list.SetItemText(i,2,strTemp);

        strTemp.Format(_T("%d"),pn_table.m_dataset_VendorInfor_Part.at(i).AtLevel);
        m_data_list.SetItemText(i,3,strTemp);

        if (pn_table.m_dataset_VendorInfor_Part.at(i).Primary!=0)
        {
            m_data_list.SetCellChecked (i,4,TRUE);
        }
        else
        {
            m_data_list.SetCellChecked (i,4,FALSE);
        }
        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).VendorPN);
        m_data_list.SetItemText(i,5,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).BuyAs);
        m_data_list.SetItemText(i,6,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).LeadTime);
        m_data_list.SetItemText(i,7,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).Vendor_Description);
        m_data_list.SetItemText(i,8,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_VendorInfor_Part.at(i).Notes);
        m_data_list.SetItemText(i,9,strTemp);

        if(ListCtrlEx::ComboBox == m_data_list.GetColumnType(6))
        {
            ListCtrlEx::CStrList strlist;
            for (int j=0; j<(int)pn_table.m_dataset_UN.size (); j++)
            {
                strlist.push_back(pn_table.m_dataset_UN.at(j).UNPurchUnits);
            }
            m_data_list.SetCellStringList(i, 6, strlist);
        }


    }

}

void CPartVendorQuotationDlg::OnBnClickedButtonAdd()
{
    CPVLinkVendorsItemDlg    dlg;
    dlg.m_message_handle = this->m_hWnd;
    dlg.DoModal ();
}


LRESULT CPartVendorQuotationDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if (message == WM_MESSAGE_ADD_VENDORS_ITEM)
    {
        // int SUID =(int)wParam;
        // m_PN_ID
        Vendor_Information_BasedOn_Part ItemVendors;
        ItemVendors.SUID =(int)wParam;
        ItemVendors.PNID =m_PN_ID;
        pn_table.Insert_LNK (ItemVendors);

        pn_table.SearchVendors_BasedOnItem (m_PN_ID);
        Initial_List();
    }

    if (WM_MESSAGE_ITEM_VENDORS_LIST == message)
    {
        g_hwnd_now = this->m_hWnd;
        //this->SetWindowTextW(Title);
        pn_table.SearchVendors_BasedOnItem (m_PN_ID);
        Initial_List();     
    }
    return CDialogEx::WindowProc(message, wParam, lParam);
}


void CPartVendorQuotationDlg::OnBnClickedButtonDelete()
{
    Vendor_Information_BasedOn_Part DeleteItem =   pn_table.m_dataset_VendorInfor_Part.at(m_curRow);
    pn_table.Delete_LNK (DeleteItem);

    pn_table.SearchVendors_BasedOnItem (m_PN_ID);
    Initial_List();

}


void CPartVendorQuotationDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

    }
    if(lRow<pn_table.m_dataset_VendorInfor_Part.size())
    {


        if (lCol == 4)//Qty
        {

            for (int i = 0 ; i< (int) m_data_list.GetRowCount ()-1; i++)
            {
                if (lRow != i)
                {
                    m_data_list.SetCellChecked (i,lCol,FALSE);
                }


            }



        }

        return  ;



        // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }
    *pResult = 0;
}

LRESULT CPartVendorQuotationDlg::Change_List_Item(WPARAM wParam,LPARAM lParam)
{


    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;

  Vendor_Information_BasedOn_Part UpdateItem =   pn_table.m_dataset_VendorInfor_Part.at(m_curRow);
  if (UpdateItem.LNKUNID == 0)
  {
	UpdateItem.LNKUNID = 1;
  }
  if (m_data_list.GetCellChecked (Changed_Item,Changed_SubItem))
  {
	  UpdateItem.Primary = 1;
  }
  else
  {
	  UpdateItem.Primary = 0;
  }
    CString strTemp;
     if (Changed_SubItem == 2)//Qty
     {
         strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
         UpdateItem.Cost = _wtof (strTemp);
 
     }
     if (Changed_SubItem == 3)
     {
         strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
         UpdateItem.AtLevel = _wtoi (strTemp);
     }
    if (Changed_SubItem == 4)
    {
       

    }

    if (Changed_SubItem == 5)
    {
        strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
        UpdateItem.VendorPN = strTemp;
    }
    if (Changed_SubItem == 6)
    {
        strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
        for (int j=0; j<(int)pn_table.m_dataset_UN.size (); j++)
        {
            if (pn_table.m_dataset_UN.at(j).UNPurchUnits.CompareNoCase (strTemp) == 0)
            {
                UpdateItem.LNKUNID = pn_table.m_dataset_UN.at(j).UNID;
                break;
            }

        }


    }
    if (Changed_SubItem == 7)
    {
        strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
        UpdateItem.LeadTime = strTemp;
    }
    if (Changed_SubItem == 8)
    {
        strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
        UpdateItem.Vendor_Description = strTemp;
    }
    if (Changed_SubItem == 9)
    {
        strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
        UpdateItem.Notes = strTemp;
    }

    if (pn_table.Update_LNK (UpdateItem))
    {
        pn_table.SearchVendors_BasedOnItem (m_PN_ID);
        Initial_List();
    }

    return 0;
}


void CPartVendorQuotationDlg::OnBnClickedButtonEditVendorPrice()
{
    if (m_curRow >=0 )
    {
        CPriceBreaksDlg dlg;
        dlg.m_LNKID = pn_table.m_dataset_VendorInfor_Part.at(m_curRow).LNKID;
        if (dlg.DoModal () == IDOK)
        {

            Vendor_Information_BasedOn_Part UpdateItem =   pn_table.m_dataset_VendorInfor_Part.at(m_curRow);
            UpdateItem.Cost = dlg.m_datasector.COSTCost;
            UpdateItem.AtLevel = dlg.m_datasector.COSTAtQty;
            UpdateItem.LeadTime.Format(_T("%d"),dlg.m_datasector.LeadTime);
            if (pn_table.Update_LNK (UpdateItem))
            {
                pn_table.SearchVendors_BasedOnItem (m_PN_ID);
                Initial_List();
            }
        }
    }
    else
    {
        AfxMessageBox (_T("Please select a item!"));
    }


}


void CPartVendorQuotationDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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

    if(lRow<pn_table.m_dataset_VendorInfor_Part.size())
    {



        if (lCol ==2 ||lCol ==3 )
        {
          //  OnBnClickedButtonEditVendorPrice();
        }
        return  ;


        // ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
    }
    *pResult = 0;
}


void CPartVendorQuotationDlg::OnBnClickedUpdateAssemblyCost()
{

}


void CPartVendorQuotationDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here


    BOOL select = FALSE;
    for (int i = 0 ; i< (int) m_data_list.GetRowCount (); i++)
    {
        if (m_data_list.GetCellChecked (i,4))
        {
            m_datasector = pn_table.m_dataset_VendorInfor_Part.at(i);
            select = TRUE;
            break;
        }
    }

    if (select)
    {
        for (int i=0; i<pn_table.m_dataset_VendorInfor_Part.size(); i++)
        {
            pn_table.m_dataset_VendorInfor_Part.at(i).Primary = 0;
            pn_table.Update_LNK (pn_table.m_dataset_VendorInfor_Part.at(i)) ;
        }
        m_datasector.Primary = 1;

        if (pn_table.Update_LNK (m_datasector))
        {

            CDialogEx::OnOK();
        }
        //CDialogEx::OnOK();
    }
    else
    {
        CDialogEx::OnCancel ();
    }

}
