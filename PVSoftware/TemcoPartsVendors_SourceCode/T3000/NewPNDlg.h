#pragma once
#include "PVDatabase.h"
#include "afxwin.h"
#include "PictureCtrl.h"
 
class CNewPNDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPNDlg)

public:
	CNewPNDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewPNDlg();

// Dialog Data
	enum { IDD = IDD_PV_NEW_PN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString m_strType;
    CString m_strUnits;
    CString m_strBy;
    CString m_strCurCost;
    CString m_strDetail;
    CString m_strFootPrint;
    CString m_strLastCost;
    CString m_strMiniStock;
    CString m_strNote;
    CString m_strPN;
    CString m_strRevision;
    CString m_strStock;
    CString m_strTitle;
    int m_new_item;

    afx_msg void OnBnClickedOk();
    PN_Struct m_item;
   /* Table_PN table_pn;*/
    virtual BOOL OnInitDialog();
    void LoadData();
    CComboBox m_combox_type;
    CComboBox m_combox_unit;
    CButton m_button_save;
    CButton m_button_cancel;
    BOOL Check_PN();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedSelectPath();
    CString m_image_path;
    afx_msg void OnPaint();
    CPictureCtrl  m_pictureCtrl;
    int m_index;
    HWND m_hParentWnd ;
    afx_msg void OnSize(UINT nType, int cx, int cy);
     CString m_imagefile;
     afx_msg void OnPvOnlypicture();
     afx_msg void OnPvShowall();
     BOOL m_isShowAll;
     BOOL m_saveCloseWindow;
     afx_msg void OnStnDblclickPictureShow();
	 afx_msg void OnBnClickedButtonVendorprice();
};
