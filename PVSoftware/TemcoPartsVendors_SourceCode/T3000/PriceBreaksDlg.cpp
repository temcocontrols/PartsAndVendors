// PriceBreaksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PriceBreaksDlg.h"
#include "afxdialogex.h"


// CPriceBreaksDlg dialog

IMPLEMENT_DYNAMIC(CPriceBreaksDlg, CDialogEx)

CPriceBreaksDlg::CPriceBreaksDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPriceBreaksDlg::IDD, pParent)
{

}

CPriceBreaksDlg::~CPriceBreaksDlg()
{
}

void CPriceBreaksDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
     
}


BEGIN_MESSAGE_MAP(CPriceBreaksDlg, CDialogEx)
ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPriceBreaksDlg::OnNMClickList1)
ON_MESSAGE(WM_LIST_ITEM_CHANGED,Change_List_Item)
ON_BN_CLICKED(IDOK, &CPriceBreaksDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CPriceBreaksDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
     
    pn_table.Search_Cost_LNK (m_LNKID);
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Select"), 50, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Cost"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("AtLevel"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Lead Time"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    g_hwnd_now = this->m_hWnd; 
    Load_DataToList();
   return TRUE;
 }
// CPriceBreaksDlg message handlers

void CPriceBreaksDlg::Load_DataToList ()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
        int i=0;
    for (;i<(int)pn_table.m_dataset_Cost.size();i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);
        strTemp.Format(_T("%0.1f"),pn_table.m_dataset_Cost.at(i).COSTCost);
        m_data_list.SetItemText (i,2,strTemp);

        strTemp.Format(_T("%0.1f"),pn_table.m_dataset_Cost.at (i).COSTAtQty);
        m_data_list.SetItemText (i,3,strTemp);

        strTemp.Format(_T("%d"),pn_table.m_dataset_Cost.at(i).LeadTime);
        m_data_list.SetItemText (i,4,strTemp);

    }
    strTemp.Format(_T("%d"),i+1);
    m_data_list.InsertItem(i,strTemp);

     
}



void CPriceBreaksDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

    if(lRow<pn_table.m_dataset_Cost.size())
    {

        if (lCol == 1)//Qty
        {
           //  m_data_list.SetCellChecked (lRow,lCol,TRUE);
            for (int i = 0 ;i< (int) m_data_list.GetRowCount ()-1;i++)
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

LRESULT CPriceBreaksDlg::Change_List_Item(WPARAM wParam,LPARAM lParam)
{   


    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;

    if (m_data_list.GetRowCount ()-1 == Changed_Item)
    {
        Cost_Struct UpdateItem ;
        CString strTemp; 
        UpdateItem.COSTLNKID = m_LNKID;
        UpdateItem.COSTCost = 0;
        UpdateItem.COSTAtQty = 0;
        UpdateItem.LeadTime = 0;
        if (Changed_SubItem == 2)
        {
            strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.COSTCost= _wtof (strTemp);
        }
        if (Changed_SubItem == 3)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.COSTAtQty =  _wtoi (strTemp);

        }
        if (Changed_SubItem == 4)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.LeadTime =  _wtoi (strTemp);
        }
        if (pn_table.Insert_Cost(UpdateItem))
        {
            pn_table.Search_Cost_LNK(m_LNKID);
            Load_DataToList(); 
        } 
    } 
    else
    {
        Cost_Struct UpdateItem =   pn_table.m_dataset_Cost.at(m_curRow);
        CString strTemp; 
        if (Changed_SubItem == 2)
        {
            strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.COSTCost= _wtof (strTemp);
        }
        if (Changed_SubItem == 3)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.COSTAtQty =  _wtoi (strTemp);

        }
        if (Changed_SubItem == 4)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.LeadTime =  _wtoi (strTemp);
        }
        if (pn_table.Update_Cost(UpdateItem))
        {
            pn_table.Search_Cost_LNK(m_LNKID);
            Load_DataToList(); 
        } 
    }
  

    return 0;
}


BOOL CPriceBreaksDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if(WM_KEYDOWN == pMsg->message)
    {

        ListCtrlEx::CListCtrlEx* pEdit = (ListCtrlEx::CListCtrlEx*)GetDlgItem(IDC_LIST1);

        ASSERT(pEdit);

        if(pMsg->hwnd == pEdit->GetSafeHwnd() && VK_DELETE == pMsg->wParam)
        {
            if (m_data_list.GetRowCount ()-1 > m_curRow)
           {
                  Cost_Struct UpdateItem =   pn_table.m_dataset_Cost.at(m_curRow);
                  if(pn_table.Delete_Cost (UpdateItem))
                  {
                      pn_table.Search_Cost_LNK(m_LNKID);
                      Load_DataToList(); 
                  }  
           }
                
        }
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


void CPriceBreaksDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    BOOL select = FALSE;
    for (int i = 0 ;i< (int) m_data_list.GetRowCount ()-1;i++)
    {
        if (m_data_list.GetCellChecked (i,1))
        {
            m_datasector = pn_table.m_dataset_Cost.at(i);
            select = TRUE;
            break;
        } 
    }
    if (select)
    {
        CDialogEx::OnOK();
    } 
    else
    {
        CDialogEx::OnCancel ();
    }
    
}
