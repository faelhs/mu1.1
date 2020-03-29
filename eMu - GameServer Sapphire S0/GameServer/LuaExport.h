#pragma once

#include "winutil.h"
#include "gObjMonster.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "SetItemOption.h"
#include "LargeRand.h"

class LuaExport
{
public:
	LuaExport();
	virtual ~LuaExport();

	void	AddTable(lua_State * Lua);
	void	AddGlobal(lua_State * Lua);

	static BOOL		LuaChatTargetSend(lua_State * Lua)
	{
		ChatTargetSend(&gObj[lua_tointeger(Lua, 2)], (char*)lua_tostring(Lua, 1), lua_tointeger(Lua, 3));
		return true;
	};

	static BOOL		LuaLogAdd(lua_State * Lua)
	{
		LogAdd(LOG_BLACK, "%s", (char*)lua_tostring(Lua, 1));
		return true;
	};

	static BOOL		LuagObjTeleport(lua_State * Lua)
	{
		gObjTeleport(lua_tointeger(Lua, 1), lua_tointeger(Lua, 2), lua_tointeger(Lua, 3), lua_tointeger(Lua, 4));
		return true;
	};

	static BOOL		LuaGCServerMsgStringSend(lua_State * Lua)
	{
		GCServerMsgStringSend((char*)lua_tostring(Lua, 1), lua_tointeger(Lua, 2), lua_tointeger(Lua, 3));
		return true;
	};

	static BOOL		LuaFireCrackerOpen(lua_State * Lua)
	{
		PMSG_SERVERCMD ServerCmd;

		PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
		ServerCmd.CmdType = 0;
		ServerCmd.X = gObj[lua_tointeger(Lua, 1)].X;
		ServerCmd.Y = gObj[lua_tointeger(Lua, 1)].Y;

		MsgSendV2(&gObj[lua_tointeger(Lua, 1)], (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		DataSend(lua_tointeger(Lua, 1), (LPBYTE)&ServerCmd, sizeof(ServerCmd));

		return true;
	};

	static BOOL		LuagObjCalDistance(lua_State * Lua)
	{
		BOOL Result = gObjCalDistance(&gObj[lua_tointeger(Lua, 1)], &gObj[lua_tointeger(Lua, 2)]);
		lua_pushnumber(Lua, Result);
		return Result;
	};

	static BOOL		LuaGCServerCmd(lua_State * Lua)
	{
		GCServerCmd(lua_tointeger(Lua, 1), lua_tointeger(Lua, 2), lua_tointeger(Lua, 3), lua_tointeger(Lua, 4));
		return true;
	};

	static BOOL		LuagUserFindDevilSquareKeyEyes(lua_State * Lua)
	{
		BOOL Result = gUserFindDevilSquareKeyEyes(lua_tointeger(Lua, 1));
		lua_pushnumber(Lua, Result);
		return Result;
	};

	static BOOL		LuaGCReFillSend(lua_State * Lua)
	{
		GCReFillSend(lua_tointeger(Lua, 1), lua_tointeger(Lua, 2), lua_tointeger(Lua, 3), lua_tointeger(Lua, 4));
		return true;
	};

	static BOOL		LuaGCManaSend(lua_State * Lua)
	{
		GCManaSend(lua_tointeger(Lua, 1), lua_tointeger(Lua, 2), lua_tointeger(Lua, 3), lua_tointeger(Lua, 4), lua_tointeger(Lua, 5));
		return true;
	};

	static BOOL		LuagQeustNpcTeleport_TalkRefAdd(lua_State * Lua)
	{
		gQeustNpcTeleport.TalkRefAdd();
		return true;
	};

	static BOOL		LuagObjIsConnected(lua_State * Lua)
	{
		BOOL Result = gObjIsConnected(lua_tointeger(Lua, 1));
		lua_pushnumber(Lua, Result);
		return Result;
	};

	static BOOL		LuagObjGuildMasterCapacityTest(lua_State * Lua)
	{
		BOOL Result = gObjGuildMasterCapacityTest(&gObj[lua_tointeger(Lua, 1)]);
		lua_pushnumber(Lua, Result);
		return Result;
	};

	static BOOL		LuagObjMonsterTopHitDamageUser(lua_State * Lua)
	{
		BOOL Result = gObjMonsterTopHitDamageUser(&gObj[lua_tointeger(Lua, 1)]);
		lua_pushnumber(Lua, Result);
		return Result;
	};

	static BOOL		LuaItemSerialCreateSend(lua_State * Lua)
	{
		int iItemID = lua_tointeger(Lua, 5);

		ItemSerialCreateSend(
			lua_tointeger(Lua, 1), lua_tointeger(Lua, 2),
			lua_tointeger(Lua, 3), lua_tointeger(Lua, 4),
			iItemID, lua_tointeger(Lua, 6),
			lua_tointeger(Lua, 7), lua_tointeger(Lua, 8),
			lua_tointeger(Lua, 9), lua_tointeger(Lua, 10),
			lua_tointeger(Lua, 11), lua_tointeger(Lua, 12),
			lua_tointeger(Lua, 13));
		return true;
	};

	static BOOL		LuaMakeRandomSetItem(lua_State * Lua)
	{
		MakeRandomSetItem(lua_tointeger(Lua, 1));
		return true;
	};

	static BOOL		LuaIsItem(lua_State * Lua)
	{
		bool isItem = IsItem(lua_tointeger(Lua, 1));
		lua_pushboolean(Lua, isItem);
		return true;
	}

	static BOOL		LuaNewOptionRand(lua_State * Lua)
	{
		int Exc = NewOptionRand(0);
		lua_pushnumber(Lua, Exc);
		return true;
	}

	static BOOL		LuaGetSetItemOption(lua_State * Lua)
	{
		int SetOption = gSetItemOption.GenSetOption(lua_tointeger(Lua, 1));
		lua_pushnumber(Lua, SetOption);
		return true;
	}

	static BOOL		LuaGetRandomValue(lua_State * Lua)
	{
		int Div = lua_tointeger(Lua, 1);

		if (Div == 0)
		{
			LogAdd(LOG_RED, "[LUA] ERROR - LuaGetRandomValue Divider == 0");
			return false;
		}

		int Val = rand() % Div;
		lua_pushnumber(Lua, Val);
		return true;
	}

	static BOOL		LuaGetLargeRandomValue(lua_State * Lua)
	{
		int Div = lua_tointeger(Lua, 1);

		if (Div == 0)
		{
			LogAdd(LOG_RED, "[LUA] ERROR - LuaGetLargeRandomValue Divider == 0");
			return false;
		}

		int Val = GetLargeRand() % Div;
		lua_pushnumber(Lua, Val);
		return true;
	}
}; 

extern LuaExport gLuaExport;