#pragma once
#include "Resource.h"

// CPVSalesDlg dialog

class CPVSalesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVSalesDlg)

public:
	CPVSalesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVSalesDlg();

// Dialog Data
	enum { IDD = IDD_PV_SALES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
