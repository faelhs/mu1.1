#ifndef _SERVER_INFO_H
#define _SERVER_INFO_H

#include "winutil.h"

struct CHARACTER_DATA
{
	short DefenseDW;
	short DefenseDK;
	short DefenseFE;
	short DefenseMG;
	short DefenseDL;
	// ---
	short MinimumMagicDamageDW;
	short MaximumMagicDamageDW;
	short MinimumDamageDW;
	short MaximumDamageDW;
	short AttackSpeedDW;
	short MagicSpeedDW;
	short BlockDW;
	// ---
	short MinimumDamageDK;
	short MaximumDamageDK;
	short MinimumMagicDamageDK;
	short MaximumMagicDamageDK;
	short AttackSpeedDK;
	short MagicSpeedDK;
	short BlockDK;
	// ---
	short MinimumDamageFE_NoBow;
	short MaximumDamageFE_NoBow;
	short MinimumDamageFE_StrBow;
	short MaximumDamageFE_StrBow;
	short MinimumDamageFE_AgiBow;
	short MaximumDamageFE_AgiBow;
	short MinimumMagicDamageFE;
	short MaximumMagicDamageFE;
	short AttackSpeedFE;
	short MagicSpeedFE;
	short BlockFE;
	// ---
	short MinimumDamageMG_Str;
	short MaximumDamageMG_Str;
	short MinimumDamageMG_Ene;
	short MaximumDamageMG_Ene;
	short MinimumMagicDamageMG;
	short MaximumMagicDamageMG;
	short AttackSpeedMG;
	short MagicSpeedMG;
	short BlockMG;
	// ---
	short MinimumDamageDL_Str;
	short MaximumDamageDL_Str;
	short MinimumDamageDL_Ene;
	short MaximumDamageDL_Ene;
	short MinimumMagicDamageDL;
	short MaximumMagicDamageDL;
	short AttackSpeedDL;
	short MagicSpeedDL;
	short BlockDL;
	// ---
	WORD PvPDamageRate[MAX_TYPE_PLAYER][MAX_TYPE_PLAYER];
	WORD PvMDamageRate[MAX_TYPE_PLAYER];
	WORD ReflectDamage;
};

struct SERVER_INFO_DATA
{
	char szServerName[50];
	char szGuardTalk[50];
	// ---
	int iServerVip;
	int iServerResetMin;
	int iServerResetMax;
	// ---
	int iMaxStatus;
	int iSkillNotLevel;
	int iItemDropTime;
	int iAncientAndExcellent;
	float fRateZen;
	int iStartMap[5];
	int iLevelUp[6];
	int iPotionHP[5];
	int iPotionMP[6];
	int iRings[6];
	int iExpParty[9];
	int iDropItemMonsterRate[6];
	// ---
	WORD wAngelAddDefense;
	WORD wSatanAddDamage;
	WORD wDinorantAddDamage;
	WORD wDarkHorseAddDamage;
};

struct COMMAND_INFO
{
	PBMSG_HEAD h;
	BYTE subcode;
	BYTE Permission[6][4];
	char Name[6][35];
};

class CServerInfo
{
public:
	void Load();
	void Connect();
	void Common();
	void Character();
	void SetInfo(int aIndex);
	void SendMain(int aIndex);
	// ---
	SERVER_INFO_DATA m_Data;
	CHARACTER_DATA m_Character;
	COMMAND_INFO _info;
};

extern CServerInfo gServerInfo;

#endif