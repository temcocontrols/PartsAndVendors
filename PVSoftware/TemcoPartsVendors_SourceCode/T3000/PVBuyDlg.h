#pragma once
#include "afxwin.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
#include "afxcmn.h"
 
// CPVBuyDlg dialog

class CPVBuyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVBuyDlg)

public:
	CPVBuyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVBuyDlg();

// Dialog Data
	enum { IDD = IDD_PV_BUY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CStaticEx m_lable_PL;
    int m_PN_ID;
    float TotalPrice ;
    ListCtrlEx::CListCtrlEx m_data_list;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    CString m_strPN;
    CString m_strPO;
    CString m_strTitle;
    CString m_strDetail;
    UINT m_number_units;
    int m_curRow;
    int m_curCol;
    int m_oldColorRow;
    int m_curColorRow;
   // Table_PN pn_table; 
    afx_msg void OnBnClickedBuildListButton();
    afx_msg void OnBnClickedSendToPo();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedItemPn();
    void LoadData2BuyList();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedDelItem();
    afx_msg void OnBnClickedAddItem();
    afx_msg LRESULT Change_Item_List(WPARAM wParam,LPARAM lParam);
private:
    short m_num;
	short m_qty;
	short m_ref;
    short m_title;
    short m_detail;
	short m_pn;
    short m_note;
    short m_totalqty;

    short m_stock;
    short m_needtobuy;
    short m_orderQty;

    short m_unitprice;
    short m_totalprice;
    short m_vendor;
    short m_vendorpn;
    BOOL m_hide_show;
    
    

    vector<PO_Struct> m_allpos;
public:
    afx_msg void OnBnClickedButtonDelAll();
    CString m_strEngrgContact;
    CString m_strBuyer;
    CString m_strShipAddress;
    afx_msg void OnBnClickedShowHide();

 
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonNewpn();
	afx_msg void OnBnClickedButtonSavetodb();
};
