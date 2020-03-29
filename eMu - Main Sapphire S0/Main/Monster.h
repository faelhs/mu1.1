#ifndef _MONSTER_H
#define _MONSTER_H

struct OBJECT_STRUCT_PREVIEW
{
	BYTE gap0[2];
	WORD word2;
	DWORD dword4;
	BYTE byte8;
	BYTE gap9[3];
	float fScalarMode;
	float float10;
	float float14;
	float float18;
	BYTE gap1C[60];
	DWORD dword58;
	BYTE gap5C[8];
	DWORD dword64;
	DWORD dword68;
	BYTE gap6C[12];
	DWORD dword78;
	BYTE gap7C[8];
	BYTE byte84;
	BYTE gap85[8];
	BYTE byte8D;
	BYTE gap8E[6];
	BYTE byte94;
	BYTE gap95[79];
	BYTE byteE4;
	BYTE gapE5[43];
	DWORD dword110;
	DWORD dword114;
	BYTE gap118[20];
	DWORD dword12C;
	DWORD dword130;
	DWORD dword134;
	BYTE gap138[52];
	DWORD dword16C;
	BYTE gap170[86];
	WORD word1C6;
	BYTE btCtlCode;
	// ---
	char	Name[25];
	// ---
	BYTE gap1CA[46];
	// ---
	short	HelmSlot;
	BYTE	HelmLevel;
	BYTE	HelmExcellent;
	BYTE	HelmAncient;
	// ---
	BYTE gap213[27];
	// ---
	short	ArmorSlot;
	BYTE	ArmorLevel;
	BYTE	ArmorExcellent;
	BYTE	ArmorAncient;
	// ---
	BYTE gap233[27];
	// ---
	short	PantsSlot;
	BYTE	PantsLevel;
	BYTE	PantsExcellent;
	BYTE	PantsAncient;
	// ---
	BYTE gap253[27];
	// ---
	short	GlovesSlot;
	BYTE	GlovesLevel;
	BYTE	GlovesExcellent;
	BYTE	GlovesAncient;
	// ---
	BYTE gap273[27];
	// ---
	short	BootsSlot;
	BYTE	BootsLevel;
	BYTE	BootsExcellent;
	BYTE	BootsAncient;
	// ---
	BYTE gap293[27];
	// ---
	WORD	WeaponFirstSlot;
	BYTE	WeaponFirstLevel;
	BYTE	WeaponFirstExcellent;
	BYTE	WeaponFirstAncient;
	// ---
	BYTE gap2B4[27];
	// ---
	WORD	WeaponSecondSlot;
	BYTE	WeaponSecondLevel;
	BYTE	WeaponSecondExcellent;
	BYTE	WeaponSecondAncient;
	// ---
	BYTE gap2D3[27];
	// ---
	short	WingsSlot;
	BYTE	WingsLevel;
	BYTE	WingsExcellent;
	BYTE	WingsAncient;
	// ---
	BYTE gap2D3_01[27];
	// ---
	short	PetSlot;
	BYTE	PetLevel;
	BYTE	PetExcellent;
	BYTE	PetAncient;
	// ---
	BYTE gap2D3_02[67];
	BYTE btStateCode;
	BYTE gap2D3_04[20];
	BYTE m_btPkLevel;
	BYTE gap2D3_03[4];
	BYTE byte36D;
	WORD word36E;
	BYTE gap370[14];
	WORD word37E;
	BYTE gap380[2];
	BYTE byte382;
	BYTE gap383[9];
	DWORD dword38C;
	BYTE gap390[12];
	WORD word39C;
	BYTE gap39E[62];
	BYTE byte3DC;
};

#define pCreateMonster			((int(__cdecl*)(int Key, int ObjectId, int PositionX, int PositionY, int a5)) 0x00509410)
#define	pOpenMonsterModel		((void(__cdecl*)(int iMonsterID)) 0x005FFC10)
#define pLoadMonster			((int(__cdecl*)(int iObjectId, int iPositionX, int iPositionY, int iKey)) 0x0050ACD0)
#define pMonsterStruct			((int(__cdecl*)(int iIndex, int iObjectId)) 0x0050ABB0)

class CMonster
{
public:
	void Load();
	static int LoadMonster(int iObjectId, int iPositionX, int iPositionY, int iKey);
	void LoadModel(int iObjectId);
};

extern CMonster gMonster;

#endif