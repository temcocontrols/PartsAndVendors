#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "afxwin.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDlg.h" 
#include "PVDatabase.h"
 
class CPVBOMDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVBOMDlg)

public:
	CPVBOMDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVBOMDlg();

// Dialog Data
	enum { IDD = IDD_PV_BOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
      ListCtrlEx::CListCtrlEx m_data_list; 
      int m_PN_ID;
	  CString m_strPNumber;
     // Table_PN pn_table; 
      CString Title;
      int m_curRow;
      int m_curCol;
      int m_oldColorRow;
      int m_curColorRow;
      float TotalPrice ;
public:
    
    virtual BOOL OnInitDialog();
    void Set_PN(int PN_ID);
    void Initial_List();
   

    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedButtonAdd();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

    afx_msg LRESULT Change_List_Item(WPARAM wParam,LPARAM lParam);
    afx_msg void OnBnClickedUpdateAssemblyCost();
    afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnPvBom();
	afx_msg void OnBnClickedSaveBomlist();
};
