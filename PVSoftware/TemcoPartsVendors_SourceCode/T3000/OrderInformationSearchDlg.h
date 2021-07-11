#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include"resource.h"

// COrderInformationSearchDlg dialog

class COrderInformationSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COrderInformationSearchDlg)

public:
	COrderInformationSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COrderInformationSearchDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PV_ORDER_INFORMAtION_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Vendor;
	CString m_partname;
	int type;
	ListCtrlEx::CListCtrlEx m_data_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
