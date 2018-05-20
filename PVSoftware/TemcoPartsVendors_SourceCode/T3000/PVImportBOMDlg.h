#pragma once
#include "afxwin.h"
#include "CM5/ListCtrlEx.h"
#include "CM5/CStatic/staticex.h"
#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
#include "afxcmn.h"

 
// CPVImportBOMDlg dialog

class CPVImportBOMDlg : public CDialogEx {
    DECLARE_DYNAMIC(CPVImportBOMDlg)

public:
    CPVImportBOMDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CPVImportBOMDlg();

// Dialog Data
    enum { IDD = IDD_PV_IMPORT_BOM };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    ListCtrlEx::CListCtrlEx m_data_list;
    afx_msg void OnBnClickedBomPath();
    virtual BOOL OnInitDialog();

    void Initial_List();
    vector<CString>				m_BOMContent;
    vector<vector<CString>>        m_fileContent;
    vector<PN_Struct> m_InsertItems;
    CStdioFile*					m_pFile;
    CString m_strFilePath;
    afx_msg void OnBnClickedNewPn();
    CComboBox m_combox_PN;
   // Table_PN pn_table;
    PN_Struct m_parentItem;
    afx_msg void OnBnClickedButtonReload();
    afx_msg void OnBnClickedOk();
    afx_msg void OnCbnSelchangeEditPn();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
 
    int m_oldColorRow;
    int m_curColorRow;
    int m_curRow ;
    int m_curCol ;
};
