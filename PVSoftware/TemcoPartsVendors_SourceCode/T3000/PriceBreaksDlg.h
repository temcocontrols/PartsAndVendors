
#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
 
// CPriceBreaksDlg dialog

class CPriceBreaksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPriceBreaksDlg)

public:
	CPriceBreaksDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPriceBreaksDlg();

// Dialog Data
	enum { IDD = IDD_PV_PRICE_BREAKS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
     afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
     afx_msg LRESULT Change_List_Item(WPARAM wParam,LPARAM lParam);
public:
    void Load_DataToList();
    Cost_Struct m_datasector;
    int m_LNKID;
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
    int m_curRow;
    int m_curCol;
    HWND m_message_handle;
 
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnBnClickedOk();
};
