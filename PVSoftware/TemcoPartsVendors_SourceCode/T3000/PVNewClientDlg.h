#pragma once
#include "Resource.h"

// CPVNewClientDlg dialog

class CPVNewClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVNewClientDlg)

public:
	CPVNewClientDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVNewClientDlg();

// Dialog Data
	enum { IDD = IDD_PV_NEWCLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewClient;
	afx_msg void OnBnClickedOk();
};
