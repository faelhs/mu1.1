#ifndef _RESET_H
#define _RESET_H

struct RESET_DATA
{
	int iEnabled;
	int iType;
	int iMove;
	int iRelogar;
	int iVip;
	int iResetMin;
	int iResetMax;
	short sLevel;
	int iMoney;
	int iPoints;
	int iResetQuest;
	int iResetSkills;
	// ---
	int	iReturnLevel;
	// ---
	WORD wReturnStrength;
	WORD wReturnDexterity;
	WORD wReturnVitality;
	WORD wReturnEnergy;
	WORD wReturnLeadership;
};

class CReset
{
public:
	void Load();
	void Init(LPOBJ lpObj);
	// ---
	int iCount;
	// ---
	char szSintax[50];
	// ---
	RESET_DATA m_Data[255];
};

extern CReset gReset;

#endif