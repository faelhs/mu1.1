#include "StdAfx.h"
#include <WinSock2.h>

CReconnect gReconnect;

void CReconnect::Load()
{
	this->iCount = 0;
	// ---
	this->iConnectState	= eReconnectType::OnLine;
	// ---
	this->dwTickCount = 0;
	// ---
	gToolKit.SetRange((LPVOID)0x006104B0, 18, ASM::NOP);
	gToolKit.SetOp((LPVOID)0x006104B0, (LPVOID)this->MenuExit, ASM::JMP);
	// ---
	gToolKit.SetRange((LPVOID)0x004AD90A, 48, ASM::NOP);
	gToolKit.SetOp((LPVOID)0x004AD90A, (LPVOID)this->Disconnect, ASM::JMP);
	// ---
	gToolKit.SetByte((LPVOID)0x00628FC8, 0xEB);
	gToolKit.SetByte((LPVOID)0x004BBA91, 0xEB);
	gToolKit.SetRange((LPVOID)0x004DC086, 5, ASM::NOP);
	// ---
	gToolKit.SetRange((LPVOID)0x0062110F, 35, ASM::NOP);
	gToolKit.SetOp((LPVOID)0x0062110F, (LPVOID)this->GetAccountInfo, ASM::JMP);
	// ---
	gToolKit.SetOp((LPVOID)0x00411016, (LPVOID)this->CreateConnect, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x004BC24F, (LPVOID)this->CreateConnect, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x004DC04C, (LPVOID)this->CreateConnect, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x00620529, (LPVOID)this->CreateConnect, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x00620E78, (LPVOID)this->CreateConnect, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x00632977, (LPVOID)this->CreateConnect, ASM::CALL);
	// ---
	XorFilter.push_back(0xE7);
	XorFilter.push_back(0x6D);
	XorFilter.push_back(0x3A);
	XorFilter.push_back(0x89);
	XorFilter.push_back(0xBC);
	XorFilter.push_back(0xB2);
	XorFilter.push_back(0x9F);
	XorFilter.push_back(0x73);
	XorFilter.push_back(0x23);
	XorFilter.push_back(0xA8);
	XorFilter.push_back(0xFE);
	XorFilter.push_back(0xB6);
	XorFilter.push_back(0x49);
	XorFilter.push_back(0x5D);
	XorFilter.push_back(0x39);
	XorFilter.push_back(0x5D);
	XorFilter.push_back(0x8A);
	XorFilter.push_back(0xCB);
	XorFilter.push_back(0x63);
	XorFilter.push_back(0x8D);
	XorFilter.push_back(0xEA);
	XorFilter.push_back(0x7D);
	XorFilter.push_back(0x2B);
	XorFilter.push_back(0x5F);
	XorFilter.push_back(0xC3);
	XorFilter.push_back(0xB1);
	XorFilter.push_back(0xE9);
	XorFilter.push_back(0x83);
	XorFilter.push_back(0x29);
	XorFilter.push_back(0x51);
	XorFilter.push_back(0xE8);
	XorFilter.push_back(0x56);
}

DWORD dwJmpAccountInfo;
DWORD dwJmpDisconnectEvent;
DWORD dwJmpMenuExit;
DWORD dwCallAccountInfo;

void __declspec(naked) CReconnect::GetAccountInfo()
{
	_asm
	{
		PUSH 0x0777D7C0;
		PUSH 0x006C47A8;
		PUSH 0x057500D8;
		MOV DWORD PTR DS:[0x7D1A9D0], EAX;
		MOV DWORD PTR DS:[0x7D17210], 0x00;
		MOV dwCallAccountInfo, 0x0041DED0;
		CALL dwCallAccountInfo;
	}
	// ---
	gReconnect.Account.clear();
	gReconnect.Password.clear();
	// ---
	gReconnect.Account.append((LPSTR)(0x777D7C0));
	gReconnect.Password.append((LPSTR)(0x777D7C0));
	// ---
	_asm
	{
		MOV dwJmpAccountInfo, 0x00621132;
		JMP dwJmpAccountInfo;
	}
}

void __declspec(naked) CReconnect::Disconnect()
{
	if(gReconnect.iConnectState != eReconnectType::OnForceDisconnect)
	{
		gReconnect.iConnectState = eReconnectType::OnReconnect;
	}
	else
	{
		pSetMainEvent(eReconnectMainEvent::Disconnect);
	}
	// ---
	_asm
	{
		MOV dwJmpDisconnectEvent, 0x004AD93A;
		JMP dwJmpDisconnectEvent;
	}
}

void __declspec(naked) CReconnect::MenuExit()
{
	gReconnect.iConnectState = eReconnectType::OnForceDisconnect;
	// ---
	_asm
	{
		MOV dwJmpMenuExit, 0x006104C2;
		JMP dwJmpMenuExit;
	}
}

void CReconnect::Run()
{
	DWORD dwDelay = GetTickCount() - this->dwTickCount;
	// ----
	if(this->iConnectState != eReconnectType::OnReconnect)
	{
		return;
	}
	// ----
	this->ClearGame();
	this->DrawProgress();
	// ----
	if(dwDelay < 1500 || pPlayerState != eReconnectState::Select_Game)
	{
		return;
	}
	// ----
	switch(pPlayerOnline)
	{
	case 0x00:
		{
			this->InitConnect();
		}
		break;
		// --
	case 0x01:
		{
			this->Relogin();
		}
		break;
	}
	// ---
	this->dwTickCount = GetTickCount();
}

void CReconnect::DrawProgress()
{
	float StartX = (MIN_WIN_WIDTH / 2) - (160 / 2);
	float StartY = (MIN_WIN_HEIGHT / 2) - (160 / 2);
	// ----
	this->iCount++;
	// ----
	if(this->iCount >= 200)
	{
		this->iCount = 0;
	}
	// ---
	pSetBlend(true);
	// ---
	gInterface.LoadImage(1, "Customs\\Interface\\new_ui_reconnect_back.tga", 0x155555);
	// ---
	gInterface.DrawGUI(0x155555, StartX, 237.0f, 240.0f, 70.0f, 0.82f, 0.60f);
	// ---
	pGLSwitchBlend();
	// ---
	gInterface.LoadImage(0, "Interface\\Progress.jpg", 0x13);
	gInterface.LoadImage(0, "Interface\\Progress_Back.jpg", 0x14);
	// ---
	gInterface.DrawGUI(0x14, StartX + 22, 275.0, 200.0, 16.0, 0.78125, 1.0);
	gInterface.DrawGUI(0x13, StartX + 22, 275.0, this->iCount, 16.0, this->iCount * 0.003906250, 1.0);
	// ---
	pGLSwitch();
	// ---
	if(pPlayerOnline == 0)
	{
		char szTemp[256] = {0};
		// ---
		pSetBlend(true);
		// ---
		sprintf(szTemp, "Reconectando...");
		// ----
		pDrawText(StartX + 70, 205, szTemp);
	}
	// ---
	else if(pPlayerOnline == 1)
	{
		char szTemp[256] = {0};
		// ---
		pSetBlend(true);
		// ---
		sprintf(szTemp, "Autenticando...");
		// ----
		pDrawText(StartX + 70, 205, szTemp);
	}
}

void CReconnect::InitConnect()
{
	PMSG_ANS_SERVER_INFO pRequest = {NULL};
	// ---
	pRequest.h.set((LPBYTE)&pRequest, 0xF4, 3, sizeof(PMSG_ANS_SERVER_INFO));
	// ---
	pRequest.Port = this->iGameServerPort;
	memcpy(pRequest.Ip, GameServerIp.c_str(), 16);
	// ---
	pDataRecv(pRequest.h.headcode, (LPBYTE)&pRequest, pRequest.h.size, 0);
}

void CReconnect::RestoreGame()
{
	this->dwTickCount = 0;
	// ---
	this->iConnectState	= eReconnectType::OnLine;
}

void CReconnect::ClearGame()
{
	//pPartyMemberCount = 0;
	// ---
	*(BYTE*)(pUserPreviewStruct + 872) = 0;
	// ---
	pClearGame_1 = 0;
	pClearGame_2 = 6;
	pClearGame_3 = 0;
	pClearGame_4 = 0;
	pClearGame_5 = 0;
	pClearGame_6 = -1;
	pClearGame_7 = -1;
	pClearGame_8 = -1;
	pClearGame_9 = -1;
	pClearGame_10 = -1;
	pClearGame_11 = -1;
	// ---
	pPShopSet(pPShopThis(), pUserPreviewStruct);
	// ---
	pRefreshGame(pUserPreviewStruct);
}

void CReconnect::CreateConnect(LPCSTR lpszIp, WORD wPort)
{
	gReconnect.ConnectServerIp.clear();
	gReconnect.GameServerIp.clear();
	// ---
	if( wPort == 44405 )
	{
		gReconnect.ConnectServerIp.append(lpszIp);
		gReconnect.iConnectServerPort = wPort;
	}
	// ---
	gReconnect.GameServerIp.append(lpszIp);
	gReconnect.iGameServerPort = wPort;
	// ---
	pCreateConnect(lpszIp, wPort);
}

void CReconnect::Relogin()
{
	CONNECTEX_LOGIN pRequest = {NULL};
	// ---
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 12, sizeof(CONNECTEX_LOGIN));
	// ---
	memcpy(pRequest.AccountID, gReconnect.Account.c_str(), 10);
	memcpy(pRequest.Password, gReconnect.Password.c_str(), 10);
	memcpy(pRequest.Name, gUser.m_Player.Name, 10);
	// ---
	pRequest.TickCount = GetTickCount();
	// ---
	this->DataSendEx((LPBYTE)&pRequest, pRequest.h.size);
}

void CReconnect::DataSendEx(LPBYTE lpData, DWORD dwSize)
{
	int StartPos = 0;
	// ----
	if( lpData[0] == 0xC1 || lpData[0] == 0xC3 )
	{
		StartPos = 3;
	}
	else if( lpData[0] == 0xC2 || lpData[0] == 0xC4 )
	{
		StartPos = 4;
	}
	// ----
	for(int i = StartPos; i < dwSize; i ++)
	{
		lpData[i] ^= lpData[i - 1] ^ XorFilter[i % 32];
	}
	// ----
	send(pActiveSocket, (char*)lpData, dwSize, 0);
}