#ifndef _VISUAL_FIX_H
#define _VISUAL_FIX_H

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;
	BYTE scode;
	BYTE result;
	BYTE NumberH;
	BYTE NumberL;
	BYTE CliVersion[5];
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;	// C1:DC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE DamageH;	// 5
	BYTE DamageL;	// 6
	BYTE DamageType;	// 7
	// ---
	int iAttackDamage;
};

struct PMSG_REFILL
{
	PBMSG_HEAD h;	// C1:26
	BYTE IPos;	// 3
	BYTE LifeH;	// 4
	BYTE LifeL;	// 5
	BYTE Flag;	// 6
	// ---
	int iLife;
};

struct PMSG_MANASEND
{
	PBMSG_HEAD h;	// C1:27
	BYTE IPos;	// 3
	BYTE ManaH;	// 4
	BYTE ManaL;	// 5
	BYTE BPH;	// 6
	BYTE BPL;	// 7
	// ---
	int iMana;
	int iBP;
};

struct PMSG_DIEPLAYER
{
	PBMSG_HEAD h;	// C1:17
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE Skill;	// 5
	BYTE KillerNumberH;	// 6
	BYTE KillerNumberL;	// 7
};

class CVisualFix
{
public:
	short aIndex;
	int AttackHP;
	int Life;
	int Mana;
	int AG;
	int MaxLife;
	int MaxMana;
	int MaxAG;
	int AttackRate;
	int DamageRate;

	char LifeTab[50];
	char ManaTab[50];
	char LifeTab2[50];
	char ManaTab2[50];
	char AGTab[50];

	void Load();

	void RecvIndex(PMSG_JOINRESULT * Data);
	void RecvDamage(PMSG_ATTACKRESULT * Data);
	void RecvHP(PMSG_REFILL * Data);
	void RecvMPAG(PMSG_MANASEND * Data);
	void RecvRespawn();
	void RecvKilledObject(PMSG_DIEPLAYER * Data);
	// ---
	static void DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6);

	static void DrawHp(float a1, float a2, int a3, float a4, float a5);
	static void DrawMp(float a1, float a2, int a3, float a4, float a5);
	static void DrawAg(float a1, float a2, int a3, float a4, float a5);

	static void DrawTabHP(signed int a1, signed int a2, LPCSTR lpMultiByteStr);
	static void DrawTabMP(signed int a1, signed int a2, LPCSTR lpMultiByteStr);
	static void DrawTabAG(signed int a1, signed int a2, LPCSTR lpMultiByteStr);

	static void InfoHp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);
	static void InfoMp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);
};

extern CVisualFix gVisualFix;

#endif