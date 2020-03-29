#ifndef _PROTOCOL_H
#define _PROTOCOL_H

struct PROTOCOL_DATA
{
	BYTE Class;
	WORD Dexterity;
	WORD AttackSpeed;
	WORD MagicSpeed;
};

class CProtocol
{
public:
	void Load();
	// ---
	static void DataRecvEx(DWORD Case, LPBYTE lpMsg, int Len, int aIndex);
	// ---
	static void LevelUp();
	// ---
	PROTOCOL_DATA m_Data;
};

void AgilityFix();

extern CProtocol gProtocol;

#endif