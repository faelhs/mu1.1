#include "StdAfx.h"
#include "Log.h"
#include "GameMain.h"

CLog gLog;

CLog::CLog()
{
	this->m_count = 0;
}

CLog::~CLog()
{
	for(int n = 0; n < this->m_count; n++)
	{
		if(this->m_LogInfo[n].Active != 0)
		{
			CloseHandle(this->m_LogInfo[n].File);
		}
	}
}

void CLog::AddLog(BOOL active, char* directory)
{
	if(this->m_count < 0 || this->m_count >= MAX_LOG)
	{
		return;
	}
	// ---
	LOG_INFO * lpInfo = &this->m_LogInfo[this->m_count++];
	// ---
	lpInfo->Active = active;
	// ---
	strcpy_s(lpInfo->Directory, directory);
	// ---
	if(lpInfo->Active != 0)
	{
		CreateDirectory(lpInfo->Directory, NULL);
		// ---
		SYSTEMTIME time;
		// ---
		GetLocalTime(&time);
		// ---
		lpInfo->Day = time.wDay;
		// ---
		lpInfo->Month = time.wMonth;
		// ---
		lpInfo->Year = time.wYear;
		// ---
		wsprintf(lpInfo->Filename,".\\%s\\LOG_%02d.%02d.%04d[%s].txt",lpInfo->Directory, lpInfo->Day, lpInfo->Month, lpInfo->Year, szServerName);
		// ---
		lpInfo->File = CreateFile(lpInfo->Filename, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		// ---
		if(lpInfo->File == INVALID_HANDLE_VALUE)
		{
			lpInfo->Active = 0;
			return;
		}
		// ---
		if(SetFilePointer(lpInfo->File, 0, 0, FILE_END) == INVALID_SET_FILE_POINTER)
		{
			lpInfo->Active = 0;
			// ---
			CloseHandle(lpInfo->File);
			// ---
			return;
		}
	}
}

void CLog::Output(eLogType type, char* text,...)
{
	if(type < 0 || type >= this->m_count)
	{
		return;
	}
	// ---
	LOG_INFO * lpInfo = &this->m_LogInfo[type];
	// ---
	if(lpInfo->Active == 0)
	{
		return;
	}
	// ---
	SYSTEMTIME time;
	// ---
	GetLocalTime(&time);
	// ---
	if(time.wDay != lpInfo->Day || time.wMonth != lpInfo->Month || time.wYear != lpInfo->Year)
	{
		CloseHandle(lpInfo->File);
		// ---
		lpInfo->Day = time.wDay;
		// ---
		lpInfo->Month = time.wMonth;
		// ---
		lpInfo->Year = time.wYear;
		// ---
		wsprintf(lpInfo->Filename,".\\%s\\LOG_%02d.%02d.%04d[%s].txt",lpInfo->Directory, lpInfo->Day, lpInfo->Month, lpInfo->Year, szServerName);
		// ---
		lpInfo->File = CreateFile(lpInfo->Filename, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		// ---
		if(lpInfo->File == INVALID_HANDLE_VALUE)
		{
			lpInfo->Active = 0;
			return;
		}
		// ---
		if(SetFilePointer(lpInfo->File, 0, 0, FILE_END) == INVALID_SET_FILE_POINTER)
		{
			lpInfo->Active = 0;
			// ---
			CloseHandle(lpInfo->File);
			// ---
			return;
		}
	}
	// ---
	char temp[1024] = {0};
	// ---
	va_list arg;
	va_start(arg,text);
	vsprintf_s(temp,text,arg);
	va_end(arg);
	// ---
	char buff[1024] = {0};
	// ---
	wsprintf(buff,"[ %02d:%02d:%02d %s\r\n",time.wHour, time.wMinute, time.wSecond, temp);
	// ---
	DWORD OutSize;
	// ---
	WriteFile(lpInfo->File, buff, strlen(buff), &OutSize, 0);
}

void LogAdd(eLogColor Color, char * szLog,...)
{
	tm today;
	// ---
	time_t ltime;
	// ---
	time(&ltime);
	// ---
	if(localtime_s(&today,&ltime) != 0)
	{
		return;
	}
	// ---
	char szTime[32] = {0};
	// ---
	if(asctime_s(szTime, sizeof(szTime), &today) != 0)
	{
		return;
	}
	// ---
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, szLog);
	// ---
	vsprintf(szBuffer, szLog, pArguments);
	// ---
	va_end(pArguments);
	// ---
	char szTemp[1024] = {0};
	// ---
	wsprintf(szTemp,"[%.8s] %s", &szTime[11], szBuffer);
	// ---
	gServerDisplayer.LogAddText(Color, szTemp, strlen(szTemp));
}

void MsgBox(char * szLog, ...)
{
	char szBuffer[512] = "";
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, szLog);
	// ---
	vsprintf(szBuffer, szLog, pArguments);
	// ---
	va_end(pArguments);
	// ---
	MessageBox(NULL, szBuffer, "error", MB_OK|MB_APPLMODAL);
}