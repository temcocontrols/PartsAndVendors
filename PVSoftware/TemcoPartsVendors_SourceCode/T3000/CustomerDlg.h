#pragma once
#include "Resource.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
#include "bado/BADO.h"
// CCustomerDlg dialog

class CCustomerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomerDlg();

// Dialog Data
	enum { IDD = IDD_PV_CUSTOMER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();


	afx_msg void OnSize(UINT nType, int cx, int cy);
	ListCtrlEx::CListCtrlEx m_data_list;
	afx_msg void OnBnClickedShowHide();

 

void DataBound();

private:
	CString m_StrCustomerName;
	CString m_StrCustomerAddress;
	CString m_StrCustomerNotes;
	CString m_StrCONName1;
	CString m_StrCONPhone1;
	CString m_StrCONEmail1;
	CString m_StrCONEmail2;
	CString m_StrCONFax;
	CString m_StrCustomerWebAddress;
	CString m_StrShipmentAddress;
	CString m_StrAccount;
	CString m_StrAccountCode;
	CString m_StrAccountFedID;
	CString m_StrAccountLocalID;
	CString m_StrCONName2;
	CString m_StrCONPhone2;
	CString m_StrAccountTerms;
public:
Table_PN pn_table; 

int m_curRow;
int m_curCol;
int m_oldColorRow;
int m_curColorRow;
CU_Struct m_Current_Customer;
BOOL m_hide_show ; 
public:
	virtual BOOL OnInitDialog();
	void LoadData2List();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_StrSearchData;
	CComboBox m_Combox_CustomerName;
	afx_msg void OnCbnSelchangeCustomername();
	afx_msg void OnBnClickedAdd();

	void ShowData();
};
