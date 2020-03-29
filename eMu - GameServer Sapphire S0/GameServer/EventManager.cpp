#include "StdAfx.h"
#include "TNotice.h"

CEventManager gEventManager;

void CEventManager::CommandInit(int aIndex, char * szMsg)
{
	int iMap, iCordX, iCordY, iTime = 0;
	// ---
	if(strlen(szMsg) <= 3)
	{
		MsgUser(aIndex, 1, "Uso: /event <time><map><x><y>");
		return;
	}
	// ---
	sscanf(szMsg, "%d %d %d %d", &iTime, &iMap, &iCordX, &iCordY);
	// ---
	this->m_Data.iTime = iTime;
	this->m_Data.iMap = iMap;
	this->m_Data.iCordX = iCordX;
	this->m_Data.iCordY = iCordY;
	// ---
	this->m_Data.bEventOn = true;
	// ---
	_beginthread(this->TimeTick, NULL, NULL);
}

void CEventManager::CommandEnter(int aIndex)
{
	if(gCommands.IsCheck(&gObj[aIndex], COMMAND_EVENT) == false)
	{
		return;
	}
	// ---
	if(!this->m_Data.bEventOn)
	{
		MsgUser(aIndex, 1, "[%s] Nenhum evento iniciado", gObj[aIndex].Name);
		return;
	}
	// ---
	if(this->m_Data.bMove != false)
	{
		MsgUser(aIndex, 1, "[%s] Você já esta neste evento.", gObj[aIndex].Name);
		return;
	}
	// ---
	this->m_Data.bMove = true;
	// --- 
	MsgUser(aIndex, 1, "[%s] Aguarde, você sera movido", gObj[aIndex].Name);
}

void CEventManager::TimeTick(LPVOID lpParam)
{
	int Delay = gEventManager.m_Data.iTime;
	// ---
	while(Delay > 1)
	{
		Sleep(1 * 1000);
		Delay--;
		MsgAllUser(0, "[Sistema] Move %s fecha em %d %s", gEventManager.m_Data.szEnter, Delay, (Delay > 1) ? "Segundos." : "Segundo.");
	}
	// ---
	Sleep(1 * 1000);
	// ---
	MsgAllUser(0, "[Sistema] Move %s fechou!", gEventManager.m_Data.szEnter);
	// ---
	for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if(gEventManager.m_Data.bMove == true)
		{
			gObjTeleport(i, gEventManager.m_Data.iMap, gEventManager.m_Data.iCordX, gEventManager.m_Data.iCordY);
		}
	}
	// ---
	gEventManager.m_Data.bEventOn = false;
	gEventManager.m_Data.bMove = false;
}