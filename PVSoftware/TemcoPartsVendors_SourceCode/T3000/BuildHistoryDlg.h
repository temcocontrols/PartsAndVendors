#pragma once
#include "resource.h"
#include "..\TreeGrid\GridCtrl_src\GridCtrl.h"
#include "SSplitter.h"
#include "afxwin.h"
#include "PVDatabase.h"

// CBuildHistoryDlg dialog

class CBuildHistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildHistoryDlg)

public:
	CBuildHistoryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBuildHistoryDlg();

// Dialog Data
	enum { IDD = IDD_PV_BUILDHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CGridCtrl m_grid_son;
    CGridCtrl m_grid_main;
    CSSplitter m_splitter;
    virtual BOOL OnInitDialog();
    void LoadMainDataToGrid();
    void LoadSonDataToGrid();
    afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
