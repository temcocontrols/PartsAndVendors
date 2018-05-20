// PVCurrenciesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVCurrenciesDlg.h"
#include "afxdialogex.h"


// CPVCurrenciesDlg dialog

IMPLEMENT_DYNAMIC(CPVCurrenciesDlg, CDialog)

CPVCurrenciesDlg::CPVCurrenciesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPVCurrenciesDlg::IDD, pParent)
{
       m_num =0; 
      m_name =1;
      m_rate =2;
      m_char =3;
}

CPVCurrenciesDlg::~CPVCurrenciesDlg()
{
}

void CPVCurrenciesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
}


BEGIN_MESSAGE_MAP(CPVCurrenciesDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CPVCurrenciesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPVCurrenciesDlg message handlers


void CPVCurrenciesDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    CDialog::OnOK();
}


BOOL CPVCurrenciesDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    /*  
    m_num =0; 
    m_name =1;
    m_rate =2;
    m_char =3;
    */
    m_data_list.ModifyStyle(0, LVS_SINGLESEL | LVS_REPORT | LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  | LVS_EX_GRIDLINES & (~LVS_EX_FULLROWSELECT)); //Not allow full row select.
    m_data_list.InsertColumn(m_num, _T("NUM"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(m_name, _T("Name"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_rate, _T("Exchange Rate"), 80, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(m_char, _T("Char"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    
    pn_table.Load_Currency ();
    
    LoadCurrencyData();
    return TRUE;  
    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CPVCurrenciesDlg::LoadCurrencyData ()
{
     CString strTemp;
     for (int i = 0 ; i<(int)pn_table.m_dataset_Currentcy.size ();i++)
     {
             strTemp.Format (_T("%d"),i);
             m_data_list.InsertItem (i,strTemp);
             m_data_list.SetItemText (i,m_name,pn_table.m_dataset_Currentcy.at(i).CURCurrencyName);
             strTemp.Format (_T("%0.1f"),pn_table.m_dataset_Currentcy.at(i).CURExchangeRate);
             m_data_list.SetItemText (i,m_rate,strTemp);
             m_data_list.SetItemText(i,m_char,pn_table.m_dataset_Currentcy.at(i).CURCurrencyChar);
     }
}
