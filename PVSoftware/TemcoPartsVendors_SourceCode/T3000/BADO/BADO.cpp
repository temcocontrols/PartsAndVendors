#include "StdAfx.h"
#include "../resource.h"
#include "../bado/BADO.h"
#include "../globle_function.h"
// #ifdef _DEBUG
// #ifndef _WIN64
#define FOR_DATABASE_CONNECT					_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")
// #else
// #pragma comment(lib,"json/json_mtd_x64.lib")
// #define FOR_DATABASE_CONNECT					_T("Provider=Microsoft Office 12.0 Access Database Engine OLE DB Provider;Data Source=")
// #endif
// #else
// #ifndef _WIN64 
// #define FOR_DATABASE_CONNECT					_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=")
// #else
// #define FOR_DATABASE_CONNECT					_T("Provider=Microsoft Office 12.0 Access Database Engine OLE DB Provider;Data Source=")
// #endif
// #endif

//Provider=Microsoft Office 12.0 Access Database Engine OLE DB Provider
//#define FOR_DATABASE_CONNECT					_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};Dbq=")
CBADO::CBADO(void)
{
	//g_strDatabasefilepath = _T("");
	//g_strOrigDatabaseFilePath=_T("");
	//g_strDatabasefilepath=_T("");
	//g_strExePth=_T("");
	//g_strImgeFolder=_T("");
	m_dbfilepath=_T("");
	m_dbImgeFolder=L"";
}

CBADO::~CBADO(void)
{
}
void CBADO::DeleteDB(){
 
DeleteFile(m_dbfilepath);
}
BOOL CBADO::OnInitADOConn()
{
    CString StrTips;
	HANDLE hFind;//
	WIN32_FIND_DATA wfd;//
	hFind = FindFirstFile(m_dbfilepath, &wfd);//
	 
	::CoInitialize(NULL);
	try 
	{
////////////////////////////////////////////////////////////////////////////////////////////
		 
         CString temp = (CString)FOR_DATABASE_CONNECT;

		 m_ConnectString=temp+m_dbfilepath;

// 		CStringArray  ArrayFileName;
// 		SplitCStringA(ArrayFileName,m_dbfilepath,L"\\");
// 		CString filename=L"";
// 		for (int i=0;i<ArrayFileName.GetSize()-1;i++)
// 		{
// 			filename+=ArrayFileName[i];
// 			filename+=L"\\";
// 		}
// 		m_dbImgeFolder=filename+_T("image");
// 		CreateDirectory(m_dbImgeFolder,NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////
//�������ݿ�


		m_pConnection.CreateInstance("ADODB.Connection");
	 
		m_pConnection->Open(m_ConnectString.GetString(),"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
        return FALSE;
	}

    return TRUE;

}
BOOL CBADO::OnInitADOConn(CString StrSQLSever,CString StrDatabase,CString StrUserName,CString StrPassword)
{

	if (m_pConnection!=NULL&&m_pConnection->State)
	{
		return TRUE;
	}

	CString StrTips;
 
	::CoInitialize(NULL);
// 	if (!AfxOleInit())
// 	{
// 		return FALSE;
// 	}
	HRESULT hr = NULL;
	try 
	{
		////////////////////////////////////////////////////////////////////////////////////////////

		//CString temp = (CString)FOR_DATABASE_CONNECT;

		//m_ConnectString=temp+m_dbfilepath;
		 

		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		
		if (SUCCEEDED(hr))
		{
			m_ConnectString.Format(_T("Provider = SQLOLEDB.1; Persist Security Info = False; User ID = %s; Password= %s; Initial Catalog = %s; Data Source = %s"),
			                         StrUserName,StrPassword,StrDatabase,StrSQLSever);

			m_pConnection->ConnectionString =(_bstr_t)m_ConnectString;
				//("Provider = SQLOLEDB.1; Persist Security Info = False; User ID = sa; Password=Travel123; Initial Catalog = m_databaseName; Data Source = 127.0.0.1");
			//("Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security Info=False;User ID="";Initial Catalog= student achievement management system;Data Source=HUI\\SQL;Initial File Name="";Server SPN=""");
			hr = m_pConnection->Open("", "", "", adConnectUnspecified);//Open database
			if (FAILED(hr))
			{
				AfxMessageBox(_T("Open Failed!"));
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox(_T("Create instance of connection failed!"));
			return FALSE;
		}
		
		//m_pConnection.CreateInstance("ADODB.Connection");
		//m_pConnection->Open((_bstr_t)m_ConnectString.GetString(),"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;

}
void CBADO::SetDBPath(CString dbpath){
m_dbfilepath=dbpath;
}
_RecordsetPtr& CBADO::OpenRecordset( CString sql )
{
	ASSERT(!sql.IsEmpty());
	try 
	{
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(_bstr_t(sql),m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);

	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRecordset;
}

void CBADO::CloseRecordset()
{
	if (m_pRecordset->State)
	{
	  m_pRecordset->Close();
	}
	

}

void CBADO::CloseConn()
{
	if (m_pConnection->State)
	{
		m_pConnection->Close();
	}
	m_pConnection=NULL;
	::CoUninitialize();


}

UINT CBADO::GetRecordCount( _RecordsetPtr pRecordset )
{
	int nCount = 0;
	try 
	{
		pRecordset->MoveFirst();
	}
	catch(...)
	{

		return 0;
	}

	if (pRecordset->FirstOfFile)
		return 0;
	while(!pRecordset->EndOfFile)
	{   
		pRecordset->MoveNext();
		nCount = nCount + 1;
	}
	pRecordset->MoveFirst();
	return nCount;

}

void CBADO::Createtable( CString strSQL )
{
	CBADO m_ado;
	m_ado.OnInitADOConn();
	m_ado.m_pRecordset = m_ado.OpenRecordset(strSQL);

	m_ado.CloseRecordset();
	m_ado.CloseConn();

}

/*------------------------------------fun-------------------------------------------------------- 
*   Functions           -   IsHaveTable(_ConnectionPtr   pConnection,   CString   strTableName) 
*   Parameter:         -   pConnection�����ݿ���� 
-   strTableName�����ݿ����Ƿ��д˱� 
*   Return   Value:   -  ��TRUE bool��FALSE���ޱ��б� 
*   Description:     -   �����ݿ��в���Ƿ���Ҫ�򿪵ı�[strTableName]�����ޱ�������ʾ����FALSE�� 
-   �����Ӧ�ô˺���ʱ��ֻ������Ƿ�Ҫ�������У������ٸ�����ʾ�� 
*   Author:               -   lishancai 
*   Date:                   -   2011-10-1 
***********************************************************************************************/ 

bool CBADO::IsHaveTable( CBADO ado, CString strTableName )
{
	
	ado.m_pRecordset = NULL;//���ݿ��ָ�� 
	bool   bIsHaveNo   =   FALSE;//�Ƿ��б�Ĭ���ޱ� 

	//pConnection:ָ�����ݿ� 
	ado.m_pRecordset   =   ado.m_pConnection-> OpenSchema(adSchemaTables);//ָ�����еı� 

	CString   strMsg; 


	while(!(ado.m_pRecordset-> EndOfFile))//ָ���Ƿ��Ѿ�ָ�����һ����¼�� 
	{ 
		_bstr_t   table_name   =   ado.m_pRecordset-> Fields-> GetItem(_T("TABLE_NAME"))-> Value;//�õ�������� 

   
		if(strTableName   ==   (LPCSTR)  table_name)//�����ж��Ƿ���ͬ�� 
		{ 
			bIsHaveNo   =   TRUE;//�б��� 
			break; 
		} 

		ado.m_pRecordset-> MoveNext(); 
	} 


	if(bIsHaveNo   ==   FALSE)
    //�ޱ������ʾ��������FALSE 
	{ 
		//strMsg.Format(_T( "���ݿ���û�в鵽�µı�:   %s��\n����ȷ�����ݿ����Ч�ԣ� "),   strTableName); 
		//MessageBox(NULL,   strMsg,   _T( "���ݿ��û�в鵽�� "),   MB_OK   |   MB_ICONWARNING); 
		//	MessageBox(_T("Products�����ڣ�"));
		return   FALSE; 
	} 
	else//���б�ſɽ�һ������ 
	{ 
		return   TRUE; 
	}

}

void CBADO::RenameTable(CString TableName_Old,CString TableName_New)
{
    
}