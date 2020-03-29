#ifndef _SQLMANAGER_H
#define _SQLMANAGER_H

struct SQLSERVER_DATA_INFO
{
	char Coluna_Vip[256];
	char Coluna_VipDays[256];
	char Coluna_Gold[256];
	char Coluna_Cash[256];
	// ---
	char Coluna_Reset[256];
	char Coluna_ResetDay[256];
	char Coluna_ResetWeek[256];
	char Coluna_ResetMonth[256];
	// ---
	char Coluna_MasterReset[256];
	char Coluna_MasterResetDay[256];
	char Coluna_MasterResetWeek[256];
	char Coluna_MasterResetMonth[256];
	// ---
	char Query_Get_Vip[256];
	char Query_Update_Vip[256];
	char Query_Get_Gold[256];
	char Query_Update_Gold[256];
	char Query_Get_Cash[256];
	char Query_Update_Cash[256];
	char Query_Get_Reset[256];
	char Query_Update_Reset[256];
	char Query_Get_MasterReset[256];
	char Query_Update_MasterReset[256];
};

class SQLClass
{
public:
	void Load();
	void Execute(char *szQuery,...);
	// ---
	char * ReturnString(char *szField, char *szQuery, ...);
	// ---
	int ReturnInt(char *szField, char *szQuery,...);
	// ---
	__int64 ReturnInt64(char *szField, char *szQuery, ...);
	// ---
	float ReturnFloat(char *szField, char *szQuery, ...);
	// ---
	double ReturnDouble(char *szField, char *szQuery, ...);
	// ---
	int GetCountInt(char* Table, const char* Optional, ...);
	// ---
	void UpdateReset(int aIndex);
	void UpdateMasterReset(int aIndex);
	// ---
	SQLSERVER_DATA_INFO m_Data;
};

extern SQLClass gSQLManager;

#endif