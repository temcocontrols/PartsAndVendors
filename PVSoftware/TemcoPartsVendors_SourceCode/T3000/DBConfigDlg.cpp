// DBConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBConfigDlg.h"
#include "afxdialogex.h"
#include "T3000.h"


// CDBConfigDlg dialog

IMPLEMENT_DYNAMIC(CDBConfigDlg, CDialogEx)

CDBConfigDlg::CDBConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBConfigDlg::IDD, pParent)
{

}

CDBConfigDlg::~CDBConfigDlg()
{
}

void CDBConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IPADDRESS1, m_addressctrl);
}


BEGIN_MESSAGE_MAP(CDBConfigDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDBConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDBConfigDlg message handlers


BOOL CDBConfigDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CString g_configfile_path = g_strExePth + _T("T3000_config.ini");
    CString strIPAddress;
    GetPrivateProfileString(_T("PVDBSETTING"),_T("SERVERIP"),_T("127.0.0.1"),strIPAddress.GetBuffer(MAX_PATH),MAX_PATH,g_configfile_path);
    //WritePrivateProfileStringW(L"PVDBSETTING", L"PONUMBER", pn_table.m_dataset_purchaseorder.at(0).POMNumber, g_configfile_path);
     
       m_addressctrl.SetWindowTextW(strIPAddress)    ;


    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CDBConfigDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
     CString g_configfile_path = g_strExePth + _T("T3000_config.ini");
     CString strIPAddress;
     m_addressctrl.GetWindowTextW(strIPAddress);
    WritePrivateProfileStringW(L"PVDBSETTING", L"SERVERIP", strIPAddress, g_configfile_path);
    CDialogEx::OnOK();
}
