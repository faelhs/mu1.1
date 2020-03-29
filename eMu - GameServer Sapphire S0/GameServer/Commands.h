#ifndef _COMMANDS_H
#define _COMMANDS_H

#include "protocol.h"

enum COMMAND_LIST
{
	COMMAND_POST,
	COMMAND_PKCLEAR,
	COMMAND_HEROCLEAR,
	COMMAND_EVO,
	COMMAND_ZEN,
	COMMAND_ADD,
	COMMAND_READD,
	COMMAND_WARE,
	COMMAND_OPENWARE,
	COMMAND_WAREINFO,
	COMMAND_ALTCLASS,
	COMMAND_CHARINFO,
	COMMAND_EVENT,
};

struct COMMANDS_DATA
{
	bool iEnabled;
	int  iVipOnly[4];
	int  iLevel[4];
	int  iMoney[4];
	int	 iResets[4];
	int  iMResets[4];
	int  iDelay;
	char szSintax[20];
	// ---
	int	 iWareType;
	int	 iWareNumber[4];
	int  iPostColor[4];
	// ---
	char szSintaxAdd[4][20];
	char szSintaxAlt[9][20];
	char szParameter[4][20];
};

class CCommands
{
public:
	void Load();
	// ---
	void Info(int aIndex);
	void Post(int aIndex, char *szMsg);
	void PkClear(int aIndex);
	void HeroClear(int aIndex);
	void Evo(int aIndex);
	void Money(int aIndex, char * szMsg);
	void ReAdd(int aIndex);
	void Add(int aIndex, char *szMsg, BYTE btType);
	void Ware(int aIndex, char * szMsg);
	void OpenWare(int aIndex);
	void WareInfo(int aIndex);
	void AltClass(int aIndex, BYTE btType);
	void CharInfo(int aIndex);
	// ---
	bool IsCheck(LPOBJ lpObj, int iCommand);
	void Manager(PMSG_CHATDATA * lpMsg, int aIndex);
	// ---
	COMMANDS_DATA m_Data[100];
};

extern CCommands gCommands;

#endif