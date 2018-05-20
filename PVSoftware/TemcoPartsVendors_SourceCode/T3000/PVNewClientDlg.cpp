// PVNewClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PVNewClientDlg.h"
#include "afxdialogex.h"


// CPVNewClientDlg dialog

IMPLEMENT_DYNAMIC(CPVNewClientDlg, CDialogEx)

CPVNewClientDlg::CPVNewClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVNewClientDlg::IDD, pParent)
	, m_strNewClient(_T(""))
{

}

CPVNewClientDlg::~CPVNewClientDlg()
{
}

void CPVNewClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strNewClient);
}


BEGIN_MESSAGE_MAP(CPVNewClientDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPVNewClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPVNewClientDlg message handlers


void CPVNewClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
