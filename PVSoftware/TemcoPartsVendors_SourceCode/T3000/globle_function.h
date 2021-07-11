#ifndef _GLOBLE_FUNCTION_H
#define _GLOBLE_FUNCTION_H

#pragma region For_Bacnet
#include "CM5/ud_str.h"



#pragma endregion For_Bacnet


#include "global_variable_extern.h"
#define FLEXGRID_CELL_COLOR RGB(128,128,128) 
#define GREEN_COLOR RGB(0,255,0)
#define YELLOW_COLOR RGB(255,255,0)
#define ORANGE_COLOR RGB(255,165,0)

#include "global_variable_extern.h"
#include <afxinet.h>
BOOL CheckForUpdate(
	LPCTSTR szFtpServer,
	LPCTSTR szFtpUsername,
	LPCTSTR szFtpPassword,
	LPCTSTR szFtpFilename,
	LPCTSTR szCurrentVersion,
	LPTSTR szLastVersion );

 
int Set_Communication_Count(bool b_transmission,int bac_instanceid);
 
 
int turn_hex_str_to_ten_num(char *str);
bool turn_hex_file_line_to_unsigned_char(char *str);
int turn_hex_char_to_int(char c);
void turn_int_to_unsigned_char(char *source,int length_source,unsigned char *aim);

float get_tstat_version(unsigned short tstat_id);

float get_curtstat_version();

int make_sure_isp_mode(int the_tstat_id);
 
bool multi_read_tstat(int id);

//
void SetPaneString(int nIndext,CString str);

 
bool can_be_writed_hex_file(int product_model,int hex_file_product_model);
CString get_product_name_by_product_model(int product_model);

//CString GetTempUnit(int analog1_or_analog2=-1);
CString GetTempUnit(int nRange=-1,int nPIDNO = 0);
CString get_product_class_name_by_model_ID(int nModelID);

 
BOOL GetSerialComPortNumber1(vector<CString>& szComm);

BOOL Post_Thread_Message(UINT MsgType,
	unsigned char device_id,
	unsigned short address,
	short new_value,
	short old_value,
	HWND Dlg_hwnd,
	UINT CTRL_ID,
	CString Changed_Name);


BOOL Post_Read_one_Thread_Message(
	unsigned char device_id,
	unsigned short address,
	HWND Dlg_hwnd);

BOOL Post_Invoke_ID_Monitor_Thread(UINT MsgType,
	int Invoke_ID,
	HWND hwnd,
	CString Show_Detail = _T(""),
	int nRow = 0,
	int nCol = 0
	);
 
 


 

void SplitCStringA(CStringArray &saArray, CString sSource, CString sToken,BOOL Skip_Token=TRUE);
char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c =":");
char * intervaltotextfull(char *textbuf, long seconds , unsigned minutes , unsigned hours,char *c =":");
 
 
  
  
  bool Open_bacnetSocket2(CString strIPAdress,short nPort,SOCKET &mysocket);
  unsigned char Str_to_Byte(CString need_conver);
 
CString GetProductName(int ModelID);

CString Get_Table_Name(int SerialNo,CString Type ,int Row);
void    Insert_Update_Table_Name(int SerialNo,CString Type,int Row,CString TableName); 
int Get_Unit_Process(CString Unit);
BOOL Get_Bit_FromRegister(unsigned short RegisterValue,unsigned short Position);
int AddNetDeviceForRefreshList(BYTE* buffer, int nBufLen,  sockaddr_in& siBind);
UINT RefreshNetWorkDeviceListByUDPFunc();
//void DFTrace(CString &nCString);
void DFTrace(LPCTSTR lpCString);
bool GetFileNameFromPath(CString ncstring,CString &cs_return);
 
int Open_MonitorDataBase(WCHAR *DataSource);
 
 
void SaveBacnetConfigFile_Cache(CString &SaveConfigFilePath);
int LoadBacnetConfigFile(bool write_to_device,LPCTSTR tem_read_path);
int LoadBacnetConfigFile_Cache(LPCTSTR tem_read_path);
int handle_read_monitordata_ex(char *npoint,int nlength);
bool IP_is_Local(LPCTSTR ip_address);
bool Is_Bacnet_Device(unsigned short n_product_class_id);
BOOL DirectoryExist(CString Path);
BOOL CreateDirectory(CString path);
BOOL DeleteDirectory(CString path);
int GetHostAdaptersInfo(CString &IP_address_local);
DWORD WinExecAndWait( LPCTSTR lpszAppPath,LPCTSTR lpParameters,LPCTSTR lpszDirectory, 	DWORD dwMilliseconds);
CString GetContentFromURL(CString URL);
CString GetProductFirmwareTimeFromTemcoWebsite(CString URL,CString HexOrBinName,CString &FileSize);
BOOL KillProcessFromName(CString strProcessName) ;
BOOL CheckTheSameSubnet(CString strIP ,CString strIP2);

 


CString GetExePath(bool bHasSlash);
void GetIPMaskGetWay();
void GetIPMaskGetWayForScan();
BOOL Is_Dig_Num(CString str);
BOOL ValidAddress(CString sAddress);

 
void TraverseFolder( const CString& strDir,std::vector<CString>& vecFile);



void LoadTstat_InputData();
void LoadInputData_CS3000();
CString GetTextFromReg(unsigned short reg);
CString GetTextFromReg_Buffer(unsigned short reg,unsigned short *Buffer);
 
BOOL  ReadLineFromHexFile(CFile& file, char* pBuffer);
int Get_Binfile_Information(LPCTSTR filepath,Bin_Info &ret_bin_Info);
int Get_HexFile_Information(LPCTSTR filepath,Bin_Info &ret_bin_Info);
BOOL HexFileValidation(const CString& strFileName);
BOOL BinFileValidation(const CString& strFileName);
bool IsDigit(CString strData);
CString NewGUID();
 CString ReadStringCharToUnicode(CString &str);
 CString DealWithFootPrint(CString FootPrint);
#endif