// PVDetailedVendorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVDetailedVendorDlg.h"
#include "afxdialogex.h"


// CPVDetailedVendorDlg dialog

IMPLEMENT_DYNAMIC(CPVDetailedVendorDlg, CDialogEx)

CPVDetailedVendorDlg::CPVDetailedVendorDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVDetailedVendorDlg::IDD, pParent)
{

    m_code = _T("");
	strm_currentcy = _T("CNY");
    m_account = _T("");
    m_str_address = _T("");
    m_name1 = _T("");
    m_phone1 = _T("");
    m_email1 = _T("");
    m_email2 = _T("");
    m_fedid = _T("");
    m_lastcontactdate = _T("");
    m_name2 = _T("");
    m_notes = _T("");
    m_phone2 = _T("");
    m_terms = _T("");
    m_vendor_name = _T("");
    m_website = _T("");
    m_localid = _T("");
}

CPVDetailedVendorDlg::~CPVDetailedVendorDlg()
{

}

void CPVDetailedVendorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CODE, m_code);
    DDV_MaxChars(pDX, m_code, 255);
    DDX_CBString(pDX, IDC_COMBO_CURRENTCY, strm_currentcy);
    DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_account);
    DDV_MaxChars(pDX, m_account,255);
    DDX_Text(pDX, IDC_EDIT_ADDRESS, m_str_address);
    DDV_MaxChars(pDX, m_str_address, 255);
    DDX_Text(pDX, IDC_EDIT_CNAME1, m_name1);
    DDV_MaxChars(pDX, m_name1, 255);
    DDX_Text(pDX, IDC_EDIT_CPHONE1, m_phone1);
    DDV_MaxChars(pDX, m_phone1, 255);
    DDX_Text(pDX, IDC_EDIT_EAMIL1, m_email1);
    DDV_MaxChars(pDX, m_email1, 255);
    DDX_Text(pDX, IDC_EDIT_EMAIL2, m_email2);
    DDV_MaxChars(pDX, m_email2, 255);
    DDX_Text(pDX, IDC_EDIT_FEDID, m_fedid);
    DDV_MaxChars(pDX, m_fedid, 255);
    DDX_Text(pDX, IDC_EDIT_LAST_CONTACT_DATE, m_lastcontactdate);
    DDX_Text(pDX, IDC_EDIT_NAME2, m_name2);
    DDV_MaxChars(pDX, m_name2, 255);
    DDX_Text(pDX, IDC_EDIT_NOTES, m_notes);
    DDX_Text(pDX, IDC_EDIT_PHONE2, m_phone2);
    DDV_MaxChars(pDX, m_phone2, 255);
    DDX_Text(pDX, IDC_EDIT_TERMS, m_terms);
    DDV_MaxChars(pDX, m_terms, 255);
    DDX_Text(pDX, IDC_EDIT_VENDOR_NAME, m_vendor_name);
    DDV_MaxChars(pDX, m_vendor_name, 255);
    DDX_Text(pDX, IDC_EDIT_WEBSITE, m_website);
    DDV_MaxChars(pDX, m_website, 255);
    DDX_Text(pDX, IDC_LOCALID, m_localid);
    DDV_MaxChars(pDX, m_localid, 255);
    DDX_Control(pDX, IDC_EDIT_LAST_CONTACT_DATE, m_DateTimeCtrl);
    DDV_MaxChars(pDX, m_name1, 255);
    DDX_Control(pDX, IDC_COMBO_CURRENTCY, m_combox_currency);
}


BEGIN_MESSAGE_MAP(CPVDetailedVendorDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_TODAY, &CPVDetailedVendorDlg::OnBnClickedButtonToday)
    ON_BN_CLICKED(IDOK, &CPVDetailedVendorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPVDetailedVendorDlg message handlers


BOOL CPVDetailedVendorDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

	
    CString title;
    title=_T("Vendor Information Maintance");

    this->SetWindowTextW(title);

    m_code = m_SuItem.SUCode;
    //  m_currentcy = m_SuItem.SUCurReverse;
    m_account = m_SuItem.SUAccount;
    m_str_address = m_SuItem.SUAddress;
    m_name1 = m_SuItem.SUContact1;
    m_phone1 = m_SuItem.SUPhone1;
    m_email1 = m_SuItem.SUEMail1;
    m_email2 = m_SuItem.SUEMail2;
    m_fedid = m_SuItem.SUFedTaxID;
    m_lastcontactdate = m_SuItem.SUDateLast;
    m_name2 = m_SuItem.SUContact2;
    m_notes = m_SuItem.SUNotes;
    m_phone2 = m_SuItem.SUPhone2;
    m_terms = m_SuItem.SUTerms;
    m_vendor_name = m_SuItem.SUSupplier;
    m_website = m_SuItem.SUWeb;
    m_localid = m_SuItem.SUStateTaxID;
    m_currency.CURID = m_SuItem.SUCURID ;
    pn_table.Load_Currency ();


    for (int i = 0;i<pn_table.m_dataset_Currentcy.size ();i++)
    {
        m_combox_currency.AddString (pn_table.m_dataset_Currentcy.at(i).CURCurrencyName);
    }
	m_combox_currency.SetCurSel(0);
    for (int i = 0;i<pn_table.m_dataset_Currentcy.size ();i++)
    {
        if (pn_table.m_dataset_Currentcy.at(i).CURID == m_currency.CURID)
        {
            //m_combox_currency.SetCurSel (i);
              m_currency = pn_table.m_dataset_Currentcy.at(i);
              break;
        }
    }
	strm_currentcy =  m_currency.CURCurrencyName;
   // m_combox_currency.SetWindowTextW(m_currency.CURCurrencyName);
	   if (strm_currentcy.IsEmpty())
	   {
		   strm_currentcy= _T("CNY");
	   }
	   
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CPVDetailedVendorDlg::OnBnClickedButtonToday()
{
    CTime time = CTime::GetCurrentTime();
    m_lastcontactdate.Format(_T("%d/%d/%d"), time.GetYear(), time.GetMonth(), time.GetDay());


    GetDlgItem(IDC_EDIT_LAST_CONTACT_DATE)->SetWindowTextW(m_lastcontactdate);
}


void CPVDetailedVendorDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    //CDialogEx::OnOK();
    UpdateData(TRUE);
    m_SuItem.SUCode = m_code;
    m_SuItem.SUAccount = m_code;
    m_SuItem.SUAddress = m_str_address;
    m_SuItem.SUContact1 = m_name1;
    m_phone1.Delete (20,m_phone1.GetLength ());
    m_SuItem.SUPhone1 = m_phone1;
    m_SuItem.SUEMail1 = m_email1;
    m_SuItem.SUEMail2 = m_email2;
    m_SuItem.SUFedTaxID = m_fedid;
    m_SuItem.SUDateLast = m_lastcontactdate;
    m_SuItem.SUContact2 = m_name2;
    m_SuItem.SUNotes = m_notes;

    m_phone2.Delete (20,m_phone2.GetLength ());
    m_SuItem.SUPhone2 = m_phone2;
    m_SuItem.SUTerms = m_terms;
    m_SuItem.SUSupplier = m_vendor_name;
    m_SuItem.SUWeb = m_website;
    m_SuItem.SUStateTaxID = m_localid;

    m_SuItem.SUCURID = pn_table.m_dataset_Currentcy.at(m_combox_currency.GetCurSel ()).CURID;
  //  m_SuItem.SUCURID = 1;
    if(m_isCreate)
    {
        pn_table.Insert_Vendor(m_SuItem);
    }
    else
    {
        pn_table.Update_Vendor(m_SuItem);
    }
    CDialog::OnOK();
}
