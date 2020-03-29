#pragma once

#include "..\include\prodef.h"

struct PMSG_CHARINFOMAIN
{
	PBMSG_HEAD h;
	BYTE Code;
	BYTE Class;
	WORD Dexterity;
	WORD AttackSpeed;
	WORD MagicSpeed;
}; 

#define SQL_FILE				".\\Customs\\SQLServer\\Hgt_SQLConnect.ini"
// ---
#define VIP_FILE				".\\Customs\\Systems\\Hgt_Vip.ini"
#define NEWS_FILE				".\\Customs\\Systems\\Hgt_News.ini"
#define TIPS_FILE				".\\Customs\\Systems\\Hgt_Tips.ini"
#define CHARACTER_FILE			".\\Customs\\Systems\\Hgt_Character.ini"
#define DAMAGE_FILE				".\\Customs\\Systems\\Hgt_Damage.ini"
#define MOVES_FILE				".\\Customs\\Systems\\Hgt_Moves.ini"
#define SKILLS_FILE				".\\Customs\\Systems\\Hgt_Skills.ini"
#define PRIVILEGE_FILE			".\\Customs\\Systems\\Hgt_Privilege.ini"
#define LOTTERY_FILE			".\\Customs\\Systems\\Hgt_Lottery.ini"
#define ITEMBLOCK_FILE			".\\Customs\\Systems\\Hgt_ItemBlock.ini"
// ---
#define HAPPYHOUR_FILE			".\\Customs\\Events\\Hgt_HappyHour.ini"
#define DROPEVENT_FILE			".\\Customs\\Events\\Hgt_DropEvent.ini"
// ---
#define COMMANDS_FILE			".\\Customs\\Commands\\Hgt_Commands.ini"
#define RESET_FILE				".\\Customs\\Commands\\Hgt_Reset.ini"
#define MASTERRESET_FILE		".\\Customs\\Commands\\Hgt_MasterReset.ini"
// ---
#define COMMON_FILE				".\\Customs\\Hgt_CommonServer.ini"

#define GAMESERVER_WIDTH		750
#define GAMESERVER_HEIGHT		610

#define NEWWINGS(x)		((x < ITEMGET(12, 100)) ? FALSE : (x > ITEMGET(12, 125)) ? FALSE : TRUE)

#include "SQLManager.h"
#include "Commands.h"
#include "ToolKit.h"
#include "ServerDisplayer.h"
#include "Log.h"
#include "Vip.h"
#include "Reconnect.h"
#include "HealthBar.h"
#include "News.h"
#include "Tips.h"
#include "Tokenizer.h"
#include "Reset.h"
#include "MasterReset.h"
#include "Moves.h"
#include "EventManager.h"
#include "HappyHour.h"
#include "Privilege.h"
#include "Lottery.h"
#include "ItemBlock.h"
#include "DropEvent.h"
// ---
#include "MuLua.h"
#include "LuaExport.h"