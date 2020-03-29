#include "stdafx.h"
#include "DevilSquare.h"

LuaExport gLuaExport;

LuaExport::LuaExport()
{

}


LuaExport::~LuaExport()
{

}

void LuaExport::AddTable(lua_State * Lua)
{
	lua_register(Lua, "ChatTargetSend", this->LuaChatTargetSend);
	lua_register(Lua, "LogAdd", this->LuaLogAdd);
	lua_register(Lua, "gObjTeleport", this->LuagObjTeleport);
	lua_register(Lua, "GCServerMsgStringSend", this->LuaGCServerMsgStringSend);
	lua_register(Lua, "FireCrackerOpen", this->LuaFireCrackerOpen);
	lua_register(Lua, "gObjCalDistance", this->LuagObjCalDistance);
	lua_register(Lua, "GCServerCmd", this->LuaGCServerCmd);
	lua_register(Lua, "gUserFindDevilSquareKeyEyes", this->LuagUserFindDevilSquareKeyEyes);
	lua_register(Lua, "GCReFillSend", this->LuaGCReFillSend);
	lua_register(Lua, "GCManaSend", this->LuaGCManaSend);
	lua_register(Lua, "gQeustNpcTeleport_TalkRefAdd", this->LuagQeustNpcTeleport_TalkRefAdd);
	lua_register(Lua, "gObjIsConnected", this->LuagObjIsConnected);
	lua_register(Lua, "gObjGuildMasterCapacityTest", this->LuagObjGuildMasterCapacityTest);
	lua_register(Lua, "gObjMonsterTopHitDamageUser", this->LuagObjMonsterTopHitDamageUser);
	lua_register(Lua, "CreateItem", this->LuaItemSerialCreateSend);
	lua_register(Lua, "MakeRandomSetItem", this->LuaMakeRandomSetItem);
	lua_register(Lua, "IsItem", this->LuaIsItem);
	lua_register(Lua, "GetExcellentOpt", this->LuaNewOptionRand);
	lua_register(Lua, "GetAncientOpt", this->LuaGetSetItemOption);
	lua_register(Lua, "GetRandomValue", this->LuaGetRandomValue);
	lua_register(Lua, "GetLargeRandomValue", this->LuaGetLargeRandomValue);
}

void LuaExport::AddGlobal(lua_State * Lua)
{
	lua_pushinteger(Lua, gEnableServerDivision);
	lua_setglobal(Lua, "gEnableServerDivision");

	lua_pushinteger(Lua, gEnableEventNPCTalk);
	lua_setglobal(Lua, "gEnableEventNPCTalk");
}