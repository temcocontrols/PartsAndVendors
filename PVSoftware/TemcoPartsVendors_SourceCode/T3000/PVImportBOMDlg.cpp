// PVImportBOMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "PVImportBOMDlg.h"
#include "afxdialogex.h"
#include "globle_function.h"


// CPVImportBOMDlg dialog

IMPLEMENT_DYNAMIC(CPVImportBOMDlg, CDialogEx)

CPVImportBOMDlg::CPVImportBOMDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CPVImportBOMDlg::IDD, pParent)
{
    m_strFilePath = L"";
    m_pFile = new CStdioFile;



    m_oldColorRow = -1;
    m_curColorRow = -1;
    m_curRow = -1;
    m_curCol = -1;

}

CPVImportBOMDlg::~CPVImportBOMDlg()
{
    delete m_pFile;

}

void CPVImportBOMDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_data_list);
    DDX_Control(pDX, IDC_EDIT_PN, m_combox_PN);
}


BEGIN_MESSAGE_MAP(CPVImportBOMDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BOM_PATH, &CPVImportBOMDlg::OnBnClickedBomPath)
    ON_BN_CLICKED(IDC_NEW_PN, &CPVImportBOMDlg::OnBnClickedNewPn)
    ON_BN_CLICKED(IDC_BUTTON_Reload, &CPVImportBOMDlg::OnBnClickedButtonReload)
    ON_BN_CLICKED(IDOK, &CPVImportBOMDlg::OnBnClickedOk)
    ON_CBN_SELCHANGE(IDC_EDIT_PN, &CPVImportBOMDlg::OnCbnSelchangeEditPn)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPVImportBOMDlg::OnNMClickList1)
END_MESSAGE_MAP()


// CPVImportBOMDlg message handlers


void CPVImportBOMDlg::OnBnClickedBomPath()
{  

    CString strPN;
    m_combox_PN.GetWindowTextW(strPN);
	if (strPN.Trim().IsEmpty())
	{
	    AfxMessageBox(L"Please select a assembly part.");
		m_combox_PN.SetFocus();
		return;
	}
    CString strFilter = _T("Delimited Text File|*.csv;*.txt;*.bom|all File|*.*||");
    CFileDialog dlg(true,_T("BOM"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,strFilter);
    dlg.DoModal();
    m_strFilePath=dlg.GetPathName();
    GetDlgItem (IDC_EDIT_PATH)->SetWindowText (m_strFilePath);
    Initial_List();
}


BOOL CPVImportBOMDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_data_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
    m_data_list.SetExtendedStyle(m_data_list.GetExtendedStyle()  |LVS_EX_GRIDLINES&(~LVS_EX_FULLROWSELECT));




    g_hwnd_now = this->m_hWnd;


    pn_table.Load_Assembly_Data();


    for (int i = 0 ; i<(int) pn_table.pv_Table_PN.size (); i++)
    {
        m_combox_PN.AddString(pn_table.pv_Table_PN.at(i).PNPartNumber);
    }


    return TRUE;
}

void CPVImportBOMDlg::Initial_List ()
{
    int colcount  = 0;
    char chToken= '\\';
    if (m_strFilePath.IsEmpty ())
    {
        return;
    }
	m_fileContent.clear();
    if(m_pFile->Open(m_strFilePath.GetString(),CFile::modeRead|CFile::shareDenyNone))
    {
		CString strRead;
        m_BOMContent.clear();

        while(m_pFile->ReadString(strRead))
        {
			strRead = ReadStringCharToUnicode(strRead);
            if (!strRead.IsEmpty ())
            {
                CString StrLog;
                StrLog.Format (_T("%s   \n"),strRead);
                //TRACE(strRead+L"\n");

                m_BOMContent.push_back(strRead);
                CStringArray ArrayString;
                SplitCStringA (ArrayString,strRead,L"\t",FALSE);

                if (colcount<ArrayString.GetSize ())  //插入列
                {
                    /*   int insertCol = ArrayString.GetSize ()- colcount;
                    for(int col = 0; col<insertCol; col++)
                    {
                    m_data_list.InsertColumn(colcount+col, _T(""), 80, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
                    }*/
                    colcount = ArrayString.GetSize ();
                }
                int testsize = ArrayString.GetSize ();
                if (testsize<=0)
                {
                    continue;
                }
                vector<CString> TempArrayString;
                if (testsize>0)
                {
                    if (ArrayString[0].IsEmpty ())
                    {
                        // continue;
                        int lastrow = m_fileContent.size ()-1;
                        for (int col = 0; col<ArrayString.GetSize (); col++)
                        {
                            if (col == 4)
                            {
                                int index = ArrayString[col].ReverseFind (chToken);
                                if (index!=-1)
                                {
                                    ArrayString[col].Delete(0,index+1);
                                }
                            }

                            CString strData = m_fileContent.at(lastrow).at(col);
                            strData += ArrayString[col];
                            m_fileContent.at(lastrow)[col]=strData;

                        }
                        continue;
                    }
                }

                /*  int rowcount = m_data_list.GetRowCount ();
                  m_data_list.InsertItem (rowcount,ArrayString[0]);*/
                TempArrayString.clear ();
                for (int col = 0; col<ArrayString.GetSize (); col++)
                {
                    // m_data_list.SetItemText (rowcount-1,col,ArrayString[col]);
                    if (col == 4)
                    {
                        int index = ArrayString[col].ReverseFind (chToken);
                        if (index!=-1)
                        {
                            ArrayString[col].Delete(0,index+1);
                        }
                    }

                    TempArrayString.push_back (ArrayString[col]);
                }

                m_fileContent.push_back (TempArrayString);

            }

        }

        m_pFile->Close();


    }
    else
    {
        ASSERT(0);
        m_pFile->Close();
        return  ;
    }

    //for(int col = 0; col<colcount; col++)//插入列
    //{
    //    m_data_list.InsertColumn(col, _T(""), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    //}

  /*  m_data_list.InsertColumn(0, _T("Item"), 50, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
    m_data_list.InsertColumn(1, _T("Quantity"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(2, _T("Reference	Value"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(3, _T("PCB"), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(4, _T("Footprint"), 250, ListCtrlEx::ComboBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(5, _T("Description"), 250, ListCtrlEx::ComboBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
    m_data_list.InsertColumn(6, _T("Part_Number"), 250, ListCtrlEx::ComboBox, LVCFMT_CENTER, ListCtrlEx::SortByString); */
	//m_data_list.InsertColumn(0, m_fileContent.at(0).at(0), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(1, m_fileContent.at(0).at(1), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(2, m_fileContent.at(0).at(2), 100, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(3, m_fileContent.at(0).at(3), 50, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(4, m_fileContent.at(0).at(4), 250, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(5, m_fileContent.at(0).at(5), 250, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	//m_data_list.InsertColumn(6, m_fileContent.at(0).at(6), 250, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
//	m_data_list.DeleteAllItems();
m_data_list.DeleteAllItems();
while ( m_data_list.DeleteColumn (0)) ;
	
	for (int col =0;col<(int)m_fileContent.at(0).size();col++)
	{
		m_data_list.InsertColumn(col, m_fileContent.at(0).at(col), 100, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	}
    for (int row = 1; row<(int)m_fileContent.size (); row++)
    {
		CString strTemp = m_fileContent.at(row).at(0);
        m_data_list.InsertItem (row-1,strTemp);
        for (int col = 0; col<m_fileContent.at(row).size(); col++)
        {
			strTemp = m_fileContent.at(row).at(col);
            m_data_list.SetItemText (row-1,col,m_fileContent.at(row).at(col));
        }
    }

	for (int row = 1;row<(int)m_fileContent.size();row++)
	{
		BOMListItemStatus checkitem;
		checkitem.ListID = m_parentItem.PNID;

		checkitem.Quantity = m_fileContent.at(row).at(1).Trim();

		checkitem.Part_Reference = m_fileContent.at(row).at(2).Trim();

		checkitem.Value = m_fileContent.at(row).at(3).Trim();
		checkitem.PCB_Footprint = m_fileContent.at(row).at(4).Trim();
		checkitem.Description =  m_fileContent.at(row).at(5).Trim();
		checkitem.Brand_Vendor =  m_fileContent.at(row).at(6).Trim();
		checkitem.PN = m_fileContent.at(row).at(7).Trim();
		checkitem= pn_table.CheckBomListItemStatus(checkitem);
		if (checkitem.PNFlag)
		{
			m_data_list.SetItemBkColor(row-1,0,RGB(255,0,0));
			m_data_list.SetItemBkColor(row-1,3,RGB(255,0,0));
			m_data_list.SetItemBkColor(row-1,4,RGB(255,0,0));
			m_data_list.SetItemBkColor(row-1,5,RGB(255,0,0));
			m_data_list.SetItemBkColor(row-1,6,RGB(255,0,0));

		}
		else
		{
		 
		  if (checkitem.BOMFlag)
			{
				m_data_list.SetItemBkColor(row-1,0,RGB(255,255,0));
				m_data_list.SetItemBkColor(row-1,1,RGB(255,255,0));
				m_data_list.SetItemBkColor(row-1,2,RGB(255,255,0));
			}
			else
			{
			     BOOL IS_AllTheSame = TRUE;
				if ( !checkitem.ItemStaus.Quantity&&!checkitem.BOMFlag)
				{
					m_data_list.SetItemBkColor(row-1,1,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}
				 
				if (!checkitem.ItemStaus.Part_Reference&&!checkitem.BOMFlag)
				{
					m_data_list.SetItemBkColor(row-1,2,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}
				 
				if (!checkitem.ItemStaus.Value&&!checkitem.PNFlag)
				{
					m_data_list.SetItemBkColor(row-1,3,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}
				 
				if (!checkitem.ItemStaus.PCB_Footprint&&!checkitem.PNFlag)
				{
					m_data_list.SetItemBkColor(row-1,4,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}
				 
				if (!checkitem.ItemStaus.Description&&!checkitem.PNFlag)
				{
					m_data_list.SetItemBkColor(row-1,5,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}
				 
				if (!checkitem.ItemStaus.Brand_Vendor&&!checkitem.PNFlag)
				{
					m_data_list.SetItemBkColor(row-1,6,RGB(255,0,0));
					IS_AllTheSame = FALSE;
				}  
				 

				if (IS_AllTheSame)
				{
					m_data_list.SetItemBkColor(row-1,0,RGB(0,255,0));
				}
				

			}
		 
			
		} 
	}
}

#include "NewPNDlg.h"
void CPVImportBOMDlg::OnBnClickedNewPn()
{
    CNewPNDlg dlg;
    dlg.m_new_item = 0;
    dlg.m_saveCloseWindow = TRUE;
    dlg.DoModal();
}


void CPVImportBOMDlg::OnBnClickedButtonReload()
{
    pn_table.Load_Assembly_Data();
    m_combox_PN.ResetContent ();

    for (int i = 0 ; i<(int) pn_table.pv_Table_PN.size (); i++)
    {
        m_combox_PN.AddString(pn_table.pv_Table_PN.at(i).PNPartNumber);
    }
}


void CPVImportBOMDlg::OnBnClickedOk()
{
    if (-1==m_parentItem.PNID)
    {
        AfxMessageBox (_T("Please select a assembly item!"));
        return;
    }
    if (1>m_fileContent.size ())
    {
        AfxMessageBox (_T("Didn't find parts list!"));
        return;
    }
    //Part List insert Database
    for (int row = 1; row<(int)m_fileContent.size (); row++)
    {
        PN_Struct InsertItem;
        InsertItem.PNPrintFooter = m_fileContent.at(row).at(4);
        InsertItem.PNDetail = m_fileContent.at(row).at(5);
        InsertItem.PNTitle =  m_fileContent.at(row).at(3);
		InsertItem.Brand_Vendor = m_fileContent.at(row).at(6);
        InsertItem.PNPartNumber = m_fileContent.at(row).at(7);
        InsertItem=pn_table.Insert_ByPN (InsertItem);
        m_InsertItems.push_back (InsertItem);
    }
    //Link the part list to assembly item
    for (int index=0; index<m_InsertItems.size(); index++)
    {
        BOM_PartList addItem;
        addItem.PLPartID =m_InsertItems.at(index).PNID;
        addItem.PLListID =m_parentItem.PNID;
        addItem.PLItem = _wtoi(m_fileContent.at(index+1).at(0));
        addItem.PLQty  = m_fileContent.at(index+1).at(1);
        addItem.PLRefMemo = m_fileContent.at(index+1).at(2);
        pn_table.Insert_PL (addItem);
    }
    AfxMessageBox (_T("Import Successfully!"));
    // CDialogEx::OnOK();
}


void CPVImportBOMDlg::OnCbnSelchangeEditPn()
{
    m_parentItem = pn_table.pv_Table_PN.at(m_combox_PN.GetCurSel ());
}


void CPVImportBOMDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    CString temp_cstring;
    long lRow,lCol;
    m_data_list.Set_Edit(true);
    DWORD dwPos=GetMessagePos();
    //Get which line is click by user.Set the check box, when user enter Insert it will jump to program dialog
    CPoint point( LOWORD(dwPos), HIWORD(dwPos));
    m_data_list.ScreenToClient(&point);
    LVHITTESTINFO lvinfo;
    lvinfo.pt=point;
    lvinfo.flags=LVHT_ABOVE;
    int nItem=m_data_list.SubItemHitTest(&lvinfo);

    lRow = lvinfo.iItem;
    lCol = lvinfo.iSubItem;

    m_curRow=lRow;

    m_curCol=lCol;
    if(lRow>m_data_list.GetItemCount()) //如果点击区超过最大行号，则点击是无效的
        return;
    if(lRow<0)
        return;
    CString New_CString;
    CString temp_task_info;

    CString temp1;
    CStringArray temparray;

    if (lCol == 0)
    {

        m_oldColorRow = m_curColorRow;
        m_curColorRow = m_curRow;


        if (m_curColorRow != -1)
        {
            m_data_list.SetItemBkColor (m_curColorRow,-1,LIST_ITEM_SELECTED);
        }

        if (m_oldColorRow != -1)
        {
            m_data_list.SetItemBkColor (m_oldColorRow,-1,RGB(255,255,255));
        }

    }


    *pResult = 0;
}
