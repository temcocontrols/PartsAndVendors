#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDebugMessageDlg dialog

class CDebugMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDebugMessageDlg)

public:
	CDebugMessageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDebugMessageDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEBUG_MESSAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnAddStatusInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReplaceStatusInfo(WPARAM wParam, LPARAM lParam);
	void UpdateStatusInfo(const CString& strInfo, BOOL bReplace);
public:
	CListBox m_lbStatusInfo;
	afx_msg void OnBnClickedButtonDataSync();
	CProgressCtrl m_ProcessCtrl;
};
