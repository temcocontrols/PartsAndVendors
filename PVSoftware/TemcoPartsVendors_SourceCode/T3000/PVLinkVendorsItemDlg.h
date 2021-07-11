#pragma once
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
#include "afxcmn.h"
 
// CPVLinkVendorsItemDlg dialog

class CPVLinkVendorsItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVLinkVendorsItemDlg)

public:
	CPVLinkVendorsItemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVLinkVendorsItemDlg();

// Dialog Data
	enum { IDD = IDD_PV_LINK_VENDORS_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void Load_DataToList();
    CString m_StrVendorName;
    CString m_StrVendorCode;
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
    HWND m_message_handle;
    afx_msg void OnBnClickedSearch();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdd();
};
