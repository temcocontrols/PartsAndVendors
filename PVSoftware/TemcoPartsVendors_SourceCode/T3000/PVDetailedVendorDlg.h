#pragma once

#include "PVDatabase.h"
#include "afxdtctl.h"
#include "afxwin.h"
// CPVDetailedVendorDlg dialog
 
class CPVDetailedVendorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVDetailedVendorDlg)

public:
	CPVDetailedVendorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVDetailedVendorDlg();

// Dialog Data
	enum { IDD = IDD_PV_VENDOR_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

   // Table_PN pn_table;
    SU_Struct m_SuItem; 
    CString m_code;
    CString strm_currentcy;
    CString m_account;
    CString m_str_address;
    CString m_name1;
    CString m_phone1;
    CString m_email1;
    CString m_email2;
    CString m_fedid;
    CString m_lastcontactdate;
    CString m_name2;
    CString m_notes;
    CString m_phone2;
    CString m_terms;
    CString m_vendor_name;
    CString m_website;
    CString m_localid;
    
    CUR_Struct m_currency;
    afx_msg void OnBnClickedButtonToday();
    afx_msg void OnBnClickedOk();

    BOOL m_isCreate;
private:
    
public:
    CDateTimeCtrl m_DateTimeCtrl;
    CComboBox m_combox_currency;
};
/*
  heroic/hi rouik/

*/
