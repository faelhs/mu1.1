#include "StdAfx.h"
#include "CSQL.h"
#include "Log.h"

SQLClass gSQLManager;
CBoundRecordSet rsSql;
CSQL PointsSql;
SQLCONNECTIONSTRING m_SqlConn;

void SQLClass::Load()
{
	strcpy_s(m_SqlConn.sDriver,"{SQL Server}");
	// ---
	GetPrivateProfileString("SQL", "IP", "127.0.0.1", m_SqlConn.sServer, sizeof(m_SqlConn.sServer), SQL_FILE);
	GetPrivateProfileString("SQL", "Database", "MuOnline", m_SqlConn.sDatabase, sizeof(m_SqlConn.sDatabase), SQL_FILE);
	GetPrivateProfileString("SQL", "User", "sa", m_SqlConn.sUID, sizeof(m_SqlConn.sUID), SQL_FILE);
	GetPrivateProfileString("SQL", "Password", "12345", m_SqlConn.sPwd, sizeof(m_SqlConn.sPwd), SQL_FILE);
	// ---
	GetPrivateProfileString("SQL", "Collumn_Gold", "null", this->m_Data.Coluna_Gold, sizeof(this->m_Data.Coluna_Gold), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_Cash", "null", this->m_Data.Coluna_Cash, sizeof(this->m_Data.Coluna_Cash), SQL_FILE);
	// ---
	GetPrivateProfileString("SQL", "Collumn_Reset", "null", this->m_Data.Coluna_Reset, sizeof(this->m_Data.Coluna_Reset), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_ResetDay", "null", this->m_Data.Coluna_ResetDay, sizeof(this->m_Data.Coluna_ResetDay), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_ResetWeek", "null", this->m_Data.Coluna_ResetWeek, sizeof(this->m_Data.Coluna_ResetWeek), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_ResetMonth", "null", this->m_Data.Coluna_ResetMonth, sizeof(this->m_Data.Coluna_ResetMonth), SQL_FILE);
	// ---
	GetPrivateProfileString("SQL", "Collumn_MasterReset", "null", this->m_Data.Coluna_MasterReset, sizeof(this->m_Data.Coluna_MasterReset), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_MasterResetDay", "null", this->m_Data.Coluna_MasterResetDay, sizeof(this->m_Data.Coluna_MasterResetDay), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_MasterResetWeek", "null", this->m_Data.Coluna_MasterResetWeek, sizeof(this->m_Data.Coluna_MasterResetWeek), SQL_FILE);
	GetPrivateProfileString("SQL", "Collumn_MasterResetMonth", "null", this->m_Data.Coluna_MasterResetMonth, sizeof(this->m_Data.Coluna_MasterResetMonth), SQL_FILE);
	// ---
	GetPrivateProfileString("SQL", "Query_Get_Reset", "null", this->m_Data.Query_Get_Reset, sizeof(this->m_Data.Query_Get_Reset), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Update_Reset", "null", this->m_Data.Query_Update_Reset, sizeof(this->m_Data.Query_Update_Reset), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Get_MasterReset", "null", this->m_Data.Query_Get_MasterReset, sizeof(this->m_Data.Query_Get_MasterReset), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Update_MasterReset", "null", this->m_Data.Query_Update_MasterReset, sizeof(this->m_Data.Query_Update_MasterReset), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Get_Gold", "null", this->m_Data.Query_Get_Gold, sizeof(this->m_Data.Query_Get_Gold), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Update_Gold", "null", this->m_Data.Query_Update_Gold, sizeof(this->m_Data.Query_Update_Gold), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Get_Cash", "null", this->m_Data.Query_Get_Cash, sizeof(this->m_Data.Query_Get_Cash), SQL_FILE);
	GetPrivateProfileString("SQL", "Query_Update_Cash", "null", this->m_Data.Query_Update_Cash, sizeof(this->m_Data.Query_Update_Cash), SQL_FILE);
	// --- 
	if(PointsSql.Connect(&m_SqlConn) == false) 
	{
		MessageBoxA(NULL, "Conexão com SQL Server Falhou !\nFavor Verificar o arquivo 'Hgt_SQLConnect.ini'", "Erro na conexão com SQL Server !", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	} 
	else 
	{
		LogAdd(LOG_RED,  "[SQL Server] Connect to DataBase (%s)", m_SqlConn.sDatabase);
	}
}

void SQLClass::Execute(char *szQuery,...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, szQuery);
	// ---
	vsprintf(szBuffer, szQuery, pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Close();
}

char * SQLClass::ReturnString(char *szField, char * szQuery, ...)
{
	char szBuffer[1024] = {0};
	// ---
	static char szResult[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, szQuery);
	// ---
	vsprintf(szBuffer, szQuery, pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Fetch();
	// ---
	strcpy_s(szResult, rsSql.Values(szField).ToString());
	// ---
	rsSql.Close();
	// ---
	return szResult;
}

int SQLClass::ReturnInt(char *szField, char * szQuery, ...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, szQuery);
	// ---
	vsprintf(szBuffer, szQuery, pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Fetch();
	// ---
	int value = rsSql.Values(szField).ToShortS();
	// ---
	rsSql.Close();
	// ---
	return value;
}

__int64 SQLClass::ReturnInt64(char *szField, char *szQuery, ...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments,szQuery);
	// ---
	vsprintf(szBuffer, szQuery, pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Fetch();
	// ---
	__int64 value = rsSql.Values(szField).ToI64U();
	// ---
	rsSql.Close();
	// ---
	return value;
}

float SQLClass::ReturnFloat(char *szField, char *szQuery,...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments,szQuery);
	// ---
	vsprintf(szBuffer,szQuery,pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Fetch();
	// ---
	float value = rsSql.Values(szField).ToFloat();
	// ---
	rsSql.Close();
	// ---
	return value;
}

double SQLClass::ReturnDouble(char *szField, char *szQuery,...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments,szQuery);
	// ---
	vsprintf(szBuffer,szQuery,pArguments);
	// ---
	va_end(pArguments);
	// ---
	PointsSql.Execute(szBuffer, &rsSql, true);
	// ---
	rsSql.Fetch();
	// ---
	double value = rsSql.Values(szField).ToDouble();
	// ---
	rsSql.Close();
	// ---
	return value;
}

int SQLClass::GetCountInt(char * Table, const char* Optional, ...)
{
	char szBuffer[1024] = {0};
	char szQuery[1024] = {0};
	// ---
	va_list pArguments;
	// ---
    va_start(pArguments, Optional);
	// ---
    vsprintf(szBuffer, Optional, pArguments);
	// ---
    va_end(pArguments);
	// ---
    if (Optional)
	{
		wsprintfA(szQuery, "SELECT * FROM %s %s;", Table, szBuffer);
	}
    else
	{
		wsprintfA(szQuery, "SELECT * FROM %s;", Table);
	}
	// ---
	int count = rsSql.RowCount;
	// ---
	rsSql.Close();
	// ---
	ZeroMemory(szQuery, sizeof(szQuery));
	// ---
	return count;
}

void SQLClass::UpdateReset(int aIndex)
{
	this->Execute(this->m_Data.Query_Update_Reset, 
		this->m_Data.Coluna_Reset, 
		this->m_Data.Coluna_Reset, 
		this->m_Data.Coluna_ResetDay, 
		this->m_Data.Coluna_ResetDay, 
		this->m_Data.Coluna_ResetWeek, 
		this->m_Data.Coluna_ResetWeek, 
		this->m_Data.Coluna_ResetMonth, 
		this->m_Data.Coluna_ResetMonth, gObj[aIndex].Name);
}

void SQLClass::UpdateMasterReset(int aIndex)
{
	this->Execute(this->m_Data.Query_Update_MasterReset, 
		this->m_Data.Coluna_MasterReset, 
		this->m_Data.Coluna_MasterReset, 
		this->m_Data.Coluna_MasterResetDay, 
		this->m_Data.Coluna_MasterResetDay, 
		this->m_Data.Coluna_MasterResetWeek, 
		this->m_Data.Coluna_MasterResetWeek, 
		this->m_Data.Coluna_MasterResetMonth, 
		this->m_Data.Coluna_MasterResetMonth, gObj[aIndex].Name);
}