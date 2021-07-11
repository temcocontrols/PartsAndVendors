#pragma once
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
 

class CItemAndScourceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CItemAndScourceDlg)

public:
	CItemAndScourceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CItemAndScourceDlg();

// Dialog Data
	enum { IDD = IDD_PV_PN_SOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
     void LoadData2List();
    CStaticEx m_Label_Search;
    ListCtrlEx::CListCtrlEx m_data_list;
    CListBox m_select_data;
    CString m_KeyWord;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
   // Table_PN pn_table; 
    afx_msg void OnBnClickedButtonSearch();
    afx_msg void OnBnClickedOk();
     vector<Part_Vendor_Information> m_dataset_selector;
     afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
