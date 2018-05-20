#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
  
#include "PVDatabase.h"

// CPVBuildDlg dialog
 
class CPVBuildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVBuildDlg)

public:
	CPVBuildDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVBuildDlg();

// Dialog Data
	enum { IDD = IDD_PV_BUILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedItemPn();
    void Initial_List();
     ListCtrlEx::CListCtrlEx m_data_list; 
    int m_PN_ID;
   // Table_PN pn_table; 
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    
    CString m_strTitle;
    CString m_strPN;
    CString m_strDetail;
    float TotalPrice ;
    int  m_curRow  ;
    int  m_curCol  ;
    int m_oldColorRow;
    int m_curColorRow; 
     afx_msg void OnBnClickedBuildListButton();
     UINT m_number_units;
     afx_msg void OnSize(UINT nType, int cx, int cy);
     afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
     afx_msg void OnBnClickedReduceStock();
     afx_msg void OnBnClickedRestock();
};
