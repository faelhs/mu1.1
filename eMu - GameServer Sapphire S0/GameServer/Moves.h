#ifndef _MOVES_H
#define _MOVES_H

#include "user.h"

struct MOVES_DATA
{
	char  szSintax[255];
	char  szVip;
	char  szPK;
	short sLevel;
	short sMap;
	short sCordX;
	short sCordY;
	bool bEnabled;
};

class CMoves
{
public:
	void Load();
	void Init(LPOBJ lpObj, bool bEnabled, char szVip, char szPK, short sLevel, short sMap, short sCordX, short sCordY);
	// ---
	MOVES_DATA m_Data[255];
	// ---
	int iCount;
};

extern CMoves gMoves;

#endif