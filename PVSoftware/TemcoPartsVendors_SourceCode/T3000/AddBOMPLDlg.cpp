// AddBOMPLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "AddBOMPLDlg.h"
#include "afxdialogex.h"


// CAddBOMPLDlg dialog

IMPLEMENT_DYNAMIC(CAddBOMPLDlg, CDialogEx)

CAddBOMPLDlg::CAddBOMPLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddBOMPLDlg::IDD, pParent)
{
  open_type = -1;
  m_curRow = -1;
  m_curCol = -1;
  m_oldColorRow = -1;
  m_curColorRow = -1;
}

CAddBOMPLDlg::~CAddBOMPLDlg()
{
}

void CAddBOMPLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Text(pDX, IDC_EDIT_PN, m_strPN);
    DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
}


BEGIN_MESSAGE_MAP(CAddBOMPLDlg, CDialogEx)
ON_BN_CLICKED(IDC_SEARCH, &CAddBOMPLDlg::OnBnClickedSearch)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CAddBOMPLDlg::OnNMDblclkList1)
ON_NOTIFY(NM_CLICK, IDC_LIST1, &CAddBOMPLDlg::OnNMClickList1)
END_MESSAGE_MAP()


// CAddBOMPLDlg message handlers


BOOL CAddBOMPLDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    while(m_data_list.DeleteColumn(0));
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("P/N"), 140, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Type"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("Title"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Detail"), 200, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Rev"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Stat"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(7, _T("Cur.Cost"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);

//     CRect ViewRect;
//     GetClientRect(&ViewRect);
//     // CRect listRect;
//     //m_data_list.GetClientRect(&listRect);
//     if (m_data_list.GetSafeHwnd())
//     {
//         m_data_list.MoveWindow(CRect(0,30/*listRect.top*/,ViewRect.Width(),ViewRect.Height()-10),TRUE);
//     }
    if (open_type == 1)
    {
        GetDlgItem (IDC_COMBO_TYPE)->ShowWindow (SW_HIDE);
    } 
    
    Load_DataToList ();


    GetDlgItem(IDC_EDIT_PN)->SetFocus ();

    return FALSE;   
}

void CAddBOMPLDlg::Load_DataToList(){
    // pn_table.Initial_Data();
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


void CAddBOMPLDlg::OnBnClickedSearch()
{
    UpdateData(TRUE);
    m_strPN.TrimLeft ();
    m_strPN.TrimRight ();
    m_strType.TrimLeft ();
    m_strType.TrimRight ();
    if (m_strType.CompareNoCase (_T("All"))==0)
    {
        m_strType = _T("");
    }
    //pn_table.Search_Data_ByPN(m_strPN,m_strType);
	pn_table.Load_Assembly_Data(m_strPN);
    Load_DataToList();
}


void CAddBOMPLDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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

//     if (lCol == 0)
//     {
// 
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
// 
//     }

    if(lRow<pn_table.pv_Table_PN.size())
    {
       /* CNewPNDlg dlg;
        dlg.m_new_item = 2;
        dlg.m_item = pn_table.pv_Table_PN.at(m_curRow);
        dlg.DoModal(); */
        
        ::PostMessage (m_message_handle,WM_MESSAGE_FRESH_BOM,pn_table.pv_Table_PN.at(m_curRow).PNID,0);
        if (open_type == 1)
        {
                CDialogEx::OnOK();
        }
    }

    *pResult = 0;
}


void CAddBOMPLDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


BOOL CAddBOMPLDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if(pMsg->message==WM_KEYDOWN)
    {
        

        if (pMsg->wParam ==VK_RETURN)
        {
            OnBnClickedSearch();
            return TRUE;
        }
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}
