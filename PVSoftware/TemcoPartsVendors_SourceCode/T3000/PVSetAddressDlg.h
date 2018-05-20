#pragma once
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
#include "afxcmn.h"
 
// CPVSetAddressDlg dialog

class CPVSetAddressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPVSetAddressDlg)

public:
	CPVSetAddressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVSetAddressDlg();

// Dialog Data
	enum { IDD = IDD_PV_SETTING_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
private:
    ListCtrlEx::CListCtrlEx m_data_list;
   // Table_PN pn_table;
};
