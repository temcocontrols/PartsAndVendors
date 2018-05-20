#pragma once
#include "afxcmn.h"
#include "afxbutton.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
 
#include "PVDatabase.h"
 
class CPVDlg : public CDialog
{
	DECLARE_DYNAMIC(CPVDlg)

public:
	CPVDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVDlg();
	BOOL OnInitDialog();
 
// Dialog Data
	enum { IDD = IDD_PARTS_VENDORS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public: 
    afx_msg void OnBnClickedOk();   
    afx_msg void OnBnClickedItemMaster();
    void Load_DataToList();
    void Search_PN_List();
    afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    int m_curRow;
    int m_oldColorRow;
    int m_curColorRow;
    int m_curCol;
    CString m_strPN;
    int m_select_type;
 
    int m_item_number;  
    CMFCButton m_button_item_master;
    ListCtrlEx::CListCtrlEx m_data_list;
//    afx_msg void OnBnClickedButton();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
//    afx_msg void OnEnKillfocusEdit1();

   // Table_PN pn_table;
    afx_msg void OnPvBom();
    afx_msg void OnBnClickedVendor();
    afx_msg void OnBnClickedPo();
 
    afx_msg void OnUpdatePvBom(CCmdUI *pCmdUI);
    afx_msg void OnPvPo();
    afx_msg void OnUpdatePvPo(CCmdUI *pCmdUI);
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
