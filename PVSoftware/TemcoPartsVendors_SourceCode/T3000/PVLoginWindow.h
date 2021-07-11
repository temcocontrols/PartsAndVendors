#pragma once
#include "resource.h"

// CPVLoginWindow dialog

class CPVLoginWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CPVLoginWindow)

public:
	CPVLoginWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVLoginWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_BACKGOURD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
