#pragma once
#include "..\treegrid\gridctrl_src\gridctrl.h"
#include "..\treegrid\TreeColumn_src\TreeColumn.h"
#include "..\treegrid\GridBtnCell_src\BtnDataBase.h"
#include"..\TreeGrid\GridTreeBtnCell_src\GridTreeBtnCell.h"

#include "bado/BADO.h"
#include "pvdatabasestruct.h"
#include "PVDatabase.h"
 
#define chDIMOF(Array) (sizeof(Array) / sizeof(Array[0]))
class CAssyTreeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAssyTreeDlg)

public:
	CAssyTreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAssyTreeDlg();

// Dialog Data
	enum { IDD = IDD_PV_ASSY_TREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CImageList m_ImageList;

    CGridCtrl m_Grid;

    CTreeColumn m_TreeColumn;   // grid with tree column
    CBtnDataBase m_BtnDataBase; // grid with some cells with buttons / controls
    TREE_IMAGE m_TreeImage;
    CString m_title;
    int m_PNID;
    CString PNName;
   // Table_PN pn_table;
    vector<unsigned char> m_vec_treechar;
public:
   
    virtual BOOL OnInitDialog();
};
