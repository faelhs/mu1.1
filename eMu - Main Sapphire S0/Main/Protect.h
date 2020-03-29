#ifndef _PROTECT_H
#define _PROTECT_H

#include "Plugins.h"

struct PROTECT_DATA
{
	char szTitle[32];
	char szIP[16];
	char szVersion[8];
	char szSerial[17];
	// ---
	PLUGIN_INFO_DATA PluginInfo[MAX_PLUGINS];
};

class CProtect
{
public:
	bool Load(char* szName);
	// ---
	PROTECT_DATA m_Data;
	// ---
	DWORD m_FileCrc;
};

extern CProtect gProtect;

#endif