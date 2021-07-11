#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
 
#include "afxwin.h"

// CPVVendorDlg dialog

class CPVVendorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVVendorDlg)

public:
	CPVVendorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVVendorDlg();

// Dialog Data
	enum { IDD = IDD_PV_VENDOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
virtual BOOL OnInitDialog();
void Load_DataToList();
public:
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedButtonNew();
    afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnVendorsMaintainvendors();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnVendorsDeletevendor();
    afx_msg void OnVendorsNewvendor();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonChange();
    afx_msg void OnBnClickedOk();
	void  ShowData();
    CString m_strVendorName;
	afx_msg void OnBnClickedButtonShowPo();
	afx_msg void OnBnClickedButtonEditVendorPrice();
};
