#pragma once
#include "pvdatabasestruct.h"

class Table_PN{
public:
    Table_PN();
    virtual ~Table_PN();
    vector<PN_Struct> pv_Table_PN;
    vector<PList_Struct> m_bomdataset;
    vector<PList_Struct> m_buydataset;
    vector<TreePL_Struct> m_Treedataset;
    vector<SU_Struct> m_dataset_vendor;
    vector<PO_Struct> m_dataset_po;
    vector<PO_Part_Struct> m_dataset_ppo;
	vector<PO_Struct> m_dataset_purchaseorder;
    vector<Type_Struct> m_dataset_type;
    vector<UN_Struct> m_dataset_UN;
    vector<Vendor_Information_BasedOn_Part> m_dataset_VendorInfor_Part;
     vector<Vendor_Information_BasedOn_Part> m_dataset_VendorPrice_Part;
    vector<Part_Vendor_Information> m_dataset_PartsVendors;
   
    vector<Cost_Struct> m_dataset_Cost;

    vector<CUR_Struct> m_dataset_Currentcy;

	vector<CU_Struct> m_dataset_Customer;

	vector<Search_POStruct> m_dataset_SearchPO;

	vector<BuyMainTable> m_dataset_BuyMainTable;
	vector<BuyDetailsTable> m_dataset_BuyDetailsTable;

	CString m_databaseIP;
	CString m_databaseName;
	CString m_databaseUserName;
	CString m_databasePwd;
    int m_PNID;
    int m_POMID;
    void Initial_Data();
    void Load_Assembly_Data(CString KeyWord=L"");
    void Initial_BomData();
    void Build_TreeData(int ParentID,CString ParentPN);
    void Build_AssemblyData(int ParentID,CString ParentPN);
    void Search_Vendor(CString VendorName=L"");
    void Search_Vendors(CString VendorName=L"");
    void Search_POM(CString strPO=L"",CString strVendorName=L"");
    PO_Struct Insert_PO(PO_Struct temp_PO);
    void Update_PO(PO_Struct temp_PO);
    void Delete_PO(PO_Struct temp_PO);
	BOOL Check_PN(CString StrPN);
    void Initial_Type();
    void Initial_UN();
    BOOL  Check_UN(UN_Struct unit);
    void Search_PO();
    void Search_PO_Part();
    void Insert_PO_Part(PO_Part_Struct ppstruct);
    void Update_PO_Part(PO_Part_Struct ppstruct);

 
    void Search_ALLPN(CString KeyWord=L"");
    void Search_Data_ByPN(CString strValue,CString strValue1,CString PageNum,CString CurrentPage);
 
    void Search_All_Parts_Vendors(CString para_PN=L"");
  
  
    void Search_PNID(int PNID);
    void Delete_ByPN(int PNID);
    void Update_ByPN(PN_Struct PNItem);
    PN_Struct Insert_ByPN(PN_Struct PNItem);
	BOOL SyncPNItemFromSpring(PN_SpringStruct PNSpringItem);
	BOMListItemStatus CheckBomListItemStatus(BOMListItemStatus PN);
    
    void Add_ItemStock(PN_Struct PNItem);
    void Reduce_ItemStock(PN_Struct PNItem);
    /*   
    Date:[10/13/2015]
    Author:[Alex]
    Function:  
    update last price 

    */

    BOOL Update_PartPrice(int PNID,float Price);

    CString GetUnitName_ByID(int UNID);
    /*   
    Date:[9/14/2015]
    Author: Alex
    Function:
    BOM --Insert Parts in the PL list
    */
    BOOL Insert_PL(BOM_PartList PLItem);
    /*   
    Date:[9/14/2015]
    Author: Alex
    Function:
    BOM --Delete Parts in the PL list
    */
    BOOL Delete_PL(BOM_PartList PLItem);
    /*   
    Date:[9/21/2015]
    Author:[Alex]
    Function:
    update the qty in the PL list
    */
    BOOL Update_PL(BOM_PartList PLItem); 
    /*   
    Date:[10/20/2015]
    Author:[Alex]
    Function:
    Vendors's informations based on one item

    */
    BOOL SearchVendors_BasedOnItem(int PNID) ;
    BOOL SearchVendorPrice_BaseOnItem(int PNID);
	BOOL Check_Vendor(int PNID);
	BOOL Check_Ordered(int PNID);
    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Insert LNK 

    */  
    BOOL Insert_LNK(Vendor_Information_BasedOn_Part LNK);

    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Delete LNK 

    */  
    BOOL Delete_LNK(Vendor_Information_BasedOn_Part LNK);

    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Update LNK 

    */  
    BOOL Update_LNK(Vendor_Information_BasedOn_Part LNK);


    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Load Cost Based ON LNK

    */

    BOOL Search_Cost_LNK(int LNKID);

    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Insert a new Cost based on LNKID

    */

    BOOL Insert_Cost(Cost_Struct cost);
    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Update Cost

    */
    BOOL Update_Cost(Cost_Struct cost);

    /*   
    Date:[10/21/2015]
    Author:[Alex]
    Function:
    Delete Cost 
    */

    BOOL Delete_Cost(Cost_Struct cost);


    /*   
         ShortCut:Alex
         Date:[12/17/2015]
         Author:[Alex]
         Function:
         Insert a unit to db
    
    */
    
    BOOL Insert_UN(UN_Struct unit);
    /*   
         ShortCut:Alex
         Date:[12/17/2015]
         Author:[Alex]
         Function:
         Delete Unit
    
    */
    BOOL Delete_UN(UN_Struct unit);

    /*   
         ShortCut:Alex
         Date:[12/17/2015]
         Author:[Alex]
         Function:
        Update unit
    
    */
    BOOL Update_UN(UN_Struct unit);
    /*   
    Date:[11/3/2015]
    Author:[Alex]
    Function:
    Insert_Vendor 
    Update_Vendor
    Delete_Vendor

    */

    BOOL Insert_Vendor(SU_Struct VItem);
    BOOL Update_Vendor(SU_Struct VItem);
    BOOL Delete_Vendor(SU_Struct VItem);

    BOOL Load_Currency();
    BOOL Insert_Currency(CUR_Struct CItem);
    BOOL Update_Currency(CUR_Struct CItem);
    BOOL Delete_Currency(CUR_Struct CItem);


   CString GetShippingAddress();
   CString GetImageFileFold();


   BOOL Search_Customers(CString CustomerName);
   BOOL Insert_CU(CU_Struct cu);
   BOOL Delete_CU(CU_Struct cu);
   BOOL Update_CU(CU_Struct cu);


   void DataSync();
   void SetMsgHandle(CWnd* pHandle);
   
   void OutPutsStatusInfo(const CString& strInfo, BOOL bReplace = FALSE,int process=0);

   void Search_OrderInformation(CString StrVendorName, CString StrPN);

   void Search_BuyMainTable(CString StrPN);
   BOOL InsertAndUpdate_BuyMainTable(BuyMainTable temp,int &BuyID);
   BOOL Check_BuildPO(CString POBegin,int &BuyID);
   BOOL Delete_BuyMainTable(BuyMainTable temp);
   void Search_BuyDetailsTable(CString BuyID);
   BOOL InsertAndUpdate_BuyDetailsTable(BuyDetailsTable temp);
   CString GetPONumber(CString BeginPO);
   BOOL DeletePONumber(CString BeginPO, CString Num);
private:
    CString m_pv_database_path;
    CString m_pv_database_image;
    CBADO m_database_operator;
	CWnd *m_msgwnd;
};
