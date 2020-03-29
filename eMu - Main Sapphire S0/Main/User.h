#ifndef _USER_H
#define _USER_H
// ---
#pragma pack(push, 1)
// ---
struct OBJECTSTRUCT_PLAYER
{
	char Name[11];
	char Class;
	BYTE Unknown12;
	BYTE Unknown13;
	__int16 Level;
	DWORD Experience;
	DWORD NextExperience;
	__int16 Strength;
	__int16 Dexterity;
	__int16 Vitality;
	__int16 Energy;
	__int16 Leadership;
	WORD Life;
	WORD Mana;
	WORD MaxLife;
	WORD MaxMana;
	__int16 AddStrength;
	__int16 AddDexterity;
	__int16 AddVitality;
	__int16 AddEnergy;
	WORD AddLeadership;
	WORD Unknown94;
	WORD Unknown96;
	WORD Stamina;
	WORD MaxStamina;
	BYTE ItemSpecialUseFlag;
	BYTE UnknownGap;
	WORD ItemSpecialUseTime[3];
	WORD AddPoint;
	WORD MaxAddPoint;
	WORD AttackSpeed;
	WORD DamageRate;
	WORD AttackRate;
	WORD DamageMin;
	WORD DamageMax;
	WORD Unknown92;
	WORD MagicSpeed;
	WORD Unknown110;
	WORD LevelPoint;
	BYTE MagicCount;
	WORD DefenseRate;
	WORD Defense;
	WORD pMagicList[150];
};
// ---
#pragma pack(pop)
// ---
class CUser
{
public:
	void Load();
	static void GetStruct();
	// ---
	DWORD dwGetStructJmp;
	// ---
	DWORD gTmpEax;
	DWORD gTmpEcx;
	DWORD gTmpEdx;
	DWORD gTmpEbx;
	DWORD gTmpEsp;
	DWORD gTmpEbp; 
	DWORD gTmpEsi;
	DWORD gTmpEdi;
	// ---
	DWORD dwStructAddr;
	// ---
	OBJECTSTRUCT_PLAYER m_Player;
};
// ---
extern CUser gUser;
// ---
#endif