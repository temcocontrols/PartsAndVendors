
#include "stdafx.h"
 
#include "globle_function.h"
#include "Windows.h"
#include "T3000.h"
 


 
#include "gloab_define.h"
 
#include "CM5\MyOwnListCtrl.h"

#include "globle_function.h"

#include "gloab_define.h"



#include "CM5\ud_str.h"

#include "tlhelp32.h"
#define DELAY_TIME	 10	//MS
#define Modbus_Serial	0
#define	Modbus_TCP	1
#include "MainFrm.h"







 
 
//val         the value that you want to write to the register
//the return value == -1 ,no connecting
//the return value == -2 ,try it again
//the return value == -3,Maybe that have more than 2 Tstat is connecting
//the return value == -4 ,between devLo and devHi,no Tstat is connected ,
//the return value == -5 ,the input have some trouble
//the return value == -6 , the bus has bannet protocol,scan stop;
//the return value >=1 ,the devLo!=devHi,Maybe have 2 Tstat is connecting
//清空串口缓冲区
//the return value is the register address
//Sleep(50);       //must use this function to slow computer
 
void SetPaneString(int nIndext,CString str)
{
    if(nIndext != BAC_SHOW_MISSION_RESULTS)
        return;
    if(str.IsEmpty())
        return;

    char * temp_cs = new char[255];

    WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1, temp_cs, 255, NULL, NULL );
    PostMessage(m_statusbar_hwnd,WM_SHOW_STATUS_TEXT,(WPARAM)temp_cs,NULL);

    return;
    CMFCStatusBar * pStatusBar=NULL;
    if(AfxGetMainWnd()->GetActiveWindow()==NULL)//if this function is called by a thread ,return
        return;
    pStatusBar = (CMFCStatusBar *) AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
    pStatusBar->SetPaneText(nIndext,str.GetString());
    pStatusBar->SetPaneTextColor (nIndext, RGB(0,0,0));
    if (nIndext==3)
    {
        pStatusBar->SetPaneTextColor (nIndext, RGB(255,255,255));
        pStatusBar->SetPaneBackgroundColor(nIndext,RGB(42,58,87));
    }
}
 

int turn_hex_str_to_ten_num(char *source)
{
    int j=0,k=0,l=0;
    for(int i=0; i<2; i++) //***********************************2
        if(j==0)
        {
            switch(source[i])
            {
            case '0':
                k=0;
                break;
            case '1':
                k=1;
                break;
            case '2':
                k=2;
                break;
            case '3':
                k=3;
                break;
            case '4':
                k=4;
                break;
            case '5':
                k=5;
                break;
            case '6':
                k=6;
                break;
            case '7':
                k=7;
                break;
            case '8':
                k=8;
                break;
            case '9':
                k=9;
                break;

            case 'a':
                k=10;
                break;
            case 'b':
                k=11;
                break;
            case 'c':
                k=12;
                break;
            case 'd':
                k=13;
                break;
            case 'e':
                k=14;
                break;
            case 'f':
                k=15;
                break;
            case 'A':
                k=10;
                break;
            case 'B':
                k=11;
                break;
            case 'C':
                k=12;
                break;
            case 'D':
                k=13;
                break;
            case 'E':
                k=14;
                break;
            case 'F':
                k=15;
                break;

            default:
                return -1;
            }
            for( ; j<2-i-1; j++)
                k*=16;
        }
        else
        {
            l+=k;
            j=0;
            i--;
        }
    l+=k;
    return l;
}

int turn_hex_char_to_int(char c)
{
    int k=0;
    switch(c)
    {
    case '0':
        k=0;
        break;
    case '1':
        k=1;
        break;
    case '2':
        k=2;
        break;
    case '3':
        k=3;
        break;
    case '4':
        k=4;
        break;
    case '5':
        k=5;
        break;
    case '6':
        k=6;
        break;
    case '7':
        k=7;
        break;
    case '8':
        k=8;
        break;
    case '9':
        k=9;
        break;

    case 'a':
        k=10;
        break;
    case 'b':
        k=11;
        break;
    case 'c':
        k=12;
        break;
    case 'd':
        k=13;
        break;
    case 'e':
        k=14;
        break;
    case 'f':
        k=15;
        break;
    case 'A':
        k=10;
        break;
    case 'B':
        k=11;
        break;
    case 'C':
        k=12;
        break;
    case 'D':
        k=13;
        break;
    case 'E':
        k=14;
        break;
    case 'F':
        k=15;
        break;

    default:
        return -1;//2
    }
    return k;
}

bool turn_hex_file_line_to_unsigned_char(char *str)
{
    char *p_temp=str;
    int itemp=strlen(p_temp);
    for(int i=0; i<itemp; i++)
    {
        *(p_temp+i)=turn_hex_char_to_int(*(p_temp+i));
        if(*(p_temp+i)==-1)
            return false;
    }
    return true;
}


void turn_int_to_unsigned_char(char *source,int length_source,unsigned char *aim)
{
    char *p_c_temp=source;
    unsigned char *p_uc_temp=aim;
    unsigned char uctemp;
    for(int i=0; i <length_source; i++)
        if(i%2==0)
        {
            char ctemp=*(p_c_temp+i);
            uctemp = ctemp*16;
        }
        else
        {
            char ctemp=*(p_c_temp+i);
            uctemp+=ctemp;
            *(p_uc_temp+i/2)=uctemp;
            uctemp=0;
        }
}






float get_tstat_version(unsigned short tstat_id)
{
    //get tstat version and judge the tstat is online or no
    //tstat is online ,return >0
    //tstat is not online ,return -2

    float tstat_version2=(float)product_register_value[4];//tstat version
    if(tstat_version2==-2 || tstat_version2==-3)
        return tstat_version2;
    if(tstat_version2 >=240 && tstat_version2 <250)
        tstat_version2 /=10;
    else
    {
        tstat_version2 = (float)(product_register_value[5]*256+product_register_value[4]);
        tstat_version2 /=10;
    }//tstat_version
    return tstat_version2;
}

float get_curtstat_version()
{
    float tstat_version2= product_register_value[4];//tstat version
    if(tstat_version2<=0)
        return tstat_version2;
    if(tstat_version2 >=240 && tstat_version2 <250)
        tstat_version2 /=10;
    else
    {
        tstat_version2 = (float)(product_register_value[5]*256+product_register_value[4]);
        tstat_version2 /=10;
    }//tstat_version
    return tstat_version2;

}


int make_sure_isp_mode(int the_tstat_id)
{
     
    return 1;//in isp mode
}

 

 




bool multi_read_tstat(int id)
{

    bool return_value=true;
     
    return return_value;
}


bool can_be_writed_hex_file(int product_model,int hex_file_product_model)
{
    //product model
    // T3-8IO-------------20
    // T3-32I-------------22
    // T3-8i/60-----------23
    // Flexdriver---------25
    //Tstat5A-------------2
    //Tstat5B-------------1
    //Tstat5B2------------3
    //Tstat5C-------------4
    //Tstat5D-------------12
    //Solar---------------30
    //hex_file_product_model parameter is the hex_file_register 0x100 (256)
    //	if (product_model==18||product_model==17)
    {
        return true;
    }
    if(hex_file_product_model==255)//////////////old version hex file,before 2005.11.15
        return true;
    if(product_model<=TSTAT_PRODUCT_MODEL && hex_file_product_model<=TSTAT_PRODUCT_MODEL)
        return true;
    if(product_model==LED_PRODUCT_MODEL && hex_file_product_model==LED_PRODUCT_MODEL)
        return true;
    if(product_model==PM_NC && hex_file_product_model==PM_NC)
        return true;
    if(product_model==PM_T3IOA && hex_file_product_model==PM_T3IOA)
        return true;
    if(product_model==PM_T3PT10 && hex_file_product_model==PM_T3PT10)
        return true;
    if(product_model==T3_32I_PRODUCT_MODEL && hex_file_product_model==T3_32I_PRODUCT_MODEL)
        return true;
    if(product_model==T3_8I_16O_PRODUCT_MODEL && hex_file_product_model==T3_8I_16O_PRODUCT_MODEL)
        return true;
    if(product_model==PM_SOLAR && hex_file_product_model==PM_SOLAR)
        return true;
    if(product_model==PM_ZIGBEE && hex_file_product_model==PM_ZIGBEE)
        return true;
    return false;
}
CString get_product_name_by_product_model(int product_model)
{
    CString return_str;
    if(product_model>0 && product_model<=TSTAT_PRODUCT_MODEL)
        product_model=TSTAT_PRODUCT_MODEL;
    switch(product_model)
    {
    case 19:
        return_str=_T("Tstat");
        break;
    case 20:
        return_str=_T("T3-8IO");
        break;
    case 22:
        return_str=_T("T3-32I");
        break;
    case 23:
        return_str=_T("T3-8i/60");
        break;
    case 25:
        return_str=_T("Flexdriver");
        break;
    case 30:
        return_str=_T("Solar");
        break;
    case PM_ZIGBEE:
        return_str=_T("ZigBee");
        break;
    default:
        return_str=_T("Unknown");
        break;
    }
    return return_str;
}

// Function : 获得单位名称，此单位用于Input Grid，Output Grid，Output Set Grid，主界面的Grid等等。
// Param: int nRange: 指示当前的Range的选择值。函数应该根据Range的选择以及TStat的型号，
//					获得单位名称，如摄氏度，华氏度，百分比，自定义的单位等。
//           int nPIDNO: 区分PID1 还是PID2，1＝PID1，2＝PID2
// return ： 单位名称
CString GetTempUnit(int nRange, int nPIDNO)
{
    CString strTemp=_T("");

    if(nRange<0) // 使用默认的温度单位
    {
        UINT uint_temp=GetOEMCP();//get system is for chinese or english
        if(uint_temp!=936 && uint_temp!=950)
        {
            if(product_register_value[MODBUS_DEGC_OR_F]==0)	//121
            {
                strTemp.Format(_T("%cC"),176);
            }
            else
            {
                strTemp.Format(_T("%cF"),176);
            }
        }
        else
        {
            //Chinese.
            if(product_register_value[MODBUS_DEGC_OR_F]==0)//121
            {
                strTemp=_T("℃");
            }
            else
            {
                strTemp=_T("℉");
            }
        }
        return strTemp;
    }

    if(nRange==0)		// Raw value, no unit
        strTemp=_T("");
    else if(nRange==1)
    {
        //
        UINT uint_temp=GetOEMCP();//get system is for chinese or english
        if(uint_temp!=936 && uint_temp!=950)
        {
            if(product_register_value[MODBUS_DEGC_OR_F]==0)//121
            {
                strTemp.Format(_T("%cC"),176);
            }
            else
            {
                strTemp.Format(_T("%cF"),176);
            }
        }
        else
        {
            //chinese.
            if(product_register_value[MODBUS_DEGC_OR_F]==0)//121
            {
                strTemp=_T("℃");
            }
            else
            {
                strTemp=_T("℉");
            }
        }
        return strTemp;
    }
    else if(nRange==2)
    {
        //
        strTemp=_T("%");
    }
    else if(nRange==3)
    {
        //ON/OFF
        strTemp=_T("");
    }
    else if(nRange==4)
    {
        //Customer Sersor
        if(nPIDNO==1)
        {
            int m_271=product_register_value[MODBUS_UNITS1_HIGH];//271 390
            int m_272=product_register_value[MODBUS_UNITS1_LOW];//272  391
            if(m_271>>8=='0')
            {
                if((m_271 & 0xFF) =='0')
                {
                    if(m_272>>8=='0')
                        strTemp.Format(_T("%c"),m_272 & 0xFF);
                    else
                        strTemp.Format(_T("%c%c"),m_272>>8,m_272 & 0xFF);
                }
                else
                    strTemp.Format(_T("%c%c%c"),m_271 & 0xFF,m_272>>8,m_272 & 0xFF);
            }
            else
                strTemp.Format(_T("%c%c%c%c"),m_271>>8,m_271 & 0xFF,m_272>>8,m_272 & 0xFF);
        }
        else if(nPIDNO==2)
        {
            int m_273=product_register_value[MODBUS_UNITS2_HIGH];//273  392;
            int m_274=product_register_value[MODBUS_UNITS2_LOW];//274 393;
            if(m_273>>8=='0')
            {
                if((m_273 & 0xFF)=='0')
                {
                    if(m_274>>8=='0')
                        strTemp.Format(_T("%c"),m_274 & 0xFF);
                    else
                        strTemp.Format(_T("%c%c"),m_274>>8,m_274 & 0xFF);
                }
                else
                    strTemp.Format(_T("%c%c%c"),m_273 & 0xFF,m_274>>8,m_274 & 0xFF);
            }
            else
                strTemp.Format(_T("%c%c%c%c"),m_273>>8,m_273 & 0xFF,m_274>>8,m_274 & 0xFF);

        }
    }
    return strTemp;
}

CString get_product_class_name_by_model_ID(int nModelID)
{
    CString strClassName;
    switch(nModelID)
    {
    case 2:
        strClassName=g_strTstat5a;
        break;
    case 1:
        strClassName=g_strTstat5b;
        break;
    case 3:
        strClassName=g_strTstat5b;
        break;
    case 4:
        strClassName=g_strTstat5c;
        break;
    case 6:
        strClassName=g_strTstat6;
        break;
    case 7:
        strClassName=g_strTstat7;
        break;
    case 12:
        strClassName=g_strTstat5d;
        break;
    case PM_NC:
        strClassName=g_strnetWork;
        break;
    case NET_WORK_OR485_PRODUCT_MODEL:
        strClassName=g_strOR485;
        break;
    case 17:
        strClassName=g_strTstat5f;
        break;
    case 18:
        strClassName=g_strTstat5g;
        break;
    case 16:
        strClassName=g_strTstat5e;
        break;
    case 19:
        strClassName=g_strTstat5h;
        break;
    case PM_LightingController:
        strClassName = g_strLightingCtrl;

    case 13:
    case 14:
        break;
    default:
        strClassName=g_strTstat5a;
        break;
    }

    return strClassName;
}


BOOL GetSerialComPortNumber1(vector<CString>& szComm)
{
    LPCTSTR strRegEntry = _T("HARDWARE\\DEVICEMAP\\SERIALCOMM\\");

    HKEY   hKey;
    LONG   lReturnCode=0;
    lReturnCode=::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegEntry, 0, KEY_READ, &hKey);
    USB_Serial.Empty();
    if(lReturnCode==ERROR_SUCCESS)
    {
        DWORD dwIndex = 0;
        WCHAR lpValueName[MAX_PATH];
        ZeroMemory(lpValueName, MAX_PATH);
        DWORD lpcchValueName = MAX_PATH;
        DWORD lpReserved = 0;
        DWORD lpType = REG_SZ;
        BYTE		lpData[MAX_PATH];
        ZeroMemory(lpData, MAX_PATH);
        DWORD lpcbData = MAX_PATH;
        dwIndex = 0;
        while(RegEnumValue(	hKey, dwIndex, lpValueName, &lpcchValueName, 0, &lpType, lpData, &lpcbData ) != ERROR_NO_MORE_ITEMS)
        {
            //TRACE("Registry's   Read!");
            dwIndex++;

            lpcchValueName = MAX_PATH;
            //lpValueName[0] = '\0';

            CString strValueName= CString(lpValueName);

            WCHAR ch[MAX_PATH];
            ZeroMemory(ch, MAX_PATH);
            memcpy(ch, lpData, lpcbData);
            CString str = CString(ch);
            szComm.push_back(str);

            if(strValueName.Find(_T("USBSER")) >=0)
            {
                DFTrace(_T("Find USB Serial Port!"));
                USB_Serial = str;
            }

            ZeroMemory(lpData, MAX_PATH);
            lpcbData = MAX_PATH;

        }
        ::RegCloseKey(hKey);

        return TRUE;
    }

    return FALSE;
}

//This function coded by Fance,used to split the cstring to each part.
void SplitCStringA(CStringArray &saArray, CString sSource, CString sToken,BOOL Skip_Token)
{
    CString sTempSource, sTempSplitted;

    sTempSource = sSource;

    int nPos = sTempSource.Find(sToken);

    //--if there are no token in the string, then add itself and return.
    if(nPos == -1)
        saArray.Add(sTempSource);
    else
    {
        while(sTempSource.GetLength() > 0)
        {
            nPos = sTempSource.Find(sToken);
            if(nPos == -1)
            {
                saArray.Add(sTempSource.Trim());
                break;
            }
            else if(nPos == 0&&Skip_Token)
            {
                sTempSource = sTempSource.Mid(sToken.GetLength(), sTempSource.GetLength());
                continue;
            }
            else
            {
                sTempSplitted = sTempSource.Mid(0, nPos);
                saArray.Add(sTempSplitted.Trim());
                sTempSource = sTempSource.Mid(nPos + sToken.GetLength(), sTempSource.GetLength());
            }
        }
    }

}


CString GetProductName(int ModelID)
{
    CString strProductName;
    switch(ModelID)
    {
    case PM_TSTAT5A:
        strProductName="TStat5A";
        break;
    case PM_TSTAT5B:
        strProductName="TStat5B";
        break;
    case PM_TSTAT5B2:
        strProductName="TStat5B2";
        break;
    case PM_TSTAT5C:
        strProductName="TStat5C";
        break;
    case PM_TSTAT5D:
        strProductName="TStat5D";
        break;
    case PM_TSTAT5E:
        strProductName="TStat5E";
        break;
    case PM_TSTAT5F:
        strProductName="TStat5F";
        break;
    case PM_TSTAT5G:
        strProductName="TStat5G";
        break;
    case PM_TSTAT5H:
        strProductName="TStat5H";
        break;
    case PM_TSTAT6:
        strProductName="TStat6";
        break;
    case PM_TSTAT5i:
        strProductName="TStat5i";
        break;
    case PM_HUMTEMPSENSOR:
        strProductName="TstatHUM";
        break;
    case PM_AirQuality:
        strProductName="Air Quality";
        break;
    case PM_TSTAT7:
        strProductName="TStat7";
        break;
    case PM_NC:
        strProductName="NC";
        break;
    case PM_CM5:
        strProductName ="CM5";
        break;
    case PM_TSTATRUNAR:
        strProductName="TStatRunar";
        break;
    //20120424
    case PM_LightingController:
        strProductName = "LC";
        break;
    case  PM_CO2_NET:
        strProductName = "CO2 Net";
        break;
    case  PM_CO2_RS485:
        strProductName = "CO2";
        break;
    case  PM_CO2_NODE:
        strProductName = "CO2 Node";
        break;

    case PM_TSTAT6_HUM_Chamber:
        strProductName =g_strHumChamber;
        break;

    case PM_T3PT10 :
        strProductName="T3-PT10";
        break;
    case PM_T3IOA :
        strProductName="T3-8IOA";
        break;
    case PM_T332AI :
        strProductName="T3-32AI";
        break;
    case  PM_T38AI16O :
        strProductName="T3-8AI160";
        break;
    case PM_T38I13O :
        strProductName="T3-8I13O";
        break;
    case PM_T3PERFORMANCE :
        strProductName="T3-Performance";
        break;
    case PM_T34AO :
        strProductName="T3-4AO";
        break;
    case PM_T36CT :
        strProductName="T3-6CT";
        break;
    case PM_MINIPANEL:
        strProductName="MiniPanel";
        break;
    case PM_PRESSURE:
        strProductName="Pressure Sensor";
        break;
    case PM_HUM_R:
        strProductName="HUM-R";
        break;
    case PM_T322AI:
        strProductName="T3-22AI";
        break;
    case PM_T38AI8AO6DO:
        strProductName="T3-8AI8AO6DO";
        break;
    default:
        strProductName="";
        break;
    }
    return strProductName;
}


CString Get_Table_Name(int SerialNo,CString Type ,int Row)
{
    //	CADO ado;
    CString Table_Name;
    //ado.OnInitADOConn();
    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();

    if (bado.IsHaveTable(bado,_T("IONAME_CONFIG")))//有Version表
    {
        CString sql;
        sql.Format(_T("Select * from IONAME_CONFIG where Type='%s' and  Row=%d and SerialNo=%d"),Type.GetBuffer(),Row,SerialNo);
        bado.m_pRecordset=bado.OpenRecordset(sql);
        if (!bado.m_pRecordset->EndOfFile)//有表但是没有对应序列号的值
        {
            bado.m_pRecordset->MoveFirst();
            while (!bado.m_pRecordset->EndOfFile)
            {
                Table_Name=bado.m_pRecordset->GetCollect(_T("InOutName"));
                bado.m_pRecordset->MoveNext();
            }
        }
        else
        {
            Table_Name.Format(_T("%s%d"),Type.GetBuffer(),Row);
        }
    }
    else
    {
        Table_Name.Format(_T("%s%d"),Type.GetBuffer(),Row);
    }
    bado.CloseRecordset();
    bado.CloseConn();
    return Table_Name;
}
void    Insert_Update_Table_Name(int SerialNo,CString Type,int Row,CString TableName)
{
    CBADO ado;
    ado.SetDBPath(g_strCurBuildingDatabasefilePath);
    ado.OnInitADOConn();
    CString sql;
    sql.Format(_T("Select * from IONAME_CONFIG where Type='%s' and  Row=%d and SerialNo=%d"),Type.GetBuffer(),Row,SerialNo);
    ado.m_pRecordset=ado.OpenRecordset(sql);

    if (!ado.m_pRecordset->EndOfFile)//有表但是没有对应序列号的值
    {

        sql.Format(_T("update IONAME_CONFIG set InOutName = '%s' where Type='%s' and  Row=%d and SerialNo=%d "),TableName.GetBuffer(),Type.GetBuffer(),Row,SerialNo);
        ado.m_pConnection->Execute(sql.GetString(),NULL,adCmdText);
    }
    else
    {
        ado.CloseRecordset();
        sql.Format(_T("Insert into IONAME_CONFIG(InOutName,Type,Row,SerialNo) values('%s','%s','%d','%d')"),TableName.GetBuffer(),Type.GetBuffer(),Row,SerialNo);
        ado.m_pConnection->Execute(sql.GetString(),NULL,adCmdText);
    }

    ado.CloseConn();
}

int Get_Unit_Process(CString Unit)
{
    int ret_Value=1;
    if (Unit.CompareNoCase(_T("RAW DATA"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("TYPE2 10K C"))==0)
    {
        ret_Value=10;
    }
    else if (Unit.CompareNoCase(_T("TYPE2 10K F"))==0)
    {
        ret_Value=10;
    }
    else if (Unit.CompareNoCase(_T("0-100%"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("ON/OFF"))==0)
    {
        ret_Value=1;
    }

    else if (Unit.CompareNoCase(_T("OFF/ON"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("Pulse Input"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("Lighting Control"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("TYPE3 10K C"))==0)
    {
        ret_Value=10;
    }
    else if (Unit.CompareNoCase(_T("TYPE3 10K F"))==0)
    {
        ret_Value=10;
    }
    else if (Unit.CompareNoCase(_T("NO USE"))==0)
    {
        ret_Value=1;
    }
    else if (Unit.CompareNoCase(_T("0-5V"))==0)
    {
        ret_Value=1000;
    }
    else if (Unit.CompareNoCase(_T("0-10V"))==0)
    {
        ret_Value=1000;
    }
    else if (Unit.CompareNoCase(_T("0-20ma"))==0)
    {
        ret_Value=1000;
    }



    return ret_Value;
}


BOOL Get_Bit_FromRegister(unsigned short RegisterValue,unsigned short Position)
{

    int postionvalue=1;
    postionvalue=postionvalue<<(Position-1);
    postionvalue= RegisterValue&postionvalue;
    BOOL ret=postionvalue>>(Position-1);
    return ret;
}



char * intervaltotext(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c)
{
    char buf[12], *textbuffer;
    char *separator = c ;
    textbuffer = buf;
    if( seconds < 0 )
    {
        seconds = -seconds;
        strcpy(textbuffer++, "-" ) ;        /* add the '-' */
    }
    if(*c!='-')
    {
        hours += seconds/3600;
        minutes += (unsigned)(seconds%3600)/60;
        seconds = (unsigned)(seconds%3600)%60;
    }
    if( hours < 10 )
    {
        strcpy(textbuffer++, "0" ) ;        /* add the leading zero 0#:##:## */
    }
    itoa(hours,textbuffer,10) ;
    textbuffer += strlen(textbuffer);
    strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/

    if( minutes < 10 )
    {
        strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:0#:## */
    }
    itoa(minutes,textbuffer,10) ;
    textbuffer += strlen(textbuffer);
    //strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/
    //if( seconds < 10 ) {
    //	strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:##:0# */
    //}
    //itoa(seconds,textbuffer,10)  ;

    if(textbuf) strcpy(textbuf, buf);
    //return( buf ) ;
    return NULL;
}

char * intervaltotextfull(char *textbuf, long seconds , unsigned minutes , unsigned hours, char *c)
{
    char buf[12], *textbuffer;
    char *separator = c ;
    textbuffer = buf;
    if( seconds < 0 )
    {
        seconds = -seconds;
        strcpy(textbuffer++, "-" ) ;        /* add the '-' */
    }
    if(*c!='-')
    {
        hours += seconds/3600;
        minutes += (unsigned)(seconds%3600)/60;
        seconds = (unsigned)(seconds%3600)%60;
    }
    if( hours < 10 )
    {
        strcpy(textbuffer++, "0" ) ;        /* add the leading zero 0#:##:## */
    }
    itoa(hours,textbuffer,10) ;
    textbuffer += strlen(textbuffer);
    strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/

    if( minutes < 10 )
    {
        strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:0#:## */
    }
    itoa(minutes,textbuffer,10) ;
    textbuffer += strlen(textbuffer);
    strcpy(textbuffer++, separator ) ;        /* add the ":" separator*/
    if( seconds < 10 )
    {
        strcpy(textbuffer++, "0" ) ;        /* add the leading zero ##:##:0# */
    }
    itoa(seconds,textbuffer,10)  ;

    if(textbuf) strcpy(textbuf, buf);
    return( buf ) ;
}

 

 
 
 

 
 
 
 

//This function add by Fance Du, used for changed the CString to hex
//2013 12 02
//Ex: "0F" -> 15
unsigned char Str_to_Byte(CString need_conver)
{
    int the_first=0;
    int the_second=0;
    switch (need_conver.GetAt(0))
    {
    case 0x30:
        the_first=0;
        break;
    case 0x31:
        the_first=1;
        break;
    case 0x32:
        the_first=2;
        break;
    case 0x33:
        the_first=3;
        break;
    case 0x34:
        the_first=4;
        break;
    case 0x35:
        the_first=5;
        break;
    case 0x36:
        the_first=6;
        break;
    case 0x37:
        the_first=7;
        break;
    case 0x38:
        the_first=8;
        break;
    case 0x39:
        the_first=9;
        break;
    case 0x41:
        the_first=10;
        break;
    case 0x42:
        the_first=11;
        break;
    case 0x43:
        the_first=12;
        break;
    case 0x44:
        the_first=13;
        break;
    case 0x45:
        the_first=14;
        break;
    case 0x46:
        the_first=15;
        break;
    default:
        the_first = 0;
        break;
    }
    switch (need_conver.GetAt(1))
    {
    case 0x30:
        the_second=0;
        break;
    case 0x31:
        the_second=1;
        break;
    case 0x32:
        the_second=2;
        break;
    case 0x33:
        the_second=3;
        break;
    case 0x34:
        the_second=4;
        break;
    case 0x35:
        the_second=5;
        break;
    case 0x36:
        the_second=6;
        break;
    case 0x37:
        the_second=7;
        break;
    case 0x38:
        the_second=8;
        break;
    case 0x39:
        the_second=9;
        break;
    case 0x41:
        the_second=10;
        break;
    case 0x42:
        the_second=11;
        break;
    case 0x43:
        the_second=12;
        break;
    case 0x44:
        the_second=13;
        break;
    case 0x45:
        the_second=14;
        break;
    case 0x46:
        the_second=15;
        break;
    default:
        the_second = 0;
        break;
    }
    return (the_first*16+the_second);
}


extern char local_network_ip[255];
extern CString local_enthernet_ip;
//socket dll.
bool Open_bacnetSocket2(CString strIPAdress,short nPort,SOCKET &mysocket)
{

    int nNetTimeout=3000;//1 second.
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);

    //if (m_hSocket!=INVALID_SOCKET)
    //{
    //	::closesocket(m_hSocket);
    //	m_hSocket=NULL;
    //}

    if(::WSAStartup(sockVersion, &wsaData) != 0)
    {
        //AfxMessageBox(_T("Init Socket failed!"));
        //	m_hSocket=NULL;
        return FALSE;
    }

    //	mysocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    mysocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(mysocket == INVALID_SOCKET)
    {
        //	AfxMessageBox(_T("Create socket failed!"));
        mysocket=NULL;
        return FALSE;
    }
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(nPort);
    if(local_enthernet_ip.IsEmpty())
        servAddr.sin_addr.s_addr = INADDR_ANY;
    else
        servAddr.sin_addr.s_addr =  inet_addr(local_network_ip);

    USES_CONVERSION;


    int bind_ret =	bind(mysocket, (struct sockaddr*)&servAddr, sizeof(servAddr));
    //if(bind_ret<0)
    //{
    //	//AfxMessageBox(_T("Locol port 47808 is not valiable"));

    //}


    //char pTemp[20];
    //pTemp=W2A(strIPAdress);


    //servAddr.sin_addr.S_un.S_addr =inet_addr("192.168.0.28");
    //	servAddr.sin_addr.S_un.S_addr =inet_addr((LPSTR)(LPCTSTR)strIPAdress);
    servAddr.sin_addr.S_un.S_addr = (inet_addr(W2A(strIPAdress)));
    //	u_long ul=1;
    //	ioctlsocket(m_hSocket,FIONBIO,(u_long*)&ul);

    setsockopt(mysocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));

    setsockopt(mysocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));


    BOOL bBroadcast=TRUE;
    setsockopt(mysocket,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));


    //char ABC[10];
    //ABC[0]=0X11;
    //ABC[1]=0X22;
    //sendto(mysocket,ABC,2,NULL,(struct sockaddr *) &servAddr,sizeof(sockaddr));
    //if(::connect(mysocket,(sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    //{
    //	DWORD dwErr = WSAGetLastError();
    //	//AfxMessageBox(_T(" Failed connect() \n"));
    //	::closesocket(mysocket);
    //	mysocket=NULL;
    //	return FALSE;
    //}
    return TRUE;
}

#define MAX_STRING	100	// should be enough for everone (-:




int GetHostAdaptersInfo(CString &IP_address_local)
{
    CString szAdaptersInfo;
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    /* variables used to print DHCP time info */

    pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    // Make an initial call to GetAdaptersInfo to get
    // the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
        if (pAdapterInfo == NULL)
        {
            return -1;
        }
    }
    int i_CntAdapters = 0;
    CString szTmp;
    if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            szTmp.Format(_T("adapter name: %s "),pAdapter->AdapterName);
            szAdaptersInfo += szTmp;
            szTmp.Format(_T("adapter description: %s "),pAdapter->Description);
            szAdaptersInfo += szTmp;
            szTmp.Format(_T("adapter address: "));
            szAdaptersInfo += szTmp;
            for (UINT i = 0; i < pAdapter->AddressLength; i++)
            {
                if (i == (pAdapter->AddressLength - 1))
                {
                    szTmp.Format(_T("%.2X "),(int)pAdapter->Address[i]);
                    szAdaptersInfo += szTmp;
                }
                else
                {
                    szTmp.Format(_T("%.2X-"),(int)pAdapter->Address[i]);
                    szAdaptersInfo += szTmp;
                }
            }
            szTmp.Format(_T("ip address: %s "),pAdapter->IpAddressList.IpAddress.String);
            szAdaptersInfo += szTmp;
            szTmp.Format(_T("ip mask: %s "),pAdapter->IpAddressList.IpMask.String);
            szAdaptersInfo += szTmp;
            szTmp.Format(_T("gateway: %s "),pAdapter->GatewayList.IpAddress.String);
            szAdaptersInfo += szTmp;

            szTmp.Format(_T("type: %d "),pAdapter->Type);
            szAdaptersInfo += szTmp;
            if(pAdapter->Type == 6)
            {
                IP_address_local.Empty();
                MultiByteToWideChar( CP_ACP,0,(char *)pAdapter->IpAddressList.IpAddress.String, (int)strlen((char *)pAdapter->IpAddressList.IpAddress.String)+1,
                                     IP_address_local.GetBuffer(MAX_PATH), MAX_PATH );
                IP_address_local.ReleaseBuffer();
                break;

                //IP_address_local.fo
            }

            szTmp.Format(_T("index: %d "),pAdapter->Index);
            szAdaptersInfo += szTmp;

            pAdapter = pAdapter->Next;
            i_CntAdapters++;
        }
    }
    else
    {
        if (pAdapterInfo)
            free(pAdapterInfo);
        return -1;
    }
    szTmp.ReleaseBuffer();
    return i_CntAdapters;
}



void GetIPMaskGetWay()
{
    g_Vector_Subnet.clear();
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen;
    pAdapterInfo=(PIP_ADAPTER_INFO)malloc(sizeof(IP_ADAPTER_INFO));
    ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    ALL_LOCAL_SUBNET_NODE  Temp_Node;
    // 第一次调用GetAdapterInfo获取ulOutBufLen大小
    if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
    }

    if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            //             CString Name;//=pAdapter->AdapterName;
            // 			MultiByteToWideChar( CP_ACP, 0, pAdapter->AdapterName, (int)strlen((char *)pAdapter->AdapterName)+1,
            // 				Name.GetBuffer(MAX_PATH), MAX_PATH );
            // 			Name.ReleaseBuffer();

            MultiByteToWideChar( CP_ACP, 0, pAdapter->IpAddressList.IpAddress.String, (int)strlen((char *)pAdapter->IpAddressList.IpAddress.String)+1,
                                 Temp_Node.StrIP.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrIP.ReleaseBuffer();
            //StrIP.Format(_T("%s"),pAdapter->IpAddressList.IpAddress.String);
            MultiByteToWideChar( CP_ACP, 0,pAdapter->IpAddressList.IpMask.String, (int)strlen((char *)pAdapter->IpAddressList.IpMask.String)+1,
                                 Temp_Node.StrMask.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrMask.ReleaseBuffer();

            //StrMask.Format(_T("%s"), pAdapter->IpAddressList.IpMask.String);

            MultiByteToWideChar( CP_ACP, 0,pAdapter->GatewayList.IpAddress.String, (int)strlen((char *)pAdapter->GatewayList.IpAddress.String)+1,
                                 Temp_Node.StrGetway.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrGetway.ReleaseBuffer();

            Temp_Node.NetworkCardType=pAdapter->Type;

            g_Vector_Subnet.push_back(Temp_Node);

            /*StrGetway.Format(_T("%s"), pAdapter->GatewayList.IpAddress.String); */
            pAdapter = pAdapter->Next;
        }
    }
    else
    {

    }
}

 
BOOL Is_Dig_Num(CString str)
{
    int n=str.GetLength();
    for(int i=0; i<n; i++)
        if (str[i]<'0'||str[i]>'9')
            return FALSE;
    return TRUE;
}

BOOL ValidAddress(CString sAddress)
{
    int nPos;
    UINT n1,n2,n3,n4;
    CString sTemp=sAddress;
    n1=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);

    n2=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);
    n3=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);
    n4=_wtoi(sTemp);
    if(n1<0 ||n1>255) return false;
    if(n2<0 ||n2>255) return false;
    if(n3<0 ||n3>255) return false;
    if(n4<0 ||n4>255) return false;
    return TRUE;
}


void GetIPMaskGetWayForScan()
{
    g_Scan_Vector_Subnet.clear();
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen;
    pAdapterInfo=(PIP_ADAPTER_INFO)malloc(sizeof(IP_ADAPTER_INFO));
    ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    ALL_LOCAL_SUBNET_NODE  Temp_Node;
    // 第一次调用GetAdapterInfo获取ulOutBufLen大小
    if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
    }

    if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {
            //             CString Name;//=pAdapter->AdapterName;
            // 			MultiByteToWideChar( CP_ACP, 0, pAdapter->AdapterName, (int)strlen((char *)pAdapter->AdapterName)+1,
            // 				Name.GetBuffer(MAX_PATH), MAX_PATH );
            // 			Name.ReleaseBuffer();

            MultiByteToWideChar( CP_ACP, 0, pAdapter->IpAddressList.IpAddress.String, (int)strlen((char *)pAdapter->IpAddressList.IpAddress.String)+1,
                                 Temp_Node.StrIP.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrIP.ReleaseBuffer();
            //StrIP.Format(_T("%s"),pAdapter->IpAddressList.IpAddress.String);
            MultiByteToWideChar( CP_ACP, 0,pAdapter->IpAddressList.IpMask.String, (int)strlen((char *)pAdapter->IpAddressList.IpMask.String)+1,
                                 Temp_Node.StrMask.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrMask.ReleaseBuffer();

            //StrMask.Format(_T("%s"), pAdapter->IpAddressList.IpMask.String);

            MultiByteToWideChar( CP_ACP, 0,pAdapter->GatewayList.IpAddress.String, (int)strlen((char *)pAdapter->GatewayList.IpAddress.String)+1,
                                 Temp_Node.StrGetway.GetBuffer(MAX_PATH), MAX_PATH );
            Temp_Node.StrGetway.ReleaseBuffer();

            Temp_Node.NetworkCardType=pAdapter->Type;

            g_Scan_Vector_Subnet.push_back(Temp_Node);

            /*StrGetway.Format(_T("%s"), pAdapter->GatewayList.IpAddress.String); */
            pAdapter = pAdapter->Next;
        }
    }
    else
    {

    }
}



 





bool IP_is_Local(LPCTSTR ip_address)
{

    IP_ADAPTER_INFO pAdapterInfo;
    ULONG len = sizeof(pAdapterInfo);
    if(GetAdaptersInfo(&pAdapterInfo, &len) != ERROR_SUCCESS)
    {
        return 0;
    }
    long nLocalIP=inet_addr(pAdapterInfo.IpAddressList.IpAddress.String);
    DWORD dw_ip = htonl(nLocalIP);

    CString temp_ip;
    temp_ip.Format(_T("%s"),ip_address);
    char tempchar[200];
    memset(tempchar,0,200);
    WideCharToMultiByte(CP_ACP,0,temp_ip.GetBuffer(),-1,tempchar,200,NULL,NULL);

    DWORD m_dwClientIP = inet_addr((char *)tempchar);

    BYTE byIP[4];
    for (int i = 0, ic = 3; i < 4; i++,ic--)
    {
        byIP[i] = (dw_ip >> ic*8)&0x000000FF;
    }

    BYTE byISPDeviceIP[4];
    DWORD dwClientIP = m_dwClientIP;
    ZeroMemory(byISPDeviceIP,4);
    for (int i = 0, ic = 3; i < 4; i++,ic--)
    {
        byISPDeviceIP[3-i] = (dwClientIP >> ic*8)&0x000000FF;
    }
    if(memcmp(byIP,byISPDeviceIP,3)==0)
    {
        return true;
    }

    //memcpy_s(byIP,3,byISPDeviceIP,3)
    return false;
}

// 执行程序的路径 // 参数  // 执行环境目录   // 最大等待时间, 超过这个时间强行终止;
DWORD WinExecAndWait( LPCTSTR lpszAppPath,LPCTSTR lpParameters,LPCTSTR lpszDirectory, 	DWORD dwMilliseconds)
{
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize    = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask    = SEE_MASK_NOCLOSEPROCESS;
    //ShExecInfo.fMask    = SEE_MASK_HMONITOR;
    ShExecInfo.hwnd        = NULL;
    ShExecInfo.lpVerb    = NULL;
    ShExecInfo.lpFile    = lpszAppPath;
    ShExecInfo.lpParameters = lpParameters;
    ShExecInfo.lpDirectory    = lpszDirectory;
    ShExecInfo.nShow    = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    if(dwMilliseconds==0)
    {
        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);  //等待进程退出，才继续运行;
    }
    else if (dwMilliseconds!=0 && WaitForSingleObject(ShExecInfo.hProcess, dwMilliseconds) == WAIT_TIMEOUT)  	// 指定时间没结束;
    {
        // 强行杀死进程;
        TRACE(_T("TerminateProcess        %s"),lpszAppPath);
        TerminateProcess(ShExecInfo.hProcess, 0);
        return 0;    //强行终止;
    }

    DWORD dwExitCode;
    BOOL bOK = GetExitCodeProcess(ShExecInfo.hProcess, &dwExitCode);
    ASSERT(bOK);

    return dwExitCode;
}




BOOL KillProcessFromName(CString strProcessName)
{
    //创建进程快照(TH32CS_SNAPPROCESS表示创建所有进程的快照)

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);



    //PROCESSENTRY32进程快照的结构体

    PROCESSENTRY32 pe;



    //实例化后使用Process32First获取第一个快照的进程前必做的初始化操作

    pe.dwSize = sizeof(PROCESSENTRY32);





    //下面的IF效果同:

    //if(hProcessSnap == INVALID_HANDLE_VALUE)   无效的句柄

    if(!Process32First(hSnapShot,&pe))

    {

        return FALSE;

    }



    //将字符串转换为小写

    strProcessName.MakeLower();



    //如果句柄有效  则一直获取下一个句柄循环下去

    while (Process32Next(hSnapShot,&pe))

    {



        //pe.szExeFile获取当前进程的可执行文件名称

        CString scTmp = pe.szExeFile;





        //将可执行文件名称所有英文字母修改为小写

        scTmp.MakeLower();



        //比较当前进程的可执行文件名称和传递进来的文件名称是否相同

        //相同的话Compare返回0

        if(!scTmp.Compare(strProcessName))

        {



            //从快照进程中获取该进程的PID(即任务管理器中的PID)

            DWORD dwProcessID = pe.th32ProcessID;

            HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);

            ::TerminateProcess(hProcess,0);

            CloseHandle(hProcess);

            return TRUE;

        }

        scTmp.ReleaseBuffer();

    }

    strProcessName.ReleaseBuffer();

    return FALSE;

}




BOOL DirectoryExist(CString Path)
{
    WIN32_FIND_DATA fd;
    BOOL ret = FALSE;
    HANDLE hFind = FindFirstFile(Path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        //目录存在
        ret = TRUE;

    }
    FindClose(hFind);
    return ret;
}

 


BOOL CreateDirectory(CString path)
{
    SECURITY_ATTRIBUTES attrib;
    attrib.bInheritHandle = FALSE;
    attrib.lpSecurityDescriptor = NULL;
    attrib.nLength = sizeof(SECURITY_ATTRIBUTES);

    return CreateDirectory( path, &attrib);
}
#if 1
BOOL DeleteDirectory(CString path)
{

    CFileFind finder;
    CString temppath;
    temppath=path;
    //temppath.Format("%s/*.*",path);
    BOOL ret;
    //temppath.Format(_T("%s*.*",path));
    temppath += "\\*.*";

    BOOL bWorking = finder.FindFile(temppath);
    ret=bWorking;
    while(bWorking)
    {
        bWorking = finder.FindNextFile();
        //ret=bWorking;
        if(finder.IsDirectory() && !finder.IsDots()) //处理文件夹
        {
            DeleteDirectory(finder.GetFilePath()); //递归删除文件夹
            RemoveDirectory(finder.GetFilePath());
        }
        else //处理文件
        {
            DeleteFile(finder.GetFilePath());
        }
    }
    RemoveDirectory(path);
    return ret;
}
#endif




void TraverseFolder( const CString& strDir,std::vector<CString>& vecFile)
{
    WIN32_FIND_DATA FindFileData;
    CString strDirTmp;
    strDirTmp = strDir;
    strDirTmp += "\\*.*";
    HANDLE hFind=::FindFirstFile(strDirTmp,&FindFileData);
    if(INVALID_HANDLE_VALUE == hFind)
    {

        return;
    }
    while(TRUE)
    {
        if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
        {
            if (FindFileData.cFileName[0]!=L'.')
            {
                strDirTmp=strDir;
                //  strDirTmp+="\\";
                strDirTmp+=FindFileData.cFileName;
                TraverseFolder(strDirTmp,vecFile);
            }
            // 				else
            // 				{
            // 					strDirTmp=strDir;
            // 					strDirTmp+="\\";
            // 					strDirTmp+=FindFileData.cFileName;
            // 					TraverseFolder(strDirTmp,vecFile);
            // 				}
        }
        else
        {
            strDirTmp=strDir;
            strDirTmp+=L"\\";
            strDirTmp+=FindFileData.cFileName;
            //TraverseFolder(strDirTmp,vecFile);
            vecFile.push_back(strDirTmp);
        }
        if (!FindNextFile(hFind,&FindFileData))
        {
            break;
        }
    }
    FindClose(hFind);
}

bool GetFileNameFromPath(CString ncstring,CString &cs_return)
{
    CStringArray ntemparray;
    SplitCStringA(ntemparray,ncstring,_T("\\"));
    int find_results = 0;
    find_results = ntemparray.GetSize();
    if(find_results>=2)
    {
        cs_return = ntemparray.GetAt(find_results - 1);
        return true;
    }
    return false;
}


void DFTrace(LPCTSTR lpCString)
{
    CString nCString;
    nCString = lpCString;
    static int count = 0;
    CTime print_time=CTime::GetCurrentTime();
    CString str=print_time.Format("%H:%M:%S    ");

    PrintText[count].Empty();
    PrintText[count] =str + nCString;
    PostMessage(h_debug_window,WM_ADD_DEBUG_CSTRING,(WPARAM)PrintText[count].GetBuffer(),NULL);
    count = (count ++) % 900;

}

CString GetContentFromURL(CString URL)
{
    CString strHtml;
    CInternetSession sess;
    CHttpFile* pHttpFile = NULL;
    try
    {
        pHttpFile = (CHttpFile*)sess.OpenURL(URL.GetBuffer());
        char sRecived[1024];
        if(pHttpFile)
        {
            while(pHttpFile->ReadString((LPTSTR)sRecived, 1024)) //解决Cstring乱码
            {
                CString temp(sRecived);
                strHtml += temp;
            }
        }

    }

    catch (CException* e)
    {
        strHtml=_T("");
    }



    return strHtml;
}
CString GetProductFirmwareTimeFromTemcoWebsite(CString URL,CString HexOrBinName,CString &FileSize)
{
    CString ftp_T3000Version;
    ftp_T3000Version=GetContentFromURL(URL);
    CStringArray HtmlArray;
    CString VersionString;
    if (ftp_T3000Version.GetLength()<=1)
    {
        return VersionString;
    }
    HtmlArray.RemoveAll();
    SplitCStringA(HtmlArray,ftp_T3000Version,_T("<hr>"));
    CString ImageString;
    if (HtmlArray.GetSize()>1)
    {
        ImageString=HtmlArray[1];
        HtmlArray.RemoveAll();
        SplitCStringA(HtmlArray,ImageString,_T("<img"));
        ImageString.Empty();
        for (int i=0; i<HtmlArray.GetSize(); i++)
        {
            if (HtmlArray[i].Find(HexOrBinName)!=-1)
            {
                ImageString=HtmlArray[i];
                break;
            }
        }

        HtmlArray.RemoveAll();

        if(ImageString.GetLength()>1)
        {
            SplitCStringA(HtmlArray,ImageString,_T("</a>"));
        }
        if(HtmlArray.GetSize()>0)
        {
            ImageString=HtmlArray[1];
        }
        //               20-Nov-2014 00:36  152K
        ImageString.TrimLeft();
        ImageString.TrimRight();
        HtmlArray.RemoveAll();
        if(ImageString.GetLength()>1)
        {
            SplitCStringA(HtmlArray,ImageString,_T("  "));
        }
        if (HtmlArray.GetSize()>0)
        {
            VersionString=HtmlArray[0];
            FileSize=HtmlArray[1];
        }

    }

    return VersionString;
}

BOOL CheckTheSameSubnet(CString strIP ,CString strIP2)
{
    BOOL ret=FALSE;
    USES_CONVERSION;
    LPCSTR szIP = W2A(strIP);
    DWORD dwIP = inet_addr(szIP);
    IN_ADDR ia,sa;
    ia.S_un.S_addr = dwIP;



    szIP=W2A(strIP2);
    dwIP=inet_addr(szIP);
    sa.S_un.S_addr=dwIP;

    if ( ia.S_un.S_un_b.s_b1 == sa.S_un.S_un_b.s_b1 &&
            ia.S_un.S_un_b.s_b2 == sa.S_un.S_un_b.s_b2 &&
            ia.S_un.S_un_b.s_b3 == sa.S_un.S_un_b.s_b3
       )
    {
        ret=TRUE;
    }



    return ret;

}


CString GetExePath(bool bHasSlash)
{
    TCHAR	szBuf[MAX_PATH];
    GetModuleFileName(NULL,szBuf,MAX_PATH);

    CString	strPath(szBuf);
    int idx = strPath.ReverseFind(_T('\\'));
    strPath = strPath.Left(idx);

    if(bHasSlash)  // has '\' at last.
    {
        if(strPath.Right(1)!=_T('\\'))
            strPath+=_T('\\');
        return strPath;
    }
    else   // don't need '\'.
    {
        if(strPath.Right(1)==_T('\\'))
            strPath.TrimRight(_T('\\'));
        return strPath;
    }
}


 
//////////////////////////////////////////////////////////////////////////
//这里改成用Minipanel的界面
//LoadTstat_功能Data的函数都是把数据解析到一个Vector容器里面
//在界面下面只要把这些数据填充到对于的表里面即可
//结构中包含了对应的 寄存器地址，寄存器值，寄存器对应意义的字符串值
// Author:Alex
//这要这里解析的正确，后面界面操作，对应的也是正确的
//只要不需要关心寄存器地址等
//
//
//
//////////////////////////////////////////////////////////////////////////
void LoadTstat_InputData()
{
    m_tstat_input_data.clear();
    int m_cvalue=0;
    int m_crange=0;
    long m_sn=0;
    CString strAuto=_T("Auto");
    CString strman=_T("Manual");
    m_tstat_input_data.clear();
    Tstat_Input_Struct temp_tstat_input;
    CString strTemp;
    m_sn=product_register_value[0]+product_register_value[1]*256+product_register_value[2]*256*256+product_register_value[3]*256*256*256;
    int	m_nModel=product_register_value[MODBUS_PRODUCT_MODEL];
    int Product_Type=product_register_value[7];
    if((Product_Type!=PM_TSTAT6)&&(Product_Type!=PM_TSTAT5i)&&(Product_Type!=PM_TSTAT7))
    {
        return;
    }
#if 1//  g_strSensorName
    strTemp.Format(_T("%.1f"),product_register_value[MODBUS_INTERNAL_THERMISTOR]/10.0);//216
    temp_tstat_input.InputName.StrValue=g_strSensorName;
    temp_tstat_input.Value.StrValue=strTemp;
    temp_tstat_input.Value.regAddress=MODBUS_INTERNAL_THERMISTOR;
    temp_tstat_input.Value.RegValue=product_register_value[MODBUS_INTERNAL_THERMISTOR];
    CString strUnit=GetTempUnit();
    temp_tstat_input.Unit.StrValue=strUnit;
    temp_tstat_input.AM.regAddress=695;
    temp_tstat_input.AM.RegValue=product_register_value[695];
    if (product_register_value[695]!=0)
    {
        temp_tstat_input.AM.StrValue=strman;
        //m_FlexGrid.put_TextMatrix(1,AM_FIELD,_T("Manual"));
    }
    else
    {
        temp_tstat_input.AM.StrValue=strAuto;
        //m_FlexGrid.put_TextMatrix(1,AM_FIELD,_T("Auto"));
    }
    temp_tstat_input.Range.StrValue=strUnit;
    temp_tstat_input.Range.regAddress=MODBUS_DEGC_OR_F;
    temp_tstat_input.Range.RegValue=product_register_value[MODBUS_DEGC_OR_F];
    temp_tstat_input.Function.StrValue=NO_APPLICATION;
    //temp_tstat_input.Filter.StrValue=NO_APPLICATION;
    temp_tstat_input.Filter.regAddress=142;
    temp_tstat_input.Filter.RegValue=product_register_value[142];
    temp_tstat_input.Filter.StrValue.Format(_T("%d"),product_register_value[142]);

    temp_tstat_input.CustomTable.StrValue=NO_APPLICATION;
    m_tstat_input_data.push_back(temp_tstat_input);
#endif

#if 1//初始化InputName
    strTemp=GetTextFromReg(MODBUS_AI1_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();
    if (!strTemp.IsEmpty())
    {
        g_strInName1.Format(_T("AI1:%s"),strTemp);

    }
    else
    {
        g_strInName1=_T("AI1:Input1");
        strTemp=_T("Input1");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI1_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);

    strTemp.Empty();

    strTemp=GetTextFromReg(MODBUS_AI2_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (!strTemp.IsEmpty())
    {
        g_strInName2.Format(_T("AI2:%s"),strTemp);

    }
    else
    {
        g_strInName2=_T("AI2:Input2");
        strTemp =  _T("Input2");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI2_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();

    strTemp=GetTextFromReg(MODBUS_AI3_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (!strTemp.IsEmpty())
    {
        g_strInName3.Format(_T("AI3:%s"),strTemp);

    }
    else
    {
        g_strInName3=_T("AI3:Input3");
        strTemp =_T("Input3");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI3_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    strTemp=GetTextFromReg(MODBUS_AI4_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (!strTemp.IsEmpty())
    {
        g_strInName4.Format(_T("AI4:%s"),strTemp);

    }
    else
    {
        g_strInName4=_T("AI4:Input4");
        strTemp =_T("Input4");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI4_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    strTemp=GetTextFromReg(MODBUS_AI5_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();


    if (!strTemp.IsEmpty())
    {
        g_strInName5.Format(_T("AI5:%s"),strTemp);

    }
    else
    {
        g_strInName5=_T("AI5:Input5");
        strTemp   =_T("Input5");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI5_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    strTemp=GetTextFromReg(MODBUS_AI6_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();


    if (!strTemp.IsEmpty())
    {
        g_strInName6.Format(_T("AI6:%s"),strTemp);

    }
    else
    {
        g_strInName6=_T("AI6:Input6");
        strTemp = _T("Input6");
    }

    temp_tstat_input.InputName.regAddress=MODBUS_AI6_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    strTemp=GetTextFromReg(MODBUS_AI7_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (!strTemp.IsEmpty())
    {
        g_strInName7.Format(_T("AI7:%s"),strTemp);

    }
    else
    {
        g_strInName7=_T("AI7:Input7");
        strTemp =_T("Input7");
    }
    temp_tstat_input.InputName.regAddress=MODBUS_AI7_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    strTemp=GetTextFromReg(MODBUS_AI8_CHAR1);
    strTemp.TrimLeft();
    strTemp.TrimRight();

    if (!strTemp.IsEmpty())
    {
        g_strInName8.Format(_T("AI8:%s"),strTemp);

    }
    else
    {
        g_strInName8=_T("AI8:Input8");
        strTemp = _T("Input8");
    }
    temp_tstat_input.InputName.regAddress=MODBUS_AI8_CHAR1;
    temp_tstat_input.InputName.StrValue=strTemp;
    m_tstat_input_data.push_back(temp_tstat_input);
    strTemp.Empty();
    temp_tstat_input.InputName.StrValue=g_strInHumName;
    m_tstat_input_data.push_back(temp_tstat_input);

    temp_tstat_input.InputName.StrValue=g_strInCO2;
    m_tstat_input_data.push_back(temp_tstat_input);

    temp_tstat_input.InputName.StrValue=g_strLightingSensor;
    m_tstat_input_data.push_back(temp_tstat_input);
#endif

#if 1   //初始化其他的input的其他值
    int nValue=0;

    float fValue=0;
    for (int i=2; i<=9; i++)
    {

        // m_tstat_input_data.at(i-1).CustomTable.StrValue=NO_APPLICATION;

        //Auto Manual
        nValue=product_register_value[MODBUS_INPUT_MANU_ENABLE];//309    141
        BYTE bFilter=0x01;
        bFilter = bFilter<< (i-2);
        m_tstat_input_data.at(i-1).AM.regAddress=MODBUS_INPUT_MANU_ENABLE;
        m_tstat_input_data.at(i-1).AM.RegValue=nValue;
        if((nValue & bFilter))
        {
            m_tstat_input_data.at(i-1).AM.StrValue=strman;
        }
        else
        {
            m_tstat_input_data.at(i-1).AM.StrValue=strAuto;
        }
        //Filter
        strTemp.Format(_T("%d"),product_register_value[141+i]);
        m_tstat_input_data.at(i-1).Filter.regAddress=141+i;
        m_tstat_input_data.at(i-1).Filter.StrValue=strTemp;

        //Range
        m_crange=0;

        nValue=product_register_value[MODBUS_ANALOG1_RANGE+i-2];	//189
        nValue &= 0x7F;//去掉最高位
        if(nValue>=0)
        {
            strTemp=analog_range_TSTAT6[nValue];
        }
        m_crange=nValue;

        m_tstat_input_data.at(i-1).Range.StrValue=strTemp;
        m_tstat_input_data.at(i-1).Range.RegValue=product_register_value[MODBUS_ANALOG1_RANGE+i-2];
        m_tstat_input_data.at(i-1).Range.regAddress=MODBUS_ANALOG1_RANGE+i-2;
        // nValue=product_register_value[MODBUS_ANALOG1_RANGE+i-2];
        //Custom
        if(m_crange==4)
        {
            m_tstat_input_data.at(i-1).CustomTable.StrValue=_T("Custom1...");
        }
        else if (m_crange==6)
        {
            m_tstat_input_data.at(i-1).CustomTable.StrValue=_T("Custom2...");
        }
        else
        {
            m_tstat_input_data.at(i-1).CustomTable.StrValue=NO_APPLICATION;
        }
        //Function
        nValue=product_register_value[MODBUS_ANALOG1_FUNCTION+i-2];		//298   167
        m_tstat_input_data.at(i-1).Function.regAddress=MODBUS_ANALOG1_FUNCTION+i-2;
        m_tstat_input_data.at(i-1).Function.RegValue=nValue;
        strTemp=INPUT_FUNS[0];
        m_tstat_input_data.at(i-1).Function.StrValue=strTemp;
        if (nValue>=0&&nValue<8)//tstat6
        {
            strTemp=INPUT_FUNS[nValue];
            m_tstat_input_data.at(i-1).Function.StrValue=strTemp;
        }

        if(m_crange==1)	//359  122
        {
            fValue=float(product_register_value[MODBUS_ANALOG_INPUT1+i-2]/10.0);	//367   131
            strTemp.Format(_T("%.1f"),fValue);
        }
        else if (m_crange==3||m_crange==5||m_crange==7||m_crange==8||m_crange==9||m_crange==10)
        {
            if (m_crange==9||m_crange==10)
            {
                int nValue=(product_register_value[MODBUS_ANALOG_INPUT1+i-2]); //367  131
                if (nValue == 0)
                {
                    strTemp = _T("Closed");
                }
                else
                {
                    strTemp = _T("Open");
                }
            }
            else if (m_crange==7||m_crange==8)
            {

                int nValue=(product_register_value[MODBUS_ANALOG_INPUT1+i-2]); //367  131
                if (nValue == 0)
                {
                    strTemp = _T("Unoccupied");
                }
                else
                {
                    strTemp = _T("Occupied");
                }

            }
            else
            {

                int nValue=(product_register_value[MODBUS_ANALOG_INPUT1+i-2]); //367  131
                if (nValue == 0)
                {
                    strTemp = _T("Off");
                }
                else
                {
                    strTemp = _T("On");
                }

            }
        }
        else if (m_crange==4||m_crange==6)  // custom sensor	359 122
        {
            fValue=float(product_register_value[MODBUS_ANALOG_INPUT1+i-2]/10.0);	//367  131
            strTemp.Format(_T("%.1f"), (float)fValue/10.0);

        }
        else if(m_crange==2)	//359 122
        {
            nValue=product_register_value[MODBUS_ANALOG_INPUT1+i-2];		//367  131
            strTemp.Format(_T("%0.1f"),  (float)nValue);
        }
        else
        {
            strTemp.Format(_T("%d"),product_register_value[MODBUS_ANALOG_INPUT1+i-2]);
        }


        //Unit
        CString strValueUnit=GetTempUnit(m_crange, 1);
        m_tstat_input_data.at(i-1).Unit.StrValue=strValueUnit;


        m_tstat_input_data.at(i-1).Value.regAddress=MODBUS_ANALOG_INPUT1+i-2;
        m_tstat_input_data.at(i-1).Value.RegValue=product_register_value[MODBUS_ANALOG_INPUT1+i-2];
        m_tstat_input_data.at(i-1).Value.StrValue=strTemp;
    }

#endif
    bool m_disable_hum,m_disable_CO2;
    if((product_register_value[20]&2)==2)
    {
        m_disable_hum=TRUE;
    }
    else
    {
        m_disable_hum=FALSE;
    }
    if((product_register_value[MODBUS_TSTAT6_CO2_AVALUE]>=0)&&(product_register_value[MODBUS_TSTAT6_CO2_AVALUE]<=3000))
    {
        m_disable_CO2=TRUE;
    }
    else
    {
        m_disable_CO2=FALSE;
    }
    if (!m_disable_hum)
    {
        m_tstat_input_data.at(9).AM.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).CustomTable.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).Filter.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).Function.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).Range.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).Unit.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(9).Value.StrValue=NO_APPLICATION;

    }
    else
    {

        CString temp;
        m_tstat_input_data.at(9).AM.regAddress=MODBUS_TSTAT6_HUM_AM;
        m_tstat_input_data.at(9).AM.RegValue=product_register_value[MODBUS_TSTAT6_HUM_AM];

        if (product_register_value[MODBUS_TSTAT6_HUM_AM]==0)
        {

            temp.Format(_T("%0.1f%%"),(float)product_register_value[MODBUS_TSTAT6_HUM_AVALUE]/10.0);
            //m_FlexGrid.put_TextMatrix(10,AM_FIELD,strAuto);
            m_tstat_input_data.at(9).AM.StrValue=strAuto;

            m_tstat_input_data.at(9).Value.regAddress=MODBUS_TSTAT6_HUM_AVALUE;
            m_tstat_input_data.at(9).Value.RegValue=product_register_value[MODBUS_TSTAT6_HUM_AVALUE];
            m_tstat_input_data.at(9).Value.StrValue=temp;

        }
        else
        {
            // m_FlexGrid.put_TextMatrix(10,AM_FIELD,strman);
            m_tstat_input_data.at(9).AM.StrValue=strman;
            temp.Format(_T("%0.1f%%"),(float)product_register_value[MODBUS_TSTAT6_HUM_MVALUE]/10);

            m_tstat_input_data.at(9).Value.regAddress=MODBUS_TSTAT6_HUM_MVALUE;
            m_tstat_input_data.at(9).Value.RegValue=product_register_value[MODBUS_TSTAT6_HUM_MVALUE];
            m_tstat_input_data.at(9).Value.StrValue=temp;


        }
        m_tstat_input_data.at(9).Unit.StrValue=_T("%");

        temp.Format(_T("%d"),product_register_value[MODBUS_TSTAT6_HUM_FILTER]);
        m_tstat_input_data.at(9).Filter.regAddress=MODBUS_TSTAT6_HUM_FILTER;
        m_tstat_input_data.at(9).Filter.RegValue=product_register_value[MODBUS_TSTAT6_HUM_FILTER];
        m_tstat_input_data.at(9).Filter.StrValue=temp;
        m_tstat_input_data.at(9).Range.StrValue=NO_APPLICATION;
    }


    if (!m_disable_CO2)
    {
        m_tstat_input_data.at(10).AM.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).CustomTable.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).Filter.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).Function.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).Range.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).Unit.StrValue=NO_APPLICATION;
        m_tstat_input_data.at(10).Value.StrValue=NO_APPLICATION;
    }
    else
    {
        CString temp;
        m_tstat_input_data.at(10).AM.regAddress=MODBUS_TSTAT6_CO2_AM;
        m_tstat_input_data.at(10).AM.RegValue=product_register_value[MODBUS_TSTAT6_CO2_AM];
        strUnit=_T("ppm");
        m_tstat_input_data.at(10).Unit.StrValue=strUnit;
        if (product_register_value[MODBUS_TSTAT6_CO2_AM]==0)
        {


            m_tstat_input_data.at(10).AM.StrValue=strAuto;
            temp.Format(_T("%d"),product_register_value[MODBUS_TSTAT6_CO2_AVALUE]);

            m_tstat_input_data.at(10).Value.regAddress=MODBUS_TSTAT6_CO2_AVALUE;
            m_tstat_input_data.at(10).Value.RegValue=product_register_value[MODBUS_TSTAT6_CO2_AVALUE];
            m_tstat_input_data.at(10).Value.StrValue=temp;

        }
        else
        {
            m_tstat_input_data.at(10).AM.StrValue=strman;
            temp.Format(_T("%d"),product_register_value[MODBUS_TSTAT6_CO2_MVALUE]);
            m_tstat_input_data.at(10).Value.regAddress=MODBUS_TSTAT6_CO2_MVALUE;
            m_tstat_input_data.at(10).Value.RegValue=product_register_value[MODBUS_TSTAT6_CO2_MVALUE];
            m_tstat_input_data.at(10).Value.StrValue=temp;

        }

        temp.Format(_T("%d"),product_register_value[MODBUS_TSTAT6_CO2_FILTER]);
        m_tstat_input_data.at(10).Filter.regAddress=MODBUS_TSTAT6_CO2_FILTER;
        m_tstat_input_data.at(10).Filter.RegValue=product_register_value[MODBUS_TSTAT6_CO2_FILTER];
        m_tstat_input_data.at(10).Filter.StrValue=temp;
        m_tstat_input_data.at(10).Range.StrValue=NO_APPLICATION;
    }

    strTemp.Format(_T("%d"),product_register_value[MODBUS_VALUE_SENSOR]);
    // LUX
    m_tstat_input_data.at(11).AM.StrValue=NO_APPLICATION;
    m_tstat_input_data.at(11).CustomTable.StrValue=NO_APPLICATION;
    m_tstat_input_data.at(11).Filter.StrValue=NO_APPLICATION;
    m_tstat_input_data.at(11).Function.StrValue=NO_APPLICATION;
    m_tstat_input_data.at(11).Range.StrValue=L"LUX";
    m_tstat_input_data.at(11).Unit.StrValue=L"LUX";
    m_tstat_input_data.at(11).Value.regAddress=MODBUS_VALUE_SENSOR;
    m_tstat_input_data.at(11).Value.RegValue=product_register_value[MODBUS_VALUE_SENSOR];
    m_tstat_input_data.at(11).Value.StrValue=strTemp;
}

void LoadInputData_CS3000()
{
    m_tstat_input_data.clear();
    Tstat_Input_Struct temp_tstat_input;

    temp_tstat_input.InputName.StrValue=L"Current";
    m_tstat_input_data.push_back(temp_tstat_input);
    temp_tstat_input.InputName.StrValue=L"Voltage";
    m_tstat_input_data.push_back(temp_tstat_input);

    m_tstat_input_data.at(0).Value.Reg_Property=REG_READ_WRITE;
    m_tstat_input_data.at(0).Value.regAddress=100;
    m_tstat_input_data.at(0).Value.RegValue=(short)product_register_value[100];


    m_tstat_input_data.at(0).Range.regAddress = 104;
    m_tstat_input_data.at(0).Range.RegValue = (short)product_register_value[104];

    if (product_register_value[7]==PM_CS_RSM_AC||product_register_value[7]==PM_CS_SM_AC)
    {

        m_tstat_input_data.at(0).Value.StrValue.Format(_T("%0.2f"),(float)(m_tstat_input_data.at(0).Value.RegValue)/100);
        if (m_tstat_input_data.at(0).Range.RegValue>=0&&m_tstat_input_data.at(0).Range.RegValue<=2)
        {
            m_tstat_input_data.at(0).Range.StrValue=CS3000_INPUT_RANGE[m_tstat_input_data.at(0).Range.RegValue];
            m_tstat_input_data.at(0).Range.Reg_Property=REG_READ_WRITE;
        }
    }
    else
    {
        m_tstat_input_data.at(0).Value.StrValue.Format(_T("%0.1f"),(float)(m_tstat_input_data.at(0).Value.RegValue)/10);
        if(m_tstat_input_data.at(0).Range.RegValue==10)
        {
            m_tstat_input_data.at(0).Range.StrValue=CS3000_INPUT_RANGE[3];
        }
    }
    m_tstat_input_data.at(1).Value.Reg_Property=REG_READ_WRITE;
    m_tstat_input_data.at(1).Value.regAddress=101;
    m_tstat_input_data.at(1).Value.RegValue=(short)product_register_value[101];
    m_tstat_input_data.at(1).Value.StrValue.Format(_T("%0.1f"),(float)(m_tstat_input_data.at(1).Value.RegValue)/10);

    m_tstat_input_data.at(0).Unit.StrValue=_T("A");
    m_tstat_input_data.at(1).Unit.StrValue=_T("V");

    m_tstat_input_data.at(0).Filter.Reg_Property=REG_READ_WRITE;
    m_tstat_input_data.at(0).Filter.regAddress=136;
    m_tstat_input_data.at(0).Filter.RegValue=product_register_value[136];
    m_tstat_input_data.at(0).Filter.StrValue.Format(_T("%d"),product_register_value[136]);

    m_tstat_input_data.at(1).Filter.Reg_Property=REG_READ_WRITE;
    m_tstat_input_data.at(1).Filter.regAddress=136;
    m_tstat_input_data.at(1).Filter.RegValue=product_register_value[136];
    m_tstat_input_data.at(1).Filter.StrValue.Format(_T("%d"),product_register_value[136]);

}
#define  THE_CHAR_LENGTH 8
CString GetTextFromReg(unsigned short reg)
{
    CString str_temp=_T("");
    unsigned short temp_buffer[4];
    unsigned short temp_buffer_Char[THE_CHAR_LENGTH];
    unsigned char p[THE_CHAR_LENGTH+1]= {'\0'};

    temp_buffer[0]=product_register_value[reg];
    temp_buffer[1]=product_register_value[reg+1];
    temp_buffer[2]=product_register_value[reg+2];
    temp_buffer[3]=product_register_value[reg+3];


    if (temp_buffer[0]==0||temp_buffer[0]==65535)
    {
        return str_temp;
    }
    unsigned short Hi_Char,Low_Char;

    for (int i=0; i<4; i++)
    {
        Hi_Char=temp_buffer[i];
        Hi_Char=Hi_Char&0xff00;
        Hi_Char=Hi_Char>>8;
        Low_Char=temp_buffer[i];
        Low_Char=Low_Char&0x00ff;
        temp_buffer_Char[2*i]=Hi_Char;
        temp_buffer_Char[2*i+1]=Low_Char;
    }

    for (int i=0; i<THE_CHAR_LENGTH; i++)
    {
        p[i] =(unsigned char)temp_buffer_Char[i];
    }
    str_temp.Format(_T("%c%c%c%c%c%c%c%c"),p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);


    return str_temp;
}
CString GetTextFromReg_Buffer(unsigned short reg,unsigned short *Buffer)
{
    CString str_temp=_T("");
    unsigned short temp_buffer[4];
    unsigned short temp_buffer_Char[THE_CHAR_LENGTH];
    unsigned char p[THE_CHAR_LENGTH+1]= {'\0'};

    temp_buffer[0]=Buffer[reg];
    temp_buffer[1]=Buffer[reg+1];
    temp_buffer[2]=Buffer[reg+2];
    temp_buffer[3]=Buffer[reg+3];


    if (temp_buffer[0]==0||temp_buffer[0]==65535)
    {
        return str_temp;
    }
    unsigned short Hi_Char,Low_Char;

    for (int i=0; i<4; i++)
    {
        Hi_Char=temp_buffer[i];
        Hi_Char=Hi_Char&0xff00;
        Hi_Char=Hi_Char>>8;
        Low_Char=temp_buffer[i];
        Low_Char=Low_Char&0x00ff;
        temp_buffer_Char[2*i]=Hi_Char;
        temp_buffer_Char[2*i+1]=Low_Char;
    }

    for (int i=0; i<THE_CHAR_LENGTH; i++)
    {
        p[i] =(unsigned char)temp_buffer_Char[i];
    }
    str_temp.Format(_T("%c%c%c%c%c%c%c%c"),p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);


    return str_temp;
}
 

bool IsDigit (CString strData)
{
    for (int i = 0; i<strData.GetLength (); i++)
    {
        if (!isdigit(strData.GetAt (i)))
        {
            return false;
        }
    }
    return true;
}

CString NewGUID ()
{
    
        CString strGuid = L"";
        GUID guid;
        if (S_OK == ::CoCreateGuid(&guid))
        {
            strGuid.Format(_T("%04x%04x%04x%04x%04x%04x%04x%04x"),guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
        }
        return strGuid;
}

CString ReadStringCharToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0',str.GetLength());

	int i;
	for ( i = 0 ; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if(szBuf == NULL)
	{
		return L"";
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_ACP, 0, szBuf, -1, ptch, nLen);
	str.Format(_T("%s"), ptch);

	if(NULL != ptch)
		delete [] ptch;
	ptch = NULL;

	if(NULL != szBuf)
		delete []szBuf;
	szBuf = NULL;
	return str;
}
CString DealWithFootPrint(CString FootPrint)
{
    char chToken= '\\';
	int index = FootPrint.ReverseFind (chToken);
	if (index!=-1)
	{
		FootPrint.Delete(0,index+1);
	}
	return FootPrint;
}