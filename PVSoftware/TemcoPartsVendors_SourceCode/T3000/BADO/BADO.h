#pragma once

class  CBADO
{
public:
	CBADO(void);
	~CBADO(void);
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;
	//CString g_strOrigDatabaseFilePath;
	//CString	g_strDatabasefilepath;
	//CString g_strExePth;
	//CString g_strImgeFolder;
	CString m_ConnectString;
	CString m_dbfilepath;
	CString m_dbImgeFolder;
public:
    void SetDBPath(CString dbpath);
	BOOL OnInitADOConn();
	BOOL OnInitADOConn(CString StrSQLSever,CString StrDatabase,CString StrUserName,CString StrPassword);
							// �������ݿ�
	_RecordsetPtr& OpenRecordset(CString sql);  //�򿪼�¼��
	void CloseRecordset();						//�رռ�¼��
	void CloseConn();							//�ر����ݿ�����
	UINT GetRecordCount(_RecordsetPtr pRecordset);//��ü�¼��

	void Createtable(CString strSQL);//�Զ�������
	bool IsHaveTable(CBADO ado, CString strTableName);//�жϱ��Ƿ����
	void DeleteDB();
    void RenameTable(CString TableName_Old,CString TableName_New);
};



