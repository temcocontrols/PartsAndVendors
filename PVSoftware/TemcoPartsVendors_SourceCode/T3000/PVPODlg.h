#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
 
// CPVPODlg dialog

class CPVPODlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVPODlg)

public:
	CPVPODlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVPODlg();
    
// Dialog Data
	enum { IDD = IDD_PV_PO };

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
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedDelOrders();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedOk();
	void ShowData();
    CString m_strPO;
    CString m_strVendorName;
};
