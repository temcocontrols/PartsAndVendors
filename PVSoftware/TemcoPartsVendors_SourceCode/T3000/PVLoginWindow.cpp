// PVLoginWindow.cpp : implementation file
//

#include "stdafx.h"
#include "PVLoginWindow.h"
#include "afxdialogex.h"

  

// CPVLoginWindow dialog

IMPLEMENT_DYNAMIC(CPVLoginWindow, CDialogEx)

CPVLoginWindow::CPVLoginWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPVLoginWindow::IDD, pParent)
{

}

CPVLoginWindow::~CPVLoginWindow()
{
}

void CPVLoginWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPVLoginWindow, CDialogEx)
	 ON_WM_PAINT()
END_MESSAGE_MAP()


// CPVLoginWindow message handlers


BOOL CPVLoginWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//hBitmap_default_bmp =(HBITMAP)LoadImage(AfxGetInstanceHandle(),  
	//	MAKEINTRESOURCE(IDB_BITMAP_PVLOGO),  
	//	IMAGE_BITMAP,0,0,  
	//	LR_LOADMAP3DCOLORS);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


 void CPVLoginWindow::OnPaint()
 {
 	CPaintDC dc(this); // device context for painting
//  	CMemDC memDC(dc,this);
//  	Graphics graphics(memDC.GetDC());
//  
//  	CRect test_rect;
//  	HWND temp_hwnd = this->m_hWnd;
//  	::GetWindowRect(temp_hwnd,&test_rect);	//获取 view的窗体大小;
//  	Bitmap bitmap(hBitmap_default_bmp,NULL);
//  	graphics.DrawImage(&bitmap,0 ,0,test_rect.Width(),test_rect.Height());
 }
