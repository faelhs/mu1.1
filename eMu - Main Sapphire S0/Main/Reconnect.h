#ifndef _RECONNECT_H
#define _RECONNECT_H

#include "Packets.h"

#pragma pack(push, 1)
struct CONNECTEX_LOGIN
{
	PBMSG_HEAD2	h;
	char		AccountID[10];
	char		Password[10];
	char		Name[10];
	DWORD		TickCount;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_ANS_SERVER_INFO
{
	PBMSG_HEAD2 h;
	char		Ip[16];
	WORD		Port;
};
#pragma pack(pop)

enum eReconnectState 
{
	Select_Server    = 2,
	Select_Char		= 4,
	Select_Game		= 5,
};

enum eReconnectMainEvent
{
	Disconnect = 0x70,
};

namespace eReconnectType
{
	enum T
	{
		OnLine				= 0,
		OnReconnect			= 1,
		OnForceDisconnect	= 2,
	};
};

class CReconnect
{
public:
	void Load();
	// ---
	std::string Account;
	std::string Password;
	// ---
	static void GetAccountInfo();
	static void Disconnect();
	static void MenuExit();
	// ---
	void Run();
	void DrawProgress();
	void InitConnect();
	void RestoreGame();
	void ClearGame();
	static void CreateConnect(LPCSTR lpszIp, WORD wPort);
	void Relogin();
	// ---
	void DataSendEx(LPBYTE lpData, DWORD dwSize);
	// ---
	int iConnectState;
	// ---
private:
	// ---
	int iCount;
	// ---
	int iGameServerPort;
	int iConnectServerPort;
	// ---
	DWORD dwTickCount;
	// ---
	std::string GameServerIp;
	std::string ConnectServerIp;
	// ---
	std::vector<DWORD> XorFilter;
};

extern CReconnect gReconnect;

#endif