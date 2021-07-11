#pragma once


// CPNDlg dialog

class CPNDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPNDlg)

public:
	CPNDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPNDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
