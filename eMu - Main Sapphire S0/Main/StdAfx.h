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
#include <windows.h>
#include <WinBase.h>
#include <WinSock2.h>
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
#include <WinInet.h>
#include <rpc.h>
#include <rpcdce.h>
#include <ShellAPI.h>
#include <Psapi.h>
#include <wchar.h>
#include "detoured.h"
#include "detours.h"
#include "glaux.h"
// ---
#include <gl\GLU.h>
#include <gl\GL.h>
// ---
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLu32.lib")
#pragma comment(lib,"GLaux.lib")
#pragma comment(lib,"Detours.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib,"Ws2_32.lib")
// ---
#include "ToolKit.h"
#include "MainInfo.h"
#include "Defines.h"
#include "Window.h"
#include "Font.h"
#include "Protocol.h"
#include "Protect.h"
#include "CRC.h"
#include "ItemManager.h"
#include "Packets.h"
#include "Controller.h"
#include "Memory.h"
#include "Points.h"
#include "VisualFix.h"
#include "Reconnect.h"
#include "User.h"
#include "Interface.h"
#include "Camera.h"
#include "Plugins.h"
#include "HealthBar.h"
#include "WingManager.h"
#include "Monster.h"
#include "MiniMap.h"
#include "GlowManager.h"
#include "MathLib.h"
#include "Tokenizer.h"
#include "Encode.h"
#include "ReadScript.h"
#include "Console.h"
#include "DrawUserInfo.h"