#include "StdAfx.h"
#include "DSProtocol.h"
#include "SProtocol.h"
#include "winutil.h"
#include "GameMain.h"
#include "DBSockMng.h"

CReconnect gReconnect;

bool CReconnect::PacketCheckTime(LPOBJ lpObj) 
{
	if((GetTickCount() - lpObj->m_PacketCheckTime) < 300)
	{
		return false;
	}
	// ----
	lpObj->m_PacketCheckTime = GetTickCount();
	// ----
	return true;
}

void CReconnect::SendLogin(int UserIndex, CONNECTEX_LOGIN * Data)
{
	BuxConvert(Data->AccountID, MAX_ACCOUNT_LEN);
	BuxConvert(Data->Password, MAX_ACCOUNT_LEN);
	// ---
	char id[11] = {NULL};
	id[10] = 0;
	memcpy(id, Data->AccountID, sizeof(Data->AccountID));
	// ---
	BuxConvert(id, MAX_ACCOUNT_LEN);
	// ---
	GJPUserClose(id);
	// ---
	if(gObj[UserIndex].Connected != PLAYER_CONNECTED)
	{
		CloseClient(UserIndex);
		// ---
		return;
	}
	// ---
	if(gObj[UserIndex].LoginMsgSnd != FALSE)
	{
		return;
	}
	// ---
	if(gObj[UserIndex].Connected >= PLAYER_LOGGED)
	{
		return;
	}
	// ---
	SDHP_IDPASS spMsg = {0};
	// ---
	spMsg.h.set((LPBYTE)&spMsg, 0x01, sizeof(spMsg));
	// ---
	spMsg.Number								= UserIndex;
	// ---
	memcpy(spMsg.Id, Data->AccountID, sizeof(spMsg.Id));
	memcpy(spMsg.Pass, Data->Password, sizeof(spMsg.Pass));
	// ---
	strcpy(spMsg.IpAddress, gObj[UserIndex].Ip_addr);
	// ---
	gObj[UserIndex].CheckTick					= Data->TickCount;
	gObj[UserIndex].CheckTick2					= GetTickCount();
	gObj[UserIndex].ConnectCheckTime			= GetTickCount();
	gObj[UserIndex].CheckSpeedHack				= true;
	gObj[UserIndex].LoginMsgSnd					= 1;
	gObj[UserIndex].LoginMsgCount				= 1;
	gObj[UserIndex].AccountID[MAX_ACCOUNT_LEN]	= 0;
	gObj[UserIndex].Name[MAX_ACCOUNT_LEN]		= 0;
	// ---
	memcpy(gObj[UserIndex].AccountID, id, MAX_ACCOUNT_LEN);
	memcpy(gObj[UserIndex].Name, Data->Name, MAX_ACCOUNT_LEN);
	// ---
	gObj[UserIndex].m_cAccountItemBlock			= 0;
	// ---
	gObj[UserIndex].bReconnect					= true;
	// ---
	wsJServerCli.DataSend((char*)&spMsg, spMsg.h.size);
	// ---
	LogAdd(LOG_GOLD, "[RECONNECT] Join Send : (%d)%s", UserIndex, gObj[UserIndex].AccountID);
	// ---
	gObj[UserIndex].DieRegen			= 1;
	gObj[UserIndex].m_bMapSvrMoveReq	= false;
	gObj[UserIndex].m_sPrevMapSvrCode	= -1; 
	gObj[UserIndex].m_sDestMapNumber	= -1;
	gObj[UserIndex].m_btDestX			= 0;
	gObj[UserIndex].m_btDestY			= 0;
}

void CReconnect::SendGame(int UserIndex)
{
	gObj[UserIndex].bReconnect = false;
	// ---
	DataServerGetCharListRequest(UserIndex);
	// ---
	if(!gReconnect.PacketCheckTime(&gObj[UserIndex]))
	{
		return;
	}
	// ---
	if(!gObjIsAccontConnect(UserIndex, gObj[UserIndex].AccountID))
	{
		return;
	}
	// ---
	if(gObj[UserIndex].Connected == PLAYER_PLAYING)
	{
		return;
	}
	// ---
	gObj[UserIndex].bEnableDelCharacter = 0;
	// ---
	char szName[MAX_ACCOUNT_LEN + 1];
	// ---
	SDHP_DBCHARINFOREQUEST pCRequest = {NULL};
	// ---
	pCRequest.h.set((LPBYTE)&pCRequest, 0x06, sizeof(pCRequest));
	// ---
	memset(szName, 0, MAX_ACCOUNT_LEN);
	memcpy(szName, gObj[UserIndex].Name, MAX_ACCOUNT_LEN);
	// ---
	BuxConvert(szName, MAX_ACCOUNT_LEN);
	// ---
	memcpy(pCRequest.Name, szName, MAX_ACCOUNT_LEN);
	// ---
	strcpy(pCRequest.AccountID, gObj[UserIndex].AccountID);
	// ---
	pCRequest.Number = UserIndex;
	// ---
	cDBSMng.Send((char*)&pCRequest, pCRequest.h.size);
}

void CReconnect::SendClose(int UserIndex)
{
	CONNECTEX_CLOSE pRequest = {NULL};
	// ----
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xC, sizeof(CONNECTEX_CLOSE));
	// ----
	DataSend(UserIndex, (LPBYTE)&pRequest, pRequest.h.size);
}