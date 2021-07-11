// BuildHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BuildHistoryDlg.h"
#include "afxdialogex.h"
 #include "T3000.h"


// CBuildHistoryDlg dialog

IMPLEMENT_DYNAMIC(CBuildHistoryDlg, CDialogEx)

CBuildHistoryDlg::CBuildHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuildHistoryDlg::IDD, pParent)
{

}

CBuildHistoryDlg::~CBuildHistoryDlg()
{
}

void CBuildHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID_SON, m_grid_son);
    DDX_Control(pDX, IDC_GRID_MAIN, m_grid_main);
    DDX_Control(pDX, IDC_STATIC_SPLITTER, m_splitter);
}


BEGIN_MESSAGE_MAP(CBuildHistoryDlg, CDialogEx)
    ON_WM_SIZE()
    ON_NOTIFY(NM_DBLCLK, IDC_GRID_MAIN, OnGridDblClick)
END_MESSAGE_MAP()


// CBuildHistoryDlg message handlers


BOOL CBuildHistoryDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
   
    CRect ViewRect;
    GetClientRect(&ViewRect);
       CWnd* pWnd = GetDlgItem(IDC_STATIC_SPLITTER);
    if(pWnd->GetSafeHwnd())
    {
        pWnd->MoveWindow(CRect(0, 0, ViewRect.Width(), ViewRect.Height()), TRUE);
    }

    CRect rect;

   
    pWnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    pWnd->DestroyWindow();

    m_splitter.Create(
        WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN|SS_VERT, 		 
        this,
        &m_grid_main,
        &m_grid_son,
        IDC_RE_PAGE2,
        rect,
        330, // left constraint for splitter position
        40 // right constraint for splitter position
        );
        pn_table.Search_BuyMainTable(L"");
        CString strbuyid;
        strbuyid.Format(L"%d",pn_table.m_dataset_BuyMainTable.at(0).BuyID);
        pn_table.Search_BuyDetailsTable(strbuyid);
        LoadMainDataToGrid();
        LoadSonDataToGrid();
       return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuildHistoryDlg::LoadMainDataToGrid()
{
          m_grid_main.SetColumnCount(6);
          m_grid_main.SetRowCount(pn_table.m_dataset_BuyMainTable.size()+1);  
          m_grid_main.SetItemText(0,0,L"NUM");  
          m_grid_main.SetItemText(0,1,L"#PO"); 
          m_grid_main.SetItemText(0,2,L"BuildTime");   
          m_grid_main.SetItemText(0,3,L"Buyer");  
          m_grid_main.SetItemText(0,4,L"PN");
          m_grid_main.SetItemText(0,5,L"Qty");
          m_grid_main.SetItemText(0,6,L"Detail");
          for (int i=0;i<pn_table.m_dataset_BuyMainTable.size();i++)
          {
             CString strTemp;
             int Row = i+1;
             strTemp.Format(_T("%d"),Row);
             m_grid_main.SetItemText(Row,0,strTemp);  
             strTemp = pn_table.m_dataset_BuyMainTable.at(i).POBegin;
             m_grid_main.SetItemText(Row,1,strTemp);  
            strTemp = pn_table.m_dataset_BuyMainTable.at(i).FullTime;
             m_grid_main.SetItemText(Row,2,strTemp);  
             strTemp = pn_table.m_dataset_BuyMainTable.at(i).Buyer;
             m_grid_main.SetItemText(Row,3,strTemp);  
             strTemp = pn_table.m_dataset_BuyMainTable.at(i).PN;
             m_grid_main.SetItemText(Row,4,strTemp);  
             strTemp.Format(_T("%d"),pn_table.m_dataset_BuyMainTable.at(i).BuyQty);
             m_grid_main.SetItemText(Row,5,strTemp);  
              strTemp = pn_table.m_dataset_BuyMainTable.at(i).Details;
             m_grid_main.SetItemText(Row,6,strTemp);  
          }
          m_grid_main.AutoSize();
          m_grid_main.SetFixedRowCount(1);
          m_grid_main.SetFixedColumnCount(1);
}
void CBuildHistoryDlg::LoadSonDataToGrid()
{
    m_grid_son.SetColumnCount(14);
    m_grid_son.SetRowCount(pn_table.m_dataset_BuyDetailsTable.size()+1);  
    m_grid_son.SetItemText(0,0,L"NUM");  
    m_grid_son.SetItemText(0,1,L"Qty"); 
    m_grid_son.SetItemText(0,2,L"Reference");   
    m_grid_son.SetItemText(0,3,L"Value");  
    m_grid_son.SetItemText(0,4,L"Description");
    m_grid_son.SetItemText(0,5,L"PN");
    m_grid_son.SetItemText(0,6,L"Note");
    m_grid_son.SetItemText(0,7,L"Use Qty");
    m_grid_son.SetItemText(0,8,L"Item Stock");
    m_grid_son.SetItemText(0,9,L"Need To Buy");
    m_grid_son.SetItemText(0,10,L"Order Qty");
    m_grid_son.SetItemText(0,11,L"Unit Price");
    m_grid_son.SetItemText(0,12,L"Total Price");
    m_grid_son.SetItemText(0,13,L"Vendor");
    for (int i=0;i<pn_table.m_dataset_BuyDetailsTable.size();i++)
    {
        CString strTemp;
        int Row = i+1;  
        strTemp.Format(_T("%d"),Row);
        m_grid_son.SetItemText(Row,0,strTemp);  
        strTemp.Format(_T("%d"),pn_table.m_dataset_BuyDetailsTable.at(i).Qty);
        m_grid_son.SetItemText(Row,1,strTemp); 
        strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).Reference;
        m_grid_son.SetItemText(Row,2,strTemp); 
         strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).Value;
        m_grid_son.SetItemText(Row,3,strTemp); 
         strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).Description;
        m_grid_son.SetItemText(Row,4,strTemp);
         strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).PN; 
        m_grid_son.SetItemText(Row,5,strTemp); 
        strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).strNote; 
        m_grid_son.SetItemText(Row,6,strTemp);
         strTemp.Format(_T("%d"),pn_table.m_dataset_BuyDetailsTable.at(i).UseQty); 
        m_grid_son.SetItemText(Row,7,strTemp); 
         strTemp.Format(_T("%d"),pn_table.m_dataset_BuyDetailsTable.at(i).ItemStock);
        m_grid_son.SetItemText(Row,8,strTemp); 
        strTemp.Format(_T("%d"),pn_table.m_dataset_BuyDetailsTable.at(i).Need2Buy);
        m_grid_son.SetItemText(Row,9,strTemp); 
         strTemp.Format(_T("%d"),pn_table.m_dataset_BuyDetailsTable.at(i).OrderQty);
        m_grid_son.SetItemText(Row,10,strTemp); 
        strTemp.Format(_T("%.3f"),pn_table.m_dataset_BuyDetailsTable.at(i).UnitPrice);
        m_grid_son.SetItemText(Row,11,strTemp); 
        pn_table.m_dataset_BuyDetailsTable.at(i).TotalPrice =pn_table.m_dataset_BuyDetailsTable.at(i).UnitPrice*pn_table.m_dataset_BuyDetailsTable.at(i).OrderQty; 
         strTemp.Format(_T("%.2f"),pn_table.m_dataset_BuyDetailsTable.at(i).TotalPrice);
        m_grid_son.SetItemText(Row,12,strTemp);
         strTemp = pn_table.m_dataset_BuyDetailsTable.at(i).VendorName; 
        m_grid_son.SetItemText(Row,13,strTemp); 
    }
    m_grid_son.AutoSize();
    m_grid_son.SetFixedRowCount(1);
    m_grid_son.SetFixedColumnCount(1);
}



void CBuildHistoryDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    if(nType == SIZE_RESTORED)
    {
        
        CRect ViewRect;
        GetClientRect(&ViewRect);

        if(m_splitter.GetSafeHwnd())
        {
            m_splitter.MoveWindow(CRect(0, 0, ViewRect.Width(), ViewRect.Height()), TRUE);
        }

    }
    
}
void CBuildHistoryDlg::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    /*Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);*/
    int row =   pItem->iRow;
    int BuyID = pn_table.m_dataset_BuyMainTable.at(row-1).BuyID;
    CString strBuyID;
    strBuyID.Format(_T("%d"),BuyID);
    pn_table.Search_BuyDetailsTable(strBuyID);
 
    LoadSonDataToGrid();
}