#pragma once

#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
#include "afxcmn.h"
#include "NewPNDlg.h"
#include "PartVendorQuotationDlg.h"
 
 
class CPVItemMasterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVItemMasterDlg)

public:
	CPVItemMasterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVItemMasterDlg();

// Dialog Data
	enum { IDD = IDD_PV_ITEMMASTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void Load_DataToList();
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
    afx_msg void OnBnClickedSearch();
    CString m_strPN;
    CString m_strType;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
	int m_currentpagenumber;
     CNewPNDlg *PartWindow;
     CPartVendorQuotationDlg *PartQuatationWindow;
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnPartsCheckbom();
    afx_msg void OnPartsCopynewitem();
    afx_msg void OnPnNewpn();
    afx_msg void OnPartsOpen();
    afx_msg void OnPartsDeleteitem();
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnPartsMaintainvendor();

//    afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnPartsShowassblytree();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    void FreshAllWindows();

	void ShowData();

private:
int m_num;
int m_select;
int m_havevendor;
int m_isorded;
int m_pn;
int m_type;
int m_title;
int m_detail;
int m_rev;
int m_stat;
int m_cost;
int m_brand_vendor;
int m_catalog;
int m_power;
int m_voltage;
int m_tolerance;
int m_part_type;
int m_schematic_part;
int m_allegro_footprint;
int m_solidworks;
public:
	afx_msg void OnMaintainitemDeleteselecteditems();
	afx_msg void OnBnClickedButtonDelete();
	 
 
 
	afx_msg void OnPartsShowpohistory();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	CComboBox m_combox_pagenumber;
	afx_msg void OnPartsExportdata();
	afx_msg void OnCbnSelchangeComboNumber();
};
