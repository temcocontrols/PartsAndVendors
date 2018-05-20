// PVSalesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PVSalesDlg.h"
#include "afxdialogex.h"


// CPVSalesDlg dialog

IMPLEMENT_DYNAMIC(CPVSalesDlg, CDialogEx)

CPVSalesDlg::CPVSalesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVSalesDlg::IDD, pParent)
{

}

CPVSalesDlg::~CPVSalesDlg()
{
}

void CPVSalesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPVSalesDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPVSalesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPVSalesDlg message handlers


void CPVSalesDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
