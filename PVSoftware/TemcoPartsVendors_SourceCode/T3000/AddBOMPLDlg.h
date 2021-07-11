#pragma once
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
#include "afxcmn.h"
 

// CAddBOMPLDlg dialog

class CAddBOMPLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddBOMPLDlg)

public:
	CAddBOMPLDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddBOMPLDlg();

// Dialog Data
	enum { IDD = IDD_PV_ALL_PARTS };

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
    HWND m_message_handle;

    int m_PN_ID;

    int open_type ;
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
