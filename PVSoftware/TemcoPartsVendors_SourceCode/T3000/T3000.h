
// T3000.h : main header file for the T3000 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "define.h"
#include <vector>
#include "global_variable_extern.h"

#include "PVMainScreenDlg.h"
#include "MainFrm.h"
extern int g_MainScreenLevel;
extern int g_ParamLevel;
extern int g_OutPutLevel;
extern int g_NetWorkLevel;
extern int g_GraphicModelevel;
extern int g_BurnHexLevel;
extern int g_LoadConfigLevel;
extern int g_BuildingsetLevel;
extern int g_AllscreensetLevel;
extern Table_PN pn_table;
extern BOOL PO_NEEDFRESH;

// CT3000App:
// See T3000.cpp for the implementation of this class
//

struct ALL_NODE {
	CString MainBuilding_Name;
	CString Building_Name;
	CString Serial_ID;
	CString Floor_name;
	CString Room_name;
	CString Product_name;
	CString Product_class_ID;
	CString Product_ID;
	CString Screen_Name;
	CString Bautrate;
	CString Background_imgID;
	CString Hardware_Ver;
	CString Software_Ver;
	CString Com_Port;
	CString EPsize;
	CString Protocol;
    CString Custom;
};

struct Building{
_variant_t Main_BuildingName;
_variant_t Building_Name;
_variant_t Protocal;
_variant_t Com_Port;
_variant_t Ip_Address;
_variant_t Ip_Port;
_variant_t Braudrate;
_variant_t Default_SubBuilding;
_variant_t Building_Path;
};
struct Building_ALL{
_variant_t Building_Name;
_variant_t Default_Building;
_variant_t Telephone;
_variant_t Address;
};

struct CustomProductTable{
_variant_t ModelNo;
_variant_t Reg_Description;
_variant_t Reg_ID;

};



struct IONAME{
_variant_t SERIAL_ID;
_variant_t INPUT1;
_variant_t INPUT2;
_variant_t INPUT3;
_variant_t INPUT4;
_variant_t INPUT5;
_variant_t INPUT6;
_variant_t INPUT7;
_variant_t INPUT8;
_variant_t INPUT9;
_variant_t OUTPUT1;
_variant_t OUTPUT2;
_variant_t OUTPUT3;
_variant_t OUTPUT4;
_variant_t OUTPUT5;
_variant_t OUTPUT6;
_variant_t OUTPUT7;
_variant_t SENSORNAME;
};
struct IONAME_Config{
_variant_t InOutName;
_variant_t Type;
_variant_t Row;
_variant_t SerialNo;
};
struct LCNameConfigure{
_variant_t SN;
_variant_t Card;
_variant_t Output;
_variant_t OutputName;
};
 
struct Product_Data{
_variant_t Serial_ID;
_variant_t Register_Data;
};
struct Screen_Label{
_variant_t Cstatic_id;
_variant_t Serial_Num;
_variant_t Point_X ;
_variant_t Point_Y;
_variant_t Height;
_variant_t Width;
_variant_t Tstat_id;
_variant_t Status;
_variant_t Tips;
_variant_t Input_or_Output;
_variant_t Text_Color;
_variant_t Back_Color;
};
struct Value_Range{
_variant_t SN;
_variant_t CInputNo;
_variant_t CRange;
};



class COwnMemDC : public CDC {
	private:
		CBitmap m_bitmap; // Offscreen bitmap
		CBitmap* m_oldBitmap; // bitmap originally found in CMemDC
		CDC* m_pDC; // Saves CDC passed in constructor
		CRect m_rect; // Rectangle of drawing area.
		BOOL m_bMemDC; // TRUE if CDC really is a Memory DC.
	public:
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
		COwnMemDC(CDC* pDC, CRect rect = CRect(0,0,0,0), BOOL bCopyFirst = FALSE) : CDC(), m_oldBitmap(NULL), m_pDC(pDC)
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			ASSERT(m_pDC != NULL); // If you asserted here, you passed in a NULL CDC.
			
			m_bMemDC = !pDC->IsPrinting();
			
			if (m_bMemDC){
				// Create a Memory DC
				CreateCompatibleDC(pDC);
				if ( rect == CRect(0,0,0,0) )
					pDC->GetClipBox(&m_rect);
				else
					m_rect = rect;

				m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
				m_oldBitmap = SelectObject(&m_bitmap);
				SetWindowOrg(m_rect.left, m_rect.top);
				if(bCopyFirst)
				{
					this->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
							m_pDC, m_rect.left, m_rect.top, SRCCOPY);
				}
			} else {
				// Make a copy of the relevent parts of the current DC for printing
				m_bPrinting = pDC->m_bPrinting;
				m_hDC = pDC->m_hDC;
				m_hAttribDC = pDC->m_hAttribDC;
			}
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
		~COwnMemDC()
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			if (m_bMemDC) {
				// Copy the offscreen bitmap onto the screen.
				m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
					this, m_rect.left, m_rect.top, SRCCOPY);
				//Swap back the original bitmap.
				SelectObject(m_oldBitmap);
			} else {
				// All we need to do is replace the DC with an illegal value,
				// this keeps us from accidently deleting the handles associated with
				// the CDC that was passed to the constructor.
				m_hDC = m_hAttribDC = NULL;
			}
		}
		
		// Allow usage as a pointer
		COwnMemDC* operator->() {return this;}
		
		// Allow usage as a pointer
		operator COwnMemDC*() {return this;}
};

class CT3000App : public CWinAppEx
{

public:
	CT3000App();

// Overrides
public:
	virtual BOOL InitInstance();
 
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	BOOL RegisterOcx(LPCTSTR   OcxFileName);
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	 
	void OnVersionInfo();
	DECLARE_MESSAGE_MAP()
public:
	BOOL user_login();
	virtual int ExitInstance();
 
 
 
	BOOL haveRegister();
	CString GetModulePath();
	int GetSoftInstallDays();
	void WriteNumber(CRegKey& key,CStringW valueName,DWORD value);
	BOOL ReadNameber(CRegKey& key,CStringW valueName,DWORD& value);
	void Judgestore();
	void ReadREG();
 
	DWORD m_maxClients;
	DWORD password;
	 
	vector<ALL_NODE> m_AllNodes;

	vector<Building> m_Building;
	vector<Building_ALL> m_Building_ALL;
	vector<CustomProductTable>  m_CustomProductTable;
	vector<IONAME> m_IONAME;
	vector<IONAME_Config> m_IONAME_Config;
	vector<LCNameConfigure> m_LCNameConfigure;
	 
	vector<Product_Data> m_Product_Data;
	vector<Screen_Label> m_Screen_Label;

	vector<Value_Range>m_Value_Range;

	int m_lastinterface;


public:
	CString m_szAppPath;
	CString m_szHelpFile;


	// CPVMainScreenDlg *m_pvmainwindowdlg;
};

extern CT3000App theApp;