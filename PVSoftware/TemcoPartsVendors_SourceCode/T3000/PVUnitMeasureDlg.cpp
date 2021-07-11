// PVUnitMeasureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVUnitMeasureDlg.h"
#include "afxdialogex.h"


// CPVUnitMeasureDlg dialog

IMPLEMENT_DYNAMIC(CPVUnitMeasureDlg, CDialogEx)

CPVUnitMeasureDlg::CPVUnitMeasureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVUnitMeasureDlg::IDD, pParent)
{

    m_strTip=_T("To add a new unit:  Scroll to * record 	Close\n\
                and make new entry there.");
}

CPVUnitMeasureDlg::~CPVUnitMeasureDlg()
{
}

void CPVUnitMeasureDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_TIP, m_strTip);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(CPVUnitMeasureDlg, CDialogEx)

ON_MESSAGE(WM_LIST_ITEM_CHANGED,Change_List_Item)

ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVUnitMeasureDlg::OnNMClickList1)
END_MESSAGE_MAP()


// CPVUnitMeasureDlg message handlers


BOOL CPVUnitMeasureDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    

    pn_table.Initial_UN ();
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));//Not allow full row select.
    m_data_list.InsertColumn(0, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("UseAs"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("How Many In>>"), 150, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("BuyAs"), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    g_hwnd_now = this->m_hWnd; 
    LoadDataToList();
    return TRUE;  
    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPVUnitMeasureDlg::LoadDataToList ()
{
    CString  strTemp;
    m_data_list.DeleteAllItems();
    int i=0;
    for (;i<(int)pn_table.m_dataset_UN.size();i++)
    {
        strTemp.Format(_T("%d"),i+1);
        m_data_list.InsertItem(i,strTemp);
        strTemp.Format(_T("%s"),pn_table.m_dataset_UN.at(i).UNUseUnits);
        m_data_list.SetItemText (i,1,strTemp);

        strTemp.Format(_T("%d"),pn_table.m_dataset_UN.at (i).UNConvUnits);
        m_data_list.SetItemText (i,2,strTemp);

        strTemp.Format(_T("%s"),pn_table.m_dataset_UN.at(i).UNPurchUnits);
        m_data_list.SetItemText (i,3,strTemp);

    }
    strTemp.Format(_T("%d"),i+1);
    m_data_list.InsertItem(i,strTemp);
}

LRESULT CPVUnitMeasureDlg::Change_List_Item(WPARAM wParam,LPARAM lParam)
{   


    int Changed_Item = (int)wParam;
    int Changed_SubItem = (int)lParam;

    if (m_data_list.GetRowCount ()-1 == Changed_Item)
    {
        UN_Struct UpdateItem ;
        CString strTemp; 
        UpdateItem.UNID = -1;
        UpdateItem.UNConvUnits = 1;
        UpdateItem.UNPurchUnits = _T("PCS");
        UpdateItem.UNUseUnits = _T("PCS");
        if (Changed_SubItem == 1)
        {
            strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNUseUnits=strTemp;
        }
        if (Changed_SubItem == 2)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNConvUnits =  _wtoi (strTemp);

        }
        if (Changed_SubItem == 3)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNPurchUnits = strTemp;
        }
        if (pn_table.Insert_UN(UpdateItem))
        {
            pn_table.Initial_UN();
            LoadDataToList(); 
        }  
    } 
    else
    {
        UN_Struct UpdateItem =   pn_table.m_dataset_UN.at(Changed_Item);
        CString strTemp; 
        if (Changed_SubItem == 1)
        {
            strTemp= m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNUseUnits= strTemp;
        }
        if (Changed_SubItem == 2)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNConvUnits =  _wtoi (strTemp);

        }
        if (Changed_SubItem == 3)
        {
            strTemp = m_data_list.GetItemText (Changed_Item,Changed_SubItem);
            UpdateItem.UNPurchUnits = strTemp;
        }
        if (pn_table.Update_UN(UpdateItem))
        {
            pn_table.Initial_UN();
            LoadDataToList(); 
        } 
    }


    return 0;
}



BOOL CPVUnitMeasureDlg::PreTranslateMessage(MSG* pMsg)
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
                
                 UN_Struct UpdateItem =   pn_table.m_dataset_UN.at(m_curRow);
                 if (pn_table.Check_UN (UpdateItem))
                 {
                        AfxMessageBox (_T("You can't delete the unit ,it is using!"));
                        return TRUE;
                 }
                if(pn_table.Delete_UN (UpdateItem))
                {
                        pn_table.Initial_UN();
                        LoadDataToList(); 
                }  
            }

        }
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}


void CPVUnitMeasureDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
    *pResult = 0;
}
