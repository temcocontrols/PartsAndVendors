
// T3000View.cpp : implementation of the CT3000View class
#include "stdafx.h"
#include "T3000.h"
 
#include "T3000Doc.h"
#include "T3000View.h"
#include "globle_function.h"
//#include "global_variable.h"
#include "global_variable_extern.h"














#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

extern int Mdb_Adress_Map;
extern BOOL m_active_key_mouse;
// CT3000View
//extern BOOL g_bPauseMultiRead;

IMPLEMENT_DYNCREATE(CT3000View, CFormView)
BEGIN_MESSAGE_MAP(CT3000View, CFormView)

	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	 
 
	 

 

	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()

	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_MOVING()
 
 

    ON_WM_HELPINFO()
   
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
 
END_MESSAGE_MAP()

 
CT3000View::CT3000View()
	: CFormView(CT3000View::IDD)
	
{
	// TODO: add construction code here
	
}

CT3000View::~CT3000View()
{
	 
	
 
		
}

void CT3000View::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
 
 

    
  



   
 
}

BOOL CT3000View::PreCreateWindow(CREATESTRUCT& cs)
{																	
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

void CT3000View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
 
 
 
}

 

void CT3000View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CT3000View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}
// CT3000View diagnostics
#ifdef _DEBUG
void CT3000View::AssertValid() const
{
	CFormView::AssertValid();
}

void CT3000View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CT3000Doc* CT3000View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CT3000Doc)));
	return (CT3000Doc*)m_pDocument;
}
#endif //_DEBUG


void CT3000View::OnFileOpen()
{
	// TODO: Add your command handler code here
	
}


HBRUSH CT3000View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	
	switch(pWnd->GetDlgCtrlID())
	{

  

	default:
		return CFormView::OnCtlColor(pDC,pWnd, nCtlColor);
	}
	 
}



 




void CT3000View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CT3000View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

//     if (pScrollBar->m_hWnd == GetDlgItem(IDC_FSB_DAYHOTEL)->m_hWnd)
//     {
//         AfxMessageBox(_T("OK"));
//     }
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}
 

 

BEGIN_EVENTSINK_MAP(CT3000View, CFormView)
	 
END_EVENTSINK_MAP()


void CT3000View::EnableToolTips(BOOL bEnable)   
{   
  
}  
BOOL CT3000View::PreTranslateMessage(MSG* pMsg)
{

// TODO: Add your specialized code here and/or call the base class
 	if(pMsg->message == WM_KEYDOWN  )
 	{
 		if(pMsg->wParam == VK_RETURN)
 		{
            CWnd *temp_focus=GetFocus();	//Maurice require ,click enter and the cursor still in this edit or combobox.
            GetDlgItem(IDC_EDIT1_TEST)->SetFocus();
            temp_focus->SetFocus();
            return TRUE;
 		}
 	}
    CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
    
    
   
     


	return CFormView::PreTranslateMessage(pMsg);
}

void CT3000View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(g_bPauseMultiRead)
		return;
 

	// 更新时间。
	CTime time = CTime::GetCurrentTime();

	CString strtime = time.Format(_T("%I:%M:%S %p"));
	//CString strtime = time.Format(_T("%m/%d/%Y %H:%M:%S %a"));
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RTC_TIME);
	pEdit->SetWindowText(strtime);

	CString strDate = time.Format(_T("%A, %b %d, %Y"));
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RTC);
	pEdit->SetWindowText(strDate);
     int Increment=product_register_value[MODBUS_SETPOINT_INCREASE];

    if (nIDEvent == 10)
    {
        if (m_old_deadband == m_new_deadband)
        {
            KillTimer(10);
        }
       // ++coolvalue;
       if (m_new_deadband > m_old_deadband)
       {
           m_old_deadband+=Increment;
           if (m_slider_Type==1)
           {
            product_register_value[MODBUS_NIGHT_HEATING_DEADBAND]+=Increment;
           }
           if (m_slider_Type==2)
           {
             product_register_value[MODBUS_NIGHT_COOLING_DEADBAND]+=Increment;
           }
           if (m_slider_Type==3)
           {
            product_register_value[MODBUS_NIGHT_SETPOINT]+=Increment;
           }
           if (m_slider_Type==4)
           {
            product_register_value[MODBUS_DAY_HEATING_DEADBAND]+=Increment;
           } 
           if (m_slider_Type==5)
           {
            product_register_value[MODBUS_DAY_COOLING_DEADBAND]+=Increment;
           }
           if (m_slider_Type==6)
           {
            product_register_value[MODBUS_DAY_SETPOINT]+=Increment;
           }
       } 
       if (m_new_deadband < m_old_deadband)
       {
           m_old_deadband-=Increment;
           
           if (m_slider_Type==1)
           {
               product_register_value[MODBUS_NIGHT_HEATING_DEADBAND]-=Increment;
           }
           if (m_slider_Type==2)
           {
               product_register_value[MODBUS_NIGHT_COOLING_DEADBAND]-=Increment;
           }
           if (m_slider_Type==3)
           {
               product_register_value[MODBUS_NIGHT_SETPOINT]-=Increment;
           }
           if (m_slider_Type==4)
           {
               product_register_value[MODBUS_DAY_HEATING_DEADBAND]-=Increment;
           } 
           if (m_slider_Type==5)
           {
               product_register_value[MODBUS_DAY_COOLING_DEADBAND]-=Increment;
           }
           if (m_slider_Type==6)
           {
               product_register_value[MODBUS_DAY_SETPOINT]-=Increment;
           }
       }
       FlexSPN =1;
       FlexSP=1;
        
       
       SendMessage(MESSAGE_SLIDER,0,0);
    }
    /*if (nIDEvent == 11)
    {
        SendMessage(MESSAGE_SLIDER,0,0);
        --coolvalue;
    }*/
	CFormView::OnTimer(nIDEvent);
}

void CT3000View::OnDestroy()
{
	CFormView::OnDestroy();
	
	KillTimer(1);
	// TODO: Add your message handler code here
}





LRESULT CT3000View::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{

return CFormView::WindowProc(message, wParam, lParam);
}

void CT3000View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	

}


void CT3000View::OnMove(int x, int y)
{
	CFormView::OnMove(x, y);
	 
}

void CT3000View::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFormView::OnWindowPosChanging(lpwndpos);

	 
	

}

void CT3000View::OnMoving(UINT fwSide, LPRECT pRect)
{
	CFormView::OnMoving(fwSide, pRect);
	 
}
 

  



 

 
 

 


 


 
 
BOOL CT3000View::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
     
    UINT nID =pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
        nID = ::GetDlgCtrlID((HWND)nID);
        if(nID)
        {
            //  这里就是你要显示的Tooltips，可以根据需要来定制
            CString strToolTips;
           // strToolTips.Format(_T("%d"), m_tipvalue);



            pTTT->lpszText=strToolTips.AllocSysString();

            pTTT->hinst = NULL;
            return(TRUE);
        }
    }

    return(FALSE);
}
