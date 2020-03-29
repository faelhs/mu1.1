#include "StdAfx.h"
#include "user.h"
#include "protocol.h"
#include "winutil.h"
#include "TNotice.h"
#include "DSProtocol.h"
#include "QuestInfo.h"
#include "GameMain.h"
#include "DBSockMng.h"

CCommands gCommands;

void CCommands::Load()
{
	GetPrivateProfileString("Commands", "Command_Post_Sintax", NULL, this->m_Data[COMMAND_POST].szSintax, sizeof(this->m_Data[COMMAND_POST].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_POST].iEnabled				= GetPrivateProfileInt("Commands", "Command_Post_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iVipOnly[0]			= GetPrivateProfileInt("Commands", "Command_Post_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iVipOnly[1]			= GetPrivateProfileInt("Commands", "Command_Post_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iVipOnly[2]			= GetPrivateProfileInt("Commands", "Command_Post_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iVipOnly[3]			= GetPrivateProfileInt("Commands", "Command_Post_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iLevel[0]			= GetPrivateProfileInt("Commands", "Command_Post_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iLevel[1]			= GetPrivateProfileInt("Commands", "Command_Post_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iLevel[2]			= GetPrivateProfileInt("Commands", "Command_Post_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iLevel[3]			= GetPrivateProfileInt("Commands", "Command_Post_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMoney[0]			= GetPrivateProfileInt("Commands", "Command_Post_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMoney[1]			= GetPrivateProfileInt("Commands", "Command_Post_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMoney[2]			= GetPrivateProfileInt("Commands", "Command_Post_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMoney[3]			= GetPrivateProfileInt("Commands", "Command_Post_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iResets[0]           = GetPrivateProfileInt("Commands", "Command_Post_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iResets[1]           = GetPrivateProfileInt("Commands", "Command_Post_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iResets[2]           = GetPrivateProfileInt("Commands", "Command_Post_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iResets[3]           = GetPrivateProfileInt("Commands", "Command_Post_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMResets[0]          = GetPrivateProfileInt("Commands", "Command_Post_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMResets[1]          = GetPrivateProfileInt("Commands", "Command_Post_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMResets[2]          = GetPrivateProfileInt("Commands", "Command_Post_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iMResets[3]          = GetPrivateProfileInt("Commands", "Command_Post_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iPostColor[0]		= GetPrivateProfileInt("Commands", "Command_Post_TypeColorFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iPostColor[1]		= GetPrivateProfileInt("Commands", "Command_Post_TypeColorVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iPostColor[2]		= GetPrivateProfileInt("Commands", "Command_Post_TypeColorVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iPostColor[3]		= GetPrivateProfileInt("Commands", "Command_Post_TypeColorVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_POST].iDelay				= GetPrivateProfileInt("Commands", "Command_Post_Delay", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_PKClear_Sintax", NULL, this->m_Data[COMMAND_PKCLEAR].szSintax, sizeof(this->m_Data[COMMAND_PKCLEAR].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_PKCLEAR].iEnabled			= GetPrivateProfileInt("Commands", "Command_PKClear_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iVipOnly[0]		= GetPrivateProfileInt("Commands", "Command_PKClear_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iVipOnly[1]		= GetPrivateProfileInt("Commands", "Command_PKClear_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iVipOnly[2]		= GetPrivateProfileInt("Commands", "Command_PKClear_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iVipOnly[3]		= GetPrivateProfileInt("Commands", "Command_PKClear_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iLevel[0]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iLevel[1]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iLevel[2]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iLevel[3]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMoney[0]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMoney[1]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMoney[2]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMoney[3]			= GetPrivateProfileInt("Commands", "Command_PKClear_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iResets[0]        = GetPrivateProfileInt("Commands", "Command_PKClear_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iResets[1]        = GetPrivateProfileInt("Commands", "Command_PKClear_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iResets[2]        = GetPrivateProfileInt("Commands", "Command_PKClear_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iResets[3]        = GetPrivateProfileInt("Commands", "Command_PKClear_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMResets[0]       = GetPrivateProfileInt("Commands", "Command_PKClear_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMResets[1]       = GetPrivateProfileInt("Commands", "Command_PKClear_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMResets[2]       = GetPrivateProfileInt("Commands", "Command_PKClear_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_PKCLEAR].iMResets[3]       = GetPrivateProfileInt("Commands", "Command_PKClear_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_HeroClear_Sintax", NULL, this->m_Data[COMMAND_HEROCLEAR].szSintax, sizeof(this->m_Data[COMMAND_HEROCLEAR].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_HEROCLEAR].iEnabled		= GetPrivateProfileInt("Commands", "Command_HeroClear_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iVipOnly[0]		= GetPrivateProfileInt("Commands", "Command_HeroClear_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iVipOnly[1]		= GetPrivateProfileInt("Commands", "Command_HeroClear_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iVipOnly[2]		= GetPrivateProfileInt("Commands", "Command_HeroClear_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iVipOnly[3]		= GetPrivateProfileInt("Commands", "Command_HeroClear_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iLevel[0]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iLevel[1]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iLevel[2]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iLevel[3]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMoney[0]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMoney[1]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMoney[2]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMoney[3]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iResets[0]      = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iResets[1]      = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iResets[2]      = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iResets[3]      = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMResets[0]     = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMResets[1]     = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_HEROCLEAR].iMResets[3]     = GetPrivateProfileInt("Commands", "Command_HeroClear_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_Evo_Sintax", NULL, this->m_Data[COMMAND_EVO].szSintax, sizeof(this->m_Data[COMMAND_EVO].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_EVO].iEnabled				= GetPrivateProfileInt("Commands", "Command_Evo_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iVipOnly[0]			= GetPrivateProfileInt("Commands", "Command_Evo_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iVipOnly[1]			= GetPrivateProfileInt("Commands", "Command_Evo_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iVipOnly[2]			= GetPrivateProfileInt("Commands", "Command_Evo_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iVipOnly[3]			= GetPrivateProfileInt("Commands", "Command_Evo_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iLevel[0]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iLevel[1]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iLevel[2]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iLevel[3]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMoney[0]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMoney[1]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMoney[2]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMoney[3]				= GetPrivateProfileInt("Commands", "Command_Evo_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iResets[0]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iResets[1]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iResets[2]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iResets[3]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMResets[0]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMResets[1]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMResets[2]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVO].iMResets[3]			= GetPrivateProfileInt("Commands", "Command_Evo_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_Money_Sintax", NULL, this->m_Data[COMMAND_ZEN].szSintax, sizeof(this->m_Data[COMMAND_ZEN].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_ZEN].iEnabled				= GetPrivateProfileInt("Commands", "Command_Money_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iVipOnly[0]			= GetPrivateProfileInt("Commands", "Command_Money_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iVipOnly[1]			= GetPrivateProfileInt("Commands", "Command_Money_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iVipOnly[2]			= GetPrivateProfileInt("Commands", "Command_Money_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iVipOnly[3]			= GetPrivateProfileInt("Commands", "Command_Money_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iLevel[0]				= GetPrivateProfileInt("Commands", "Command_Money_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iLevel[1]				= GetPrivateProfileInt("Commands", "Command_Money_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iLevel[2]				= GetPrivateProfileInt("Commands", "Command_Money_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iLevel[3]				= GetPrivateProfileInt("Commands", "Command_Money_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMoney[0]				= GetPrivateProfileInt("Commands", "Command_Money_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMoney[1]				= GetPrivateProfileInt("Commands", "Command_Money_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMoney[2]				= GetPrivateProfileInt("Commands", "Command_Money_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMoney[3]				= GetPrivateProfileInt("Commands", "Command_Money_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iResets[0]			= GetPrivateProfileInt("Commands", "Command_Money_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iResets[1]			= GetPrivateProfileInt("Commands", "Command_Money_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iResets[2]			= GetPrivateProfileInt("Commands", "Command_Money_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iResets[3]			= GetPrivateProfileInt("Commands", "Command_Money_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMResets[0]			= GetPrivateProfileInt("Commands", "Command_Money_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMResets[1]			= GetPrivateProfileInt("Commands", "Command_Money_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMResets[2]			= GetPrivateProfileInt("Commands", "Command_Money_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ZEN].iMResets[3]			= GetPrivateProfileInt("Commands", "Command_Money_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_AddPoints_SintaxStr", NULL, this->m_Data[COMMAND_ADD].szSintaxAdd[0], sizeof(this->m_Data[COMMAND_ADD].szSintaxAdd[0]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AddPoints_SintaxAgi", NULL, this->m_Data[COMMAND_ADD].szSintaxAdd[1], sizeof(this->m_Data[COMMAND_ADD].szSintaxAdd[1]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AddPoints_SiyntaxVit", NULL, this->m_Data[COMMAND_ADD].szSintaxAdd[2], sizeof(this->m_Data[COMMAND_ADD].szSintaxAdd[2]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AddPoints_SintaxEne", NULL, this->m_Data[COMMAND_ADD].szSintaxAdd[3], sizeof(this->m_Data[COMMAND_ADD].szSintaxAdd[3]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AddPoints_SintaxCmd", NULL, this->m_Data[COMMAND_ADD].szSintaxAdd[4], sizeof(this->m_Data[COMMAND_ADD].szSintaxAdd[4]), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_ADD].iEnabled          = GetPrivateProfileInt("Commands", "Command_AddPoints_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iVipOnly[0]       = GetPrivateProfileInt("Commands", "Command_AddPoints_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iVipOnly[1]       = GetPrivateProfileInt("Commands", "Command_AddPoints_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iVipOnly[2]       = GetPrivateProfileInt("Commands", "Command_AddPoints_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iVipOnly[3]       = GetPrivateProfileInt("Commands", "Command_AddPoints_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iLevel[0]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iLevel[1]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iLevel[2]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iLevel[3]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMoney[0]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMoney[1]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMoney[2]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMoney[3]         = GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iResets[0]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iResets[1]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iResets[2]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iResets[3]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ADD].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_AddPoints_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_ReAddPoints_Sintax", NULL, this->m_Data[COMMAND_READD].szSintax, sizeof(this->m_Data[COMMAND_READD].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_READD].iEnabled        = GetPrivateProfileInt("Commands", "Command_ReAddPoints_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_ReAddPoints_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_ReAddPoints_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_ReAddPoints_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_ReAddPoints_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iResets[0]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iResets[1]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iResets[2]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iResets[3]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_READD].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_ReAddPoints_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_Warehouse_Sintax", NULL, this->m_Data[COMMAND_WARE].szSintax, sizeof(this->m_Data[COMMAND_WARE].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_WARE].iEnabled				= GetPrivateProfileInt("Commands", "Command_Warehouse_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iVipOnly[0]			= GetPrivateProfileInt("Commands", "Command_Warehouse_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iVipOnly[1]			= GetPrivateProfileInt("Commands", "Command_Warehouse_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iVipOnly[2]			= GetPrivateProfileInt("Commands", "Command_Warehouse_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iVipOnly[3]			= GetPrivateProfileInt("Commands", "Command_Warehouse_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iLevel[0]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iLevel[1]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iLevel[2]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iLevel[3]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMoney[0]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMoney[1]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMoney[2]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMoney[3]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iResets[0]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iResets[1]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iResets[2]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iResets[3]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMResets[0]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMResets[1]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMResets[2]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iMResets[3]			= GetPrivateProfileInt("Commands", "Command_Warehouse_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iWareType			= GetPrivateProfileInt("Commands", "Command_Warehouse_WareType", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iWareNumber[0]		= GetPrivateProfileInt("Commands", "Command_Warehouse_WareNumberFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iWareNumber[1]		= GetPrivateProfileInt("Commands", "Command_Warehouse_WareNumberVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iWareNumber[2]		= GetPrivateProfileInt("Commands", "Command_Warehouse_WareNumberVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iWareNumber[3]		= GetPrivateProfileInt("Commands", "Command_Warehouse_WareNumberVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WARE].iDelay				= GetPrivateProfileInt("Commands", "Command_Warehouse_Delay", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_OpenWarehouse_Sintax", NULL, this->m_Data[COMMAND_OPENWARE].szSintax, sizeof(this->m_Data[COMMAND_OPENWARE].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_OPENWARE].iEnabled        = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iResets[0]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iResets[1]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iResets[2]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iResets[3]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_OPENWARE].iDelay			= GetPrivateProfileInt("Commands", "Command_OpenWarehouse_Delay", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_WarehouseInfo_Sintax", NULL, this->m_Data[COMMAND_WAREINFO].szSintax, sizeof(this->m_Data[COMMAND_WAREINFO].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_WAREINFO].iEnabled        = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iResets[0]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iResets[1]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iResets[2]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iResets[3]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_WAREINFO].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_WarehouseInfo_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_EventManager_Sintax_Open", NULL, gEventManager.m_Data.szSintax, sizeof(gEventManager.m_Data.szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_EventManager_Sintax_Enter", NULL, gEventManager.m_Data.szEnter, sizeof(gEventManager.m_Data.szEnter), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_EVENT].iEnabled        = GetPrivateProfileInt("Commands", "Command_EventManager_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_EventManager_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_EventManager_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_EventManager_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_EventManager_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_EventManager_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iResets[0]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iResets[1]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iResets[2]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iResets[3]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_EVENT].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_EventManager_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_DW", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[0], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[0]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_SM", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[1], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[1]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_DK", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[2], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[2]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_BK", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[3], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[3]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_FE", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[4], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[4]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_ME", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[5], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[5]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_MG", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[6], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[6]), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_AltClass_Sintax_DL", NULL, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[7], sizeof(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[7]), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_ALTCLASS].iEnabled        = GetPrivateProfileInt("Commands", "Command_AltClass_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_AltClass_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_AltClass_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_AltClass_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_AltClass_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_AltClass_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iResets[0]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iResets[1]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iResets[2]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iResets[3]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_ALTCLASS].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_AltClass_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	GetPrivateProfileString("Commands", "Command_CharInfo_Sintax", NULL, this->m_Data[COMMAND_CHARINFO].szSintax, sizeof(this->m_Data[COMMAND_CHARINFO].szSintax), COMMANDS_FILE);
	// ---
	this->m_Data[COMMAND_CHARINFO].iEnabled        = GetPrivateProfileInt("Commands", "Command_CharInfo_Enabled", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iVipOnly[0]     = GetPrivateProfileInt("Commands", "Command_CharInfo_SwitchFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iVipOnly[1]     = GetPrivateProfileInt("Commands", "Command_CharInfo_SwitchVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iVipOnly[2]     = GetPrivateProfileInt("Commands", "Command_CharInfo_SwitchVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iVipOnly[3]     = GetPrivateProfileInt("Commands", "Command_CharInfo_SwitchVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iLevel[0]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedLevelFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iLevel[1]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedLevelVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iLevel[2]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedLevelVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iLevel[3]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedLevelVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMoney[0]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMoneyFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMoney[1]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMoneyVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMoney[2]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMoneyVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMoney[3]       = GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMoneyVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iResets[0]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iResets[1]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iResets[2]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iResets[3]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedResetsVip3", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMResets[0]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMasterResetsFree", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMResets[1]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMasterResetsVip1", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMResets[2]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMasterResetsVip2", NULL, COMMANDS_FILE);
	this->m_Data[COMMAND_CHARINFO].iMResets[3]		= GetPrivateProfileInt("Commands", "Command_CharInfo_NeedMasterResetsVip3", NULL, COMMANDS_FILE);
	// ---
	LogAdd(LOG_GOLD, "[COMMANDS FILE] Carregado !");
}

bool CCommands::IsCheck(LPOBJ lpObj, int iCommand)
{
	if(!this->m_Data[iCommand].iEnabled)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Comando Desativado.", lpObj->Name);
		return false;
	}
	// ---
	if(!this->m_Data[iCommand].iVipOnly[lpObj->m_Vip])
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Vip Insuficiente.", lpObj->Name);
		return false;
	}
	// ---
	if(lpObj->Level < this->m_Data[iCommand].iLevel[lpObj->m_Vip])
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Level Necessario %d.", lpObj->Name, this->m_Data[iCommand].iLevel[lpObj->m_Vip]);
		return false;
	}
	// ---
	if(lpObj->Money < this->m_Data[iCommand].iMoney[lpObj->m_Vip])
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Zen Necessario %d.", lpObj->Name, this->m_Data[iCommand].iMoney[lpObj->m_Vip]);
		return false;
	}
	// ---
	if(lpObj->m_Resets < this->m_Data[iCommand].iResets[lpObj->m_Vip])
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Reset Necessario %d.", lpObj->Name, this->m_Data[iCommand].iResets[lpObj->m_Vip]);
		return false;
	}
	// ---
	if(lpObj->m_MasterResets < this->m_Data[iCommand].iMResets[lpObj->m_Vip])
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Master Reset Necessario %d.", lpObj->Name, this->m_Data[iCommand].iMResets[lpObj->m_Vip]);
		return false;
	}
	// ---
	lpObj->Money -= this->m_Data[iCommand].iMoney[lpObj->m_Vip];
	// ---
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	// ---
	return true;
}

void CCommands::Info(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	// ---
	MsgUser(aIndex, 0, "eMu Season I");
	MsgUser(aIndex, 0, "Version : 1.0.0.0x");
	MsgUser(aIndex, 0, "Developer : Hugo Gomes | HGTeam");
	MsgUser(aIndex, 0, "Skype : hugo.alexandre.777");
	// ---
	GCLevelUpMsgSend(aIndex, true);
}

void CCommands::Post(int aIndex, char *szMsg)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_POST) == false)
	{
		return;
	}
	// ---
	if(strlen(szMsg) <= NULL)
	{
		MsgUser(aIndex, 1, "Como usar o comando: /post <msg>");
		return;
	}
	// ---
	DWORD dwDelay = (GetTickCount() - gObj[aIndex].m_DelayPost) / 1000;
	// ---
	if(dwDelay < this->m_Data[COMMAND_POST].iDelay)
	{
		MsgUser(aIndex, 1, "[%s] Aguarde %d segundo(s) para postar.", gObj[aIndex].Name, (this->m_Data[COMMAND_POST].iDelay - dwDelay));
		return;
	}
	// ---
	gObj[aIndex].m_DelayPost = GetTickCount();
	// ---
	char CMessage[100];
	// ---
	PMSG_CHATDATA pMsg;
	// ---
	pMsg.h.set((LPBYTE)&pMsg,0x00,sizeof(pMsg));
	// ---
	memset(&pMsg.chatid, 0, sizeof(pMsg.chatid));
	memset(&pMsg.chatmsg, 0, sizeof(pMsg.chatmsg));
	// ---
	sprintf_s(CMessage, "[POST] %s: %s", gObj[aIndex].Name, szMsg); // -> Normal
	// ---
	if(this->m_Data[COMMAND_POST].iPostColor[gObj[aIndex].m_Vip] == 0) // -> Golden
	{
		pMsg.h.headcode = 0x02;
	}
	else if(this->m_Data[COMMAND_POST].iPostColor[gObj[aIndex].m_Vip] == 1) // -> Blue
	{
		sprintf(CMessage, "~[POST] %s: %s", gObj[aIndex].Name, szMsg);
	}
	else if(this->m_Data[COMMAND_POST].iPostColor[gObj[aIndex].m_Vip] == 2) // -> Green
	{
		sprintf(CMessage, "@[POST] %s: %s", gObj[aIndex].Name, szMsg);
	}
	else if(this->m_Data[COMMAND_POST].iPostColor[gObj[aIndex].m_Vip] == 3) // -> Yellow
	{
		sprintf(CMessage, "@@[POST] %s: %s", gObj[aIndex].Name, szMsg);
	}
	// ---
	memcpy(&pMsg.chatmsg,CMessage,strlen(CMessage));
	// ---
	pMsg.h.size = (strlen(CMessage)+ 0x13);
	// ---
	DataSendAll((LPBYTE)&pMsg,pMsg.h.size);
}

void CCommands::PkClear(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_PKCLEAR) == false)
	{
		return;
	}
	// ---
	if(gObj[aIndex].m_PK_Level <= 3)
	{
		MsgUser(aIndex, 1, "%s você não é serial killer", gObj[aIndex].Name);
		return;
	}
	// ---
	gObj[aIndex].m_PK_Level	= 0;
	gObj[aIndex].m_PK_Time	= 0;
	gObj[aIndex].m_PK_Count	= 0;
	// ---
	GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);
	// ---
	MsgUser(aIndex, 1, "%s você não é mais um serial killer", gObj[aIndex].Name);
}

void CCommands::HeroClear(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_HEROCLEAR) == false)
	{
		return;
	}
	// ---
	if(gObj[aIndex].m_PK_Level <= 3)
	{
		MsgUser(aIndex, 1, "%s você não é Heroi", gObj[aIndex].Name);
		return;
	}
	// ---
	gObj[aIndex].m_PK_Level		= 0;
	gObj[aIndex].m_PK_Time		= 0;
	gObj[aIndex].m_PK_Time		= 0;
	// ---
	GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);
	GCPkLevelSend(aIndex, 3);
	// ---
	MsgUser(aIndex, 1, "%s você não é mais um Heroi", gObj[aIndex].Name);
}
// ---
void CCommands::Evo(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_EVO) == false)
	{
		return;
	}
	// ---
	if(gObj[aIndex].DbClass == 1 || gObj[aIndex].DbClass == 17 || gObj[aIndex].DbClass == 33)
	{
		MsgUser(aIndex, 1, "Você já está na ultima evolução.");
		return;
	}
	// ---
	else if(gObj[aIndex].DbClass == 48 || gObj[aIndex].DbClass == 64)
	{
		MsgUser(aIndex, 1, "Você não possui evolução.");
		return;
	}
	// ---
	gObj[aIndex].ChangeUP = 1;
	gObj[aIndex].DbClass |= 1;
	// ---
	gObjMakePreviewCharSet(gObj[aIndex].m_Index);
	// ---
	BYTE btClass = (gObj[aIndex].Class << 5) & 0xE0;
	btClass |= (gObj[aIndex].ChangeUP << 4) & 0x10;
	// ---
	GCSendQuestPrize(gObj[aIndex].m_Index, 201, btClass);
	// ---
	MsgUser(aIndex, 1, "%s sua evolução teve sucesso!", gObj[aIndex].Name);
}
// ---
void CCommands::Money(int aIndex, char * szMsg)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_ZEN) == false)
	{
		return;
	}
	// ---
	int iZenCount = atoi(szMsg);
	// ---
	if(iZenCount < 0)
	{
		MsgUser(aIndex, 1, "Você não pode adicionar valores negativos no zen!");
		return;
	}
	else
	{
		if(gObj[aIndex].Money + iZenCount >= 2000000000 || gObj[aIndex].Money >= 2000000000 || iZenCount >= 2000000000)
		{
			MsgUser(aIndex, 1, "Você não pode adicionar mais que %d.", 2000000000);
			return;
		}
		else
		{
			gObj[aIndex].Money += iZenCount;
			// ---
			GCMoneySend(aIndex, gObj[aIndex].Money);
			// ---
			MsgUser(aIndex, 1, "Você Adcionou %d Zen(s).", iZenCount);
		}
	}
}

void CCommands::ReAdd(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_READD) == false)
	{
		return;
	}
	// ---
	WORD wStrength		= DCInfo.DefClass[gObj[aIndex].Class].Strength; 
	WORD wDexterity		= DCInfo.DefClass[gObj[aIndex].Class].Dexterity; 
	WORD wVitality		= DCInfo.DefClass[gObj[aIndex].Class].Vitality; 
	WORD wEnergy		= DCInfo.DefClass[gObj[aIndex].Class].Energy;
	WORD wLeadership	= DCInfo.DefClass[gObj[aIndex].Class].Leadership;
	// ---
	gObj[aIndex].LevelUpPoint += (gObj[aIndex].Strength - wStrength) + (gObj[aIndex].Dexterity - wDexterity) + (gObj[aIndex].Vitality - wVitality) + (gObj[aIndex].Energy - wEnergy) + (gObj[aIndex].Leadership - wLeadership);
	// ---
	gObj[aIndex].Strength		= wStrength; 
	gObj[aIndex].Dexterity		= wDexterity; 
	gObj[aIndex].Vitality		= wVitality; 
	gObj[aIndex].Energy			= wEnergy;
	gObj[aIndex].Leadership		= wLeadership;
	// ---
	gToolKit.Refresh(aIndex);
	// ---
	gObjCalCharacter(aIndex);
	// ---
	GCManaSend(aIndex, gObj[aIndex].MaxMana + gObj[aIndex].AddMana, 0xFE, 0, gObj[aIndex].MaxBP + gObj[aIndex].AddBP);
	// ---
	gObjSetBP(aIndex);
	// ---
	GCReFillSend(aIndex, gObj[aIndex].MaxLife + gObj[aIndex].AddLife, 0xFE, 0);
	// ---
	GCLevelUpMsgSend(aIndex, true);
	// ---
	MsgUser(aIndex, 1, "[%s] Pontos redistribuidos.", gObj[aIndex].Name);
}

void CCommands::Add(int aIndex, char *szMsg, BYTE btType)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_ADD) == false)
	{
		return;
	}
	// ---
	int iPoints = atoi(szMsg);
	// ---
	if(gObj[aIndex].LevelUpPoint < iPoints || iPoints < 0 || iPoints == 0)
	{
		MsgUser(aIndex, 1, "[%s] Você Não tem Pontos para adicionar !", gObj[aIndex].Name);
		return;
	}
	// ---
	if(iPoints > gServerInfo.m_Data.iMaxStatus)
	{
		MsgUser(aIndex, 1, "[%s] Você não pode adicionar mais que %s pontos !", gObj[aIndex].Name, gServerInfo.m_Data.iMaxStatus);
		return;
	}
	// ---
	char * szBuffer = "";
	// ---
	switch(btType)
	{
	case 0:
		{
			if(gObj[aIndex].Strength + iPoints > gServerInfo.m_Data.iMaxStatus)
			{
				MsgUser(aIndex, 1, "[%s] Limite %d em Força !", gObj[aIndex].Name, gServerInfo.m_Data.iMaxStatus);
				return;
			}
			else
			{
				szBuffer = "Força";
				gObj[aIndex].Strength += iPoints;
				gObj[aIndex].LevelUpPoint -= iPoints;
			}
		}
		break;
	case 1:
		{
			if(gObj[aIndex].Dexterity + iPoints > 32767)
			{
				MsgUser(aIndex, 1, "[%s] Limite %d em Agilidade !", gObj[aIndex].Name, 32767);
				return;
			}
			else
			{
				szBuffer = "Agilidade";
				gObj[aIndex].Dexterity += iPoints;
				gObj[aIndex].LevelUpPoint -= iPoints;
			}
		}
		break;
	case 2:
		{
			if(gObj[aIndex].Vitality + iPoints > 32767)
			{
				MsgUser(aIndex, 1, "[%s] Limite %d em Vitalidade !", gObj[aIndex].Name, 32767);
				return;
			}
			else
			{
				szBuffer = "Vitalidade";
				gObj[aIndex].Vitality += iPoints;
				gObj[aIndex].MaxLife += gObj[aIndex].VitalityToLife * iPoints;
				gObj[aIndex].LevelUpPoint -= iPoints;
			}
		}
		break;
	case 3:
		{
			if(gObj[aIndex].Energy + iPoints > 32767)
			{
				MsgUser(aIndex, 1, "[%s] Limite %d em Energia !", gObj[aIndex].Name, 32767);
				return;
			}
			else
			{
				szBuffer = "Energia";
				gObj[aIndex].Energy += iPoints;
				gObj[aIndex].MaxMana += gObj[aIndex].EnergyToMana * iPoints;
				gObj[aIndex].LevelUpPoint -= iPoints;
			}
		}
		break;
	case 4:
		{
			if(gObj[aIndex].Class == CLASS_DARKLORD)
			{
				if(gObj[aIndex].Leadership + iPoints > 32767)
				{
					MsgUser(aIndex, 1, "[%s] Limite %d em Carisma !", gObj[aIndex].Name, 32767);
					return;
				}
				else
				{
					szBuffer = "Comando";
					gObj[aIndex].Leadership += iPoints;
					gObj[aIndex].LevelUpPoint -= iPoints;
				}
			}
			else
			{
				MsgUser(aIndex, 1, "[%s] Somente Para Dark Lord", gObj[aIndex].Name);
				return;
			}
		}
		break;
	}
	// ---
	gToolKit.Refresh(aIndex);
	// ---
	gObjCalCharacter(aIndex);
	// ---
	GCManaSend(aIndex, gObj[aIndex].MaxMana + gObj[aIndex].AddMana, 0xFE, 0, gObj[aIndex].MaxBP + gObj[aIndex].AddBP);
	// ---
	gObjSetBP(aIndex);
	// ---
	GCLevelUpMsgSend(aIndex, true);
	// ---
	MsgUser(aIndex, 1, "[%s] %d Ponto(s) Adcionados em %s", gObj[aIndex].Name, iPoints, szBuffer);
}

void CCommands::Ware(int aIndex, char * szMsg)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_WARE) == false)
	{
		return;
	}
	// ---
	int iWareCode = atoi(szMsg);
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo : /ware <numero>", gObj[aIndex].Name);
		return;
	}
	// ---
	DWORD dwDelay = (GetTickCount() - gObj[aIndex].m_DelayWare) / 1000;
	// ---
	if(dwDelay < this->m_Data[COMMAND_WARE].iDelay)
	{
		MsgUser(aIndex, 1, "[%s] Aguarde %d segundo(s) para usar o bau.", gObj[aIndex].Name, (this->m_Data[COMMAND_WARE].iDelay - dwDelay));
		return;
	}
	// ---
	gObj[aIndex].m_DelayWare = GetTickCount();
	// ---	
	if(gObj[aIndex].pTransaction == 1 || gObj[aIndex].WarehouseSave == 1)
	{
		MsgUser(aIndex, 1, "[%s] Você não pode trocar de baú agora.", gObj[aIndex].Name);
		return;
	}
	// ---
	switch(this->m_Data[COMMAND_WARE].iWareType)
	{
		case 0:
			{
				if(iWareCode > this->m_Data[COMMAND_WARE].iWareNumber[gObj[aIndex].m_Vip])
				{
					MsgUser(aIndex, 1, "[%s] Seu limite de baús é %d", gObj[aIndex].Name, this->m_Data[COMMAND_WARE].iWareNumber[gObj[aIndex].m_Vip]);
					return;
				}
			}
			break;
			// ---
		case 1:
			{
				if(iWareCode > gObj[aIndex].m_WareNumber)
				{
					MsgUser(aIndex, 1, "[%s] Seu limite de baús é %d", gObj[aIndex].Name, gObj[aIndex].m_WareNumber);
					return;
				}
			}
			break;
		default:
			break;
	}
	// ---
	MsgUser(aIndex, 1, "[%s] Trocando baú ...", gObj[aIndex].Name);
	// ---
	Sleep(1000);
	// ---
	gSQLManager.Execute("EXEC WarehouseChange '%s', %d", gObj[aIndex].AccountID, iWareCode);
	// ---
	MsgUser(aIndex, 1, "[%s] Baú (%d) selecionado.", gObj[aIndex].Name, iWareCode);
}

void CCommands::OpenWare(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_OPENWARE) == false)
	{
		return;
	}
	// ---
	if(gObj[aIndex].pTransaction == 1)
    {
		MsgUser(aIndex, 1, "%s Feche o Trade Para Usar o Comando!", gObj[aIndex].Name);		
		return;
    }
	// ---
	if(gObj[aIndex].m_IfState.use == 1 && gObj[aIndex].m_IfState.type == 7 )
    {
		MsgUser(aIndex, 1, "%s Feche o chaosbox para usar o comando!", gObj[aIndex].Name);	
		return;
	}
	// ---
	if(gObj[aIndex].m_ReqWarehouseOpen != 0  || gObj[aIndex].WarehouseSave != 0 )
	{
		MsgUser(aIndex, 1, "%s Feche o baú para usar o comando!", gObj[aIndex].Name);	
		return;
	}
	// ---
	DWORD dwDelay = (GetTickCount() - gObj[aIndex].m_DelayOpenWare) / 1000;
	// ---
	if(dwDelay < this->m_Data[COMMAND_OPENWARE].iDelay)
	{
		MsgUser(aIndex, 1, "[%s] Aguarde %d segundo(s) para abrir o bau.", gObj[aIndex].Name, (this->m_Data[COMMAND_OPENWARE].iDelay - dwDelay));
		return;
	}
	// ---
	gObj[aIndex].m_DelayWare = GetTickCount();
	// ---	
	gObj[aIndex].m_ReqWarehouseOpen		= 1;
	gObj[aIndex].m_IfState.type			= 6;
	gObj[aIndex].m_IfState.use			= 1;
	gObj[aIndex].m_IfState.state		= 0;
	gObj[aIndex].WarehouseSave			= 1;
	gObj[aIndex].WarehouseCount			= 0;
	// ---
	GDGetWarehouseList(aIndex, gObj[aIndex].AccountID);
	// ---
	GCLevelUpMsgSend(aIndex, true);
	// ---
	MsgUser(aIndex, 1, "[%s] Abrindo baú ...", gObj[aIndex].Name);
	// ---
	Sleep(1000);
	// ---
	MsgUser(aIndex, 1, "[%s] Baú aberto com sucesso.", gObj[aIndex].Name);	
}

void CCommands::WareInfo(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_WAREINFO) == false)
	{
		return;
	}
	// ---
	switch(this->m_Data[COMMAND_WARE].iWareType)
	{
		case 0:
			{
				MsgUser(aIndex, 1, "[%s] Você possui %d Baús Extras.", gObj[aIndex].Name, this->m_Data[COMMAND_WARE].iWareNumber[gObj[aIndex].m_Vip]);
			}
			break;
		case 1:
			{
				MsgUser(aIndex, 1, "[%s] Você possui %d Baús Extras.", gObj[aIndex].Name, gObj[aIndex].m_WareNumber);
			}
			break;
	}
	// ---
	MsgUser(aIndex, 1, "[%s] Para comprar novos baús, utilize o Expansion of Vault.", gObj[aIndex].Name);
}

void CCommands::AltClass(int aIndex, BYTE btType)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_ALTCLASS) == false)
	{
		return;
	}
	// ---
	for(int i = 0; i < 11; i++)
	{
		if(gObj[aIndex].pInventory[i].m_Type > 0)
		{
			MsgUser(aIndex, 1, "[%s] Remova todos os items antes de usar o comando.", gObj[aIndex].Name);
			return;
		}
	}
	// ---
	switch(btType)
	{	
		case 0: gObj[aIndex].DbClass = 0;								break;
		case 1: gObj[aIndex].DbClass = 1;								break;
		case 2: gObj[aIndex].DbClass = 16;								break;
		case 3: gObj[aIndex].DbClass = 17;								break;
		case 4: gObj[aIndex].DbClass = 32;								break;
		case 5:	gObj[aIndex].DbClass = 33;								break;
		case 6:	gObj[aIndex].DbClass = 48;								break;
		case 7:	gObj[aIndex].DbClass = 64; gObj[aIndex].AddLeadership;	break;
		// ---
		default: break;
	}
	// ---
	gObj[aIndex].CloseType  = 1;
	gObj[aIndex].CloseCount = 1;
}

void CCommands::CharInfo(int aIndex)
{
	if(this->IsCheck(&gObj[aIndex], COMMAND_CHARINFO) == false)
	{
		return;
	}
	// ---
	MsgUser(aIndex, 1, "[%s] Você possui %d Golds, %d Cashs.", gObj[aIndex].Name, gObj[aIndex].m_Gold, gObj[aIndex].m_Cash);
	// ---
	MsgUser(aIndex, 1, "[%s] Você possui %d Resets, %d MasterResets.", gObj[aIndex].Name, gObj[aIndex].m_Resets, gObj[aIndex].m_MasterResets);
	// ---
	/*if(hgtObj->m_Vip > 0)
	{
		MsgUser(aIndex, 1, "[%s] Você possui %d dia(s) Vip.", gObj[aIndex].Name, gObj[aIndex].m_VipDays);
	}
	else
	{
		MsgUser(aIndex, 1, "[%s] Você não é Vip.", gObj[aIndex].Name);
	}*/
	// ---
	/*if(hgtObj->m_OnHour > 0)
	{
		MsgUser(aIndex, 1, "[%s] Você possui %d hora(s) online.", gObj[aIndex].Name, gObj[aIndex].m_OnHour);
	}
	else
	{
		MsgUser(aIndex, 1, "[%s] Você possui %d minuto(s) online.", gObj[aIndex].Name, gObj[aIndex].m_OnMin);
	}*/
}

void CCommands::Manager(PMSG_CHATDATA * lpMsg, int aIndex)
{
	if (!_memicmp(lpMsg->chatmsg, "/info", strlen("/info")))
	{
		this->Info(aIndex);
	}

	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_POST].szSintax, strlen(this->m_Data[COMMAND_POST].szSintax)))
	{
		this->Post(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_POST].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_PKCLEAR].szSintax, strlen(this->m_Data[COMMAND_PKCLEAR].szSintax)))
	{
		this->PkClear(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_HEROCLEAR].szSintax, strlen(this->m_Data[COMMAND_HEROCLEAR].szSintax)))
	{
		this->HeroClear(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_EVO].szSintax, strlen(this->m_Data[COMMAND_EVO].szSintax)))
	{
		this->Evo(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ZEN].szSintax, strlen(this->m_Data[COMMAND_ZEN].szSintax)))
	{
		this->Money(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ZEN].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ADD].szSintaxAdd[0], strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[0])))
	{
		this->Add(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[0])], 0);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ADD].szSintaxAdd[1], strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[1])))
	{
		this->Add(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[1])], 1);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ADD].szSintaxAdd[2], strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[2])))
	{
		this->Add(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[2])], 2);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ADD].szSintaxAdd[3], strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[3])))
	{
		this->Add(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[3])], 3);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ADD].szSintaxAdd[4], strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[4])))
	{
		this->Add(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_ADD].szSintaxAdd[4])], 4);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_READD].szSintax, strlen(this->m_Data[COMMAND_READD].szSintax)))
	{
		this->ReAdd(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_WARE].szSintax, strlen(this->m_Data[COMMAND_WARE].szSintax)))
	{
		this->Ware(aIndex, &lpMsg->chatmsg[strlen(this->m_Data[COMMAND_WARE].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_OPENWARE].szSintax, strlen(this->m_Data[COMMAND_OPENWARE].szSintax)))
	{
		this->OpenWare(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_WAREINFO].szSintax, strlen(this->m_Data[COMMAND_WAREINFO].szSintax)))
	{
		this->WareInfo(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[0], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[0])))
	{
		this->AltClass(aIndex, 0);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[1], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[1])))
	{
		this->AltClass(aIndex, 1);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[2], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[2])))
	{
		this->AltClass(aIndex, 2);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[3], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[3])))
	{
		this->AltClass(aIndex, 3);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[4], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[4])))
	{
		this->AltClass(aIndex, 4);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[5], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[5])))
	{
		this->AltClass(aIndex, 5);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[6], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[6])))
	{
		this->AltClass(aIndex, 6);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[7], strlen(this->m_Data[COMMAND_ALTCLASS].szSintaxAlt[7])))
	{
		this->AltClass(aIndex, 7);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, this->m_Data[COMMAND_CHARINFO].szSintax, strlen(this->m_Data[COMMAND_CHARINFO].szSintax)))
	{
		this->CharInfo(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gReset.szSintax, strlen(gReset.szSintax)))
	{
		gReset.Init(&gObj[aIndex]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gMasterReset.szSintax, strlen(gMasterReset.szSintax)))
	{
		gMasterReset.Init(&gObj[aIndex]);
	}
	// ---
	for(int i = 0; i <  gMoves.iCount; i++)
	{
		if (!_memicmp(lpMsg->chatmsg, gMoves.m_Data[i].szSintax, strlen(gMoves.m_Data[i].szSintax)))
		{
			gMoves.Init(&gObj[aIndex], gMoves.m_Data[i].bEnabled, gMoves.m_Data[i].szVip, gMoves.m_Data[i].szPK, gMoves.m_Data[i].sLevel, gMoves.m_Data[i].sMap, gMoves.m_Data[i].sCordX, gMoves.m_Data[i].sCordY);
		}
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gEventManager.m_Data.szSintax, strlen(gEventManager.m_Data.szSintax)))
	{
		gEventManager.CommandInit(aIndex, &lpMsg->chatmsg[strlen(gEventManager.m_Data.szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gEventManager.m_Data.szEnter, strlen(gEventManager.m_Data.szEnter)))
	{
		gEventManager.CommandEnter(aIndex);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_RELOAD].szSintax, strlen(gPrivilege.m_Data[COMMAND_RELOAD].szSintax)))
	{
		gPrivilege.Reload(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_RELOAD].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_DISCONNECT].szSintax, strlen(gPrivilege.m_Data[COMMAND_DISCONNECT].szSintax)))
	{
		gPrivilege.Disconnect(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_DISCONNECT].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_BLOCK].szSintax, strlen(gPrivilege.m_Data[COMMAND_BLOCK].szSintax)))
	{
		gPrivilege.Block(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_BLOCK].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_UNBLOCK].szSintax, strlen(gPrivilege.m_Data[COMMAND_UNBLOCK].szSintax)))
	{
		gPrivilege.UnBlock(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_UNBLOCK].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_SKIN].szSintax, strlen(gPrivilege.m_Data[COMMAND_SKIN].szSintax)))
	{
		gPrivilege.Skin(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_SKIN].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_MAKE].szSintax, strlen(gPrivilege.m_Data[COMMAND_MAKE].szSintax)))
	{
		gPrivilege.Make(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_MAKE].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_GMOVE].szSintax, strlen(gPrivilege.m_Data[COMMAND_GMOVE].szSintax)))
	{
		gPrivilege.Move(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_GMOVE].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_MOVEALL].szSintax, strlen(gPrivilege.m_Data[COMMAND_MOVEALL].szSintax)))
	{
		gPrivilege.MoveAll(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_MOVEALL].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_REWARD].szSintax, strlen(gPrivilege.m_Data[COMMAND_REWARD].szSintax)))
	{
		gPrivilege.Reward(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_REWARD].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_SETZEN].szSintax, strlen(gPrivilege.m_Data[COMMAND_SETZEN].szSintax)))
	{
		gPrivilege.SetZen(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_SETZEN].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_SETLEVEL].szSintax, strlen(gPrivilege.m_Data[COMMAND_SETLEVEL].szSintax)))
	{
		gPrivilege.SetLevel(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_SETLEVEL].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_SETPK].szSintax, strlen(gPrivilege.m_Data[COMMAND_SETPK].szSintax)))
	{
		gPrivilege.SetPKLevel(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_SETPK].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_SETDROP].szSintax, strlen(gPrivilege.m_Data[COMMAND_SETDROP].szSintax)))
	{
		gPrivilege.SetDrop(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_SETDROP].szSintax)]);
	}
	// ---
	if (!_memicmp(lpMsg->chatmsg, gPrivilege.m_Data[COMMAND_HIDE].szSintax, strlen(gPrivilege.m_Data[COMMAND_HIDE].szSintax)))
	{
		gPrivilege.Hide(aIndex, &lpMsg->chatmsg[strlen(gPrivilege.m_Data[COMMAND_HIDE].szSintax)]);
	}
}