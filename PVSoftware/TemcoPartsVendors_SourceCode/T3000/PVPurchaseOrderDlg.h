#pragma once
#include "AutoRichEditCtrl.h"
#include "afxcmn.h"
#include "PVDatabase.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "afxwin.h"
#include "QPrint.h"
 
// CPVPurchaseOrderDlg dialog
void HeaderFooter(CQPrint*prt,int page,bool hf);
class CPVPurchaseOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVPurchaseOrderDlg)

public:
	CPVPurchaseOrderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVPurchaseOrderDlg();

// Dialog Data
	enum { IDD = IDD_PV_PURCHASE_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    ListCtrlEx::CListCtrlEx  m_data_list;
    CAutoRichEditCtrl m_RichEdit_TO;
    CAutoRichEditCtrl m_RichEdit_Terms;
    CAutoRichEditCtrl m_RichEdit_Date;
    CAutoRichEditCtrl m_RichEdit_Date_Required;
    CAutoRichEditCtrl m_RichEdit_Fob;
    CAutoRichEditCtrl m_RichEdit_Shipping_Method;
    virtual BOOL OnInitDialog();
    void LoadData2List();
    CAutoRichEditCtrl m_RichEdit_SHIP_TO;
   // Table_PN pn_table;
    CStaticEx m_static_account;
    CStaticEx m_static_attn;
    CStaticEx m_static_buyer;
    CStaticEx m_static_phone;
    CStaticEx m_static_contect;
    CStaticEx m_static_purchase_date;
    CStaticEx m_static_po;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg LRESULT Change_Item_List(WPARAM wParam,LPARAM lParam);
    afx_msg void OnBnClickedButtonPrintExcel();
	afx_msg void OnBnClickedButtonPrint();
};
