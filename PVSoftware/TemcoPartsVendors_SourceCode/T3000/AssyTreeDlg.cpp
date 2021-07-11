// AssyTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "AssyTreeDlg.h"
#include "afxdialogex.h"
#include "..\TreeGrid\GridBtnCell_src\GridBtnCell.h"
#include "..\TreeGrid\GridBtnCell_src\GridBtnCellCombo.h"

// CAssyTreeDlg dialog
static const char m_szInsDelBranch[] =  "Make sure the current cell is\n"
    "in the tree column and try again";

#define FIXED_ROW_COUNT         1
#define FIXED_COLUMN_COUNT      1
#define TREE_COLUMN             1
#define CTL_COLUMN_BEGIN        (TREE_COLUMN + 1)
IMPLEMENT_DYNAMIC(CAssyTreeDlg, CDialogEx)

CAssyTreeDlg::CAssyTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAssyTreeDlg::IDD, pParent)
{
   m_TreeImage = TREE_IMAGE_AUTO;
}

CAssyTreeDlg::~CAssyTreeDlg()
{
    
}

void CAssyTreeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CAssyTreeDlg, CDialogEx)
END_MESSAGE_MAP()


// CAssyTreeDlg message handlers


BOOL CAssyTreeDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    this->SetWindowTextW(m_title);
    pn_table.Build_TreeData (m_PNID,PNName);
    

    m_Grid.SetEditable(FALSE);
    m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xFF));

    m_ImageList.Create( MAKEINTRESOURCE(IDB_FOLDERS),
        16,     // pixel size
        1,
        RGB(255,255,255));
    m_Grid.SetImageList(&m_ImageList);

    TRY 
    {
        m_Grid.SetColumnCount (11);//设置总列数
        m_Grid.SetFixedRowCount(1); //设置固定列
       // m_Grid.SetRowCount(5);
    }
    CATCH (CMemoryException, e)
    {
    	e->ReportError ();
        e->Delete ();
        return FALSE;
    }
    END_CATCH
    DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
    GV_ITEM Item;
    int row = 0;
    int col = 0;
     
    Item.mask = GVIF_TEXT|GVIF_FORMAT;
    Item.row = row;
    Item.col = 0;
    Item.nState = 0;
    Item.nFormat = DT_LEFT|DT_WORDBREAK;
    Item.strText = _T("Tree Item");
    m_Grid.SetItem(&Item);  

    Item.col = 1;
    Item.strText = _T("P/N");
    m_Grid.SetItem(&Item);  

    Item.col = 2;
    Item.strText = _T("Qty");
    m_Grid.SetItem(&Item);  

    Item.col = 3;
    Item.strText = _T("Type");
    m_Grid.SetItem(&Item); 

    Item.col = 4;
    Item.strText = _T("Cur.Cost");
    m_Grid.SetItem(&Item); 

    Item.col = 5;
    Item.strText = _T("Assy Cost");
    m_Grid.SetItem(&Item);

    Item.col = 6;
    Item.strText = _T("Title");
    m_Grid.SetItem(&Item);

    Item.col = 7;
    Item.strText = _T("Detail");
    m_Grid.SetItem(&Item);

    Item.col = 8;
    Item.strText = _T("Vendor");
    m_Grid.SetItem(&Item);

    Item.col = 9;
    Item.strText = _T("Vendor P/N");
    m_Grid.SetItem(&Item);

    Item.col = 10;
    Item.strText = _T("Ref(m)");
    m_Grid.SetItem(&Item);

    for (int i=1;i<10;i++)
    {
        CString index;
        index.Format (_T("%d"),i);
        m_Grid.InsertRow (index,-1);
    }
     
    return TRUE;  

}
