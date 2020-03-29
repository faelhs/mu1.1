#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WINVER
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT               
#define _WIN32_WINNT 0x0501
#endif
#ifndef _WIN32_WINNT               
#define _WIN32_WINNT 0x0610
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x0600
#endif
#define WIN32_LEAN_AND_MEAN
// ---
#include <afx.h>
#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <process.h>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <winsock2.h>
#include <WinInet.h>
#include <rpc.h>
#include <rpcdce.h>
#include <Psapi.h>
#include <Imm.h>
#include "..\\Lua\\include\\lua.hpp"
#include "COMMCTRL.h"
#include "MuMsg.h"
// ---
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"rpcrt4.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"COMCTL32.lib")
#pragma comment(lib,"..\\Lua\\lib\\lua52.lib")
// ---
#include "ServerInfo.h"
#include "Import.h"
// ---
#define SERVER_INFO_PATH	"Data\\Serverinfo.dat"
#define SERVER_FILE			".\\Hgt_GameServer.ini"
// ---
#define FINAL_PATH			"..\\data\\"
#define COMMONSERVER_PATH	"..\\data\\commonserver.cfg"
// ---
#ifdef INTERNATIONAL_KOREAN	
#define PROTOCOL_MOVE 0xD3
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xD7
#define PROTOCOL_BEATTACK 0x10
#endif
// ---
#ifdef INTERNATIONAL_ENGLISH
#define PROTOCOL_MOVE 0xD4
#define PROTOCOL_POSITION 0x15
#define PROTOCOL_ATTACK 0x11
#define PROTOCOL_BEATTACK 0xDB
#endif
// ---
#ifdef INTERNATIONAL_JAPAN
#define PROTOCOL_MOVE 0x1D
#define PROTOCOL_POSITION 0xD6
#define PROTOCOL_ATTACK 0xDC
#define PROTOCOL_BEATTACK 0xD7
#endif
// ---
#ifdef INTERNATIONAL_CHINA
#define PROTOCOL_MOVE 0xD7
#define PROTOCOL_POSITION 0xDD
#define PROTOCOL_ATTACK 0xD9
#define PROTOCOL_BEATTACK 0x1D
#endif
// ---
#ifdef INTERNATIONAL_TAIWAN
#define PROTOCOL_MOVE 0xD6
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xDD
#define PROTOCOL_BEATTACK 0xD2
#endif
// ---
#ifdef INTERNATIONAL_VIETNAM
#define PROTOCOL_MOVE 0xD9
#define PROTOCOL_POSITION 0xDC
#define PROTOCOL_ATTACK 0x15
#define PROTOCOL_BEATTACK 0x1D
#endif
// ---
#ifdef INTERNATIONAL_PHILIPPINES
#define PROTOCOL_MOVE 0xDD
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xD6
#define PROTOCOL_BEATTACK 0x11
#endif