#include "StdAfx.h"
#include "ServerInfo.h"
#include "GameServer.h"
#include "GameMain.h"
#include "TNotice.h"

CServerInfo gServerInfo;

void CServerInfo::Load()
{
	memset(&this->m_Data, 0, sizeof(this->m_Data));
	memset(&this->m_Character, 0, sizeof(this->m_Character));
	// ---
	this->Connect();
	this->Common();
	this->Character();
	// ---
	LogAdd(LOG_GOLD, "[SERVER INFO FILE] Carregado !");
}

void CServerInfo::Connect()
{
	UDPPort						= GetPrivateProfileInt("GameServerInfo","ServerUpdPort", 60006, SERVER_FILE);
	GameServerPort				= GetPrivateProfileInt("GameServerInfo","GameServerPort", 55901, SERVER_FILE);
	// ---
	GetPrivateProfileString("GameServerInfo", "JoinServerIP", "127.0.0.1", JoinServerIp, 256, SERVER_FILE);
	JoinServerPort				= GetPrivateProfileInt("GameServerInfo","JoinServerPort", 55970, SERVER_FILE);
	// ---
	ExDbPort					= GetPrivateProfileInt("GameServerInfo","ExDBServerPort", 55906, SERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "ExDBServerIP", "127.0.0.1", ExDbIp, 256, SERVER_FILE);
	// ---
	DataServerPort				= GetPrivateProfileInt("GameServerInfo","DataServerPort", 55960, SERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "DataServerIP", "127.0.0.1", DataServerIp, 256, SERVER_FILE);
}

void CServerInfo::Common()
{
	GetPrivateProfileString("CommonServer", "Server_Name", NULL, this->m_Data.szServerName, sizeof(this->m_Data.szServerName), COMMON_FILE);
	// ---
	GetPrivateProfileString("CommonServer", "Guard_Talk", NULL, this->m_Data.szGuardTalk, sizeof(this->m_Data.szGuardTalk), COMMON_FILE);
	// ---
	this->m_Data.iServerVip					= GetPrivateProfileInt("CommonServer", "VipEnterServer", NULL, COMMON_FILE);
	// ---
	this->m_Data.iServerResetMax			= GetPrivateProfileInt("CommonServer", "ResetsMaxEnterServer", NULL, COMMON_FILE);
	this->m_Data.iServerResetMin			= GetPrivateProfileInt("CommonServer", "ResetsMinEnterServer", NULL, COMMON_FILE);
	// ---
	this->m_Data.iMaxStatus					= GetPrivateProfileInt("CommonServer", "ServerMaxStatus", NULL, COMMON_FILE);
	// ---
	this->m_Data.iSkillNotLevel				= GetPrivateProfileInt("CommonServer", "SkillNotLevel", NULL, COMMON_FILE);
	// ---
	this->m_Data.iItemDropTime				= GetPrivateProfileInt("CommonServer","ItemDropTime", NULL, COMMON_FILE);
	// ---
	this->m_Data.iAncientAndExcellent		= GetPrivateProfileInt("CommonServer","AncientAndExcellent", NULL, COMMON_FILE);
	// ---
	this->m_Data.fRateZen					= GetPrivateProfileFloat("CommonServer", "AddZen", NULL, COMMON_FILE);
	// ---
	this->m_Data.iStartMap[0]				= GetPrivateProfileInt("CommonServer", "StartMapDK", NULL, COMMON_FILE);
	this->m_Data.iStartMap[1]				= GetPrivateProfileInt("CommonServer", "StartMapDW", NULL, COMMON_FILE);
	this->m_Data.iStartMap[2]				= GetPrivateProfileInt("CommonServer", "StartMapFE", NULL, COMMON_FILE);
	this->m_Data.iStartMap[3]				= GetPrivateProfileInt("CommonServer", "StartMapMG", NULL, COMMON_FILE);
	this->m_Data.iStartMap[4]				= GetPrivateProfileInt("CommonServer", "StartMapDL", NULL, COMMON_FILE);
	// ---
	this->m_Data.iLevelUp[0]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsDW", NULL, COMMON_FILE);
	this->m_Data.iLevelUp[1]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsDK", NULL, COMMON_FILE);
	this->m_Data.iLevelUp[2]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsFE", NULL, COMMON_FILE);
	this->m_Data.iLevelUp[3]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsMG", NULL, COMMON_FILE);
	this->m_Data.iLevelUp[4]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsDL", NULL, COMMON_FILE);
	this->m_Data.iLevelUp[5]				= GetPrivateProfileInt("CommonServer", "LevelUpPointsPlus", NULL, COMMON_FILE);
	// ---
	this->m_Data.iPotionHP[0]				= GetPrivateProfileInt("CommonServer", "Recovery_Healing_Apple", NULL, COMMON_FILE);
	this->m_Data.iPotionHP[1]				= GetPrivateProfileInt("CommonServer", "Recovery_Healing_Small", NULL, COMMON_FILE);
	this->m_Data.iPotionHP[2]				= GetPrivateProfileInt("CommonServer", "Recovery_Healing_Medium", NULL, COMMON_FILE);
	this->m_Data.iPotionHP[3]				= GetPrivateProfileInt("CommonServer", "Recovery_Healing_Large", NULL, COMMON_FILE);
	this->m_Data.iPotionHP[4]				= GetPrivateProfileInt("CommonServer", "Recovery_Healing_Div", NULL, COMMON_FILE);
	// ---
	this->m_Data.iPotionMP[0]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Small", NULL, COMMON_FILE);
	this->m_Data.iPotionMP[1]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Small_Div", NULL, COMMON_FILE);
	this->m_Data.iPotionMP[2]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Medium", NULL, COMMON_FILE);
	this->m_Data.iPotionMP[3]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Medium_Div", NULL, COMMON_FILE);
	this->m_Data.iPotionMP[4]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Large", NULL, COMMON_FILE);
	this->m_Data.iPotionMP[5]				= GetPrivateProfileInt("CommonServer", "Recovery_Mana_Large_Div", NULL, COMMON_FILE);
	// ---
	this->m_Data.iRings[0]					= GetPrivateProfileInt("CommonServer", "TranformRing_BudgeDragon", NULL, COMMON_FILE);
	this->m_Data.iRings[1]					= GetPrivateProfileInt("CommonServer", "TranformRing_Giant", NULL, COMMON_FILE);
	this->m_Data.iRings[2]					= GetPrivateProfileInt("CommonServer", "TranformRing_Skeleton", NULL, COMMON_FILE);
	this->m_Data.iRings[3]					= GetPrivateProfileInt("CommonServer", "TranformRing_ThunderLich", NULL, COMMON_FILE);
	this->m_Data.iRings[4]					= GetPrivateProfileInt("CommonServer", "TranformRing_PoisonBull", NULL, COMMON_FILE);
	this->m_Data.iRings[5]					= GetPrivateProfileInt("CommonServer", "TranformRing_DeathCow", NULL, COMMON_FILE);
	// ---
	this->m_Data.iExpParty[0]				= GetPrivateProfileInt("CommonServer", "PartyExp_Percent3", NULL, COMMON_FILE);
	this->m_Data.iExpParty[1]				= GetPrivateProfileInt("CommonServer", "PartyExp_Percent4", NULL, COMMON_FILE);
	this->m_Data.iExpParty[2]				= GetPrivateProfileInt("CommonServer", "PartyExp_Percent5", NULL, COMMON_FILE);
	this->m_Data.iExpParty[3]				= GetPrivateProfileInt("CommonServer", "PartyExp_PercentDefault", NULL, COMMON_FILE);
	this->m_Data.iExpParty[4]				= GetPrivateProfileInt("CommonServer", "PartyExp_SetPercent2", NULL, COMMON_FILE);
	this->m_Data.iExpParty[5]				= GetPrivateProfileInt("CommonServer", "PartyExp_SetPercent3", NULL, COMMON_FILE);
	this->m_Data.iExpParty[6]				= GetPrivateProfileInt("CommonServer", "PartyExp_SetPercent4", NULL, COMMON_FILE);
	this->m_Data.iExpParty[7]				= GetPrivateProfileInt("CommonServer", "PartyExp_SetPercent5", NULL, COMMON_FILE);
	this->m_Data.iExpParty[8]				= GetPrivateProfileInt("CommonServer", "PartyExp_SetPercentDefault", NULL, COMMON_FILE);
	// ---
	this->m_Data.iDropItemMonsterRate[0]	= GetPrivateProfileInt("CommonServer", "ItemDrop_Excellent", NULL, COMMON_FILE);
	this->m_Data.iDropItemMonsterRate[1]	= GetPrivateProfileInt("CommonServer", "ItemDrop_ExcellentSkill", NULL, COMMON_FILE);
	this->m_Data.iDropItemMonsterRate[2]	= GetPrivateProfileInt("CommonServer", "ItemDrop_ExcellentLuck", NULL, COMMON_FILE);
	this->m_Data.iDropItemMonsterRate[3]	= GetPrivateProfileInt("CommonServer", "ItemDrop_Skill", NULL, COMMON_FILE);
	this->m_Data.iDropItemMonsterRate[4]	= GetPrivateProfileInt("CommonServer", "ItemDrop_Luck", NULL, COMMON_FILE);
	// ---
	this->m_Data.wSatanAddDamage			= GetPrivateProfileInt("CommonServer", "Pet_Satan_AddDamage", NULL, COMMON_FILE);
	this->m_Data.wDinorantAddDamage			= GetPrivateProfileInt("CommonServer", "Pet_Dinorant_AddDamage", NULL, COMMON_FILE);
	this->m_Data.wAngelAddDefense			= GetPrivateProfileInt("CommonServer", "Pet_Angel_AddDefense", NULL, COMMON_FILE);
	this->m_Data.wDarkHorseAddDamage		= GetPrivateProfileInt("CommonServer", "Pet_DarkHorse_AddDamage", NULL, COMMON_FILE);
}

void CServerInfo::Character()
{
	char * szClassPrefixes[] = { "DW", "DK", "ELF", "MG", "DL" };
	// ---
	char szTemp[128];
	// ---
	this->m_Character.MinimumDamageDW			= GetPrivateProfileInt("Wizard","AttackDamageMinDiv1",8, CHARACTER_FILE);
	this->m_Character.MaximumDamageDW			= GetPrivateProfileInt("Wizard","AttackDamageMaxDiv1",4, CHARACTER_FILE);
	this->m_Character.MinimumMagicDamageDW		= GetPrivateProfileInt("Wizard","MagicDamageMinDiv",9, CHARACTER_FILE);
	this->m_Character.MaximumMagicDamageDW		= GetPrivateProfileInt("Wizard","MagicDamageMaxDiv",4, CHARACTER_FILE);
	this->m_Character.AttackSpeedDW				= GetPrivateProfileInt("Wizard","AttackSpeedDiv",20, CHARACTER_FILE);
	this->m_Character.MagicSpeedDW				= GetPrivateProfileInt("Wizard","MagicSpeedDiv",10, CHARACTER_FILE);
	this->m_Character.DefenseDW					= GetPrivateProfileInt("Wizard","DefenseDiv",4, CHARACTER_FILE);
	this->m_Character.BlockDW					= GetPrivateProfileInt("Wizard","SuccessBlockDiv",4, CHARACTER_FILE);
		
	this->m_Character.MinimumDamageDK			= GetPrivateProfileInt("Knight","AttackDamageMinDiv1",6, CHARACTER_FILE);
	this->m_Character.MaximumDamageDK			= GetPrivateProfileInt("Knight","AttackDamageMaxDiv1",4, CHARACTER_FILE);
	this->m_Character.MinimumMagicDamageDK		= GetPrivateProfileInt("Knight","MagicDamageMinDiv",9, CHARACTER_FILE);
	this->m_Character.MaximumMagicDamageDK		= GetPrivateProfileInt("Knight","MagicDamageMaxDiv",4, CHARACTER_FILE);
	this->m_Character.AttackSpeedDK				= GetPrivateProfileInt("Knight","AttackSpeedDiv",15, CHARACTER_FILE);
	this->m_Character.MagicSpeedDK				= GetPrivateProfileInt("Knight","MagicSpeedDiv",20, CHARACTER_FILE);
	this->m_Character.DefenseDK					= GetPrivateProfileInt("Knight","DefenseDiv",3, CHARACTER_FILE);
	this->m_Character.BlockDK					= GetPrivateProfileInt("Wizard","SuccessBlockDiv",4, CHARACTER_FILE);
	
	this->m_Character.MinimumDamageFE_NoBow		= GetPrivateProfileInt("Fairy","AttackDamageMinDiv1", 7, CHARACTER_FILE);
	this->m_Character.MaximumDamageFE_NoBow		= GetPrivateProfileInt("Fairy","AttackDamageMaxDiv1", 4, CHARACTER_FILE);
	this->m_Character.MinimumDamageFE_StrBow		= GetPrivateProfileInt("Fairy","AttackDamageMinDiv2",14, CHARACTER_FILE);
	this->m_Character.MaximumDamageFE_StrBow		= GetPrivateProfileInt("Fairy","AttackDamageMaxDiv2",8, CHARACTER_FILE);
	this->m_Character.MinimumDamageFE_AgiBow		= GetPrivateProfileInt("Fairy","AttackDamageMinDiv3",7, CHARACTER_FILE);
	this->m_Character.MaximumDamageFE_AgiBow		= GetPrivateProfileInt("Fairy","AttackDamageMaxDiv3",4, CHARACTER_FILE);
	this->m_Character.MinimumMagicDamageFE		= GetPrivateProfileInt("Fairy","MagicDamageMinDiv",9, CHARACTER_FILE);
	this->m_Character.MaximumMagicDamageFE		= GetPrivateProfileInt("Fairy","MagicDamageMaxDiv",4, CHARACTER_FILE);
	this->m_Character.AttackSpeedFE				= GetPrivateProfileInt("Fairy","AttackSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.MagicSpeedFE				= GetPrivateProfileInt("Fairy","MagicSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.DefenseFE					= GetPrivateProfileInt("Fairy","DefenseDiv",10, CHARACTER_FILE);
	this->m_Character.BlockFE					= GetPrivateProfileInt("Fairy","SuccessBlockDiv",4, CHARACTER_FILE);
	
	this->m_Character.MinimumDamageMG_Str		= GetPrivateProfileInt("Magic","AttackDamageMinDiv1",6, CHARACTER_FILE);
	this->m_Character.MaximumDamageMG_Str		= GetPrivateProfileInt("Magic","AttackDamageMaxDiv1",4, CHARACTER_FILE);
	this->m_Character.MinimumDamageMG_Ene		= GetPrivateProfileInt("Magic","AttackDamageMinDiv2",12, CHARACTER_FILE);
	this->m_Character.MaximumDamageMG_Ene		= GetPrivateProfileInt("Magic","AttackDamageMaxDiv2",8, CHARACTER_FILE);
	this->m_Character.MinimumMagicDamageMG		= GetPrivateProfileInt("Magic","MagicDamageMinDiv",9, CHARACTER_FILE);
	this->m_Character.MaximumMagicDamageMG		= GetPrivateProfileInt("Magic","MagicDamageMaxDiv",4, CHARACTER_FILE);
	this->m_Character.AttackSpeedMG				= GetPrivateProfileInt("Magic","AttackSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.MagicSpeedMG				= GetPrivateProfileInt("Magic","MagicSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.DefenseMG					= GetPrivateProfileInt("Magic","DefenseDiv",4, CHARACTER_FILE);	
	this->m_Character.BlockMG					= GetPrivateProfileInt("Magic","SuccessBlockDiv",4, CHARACTER_FILE);

	this->m_Character.MinimumDamageDL_Str		= GetPrivateProfileInt("Lord","AttackDamageMinDiv1",7, CHARACTER_FILE);
	this->m_Character.MaximumDamageDL_Str		= GetPrivateProfileInt("Lord","AttackDamageMaxDiv1",5, CHARACTER_FILE);
	this->m_Character.MinimumDamageDL_Ene		= GetPrivateProfileInt("Lord","AttackDamageMinDiv2",14, CHARACTER_FILE);
	this->m_Character.MaximumDamageDL_Ene		= GetPrivateProfileInt("Lord","AttackDamageMaxDiv2",10, CHARACTER_FILE);
	this->m_Character.MinimumMagicDamageDL		= GetPrivateProfileInt("Lord","MagicDamageMinDiv",9, CHARACTER_FILE);
	this->m_Character.MaximumMagicDamageDL		= GetPrivateProfileInt("Lord","MagicDamageMaxDiv",4, CHARACTER_FILE);
	this->m_Character.AttackSpeedDL				= GetPrivateProfileInt("Lord","AttackSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.MagicSpeedDL				= GetPrivateProfileInt("Lord","MagicSpeedDiv",50, CHARACTER_FILE);
	this->m_Character.DefenseDL					= GetPrivateProfileInt("Lord","DefenseDiv",7, CHARACTER_FILE);
	this->m_Character.BlockDL					= GetPrivateProfileInt("Lord","SuccessBlockDiv",4, CHARACTER_FILE);
	// ---
	for(int iPlayer = 0; iPlayer < MAX_TYPE_PLAYER; iPlayer++)
	{
		for(int iTarget = 0; iTarget < MAX_TYPE_PLAYER; iTarget++)
		{
			sprintf(szTemp, "%sTo%s_DamageRate", szClassPrefixes[iPlayer], szClassPrefixes[iTarget]);
			// ---
			this->m_Character.PvPDamageRate[iPlayer][iTarget] = GetPrivateProfileInt("PVPDamage", szTemp, 100, DAMAGE_FILE);
		}
	}
	// ---
	this->m_Character.PvMDamageRate[CLASS_KNIGHT]	= GetPrivateProfileInt("PVMDamage", "DK_DamageRate", 100, DAMAGE_FILE);
	this->m_Character.PvMDamageRate[CLASS_WIZARD]	= GetPrivateProfileInt("PVMDamage", "DW_DamageRate", 100, DAMAGE_FILE);
	this->m_Character.PvMDamageRate[CLASS_ELF]		= GetPrivateProfileInt("PVMDamage", "ELF_DamageRate", 100, DAMAGE_FILE);
	this->m_Character.PvMDamageRate[CLASS_MAGUMSA]	= GetPrivateProfileInt("PVMDamage", "MG_DamageRate", 100, DAMAGE_FILE);
	this->m_Character.PvMDamageRate[CLASS_DARKLORD]	= GetPrivateProfileInt("PVMDamage", "DL_DamageRate", 100, DAMAGE_FILE);
	// ---
	this->m_Character.ReflectDamage = GetPrivateProfileInt("ReflectDamage", "ReflectPercentDamage", 50, DAMAGE_FILE);
	// ---
	LogAdd(LOG_GOLD, "[CHARACTER FILE] Carregado !");
}

void CServerInfo::SetInfo(int aIndex)
{
	gObj[aIndex].m_Vip = gSQLManager.ReturnInt("Vip", "SELECT Vip FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	// ---
	gObj[aIndex].m_Resets = gSQLManager.ReturnInt("Resets", "SELECT Resets FROM Character WHERE Name = '%s'", gObj[aIndex].Name);
	// ---
	gObj[aIndex].m_MasterResets = gSQLManager.ReturnInt("MasterResets", "SELECT MasterResets FROM Character WHERE Name = '%s'", gObj[aIndex].Name);
	// ---
	gObj[aIndex].m_Cash = gSQLManager.ReturnInt("Cash", "SELECT Cash FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	// ---
	gObj[aIndex].m_Gold = gSQLManager.ReturnInt("Gold", "SELECT Gold FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	// ---
	gObj[aIndex].m_WareNumber = gSQLManager.ReturnInt("WareNumber", "SELECT WareNumber FROM MEMB_INFO WHERE memb___id = '%s'", gObj[aIndex].AccountID);
	// ---
	if(gServerInfo.m_Data.iServerVip != -1 && gObj[aIndex].m_Vip < gServerInfo.m_Data.iServerVip)
	{
		MsgUser(aIndex, 1, "[%s] Servidor limitado por vip, saindo ...", gObj[aIndex].Name);
		gObjCloseSet(aIndex, 2);
		return;
	}
	// ---
	if(	(gServerInfo.m_Data.iServerResetMin != -1 && gObj[aIndex].m_Resets < gServerInfo.m_Data.iServerResetMin) ||
		(gServerInfo.m_Data.iServerResetMax != -1 && gObj[aIndex].m_Resets > gServerInfo.m_Data.iServerResetMax))
	{
		MsgUser(aIndex, 1, "[%s] Servidor limitado por resets, saindo ...", gObj[aIndex].Name);
		gObjCloseSet(aIndex, 2);
		return;
	}
	// ---
	MsgUser(aIndex, 0, "%s Seja Bem Vindo(a) ao %s", gObj[aIndex].Name, gServerInfo.m_Data.szServerName);
	// ---
	MsgUser(aIndex, 0, "Conta %s, Tenha um Bom jogo", gVip.GetName(gObj[aIndex].m_Vip));
}

void CServerInfo::SendMain(int aIndex)
{
	PMSG_CHARINFOMAIN Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(Result);
	Result.h.headcode = 0xFE;
	Result.Code = 0x07;
	Result.Class = gObj[aIndex].Class;
	Result.Dexterity = (WORD)(gObj[aIndex].Dexterity);
	Result.AttackSpeed = (WORD)(gObj[aIndex].m_AttackSpeed);
	Result.MagicSpeed = (WORD)(gObj[aIndex].m_MagicSpeed);

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
}