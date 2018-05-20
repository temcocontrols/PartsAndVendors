#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "PVDatabase.h"
 
// CPVCurrenciesDlg dialog

class CPVCurrenciesDlg : public CDialog
{
	DECLARE_DYNAMIC(CPVCurrenciesDlg)

public:
	CPVCurrenciesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVCurrenciesDlg();

// Dialog Data
	enum { IDD = IDD_PV_CURRENCY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

    ListCtrlEx::CListCtrlEx m_data_list;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    void LoadCurrencyData();

public:
   // Table_PN pn_table;
    int m_num ; 
    int m_name;
    int m_rate;
    int m_char;
    CUR_Struct m_CItem;
   
};
