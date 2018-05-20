#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
// CPartVendorQuotationDlg dialog
 
class CPartVendorQuotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPartVendorQuotationDlg)

public:
	CPartVendorQuotationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPartVendorQuotationDlg();

// Dialog Data
	enum { IDD = IDD_PV_VENDOR_QUOTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
     void Initial_List();
public:
    ListCtrlEx::CListCtrlEx m_data_list;
    int m_PN_ID;
   // Table_PN pn_table; 
    CString Title;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
    HANDLE m_hParentWnd;
    Vendor_Information_BasedOn_Part    m_datasector;
    afx_msg void OnBnClickedButtonAdd();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg LRESULT Change_List_Item(WPARAM wParam,LPARAM lParam);
    afx_msg void OnBnClickedButtonEditVendorPrice();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedUpdateAssemblyCost();
    afx_msg void OnBnClickedOk();
};
