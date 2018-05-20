// NewPNDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "NewPNDlg.h"
#include "afxdialogex.h"
#include "globle_function.h"
#include "FileOperations.h"

// CNewPNDlg dialog

IMPLEMENT_DYNAMIC(CNewPNDlg, CDialogEx)

CNewPNDlg::CNewPNDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CNewPNDlg::IDD, pParent)
    , m_image_path(_T(""))
{
    m_strType = _T("PS");
    m_strUnits = _T("each");
    m_strBy = _T("");
    m_strCurCost = _T("");
    m_strDetail = _T("");
    m_strFootPrint = _T("");
    m_strLastCost = _T("");
    m_strMiniStock = _T("");
    m_strNote = _T("");
    m_strPN = _T("");
    m_strRevision = _T("");
    m_strStock = _T("");
    m_strTitle = _T("");
    m_index = -1;
    m_isShowAll = TRUE;

    m_saveCloseWindow     = FALSE;

}

CNewPNDlg::~CNewPNDlg()
{

}

void CNewPNDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
    DDX_CBString(pDX, IDC_COMBO_UNITS, m_strUnits);
    DDX_Text(pDX, IDC_EDIT_BY, m_strBy);
    DDX_Text(pDX, IDC_EDIT_CUR_COST, m_strCurCost);
    DDX_Text(pDX, IDC_EDIT_DETAIL, m_strDetail);
    DDX_Text(pDX, IDC_EDIT_FOOT_PRINT, m_strFootPrint);
    DDX_Text(pDX, IDC_EDIT_LAST_COST, m_strLastCost);
    DDX_Text(pDX, IDC_EDIT_MINI_STOCK, m_strMiniStock);
    DDX_Text(pDX, IDC_EDIT_NOTE, m_strNote);
    DDX_Text(pDX, IDC_EDIT_PN, m_strPN);
    DDX_Text(pDX, IDC_EDIT_REVISION, m_strRevision);
    DDX_Text(pDX, IDC_EDIT_STOCK, m_strStock);
    DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_combox_type);
    DDX_Control(pDX, IDC_COMBO_UNITS, m_combox_unit);
    DDX_Control(pDX, IDOK, m_button_save);
    DDX_Control(pDX, IDCANCEL, m_button_cancel);
    DDX_Text(pDX, IDC_IMAGE_PATH, m_image_path);
    DDX_Control(pDX, IDC_PICTURE_SHOW, m_pictureCtrl);
}


BEGIN_MESSAGE_MAP(CNewPNDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CNewPNDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_SELECT_PATH, &CNewPNDlg::OnBnClickedSelectPath)
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_COMMAND(ID_PV_ONLYPICTURE, &CNewPNDlg::OnPvOnlypicture)
    ON_COMMAND(ID_PV_SHOWALL, &CNewPNDlg::OnPvShowall)
    ON_STN_DBLCLK(IDC_PICTURE_SHOW, &CNewPNDlg::OnStnDblclickPictureShow)
	ON_BN_CLICKED(IDC_BUTTON_VENDORPRICE, &CNewPNDlg::OnBnClickedButtonVendorprice)
END_MESSAGE_MAP()


void CNewPNDlg::OnBnClickedOk()
{
    UpdateData(TRUE);
   /* if (!Check_PN())
    {
        AfxMessageBox(_T("Item already exists in database."));
        return;
    }*/
    m_item.PNType = m_strType;
    for (int i=0; i<pn_table.m_dataset_UN.size(); i++)
    {
        if (m_strUnits.CompareNoCase(pn_table.m_dataset_UN.at(i).UNUseUnits)==0)
        {
            m_item.PNUNID = pn_table.m_dataset_UN.at(i).UNID;
        }
    }
    m_item.ReqBy=m_strBy ;
    m_item.PNCurrentCost = _wtof(m_strCurCost);
    m_item.PNDetail = m_strDetail;
    m_item.PNPrintFooter = m_strFootPrint;
    m_item.PNLastRollupCost = _wtof(m_strLastCost);
    m_item.PNMinStockQty = _wtof(m_strMiniStock);
    m_item.PNNote.Format(_T("%s"),m_strNote);
    m_item.PNPartNumber.Format(_T("%s"),m_strPN);
    m_item.PNRevision.Format(_T("%s"), m_strRevision);
    m_item.Stock=_wtof(m_strStock);
    m_item.PNTitle.Format(_T("%s"),m_strTitle);
    if (!m_image_path.IsEmpty())
    {
        HANDLE hFind;//
        WIN32_FIND_DATA wfd;//
        hFind = FindFirstFile(m_image_path, &wfd);//
        if (hFind!=INVALID_HANDLE_VALUE)//说明当前目录下无t3000.mdb
        {
            CString strSuffix ;
            CString stroldfilename;
            if (!m_item.PNImageName.IsEmpty ())
            {
              stroldfilename = pn_table.GetImageFileFold () +m_item.PNImageName;
            }
            strSuffix.Format (_T(".%s"), m_image_path.Right (3));
            m_item.PNImageName = NewGUID () + strSuffix;
            CString strDest;
            strDest= pn_table.GetImageFileFold () +m_item.PNImageName;
            CopyFile(m_image_path,strDest,FALSE);
            DeleteFile(stroldfilename);
        }
         
    }
    if (m_new_item == 2)
    {
		pn_table.Update_ByPN (m_item);
      //  ::PostMessageA (m_hParentWnd,WM_MESSAGE_ITEM_MASTER,0,0);
       // table_pn.pv_Table_PN[m_index] = m_item;
    }
    if (m_new_item == 1||m_new_item == 0)
    {
       m_item= pn_table.Insert_ByPN (m_item);
      // table_pn.pv_Table_PN.push_back (m_item);

      // ::PostMessageA (m_hParentWnd,WM_MESSAGE_ITEM_MASTER,0,0);
    }

  //  ::PostMessageA (m_hParentWnd,WM_MESSAGE_ITEM_RELOAD_ALLDATA,0,0);

    AfxMessageBox(_T("Save to Database,successfully"));

    if (m_saveCloseWindow)
    {
       CDialogEx::OnOK ();
    } 
    
   // 

}


BOOL CNewPNDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	 pn_table.Initial_Type();
	 pn_table.Initial_UN();
     //table_pn.Initial_Data ();
     for (int i=0; i<pn_table.m_dataset_type.size(); i++)
     {
         m_combox_type.AddString(pn_table.m_dataset_type.at(i).TYPEType);
     }
     for (int i=0; i<pn_table.m_dataset_UN.size(); i++)
     {
         m_combox_unit.AddString(pn_table.m_dataset_UN.at(i).UNUseUnits);
     }
     int width = GetSystemMetrics ( SM_CXSCREEN ); 
     int height= GetSystemMetrics ( SM_CYSCREEN );
     CRect ViewRect;
     GetClientRect(&ViewRect);

     MoveWindow (width-ViewRect.Width (),0,ViewRect.Width (),ViewRect.Height ()+50);



	 //m_combox_type.ResetContent();
	 //for (int i = 0; i < pn_table.m_dataset_type.size(); i++)
	 //{
		// m_combox_type.AddString(pn_table.m_dataset_type.at(i).TYPEType);
	 //}
	 //m_combox_unit.ResetContent();
	 //for (int i = 0; i < pn_table.m_dataset_UN.size(); i++)
	 //{
		// m_combox_unit.AddString(pn_table.m_dataset_UN.at(i).UNUseUnits);
	 //}
    return FALSE; 
    
     // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CNewPNDlg::Check_PN ()
{
    /*if (m_strPN.CompareNoCase (m_item.PNPartNumber)==0)
    {
        return TRUE;
    }*/
   /* for (int i=0; i<table_pn.pv_Table_PN.size (); i++)
    {
        if (table_pn.pv_Table_PN.at(i).PNPartNumber.CompareNoCase(m_item.PNPartNumber)==0)
        {
            continue;
        }
        if (table_pn.pv_Table_PN.at(i).PNPartNumber.CompareNoCase(m_strPN)==0)
        {
            return FALSE;
        }
    }*/

    return TRUE;
}

void CNewPNDlg::LoadData()
{
    if (m_new_item==1||m_new_item == 2)
    {
        m_strType=m_item.PNType;
        m_strUnits= pn_table.GetUnitName_ByID(m_item.PNUNID);
        m_strBy=m_item.ReqBy;
        m_strCurCost.Format(_T("%0.3f"),m_item.PNCurrentCost);
        m_strDetail = m_item.PNDetail;
        m_strFootPrint = m_item.PNPrintFooter;
        m_strLastCost.Format(_T("%0.2f"), m_item.PNLastRollupCost);
        m_strMiniStock.Format(_T("%0.2f"), m_item.PNMinStockQty);
        m_strNote.Format(_T("%s"), m_item.PNNote);
        m_strPN.Format(_T("%s"), m_item.PNPartNumber);
        m_strRevision.Format(_T("%s"), m_item.PNRevision);
        m_strStock.Format(_T("%0.2f"), m_item.Stock);
        m_strTitle.Format(_T("%s"), m_item.PNTitle);
       
      
       
        if (m_item.PNImageName.IsEmpty ())
        {
            m_imagefile = pn_table.GetImageFileFold ()+L"default.jpg";
        }
        else
        {
            m_imagefile = pn_table.GetImageFileFold ()+m_item.PNImageName;
        }


        m_pictureCtrl.Load (m_imagefile);
        
       
        

    }
    if (m_new_item == 1)
    {
        m_strPN = L"";
        GetDlgItem (IDC_EDIT_PN)->SetFocus ();
    }
	//pn_table.Initial_Type();
	//pn_table.Initial_UN();
	//pn_table.Initial_Data ();
   
      

    if (m_isShowAll)
    {
        
            GetDlgItem ( IDC_STATIC_PN                 )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_PN                   )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_TITLE              )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_TITLE                )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_DETAIL             )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_DETAIL               )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_TYPE               )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_COMBO_TYPE                )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_REVISION           )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_REVISION             )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_UNITS              )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_COMBO_UNITS               )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_BY                 )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_BY                   )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_CURCOST            )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_CUR_COST             )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_FP                 )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_FOOT_PRINT           )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_MINISTOCK          )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_MINI_STOCK           )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_LCAC               )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_LAST_COST            )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_STOCK              )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_STOCK                )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_EDIT_NOTE                 )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_STATIC_IMAGE              )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_IMAGE_PATH                )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDC_SELECT_PATH               )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDOK                          )->ShowWindow (SW_SHOW);
            GetDlgItem ( IDCANCEL                      )->ShowWindow (SW_SHOW);

            CRect ViewRect;
            GetClientRect(&ViewRect);

            if (m_pictureCtrl.GetSafeHwnd())
            {
                m_pictureCtrl.MoveWindow(CRect(365,0,ViewRect.Width(),ViewRect.Height()),TRUE);
            }

            //m_pictureCtrl.m_bIsPicLoaded = TRUE;
            if (!m_imagefile.IsEmpty ())
            {
                m_pictureCtrl.Load (m_imagefile);
            }

    } 
    else
    {
        GetDlgItem ( IDC_STATIC_PN                 )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_PN                   )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_TITLE              )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_TITLE                )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_DETAIL             )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_DETAIL               )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_TYPE               )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_COMBO_TYPE                )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_REVISION           )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_REVISION             )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_UNITS              )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_COMBO_UNITS               )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_BY                 )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_BY                   )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_CURCOST            )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_CUR_COST             )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_FP                 )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_FOOT_PRINT           )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_MINISTOCK          )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_MINI_STOCK           )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_LCAC               )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_LAST_COST            )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_STOCK              )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_STOCK                )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_EDIT_NOTE                 )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_STATIC_IMAGE              )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_IMAGE_PATH                )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDC_SELECT_PATH               )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDOK                          )->ShowWindow (SW_HIDE);
        GetDlgItem ( IDCANCEL                      )->ShowWindow (SW_HIDE);


        CRect ViewRect;
        GetClientRect(&ViewRect);

        if (m_pictureCtrl.GetSafeHwnd())
        {
            m_pictureCtrl.MoveWindow(CRect(0,0,ViewRect.Width(),ViewRect.Height()),TRUE);
        }

        //m_pictureCtrl.m_bIsPicLoaded = TRUE;
        if (!m_imagefile.IsEmpty ())
        {
            m_pictureCtrl.Load (m_imagefile);
        }
    }

    UpdateData(FALSE);


   
     
}


LRESULT CNewPNDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if (message == WM_MESSAGE_FRESH_PN_DETAIL)
    {
        m_image_path = L"";
       LoadData ();
    }
    return CDialogEx::WindowProc(message, wParam, lParam);
}


void CNewPNDlg::OnBnClickedSelectPath()
{
    CString strFilter = _T("jpg file;bmp file;png file|*.jpg;*.bmp;*.png|all File|*.*||");
    CFileDialog dlg(true,_T("bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,strFilter);
    if(IDOK==dlg.DoModal())
    {
        CString  FilePath=dlg.GetPathName();
        GetDlgItem (IDC_IMAGE_PATH)->SetWindowTextW(FilePath);
        CString strSuffix = FilePath.Right (3);
        if (strSuffix.CompareNoCase (L"jpg")!=0 &&
                strSuffix.CompareNoCase (L"bmp")!=0 &&
                strSuffix.CompareNoCase (L"png")!=0
           )
        {
            AfxMessageBox (L"Please Select the image (jpg,bmp,png)");
            return ;
        }
        m_pictureCtrl.LoadFromFile (FilePath);
    }
}


void CNewPNDlg::OnPaint()
{
    CPaintDC dc(this);
     
}


void CNewPNDlg::OnSize(UINT nType, int cx, int cy)
{
    if (nType == SIZE_RESTORED)
    {
        CRect ViewRect;
        GetClientRect(&ViewRect);
       if (m_isShowAll)
       {
           if (m_pictureCtrl.GetSafeHwnd())
           {
               m_pictureCtrl.MoveWindow(CRect(365,0,ViewRect.Width(),ViewRect.Height()),TRUE);
           }
       }
       else
       {
           if (m_pictureCtrl.GetSafeHwnd())
           {
               m_pictureCtrl.MoveWindow(CRect(0,0,ViewRect.Width(),ViewRect.Height()),TRUE);
           }
       }
        

        //m_pictureCtrl.m_bIsPicLoaded = TRUE;
      if (!m_imagefile.IsEmpty ())
      {
         m_pictureCtrl.Load (m_imagefile);
      }
       
    }
    
    
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
}


void CNewPNDlg::OnPvOnlypicture()
{
     m_isShowAll = FALSE;
     PostMessage (WM_MESSAGE_FRESH_PN_DETAIL,0,0);
}


void CNewPNDlg::OnPvShowall()
{
     m_isShowAll = TRUE;
      PostMessage (WM_MESSAGE_FRESH_PN_DETAIL,0,0);
}


void CNewPNDlg::OnStnDblclickPictureShow()
{
   
}


void CNewPNDlg::OnBnClickedButtonVendorprice()
{
	if (m_item.PNID>0)
	{
		CPartVendorQuotationDlg dlg;
		dlg.m_PN_ID = m_item.PNID;
		CString Title;
		Title.Format(_T("Part's Quatation List:%s"), m_item.PNPartNumber);

		dlg.Title = Title;
		dlg.DoModal();
	}
	 
	
}
