
// T3000View.h : interface of the CT3000View class
//

#pragma once

#include "MainFrm.h"
#include "afxwin.h"
#include "afxcmn.h"








#include "singleslider/MacSliderCtrl.h"
#include "AutoRichEditCtrl.h"
#include "CM5/CStatic/staticex.h"
//#include "TemcoDataGrid.h"
#define WM_FRESHVIEW WM_USER + 1100


//#define  DaySP		0  //address 345
//#define  DcoolDB	1  //address 346
//#define  DheatDB	2  //address 347
//#define  DcoolSP	3  //address 348
//#define  DheatSP	4  //address 349
//#define  NightSP	5  //address 350
//#define  NheatDB	6  //address 352
//#define  NcoolDB	7  //address 353
//#define  NheatSP	8  //address 354
//#define  NcoolSP	9  //address 355
//#define  Max		10  //address 365
//#define  Min		11  //address 366


class CT3000View : public CFormView
{
public: // create from serialization only
	CT3000View();
	DECLARE_DYNCREATE(CT3000View)

public:
	enum{ IDD = IDD_T3000_FORM };

// Attributes
public:
	CT3000Doc* GetDocument() const;



public:
	
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
 
// Implementation
public:
	virtual ~CT3000View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//protected:
////	CMFCStatusBar& GetStatusBar () const
//	{
//		return ((CMainFrame*) AfxGetMainWnd ())->GetStatusBar ();
//	}
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void OnFileOpen();

	
	int m_InRanges[10];
	int m_OutRanges[10];
public:
	// scan Tstats in database
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult); 
	 
 


	int m_outRows;
	int m_inRows;


 
	CTabCtrl m_SetPtTabCtrl;
    

 
  
 
	
 
	CEdit m_inNameEdt;
	CEdit m_outNameEdt;

	CAutoRichEditCtrl m_DayCoolEdit;
	CAutoRichEditCtrl m_DayHeatEdit;
	CStatic m_DayCoolStatic;
	CStatic m_DaySPStatic;
	CStatic m_DayHeatStatic;

    int m_new_deadband;
    int m_old_deadband;
    int m_slider_Type; 
	

	 
	DECLARE_EVENTSINK_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	
	static void EnableToolTips(BOOL bEnable);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);





	
     
     //afx_msg void OnBnClickedTestSlider();
};

#ifndef _DEBUG  // debug version in T3000View.cpp
inline CT3000Doc* CT3000View::GetDocument() const
   { return reinterpret_cast<CT3000Doc*>(m_pDocument); }
#endif

