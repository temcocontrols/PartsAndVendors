// DebugMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebugMessageDlg.h"
#include "afxdialogex.h"
#include "global_struct.h"
#include "resource.h"
#include "PVDatabase.h"

UINT DataSync(LPVOID pParam)
{
	CDebugMessageDlg* dlg = (CDebugMessageDlg*)(pParam);
	Table_PN datasync;
	datasync.SetMsgHandle(dlg);
	datasync.DataSync();
	AfxMessageBox(L"Data Sync is Successful!");
	return 1;
}
// CDebugMessageDlg dialog

IMPLEMENT_DYNAMIC(CDebugMessageDlg, CDialogEx)

CDebugMessageDlg::CDebugMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DEBUG_MESSAGE, pParent)
{
	
}

CDebugMessageDlg::~CDebugMessageDlg()
{
}

void CDebugMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_lbStatusInfo);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProcessCtrl);
}


BEGIN_MESSAGE_MAP(CDebugMessageDlg, CDialogEx)
	ON_MESSAGE(WM_REPLACE_STATUSINFO, OnReplaceStatusInfo)
	ON_MESSAGE(WM_ADD_STATUSINFO, OnAddStatusInfo)
	ON_BN_CLICKED(IDC_BUTTON_DATA_SYNC, &CDebugMessageDlg::OnBnClickedButtonDataSync)
END_MESSAGE_MAP()

int Add_log_count = 0;
afx_msg LRESULT CDebugMessageDlg::OnAddStatusInfo(WPARAM wParam, LPARAM lParam)
{
	CString strInfo = CString(LPTSTR(lParam));
	int process = int(wParam);
	UpdateStatusInfo(strInfo, false);
	
	WCHAR* szTemp = (LPTSTR(lParam));
	delete[] szTemp;
	m_ProcessCtrl.SetPos(process);
	//UpdateStatusInfo(g_strFlashInfo, false);
	return 1;
}
// CDebugMessageDlg message handlers
afx_msg LRESULT CDebugMessageDlg::OnReplaceStatusInfo(WPARAM wParam, LPARAM lParam)
{
	static int test_loop_count = 0;
	CString strInfo = CString(LPTSTR(lParam));
	int process = int(wParam);
	UpdateStatusInfo(strInfo, true);
	 
	WCHAR* szTemp = (LPTSTR(lParam));
	delete[] szTemp;
	m_ProcessCtrl.SetPos(process);
	//UpdateStatusInfo(g_strFlashInfo, true);
	return 1;
}

////////////////////////////////////////////////////////////////////////////
// ²ÎÊý BOOL, =TRUE replace the current line, =FALSE add a new line
void CDebugMessageDlg::UpdateStatusInfo(const CString& strInfo, BOOL bReplace)
{
	int nLineCount = m_lbStatusInfo.GetCount();
	int nCurrentLineNum = nLineCount;
	if (bReplace)
	{
		nCurrentLineNum--;
		m_lbStatusInfo.DeleteString(nCurrentLineNum);
	}

	int nRet = m_lbStatusInfo.InsertString(nCurrentLineNum, strInfo);
	if (nRet == LB_ERR)
	{
		ASSERT(0);
	}
	m_lbStatusInfo.SetCurSel(nRet);

	UpdateData(FALSE);
}

void CDebugMessageDlg::OnBnClickedButtonDataSync()
{ 
	m_ProcessCtrl.SetRange(0, 100);
	AfxBeginThread(DataSync, this);
}
