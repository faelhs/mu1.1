// ------------------------------
// Decompiled by Deathway
// Date : 2007-05-09
// ------------------------------
#ifndef USER_H__
#define USER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkillDelay.h"
#include "ComboAttack.h"
#include "giocp.h"
#include "..\ggsvr\ggsvr.h"
#include "MagicInf.h"
#include "zzzitem.h"
#include "classdef.h"
#include "..\include\define.h"
#include "GuildClass.h"
#include "TDurMagicKeyChecker.h"


#if (GS_CASTLE == 1)


#define OBJMAX 4000
#define OBJMAXUSER 1500
#define OBJ_MAXMONSTER 1500

#else

#define OBJMAX 7400
#define OBJMIN 5400
#define OBJMAXUSER 1000
#define OBJ_MAXMONSTER 5800

#endif

#define OBJ_STARTUSERINDEX (OBJMAX - OBJMAXUSER)
#define OBJ_CALLMONCOUNT (OBJ_STARTUSERINDEX - OBJ_MAXMONSTER)
#define MAX_MONSTER_SEND_MSG	10
#define MAX_MONSTER_SEND_ATTACK_MSG	50
#define MAX_MONSTER_TYPE 512
#define MAX_GUILD_LEN 8
#define MAX_ACCOUNT_LEN 10
#define INVENTORY_SIZE 108
#define WAREHOUSE_SIZE 120
#define TRADE_BOX_SIZE 32
#define MAGIC_SIZE 60
#define INVETORY_WEAR_SIZE	12
#define INVENTORY_BAG_START INVETORY_WEAR_SIZE
#define MAIN_INVENTORY_SIZE 76	// Not included PersonalSh
#define INVENTORY_MAP_SIZE 96	// Not included wared iems
#define TRADE_BOX_MAP_SIZE 32
#define PSHOP_SIZE 32
#define PSHOP_MAP_SIZE 32
#define MAX_CHAR_LEVEL	400
#define MAX_SELF_DEFENSE 5
#define MAX_ST_HIT_DAMAGE 40
#define MAX_ZEN 2000000000
#define MAX_WAREHOUSE_ZEN	100000000
#define ACTIVE_ITEM_SEARCH 0
#define CHAOS_BOX_SIZE 32
#define CHAOS_BOX_MAP_SIZE 32

enum MAP_INDEX
{
	MAP_INDEX_LORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_BATTLESOCCER = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
	MAP_INDEX_CHAOSCASTLE1 = 0x12,
	MAP_INDEX_CHAOSCASTLE2 = 0x13,
	MAP_INDEX_CHAOSCASTLE3 = 0x14,
	MAP_INDEX_CHAOSCASTLE4 = 0x15,
	MAP_INDEX_CHAOSCASTLE5 = 0x16,
	MAP_INDEX_CHAOSCASTLE6 = 0x17,
	MAP_INDEX_KALIMA1 = 0x18,
	MAP_INDEX_KALIMA2 = 0x19,
	MAP_INDEX_KALIMA3 = 0x1a,
	MAP_INDEX_KALIMA4 = 0x1b,
	MAP_INDEX_KALIMA5 = 0x1c,
	MAP_INDEX_KALIMA6 = 0x1d,
	MAP_INDEX_CASTLESIEGE = 0x1e,
	MAP_INDEX_CASTLEHUNTZONE = 0x1f,
	MAP_INDEX_DEVILSQUARE2 = 0x20,
	MAP_INDEX_AIDA = 0x21,
	MAP_INDEX_KALIMA7 = 0x24,
};

enum EXP_GETTING_EVENT_TYPE {
	EVENT_TYPE_NONE = 0x0,
	EVENT_TYPE_PARTY = 0x1,
	EVENT_TYPE_DEVILSQUARE = 0x2,
	EVENT_TYPE_CHAOSCASTLE = 0x3,
	EVENT_TYPE_BLOODCASTLE = 0x4,
	EVENT_TYPE_CRYWOLF = 0x5,
};


#define MAX_RESISTENCE_TYPE 7

#define R_ICE			0
#define R_POISON		1
#define R_LIGHTNING		2
#define R_FIRE			3
#define R_EARTH			4
#define R_WIND			5
#define R_WATER			6


#define OBJ_EMPTY -1
#define OBJ_MONSTER 2
#define OBJ_USER 1
#define OBJ_NPC	3
#define MAX_PARTY_LEVEL_DIFFERENCE	130
#define MAX_MAGIC 60
#define MAX_VIEWPORT 75

#if GS_CASTLE==1
#	define MAX_VIEWPORT_MONSTER 75
#else
#	define MAX_VIEWPORT_MONSTER 20
#endif

#define MAX_ROAD_PATH_TABLE 16
#define MAX_ARRAY_FRUSTRUM 4
#define PLAYER_EMPTY  0
#define PLAYER_CONNECTED 1
#define PLAYER_LOGGED 2
#define PLAYER_PLAYING 3
#define MAX_CHECKSUM_KEY 1024
#define OBJMAX_RANGE(aIndex) ( ((aIndex) < 0 )?FALSE:( (aIndex) > OBJMAX-1 )?FALSE:TRUE   )
#define FRIEND_SERVER_STATE_LOGIN_FAIL	0
#define FRIEND_SERVER_STATE_OFFLINE		1
#define FRIEND_SERVER_STATE_ONLINE		2

#define MAIN_INVENTORY_RANGE(x) (((x)<0)?FALSE:((x)>MAIN_INVENTORY_SIZE-1)?FALSE:TRUE )
#define INVENTORY_RANGE(x) (((x)<0)?FALSE:((x)>INVENTORY_SIZE-1)?FALSE:TRUE )
#define WAREHOUSE_RANGE(x) (((x)<0)?FALSE:((x)>WAREHOUSE_SIZE-1)?FALSE:TRUE )
#define TRADE_BOX_RANGE(x) (((x)<0)?FALSE:((x)>TRADE_BOX_SIZE-1)?FALSE:TRUE )
#define OBJMON_RANGE(x) ( ((x)<0)?FALSE:((x)>OBJ_MAXMONSTER-1)?FALSE:TRUE)
#define PSHOP_RANGE(x) ( (((x)-MAIN_INVENTORY_SIZE)<0)?FALSE:(((x)-MAIN_INVENTORY_SIZE)>(INVENTORY_SIZE-MAIN_INVENTORY_SIZE-1))?FALSE:TRUE )
#define ATTRIBUTE_RANGE(x) (((x)<51)?FALSE:((x)>58)?FALSE:TRUE )

#define CURRENT_DB_VERSION	3

#define CHAR_SET_SIZE		18

	#define CS_CLASS		0

	#define CS_WEAPON1_TYPE	1
	#define CS_WEAPON2_TYPE	2

	#define CS_WEAPON1_DATA	12
	#define CS_WEAPON2_DATA	13

	#define CS_HELMET1		13
	#define CS_HELMET2		9
	#define CS_HELMET3		3

	#define CS_ARMOR1		14
	#define CS_ARMOR2		9
	#define CS_ARMOR3		3

	#define CS_PANTS1		14
	#define CS_PANTS2		9
	#define CS_PANTS3		4

	#define CS_GLOVES1		15
	#define CS_GLOVES2		9
	#define CS_GLOVES3		4

	#define CS_BOOTS1		15
	#define CS_BOOTS2		9
	#define CS_BOOTS3		5



#define CHECK_LIMIT(value, limit) ( ((value)<0)?FALSE:((value)>((limit)-1))?FALSE:TRUE  )
#define CHECK_LIMIT2(value, base, limit) ( ((value)<base)?FALSE:((value)>((limit)-1))?FALSE:TRUE  )
#define CHECK_CLASS(value, type) ( ((value)!=(type))?FALSE:TRUE )


#define CS_GET_CLASS(x) ( (((x)>>4)<<5)&(0xE0) )
#define CS_GET_CHANGEUP(x) ( ((x)&0x07) )
#define CS_SET_CLASS(x) ( ((x)<<5)& 0xE0 )
#define CS_SET_CHANGEUP(x) ( ((x) << 4) & 0x10 )

#define CS_SET_HELMET1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_HELMET2(x) ( ((x) & 0x10 ) << 3 )
#define CS_SET_HELMET3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_ARMOR1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_ARMOR2(x) ( ((x) & 0x10 ) << 2 )
#define CS_SET_ARMOR3(x) ( ((x) & 0x0F )      )

#define CS_SET_PANTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_PANTS2(x) ( ((x) & 0x10 ) << 1 )
#define CS_SET_PANTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_GLOVES1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_GLOVES2(x) ( ((x) & 0x10 )      )
#define CS_SET_GLOVES3(x) ( ((x) & 0x0F )      )

#define CS_SET_BOOTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_BOOTS2(x) ( ((x) & 0x10 ) >> 1 )
#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_WING1(x)  ( ((x) & 0x03 ) << 2 )
#define CS_SET_HELPER(x) ( ((x) & 0x03 )      )

#define CS_SET_SMALLLEVEL_RH(x)		( (x)       )
#define CS_SET_SMALLLEVEL_LH(x)		( (x) << 3  ) 
#define CS_SET_SMALLLEVEL_HELMET(x)	( (x) << 6  )
#define CS_SET_SMALLLEVEL_ARMOR(x)	( (x) << 9  )
#define CS_SET_SMALLLEVEL_PANTS(x)	( (x) << 12 )
#define CS_SET_SMALLLEVEL_GLOVES(x)	( (x) << 15 )
#define CS_SET_SMALLLEVEL_BOOTS(x)	( (x) << 18 )

#define CS_SET_SMALLLEVEL1(x)		( ((x) >> 16) & 0xFF )
#define CS_SET_SMALLLEVEL2(x)		( ((x) >> 8 ) & 0xFF )
#define CS_SET_SMALLLEVEL3(x)		((x) & 0xFF )



#include "ViewPortGuild.h"

typedef union tagPATHTABLE
{
	short sPathTable[16];
	char cPathTable[32];
} PATHTABLE, * LPPATHTABLE;

typedef struct tagActionState
{
	unsigned long Rest:1;	// 0
	unsigned long Attack:1;	// 1
	unsigned long Move:1;	// 2
	unsigned long Escape:1;	// 3
	unsigned long Emotion:4;	// 4
	unsigned long EmotionCount:8;	// 8

} ACTION_STATE, * LPACTION_STATE;

typedef struct tagInterfaceState
{
	DWORD use	: 2;
	DWORD state : 4;
	DWORD type	: 10;

} INTERFACE_STATE, * LPINTERFACE_STATE;



typedef struct
{
	DWORD unk0 : 1;
	DWORD unk1 : 1;
	DWORD unk2 : 1;
	DWORD unk3 : 1;
	DWORD unk4 : 1;
	DWORD unk5 : 1;
	DWORD unk6 : 1;
	DWORD unk7 : 1;
	DWORD unk8 : 1;
	DWORD unk9 : 1;
	DWORD unkA : 1;
	DWORD unkB : 1;
	DWORD unkC : 1;
	DWORD unkD : 1;
	DWORD unkE : 1;
	DWORD unkF : 1;
	DWORD unk10: 1;

}  ST_SKILL_STATE;


union STU_SKILL_STATE
{
	ST_SKILL_STATE SkillStates;
	DWORD AllData;
};



extern short RoadPathTable[MAX_ROAD_PATH_TABLE];
extern int  gServerMaxUser;	
extern BOOL g_EnergyCheckOff;

struct HITDAMAGE_STRUCT
{
	short number;	// 0
	int HitDamage;	// 4
	DWORD LastHitTime;	// 8
};

struct VIEWPORT_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8
};

struct VIEWPORT_PLAYER_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8

};

struct MessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	DWORD MsgTime;	// 8
	int SubCode;	// C

};

struct ExMessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	DWORD MsgTime;	// 8
	int SubCode;	// C
	int SubCode2;	// 10
};

typedef struct tagSEND_MONSTER_ATTACK_MENSSAGE
{
	int iMsgCode;	// unk0
	int iIndex;	// unk4
	DWORD dwDelay;	// unk8
	int iSubCode;	// unkC
	int iSubCode2;	// unk10
}SEND_MONSTER_ATTACK_MENSSAGE;

extern ExMessageStateMachine gSMAttackProcMsg[OBJMAX][MAX_MONSTER_SEND_ATTACK_MSG];
extern MessageStateMachine gSMMsg[OBJMAX][MAX_MONSTER_SEND_MSG];




struct OBJECTSTRUCT
{
	int m_Index;
	BYTE Connected;
	char LoginMsgSnd;
	char LoginMsgCount;
	char CloseCount;
	char CloseType;
	BYTE bEnableDelCharacter;
	struct _PER_SOCKET_CONTEXT* PerSocketContext;
	SOCKET m_socket;
	char Ip_addr[16];
	int UserNumber;
	int DBNumber;
	BYTE Magumsa;
	DWORD AutoSaveTime;
	DWORD ConnectCheckTime;
	DWORD CheckTick;
	BYTE CheckSpeedHack;
	DWORD CheckTick2;
	BYTE CheckTickCount;
	DWORD SaveTimeForStatics;
	int iPingTime; 
	BYTE m_TimeCount;
	DWORD m_dwPKTimer;
	short CheckSumTableNum;
	DWORD CheckSumTime;
	WORD Type;
	unsigned char Live;
	char CharacterPos;
	char AccountID[11];
	char Name[11];
	char LastJoominNumber[14];
	bool PlusStatQuestClear;
	bool ComboSkillquestClear;
	struct ComboSkillData comboSkill;
	WORD Class;
	BYTE DbClass;
	BYTE ChangeUP;
	short Level;
	int LevelUpPoint;
	int iFruitPoint;
	DWORD Experience;
	DWORD NextExp;
	int Money;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	float Life;
	float MaxLife;
	int m_iScriptMaxLife;
	float FillLife;
	float FillLifeMax;
	float Mana;
	float MaxMana;
	WORD Leadership;
	WORD AddLeadership;
	WORD ChatLimitTime;
	BYTE ChatLimitTimeSec;
	BYTE FillLifeCount;
	short AddStrength;
	short AddDexterity;
	short AddVitality;
	short AddEnergy;
	int BP;
	int MaxBP;
	int AddBP;
	float VitalityToLife;
	float EnergyToMana;
	char m_PK_Count;
	char m_PK_Level;
	int m_PK_Time;
	short X;
	short Y;
	BYTE Dir;
	BYTE MapNumber;
	int AddLife;
	int AddMana;
	BYTE DamageMinus;
	BYTE DamageReflect;
	short MonsterDieGetMoney;
	BYTE MonsterDieGetLife;
	BYTE MonsterDieGetMana;
	BYTE StartX;
	BYTE StartY;
	short m_OldX;
	short m_OldY;
	short TX;
	short TY;
	short MTX;
	short MTY;
	int PathCount;
	int PathCur;
	char PathStartEnd;
	short PathOri[15];
	short PathX[15];
	short PathY[15];
	char PathDir[15];
	DWORD PathTime;
	BYTE m_MoveGateNumber;
	DWORD Authority;
	DWORD AuthorityCode;
	DWORD Penalty;
	BYTE m_cAccountItemBlock;
	struct tagActionState m_ActState;
	BYTE m_ActionNumber;
	DWORD m_State;
	char m_StateSub;
	unsigned char m_Rest;
	char m_ViewState;
	int m_ViewSkillState;
	DWORD m_LastMoveTime;
	DWORD m_LastAttackTime;
	BYTE m_FriendServerOnline;
	int m_DetectSpeedHackTime;
	unsigned long m_SumLastAttackTime;
	unsigned long m_DetectCount;
	int m_DetectedHackKickCount;
	int m_SpeedHackPenalty;
	unsigned char m_AttackSpeedHackDetectedCount;
	unsigned long m_PacketCheckTime;
	unsigned char m_ShopTime;
	unsigned long m_TotalAttackTime;
	int m_TotalAttackCount;
	unsigned long TeleportTime;
	char Teleport;
	char KillerType;
	char DieRegen;
	char RegenOk;
	BYTE RegenMapNumber;
	BYTE RegenMapX;
	BYTE RegenMapY;
	DWORD RegenTime;
	DWORD MaxRegenTime;
	short m_PosNum;
	DWORD LifeRefillTimer;
	DWORD CurActionTime;
	DWORD NextActionTime;
	DWORD DelayActionTime;
	char DelayLevel;
	char m_PoisonType;
	char m_IceType;
	char m_PoisonBeattackCount;
	char m_ColdBeattackCount;
	char m_ImmuneToMagicCount;
	char m_ImmuneToHarmCount;
	char m_iMonsterBattleDelay;
	char m_cKalimaGateExist;
	int m_iKalimaGateIndex;
	char m_cKalimaGateEnterCount;
	struct OBJECTSTRUCT* lpAttackObj;
	short m_SkillNumber;
	DWORD m_SkillTime;
	bool m_bAttackerKilled;
	char m_ManaFillCount;
	char m_LifeFillCount;
	int SelfDefense[5];
	DWORD SelfDefenseTime[5];
	DWORD MySelfDefenseTime;
	char m_Drink;
	int m_SkillDefense;
	char m_SkillDefenseTime;
	int m_SkillAttack;
	char m_SkillAttackTime;
	int m_SkillAttack2;
	char m_SkillAttackTime2;
	int m_SkillAddLife;
	int m_SkillAddLifeTime;
	int m_SkillHarden;
	int m_SkillHardenTime;
	int m_SkillMagumReduceDefense;
	int m_SkillMagumReduceDefenseTime;
	int PartyNumber;
	int PartyTargetUser;
	int GuildNumber;
	struct _GUILD_INFO_STRUCT* lpGuild;
	char GuildName[11];
	int GuildStatus;
	int iGuildUnionTimeStamp;
	int m_RecallMon;
	int m_Change;
	short TargetNumber;
	short TargetShopNumber;
	short ShopNumber;
	short LastAttackerID;
	int m_AttackDamageMin;
	int m_AttackDamageMax;
	int m_MagicDamageMin;
	int m_MagicDamageMax;
	int m_AttackDamageLeft;
	int m_AttackDamageRight;
	int m_AttackDamageMaxLeft;
	int m_AttackDamageMinLeft;
	int m_AttackDamageMaxRight;
	int m_AttackDamageMinRight;
	int m_AttackRating;
	int m_AttackSpeed;
	int m_MagicSpeed;
	int m_Defense;
	int m_MagicDefense;
	int m_SuccessfulBlocking;
	short m_MoveSpeed;
	short m_MoveRange;
	short m_AttackRange;
	short m_AttackType;
	short m_ViewRange;
	short m_Attribute;
	short m_ItemRate;
	short m_MoneyRate;
	int m_CriticalDamage;
	int m_ExcelentDamage;
	class CMagicInf* m_lpMagicBack;
	class CMagicInf* Magic;
	char MagicCount;
	unsigned char UseMagicNumber;
	unsigned long UseMagicTime;
	char UseMagicCount;
	short OSAttackSerial;
	unsigned char SASCount;
	DWORD SkillAttackTime;
	unsigned char CharSet[18];
	char m_Resistance[MAX_RESISTENCE_TYPE];
	char m_AddResistance[MAX_RESISTENCE_TYPE];
	int FrustrumX[MAX_ARRAY_FRUSTRUM];
	int FrustrumY[MAX_ARRAY_FRUSTRUM];
	struct VIEWPORT_STRUCT VpPlayer[MAX_VIEWPORT];
	struct VIEWPORT_PLAYER_STRUCT VpPlayer2[MAX_VIEWPORT];
	int VPCount;
	int VPCount2;
	struct HITDAMAGE_STRUCT sHD[MAX_ST_HIT_DAMAGE];
	short sHDCount;
	struct tagInterfaceState m_IfState;
	DWORD m_InterfaceTime;
	class CItem* pInventory;
	LPBYTE pInventoryMap;
	char* pInventoryCount;
	char pTransaction;
	class CItem* Inventory1;
	LPBYTE InventoryMap1;
	char InventoryCount1;
	class CItem* Inventory2;
	LPBYTE InventoryMap2;
	char InventoryCount2;
	class CItem* Trade;
	LPBYTE TradeMap;
	int TradeMoney;
	bool TradeOk;
	class CItem* pWarehouse;
	LPBYTE pWarehouseMap;
	char WarehouseCount;
	short WarehousePW;
	BYTE WarehouseLock;
	BYTE WarehouseUnfailLock;
	int WarehouseMoney;
	int WarehouseSave;
	class CItem* pChaosBox;
	LPBYTE pChaosBoxMap;
	int ChaosMoney;
	int ChaosSuccessRate;
	BOOL ChaosLock;
	DWORD m_Option;
	int m_nEventScore;
	int m_nEventExp;
	int m_nEventMoney;
	BYTE m_bDevilSquareIndex;
	bool m_bDevilSquareAuth;
	char m_cBloodCastleIndex;
	char m_cBloodCastleSubIndex;
	int m_iBloodCastleEXP;
	bool m_bBloodCastleComplete;
	char m_cChaosCastleIndex;
	char m_cChaosCastleSubIndex;
	int m_iChaosCastleBlowTime;
	char m_cKillUserCount;
	char m_cKillMonsterCount;
	int m_iDuelUserReserved;
	int m_iDuelUserRequested;
	int m_iDuelUser;
	BYTE m_btDuelScore;
	int m_iDuelTickCount;
	bool m_bPShopOpen;
	bool m_bPShopTransaction;
	bool m_bPShopItemChange;
	bool m_bPShopRedrawAbs;
	char m_szPShopText[36];
	bool m_bPShopWantDeal;
	int m_iPShopDealerIndex;
	char m_szPShopDealerName[10];
	struct _RTL_CRITICAL_SECTION m_critPShopTrade;
	int m_iVpPShopPlayer[MAX_VIEWPORT];
	WORD m_wVpPShopPlayerCount;
	bool IsInBattleGround;
	bool HaveWeaponInHand;
	short EventChipCount;
	int MutoNumber;
	BOOL UseEventServer;
	bool LoadWareHouseInfo;
	int iStoneCount;
	BYTE m_Quest[50];
	bool m_SendQuestInfo;
	int m_SkyBossMonSheildLinkIndex;
	int m_SkyBossMonSheild;
	int m_SkyBossMonSheildTime;
	int m_MaxLifePower;
	int m_WizardSkillDefense;
	int m_WizardSkillDefenseTime;
	int m_PacketChecksumTime;
	int m_CheckLifeTime;
	unsigned char m_MoveOtherServer;
	char BackName[11];
	char m_BossGoldDerconMapNumber;
	char m_LastTeleportTime;
	BYTE m_ClientHackLogCount;
	BOOL m_bIsInMonsterHerd;
	BOOL m_bIsMonsterAttackFirst;
	class MonsterHerd* m_lpMonsterHerd;
	int fSkillFrustrumX[MAX_ARRAY_FRUSTRUM];
	int fSkillFrustrumY[MAX_ARRAY_FRUSTRUM];
	BYTE SkillHellFire2State;
	BYTE SkillHellFire2Count;
	DWORD SkillHellFire2Time;
	unsigned char m_ReqWarehouseOpen;
	int m_NotAttackAreaCount;
	short SetOpAddSkillAttack;
	short SetOpAddExDamage;
	short SetOpAddExDamageSuccessRate;
	short SetOpAddCriticalDamage;
	short SetOpAddCriticalDamageSuccessRate;
	short SetOpIncAGValue;
	short SetOpAddDamage;
	short SetOpAddMinAttackDamage;
	short SetOpAddMaxAttackDamage;
	short SetOpAddAttackDamage;
	short SetOpAddDefence;
	short SetOpAddDefenceRate;
	short SetOpAddMagicPower;
	BYTE SetOpIgnoreDefense;
	BYTE SetOpDoubleDamage;
	BYTE SetOpTwoHandSwordImproveDamage;
	BYTE SetOpImproveSuccessAttackRate;
	BYTE SetOpReflectionDamage;
	BYTE SetOpImproveSheldDefence;
	BYTE SetOpDecreaseAG;
	BYTE SetOpImproveItemDropRate;
	bool IsFullSetItem;
	class TDurMagicKeyChecker DurMagicKeyChecker;
	WORD SkillRecallParty_Time;
	BYTE SkillRecallParty_MapNumber;
	BYTE SkillRecallParty_X;
	BYTE SkillRecallParty_Y;
	WORD SkillAddCriticalDamageTime;
	WORD SkillAddCriticalDamage;
	bool bIsChaosMixCompleted;
	bool SkillLongSpearChange;
	class CSkillDelay SkillDelay;
	int iObjectSecTimer;
	bool m_bMapSvrMoveQuit;
	bool m_bMapSvrMoveReq;
	DWORD m_dwMapSvrQuitTick;
	short m_sPrevMapSvrCode;
	short m_sDestMapNumber;
	BYTE m_btDestX;
	BYTE m_btDestY;
	bool m_bIsCastleNPCUpgradeCompleted;
	BYTE m_btWeaponState;
	int m_iWeaponUser;
	BYTE m_btKillCount;
	int m_iSkillStunTime;
	int m_iSkillBrandOfSkillTime;
	int m_iSkillInvisibleTime;
	int m_iSkillManaSwellTime;
	int m_iSkillManaSwell;
	int m_iAccumulatedDamage;
	int m_iPotionBlessTime;
	int m_iPotionSoulTime;
	int m_iAccumulatedCrownAccessTime;
	int m_iGroupNumber;
	int m_iSubGroupNumber;
	int m_iGroupMemberGuid;
	int m_iRegenType;
	int m_iLastAutomataRuntime;
	int m_iLastAutomataDelay;
	int m_iCrywolfMVPScore;
	DWORD m_dwLastCheckTick;
	int m_iAutoRecuperationTime;
	int m_iSkillNPCHelpTime;
	int m_iSkillNPCDefense;
	int m_iSkillNPCAttack;
	int m_iMuseElfInfinityArrowSkillTime;
	int m_iSkillDistanceErrorCount;
	DWORD m_dwSkillDistanceErrorTick;

#if (GS_CASTLE == 1)
	union
	{
		struct
		{
			BYTE m_btCsNpcExistVal1;
			BYTE m_btCsNpcExistVal2;
			BYTE m_btCsNpcExistVal3;
			BYTE m_btCsNpcExistVal4;
		};

		int m_iCsNpcExistVal;
	};

	BYTE m_btCsNpcType;
	BYTE m_btCsGateOpen;
	int m_iCsGateLeverLinkIndex;
	BYTE m_btCsNpcDfLevel;
	BYTE m_btCsNpcRgLevel;
	BYTE m_btCsJoinSide;
	bool m_bCsGuildInvolved;
	BYTE m_btLifeStoneCount;
	BYTE m_btCreationState;
	int m_iCreatedActivationTime;
#endif

	int m_Vip;

	int m_Resets;
	int m_MasterResets;

	int m_Cash;
	int m_Gold;

	int m_DelayPost;
	int m_DelayWare;
	int m_DelayOpenWare;

	bool bReconnect;

	int m_WareNumber;

};

typedef OBJECTSTRUCT * LPOBJ;

class BILL_CLASS
{

private:

	char cCertifyType;
	BYTE PayCode;
	int EndTime;
	char EndsDays[13];

public:

	BILL_CLASS()
	{
		this->Init();
	}

	void Init()
	{
		this->cCertifyType=-1;
		this->PayCode=0;
		this->EndTime=0;
		this->EndsDays[0]='\0';
	};

	BOOL SetBill(BYTE certify_type, BYTE pay, DWORD end_time, char* ends_days)
	{
		BOOL bRet=FALSE;

		if ( this->cCertifyType == -1 )bRet = TRUE;
		cCertifyType = certify_type;
		PayCode = pay;
		EndTime = end_time;
		strcpy(EndsDays, ends_days);
		return bRet;
	};

	BOOL IsEndTime()
	{
		if( cCertifyType == -1             )    return FALSE;
		if( cCertifyType == CERTIFYTYPE_IP )    return FALSE;
		if( PayCode      == BILLTYPE_JUNGYANG ) return FALSE;

		if( EndTime < 0 )						return TRUE;
		
		return FALSE;
	};

	BYTE GetPayCode() 
	{
		return this->PayCode;
	};

	char* GetEndsDays() 
	{
		return &this->EndsDays[0];
	};

	int GetEndTime() 
	{ 
		return this->EndTime;
	};

	int GetCertify() 
	{
		return this->cCertifyType;
	};
};

#include "protocol.h"

extern OBJECTSTRUCT gObj[OBJMAX];
extern BILL_CLASS m_ObjBill[OBJMAX];

extern int gObjCSFlag;
extern int gItemLoop;
extern int gItemLoop2;
extern int gItemLoopMax;
extern int gObjTotalUser;
extern int gDisconnect;
extern int aaaaaaaaa;
extern int gCurConnectUser; 
extern int skillSuccess;
extern int GuildInfoOfs;
extern int GuildInfoCount;
extern int GuilUserOfs;
extern int GuildUserCount;
extern int lOfsChange;
extern int ChangeCount;
extern int gObjCallMonCount;
extern int gObjMonCount;
extern int gObjCount;

void gObjCalCharacter(int aIndex);
void gObjSkillUseProcTime500(LPOBJ lpObj);
void MonsterAndMsgProc();
void MoveMonsterProc();
void gObjRefillProcess(int aIndex, LPOBJ lpObj);
void gObjInit();
void gObjEnd();
void gObjClearViewportOfMine(LPOBJ lpObj);
void gObjClearViewport(LPOBJ lpObj);
void gObjCloseSet(int aIndex, int Flag);
void gObjCharTradeClear(LPOBJ lpObj);
void gObjCharZeroSet(int aIndex);
int gObjGetSocket(SOCKET socket);
void gObjSetTradeOption(int aIndex, int option);
void gObjSetDuelOption(int aIndex, int option);
bool IsDuelEnable(int aIndex);
bool IsOnDuel(int aIndex1, int aIndex2);
int GetMapMoveLevel(LPOBJ lpObj, int mapnumber, int max_over);
void DbItemSetInByte(LPOBJ lpObj, struct SDHP_DBCHAR_INFORESULT* lpMsg, int ItemDbByte, bool* bAllItemExist);
void gObjSetBP(int aIndex);
int gObjSetCharacter(unsigned char* lpdata, int aIndex);
int gObjCanItemTouch(LPOBJ lpObj, int type);
void gObjMagicTextSave(LPOBJ lpObj);
void ItemIsBufExOption(BYTE * buf, class CItem* lpItem);
void gObjStatTextSave(LPOBJ lpObj);
void gObjItemTextSave(LPOBJ lpObj);
void gObjWarehouseTextSave(LPOBJ lpObj);
void gObjAuthorityCodeSet(LPOBJ lpObj);
int gObjSetPosMonster(int aIndex, int PosTableNum);
int gObjSetMonster(int aIndex, int MonsterClass);
void gObjDestroy(SOCKET aSocket, int client);
short gObjAddSearch(unsigned int aSocket, char* ip);
short gObjAdd(SOCKET aSocket, char* ip, int aIndex);
short gObjMonsterRecall(int iMapNumber);
short gObjAddMonster(int iMapNumber);
short gObjAddCallMon();
void gObjUserKill(int aIndex);
void gObjAllLogOut();
void gObjAllDisconnect();
void gObjTradeSave(LPOBJ lpObj, int index);
void gObjBillRequest(LPOBJ lpObj);
short gObjMemFree(int index);
int gObjGameClose(int aIndex);
short gObjDel(int index);
short gObjSometimeClose(int index);
int gObjIsGamePlaing(LPOBJ lpObj);
int gObjIsConnectedGP(int aIndex, char* CharName);
int gObjIsConnectedGP(int aIndex);
int gObjIsConnected(LPOBJ lpObj, int dbnumber);
int gObjIsConnected(int aIndex);
int gObjIsConnected(LPOBJ lpObj);
int gObjIsAccontConnect(int aIndex, char* accountid);
int gObjJoominCheck(int aIndex, char* szInJN);
int gObjTaiwanJoominCheck(int aIndex, char* szInJN);
int gObjCheckXYMapTile(LPOBJ lpObj, int iDbgName);
int gObjSetAccountLogin(int aIndex, char* szId, int aUserNumber, int aDBNumber, char* JoominNumber);
int gObjGetUserNumber(int aIndex);
int gObjGetNumber(int aIndex, int& UN, int& DBN);
LPSTR gObjGetAccountId(int aIndex);
int gObjGetIndex(char* szId);
int gObjUserIdConnectCheck(char* szId, int index);
unsigned char GetPathPacketDirPos(int px, int py);
int gObjCalDistance(LPOBJ lpObj1, LPOBJ lpObj2);
int gObjPositionCheck(LPOBJ lpObj);
int gObjCheckTileArea(int aIndex, int x, int y, int dis);
int ExtentCheck(int x, int y, int w, int h);
void gObjSetInventory1Pointer(LPOBJ lpObj);
void gObjSetInventory2Pointer(LPOBJ lpObj);
void gObjAddMsgSend(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode);
void gObjAddMsgSendDelay(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode);
void gObjAddMsgSendDelayInSpecificQPos(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode, int iQPosition);
void gObjAddAttackProcMsgSendDelay(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode, int SubCode2);
void gObjMsgProc(LPOBJ lpObj);
void gObjStateProc(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode);
void gObjStateAttackProc(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode, int SubCode2);
int gObjBackSpring(LPOBJ lpObj, LPOBJ lpTargetObj);
int BackSpringCheck(int& x, int& y, int& dir, unsigned char map);
int gObjBackSpring2(LPOBJ lpObj, LPOBJ lpTargetObj, int count);
bool gObjLevelUp(LPOBJ lpObj, int addexp, int iMonsterType, int iEventType);
int gObjLevelUpPointAdd(unsigned char type, LPOBJ lpObj);
void gObjMonsterItemLoadScript(LPOBJ lpObj, char* script_file);
void gObjGiveItemSearch(LPOBJ lpObj, int maxlevel);
unsigned char gObjWarehouseInsertItem(LPOBJ lpObj, int type, int index, int level, int pos);
void gObjGiveItemWarehouseSearch(LPOBJ lpObj, int maxlevel);
int gObjGuildMasterCapacityTest(LPOBJ lpObj);
void gObjNextExpCal(LPOBJ lpObj);
int retResistance(LPOBJ lpObj, int Resistance_Type);
int retCalcSkillResistance(LPOBJ lpTargetObj, int isDouble);
int gObjAttackQ(LPOBJ lpObj);
void gObjPlayerKiller(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjUserDie(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjInterfaceTimeCheck(LPOBJ lpObj);
void gObjPkDownTimeCheck(LPOBJ lpObj, int TargetLevel);
int gObjAngelSprite(LPOBJ lpObj);
int gObjSatanSprite(LPOBJ lpObj);
int gObjWingSprite(LPOBJ lpObj);
int gObjUniriaSprite(LPOBJ lpObj);
void gObjSpriteDamage(LPOBJ lpObj, int damage);
void gObjSecondDurDown(LPOBJ lpObj);
void gObjChangeDurProc(LPOBJ lpObj);
void gObjWingDurProc(LPOBJ lpObj);
void gObjPenaltyDurDown(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjWeaponDurDown(LPOBJ lpObj, LPOBJ lpTargetObj, int type);
void gObjArmorRandomDurDown(LPOBJ lpObj, LPOBJ lpAttackObj);
bool gObjIsSelfDefense(LPOBJ lpObj, int aTargetIndex);
void gObjCheckSelfDefense(LPOBJ lpObj, int aTargetIndex);
void gObjTimeCheckSelfDefense(LPOBJ lpObj);
int gObjAttack(LPOBJ lpObj, LPOBJ lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage, BOOL bCombo);
void gObjMonsterExpDivision(LPOBJ lpMonObj, LPOBJ lpObj, int AttackDamage, int MSBFlag);
int gObjMonsterExpSingle(LPOBJ lpObj, LPOBJ lpTargetObj, int dmg, int tot_dmg, bool& bSendExp);
void gObjExpParty(LPOBJ lpObj, LPOBJ lpTargetObj, int AttackDamage, int MSBFlag);
void gObjMonsterDieLifePlus(LPOBJ lpObj, LPOBJ lpTartObj);
void gObjLifeCheck(LPOBJ lpTargetObj, LPOBJ lpObj, int AttackDamage, int DamageSendType, int MSBFlag, int MSBDamage, unsigned char Skill);
int gObjInventoryTrans(int aIndex);
int gObjInventoryCommit(int aIndex);
int gObjInventoryRollback(int aIndex);
void gObjInventoryItemSet(int aIndex, int itempos, unsigned char set_byte);
void gObjInventoryItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
bool gObjFixInventoryPointer(int aIndex);
void gObjInventoryItemSet_PShop(int aIndex, int itempos, unsigned char set_byte);
void gObjInventoryItemBoxSet_PShop(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
BYTE gObjInventoryDeleteItem(int aIndex, int itempos);
BYTE gObjWarehouseDeleteItem(int aIndex, int itempos);
BYTE gObjChaosBoxDeleteItem(int aIndex, int itempos);
BYTE gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
DWORD gGetItemNumber();
void gPlusItemNumber();
BYTE gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
BYTE gObjOnlyInventoryInsertItem(int aIndex, class CItem item);
BYTE gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level);
int gObjSearchItem(LPOBJ lpObj, int item_type, int add_dur, int nLevel);
int gObjSearchItemMinus(LPOBJ lpObj, int pos, int m_dur);
unsigned char gObjShopBuyInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
unsigned char gObjShopBuyInventoryInsertItem(int aIndex, class CItem item);
unsigned char gObjInventoryInsertItemTemp(LPOBJ lpObj, class CMapItem* Item);
unsigned char gObjInventoryInsertItem(int aIndex, class CMapItem* item);
unsigned char gObjInventoryInsertItem(int aIndex, class CItem item);
unsigned char gObjMonsterInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int op1, int op2, int op3);
unsigned char gObjInventoryRectCheck(int aIndex, int sx, int sy, int width, int height);
unsigned char gObjOnlyInventoryRectCheck(int aIndex, int sx, int sy, int width, int height);
int CheckInventoryEmptySpace(LPOBJ lpObj, int iItemHeight, int iItemWidth);
int gObjIsItemPut(LPOBJ lpObj, class CItem* lpItem, int pos);
unsigned char gObjWerehouseRectCheck(int aIndex, int sx, int sy, int width, int height);
unsigned char gObjMapRectCheck(unsigned char* lpMapBuf, int sx, int sy, int ex, int ey, int width, int height);
void gObjWarehouseItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
void gObjWarehouseItemSet(int aIndex, int itempos, unsigned char set_byte);
void gObjChaosItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
void gObjChaosItemSet(int aIndex, int itempos, unsigned char set_byte);
unsigned char gObjChaosBoxInsertItemPos(int aIndex, class CItem item, int pos, int source);
unsigned char gObjWarehouseInsertItemPos(int aIndex, class CItem item, int pos, int source);
unsigned char gObjInventoryInsertItemPos(int aIndex, class CItem item, int pos, int RequestCheck);
int gObjInventorySearchSerialNumber(LPOBJ lpObj, unsigned long serial);
int gObjWarehouseSearchSerialNumber(LPOBJ lpObj, unsigned long sirial);
unsigned char gObjInventoryMoveItem(int aIndex, unsigned char source, unsigned char target, int& durSsend, int& durTsend, unsigned char sFlag, unsigned char tFlag, unsigned char* siteminfo);
unsigned char gObjTradeRectCheck(int aIndex, int sx, int sy, int width, int height);
int gObjTradeItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
unsigned char gObjTradeInventoryMove(LPOBJ lpObj, unsigned char source, unsigned char target);
unsigned char gObjInventoryTradeMove(LPOBJ lpObj, unsigned char source, unsigned char target);
unsigned char gObjTradeTradeMove(LPOBJ lpObj, unsigned char source, unsigned char target);
void gObjTradeCancel(int aIndex);
void gObjTempInventoryItemBoxSet(unsigned char* TempMap, int itempos, int xl, int yl, unsigned char set_byte);
unsigned char gObjTempInventoryRectCheck(unsigned char* TempMap, int sx, int sy, int width, int height);
unsigned char gObjTempInventoryInsertItem(LPOBJ lpObj, class CItem item, unsigned char* TempMap);
int TradeItemInventoryPutTest(int aIndex);
int TradeitemInventoryPut(int aIndex);
void gObjTradeOkButton(int aIndex);
unsigned char LevelSmallConvert(int level);
unsigned char LevelSmallConvert(int aIndex, int inventoryindex);
void gObjAttackDamageCalc(int aIndex);
void gObjMakePreviewCharSet(int aIndex);
void InitFrustrum();
void CreateFrustrum(int x, int y, int aIndex);
bool TestFrustrum2(int x, int y, int aIndex);
int gObjCheckViewport(int aIndex, int x, int y);
void gObjViewportClose(LPOBJ lpObj);
void gObjViewportListCreate(short aIndex);
int ViewportAdd(int aIndex, int aAddIndex, int aType);
int ViewportAdd2(int aIndex, int aAddIndex, int aType);
void ViewportDel(short aIndex, int aDelIndex);
void Viewport2Del(short aIndex, int aDelIndex);
void gObjViewportAllDel(short aIndex);
void gObjViewportListDestroy(short aIndex);
void PShop_ViewportListRegenarate(short aIndex);
bool PShop_CheckInventoryEmpty(short aIndex);
void gObjStateSetCreate(int aIndex);
void gObjSetState();
void gObjSecondProc();
void gObjManaPotionFill(LPOBJ lpObj);
void gObjRestPotionFill(LPOBJ lpObj);
void gObjUseDrink(LPOBJ lpObj, int level);
int gObjCurMoveMake(unsigned char* const path, LPOBJ lpObj);
void gObjViewportListProtocolDestroy(LPOBJ lpObj);
void gObjViewportListProtocolCreate(LPOBJ lpObj);
void gObjViewportListProtocol(short aIndex);
void gObjSkillUseProc(LPOBJ lpObj);
void gObjSkillBeAttackProc(LPOBJ lpObj);
void gObjTeleportMagicUse(int aIndex, unsigned char x, unsigned char y);
int gObjMoveGate(int aIndex, int gt);
void gObjTeleport(int aIndex, int map, int x, int y);
void gObjMoveDataLoadingOK(int aIndex);
class CMagicInf* gObjGetMagic(LPOBJ lpObj, int mIndex);
class CMagicInf* gObjGetMagicSearch(LPOBJ lpObj, unsigned char skillnumber);
int gObjMagicManaUse(LPOBJ lpObj, class CMagicInf* lpMagic);
int gObjMagicBPUse(LPOBJ lpObj, class CMagicInf* lpMagic);
int gObjPosMagicAttack(LPOBJ lpObj, class CMagicInf* lpMagic, unsigned char x, unsigned char y);
void gObjMagicAddEnergyCheckOnOff(int flag);
int gObjMagicAdd(LPOBJ lpObj, unsigned char aSkill, unsigned char Level);
int gObjMagicDel(LPOBJ lpObj, unsigned char aSkill, unsigned char Level);
int gObjMagicAdd(LPOBJ lpObj, unsigned char Type, unsigned char Index, unsigned char Level, unsigned char& SkillNumber);
int gObjWeaponMagicAdd(LPOBJ lpObj, BYTE aSkill, BYTE Level);
int gObjMonsterMagicAdd(LPOBJ lpObj, BYTE aSkill, BYTE Level);
int gObjMagicEnergyCheck(LPOBJ lpObj, unsigned char aSkill);
int gObjItemLevelUp(LPOBJ lpObj, int source, int target);
int gObjItemRandomLevelUp(LPOBJ lpObj, int source, int target);
int gObjItemRandomOption3Up(LPOBJ lpObj, int source, int target);
void gObjAbilityReSet(LPOBJ lpObj);
int gObjTargetGuildWarCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjGuildWarEndSend(struct _GUILD_INFO_STRUCT* lpGuild1, struct _GUILD_INFO_STRUCT* lpGuild2, unsigned char Result1, unsigned char Result2);
void gObjGuildWarEndSend(LPOBJ lpObj, unsigned char Result1, unsigned char Result2);
void gObjGuildWarEnd(struct _GUILD_INFO_STRUCT* lpGuild, struct _GUILD_INFO_STRUCT* lpTargetGuild);
int gObjGuildWarProc(struct _GUILD_INFO_STRUCT* lpGuild1, struct _GUILD_INFO_STRUCT* lpGuild2, int score);
int gObjGuildWarCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjGuildWarMasterClose(LPOBJ lpObj);
int gObjGuildWarItemGive(struct _GUILD_INFO_STRUCT* lpWinGuild, struct _GUILD_INFO_STRUCT* lpLoseGuild);
int gObjGetPkTime(LPOBJ lpObj, int& hour, int& min);
int gObjMonsterCall(int aIndex, int MonsterType, int x, int y);
void gObjMonsterCallKill(int aIndex);
int gObjCheckTeleportArea(int aIndex, BYTE x, BYTE y);
int gObjCheckAttackAreaUsedPath(int aIndex, int TarObjIndex);
int gObjCheckattackAreaUsedViewPort(int aIndex, int TarObjIndex);
int gObjCheckAttackArea(int aIndex, int TarObjIndex);
int gUserFindDevilSquareInvitation(int aIndex);
int gUserFindDevilSquareKeyEyes(int aIndex);
void gObjSendUserStatistic(int aIndex, int startLevel, int endLevel);
LPOBJ gObjFind(char* targetcharname);
int gObjFind10EventChip(int aIndex);
int gObjDelete10EventChip(int aIndex);
void gObjSetPosition(int aIndex, int x, int y);
int gObjGetItemCountInEquipment(int aIndex, int itemtype, int itemindex, int itemlevel);
int gObjGetItemCountInIventory(int aIndex, int itemnum);
int gObjGetItemCountInIventory(int aIndex, int itemtype, int itemindex, int itemlevel);
int gObjGetManaItemPos(int aIndex);
void gObjDelteItemCountInInventory(int aIndex, int itemtype, int itemindex, int count);
void gObjGetStatPointState(int aIndex, short& AddPoint, short& MaxAddPoint, short& MinusPoint, short& MaxMinusPoint);
int gObjCheckStatPointUp(int aIndex);
int gObjCheckStatPointDown(int aIndex);
void gObjUseCircle(int aIndex, int pos);
void gObjUsePlusStatFruit(int aIndex, int pos);
void gObjUseMinusStatFruit(int aIndex, int pos);
void gObjCalcMaxLifePower(int aIndex);
void gObjDelayLifeCheck(int aIndex);
int gObjDuelCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjDuelCheck(LPOBJ lpObj);
void gObjResetDuel(LPOBJ lpObj);
void gObjSendDuelEnd(LPOBJ lpObj);
void gObjCheckAllUserDuelStop();
void gObjNProtectGGCheckSum(int aIndex);
void SkillFrustrum(unsigned char bangle, int aIndex);
int SkillTestFrustrum(int x, int y, int aIndex);
int gObjCheckMaxZen(int aIndex, int nAddZen);
void MakeRandomSetItem(int aIndex);
void MakeRewardSetItem(int aIndex, BYTE cDropX, BYTE cDropY, int iRewardType, int iMapnumber);
void gObjRecall(int aIndex, int mapnumber, int x, int y);
void gObjSetExpPetItem(int aIndex, int exp);
int gObjGetRandomItemDropLocation(int iMapNumber, BYTE& cX, BYTE& cY, int iRangeX, int iRangeY, int iLoopCount);
int gObjGetRandomFreeLocation(int iMapNumber, BYTE& cX, BYTE& cY, int iRangeX, int iRangeY, int iLoopCount);
int gObjCheckAttackTypeMagic(int iClass, int iSkill);
int gObjGetGuildUnionNumber(LPOBJ lpObj);
void gObjGetGuildUnionName(LPOBJ lpObj, char* szUnionName, int iUnionNameLen);
int gObjCheckRival(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjGetRelationShip(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjNotifyUpdateUnionV1(LPOBJ lpObj);
void gObjNotifyUpdateUnionV2(LPOBJ lpObj);
void gObjUnionUpdateProc(int aIndex);
void gObjSetKillCount(int aIndex, int iOption);
void gObjNotifyUseWeaponV1(LPOBJ lpOwnerObj, LPOBJ lpWeaponObj, int iTargetX, int iTargetY);
void gObjNotifyUseWeaponDamage(LPOBJ lpWeaponObj, int iTargetX, int iTargetY);
void gObjUseBlessAndSoulPotion(int aIndex, int iItemLevel);
void gObjWeaponDurDownInCastle(LPOBJ lpObj, LPOBJ lpTargetObj, int iDecValue);
void gObjReady4Relife(LPOBJ lpObj);
void gObjCheckTimeOutValue(LPOBJ lpObj, DWORD& rNowTick);
void MsgOutput(int aIndex, char* msg, ...);
void gProcessAutoRecuperation(LPOBJ lpObj);
int gObjCheckOverlapItemUsingDur(int iUserIndex, int iMaxOverlapped, int iItemType, int iItemLevel);
int gObjOverlapItemUsingDur(class CItem* lpItem, int iMapNumber, int iItemNumber, int iUserIndex, int iMaxOverlapped, int iItemType, int iItemLevel);
int gObjCheckSerial0ItemList(class CItem* lpItem);
int gObjCheckInventorySerial0Item(LPOBJ lpObj);
BOOL gCheckSkillDistance(int aIndex, int aTargetIndex, int iSkillNum);
void gObjSaveChaosBoxItemList(LPOBJ lpObj);
int gObjGetRandomFreeArea(int iMapNumber,unsigned char & cX,unsigned char & cY,int iSX,int iSY,int iDX,int iDY,int iLoopCount);

#endif