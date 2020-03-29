#ifndef _RECONNECT_H
#define _RECONNECT_H
// ---
#include "winutil.h"
// ---
#pragma pack(push, 1)
// ---
struct CONNECTEX_LOGIN
{
	PBMSG_HEAD2	h;
	char		AccountID[10];
	char		Password[10];
	char		Name[10];
	DWORD		TickCount;
};
// ---
#pragma pack(pop)
// ---
#pragma pack(push, 1)
// ---
struct CONNECTEX_CLOSE
{
	PBMSG_HEAD2	h;
};
// ---
#pragma pack(pop)
// ---
class CReconnect
{
public:
	void SendLogin(int UserIndex, CONNECTEX_LOGIN * Data);
	void SendGame(int UserIndex);
	void SendClose(int UserIndex);
private:
	bool PacketCheckTime(LPOBJ lpObj);
};

extern CReconnect gReconnect;

#endif