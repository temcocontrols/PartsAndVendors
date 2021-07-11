#pragma once
#include "afxcmn.h"
#include "resource.h"

// CDBConfigDlg dialog

class CDBConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBConfigDlg)

public:
	CDBConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDBConfigDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DBCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    CIPAddressCtrl m_addressctrl;
};
