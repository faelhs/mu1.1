#ifndef _LOG_H
#define _LOG_H
// ---
#include "ServerDisplayer.h"
// ---
#define MAX_LOG 8
// ---
enum eLogType
{
	LOG_GENERAL    = 0,
	LOG_GAMESHOP   = 1,
	LOG_COMMAND    = 2,
	LOG_BOTMANAGER = 3,
	LOG_CHAT       = 4,
	LOG_TRADE      = 5,
};
// ---
struct LOG_INFO
{
	BOOL Active;
	char Directory[256];
	int Day;
	int Month;
	int Year;
	char Filename[256];
	HANDLE File;
};
// ---
class CLog
{
public:
	CLog();
	virtual ~CLog();
	// ---
	void AddLog(BOOL active, char* directory);
	void Output(eLogType type, char* text,...);
private:
	LOG_INFO m_LogInfo[MAX_LOG];
	// ---
	int m_count;
};
extern CLog gLog;
// ---
void LogAdd(eLogColor Color, char * szLog,...);
void MsgBox(char * szLog, ...);
// ---
#endif