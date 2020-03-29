#ifndef _MASTER_RESET_H
#define _MASTER_RESET_H

struct MASTER_RESET_DATA
{
	bool bEnabled;
	int iResetStatus;
	int iMover;
	int iRelogar;
	int iGold;
	int iCash;
	// ---
	int iResets;
	int iLevel;
	int iMoney;
	int iLevelReborn;
	// ---
	int iResetQuest;
	int iResetSkills;
	// ---
	WORD wStrength;
	WORD wDexterity;
	WORD wVitality;
	WORD wEnergy;
	WORD wLeadership;
};

class CMasterReset
{
public:
	void Load();
	void Init(LPOBJ lpObj);
	// ---
	char szSintax[50];
	// ---
	MASTER_RESET_DATA m_Data[4];
};

extern CMasterReset gMasterReset;

#endif