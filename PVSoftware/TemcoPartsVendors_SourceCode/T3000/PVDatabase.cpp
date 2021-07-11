#include "StdAfx.h"
#include "PVDatabase.h"
#include "global_variable_extern.h"
#include "globle_function.h"
#include <stack>

using namespace std;
////  Table_PN
Table_PN::Table_PN()
{
	m_msgwnd = NULL;
	TCHAR exeFullPath[MAX_PATH+1]; //
	GetModuleFileName(NULL, exeFullPath, MAX_PATH); //
	(_tcsrchr(exeFullPath, _T('\\')))[1] = 0;//
	g_strDatabasefilepath=exeFullPath;//
	g_strExePth=g_strDatabasefilepath;//

    CString g_configfile_path = g_strExePth + _T("T3000_config.ini");
    CString strTemp = g_strExePth + _T("Database\\PV\\PV.mdb");
    CString path;
    GetPrivateProfileString(_T("PartsVendors"), _T("PVDB"), strTemp, path.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
    path.ReleaseBuffer();
    m_pv_database_path = path;                              //L"Z:\\Designs\\Lib\\DB\\Temco.mdb"; //path;    L"Z:\\Designs\\Lib\\DB\\Temco.mdb"       //
    m_database_operator.SetDBPath(m_pv_database_path);

    strTemp = g_strExePth + _T("Database\\PV\\image\\");

    GetPrivateProfileString(_T("PartsVendors"), _T("PVPicturePath"), strTemp, path.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
    path.ReleaseBuffer();
    m_pv_database_image = path;

	/*m_databaseIP = L"192.168.0.107\\MSSQL";
	m_databaseName = L"Temco_PV";
	m_databaseUserName = L"sa";
	m_databasePwd = L"Travel123";*/
	strTemp=L"192.168.0.107\\MSSQL";
	GetPrivateProfileString(_T("PVDBSETTING"), _T("SERVERIP"), strTemp, m_databaseIP.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	m_databaseIP.ReleaseBuffer();

	// m_databaseIP = L"127.0.0.1";
	strTemp=L"TemcoPartsVendors_Default_v1";
	//m_databaseName = L"TemcoPartsVendors_Default_v1";
	GetPrivateProfileString(_T("PVDBSETTING"), _T("DBNAME"), strTemp, m_databaseName.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	m_databaseName.ReleaseBuffer();

	//m_databaseUserName = L"sa";
	strTemp=L"sa";
	GetPrivateProfileString(_T("PVDBSETTING"), _T("USERNAME"), strTemp, m_databaseUserName.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	m_databaseUserName.ReleaseBuffer();

	//m_databasePwd = L"Travel123"; 
	strTemp=L"Travel123";
	GetPrivateProfileString(_T("PVDBSETTING"), _T("PASSWORD"), strTemp, m_databasePwd.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	m_databasePwd.ReleaseBuffer();
}
Table_PN::~Table_PN()
{

}
void Table_PN::Initial_Data()
{
    PN_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql = _T("Select * from qryPN");
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    pv_Table_PN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPartNumber = temp_var;
        }
        else
        {
            temp_struct.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNType = temp_var;
        }
        else
        {
            temp_struct.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNTitle = temp_var;
        }
        else
        {
            temp_struct.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNDetail = temp_var;
        }
        else
        {
            temp_struct.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNRevision = temp_var;
        }
        else
        {
            temp_struct.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStatus = temp_var;
        }
        else
        {
            temp_struct.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.ReqBy = temp_var;
        }
        else
        {
            temp_struct.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNCurrentCost = temp_var;
        }
        else
        {
            temp_struct.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPrintFooter = temp_var;
        }
        else
        {
            temp_struct.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNMinStockQty = temp_var;
        }
        else
        {
            temp_struct.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNLastRollupCost = temp_var;
        }
        else
        {
            temp_struct.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNNote = temp_var;
        }
        else
        {
            temp_struct.PNNote = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Catalog = temp_var;
		}
		else
		{
			temp_struct.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Power = temp_var;
		}
		else
		{
			temp_struct.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Voltage = temp_var;
		}
		else
		{
			temp_struct.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Tolerance = temp_var;
		}
		else
		{
			temp_struct.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Part_type = temp_var;
		}
		else
		{
			temp_struct.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Schematic_part = temp_var;
		}
		else
		{
			temp_struct.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Solidworks = temp_var;
		}
		else
		{
			temp_struct.Solidworks = _T("");
		}


        pv_Table_PN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
BOOL Table_PN::Check_PN(CString StrPN)
{
	return TRUE;
}
void Table_PN::Load_Assembly_Data(CString KeyWord)
{
    PN_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
   
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
  /*  strSql = _T("Select * From qryPN   \
                Where PNType = 'PL' or PNtype = 'CAT' \
                Order by PNID DESC ");*/
	strSql = _T("select  PNID,PNUNID,PNPartNumber,PNType,PNTitle,PNDetail,PNRevision,PNStatus,\
	             PNReqBy,PNCurrentCost,PNUser3,PNMinStockQty,PNLastRollupCost,PNQty,PNNotes,PNPictureName,\
				 	Brand_Vendor,Catalog,Power,Voltage,Tolerance,Part_type,Schematic_part,\
					Allegro_footprint,Solidworks from (Select PNID,PNUNID,PNPartNumber,PNType,\
					PNTitle,PNDetail,PNRevision,PNStatus,PNReqBy,PNCurrentCost,PNUser3,PNMinStockQty,\
					PNLastRollupCost,PNQty,PNNotes,PNPictureName,	\
					Brand_Vendor,Catalog,Power,Voltage,Tolerance,Part_type,\
					Schematic_part,Allegro_footprint,Solidworks,\
					CONCAT(PNPartNumber,',',PNType,',',PNTitle+',',PNDetail,',',PNNotes,','\
					,PNUser3,',',Brand_Vendor,',',Catalog+',',Power,',',Voltage,',', Tolerance,',', Part_type) \
					AS SearchData from PN ) \
					AS BB \
	          Where (PNType = 'PL' or PNtype = 'CAT') and  SearchData LIKE '%") +
		      KeyWord +
		       _T("%'  Order by PNID DESC");


    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    pv_Table_PN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPartNumber = temp_var;
        }
        else
        {
            temp_struct.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNType = temp_var;
        }
        else
        {
            temp_struct.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNTitle = temp_var;
        }
        else
        {
            temp_struct.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNDetail = temp_var;
        }
        else
        {
            temp_struct.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNRevision = temp_var;
        }
        else
        {
            temp_struct.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStatus = temp_var;
        }
        else
        {
            temp_struct.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.ReqBy = temp_var;
        }
        else
        {
            temp_struct.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNCurrentCost = temp_var;
        }
        else
        {
            temp_struct.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPrintFooter = temp_var;
        }
        else
        {
            temp_struct.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNMinStockQty = temp_var;
        }
        else
        {
            temp_struct.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNLastRollupCost = temp_var;
        }
        else
        {
            temp_struct.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNNote = temp_var;
        }
        else
        {
            temp_struct.PNNote = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Catalog = temp_var;
		}
		else
		{
			temp_struct.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Power = temp_var;
		}
		else
		{
			temp_struct.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Voltage = temp_var;
		}
		else
		{
			temp_struct.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Tolerance = temp_var;
		}
		else
		{
			temp_struct.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Part_type = temp_var;
		}
		else
		{
			temp_struct.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Schematic_part = temp_var;
		}
		else
		{
			temp_struct.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Solidworks = temp_var;
		}
		else
		{
			temp_struct.Solidworks = _T("");
		}


        pv_Table_PN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Search_Data_ByPN(CString strValue, CString strValue1 , CString PageNum , CString CurrentPage)
{
    PN_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;

	/*if (isTop100)
	{*/
		


	strSql = _T("Select top "); 
	strSql += PageNum;
	strSql +=_T("	o.* from(Select ROW_NUMBER() over(Order by PNID DESC) as rownumber, * from( ");
	strSql+=_T("Select  * from qryPN Where PNPartNumber LIKE '%") +
			strValue +
			_T("%' AND PNType LIKE '%") +
			strValue1 +
			_T("%' ");
	strSql+= _T(" ) as oo ) as o Where rownumber >");

	strTemp.Format(_T("%d"), _wtoi(PageNum)*(_wtoi(CurrentPage) - 1));
	strSql += strTemp;
		/*}
		else
		{
			strSql = _T("Select * from qryPN Where PNPartNumber LIKE '%") +
				strValue +
				_T("%' AND PNType LIKE '%") +
				strValue1 +
				_T("%'");
		}*/
    


    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    pv_Table_PN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPartNumber = temp_var;
        }
        else
        {
            temp_struct.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNType = temp_var;
        }
        else
        {
            temp_struct.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNTitle = temp_var;
        }
        else
        {
            temp_struct.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNDetail = temp_var;
        }
        else
        {
            temp_struct.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNRevision = temp_var;
        }
        else
        {
            temp_struct.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStatus = temp_var;
        }
        else
        {
            temp_struct.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.ReqBy = temp_var;
        }
        else
        {
            temp_struct.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNCurrentCost = temp_var;
        }
        else
        {
            temp_struct.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPrintFooter = temp_var;
        }
        else
        {
            temp_struct.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNMinStockQty = temp_var;
        }
        else
        {
            temp_struct.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNLastRollupCost = temp_var;
        }
        else
        {
            temp_struct.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNNote = temp_var;
        }
        else
        {
            temp_struct.PNNote = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPictureName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNImageName = temp_var;
        }
        else
        {
            temp_struct.PNImageName = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Catalog = temp_var;
		}
		else
		{
			temp_struct.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Power = temp_var;
		}
		else
		{
			temp_struct.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Voltage = temp_var;
		}
		else
		{
			temp_struct.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Tolerance = temp_var;
		}
		else
		{
			temp_struct.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Part_type = temp_var;
		}
		else
		{
			temp_struct.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Schematic_part = temp_var;
		}
		else
		{
			temp_struct.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Solidworks = temp_var;
		}
		else
		{
			temp_struct.Solidworks = _T("");
		}
		

        pv_Table_PN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
	for (int i=0;i<pv_Table_PN.size();i++)
	{
		if (pv_Table_PN.at(i).PNID != 0)
		{
			pv_Table_PN.at(i).Is_HaveVendor = Check_Vendor(pv_Table_PN.at(i).PNID);
			pv_Table_PN.at(i).Is_Ordered = Check_Ordered(pv_Table_PN.at(i).PNID);
		}
	}
	
}

void Table_PN::Search_ALLPN (CString KeyWord)
{
    PN_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;

	strSql = _T("select  PNID,PNUNID,PNPartNumber,PNType,PNTitle,PNDetail,PNRevision,PNStatus,PNReqBy,PNCurrentCost,PNUser3,PNMinStockQty,PNLastRollupCost,PNQty,PNNotes,PNPictureName,	Brand_Vendor,Catalog,Power,Voltage,Tolerance,Part_type,Schematic_part,Allegro_footprint,Solidworks from (Select PNID,PNUNID,PNPartNumber,PNType,PNTitle,PNDetail,PNRevision,PNStatus,PNReqBy,PNCurrentCost,PNUser3,PNMinStockQty,PNLastRollupCost,PNQty,PNNotes,PNPictureName,	Brand_Vendor,Catalog,Power,Voltage,Tolerance,Part_type,Schematic_part,Allegro_footprint,Solidworks,CONCAT(PNPartNumber,',',PNType,',',PNTitle+',',PNDetail,',',PNNotes,',',PNUser3,',',Brand_Vendor,',',Catalog+',',Power,',',Voltage,',', Tolerance,',', Part_type) AS SearchData from PN ) AS BB Where SearchData LIKE '%") +
         KeyWord +
         _T("%'  Order by PNID DESC");


    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    pv_Table_PN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPartNumber = temp_var;
        }
        else
        {
            temp_struct.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNType = temp_var;
        }
        else
        {
            temp_struct.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNTitle = temp_var;
        }
        else
        {
            temp_struct.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNDetail = temp_var;
        }
        else
        {
            temp_struct.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNRevision = temp_var;
        }
        else
        {
            temp_struct.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStatus = temp_var;
        }
        else
        {
            temp_struct.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.ReqBy = temp_var;
        }
        else
        {
            temp_struct.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNCurrentCost = temp_var;
        }
        else
        {
            temp_struct.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPrintFooter = temp_var;
        }
        else
        {
            temp_struct.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNMinStockQty = temp_var;
        }
        else
        {
            temp_struct.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNLastRollupCost = temp_var;
        }
        else
        {
            temp_struct.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNNote = temp_var;
        }
        else
        {
            temp_struct.PNNote = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPictureName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNImageName = temp_var;
        }
        else
        {
            temp_struct.PNImageName = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Catalog = temp_var;
		}
		else
		{
			temp_struct.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Power = temp_var;
		}
		else
		{
			temp_struct.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Voltage = temp_var;
		}
		else
		{
			temp_struct.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Tolerance = temp_var;
		}
		else
		{
			temp_struct.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Part_type = temp_var;
		}
		else
		{
			temp_struct.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Schematic_part = temp_var;
		}
		else
		{
			temp_struct.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Solidworks = temp_var;
		}
		else
		{
			temp_struct.Solidworks = _T("");
		}

        pv_Table_PN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

 

void Table_PN::Search_All_Parts_Vendors(CString para_PN/* = */)
{
    Part_Vendor_Information temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;


	/*PNType  <> 'PL'   AND  PNType  <> 'CAT'\
		AND LNKUse = -1\
		AND*/

    strSql = _T("Select TOP 50 *\
                     from qryItemsAndAnySources         \
                     Where (PNPartNumber LIKE '%") +
             para_PN +
             _T("%' OR  PNTitle LIKE '%") +
             para_PN +
             _T("%' OR  PNDetail LIKE '%") +
             para_PN +
             _T("%' OR  SUSupplier LIKE '%") +
             para_PN +
             _T("%')   Order By PNID DESC");

    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_PartsVendors.clear();

    //PLID
    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKID = temp_var;
        }
        else
        {
            temp_struct.LNKID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUID = temp_var;
        }
        else
        {
            temp_struct.SUID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKUNID = temp_var;
        }
        else
        {
            temp_struct.LNKUNID = 0;
        }

        /*  CString PartName;
          CString PartTitle;
          CString PartDetail;
          CString Type;*/
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PartName = temp_var;
        }
        else
        {
            temp_struct.PartName = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Type = temp_var;
        }
        else
        {
            temp_struct.Type = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PartTitle = temp_var;
        }
        else
        {
            temp_struct.PartTitle = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PartDetail = temp_var;
        }
        else
        {
            temp_struct.PartDetail = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorName = temp_var;
        }
        else
        {
            temp_struct.VendorName = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_Description = temp_var;
        }
        else
        {
            temp_struct.Vendor_Description = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorPN = temp_var;
        }
        else
        {
            temp_struct.VendorPN = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNPurchUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.BuyAs = temp_var;
        }
        else
        {
            temp_struct.BuyAs = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        float  costValue = _wtof(strTemp);
        temp_struct.VendorCost = costValue;


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        costValue = _wtof(strTemp);
        temp_struct.Cost = costValue;



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKAtQty"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }


        temp_struct.AtLevel  = _wtoi(strTemp);

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKROHSNote"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Notes = temp_var;
        }
        else
        {
            temp_struct.Notes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKLeadtime"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LeadTime = temp_var;
        }
        else
        {
            temp_struct.LeadTime = _T("");
        }

        m_dataset_PartsVendors.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

}
void Table_PN::Search_PNID(int PNID)
{
    PN_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from qryPN where PNID = %d"), PNID);

    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    pv_Table_PN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPartNumber = temp_var;
        }
        else
        {
            temp_struct.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNType = temp_var;
        }
        else
        {
            temp_struct.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNTitle = temp_var;
        }
        else
        {
            temp_struct.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNDetail = temp_var;
        }
        else
        {
            temp_struct.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNRevision = temp_var;
        }
        else
        {
            temp_struct.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStatus = temp_var;
        }
        else
        {
            temp_struct.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.ReqBy = temp_var;
        }
        else
        {
            temp_struct.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNCurrentCost = temp_var;
        }
        else
        {
            temp_struct.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNPrintFooter = temp_var;
        }
        else
        {
            temp_struct.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNMinStockQty = temp_var;
        }
        else
        {
            temp_struct.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNLastRollupCost = temp_var;
        }
        else
        {
            temp_struct.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNNote = temp_var;
        }
        else
        {
            temp_struct.PNNote = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPictureName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNImageName = temp_var;
        }
        else
        {
            temp_struct.PNImageName = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Catalog = temp_var;
		}
		else
		{
			temp_struct.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Power = temp_var;
		}
		else
		{
			temp_struct.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Voltage = temp_var;
		}
		else
		{
			temp_struct.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Tolerance = temp_var;
		}
		else
		{
			temp_struct.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Part_type = temp_var;
		}
		else
		{
			temp_struct.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Schematic_part = temp_var;
		}
		else
		{
			temp_struct.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Solidworks = temp_var;
		}
		else
		{
			temp_struct.Solidworks = _T("");
		}

        pv_Table_PN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Delete_ByPN(int PNID)
{
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;

	strSql.Format(_T("Delete  from PL where PL.PLListID = %d"), PNID);
	m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
	strSql.Format(_T("Delete  from PL where PL.PLPartID = %d"), PNID);
	m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

	strSql.Format(_T("Delete  from LNK where LNK.LNKPNID = %d"), PNID);
	m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
	
    strSql.Format(_T("Delete  from PN where PNID = %d"), PNID);
    m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Update_ByPN(PN_Struct PNItem)
{
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from qryPN Where PNID = %d"), PNItem.PNID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    /*  strSql.Format(_T("UPDATE qryPN SET  \
           PNPartNumber = '%s'   \
          ,PNType = '%s'  \
          ,PNTitle = '%s' \
          ,PNDetail = '%s'  \
          ,PNRevision = '%s'    \
          ,PNStatus = 'U'      \
          ,PNReqBy = '%s'       \
          ,PNCurrentCost = %f    \
          ,PNUser3 = '%s'            \
          ,PNMinStockQty = %f       \
          ,PNLastRollupCost =%f        \
          ,PNQty = %f ,PNNotes = '%s'   WHERE PNID = %d"),*/
    /*   PNItem.PNPartNumber,
       PNItem.PNType,
       PNItem.PNTitle,
       PNItem.PNDetail,
       PNItem.PNRevision,

       PNItem.ReqBy,
       PNItem.PNCurrentCost,
       PNItem.PNPrintFooter,
       PNItem.PNMinStockQty,
       PNItem.PNLastRollupCost,
       PNItem.Stock,
       PNItem.PNNote,
       PNItem.PNID);*/
    if(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = (_variant_t)PNItem.PNPartNumber;

        if(!PNItem.PNPartNumber.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNPartNumber", temp_var);
        }

        temp_var = (_variant_t)PNItem.PNType;

        if(!PNItem.PNType.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNType", temp_var);
        }

        temp_var = (_variant_t)PNItem.PNTitle;

        if(!PNItem.PNTitle.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNTitle", temp_var);
        }


        temp_var = (_variant_t)PNItem.PNDetail;

        if(!PNItem.PNDetail.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNDetail", temp_var);
        }

        temp_var = (_variant_t)PNItem.PNRevision;

        if(!PNItem.PNRevision.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNRevision", temp_var);
        }


        m_database_operator.m_pRecordset->PutCollect("PNStatus", (_variant_t)"U");


        temp_var = (_variant_t)PNItem.ReqBy;

        if(!PNItem.ReqBy.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNReqBy", temp_var);
        }


        temp_var = (_variant_t)PNItem.PNCurrentCost;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNCurrentCost", temp_var);
        }

        temp_var = (_variant_t)PNItem.PNPrintFooter;

        if(!PNItem.PNPrintFooter.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNUser3", (_variant_t)PNItem.PNPrintFooter);
        }

        temp_var = (_variant_t)PNItem.PNMinStockQty;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNMinStockQty", (_bstr_t)PNItem.PNMinStockQty);
        }

        temp_var = (_variant_t)PNItem.PNLastRollupCost;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNLastRollupCost", (_bstr_t)PNItem.PNLastRollupCost);
        }

        temp_var = (_variant_t)PNItem.Stock;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNQty", (_bstr_t)PNItem.Stock);
        }

        //
        temp_var = (_variant_t)PNItem.PNNote;

        if(!PNItem.PNNote.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNNotes", (_variant_t)PNItem.PNNote);
        }

        if(!PNItem.PNImageName.IsEmpty())
        {
            m_database_operator.m_pRecordset->PutCollect("PNPictureName", (_variant_t)PNItem.PNImageName);
        }


        m_database_operator.m_pRecordset->Update();


    }

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

}


void Table_PN::Add_ItemStock(PN_Struct PNItem)
{
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from qryPN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    PN_Struct temp_struct;

    if(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }

        temp_var = (_variant_t)PNItem.Stock;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNQty", (_bstr_t)(PNItem.Stock + temp_struct.Stock));
        }

        m_database_operator.m_pRecordset->Update();


    }

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

}

void Table_PN::Reduce_ItemStock(PN_Struct PNItem)
{
    _variant_t temp_var;
   // m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from qryPN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    PN_Struct temp_struct;

    if(!m_database_operator.m_pRecordset->EndOfFile)
    {


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Stock = temp_var;
        }
        else
        {
            temp_struct.Stock = 0;
        }


        temp_var = (_variant_t)PNItem.Stock;

        if(temp_var.vt != VT_NULL)
        {
            m_database_operator.m_pRecordset->PutCollect("PNQty", (_bstr_t)(temp_struct.Stock - PNItem.Stock));
        }




        m_database_operator.m_pRecordset->Update();


    }

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

BOOL Table_PN::Update_PartPrice(int PNID, float Price)
{
    try
    {
        //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
		m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;

        strSql.Format(_T("UPDATE qryPN SET  PNLastRollupCost = %0.2f  WHERE PNID = %d "), Price, PNID);

        m_database_operator.OpenRecordset(strSql);
        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }

    catch(CException* e)
    {
        return FALSE;
    }

}
PN_Struct Table_PN::Insert_ByPN(PN_Struct PNItem)
{
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    /*  strSql.Format(_T("UPDATE qryPN SET  \
           PNPartNumber = '%s'   \
          ,PNType = '%s'  \
          ,PNTitle = '%s' \
          ,PNDetail = '%s'  \
          ,PNRevision = '%s'    \
          ,PNStatus = 'U'      \
          ,PNReqBy = '%s'       \
          ,PNCurrentCost = %f    \
          ,PNUser3 = '%s'            \
          ,PNMinStockQty = %f       \
          ,PNLastRollupCost =%f        \
          ,PNQty = %f ,PNNotes = '%s'   WHERE PNID = %d"),*/
    /*   PNItem.PNPartNumber,
       PNItem.PNType,
       PNItem.PNTitle,
       PNItem.PNDetail,
       PNItem.PNRevision,

       PNItem.ReqBy,
       PNItem.PNCurrentCost,
       PNItem.PNPrintFooter,
       PNItem.PNMinStockQty,
       PNItem.PNLastRollupCost,
       PNItem.Stock,
       PNItem.PNNote,
       PNItem.PNID);*/
    if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
    {
	    if (!m_database_operator.m_pRecordset->Supports(adAddNew))
	    {
		    AfxMessageBox(L"Can't Add a new Item");
	    }
        m_database_operator.m_pRecordset->AddNew();
        temp_var = (_variant_t)PNItem.PNPartNumber;

		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNPartNumber"))->Value=_bstr_t(PNItem.PNPartNumber);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNType"))->Value=_bstr_t(PNItem.PNType);


		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNTitle"))->Value=_bstr_t(PNItem.PNTitle);

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNDetail"))->Value=_bstr_t(PNItem.PNDetail);
	
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNRevision"))->Value=_bstr_t(PNItem.PNRevision);
	/*	m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Brand_Vendor"))->Value=_bstr_t(PNItem.Brand_Vendor);*/

        m_database_operator.m_pRecordset->PutCollect("PNStatus", (_variant_t)"U");
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNStatus"))->Value=_bstr_t(L"U");

        

			m_database_operator.m_pRecordset->Fields->GetItem
		(_variant_t(L"PNReqBy"))->Value=_bstr_t(PNItem.ReqBy);
      
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNCurrentCost"))->Value=_bstr_t(PNItem.PNCurrentCost);
		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNUser3"))->Value=_bstr_t(PNItem.PNPrintFooter);
        
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNMinStockQty"))->Value=_bstr_t(PNItem.PNMinStockQty);
		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNLastRollupCost"))->Value=_bstr_t(PNItem.PNLastRollupCost);

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNQty"))->Value=_bstr_t(PNItem.Stock);
        //
  
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNNotes"))->Value=_bstr_t(PNItem.PNNote);
      
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNPictureName"))->Value=_bstr_t(PNItem.PNImageName);

		

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Brand_Vendor"))->Value=_bstr_t(PNItem.Brand_Vendor);

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Catalog"))->Value=_bstr_t(PNItem.Catalog);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Power"))->Value=_bstr_t(PNItem.Power);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Voltage"))->Value=_bstr_t(PNItem.Voltage);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Tolerance"))->Value=_bstr_t(PNItem.Tolerance);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Part_type"))->Value=_bstr_t(PNItem.Part_type);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Schematic_part"))->Value=_bstr_t(PNItem.Schematic_part);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Allegro_footprint"))->Value=_bstr_t(PNItem.Allegro_footprint);
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Solidworks"))->Value=_bstr_t(PNItem.Solidworks);
        m_database_operator.m_pRecordset->Update();


    }
	else
		{
			temp_var = (_variant_t)PNItem.PNPartNumber;
			m_database_operator.m_pRecordset->PutCollect("PNPartNumber", temp_var);
		 

			temp_var = (_variant_t)PNItem.PNType;
			m_database_operator.m_pRecordset->PutCollect("PNType", temp_var);
			 

			temp_var = (_variant_t)PNItem.PNTitle;
			m_database_operator.m_pRecordset->PutCollect("PNTitle", temp_var);
			 
			temp_var = (_variant_t)PNItem.Brand_Vendor;
			 m_database_operator.m_pRecordset->PutCollect("Brand_Vendor", temp_var);
			 

			temp_var = (_variant_t)PNItem.PNDetail;
			m_database_operator.m_pRecordset->PutCollect("PNDetail", temp_var);
			 

			temp_var = (_variant_t)PNItem.PNRevision;
			m_database_operator.m_pRecordset->PutCollect("PNRevision", temp_var);
			 


			m_database_operator.m_pRecordset->PutCollect("PNStatus", (_variant_t)"U");


			temp_var = (_variant_t)PNItem.ReqBy;
			m_database_operator.m_pRecordset->PutCollect("PNReqBy", temp_var);
			 


			temp_var = (_variant_t)PNItem.PNCurrentCost;

			if(temp_var.vt != VT_NULL)
			{
				m_database_operator.m_pRecordset->PutCollect("PNCurrentCost", temp_var);
			}

			temp_var = (_variant_t)PNItem.PNPrintFooter;
			m_database_operator.m_pRecordset->PutCollect("PNUser3", (_variant_t)PNItem.PNPrintFooter);
		 

			temp_var = (_variant_t)PNItem.PNMinStockQty;

			if(temp_var.vt != VT_NULL)
			{
				m_database_operator.m_pRecordset->PutCollect("PNMinStockQty", (_bstr_t)PNItem.PNMinStockQty);
			}

			temp_var = (_variant_t)PNItem.PNLastRollupCost;

			if(temp_var.vt != VT_NULL)
			{
				m_database_operator.m_pRecordset->PutCollect("PNLastRollupCost", (_bstr_t)PNItem.PNLastRollupCost);
			}

			temp_var = (_variant_t)PNItem.Stock;

			if(temp_var.vt != VT_NULL)
			{
				m_database_operator.m_pRecordset->PutCollect("PNQty", (_bstr_t)PNItem.Stock);
			}

			//
			temp_var = (_variant_t)PNItem.PNNote;
			m_database_operator.m_pRecordset->PutCollect("PNNotes", (_variant_t)PNItem.PNNote);
			 

			if(!PNItem.PNImageName.IsEmpty())
			{
				m_database_operator.m_pRecordset->PutCollect("PNPictureName", (_variant_t)PNItem.PNImageName);
			}

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Brand_Vendor"))->Value=_bstr_t(PNItem.Brand_Vendor);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Catalog"))->Value=_bstr_t(PNItem.Catalog);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Power"))->Value=_bstr_t(PNItem.Power);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Voltage"))->Value=_bstr_t(PNItem.Voltage);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Tolerance"))->Value=_bstr_t(PNItem.Tolerance);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Part_type"))->Value=_bstr_t(PNItem.Part_type);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Schematic_part"))->Value=_bstr_t(PNItem.Schematic_part);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Allegro_footprint"))->Value=_bstr_t(PNItem.Allegro_footprint);
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Solidworks"))->Value=_bstr_t(PNItem.Solidworks);

			m_database_operator.m_pRecordset->Update();


		}
	 

    strSql.Format(_T("Select * from qryPN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    if(m_database_operator.m_pRecordset->EndOfFile == VARIANT_FALSE)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNID = temp_var;
        }
        else
        {
            PNItem.PNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUNID"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNUNID = temp_var;
        }
        else
        {
            PNItem.PNUNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNPartNumber = temp_var;
        }
        else
        {
            PNItem.PNPartNumber = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNType = temp_var;
        }
        else
        {
            PNItem.PNType = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNTitle = temp_var;
        }
        else
        {
            PNItem.PNTitle = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNDetail = temp_var;
        }
        else
        {
            PNItem.PNDetail = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNRevision"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNRevision = temp_var;
        }
        else
        {
            PNItem.PNRevision = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNStatus"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNStatus = temp_var;
        }
        else
        {
            PNItem.PNStatus = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNReqBy"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.ReqBy = temp_var;
        }
        else
        {
            PNItem.ReqBy = _T("");
        }



        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNCurrentCost = temp_var;
        }
        else
        {
            PNItem.PNCurrentCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNPrintFooter = temp_var;
        }
        else
        {
            PNItem.PNPrintFooter = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNMinStockQty"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNMinStockQty = temp_var;
        }
        else
        {
            PNItem.PNMinStockQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNLastRollupCost = temp_var;
        }
        else
        {
            PNItem.PNLastRollupCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.Stock = temp_var;
        }
        else
        {
            PNItem.Stock = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNNotes"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNNote = temp_var;
        }
        else
        {
            PNItem.PNNote = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPictureName"));

        if(temp_var.vt != VT_NULL)
        {
            PNItem.PNImageName = temp_var;
        }
        else
        {
            PNItem.PNImageName = _T("");
        }


		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Brand_Vendor = temp_var;
		}
		else
		{
			PNItem.Brand_Vendor = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Catalog"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Catalog = temp_var;
		}
		else
		{
			PNItem.Catalog = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Power"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Power = temp_var;
		}
		else
		{
			PNItem.Power = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Voltage"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Voltage = temp_var;
		}
		else
		{
			PNItem.Voltage = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Tolerance"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Tolerance = temp_var;
		}
		else
		{
			PNItem.Tolerance = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Part_type"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Part_type = temp_var;
		}
		else
		{
			PNItem.Part_type = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Schematic_part"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Schematic_part = temp_var;
		}
		else
		{
			PNItem.Schematic_part = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Allegro_footprint"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Allegro_footprint = temp_var;
		}
		else
		{
			PNItem.Allegro_footprint = _T("");
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Solidworks"));

		if(temp_var.vt != VT_NULL)
		{
			PNItem.Solidworks = temp_var;
		}
		else
		{
			PNItem.Solidworks = _T("");
		}

    }

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();


    return PNItem;
}

BOOL Table_PN::SyncPNItemFromSpring(PN_SpringStruct PNItem)
{
    _variant_t temp_var;

    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    /*  strSql.Format(_T("UPDATE qryPN SET  \
           PNPartNumber = '%s'   \
          ,PNType = '%s'  \
          ,PNTitle = '%s' \
          ,PNDetail = '%s'  \
          ,PNRevision = '%s'    \
          ,PNStatus = 'U'      \
          ,PNReqBy = '%s'       \
          ,PNCurrentCost = %f    \
          ,PNUser3 = '%s'            \
          ,PNMinStockQty = %f       \
          ,PNLastRollupCost =%f        \
          ,PNQty = %f ,PNNotes = '%s'   WHERE PNID = %d"),*/
    /*   PNItem.PNPartNumber,
       PNItem.PNType,
       PNItem.PNTitle,
       PNItem.PNDetail,
       PNItem.PNRevision,

       PNItem.ReqBy,
       PNItem.PNCurrentCost,
       PNItem.PNPrintFooter,
       PNItem.PNMinStockQty,
       PNItem.PNLastRollupCost,
       PNItem.Stock,
       PNItem.PNNote,
       PNItem.PNID);*/
    if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
    {
	    if (!m_database_operator.m_pRecordset->Supports(adAddNew))
	    {
		    AfxMessageBox(L"Can't Add a new Item");
	    }
        m_database_operator.m_pRecordset->AddNew();
        

		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNPartNumber"))->Value=_bstr_t(PNItem.PNPartNumber);

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNTitle"))->Value=_bstr_t(PNItem.PNTitle);
			
		 
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNType"))->Value=_bstr_t(L"Part");

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNDetail"))->Value=_bstr_t(PNItem.PNDetail);
	
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"PNUser3"))->Value=_bstr_t(PNItem.PNUser3);
 

        
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Brand_Vendor"))->Value=_bstr_t(PNItem.Brand_Vendor);

        

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Catalog"))->Value=_bstr_t(PNItem.Catalog);
      
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Power"))->Value=_bstr_t(PNItem.Power);
		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Voltage"))->Value=_bstr_t(PNItem.Voltage);
        
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Tolerance"))->Value=_bstr_t(PNItem.Tolerance);
		
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Part_type"))->Value=_bstr_t(PNItem.Part_type);

		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Schematic_part"))->Value=_bstr_t(PNItem.Schematic_part);
        //
  
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Allegro_footprint"))->Value=_bstr_t(PNItem.Allegro_footprint);
      
		m_database_operator.m_pRecordset->Fields->GetItem
			(_variant_t(L"Solidworks"))->Value=_bstr_t(PNItem.Solidworks);

		

	 

        m_database_operator.m_pRecordset->Update();


    }
	else
		{
			 
			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"PNPartNumber"))->Value=_bstr_t(PNItem.PNPartNumber);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"PNTitle"))->Value=_bstr_t(PNItem.PNTitle);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"PNDetail"))->Value=_bstr_t(PNItem.PNDetail);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"PNUser3"))->Value=_bstr_t(PNItem.PNUser3);



			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Brand_Vendor"))->Value=_bstr_t(PNItem.Brand_Vendor);



			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Catalog"))->Value=_bstr_t(PNItem.Catalog);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Power"))->Value=_bstr_t(PNItem.Power);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Voltage"))->Value=_bstr_t(PNItem.Voltage);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Tolerance"))->Value=_bstr_t(PNItem.Tolerance);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Part_type"))->Value=_bstr_t(PNItem.Part_type);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Schematic_part"))->Value=_bstr_t(PNItem.Schematic_part);
			//

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Allegro_footprint"))->Value=_bstr_t(PNItem.Allegro_footprint);

			m_database_operator.m_pRecordset->Fields->GetItem
				(_variant_t(L"Solidworks"))->Value=_bstr_t(PNItem.Solidworks);
			m_database_operator.m_pRecordset->Update();


		}
	 
	 BOOL ReturnValue = TRUE;
    strSql.Format(_T("Select * from qryPN Where PNPartNumber = '%s' "), PNItem.PNPartNumber);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
    {
        
		ReturnValue = FALSE;
    }

    // m_database_operator.OpenRecordset(strSql);
    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();


    return ReturnValue;
}


BOMListItemStatus Table_PN::CheckBomListItemStatus(BOMListItemStatus PNItem)
{
    BOMListItemStatus ReturnItem;
    _variant_t temp_var;
  
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PN Where PNPartNumber = '%s' "), PNItem.PN);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

     
    if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
    {
	    ReturnItem.PNFlag =TRUE ;
		return ReturnItem;
    }
	else
	{
	    ReturnItem.PNFlag = FALSE;
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));
		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.PartID = temp_var;
			PNItem.PartID = temp_var;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));
		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.PN = temp_var;
		}
	
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));
		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.Value = temp_var;
		}
		if (ReturnItem.Value.Trim().CompareNoCase(PNItem.Value)==0)
		{
		   ReturnItem.ItemStaus.Value = TRUE;
		}
		else
		{
		   ReturnItem.ItemStaus.Value = FALSE;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.Description = temp_var;
		}
		if (ReturnItem.Description.Trim().CompareNoCase(PNItem.Description)==0)
		{
			ReturnItem.ItemStaus.Description = TRUE;
		}
		else
		{
			ReturnItem.ItemStaus.Description = FALSE;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.PCB_Footprint = temp_var;
		}

		if (ReturnItem.PCB_Footprint.Trim().CompareNoCase(PNItem.PCB_Footprint)==0)
		{
			ReturnItem.ItemStaus.PCB_Footprint = TRUE;
		}
		else
		{
			ReturnItem.ItemStaus.PCB_Footprint = FALSE;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.Brand_Vendor = temp_var;
		}

		if (ReturnItem.Brand_Vendor.Trim().CompareNoCase(PNItem.Brand_Vendor)==0)
		{
			ReturnItem.ItemStaus.Brand_Vendor = TRUE;
		}
		else
		{
			ReturnItem.ItemStaus.Brand_Vendor = FALSE;
		}


	}
    m_database_operator.CloseRecordset();
    ////m_database_operator.CloseConn();

	

	strSql.Format(_T("Select * from PL Where PLListID = %d AND PLPartID = %d  "), PNItem.ListID, PNItem.PartID);
	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

	if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
	{
	   ReturnItem.BOMFlag =TRUE ;
	   return ReturnItem;
		/*m_database_operator.m_pRecordset->AddNew();
		m_database_operator.m_pRecordset->PutCollect("PLListID", (_variant_t)PLItem.PLListID);
		m_database_operator.m_pRecordset->PutCollect("PLPartID", (_variant_t)PLItem.PLPartID);
		m_database_operator.m_pRecordset->PutCollect("PLItem", (_variant_t)PLItem.PLItem);
		m_database_operator.m_pRecordset->PutCollect("PLQty", (_variant_t)PLItem.PLQty);

		if(!PLItem.PLRefMemo.IsEmpty())
		{
		m_database_operator.m_pRecordset->PutCollect("PLRefMemo", (_variant_t)PLItem.PLRefMemo);
		}

		m_database_operator.m_pRecordset->Update();*/
	}
	else
	{
	    ReturnItem.BOMFlag = FALSE;
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLRefMemo"));
		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.Part_Reference = temp_var;
		}
		if (ReturnItem.Part_Reference.Trim().CompareNoCase(PNItem.Part_Reference)==0)
		{
			ReturnItem.ItemStaus.Part_Reference = TRUE;
		}
		else
		{
			ReturnItem.ItemStaus.Part_Reference = FALSE;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLQty"));
		if(temp_var.vt != VT_NULL)
		{
			ReturnItem.Quantity = temp_var;
		}

		if (ReturnItem.Quantity.Trim().CompareNoCase(PNItem.Quantity)==0)
		{
			ReturnItem.ItemStaus.Quantity = TRUE;
		}
		else
		{
			ReturnItem.ItemStaus.Quantity = FALSE;
		}
	 
	}

	m_database_operator.CloseRecordset();
	//m_database_operator.CloseConn();



    return ReturnItem;
}

void Table_PN::Initial_BomData()
{
    PList_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from qryBOM where PLListID = %d order by PLItem"), m_PNID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_bomdataset.clear();

    //PLID
    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_struct.ParentPNID = m_PNID;
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLItem"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Item = temp_var;
        }
        else
        {
            temp_struct.Item = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PLID = temp_var;
        }
        else
        {
            temp_struct.PLID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLPartID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PartID = temp_var;
        }
        else
        {
            temp_struct.PartID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Qty = temp_var;
        }
        else
        {
            temp_struct.Qty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PN = temp_var;
        }
        else
        {
            temp_struct.PN = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStock = temp_var;
        }
        else
        {
            temp_struct.PNStock = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Type = temp_var;
        }
        else
        {
            temp_struct.Type = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Title = temp_var;
        }
        else
        {
            temp_struct.Title = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Detail = temp_var;
        }
        else
        {
            temp_struct.Detail = _T("");
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        float costValue = _wtof(strTemp);
        temp_struct.MFCost = costValue;


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        if(_wtoi(strTemp) != 0)
        {
            float costValue = _wtof(strTemp);
            temp_struct.MFCost = costValue;
        }

        temp_struct.MFExtCost  = temp_struct.Qty * temp_struct.MFCost;

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor = temp_var;
        }
        else
        {
            temp_struct.Vendor = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_PN = temp_var;
        }
        else
        {
            temp_struct.Vendor_PN = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_Desc = temp_var;
        }
        else
        {
            temp_struct.Vendor_Desc = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRMfrName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Mfr = temp_var;
        }
        else
        {
            temp_struct.Mfr = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRPNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Mfr_PN = temp_var;
        }
        else
        {
            temp_struct.Mfr_PN = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLRefMemo"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Reference = temp_var;
        }
        else
        {
            temp_struct.Reference = _T("");
        }
		

			temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Brand_Vendor"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.Brand = temp_var;
		}
		else
		{
			temp_struct.Brand = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNUser3"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.FootPrint = temp_var;
		}
		else
		{
			temp_struct.FootPrint = _T("");
		}

		

        m_bomdataset.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

void Table_PN::Build_TreeData(int ParentID, CString ParentPN)
{
    PList_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    struct NodeSTRUCT
    {
        int PNID;
        CString PNName;
    };

    m_bomdataset.clear();
    NodeSTRUCT parentnode;
    parentnode.PNID = ParentID;
    parentnode.PNName = ParentPN;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;

    std::stack <NodeSTRUCT> bomstack;
    bomstack.push(parentnode);

    while(!bomstack.empty())
    {
        NodeSTRUCT childnode = bomstack.top();
        bomstack.pop();

        strSql.Format(_T("Select * from qryBOM where PLListID = %d order by PLItem"), childnode.PNID);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        temp_struct.ParentPNID = childnode.PNID;
        temp_struct.ParentStrPN = childnode.PNName;

        while(!m_database_operator.m_pRecordset->EndOfFile)
        {

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLItem"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Item = temp_var;
            }
            else
            {
                temp_struct.Item = 0;
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.PN = temp_var;
                childnode.PNName = temp_var;
            }
            else
            {
                temp_struct.PN = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLPartID"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.PLID = temp_var;

            }
            else
            {
                temp_struct.PLID = 0;
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLPartID"));

            if(temp_var.vt != VT_NULL)
            {

                childnode.PNID = temp_var;
                bomstack.push(childnode);
            }


            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLQty"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Qty = temp_var;
            }
            else
            {
                temp_struct.Qty = 0;
            }


            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.PNStock = temp_var;
            }
            else
            {
                temp_struct.PNStock = 0;
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Type = temp_var;
            }
            else
            {
                temp_struct.Type = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Title = temp_var;
            }
            else
            {
                temp_struct.Title = _T("");
            }


            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Detail = temp_var;
            }
            else
            {
                temp_struct.Detail = _T("");
            }





            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

            if(temp_var.vt != VT_NULL)
            {
                strTemp = temp_var;
            }
            else
            {
                strTemp = _T("");
            }

            float costValue = _wtof(strTemp);
            temp_struct.MFCost = costValue;


            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

            if(temp_var.vt != VT_NULL)
            {
                strTemp = temp_var;
            }
            else
            {
                strTemp = _T("");
            }

            if(_wtoi(strTemp) != 0)
            {
                float costValue = _wtof(strTemp);
                temp_struct.MFCost = costValue;
            }

            temp_struct.MFExtCost  = temp_struct.Qty * temp_struct.MFCost;

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Vendor = temp_var;
            }
            else
            {
                temp_struct.Vendor = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Vendor_PN = temp_var;
            }
            else
            {
                temp_struct.Vendor_PN = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Vendor_Desc = temp_var;
            }
            else
            {
                temp_struct.Vendor_Desc = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRMfrName"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Mfr = temp_var;
            }
            else
            {
                temp_struct.Mfr = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRPNID"));

            if(temp_var.vt != VT_NULL)
            {
                temp_struct.Mfr_PN = temp_var;
            }
            else
            {
                temp_struct.Mfr_PN = _T("");
            }

            m_bomdataset.push_back(temp_struct);
            m_database_operator.m_pRecordset->MoveNext();
        }

    }


    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();


}
//Build_AssemblyData

void Table_PN::Build_AssemblyData(int ParentID, CString ParentPN)
{
    PList_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    struct NodeSTRUCT
    {
        int PNID;
        CString PNName;
    };
    vector<PList_Struct> tempdataset ;
    m_bomdataset.clear();
    NodeSTRUCT parentnode;
    parentnode.PNID = ParentID;
    parentnode.PNName = ParentPN;

	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
 
    strSql.Format(_T("Select * from qryBOM where PLListID = %d  order by PLItem"), parentnode.PNID);
    m_database_operator.CloseRecordset();
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    temp_struct.ParentPNID = parentnode.PNID;
    temp_struct.ParentStrPN = parentnode.PNName;

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLItem"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Item = temp_var;
        }
        else
        {
            temp_struct.Item = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PN = temp_var;

        }
        else
        {
            temp_struct.PN = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLRefMemo"));

		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Reference = temp_var;

		}
		else
		{
			temp_struct.Reference = _T("");
		}
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLPartID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PLID = temp_var;

        }
        else
        {
            temp_struct.PLID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Qty = temp_var;
        }
        else
        {
            temp_struct.Qty = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNStock = temp_var;
        }
        else
        {
            temp_struct.PNStock = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Type = temp_var;
        }
        else
        {
            temp_struct.Type = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Title = temp_var;
        }
        else
        {
            temp_struct.Title = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Detail = temp_var;
        }
        else
        {
            temp_struct.Detail = _T("");
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        float costValue = _wtof(strTemp);
        temp_struct.MFCost = costValue;

        //LNKCurrentCost


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.vendorPrice = temp_var;
        }
        else
        {
            temp_struct.vendorPrice = 0;
        }

        /* float costValue = _wtof(strTemp);
         temp_struct.MFCost = costValue;*/

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        if(_wtoi(strTemp) != 0)
        {
            float costValue = _wtof(strTemp);
            temp_struct.MFCost = costValue;
        }

        temp_struct.MFExtCost  = temp_struct.Qty * temp_struct.MFCost;

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor = temp_var;
        }
        else
        {
            temp_struct.Vendor = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_PN = temp_var;
        }
        else
        {
            temp_struct.Vendor_PN = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_Desc = temp_var;
        }
        else
        {
            temp_struct.Vendor_Desc = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRMfrName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Mfr = temp_var;
        }
        else
        {
            temp_struct.Mfr = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRPNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Mfr_PN = temp_var;
        }
        else
        {
            temp_struct.Mfr_PN = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UseUnitID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNUNID = temp_var;
        }
        else
        {
            temp_struct.PNUNID = -1;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyUnitID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.BuyUNID = temp_var;
        }
        else
        {
            temp_struct.BuyUNID = -1;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKID = temp_var;
        }
        else
        {
            temp_struct.LNKID = -1;
        }


        tempdataset.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }


    for(int i = 0; i < tempdataset.size(); i++)
    {
        parentnode.PNID = tempdataset.at(i).PLID;
        parentnode.PNName = tempdataset.at(i).PN;
        int qty = tempdataset.at(i).Qty;
        strSql.Format(_T("Select * from qryBOM where PLListID = %d order by PLItem"), parentnode.PNID);
        m_database_operator.CloseRecordset();
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
        temp_struct.ParentPNID = parentnode.PNID;
        temp_struct.ParentStrPN = parentnode.PNName;

        if(VARIANT_FALSE == m_database_operator.m_pRecordset->EndOfFile)
        {
            while(!m_database_operator.m_pRecordset->EndOfFile)
            {

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLItem"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Item = temp_var;
                }
                else
                {
                    temp_struct.Item = 0;
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNPartNumber"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.PN = temp_var;
                }
                else
                {
                    temp_struct.PN = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLPartID"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.PLID = temp_var;
                }
                else
                {
                    temp_struct.PLID = 0;
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PLQty"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Qty = temp_var;
                    temp_struct.Qty = temp_struct.Qty * qty;
                }
                else
                {
                    temp_struct.Qty = 0;
                }


                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNQty"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.PNStock = temp_var;
                }
                else
                {
                    temp_struct.PNStock = 0;
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNType"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Type = temp_var;
                }
                else
                {
                    temp_struct.Type = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNTitle"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Title = temp_var;
                }
                else
                {
                    temp_struct.Title = _T("");
                }


                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNDetail"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Detail = temp_var;
                }
                else
                {
                    temp_struct.Detail = _T("");
                }





                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNCurrentCost"));

                if(temp_var.vt != VT_NULL)
                {
                    strTemp = temp_var;
                }
                else
                {
                    strTemp = _T("");
                }

                float costValue = _wtof(strTemp);
                temp_struct.MFCost = costValue;



                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKCurrentCost"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.vendorPrice = temp_var;
                }
                else
                {
                    temp_struct.vendorPrice = 0;
                }


                /*temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNLastRollupCost"));
                if(temp_var.vt != VT_NULL)
                {
                    strTemp = temp_var;
                }
                else
                {
                    strTemp = _T("");
                }
                if(_wtoi(strTemp) != 0)
                {
                    float costValue = _wtof(strTemp);
                    temp_struct.MFCost = costValue;
                }*/

                temp_struct.MFExtCost  = temp_struct.Qty * temp_struct.MFCost;

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Vendor = temp_var;
                }
                else
                {
                    temp_struct.Vendor = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Vendor_PN = temp_var;
                }
                else
                {
                    temp_struct.Vendor_PN = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Vendor_Desc = temp_var;
                }
                else
                {
                    temp_struct.Vendor_Desc = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRMfrName"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Mfr = temp_var;
                }
                else
                {
                    temp_struct.Mfr = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("MFRPNID"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.Mfr_PN = temp_var;
                }
                else
                {
                    temp_struct.Mfr_PN = _T("");
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UseUnitID"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.PNUNID = temp_var;
                }
                else
                {
                    temp_struct.PNUNID = -1;
                }

                temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyUnitID"));

                if(temp_var.vt != VT_NULL)
                {
                    temp_struct.BuyUNID = temp_var;
                }
                else
                {
                    temp_struct.BuyUNID = -1;
                }

                m_bomdataset.push_back(temp_struct);
                m_database_operator.m_pRecordset->MoveNext();
            }
        }
        else
        {
            m_bomdataset.push_back(tempdataset.at(i));
        }


    }

    //use unit update  -- just a name
    for(int i = 0; i < m_bomdataset.size(); i++)
    {
        if(m_bomdataset.at(i).PNUNID == -1)
        {
            continue;
        }

        strSql.Format(_T("select * from UN Where UNID = %d"), m_bomdataset.at(i).PNUNID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(VARIANT_FALSE == m_database_operator.m_pRecordset->EndOfFile)
        {
            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNUseUnits"));

            if(temp_var.vt != VT_NULL)
            {
                m_bomdataset.at(i).UseAs = temp_var;
            }
            else
            {
                m_bomdataset.at(i).UseAs = _T("");
            }
        }
    }

    //buy unit update  --name and convert number
    for(int i = 0; i < m_bomdataset.size(); i++)
    {
        if(m_bomdataset.at(i).PNUNID == -1)
        {
            continue;
        }

        strSql.Format(_T("select * from UN Where UNID = %d"), m_bomdataset.at(i).BuyUNID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(VARIANT_FALSE == m_database_operator.m_pRecordset->EndOfFile)
        {


            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNPurchUnits"));

            if(temp_var.vt != VT_NULL)
            {
                m_bomdataset.at(i).BuyAs = temp_var;
            }
            else
            {
                m_bomdataset.at(i).BuyAs = _T("");
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNConvUnits"));

            if(temp_var.vt != VT_NULL)
            {
                m_bomdataset.at(i).UNConvUnits = temp_var;
            }
            else
            {
                m_bomdataset.at(i).UNConvUnits = 1;
            }

        }
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Search_Vendor(CString VendorName)
{
    SU_Struct temp_struct;
    CString  strTemp;
    int IntTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql = _T("Select * from qrySU Where SUSupplier LIKE '%") +  VendorName +
             _T("%'   Order By SUID DESC");
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_vendor .clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUID = temp_var;
        }
        else
        {
            temp_struct.SUID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUSupplier = temp_var;
        }
        else
        {
            temp_struct.SUSupplier = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAddress"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUAddress = temp_var;
        }
        else
        {
            temp_struct.SUAddress = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCountry"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCountry = temp_var;
        }
        else
        {
            temp_struct.SUCountry = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUPhone1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUPhone1 = temp_var;
        }
        else
        {
            temp_struct.SUPhone1 = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUPhone2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUPhone2 = temp_var;
        }
        else
        {
            temp_struct.SUPhone2 = _T("");
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFAX"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUFAX = temp_var;
        }
        else
        {
            temp_struct.SUFAX = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUWeb"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUWeb = temp_var;
        }
        else
        {
            temp_struct.SUWeb = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUContact1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUContact1 = temp_var;
        }
        else
        {
            temp_struct.SUContact1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUContact2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUContact2 = temp_var;
        }
        else
        {
            temp_struct.SUContact2 = _T("");
        }

        //temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUDateLast"));

        //if(temp_var.vt != VT_NULL)
        //{
        //    temp_struct.SUDateLast = temp_var;
        //}
        //else
        //{
        //    temp_struct.SUDateLast = _T("");
        //}

		temp_struct.SUDateLast = _T("");
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFollowup"));
		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUFollowup"));
		}

        
		
        if(IntTemp == 1)
        {
            temp_struct.SUFollowup = TRUE;
        }
        else
        {
            temp_struct.SUFollowup = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUNotes = temp_var;
        }
        else
        {
            temp_struct.SUNotes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCode"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCode = temp_var;
        }
        else
        {
            temp_struct.SUCode = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAccount"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUAccount = temp_var;
        }
        else
        {
            temp_struct.SUAccount = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUTerms"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUTerms = temp_var;
        }
        else
        {
            temp_struct.SUTerms = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFedTaxID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUFedTaxID = temp_var;
        }
        else
        {
            temp_struct.SUFedTaxID = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUStateTaxID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUStateTaxID = temp_var;
        }
        else
        {
            temp_struct.SUStateTaxID = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUEMail1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUEMail1 = temp_var;
        }
        else
        {
            temp_struct.SUEMail1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUEMail2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUEMail2 = temp_var;
        }
        else
        {
            temp_struct.SUEMail2 = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurDedExRate"));
		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUCurDedExRate"));
		}
       

        if(IntTemp == 1)
        {
            temp_struct.SUCurDedExRate = TRUE;
        }
        else
        {
            temp_struct.SUCurDedExRate = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurExRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCurExRate = temp_var;
        }
        else
        {
            temp_struct.SUFollowup = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCURID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCURID = temp_var;
        }
        else
        {
            temp_struct.SUCURID = 0;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurReverse"));
		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUCurReverse"));
		}
        

        if(IntTemp == 1)
        {
            temp_struct.SUCurReverse = TRUE;
        }
        else
        {
            temp_struct.SUCurReverse = FALSE;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurReverse"));
		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUNoPhonePrefix"));
		}
       

        if(IntTemp == 1)
        {
            temp_struct.SUNoPhonePrefix = TRUE;
        }
        else
        {
            temp_struct.SUNoPhonePrefix = FALSE;
        }

        m_dataset_vendor.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Search_Vendors(CString VendorName)
{
    SU_Struct temp_struct;
    CString  strTemp;
    int IntTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;

    strSql = _T("Select * from qrySU where SUSupplier LIKE '%");
    strSql += VendorName;
    strSql += _T("%' Order by SUID DESC ") ;
    /*and SUCode LIKE '%");
      strSql+=Code;
      strSql+=_T("%'") ;*/


    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_vendor .clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUID = temp_var;
        }
        else
        {
            temp_struct.SUID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUSupplier = temp_var;
        }
        else
        {
            temp_struct.SUSupplier = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAddress"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUAddress = temp_var;
        }
        else
        {
            temp_struct.SUAddress = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCountry"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCountry = temp_var;
        }
        else
        {
            temp_struct.SUCountry = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUPhone1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUPhone1 = temp_var;
        }
        else
        {
            temp_struct.SUPhone1 = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUPhone2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUPhone2 = temp_var;
        }
        else
        {
            temp_struct.SUPhone2 = _T("");
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFAX"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUFAX = temp_var;
        }
        else
        {
            temp_struct.SUFAX = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUWeb"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUWeb = temp_var;
        }
        else
        {
            temp_struct.SUWeb = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUContact1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUContact1 = temp_var;
        }
        else
        {
            temp_struct.SUContact1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUContact2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUContact2 = temp_var;
        }
        else
        {
            temp_struct.SUContact2 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUDateLast"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUDateLast = temp_var;
        }
        else
        {
            temp_struct.SUDateLast = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFollowup"));
        if (temp_var.vt == VT_NULL)
        {
            IntTemp = 0;
        }
        else
        {
            IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUFollowup"));
        }
        if(IntTemp == 1)
        {
            temp_struct.SUFollowup = TRUE;
        }
        else
        {
            temp_struct.SUFollowup = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUNotes = temp_var;
        }
        else
        {
            temp_struct.SUNotes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCode"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCode = temp_var;
        }
        else
        {
            temp_struct.SUCode = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAccount"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUAccount = temp_var;
        }
        else
        {
            temp_struct.SUAccount = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUTerms"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUTerms = temp_var;
        }
        else
        {
            temp_struct.SUTerms = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUFedTaxID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUFedTaxID = temp_var;
        }
        else
        {
            temp_struct.SUFedTaxID = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUStateTaxID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUStateTaxID = temp_var;
        }
        else
        {
            temp_struct.SUStateTaxID = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUEMail1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUEMail1 = temp_var;
        }
        else
        {
            temp_struct.SUEMail1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUEMail2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUEMail2 = temp_var;
        }
        else
        {
            temp_struct.SUEMail2 = _T("");
        }

     
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurDedExRate"));
        if (temp_var.vt == VT_NULL)
        {
            IntTemp = 0;
        }
        else
        {
            IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUCurDedExRate"));
        }
        if(IntTemp == 1)
        {
            temp_struct.SUCurDedExRate = TRUE;
        }
        else
        {
            temp_struct.SUCurDedExRate = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurExRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCurExRate = temp_var;
        }
        else
        {
            temp_struct.SUFollowup = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCURID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUCURID = temp_var;
        }
        else
        {
            temp_struct.SUCURID = 0;
        }

        
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUCurReverse"));
        if (temp_var.vt == VT_NULL)
        {
            IntTemp = 0;
        }
        else
        {
            IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUCurReverse"));
        }
        if(IntTemp == 1)
        {
            temp_struct.SUCurReverse = TRUE;
        }
        else
        {
            temp_struct.SUCurReverse = FALSE;
        }

        
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUNoPhonePrefix"));
        if (temp_var.vt == VT_NULL)
        {
            IntTemp = 0;
        }
        else
        {
            IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("SUNoPhonePrefix"));
        }
        if(IntTemp == 1)
        {
            temp_struct.SUNoPhonePrefix = TRUE;
        }
        else
        {
            temp_struct.SUNoPhonePrefix = FALSE;
        }

        m_dataset_vendor.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
void Table_PN::Search_POM(CString m_strPO,CString m_strVendorName)
{
    PO_Struct temp_struct;
    CString  strTemp;
    int IntTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
   // strSql.Format(_T("Select * from POM Order By POMID DESC"));
   strSql= _T("Select * from POM Where POMNumber LIKE '%") +
        m_strPO +
        _T("%' AND POMSupplier LIKE '%") +
        m_strVendorName +
        _T("%'  Order By POMID DESC");

    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_po.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMID = temp_var;
        }
        else
        {
            temp_struct.POMID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMNumber = temp_var;
        }
        else
        {
            temp_struct.POMNumber = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDatePrinted"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDatePrinted = temp_var;
        }
        else
        {
            temp_struct.POMDatePrinted = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSupplier = temp_var;
        }
        else
        {
            temp_struct.POMSupplier = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSUID = temp_var;
        }
        else
        {
            temp_struct.POMSUID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMAccount"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMAccount = temp_var;
        }
        else
        {
            temp_struct.POMAccount = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMNotes = temp_var;
        }
        else
        {
            temp_struct.POMNotes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMAttnTo"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMAttnTo = temp_var;
        }
        else
        {
            temp_struct.POMAttnTo = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMFromBuyer"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMFromBuyer = temp_var;
        }
        else
        {
            temp_struct.POMFromBuyer = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMEngrgContact"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMEngrgContact = temp_var;
        }
        else
        {
            temp_struct.POMEngrgContact = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateReq"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateReq = temp_var;
        }
        else
        {
            temp_struct.POMDateReq = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateClosed"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateClosed = temp_var;
        }
        else
        {
            temp_struct.POMDateClosed = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMFOB"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMFOB = temp_var;
        }
        else
        {
            temp_struct.POMFOB = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTerms"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTerms = temp_var;
        }
        else
        {
            temp_struct.POMTerms = _T("");
        }

        
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMInsurance"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMInsurance"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMInsurance = TRUE;
        }
        else
        {
            temp_struct.POMInsurance = FALSE;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMUseOurShpngAcct"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMUseOurShpngAcct"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMUseOurShpngAcct = TRUE;
        }
        else
        {
            temp_struct.POMUseOurShpngAcct = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShippingAcct"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShippingAcct = temp_var;
        }
        else
        {
            temp_struct.POMShippingAcct = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMThisIsRFQ"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMThisIsRFQ"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMThisIsRFQ = TRUE;
        }
        else
        {
            temp_struct.POMThisIsRFQ = FALSE;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMPendingPrint"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMPendingPrint"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMPendingPrint = TRUE;
        }
        else
        {
            temp_struct.POMPendingPrint = FALSE;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxRate = temp_var;
        }
        else
        {
            temp_struct.POMTaxRate = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipMethod"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipMethod = temp_var;
        }
        else
        {
            temp_struct.POMShipMethod = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipTo"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipTo = temp_var;
        }
        else
        {
            temp_struct.POMShipTo = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxRate2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxRate2 = temp_var;
        }
        else
        {
            temp_struct.POMTaxRate2 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxTotal2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxTotal2 = temp_var;
        }
        else
        {
            temp_struct.POMTaxTotal2 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTax2OnTax1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTax2OnTax1 = temp_var;
        }
        else
        {
            temp_struct.POMTax2OnTax1 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTotalCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTotalCost = temp_var;
        }
        else
        {
            temp_struct.POMTotalCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTotalTax"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTotalTax = temp_var;
        }
        else
        {
            temp_struct.POMTotalTax = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSubTotal"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSubTotal = temp_var;
        }
        else
        {
            temp_struct.POMSubTotal = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMCURID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMCURID = temp_var;
        }
        else
        {
            temp_struct.POMCURID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipMethod"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipMethod = temp_var;
        }
        else
        {
            temp_struct.POMShipMethod = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMCurExRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMCurExRate = temp_var;
        }
        else
        {
            temp_struct.POMCurExRate = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateReqDate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateReqDate = temp_var;
        }
        else
        {
            temp_struct.POMDateReqDate = _T("");
        }

        m_dataset_po.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}
PO_Struct Table_PN::Insert_PO(PO_Struct temp_PO)
{
    temp_PO.POMID = -1;

    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from POM Where POMNumber = '%s' "), temp_PO.POMNumber);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile)
        {
            m_database_operator.m_pRecordset->AddNew();

            m_database_operator.m_pRecordset->PutCollect("POMNumber", (_variant_t)temp_PO.POMNumber);
            m_database_operator.m_pRecordset->PutCollect("POMSupplier", (_variant_t)temp_PO.POMSupplier);
            m_database_operator.m_pRecordset->PutCollect("POMFromBuyer", (_variant_t)temp_PO.POMFromBuyer);
            m_database_operator.m_pRecordset->PutCollect("POMEngrgContact", (_variant_t)temp_PO.POMEngrgContact);
            m_database_operator.m_pRecordset->PutCollect("POMDateReq", (_variant_t)temp_PO.POMDateReq);
            m_database_operator.m_pRecordset->PutCollect("POMShipTo", (_variant_t)temp_PO.POMShipTo);
            CTime time = CTime::GetCurrentTime();
            CString strTime = L"";
            strTime.Format(_T("%d/%d/%d"), time.GetYear(), time.GetMonth(), time.GetDay());
            m_database_operator.m_pRecordset->PutCollect(_T("POMDateReq"), (_variant_t)strTime);

            m_database_operator.m_pRecordset->Update();
        }

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {
            temp_PO.POMID = m_database_operator.m_pRecordset->GetCollect("POMID");
        }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();


    }
    catch(CException* e)
    {

        e->GetErrorMessage(_T("Exception,PO-Insert"), 0);
    }

    return temp_PO ;
}
void Table_PN::Update_PO(PO_Struct temp_PO)
{
    temp_PO.POMID = -1;

    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from POM Where POMNumber = '%s' "), temp_PO.POMNumber);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {


            m_database_operator.m_pRecordset->PutCollect("POMTotalCost", (_variant_t)temp_PO.POMTotalCost);

            m_database_operator.m_pRecordset->Update();
        }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();


    }
    catch(CException* e)
    {

        e->GetErrorMessage(_T("Exception,PO-Insert"), 0);
    }
}

void Table_PN::Delete_PO(PO_Struct temp_PO)
{
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Delete  from POM where POMID = %d"), temp_PO.POMID);
    m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);


    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

void Table_PN::Initial_Type()
{
    Type_Struct temp_struct;
    CString  strTemp;

    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from TYPE Order By TYPEID"));
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_type.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("TYPEID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.TYPEID = temp_var;
        }
        else
        {
            temp_struct.TYPEID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("TYPEType"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.TYPEType = temp_var;
        }
        else
        {
            temp_struct.TYPEType = L"";
        }

        m_dataset_type.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

void Table_PN::Search_PO()
{
    PO_Struct temp_struct;
    CString  strTemp;
    int IntTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from POM Where POMID = %d Order By POMID"), m_POMID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	m_dataset_purchaseorder.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMID = temp_var;
        }
        else
        {
            temp_struct.POMID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMNumber"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMNumber = temp_var;
        }
        else
        {
            temp_struct.POMNumber = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDatePrinted"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDatePrinted = temp_var;
        }
        else
        {
            temp_struct.POMDatePrinted = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSupplier = temp_var;
        }
        else
        {
            temp_struct.POMSupplier = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSUID = temp_var;
        }
        else
        {
            temp_struct.POMSUID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMAccount"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMAccount = temp_var;
        }
        else
        {
            temp_struct.POMAccount = _T("");
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMNotes = temp_var;
        }
        else
        {
            temp_struct.POMNotes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMAttnTo"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMAttnTo = temp_var;
        }
        else
        {
            temp_struct.POMAttnTo = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMFromBuyer"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMFromBuyer = temp_var;
        }
        else
        {
            temp_struct.POMFromBuyer = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMEngrgContact"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMEngrgContact = temp_var;
        }
        else
        {
            temp_struct.POMEngrgContact = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateReq"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateReq = temp_var;
        }
        else
        {
            temp_struct.POMDateReq = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateClosed"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateClosed = temp_var;
        }
        else
        {
            temp_struct.POMDateClosed = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMFOB"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMFOB = temp_var;
        }
        else
        {
            temp_struct.POMFOB = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTerms"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTerms = temp_var;
        }
        else
        {
            temp_struct.POMTerms = _T("");
        }

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMInsurance"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMInsurance"));
		}
      

        if(IntTemp == 1)
        {
            temp_struct.POMInsurance = TRUE;
        }
        else
        {
            temp_struct.POMInsurance = FALSE;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMUseOurShpngAcct"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMUseOurShpngAcct"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMUseOurShpngAcct = TRUE;
        }
        else
        {
            temp_struct.POMUseOurShpngAcct = FALSE;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShippingAcct"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShippingAcct = temp_var;
        }
        else
        {
            temp_struct.POMShippingAcct = _T("");
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMThisIsRFQ"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMThisIsRFQ"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMThisIsRFQ = TRUE;
        }
        else
        {
            temp_struct.POMThisIsRFQ = FALSE;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMPendingPrint"));

		if (temp_var.vt == VT_NULL)
		{
			IntTemp = 0;
		}
		else
		{
			IntTemp = m_database_operator.m_pRecordset->GetCollect(_T("POMPendingPrint"));
		}
        if(IntTemp == 1)
        {
            temp_struct.POMPendingPrint = TRUE;
        }
        else
        {
            temp_struct.POMPendingPrint = FALSE;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxRate = temp_var;
        }
        else
        {
            temp_struct.POMTaxRate = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipMethod"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipMethod = temp_var;
        }
        else
        {
            temp_struct.POMShipMethod = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipTo"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipTo = temp_var;
        }
        else
        {
            temp_struct.POMShipTo = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxRate2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxRate2 = temp_var;
        }
        else
        {
            temp_struct.POMTaxRate2 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTaxTotal2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTaxTotal2 = temp_var;
        }
        else
        {
            temp_struct.POMTaxTotal2 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTax2OnTax1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTax2OnTax1 = temp_var;
        }
        else
        {
            temp_struct.POMTax2OnTax1 = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTotalCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTotalCost = temp_var;
        }
        else
        {
            temp_struct.POMTotalCost = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTotalTax"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMTotalTax = temp_var;
        }
        else
        {
            temp_struct.POMTotalTax = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSubTotal"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMSubTotal = temp_var;
        }
        else
        {
            temp_struct.POMSubTotal = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMCURID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMCURID = temp_var;
        }
        else
        {
            temp_struct.POMCURID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMShipMethod"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMShipMethod = temp_var;
        }
        else
        {
            temp_struct.POMShipMethod = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMCurExRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMCurExRate = temp_var;
        }
        else
        {
            temp_struct.POMCurExRate = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMDateReqDate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POMDateReqDate = temp_var;
        }
        else
        {
            temp_struct.POMDateReqDate = _T("");
        }

		m_dataset_purchaseorder.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();

    for(int i = 0 ; i < (int)m_dataset_purchaseorder.size(); i++)
    {
        strSql.Format(_T("Select * from qrySU  Where SUSupplier = '%s' "), m_dataset_purchaseorder.at(i).POMSupplier);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        while(!m_database_operator.m_pRecordset->EndOfFile)
        {
            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUPhone1"));

            if(temp_var.vt != VT_NULL)
            {
				m_dataset_purchaseorder.at(i).POMSupplier_Phone = temp_var;
            }

            //  POMAddress
            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAddress"));

            if(temp_var.vt != VT_NULL)
            {
				m_dataset_purchaseorder.at(i).POMAddress = temp_var;
            }

            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUAccount"));

            if(temp_var.vt != VT_NULL)
            {
				m_dataset_purchaseorder.at(i).POMAccount = temp_var;
            }

            m_database_operator.m_pRecordset->MoveNext();
        }
    }
	m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

void Table_PN::Search_PO_Part()
{
    PO_Part_Struct temp_struct;
    CString  strTemp;
    /* int POID;
     int POPOMID;
     int POLNKID;*/
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PO Where POPOMID = %d  Order By POItem"), m_POMID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_ppo .clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POID = temp_var;
        }
        else
        {
            temp_struct.POID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POPOMID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POPOMID = temp_var;
        }
        else
        {
            temp_struct.POPOMID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POLNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POLNKID = temp_var;
        }
        else
        {
            temp_struct.POLNKID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POItem"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Item = temp_var;
        }
        else
        {
            temp_struct.Item = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POPart"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PN = temp_var;
        }
        else
        {
            temp_struct.PN = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PODescription"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Descrition = temp_var;
        }
        else
        {
            temp_struct.Descrition = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POPurchUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Buy_As = temp_var;
        }
        else
        {
            temp_struct.Buy_As = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POUseUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Use_As = temp_var;
        }
        else
        {
            temp_struct.Use_As = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POCost = temp_var;
        }
        else
        {
            temp_struct.POCost = 0;
        }





        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Qty = temp_var;
        }
        else
        {
            temp_struct.Qty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POExtension"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.POExtension = temp_var;
        }
        else
        {
            temp_struct.POExtension = 0 ;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POItemQtyReceived"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.RvcdQty = temp_var;
        }
        else
        {
            temp_struct.RvcdQty = 0 ;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POReceived"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.RvcdAll = temp_var;
        }
        else
        {
            temp_struct.RvcdAll = 0 ;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POConvUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.UnitCov = temp_var;
        }
        else
        {
            temp_struct.UnitCov = 1;
        }
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PONOTE"));
        if(temp_var.vt != VT_NULL)
        {
            temp_struct.StrNote = temp_var;
        }
        else
        {
            temp_struct.StrNote =L"";
        }
        m_dataset_ppo.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }


    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();



}

void Table_PN::Insert_PO_Part(PO_Part_Struct ppstruct)
{
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PO Where POPOMID = %d  Order By POItem"), ppstruct.POPOMID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    m_database_operator.m_pRecordset->AddNew();

    m_database_operator.m_pRecordset->PutCollect("POPOMID", (_variant_t)ppstruct.POPOMID);
    m_database_operator.m_pRecordset->PutCollect("POLNKID", (_variant_t)ppstruct.POLNKID);
    m_database_operator.m_pRecordset->PutCollect("POItem", (_variant_t)ppstruct.Item);
    m_database_operator.m_pRecordset->PutCollect("POPart", (_variant_t)ppstruct.PN);
    m_database_operator.m_pRecordset->PutCollect("POIHPart", (_variant_t)ppstruct.PN);
    m_database_operator.m_pRecordset->PutCollect("PODescription", (_variant_t)ppstruct.Descrition);

    m_database_operator.m_pRecordset->PutCollect("POPurchUnits", (_variant_t)ppstruct.Buy_As);
    m_database_operator.m_pRecordset->PutCollect("POCost", (_variant_t)ppstruct.POCost);
    m_database_operator.m_pRecordset->PutCollect("POQty", (_variant_t)ppstruct.Qty);
    m_database_operator.m_pRecordset->PutCollect("POExtension", (_variant_t)ppstruct.POExtension);
    m_database_operator.m_pRecordset->PutCollect("POUseUnits", (_variant_t)ppstruct.Use_As);
    m_database_operator.m_pRecordset->PutCollect("POConvUnits", (_variant_t)ppstruct.UnitCov);
    m_database_operator.m_pRecordset->PutCollect("PONOTE", (_variant_t)ppstruct.StrNote);
    m_database_operator.m_pRecordset->Update();



}
void Table_PN::Update_PO_Part(PO_Part_Struct ppstruct)
{
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from PO Where POID = %d "), ppstruct.POID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    if(!m_database_operator.m_pRecordset->EndOfFile)
    {
        m_database_operator.m_pRecordset->PutCollect("POCost", (_variant_t)ppstruct.POCost);
        m_database_operator.m_pRecordset->PutCollect("POQty", (_variant_t)ppstruct.Qty);
        m_database_operator.m_pRecordset->PutCollect("POItemQtyReceived", (_variant_t)ppstruct.RvcdQty);
        m_database_operator.m_pRecordset->PutCollect("POExtension", (_variant_t)ppstruct.POExtension);
        m_database_operator.m_pRecordset->PutCollect("POReceived", (_variant_t)ppstruct.RvcdAll);

        m_database_operator.m_pRecordset->Update();
    }



    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();


}


CString Table_PN::GetUnitName_ByID(int UNID)
{
    CString  strTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from UN where UNID = %d"), UNID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

    if(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNUseUnits"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
    return strTemp;
}

BOOL Table_PN::Insert_PL(BOM_PartList PLItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from PL Where PLListID = %d AND PLPartID = %d  "), PLItem.PLListID, PLItem.PLPartID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
        {
            m_database_operator.m_pRecordset->AddNew();
            m_database_operator.m_pRecordset->PutCollect("PLListID", (_variant_t)PLItem.PLListID);
            m_database_operator.m_pRecordset->PutCollect("PLPartID", (_variant_t)PLItem.PLPartID);
            m_database_operator.m_pRecordset->PutCollect("PLItem", (_variant_t)PLItem.PLItem);
            m_database_operator.m_pRecordset->PutCollect("PLQty", (_variant_t)PLItem.PLQty);

            if(!PLItem.PLRefMemo.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("PLRefMemo", (_variant_t)PLItem.PLRefMemo);
            }

            m_database_operator.m_pRecordset->Update();
        }
		else
		{
			m_database_operator.m_pRecordset->PutCollect("PLListID", (_variant_t)PLItem.PLListID);
			m_database_operator.m_pRecordset->PutCollect("PLPartID", (_variant_t)PLItem.PLPartID);
			m_database_operator.m_pRecordset->PutCollect("PLItem", (_variant_t)PLItem.PLItem);
			m_database_operator.m_pRecordset->PutCollect("PLQty", (_variant_t)PLItem.PLQty);

			if(!PLItem.PLRefMemo.IsEmpty())
			{
				m_database_operator.m_pRecordset->PutCollect("PLRefMemo", (_variant_t)PLItem.PLRefMemo);
			}

			m_database_operator.m_pRecordset->Update();
		}

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Update_PL(BOM_PartList PLItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from PL Where PLID = %d "), PLItem.PLID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {
            m_database_operator.m_pRecordset->PutCollect("PLQty", (_variant_t)PLItem.PLQty);
            m_database_operator.m_pRecordset->Update();
        }


        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Delete_PL(BOM_PartList PLItem)
{
    try
    {
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

        CString strSql;

        strSql.Format(_T("Delete   from PL where PLID = %d"), PLItem.PLID);
        // m_database_operator.m_pRecordset = m_database_operator.OpenRecordset (strSql);


        m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

        // m_database_operator.OpenRecordset(strSql);
        //  m_database_operator.CloseRecordset();
        //if (m_database_operator.GetRecordCount (m_database_operator.m_pRecordset)<=0)
        //{
        //  return FALSE;
        //}
        //  try
        //  {
        //      // 假设删除第二条记录
        //      m_database_operator.m_pRecordset->MoveFirst();
        //      m_database_operator.m_pRecordset->Move(1);        // 从0开始
        //      m_database_operator.m_pRecordset->Delete(adAffectCurrent);  // 参数adAffectCurrent为删除当前记录
        //      m_database_operator.m_pRecordset->Update();
        //  }
        //  catch(_com_error *e)
        //  {
        //      AfxMessageBox(e->ErrorMessage());
        //  }

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

BOOL Table_PN::SearchVendors_BasedOnItem(int PNID)
{
    Vendor_Information_BasedOn_Part temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select PNID,LNKID,SUID,LNKUNID,SUSupplier,LNKVendorDesc,LNKLeadtime,\
        LNKVendorPN,UNPurchUnits,LNKAtQty,LNKCurrentCost,LNKROHSNote,LNKUse \
        from qryItemsAndAnySources         \
        where PNID = %d order by LNKID"), PNID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_VendorInfor_Part.clear();

    //PLID
    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKID = temp_var;
        }
        else
        {
            temp_struct.LNKID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKUse"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Primary = temp_var;
        }
        else
        {
            temp_struct.Primary  = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUID = temp_var;
        }
        else
        {
            temp_struct.SUID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKUNID = temp_var;
        }
        else
        {
            temp_struct.LNKUNID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorName = temp_var;
        }
        else
        {
            temp_struct.VendorName = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_Description = temp_var;
        }
        else
        {
            temp_struct.Vendor_Description = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorPN = temp_var;
        }
        else
        {
            temp_struct.VendorPN = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNPurchUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.BuyAs = temp_var;
        }
        else
        {
            temp_struct.BuyAs = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        float costValue = _wtof(strTemp);
        temp_struct.Cost = costValue;


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKAtQty"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }


        temp_struct.AtLevel  = _wtoi(strTemp);

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKROHSNote"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Notes = temp_var;
        }
        else
        {
            temp_struct.Notes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKLeadtime"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LeadTime = temp_var;
        }
        else
        {
            temp_struct.LeadTime = _T("");
        }

        m_dataset_VendorInfor_Part.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

    return TRUE;
}
BOOL Table_PN::SearchVendorPrice_BaseOnItem(int PNID)
{

    Vendor_Information_BasedOn_Part temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select PNID,LNKID,SUID,LNKUNID,SUSupplier,LNKVendorDesc,LNKLeadtime,\
                     LNKVendorPN,UNPurchUnits,LNKAtQty,LNKCurrentCost,LNKROHSNote,LNKUse \
                     from qryItemsAndAnySources         \
                     where PNID = %d and LNKUse = 1 order by LNKID"), PNID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_VendorPrice_Part.clear();

    //PLID
    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKID = temp_var;
        }
        else
        {
            temp_struct.LNKID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKUse"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Primary = temp_var;
        }
        else
        {
            temp_struct.Primary  = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.SUID = temp_var;
        }
        else
        {
            temp_struct.SUID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKUNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LNKUNID = temp_var;
        }
        else
        {
            temp_struct.LNKUNID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUSupplier"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorName = temp_var;
        }
        else
        {
            temp_struct.VendorName = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorDesc"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Vendor_Description = temp_var;
        }
        else
        {
            temp_struct.Vendor_Description = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKVendorPN"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.VendorPN = temp_var;
        }
        else
        {
            temp_struct.VendorPN = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNPurchUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.BuyAs = temp_var;
        }
        else
        {
            temp_struct.BuyAs = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKCurrentCost"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }

        float costValue = _wtof(strTemp);
        temp_struct.Cost = costValue;


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKAtQty"));

        if(temp_var.vt != VT_NULL)
        {
            strTemp = temp_var;
        }
        else
        {
            strTemp = _T("");
        }


        temp_struct.AtLevel  = _wtoi(strTemp);

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKROHSNote"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.Notes = temp_var;
        }
        else
        {
            temp_struct.Notes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("LNKLeadtime"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LeadTime = temp_var;
        }
        else
        {
            temp_struct.LeadTime = _T("");
        }

        m_dataset_VendorPrice_Part.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

    return TRUE;
}
BOOL Table_PN::Check_Vendor(int PNID)
{
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;
	strSql.Format(_T("Select SUSupplier\
        from qryItemsAndAnySources         \
        where PNID = %d order by LNKID"), PNID);
	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	if (!m_database_operator.m_pRecordset->EndOfFile)
	{

		m_database_operator.CloseRecordset();
		return TRUE;
	}
	return FALSE;

}
BOOL Table_PN::Check_Ordered(int PNID)
{
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;
	strSql.Format(_T("Select POPart\
        from [TemcoPartsVendors_Default_v1].[dbo].[qryPO]        \
        where LNKPNID = %d "), PNID);
	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	if (!m_database_operator.m_pRecordset->EndOfFile)
	{

		m_database_operator.CloseRecordset();
		return TRUE;
	}
	return FALSE;

}
BOOL Table_PN::Insert_LNK(Vendor_Information_BasedOn_Part LNK)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from LNK Where LNKSUID = %d  AND LNKPNID = %d "), LNK.SUID, LNK.PNID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile)
        {
            m_database_operator.m_pRecordset->AddNew();

            m_database_operator.m_pRecordset->PutCollect("LNKSUID", (_variant_t)LNK.SUID);
            m_database_operator.m_pRecordset->PutCollect("LNKPNID", (_variant_t)LNK.PNID);

            m_database_operator.m_pRecordset->Update();
        }

        //         else
        //         {
        //             m_database_operator.m_pRecordset->PutCollect ("PLQty",(_variant_t)PLItem.PLQty);
        //             m_database_operator.m_pRecordset->Update ();
        //         }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Update_LNK(Vendor_Information_BasedOn_Part LNK)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from LNK Where LNKID = %d "), LNK.LNKID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {
           /* if(LNK.Primary != 0)
            {
                m_database_operator.m_pRecordset->PutCollect("LNKUse", 1);
            }
            else
            {
                m_database_operator.m_pRecordset->PutCollect("LNKUse", 0);
            }

            if(!LNK.LeadTime.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("LNKLeadtime", (_variant_t)LNK.LeadTime);
            }

            if(!LNK.VendorPN.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("LNKVendorPN", (_variant_t)LNK.VendorPN);
            }

            m_database_operator.m_pRecordset->PutCollect("LNKUNID", (_variant_t)LNK.LNKUNID);


            if(!LNK.Vendor_Description.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("LNKVendorDesc", (_variant_t)LNK.Vendor_Description);
            }


             


            m_database_operator.m_pRecordset->PutCollect("LNKAtQty", (_variant_t)LNK.AtLevel);
            m_database_operator.m_pRecordset->PutCollect("LNKCurrentCost", (_variant_t)LNK.Cost);

            if(!LNK.Notes.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("LNKRoHSNote", (_variant_t)LNK.Notes);
            }



            m_database_operator.m_pRecordset->Update();*/

			CString StrSql;
            if (LNK.LNKUNID==0)
            {
                LNK.LNKUNID = 1;
            }
			StrSql.Format(_T("Update LNK Set LNKUse=%d,LNKLeadtime='%s',LNKUNID=%d,LNKVendorDesc='%s',LNKCurrentCost=%.2f,LNKRoHSNote='%s' Where LNKID = %d"),LNK.Primary,LNK.LeadTime,LNK.LNKUNID,LNK.Vendor_Description,LNK.Cost,LNK.Notes,LNK.LNKID);
            m_database_operator.m_pConnection->Execute(StrSql.GetString(),NULL,adCmdText);
		}


        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Delete_LNK(Vendor_Information_BasedOn_Part LNK)
{
    try
    {
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Delete  from LNK where LNKID = %d"), LNK.LNKID);
        m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

BOOL Table_PN::Search_Cost_LNK(int LNKID)
{
    Cost_Struct temp_struct;
    CString strTemp;
    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * From COST Where COSTLNKID =%d "), LNKID);
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_Cost.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.COSTID = temp_var;
        }
        else
        {
            temp_struct.COSTID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTLNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.COSTLNKID = temp_var;
        }
        else
        {
            temp_struct.COSTLNKID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTLNKID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.COSTLNKID = temp_var;
        }
        else
        {
            temp_struct.COSTLNKID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTAtQty"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.COSTAtQty = temp_var;
        }
        else
        {
            temp_struct.COSTAtQty = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTLeadtime"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.LeadTime = temp_var;
        }
        else
        {
            temp_struct.LeadTime = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("COSTCost"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.COSTCost = temp_var;
        }
        else
        {
            temp_struct.COSTCost = 0;
        }

        m_dataset_Cost.push_back(temp_struct);

        m_database_operator.m_pRecordset->MoveNext() ;


    }


    return FALSE;
}

BOOL Table_PN::Insert_Cost(Cost_Struct cost)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("INSERT INTO COST(COSTLNKID,COSTAtQty,COSTLeadtime,COSTCost) Values(%d,%f,%d,%f)"), cost.COSTLNKID, cost.COSTAtQty, cost.LeadTime, cost.COSTCost);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Update_Cost(Cost_Struct cost)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("update COST set COSTAtQty = %f,COSTLeadtime=%d,COSTCost=%f  Where COSTID=%d"), cost.COSTAtQty, cost.LeadTime, cost.COSTCost, cost.COSTID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Delete_Cost(Cost_Struct cost)
{
    try
    {
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Delete   from COST where COSTID = %d"), cost.COSTID);
        m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

void Table_PN::Initial_UN()
{
    UN_Struct temp_struct;
    CString  strTemp;

    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from UN Order By UNID"));
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_UN.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.UNID = temp_var;
        }
        else
        {
            temp_struct.UNID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNUseUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.UNUseUnits = temp_var;
        }
        else
        {
            temp_struct.UNUseUnits = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNPurchUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.UNPurchUnits = temp_var;
        }
        else
        {
            temp_struct.UNPurchUnits = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UNConvUnits"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.UNConvUnits = temp_var;
        }
        else
        {
            temp_struct.UNConvUnits = 0;
        }


        m_dataset_UN.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();
}

BOOL Table_PN::Insert_UN(UN_Struct unit)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("INSERT INTO UN(UNUseUnits,UNPurchUnits,UNConvUnits) Values('%s','%s',%d)"), unit.UNUseUnits, unit.UNPurchUnits, unit.UNConvUnits);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Update_UN(UN_Struct unit)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from UN  Where UNID = %d"), unit.UNID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {
            // m_database_operator.m_pRecordset->AddNew();

            //m_database_operator.m_pRecordset->PutCollect("UNUseUnits", (_variant_t)LNK.SUID);
            //m_database_operator.m_pRecordset->PutCollect("LNKPNID", (_variant_t)LNK.PNID);
            if(!unit.UNUseUnits.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("UNUseUnits", (_variant_t)unit.UNUseUnits);
            }

            if(!unit.UNPurchUnits.IsEmpty())
            {
                m_database_operator.m_pRecordset->PutCollect("UNPurchUnits", (_variant_t)unit.UNPurchUnits);
            }

            m_database_operator.m_pRecordset->PutCollect("UNConvUnits", (_variant_t)unit.UNConvUnits);
            m_database_operator.m_pRecordset->Update();
        }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Delete_UN(UN_Struct unit)
{
    try
    {
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Delete  *  from UN where UNID = %d "), unit.UNID);
        m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

int Table_PN::Check_UN(UN_Struct unit)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        BOOL Flag = FALSE;
        strSql.Format(_T("Select * from LNK  Where LNKUNID = %d"), unit.UNID);
        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(!m_database_operator.m_pRecordset->EndOfFile)
        {
            Flag = TRUE;
        }
        else
        {
            Flag = FALSE;
        }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return Flag;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

BOOL Table_PN::Insert_Vendor(SU_Struct VItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

        CString strSql;


        strSql.Format(_T("Select * from SU Where SUSupplier = '%s'"), VItem.SUSupplier);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
        {
            m_database_operator.m_pRecordset->AddNew();

            if(!VItem.SUSupplier.IsEmpty())
            {
                temp_var = VItem.SUSupplier;
                m_database_operator.m_pRecordset->PutCollect("SUSupplier", temp_var);
            }

            if(!VItem.SUAddress.IsEmpty())
            {
                temp_var = VItem.SUAddress;
                m_database_operator.m_pRecordset->PutCollect("SUAddress", temp_var);
            }

            if(!VItem.SUCountry.IsEmpty())
            {
                temp_var = VItem.SUCountry;

                m_database_operator.m_pRecordset->PutCollect("SUCountry", temp_var);
            }



            if(!VItem.SUPhone1.IsEmpty())
            {
                temp_var = VItem.SUPhone1;
                m_database_operator.m_pRecordset->PutCollect("SUPhone1", temp_var);
            }

            if(!VItem.SUPhone2.IsEmpty())
            {
                temp_var = VItem.SUPhone2;
                m_database_operator.m_pRecordset->PutCollect("SUPhone2", temp_var);
            }


            if(!VItem.SUFAX.IsEmpty())
            {
                temp_var = VItem.SUFAX;
                m_database_operator.m_pRecordset->PutCollect("SUFAX", temp_var);
            }

            if(!VItem.SUWeb.IsEmpty())
            {

                temp_var = VItem.SUWeb;
                m_database_operator.m_pRecordset->PutCollect("SUWeb", temp_var);
            }


            if(!VItem.SUContact1.IsEmpty())
            {
                temp_var = VItem.SUContact1;
                m_database_operator.m_pRecordset->PutCollect("SUContact1", temp_var);
            }

            if(!VItem.SUContact2.IsEmpty())
            {
                temp_var = VItem.SUContact2;
                m_database_operator.m_pRecordset->PutCollect("SUContact2", temp_var);
            }

            if(!VItem.SUDateLast.IsEmpty())
            {
                temp_var = VItem.SUDateLast;
                m_database_operator.m_pRecordset->PutCollect("SUDateLast", temp_var);
            }



            if(!VItem.SUDateLast.IsEmpty())
            {
                temp_var = VItem.SUDateLast;
                m_database_operator.m_pRecordset->PutCollect("SUNotes", temp_var);
            }

            if(!VItem.SUCode.IsEmpty())
            {
                temp_var = VItem.SUCode;
                m_database_operator.m_pRecordset->PutCollect("SUCode", temp_var);
            }

            if(!VItem.SUAccount.IsEmpty())
            {
                temp_var = VItem.SUAccount;
                m_database_operator.m_pRecordset->PutCollect("SUAccount", temp_var);
            }

            if(!VItem.SUTerms.IsEmpty())
            {
                temp_var = VItem.SUTerms;
                m_database_operator.m_pRecordset->PutCollect("SUTerms", temp_var);
            }

            if(!VItem.SUFedTaxID.IsEmpty())
            {
                temp_var = VItem.SUFedTaxID;
                m_database_operator.m_pRecordset->PutCollect("SUFedTaxID", temp_var);
            }

            if(!VItem.SUStateTaxID.IsEmpty())
            {
                temp_var = VItem.SUStateTaxID;
                m_database_operator.m_pRecordset->PutCollect("SUStateTaxID", temp_var);
            }

            if(!VItem.SUEMail1.IsEmpty())
            {
                temp_var = VItem.SUEMail1;
                m_database_operator.m_pRecordset->PutCollect("SUEMail1", temp_var);
            }

            if(!VItem.SUEMail2.IsEmpty())
            {
                temp_var = VItem.SUEMail2;
                m_database_operator.m_pRecordset->PutCollect("SUEMail2", temp_var);
            }

            if(VItem.SUCURID != -1)
            {
                temp_var = VItem.SUCURID;
                m_database_operator.m_pRecordset->PutCollect("SUCURID", temp_var);
            }

            m_database_operator.m_pRecordset->Update();


        }
        else
        {
            m_database_operator.CloseRecordset();
            //m_database_operator.CloseConn();
            return FALSE ;

        }

        m_database_operator.CloseRecordset();
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }

}

BOOL Table_PN::Update_Vendor(SU_Struct VItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

        CString strSql;


        strSql.Format(_T("Select * from SU Where SUID = %d "), VItem.SUID);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile == VARIANT_FALSE)
        {

            if(!VItem.SUSupplier.IsEmpty())
            {
                temp_var = VItem.SUSupplier;
                m_database_operator.m_pRecordset->PutCollect("SUSupplier", temp_var);
            }

            if(!VItem.SUAddress.IsEmpty())
            {
                temp_var = VItem.SUAddress;
                m_database_operator.m_pRecordset->PutCollect("SUAddress", temp_var);
            }

            if(!VItem.SUCountry.IsEmpty())
            {
                temp_var = VItem.SUCountry;

                m_database_operator.m_pRecordset->PutCollect("SUCountry", temp_var);
            }



            if(!VItem.SUPhone1.IsEmpty())
            {
                temp_var = VItem.SUPhone1;
                m_database_operator.m_pRecordset->PutCollect("SUPhone1", temp_var);
            }

            if(!VItem.SUPhone2.IsEmpty())
            {
                temp_var = VItem.SUPhone2;
                m_database_operator.m_pRecordset->PutCollect("SUPhone2", temp_var);
            }


            if(!VItem.SUFAX.IsEmpty())
            {
                temp_var = VItem.SUFAX;
                m_database_operator.m_pRecordset->PutCollect("SUFAX", temp_var);
            }

            if(!VItem.SUWeb.IsEmpty())
            {

                temp_var = VItem.SUWeb;
                m_database_operator.m_pRecordset->PutCollect("SUWeb", temp_var);
            }


            if(!VItem.SUContact1.IsEmpty())
            {
                temp_var = VItem.SUContact1;
                m_database_operator.m_pRecordset->PutCollect("SUContact1", temp_var);
            }

            if(!VItem.SUContact2.IsEmpty())
            {
                temp_var = VItem.SUContact2;
                m_database_operator.m_pRecordset->PutCollect("SUContact2", temp_var);
            }

            if(!VItem.SUDateLast.IsEmpty())
            {
                temp_var = VItem.SUDateLast;
                m_database_operator.m_pRecordset->PutCollect("SUDateLast", temp_var);
            }



            if(!VItem.SUDateLast.IsEmpty())
            {
                temp_var = VItem.SUDateLast;
                m_database_operator.m_pRecordset->PutCollect("SUNotes", temp_var);
            }

            if(!VItem.SUCode.IsEmpty())
            {
                temp_var = VItem.SUCode;
                m_database_operator.m_pRecordset->PutCollect("SUCode", temp_var);
            }

            if(!VItem.SUAccount.IsEmpty())
            {
                temp_var = VItem.SUAccount;
                m_database_operator.m_pRecordset->PutCollect("SUAccount", temp_var);
            }

            if(!VItem.SUTerms.IsEmpty())
            {
                temp_var = VItem.SUTerms;
                m_database_operator.m_pRecordset->PutCollect("SUTerms", temp_var);
            }

            if(!VItem.SUFedTaxID.IsEmpty())
            {
                temp_var = VItem.SUFedTaxID;
                m_database_operator.m_pRecordset->PutCollect("SUFedTaxID", temp_var);
            }

            if(!VItem.SUStateTaxID.IsEmpty())
            {
                temp_var = VItem.SUStateTaxID;
                m_database_operator.m_pRecordset->PutCollect("SUStateTaxID", temp_var);
            }

            if(!VItem.SUEMail1.IsEmpty())
            {
                temp_var = VItem.SUEMail1;
                m_database_operator.m_pRecordset->PutCollect("SUEMail1", temp_var);
            }

            if(!VItem.SUEMail2.IsEmpty())
            {
                temp_var = VItem.SUEMail2;
                m_database_operator.m_pRecordset->PutCollect("SUEMail2", temp_var);
            }

            if(!VItem.SUNotes.IsEmpty())
            {
                temp_var = VItem.SUNotes;
                m_database_operator.m_pRecordset->PutCollect("SUNotes", temp_var);
            }

            if(VItem.SUCURID != -1)
            {
                temp_var = VItem.SUCURID;
                m_database_operator.m_pRecordset->PutCollect("SUCURID", temp_var);
            }

            m_database_operator.m_pRecordset->Update();

        }
 
        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}

BOOL Table_PN::Delete_Vendor(SU_Struct VItem)
{
    TRY
    {
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
		strSql.Format(_T("Delete from LNK Where LNK.LNKSUID= %d"), VItem.SUID);
		m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
        strSql.Format(_T("Delete   from SU where SUID = %d"), VItem.SUID);
        m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

        //m_database_operator.CloseConn();
        return TRUE;
    }
    CATCH(CMemoryException, e)
    {
        return FALSE;
    }
    END_CATCH
}

CString Table_PN::GetShippingAddress()
{
    CString shipAddress = L"";


    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from ORG  Where ORGPOUseShpgAddr = -1"));
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);


    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("ORGAddress"));

        if(temp_var.vt != VT_NULL)
        {
            shipAddress = temp_var;
        }

        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

    return shipAddress;
}

CString Table_PN::GetImageFileFold()
{
    return m_pv_database_image;
}

BOOL Table_PN::Load_Currency()
{
    CUR_Struct temp_struct;
    CString  strTemp;

    _variant_t temp_var;
    m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql.Format(_T("Select * from CUR Order By CURID"));
    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_Currentcy.clear();

    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURID = temp_var;
        }
        else
        {
            temp_struct.CURID = 0;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURCurrencyName"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURCurrencyName = temp_var;
        }
        else
        {
            temp_struct.CURCurrencyName = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURExchangeRate"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURExchangeRate = temp_var;
        }
        else
        {
            temp_struct.CURExchangeRate = 1;
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURCurrencyChar"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURCurrencyChar = temp_var;
        }
        else
        {
            temp_struct.CURCurrencyChar = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURFormat"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURFormat = temp_var;
        }
        else
        {
            temp_struct.CURFormat = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURFormatExt"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CURFormatExt = temp_var;
        }
        else
        {
            temp_struct.CURFormatExt = L"";
        }

        m_dataset_Currentcy.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

    return TRUE;
}

BOOL Table_PN::Insert_Currency(CUR_Struct CItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

        CString strSql;


        strSql.Format(_T("Select * from CUR Where CURID = %d "), CItem.CURID);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile == VARIANT_FALSE)
        {
            if(!CItem.CURCurrencyName.IsEmpty())
            {
                temp_var = CItem.CURCurrencyName;
                m_database_operator.m_pRecordset->PutCollect("CURCurrencyName", temp_var);
            }
            if(CItem.CURExchangeRate > -1)
            {
                temp_var = CItem.CURExchangeRate;
                m_database_operator.m_pRecordset->PutCollect("CURExchangeRate", temp_var);
            }

            if(!CItem.CURCurrencyChar.IsEmpty())
            {
                temp_var = CItem.CURCurrencyChar;
                m_database_operator.m_pRecordset->PutCollect("CURCurrencyChar", temp_var);
            }

            if(!CItem.CURFormat.IsEmpty())
            {
                temp_var = CItem.CURFormat;
                m_database_operator.m_pRecordset->PutCollect("CURFormat", temp_var);
            }

            if(!CItem.CURFormatExt.IsEmpty())
            {
                temp_var = CItem.CURFormatExt;
                m_database_operator.m_pRecordset->PutCollect("CURFormatExt", temp_var);
            }


            m_database_operator.m_pRecordset->Update();

        }

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Update_Currency(CUR_Struct CItem)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
        CString strSql;
        strSql.Format(_T("Select * from CUR Where CURID = %d "), CItem.CURID);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if(m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
        {
            if(!CItem.CURCurrencyName.IsEmpty())
            {
                temp_var = CItem.CURCurrencyName;
                m_database_operator.m_pRecordset->PutCollect("CURCurrencyName", temp_var);
            }
            if(CItem.CURExchangeRate > -1)
            {
                temp_var = CItem.CURExchangeRate;
                m_database_operator.m_pRecordset->PutCollect("CURExchangeRate", temp_var);
            }

            if(!CItem.CURCurrencyChar.IsEmpty())
            {
                temp_var = CItem.CURCurrencyChar;
                m_database_operator.m_pRecordset->PutCollect("CURCurrencyChar", temp_var);
            }

            if(!CItem.CURFormat.IsEmpty())
            {
                temp_var = CItem.CURFormat;
                m_database_operator.m_pRecordset->PutCollect("CURFormat", temp_var);
            }

            if(!CItem.CURFormatExt.IsEmpty())
            {
                temp_var = CItem.CURFormatExt;
                m_database_operator.m_pRecordset->PutCollect("CURFormatExt", temp_var);
            }


            m_database_operator.m_pRecordset->Update();

        }

        //m_database_operator.CloseConn();
        return TRUE;
    }
    catch(CException* e)
    {
        return FALSE;
    }
}
BOOL Table_PN::Delete_Currency(CUR_Struct CItem)
{
	return FALSE;
}

BOOL Table_PN::Search_Customers(CString CustomerName)
{

   CU_Struct temp_struct;
    CString  strTemp;
    _variant_t temp_var;
    //m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
    CString strSql;
    strSql = _T("Select *\
                     from qryCustomer         \
                     Where (CUCustomer LIKE '%") +
             CustomerName +
             _T("%')");

    m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
    m_dataset_Customer.clear();

    //PLID
    while(!m_database_operator.m_pRecordset->EndOfFile)
    {
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUID"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUID = temp_var;
        }
        else
        {
            temp_struct.CUID = 0;
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUCustomer"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUCustomer = temp_var;
        }
        else
        {
            temp_struct.CUCustomer = L"";
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUAddress"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUAddress = temp_var;
        }
        else
        {
            temp_struct.CUAddress = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUShipAddress"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUShipAddress = temp_var;
        }
        else
        {
            temp_struct.CUShipAddress = L"";
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUPhone1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUPhone1 = temp_var;
        }
        else
        {
            temp_struct.CUPhone1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUPhone2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUPhone2 = temp_var;
        }
        else
        {
            temp_struct.CUPhone2 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUContact1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUContact1 = temp_var;
        }
        else
        {
            temp_struct.CUContact1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUContact2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUContact2 = temp_var;
        }
        else
        {
            temp_struct.CUContact2 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUFax"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUFax = temp_var;
        }
        else
        {
            temp_struct.CUFax = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUEmail1"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUEmail1 = temp_var;
        }
        else
        {
            temp_struct.CUEmail1 = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUEmail2"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUEmail2 = temp_var;
        }
        else
        {
            temp_struct.CUEmail2 = _T("");
        }


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUNotes"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUNotes = temp_var;
        }
        else
        {
            temp_struct.CUNotes = _T("");
        }

        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUWeb"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.CUWeb = temp_var;
		}
		else
		{
			temp_struct.CUWeb = _T("");
		}

       
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUCode"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.CUCode = temp_var;
		}
		else
		{
			temp_struct.CUCode = _T("");
		}


        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUTerms"));

        if(temp_var.vt != VT_NULL)
        {
            temp_struct.CUTerms = temp_var;
        }
        else
        {
            temp_struct.CUTerms = _T("");
        }
 
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUFedTaxID"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.CUFedTaxID = temp_var;
		}
		else
		{
			temp_struct.CUFedTaxID = _T("");
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CUStateTaxID"));

		if(temp_var.vt != VT_NULL)
		{
			temp_struct.CUStateTaxID = temp_var;
		}
		else
		{
			temp_struct.CUStateTaxID = _T("");
		}
	 

        m_dataset_Customer.push_back(temp_struct);
        m_database_operator.m_pRecordset->MoveNext();
    }

    m_database_operator.CloseRecordset();
    //m_database_operator.CloseConn();

	return TRUE;
}
BOOL Table_PN::Insert_CU(CU_Struct cu)
{
	try
	{
		_variant_t temp_var;
		m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

		CString strSql;


		strSql.Format(_T("Select * from CU Where CUCustomer = '%s' "), cu.CUCustomer);

		m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
		int recordcount = m_database_operator.GetRecordCount(m_database_operator.m_pRecordset);
		if(recordcount < 0)
		{
			if(!cu.CUCustomer.IsEmpty())
			{
				temp_var = cu.CUCustomer;
				m_database_operator.m_pRecordset->PutCollect("CUCustomer", temp_var);
			}
			if(!cu.CUAddress.IsEmpty())
			{
				temp_var = cu.CUAddress;
				m_database_operator.m_pRecordset->PutCollect("CUAddress", temp_var);
			}
			if(!cu.CUShipAddress.IsEmpty())
			{
				temp_var = cu.CUShipAddress;
				m_database_operator.m_pRecordset->PutCollect("CUShipAddress", temp_var);
			}
			if(!cu.CUPhone1.IsEmpty())
			{
				temp_var = cu.CUPhone1;
				m_database_operator.m_pRecordset->PutCollect("CUPhone1", temp_var);
			}
			if(!cu.CUPhone2.IsEmpty())
			{
				temp_var = cu.CUPhone2;
				m_database_operator.m_pRecordset->PutCollect("CUPhone2", temp_var);
			}
			if(!cu.CUContact1.IsEmpty())
			{
				temp_var = cu.CUContact1;
				m_database_operator.m_pRecordset->PutCollect("CUContact1", temp_var);
			}
			if(!cu.CUContact2.IsEmpty())
			{
				temp_var = cu.CUContact2;
				m_database_operator.m_pRecordset->PutCollect("CUContact2", temp_var);
			}
			if(!cu.CUFax.IsEmpty())
			{
				temp_var = cu.CUFax;
				m_database_operator.m_pRecordset->PutCollect("CUFax", temp_var);
			}
			if(!cu.CUEmail1.IsEmpty())
			{
				temp_var = cu.CUEmail1;
				m_database_operator.m_pRecordset->PutCollect("CUEmail1", temp_var);
			}
			if(!cu.CUEmail2.IsEmpty())
			{
				temp_var = cu.CUEmail2;
				m_database_operator.m_pRecordset->PutCollect("CUEmail2", temp_var);
			}
			if(!cu.CUNotes.IsEmpty())
			{
				temp_var = cu.CUNotes;
				m_database_operator.m_pRecordset->PutCollect("CUNotes", temp_var);
			}
			if(!cu.CUWeb.IsEmpty())
			{
				temp_var = cu.CUCustomer;
				m_database_operator.m_pRecordset->PutCollect("CUWeb", temp_var);
			}
			if(!cu.CUCode.IsEmpty())
			{
				temp_var = cu.CUCode;
				m_database_operator.m_pRecordset->PutCollect("CUCode", temp_var);
			}
			if(!cu.CUAccount.IsEmpty())
			{
				temp_var = cu.CUAccount;
				m_database_operator.m_pRecordset->PutCollect("CUAccount", temp_var);
			}
			if(!cu.CUTerms.IsEmpty())
			{
				temp_var = cu.CUTerms;
				m_database_operator.m_pRecordset->PutCollect("CUTerms", temp_var);
			}
			if(!cu.CUFedTaxID.IsEmpty())
			{
				temp_var = cu.CUFedTaxID;
				m_database_operator.m_pRecordset->PutCollect("CUFedTaxID", temp_var);
			}
			if(!cu.CUStateTaxID.IsEmpty())
			{
				temp_var = cu.CUStateTaxID;
				m_database_operator.m_pRecordset->PutCollect("CUStateTaxID", temp_var);
			}
			 

			m_database_operator.m_pRecordset->Update();

		}
		else
		{
		  //m_database_operator.CloseConn();
		  return FALSE;
		}
		//m_database_operator.CloseConn();
		return TRUE;
	}
	catch(CException* e)
	{
		return FALSE;
	}

}
BOOL Table_PN::Delete_CU(CU_Struct cu)
{
  
  return FALSE;

}
BOOL Table_PN::Update_CU(CU_Struct cu)
{

	try
	{
		_variant_t temp_var;
		m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);

		CString strSql;


		strSql.Format(_T("Select * from CU Where CUID = %d "), cu.CUID);

		m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
		int recordcount = m_database_operator.GetRecordCount(m_database_operator.m_pRecordset);
		if(recordcount>0)
		{
			if(!cu.CUCustomer.IsEmpty())
			{
				temp_var = cu.CUCustomer;
				m_database_operator.m_pRecordset->PutCollect("CUCustomer", temp_var);
			}
			if(!cu.CUAddress.IsEmpty())
			{
				temp_var = cu.CUAddress;
				m_database_operator.m_pRecordset->PutCollect("CUAddress", temp_var);
			}
			if(!cu.CUShipAddress.IsEmpty())
			{
				temp_var = cu.CUShipAddress;
				m_database_operator.m_pRecordset->PutCollect("CUShipAddress", temp_var);
			}
			if(!cu.CUPhone1.IsEmpty())
			{
				temp_var = cu.CUPhone1;
				m_database_operator.m_pRecordset->PutCollect("CUPhone1", temp_var);
			}
			if(!cu.CUPhone2.IsEmpty())
			{
				temp_var = cu.CUPhone2;
				m_database_operator.m_pRecordset->PutCollect("CUPhone2", temp_var);
			}
			if(!cu.CUContact1.IsEmpty())
			{
				temp_var = cu.CUContact1;
				m_database_operator.m_pRecordset->PutCollect("CUContact1", temp_var);
			}
			if(!cu.CUContact2.IsEmpty())
			{
				temp_var = cu.CUContact2;
				m_database_operator.m_pRecordset->PutCollect("CUContact2", temp_var);
			}
			if(!cu.CUFax.IsEmpty())
			{
				temp_var = cu.CUFax;
				m_database_operator.m_pRecordset->PutCollect("CUFax", temp_var);
			}
			if(!cu.CUEmail1.IsEmpty())
			{
				temp_var = cu.CUEmail1;
				m_database_operator.m_pRecordset->PutCollect("CUEmail1", temp_var);
			}
			if(!cu.CUEmail2.IsEmpty())
			{
				temp_var = cu.CUEmail2;
				m_database_operator.m_pRecordset->PutCollect("CUEmail2", temp_var);
			}
			if(!cu.CUNotes.IsEmpty())
			{
				temp_var = cu.CUNotes;
				m_database_operator.m_pRecordset->PutCollect("CUNotes", temp_var);
			}
			if(!cu.CUWeb.IsEmpty())
			{
				temp_var = cu.CUCustomer;
				m_database_operator.m_pRecordset->PutCollect("CUWeb", temp_var);
			}
			if(!cu.CUCode.IsEmpty())
			{
				temp_var = cu.CUCode;
				m_database_operator.m_pRecordset->PutCollect("CUCode", temp_var);
			}
			if(!cu.CUAccount.IsEmpty())
			{
				temp_var = cu.CUAccount;
				m_database_operator.m_pRecordset->PutCollect("CUAccount", temp_var);
			}
			if(!cu.CUTerms.IsEmpty())
			{
				temp_var = cu.CUTerms;
				m_database_operator.m_pRecordset->PutCollect("CUTerms", temp_var);
			}
			if(!cu.CUFedTaxID.IsEmpty())
			{
				temp_var = cu.CUFedTaxID;
				m_database_operator.m_pRecordset->PutCollect("CUFedTaxID", temp_var);
			}
			if(!cu.CUStateTaxID.IsEmpty())
			{
				temp_var = cu.CUStateTaxID;
				m_database_operator.m_pRecordset->PutCollect("CUStateTaxID", temp_var);
			}


			m_database_operator.m_pRecordset->Update();

		}
		else
		{
			//m_database_operator.CloseConn();
			return FALSE;
		}
		//m_database_operator.CloseConn();
		return TRUE;
	}
	catch(CException* e)
	{
		return FALSE;
	}
}

void Table_PN::DataSync()
{
	vector<CString> m_springdbtable;
	m_springdbtable.push_back(L"Capacitor");
	m_springdbtable.push_back(L"Connector");
	m_springdbtable.push_back(L"crystal");
	m_springdbtable.push_back(L"Diode_TVS");
	m_springdbtable.push_back(L"FUSE");
	m_springdbtable.push_back(L"IC");
	m_springdbtable.push_back(L"Icons");
	m_springdbtable.push_back(L"Inductor");
	m_springdbtable.push_back(L"Relays_Beeper");
	m_springdbtable.push_back(L"Resistor");
	m_springdbtable.push_back(L"Transistor_MOS");
	CString StrTip;
    CString SpringDBPath;
	TCHAR exeFullPath[MAX_PATH+1]; //
	GetModuleFileName(NULL, exeFullPath, MAX_PATH); //
	(_tcsrchr(exeFullPath, _T('\\')))[1] = 0;//
	g_strDatabasefilepath=exeFullPath;//
	g_strExePth=g_strDatabasefilepath;//
	 CString g_configfile_path = g_strExePth + _T("T3000_config.ini");

	CString strTemp=L"Z:\Designs\Lib\Temco\tecmco_database.mdb";
	GetPrivateProfileString(_T("PVDBSETTING"), _T("SPRINGDB"),strTemp, SpringDBPath.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	SpringDBPath.ReleaseBuffer();

	StrTip.Format(_T("Sync DB = %s"), SpringDBPath);
	OutPutsStatusInfo(StrTip, FALSE, 0);Sleep(30);

	CString SpringDBSql;
	CBADO SpringDB;
	SpringDB.SetDBPath(SpringDBPath);
	SpringDB.OnInitADOConn();
	int AllRecordCout = 0;
	int CurrentRecord = 0;
	int currentpos = 0;
	 
	for (int i = 0;i < m_springdbtable.size();i++)
	{
		SpringDBSql.Format(_T("Select * From %s"),m_springdbtable.at(i));
		SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
		AllRecordCout += SpringDB.GetRecordCount(SpringDB.m_pRecordset);
	}
	StrTip.Format(_T("Need to sync data record = %d"), AllRecordCout);
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
  _variant_t temp_var;


  StrTip.Format(_T("Sync Capacitor Start"));
  OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
  StrTip.Format(_T("-----------------------------"));
  OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	SpringDBSql=L"Select * From Capacitor";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
 
	
 
	//Capacitor
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
	    PN_SpringStruct   temp_struct_Spring;
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_Number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);

		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

		temp_struct_Spring.Catalog = L"Capacitor";
		temp_struct_Spring.Power = L"";
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);

		StrTip.Format(_T("Sync PNumber =  %s"),temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

		SpringDB.m_pRecordset->MoveNext();
		 
	}
	SpringDB.CloseRecordset();


	StrTip.Format(_T("Sync Capacitor End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


	StrTip.Format(_T("Sync Connector Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	SpringDBSql=L"Select * From Connector";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
	     PN_SpringStruct   temp_struct_Spring;
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_Number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

		temp_struct_Spring.Catalog = L"Connector";

		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}

		
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_Type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Allegro_Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);

		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	StrTip.Format(_T("Sync Connector End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync crystal Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	SpringDBSql=L"Select * From crystal";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

		temp_struct_Spring.Catalog = L"Crystal";

		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);

		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();



	StrTip.Format(_T("Sync crystal End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Diode_TVS Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);



	SpringDBSql=L"Select * From Diode_TVS";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

		temp_struct_Spring.Catalog = L"Diode_TVS";

		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);

		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();


	StrTip.Format(_T("Sync Diode_TVS End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync FUSE Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


	SpringDBSql=L"Select * From FUSE";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

temp_struct_Spring.Catalog = L"FUSE";

		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	StrTip.Format(_T("Sync FUSE End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync IC Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


	SpringDBSql=L"Select * From IC";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"IC";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}

		

		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();


	StrTip.Format(_T("Sync IC End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Icons Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


	SpringDBSql=L"Select * From Icons";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Icons";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_Number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



 
			temp_struct_Spring.Power = L"";
	 


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	StrTip.Format(_T("Sync Icons End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Inductor Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


	SpringDBSql=L"Select * From Inductor";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Inductor";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



		 		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		 		if(temp_var.vt != VT_NULL)
		 		{
		 			temp_struct_Spring.Power = temp_var;
		 		}
		 		else
		 		{
		           temp_struct_Spring.Power = L"";
		         }


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	StrTip.Format(_T("Sync Inductor End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Key Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

	SpringDBSql=L"Select * From [Key]";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Key";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();
	 
	StrTip.Format(_T("Sync Key End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Relays_Beeper Start"));Sleep(30);
	OutPutsStatusInfo(StrTip, FALSE, currentpos);


	SpringDBSql=L"Select * From Relays_Beeper";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Relays_Beeper";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	StrTip.Format(_T("Sync Relays_Beeper End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Resistor Start"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);



	SpringDBSql=L"Select * From Resistor";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Resistor";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		 
		 
			temp_struct_Spring.Voltage = L"";
		 
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);

		SyncPNItemFromSpring(temp_struct_Spring);
		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();


	StrTip.Format(_T("Sync Resistor End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("Sync Transistor_MOS Start"));Sleep(30);
	OutPutsStatusInfo(StrTip, FALSE, currentpos);

	SpringDBSql=L"Select * From Transistor_MOS";
	SpringDB.m_pRecordset = SpringDB.OpenRecordset(SpringDBSql);
	while(!SpringDB.m_pRecordset->EndOfFile)
	{
		PN_SpringStruct   temp_struct_Spring;

		temp_struct_Spring.Catalog = L"Transistor_MOS";


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("part_number"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNPartNumber = temp_var;
		}
		else
		{
			temp_struct_Spring.PNPartNumber = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Value"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNTitle = temp_var;
		}
		else
		{
			temp_struct_Spring.PNTitle = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Description"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNDetail = temp_var;
		}
		else
		{
			temp_struct_Spring.PNDetail = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.PNUser3 = temp_var;
			temp_struct_Spring.PNUser3= DealWithFootPrint(temp_struct_Spring.PNUser3);
		}
		else
		{
			temp_struct_Spring.PNUser3 = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Brand_Vendor"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Brand_Vendor = temp_var;
		}
		else
		{
			temp_struct_Spring.Brand_Vendor = L"";
		}



		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Power"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Power = temp_var;
		}
		else
		{
			temp_struct_Spring.Power = L"";
		}


		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Voltage"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Voltage = temp_var;
		}
		else
		{
			temp_struct_Spring.Voltage = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Tolerance"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Tolerance = temp_var;
		}
		else
		{
			temp_struct_Spring.Tolerance = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Part_type"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Part_type = temp_var;
		}
		else
		{
			temp_struct_Spring.Part_type = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Schematic_Part"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Schematic_part = temp_var;
		}
		else
		{
			temp_struct_Spring.Schematic_part = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("allegro_footprint"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Allegro_footprint = temp_var;
		}
		else
		{
			temp_struct_Spring.Allegro_footprint = L"";
		}
		temp_var = SpringDB.m_pRecordset->GetCollect(_T("Solidworks"));
		if(temp_var.vt != VT_NULL)
		{
			temp_struct_Spring.Solidworks = temp_var;
		}
		else
		{
			temp_struct_Spring.Solidworks = L"";
		}

		SyncPNItemFromSpring(temp_struct_Spring);

		StrTip.Format(_T("Sync PNumber =  %s"), temp_struct_Spring.PNPartNumber);
		CurrentRecord++;
		currentpos = (((float)CurrentRecord) / ((float)AllRecordCout)) * 100;
		OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
		SpringDB.m_pRecordset->MoveNext();

	}
	SpringDB.CloseRecordset();

	SpringDB.CloseConn();


	currentpos = 100;

	StrTip.Format(_T("Sync Transistor_MOS End"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);
	StrTip.Format(_T("-----------------------------"));
	OutPutsStatusInfo(StrTip, FALSE, currentpos);Sleep(30);


}
void Table_PN::SetMsgHandle(CWnd* pHandle)
{
	m_msgwnd = pHandle;
}

void Table_PN::OutPutsStatusInfo(const CString& strInfo, BOOL bReplace,int process)
{
	int nCount = strInfo.GetLength();
	WCHAR* strNew = new WCHAR[nCount + 1];
	ZeroMemory(strNew, (nCount + 1)*sizeof(WCHAR));
	LPCTSTR str = LPCTSTR(strInfo);
	memcpy(strNew, str, nCount*sizeof(WCHAR));
	//g_strFlashInfo = strInfo;
	int nRet = 0;
	if (bReplace)
	{
		nRet = PostMessage(m_msgwnd->m_hWnd, WM_REPLACE_STATUSINFO, process, LPARAM(strNew));
	}
	else
	{
		nRet = PostMessage(m_msgwnd->m_hWnd, WM_ADD_STATUSINFO, process, LPARAM(strNew));
	}

}


void Table_PN::Search_OrderInformation(CString StrVendorName, CString StrPN)
{
	Search_POStruct temp_struct;
	CString  strTemp;
	_variant_t temp_var;
	//m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;

	strSql=_T("Select [POID],[POMID], [POMNumber], [POMSupplier], [POMFromBuyer], [POMEngrgContact], [POMTotalCost], [POPart], [PODescription], [POItemQtyReceived], [POCost], [POQty], [POPurchUnits], [POExtension], [CURCurrencyChar] from [TemcoPartsVendors_Default_v1].[dbo].[qryPO] Where POMSupplier LIKE '%") + StrVendorName + L"%' AND POPart LIKE '%"+StrPN+_T("%' Order by POID DESC");

	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	m_dataset_SearchPO.clear();

	while (!m_database_operator.m_pRecordset->EndOfFile)
	{
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POID = temp_var;
		}
		else
		{
			temp_struct.POID = -1;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMID = temp_var;
		}
		else
		{
			temp_struct.POMID = -1;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMNumber"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMNumber = temp_var;
		}
		else
		{
			temp_struct.POMNumber = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMSupplier"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMSupplier = temp_var;
		}
		else
		{
			temp_struct.POMSupplier = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMFromBuyer"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMFromBuyer = temp_var;
		}
		else
		{
			temp_struct.POMFromBuyer = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMEngrgContact"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMEngrgContact = temp_var;
		}
		else
		{
			temp_struct.POMEngrgContact = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POMTotalCost"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POMTotalCost = temp_var;
		}
		else
		{
			temp_struct.POMTotalCost = 0.0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POPart"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POPart = temp_var;
		}
		else
		{
			temp_struct.POPart = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PODescription"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.PODescription = temp_var;
		}
		else
		{
			temp_struct.PODescription = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POItemQtyReceived"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POReceived = temp_var;
		}
		else
		{
			temp_struct.POReceived = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POCost"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POCost = temp_var;
		}
		else
		{
			temp_struct.POCost = 0.0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POQty"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POQty = temp_var;
		}
		else
		{
			temp_struct.POQty = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POPurchUnits"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POPurchUnits = temp_var;
		}
		else
		{
			temp_struct.POPurchUnits = L"PCS";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POExtension"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POExtension = temp_var;
		}
		else
		{
			temp_struct.POExtension =0.0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("CURCurrencyChar"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.CURCurrencyChar = temp_var;
		}
		else
		{
			temp_struct.CURCurrencyChar = L"￥";
		}
		m_dataset_SearchPO.push_back(temp_struct);
		m_database_operator.m_pRecordset->MoveNext();
	}
	m_database_operator.CloseRecordset();


}


void Table_PN::Search_BuyMainTable(CString StrPN)
{
	BuyMainTable temp_struct;
	CString  strTemp;
	_variant_t temp_var;
	//m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;

	strSql = _T("Select * from BuyMainTable  Where PN LIKE '%") + StrPN + _T("%' Order by BuyID DESC");

	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	m_dataset_BuyMainTable.clear();

	while (!m_database_operator.m_pRecordset->EndOfFile)
	{
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.BuyID = temp_var;
		}
		else
		{
			temp_struct.BuyID = -1;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("POBegin"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.POBegin = temp_var;
		}
		else
		{
			temp_struct.POBegin = L"";
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Buyer"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Buyer = temp_var;
		}
		else
		{
			temp_struct.Buyer = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Contact"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Contact = temp_var;
		}
		else
		{
			temp_struct.Contact = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("ShipAddress"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.ShipAddress = temp_var;
		}
		else
		{
			temp_struct.ShipAddress = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("AssmeblyPNID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.AssmeblyPNID = temp_var;
		}
		else
		{
			temp_struct.AssmeblyPNID = -1;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PN"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.PN = temp_var;
		}
		else
		{
			temp_struct.PN = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Title"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Title = temp_var;
		}
		else
		{
			temp_struct.Title = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Details"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Details = temp_var;
		}
		else
		{
			temp_struct.Details = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyQty"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.BuyQty = temp_var;
		}
		else
		{
			temp_struct.BuyQty = 0;
		}
        /* m_database_operator.m_pRecordset->PutCollect("Year", temp_var);
        temp_var = st.wMonth;
        m_database_operator.m_pRecordset->PutCollect("Month", temp_var);
        temp_var = st.wDay;
        m_database_operator.m_pRecordset->PutCollect("Day", temp_var);
        temp_var =strDate+L" "+strTime;
        m_database_operator.m_pRecordset->PutCollect("FullTime", temp_var);*/
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Year"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.Year = temp_var;
        }
        else
        {
            temp_struct.Year = 0;
        }
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Month"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.Month = temp_var;
        }
        else
        {
            temp_struct.Month = 0;
        }
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Day"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.Day = temp_var;
        }
        else
        {
            temp_struct.Day = 0;
        }
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("FullTime"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.FullTime = temp_var;
        }
        else
        {
            temp_struct.FullTime =L"";
        }
		m_dataset_BuyMainTable.push_back(temp_struct);
		m_database_operator.m_pRecordset->MoveNext();
	}
	m_database_operator.CloseRecordset();
}
//False :不存在
//True:存在
BOOL Table_PN::Check_BuildPO(CString POBegin,int &BuyID)
{
    try
    {
        _variant_t temp_var;
        m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);

        CString strSql;


        strSql.Format(_T("Select * from BuyMainTable Where POBegin = '%s' "), POBegin);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

        if (m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
        {
            return FALSE;
        }
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyID"));
        if (temp_var.vt != VT_NULL)
        {
            BuyID = temp_var;
        }
        else
        {
            BuyID = -1;
        }

        return TRUE;
    }
    catch (CException* e)
    {
        return FALSE;
    }

}
BOOL Table_PN::InsertAndUpdate_BuyMainTable(BuyMainTable temp,  int &BuyID)
{
	try
	{
		_variant_t temp_var;
		m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);

		CString strSql;


		strSql.Format(_T("Select * from BuyMainTable Where POBegin = '%s' "), temp.POBegin);

		m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

		if (m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
		{
            m_database_operator.m_pRecordset->AddNew();
			if (!temp.POBegin.IsEmpty())
			{
				temp_var = temp.POBegin;
				m_database_operator.m_pRecordset->PutCollect("POBegin", temp_var);
			}
			if (!temp.Buyer.IsEmpty())
			{
				temp_var = temp.Buyer;
				m_database_operator.m_pRecordset->PutCollect("Buyer", temp_var);
			}
			if (!temp.Contact.IsEmpty())
			{
				temp_var = temp.Contact;
				m_database_operator.m_pRecordset->PutCollect("Contact", temp_var);
			}
			if (!temp.ShipAddress.IsEmpty())
			{
				temp_var = temp.ShipAddress;
				m_database_operator.m_pRecordset->PutCollect("ShipAddress", temp_var);
			}
			if (temp.AssmeblyPNID > -1)
			{
				temp_var = temp.AssmeblyPNID;
				m_database_operator.m_pRecordset->PutCollect("AssmeblyPNID", temp_var);
			}
			if (!temp.PN.IsEmpty())
			{
				temp_var = temp.PN;
				m_database_operator.m_pRecordset->PutCollect("PN", temp_var);
			}
			if (!temp.Title.IsEmpty())
			{
				temp_var = temp.Title;
				m_database_operator.m_pRecordset->PutCollect("Title", temp_var);
			}
			if (!temp.Details.IsEmpty())
			{
				temp_var = temp.Details;
				m_database_operator.m_pRecordset->PutCollect("Details", temp_var);
			}
			if (temp.BuyQty > -1)
			{
				temp_var = temp.BuyQty;
				m_database_operator.m_pRecordset->PutCollect("BuyQty", temp_var);
			}
            SYSTEMTIME st;
            CString strDate,strTime;
            GetLocalTime(&st);
            strDate.Format(_T("%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay);
            strTime.Format(_T("%2d:%2d:%2d"), st.wHour,st.wMinute,st.wSecond);
            strDate+=_T(" ");
            strDate+=strTime;
            temp_var = st.wYear;
            m_database_operator.m_pRecordset->PutCollect("Year", temp_var);
            temp_var = st.wMonth;
            m_database_operator.m_pRecordset->PutCollect("Month", temp_var);
            temp_var = st.wDay;
            m_database_operator.m_pRecordset->PutCollect("Day", temp_var);
            temp_var =strDate+L" "+strTime;
            m_database_operator.m_pRecordset->PutCollect("FullTime", temp_var);

			m_database_operator.m_pRecordset->Update();

		}
		
		 
		
        strSql.Format(_T("Select BuyID from BuyMainTable Where POBegin = '%s'"), temp.POBegin);

        m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
        if (m_database_operator.m_pRecordset->EndOfFile == VARIANT_FALSE)
        {
            temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyID"));
            if (temp_var.vt != VT_NULL)
            {
                BuyID = temp_var;
            }
            else
            {
                BuyID = -1;
            }
        }
        return TRUE;
	}
	catch (CException* e)
	{
		return FALSE;
	}
}

BOOL Table_PN::Delete_BuyMainTable(BuyMainTable temp)
{

 
	try
	{
		_variant_t temp_var;
		m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);

		CString strSql;


		strSql.Format(_T("delete from BuyMainTable Where BuyID = %d "), temp.BuyID);

		m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);

		strSql.Format(_T("delete from BuyDetailsTable Where BuyID = %d "), temp.BuyID);

		m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
		 


		return TRUE;
	}
	catch (CException* e)
	{
		return FALSE;
	}
}


void Table_PN::Search_BuyDetailsTable(CString BuyID)
{
	BuyDetailsTable temp_struct;
	CString  strTemp;
	_variant_t temp_var;
	//m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;

	strSql = _T("Select * from BuyDetailsTable  Where BuyID =  ") + BuyID + _T("  Order by BuyDetailsID DESC");

	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	m_dataset_BuyDetailsTable.clear();

	while (!m_database_operator.m_pRecordset->EndOfFile)
	{
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyDetailsID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.BuyDetailsID = temp_var;
		}
		else
		{
			temp_struct.BuyDetailsID = -1;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.BuyID = temp_var;
		}
		else
		{
			temp_struct.BuyID =0;
		}
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PNID"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.PNID = temp_var;
        }
        else
        {
            temp_struct.PNID =0;
        }
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Item"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Item = temp_var;
		}
		else
		{
			temp_struct.Item = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Qty"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Qty = temp_var;
		}
		else
		{
			temp_struct.Qty = 0;
		}


		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Reference"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Reference = temp_var;
		}
		else
		{
			temp_struct.Reference = L"";
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Value"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Value = temp_var;
		}
		else
		{
			temp_struct.Value = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Description"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Description = temp_var;
		}
		else
		{
			temp_struct.Description = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("PN"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.PN = temp_var;
		}
		else
		{
			temp_struct.PN = L"";
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UseQty"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.UseQty = temp_var;
		}
		else
		{
			temp_struct.UseQty = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("ItemStock"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.ItemStock = temp_var;
		}
		else
		{
			temp_struct.ItemStock = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("Need2Buy"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.Need2Buy = temp_var;
		}
		else
		{
			temp_struct.Need2Buy = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("OrderQty"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.OrderQty = temp_var;
		}
		else
		{
			temp_struct.OrderQty = 0;
		}

		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("UnitPrice"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.UnitPrice = temp_var;
		}
		else
		{
			temp_struct.UnitPrice = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("TotalPrice"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.TotalPrice = temp_var;
		}
		else
		{
			temp_struct.TotalPrice = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("SUID"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.SUID = temp_var;
		}
		else
		{
			temp_struct.SUID = 0;
		}
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("VendorName"));
		if (temp_var.vt != VT_NULL)
		{
			temp_struct.VendorName = temp_var;
		}
		else
		{
			temp_struct.VendorName = L"";
		}
        temp_var = m_database_operator.m_pRecordset->GetCollect(_T("NOTE"));
        if (temp_var.vt != VT_NULL)
        {
            temp_struct.strNote = temp_var;
        }
        else
        {
            temp_struct.strNote = L"";
        } 

		m_dataset_BuyDetailsTable.push_back(temp_struct);
		m_database_operator.m_pRecordset->MoveNext();
	}
	m_database_operator.CloseRecordset();
}
BOOL Table_PN::InsertAndUpdate_BuyDetailsTable(BuyDetailsTable temp)
{
	try
	{
		_variant_t temp_var;
		m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);

		CString strSql;


		strSql.Format(_T("Select * from BuyDetailsTable Where BuyDetailsID = %d "), temp.BuyDetailsID);

		m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);

		if (m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
		{
            m_database_operator.m_pRecordset->AddNew();
			if (temp.BuyID > -1)
			{
				temp_var = temp.BuyID;
				m_database_operator.m_pRecordset->PutCollect("BuyID", temp_var);
			}
			if (temp.Item > -1)
			{
				temp_var = temp.Item;
				m_database_operator.m_pRecordset->PutCollect("Item", temp_var);
			}
			if (temp.Qty > -1)
			{
				temp_var = temp.Qty;
				m_database_operator.m_pRecordset->PutCollect("Qty", temp_var);
			}
            if (temp.PNID > -1)
            {
                temp_var = temp.PNID;
                m_database_operator.m_pRecordset->PutCollect("PNID", temp_var);
            }
			if (!temp.Reference.IsEmpty())
			{
				temp_var = temp.Reference;
				m_database_operator.m_pRecordset->PutCollect("Reference", temp_var);
			}
			if (!temp.Value.IsEmpty())
			{
				temp_var = temp.Value;
				m_database_operator.m_pRecordset->PutCollect("Value", temp_var);
			}
			if (!temp.Description.IsEmpty())
			{
				temp_var = temp.Description;
				m_database_operator.m_pRecordset->PutCollect("Description", temp_var);
			}
			if (!temp.PN.IsEmpty())
			{
				temp_var = temp.PN;
				m_database_operator.m_pRecordset->PutCollect("PN", temp_var);
			}
			if (temp.UseQty > -1)
			{
				temp_var = temp.UseQty;
				m_database_operator.m_pRecordset->PutCollect("UseQty", temp_var);
			}
			if (temp.ItemStock > -1)
			{
				temp_var = temp.ItemStock;
				m_database_operator.m_pRecordset->PutCollect("ItemStock", temp_var);
			}
			if (temp.Need2Buy > -1)
			{
				temp_var = temp.Need2Buy;
				m_database_operator.m_pRecordset->PutCollect("Need2Buy", temp_var);
			}
			if (temp.OrderQty > -1)
			{
				temp_var = temp.OrderQty;
				m_database_operator.m_pRecordset->PutCollect("OrderQty", temp_var);
			}
			if (temp.UnitPrice > -1)
			{
				temp_var = temp.UnitPrice;
				m_database_operator.m_pRecordset->PutCollect("UnitPrice", temp_var);
			}
			if (temp.SUID > -1)
			{
				temp_var = temp.SUID;
				m_database_operator.m_pRecordset->PutCollect("SUID", temp_var);
			}
			if (!temp.VendorName.IsEmpty())
			{
				temp_var = temp.VendorName;
				m_database_operator.m_pRecordset->PutCollect("VendorName", temp_var);
			}
            if (!temp.strNote.IsEmpty())
            {
                temp_var = temp.strNote;
                m_database_operator.m_pRecordset->PutCollect("NOTE", temp_var);
            }
			m_database_operator.m_pRecordset->Update();

		}
        

		return TRUE;
	}
	catch (CException* e)
	{
		return FALSE;
	}
}

CString Table_PN::GetPONumber(CString BeginPO)
{
	CString  strTemp;
	_variant_t temp_var;
	//m_database_operator.OnInitADOConn(m_databaseIP,m_databaseName,m_databaseUserName,m_databasePwd);
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;
	int BuyNum = 0;
	strSql.Format(_T("Select * from AutoBuyPO  Where BuyDate = '%s' Order By BuyNum DESC "), BeginPO);// = +BuyID + _T(" Order by BuyDetailsID DESC");

	m_database_operator.m_pRecordset = m_database_operator.OpenRecordset(strSql);
	if (!m_database_operator.m_pRecordset->EndOfFile != VARIANT_FALSE)
	{
		temp_var = m_database_operator.m_pRecordset->GetCollect(_T("BuyNum"));
		if (temp_var.vt != VT_NULL)
		{
			BuyNum = temp_var;
		}
		else
		{
			BuyNum = 0;
		}

	} 
	else
	{
		BuyNum = 0;
	}
	BuyNum++;
	strSql.Format(_T("INSERT INTO AutoBuyPO([BuyDate], [BuyNum])  VALUES ('%s',%d) "), BeginPO, BuyNum);
	
	m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
	
	strTemp.Format(_T("%s-%d"), BeginPO, BuyNum);
	return strTemp;
}

BOOL Table_PN::DeletePONumber(CString BeginPO, CString Num)
{
	m_database_operator.OnInitADOConn(m_databaseIP, m_databaseName, m_databaseUserName, m_databasePwd);
	CString strSql;
	int BuyNum = _wtoi(Num);
	strSql.Format(_T("DELETE FROM [dbo].[AutoBuyPO] WHERE BuyDate='%s' AND BuyNum=%d"), BeginPO, BuyNum);
	m_database_operator.m_pConnection->Execute(strSql.GetString(), NULL, adCmdText);
	return TRUE;
}