// PVSetAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVSetAddressDlg.h"
#include "afxdialogex.h"


// CPVSetAddressDlg dialog

IMPLEMENT_DYNAMIC(CPVSetAddressDlg, CDialogEx)

CPVSetAddressDlg::CPVSetAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVSetAddressDlg::IDD, pParent)
{

}

CPVSetAddressDlg::~CPVSetAddressDlg()
{
}

void CPVSetAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPVSetAddressDlg, CDialogEx)
END_MESSAGE_MAP()


// CPVSetAddressDlg message handlers


BOOL CPVSetAddressDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

  

    return TRUE;   
}
