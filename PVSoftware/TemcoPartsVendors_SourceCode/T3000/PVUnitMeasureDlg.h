#pragma once
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
#include "afxcmn.h"
 
// CPVUnitMeasureDlg dialog

class CPVUnitMeasureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVUnitMeasureDlg)

public:
	CPVUnitMeasureDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVUnitMeasureDlg();

// Dialog Data
	enum { IDD = IDD_PV_UNITS_MANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void LoadDataToList();
    afx_msg LRESULT Change_List_Item(WPARAM wParam,LPARAM lParam);
    CString m_strTip;
    Cost_Struct m_datasector;
    int m_LNKID;
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
    int m_curRow;
    int m_curCol;
    HWND m_message_handle;
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
