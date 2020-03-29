#ifndef _TOOLKIT_H
#define _TOOLKIT_H

struct PMSG_REFRESH_CHAR
{
	PBMSG_HEAD h;	// C3:F3:03
	BYTE subcode;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
	BYTE MapNumber;	// 6
	BYTE Dir;	// 7
	DWORD Exp;	// 8
	DWORD NextExp;	// C
	WORD LevelUpPoint;	// 10
	WORD Str;	// 12
	WORD Dex;	// 14
	WORD Vit;	// 16
	WORD Energy;	// 18
	WORD Life;	// 1A
	WORD MaxLife;	// 1C
	WORD Mana;	// 1E
	WORD MaxMana;	// 20
	WORD BP;	// 26
	WORD MaxBP;	// 28
	int Money;	// 2C
	BYTE PkLevel;	// 30
	BYTE CtlCode;	// 31
	short AddPoint;	// 32
	short MaxAddPoint;	// 34
	WORD Leadership;	// 36
	WORD wMinusPoint;	// 38
	WORD wMaxMinusPoint;	// 3A
};

struct PMSG_REFRESH_REGEN 
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char MapX;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char MapY;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char MapNumber;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Dir;
  /*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short Life;
  /*<thisrel this+0xa>*/ /*|0x2|*/ unsigned short Mana;
  /*<thisrel this+0xe>*/ /*|0x2|*/ unsigned short BP;
  /*<thisrel this+0x10>*/ /*|0x4|*/ unsigned long Exp;
  /*<thisrel this+0x14>*/ /*|0x4|*/ unsigned long Money;
};

class CToolKit
{
public:
	void Refresh(DWORD aIndex);
	void SendMsg(int iColor, char * szMsg, ...);
	char * GetMapName(int iMapNumber);
	int ExcOpt(int amount);
};

float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float fDefault, LPCSTR lpFileName);

extern CToolKit gToolKit;

#endif