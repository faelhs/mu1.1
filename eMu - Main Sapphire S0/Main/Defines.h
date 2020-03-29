#ifndef _DEFINES_H
#define _DEFINES_H

#define MIN_WIN_WIDTH		640
#define MIN_WIN_HEIGHT		480

#define ITEM(x, y)		((x * 512) + y)
#define ITEM_ID(x, y)		((x * 512) + y + 515)

#define	MAIN_FILE				".\\Main.ini"
#define GLOW_FILE				".\\Data\\Customs\\Configs\\Hgt_Glow.ini"
#define PLUGIN_FILE				".\\Data\\Customs\\Configs\\Plugins.hgt"

#define pDataRecv				((void(*)(DWORD Type, LPBYTE Data, int Len, int aIndex)) 0x004DB720)

#define pTextDescription        ((int(*)(int Arg1, const char * Text, ...)) 0x0068EFC7) // 007903A0

#define pMakePreviewCharSet     ((void(*)(int aIndex, BYTE * CharSet, int PreviewObject, int Mode, int Agr5, int Agr6, int Agr7)) 0x0050A590)

#define CS_GET_STRUCT(x, y)		(1060 * x + *(int*) y)

#define pPreviewThis            ((DWORD)0x7424644)

#define pUserPreviewStruct		*(int*)0x742464C

#define pInitModelData			((void(__cdecl*)()) 0x005FD0E0)
#define pInitTextureData		((void(__cdecl*)()) 0x005FE910)
#define pAccessModel            ((void(__cdecl*)(int Type, char *Dir, char *FileName, int i)) 0x005FACA0)
#define pOpenTexture            ((int(__cdecl*)(int ObjectID, char *SubFolder, int Wrap, int Type, bool Check)) 0x005FA860)

#define pMainSpeedFrameOne		(float*)(0x006A79D0)
#define pMainSpeedFrameTwo		(float*)(0x006A79A4)

#define pDrawGUI				((void(__cdecl*)(int ObjectId, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x0060DCF0)
#define pDrawInterface			((void(__cdecl*)()) 0x00598C30)
#define pDrawText				((int(*)(int PosX, int PosY, LPCSTR lpText)) 0x0060FAC0)
#define pDrawLegend				((char(*)(int PosX, int PosY, LPCSTR lpText)) 0x005487E0)
#define pDrawBarForm			((void(__cdecl*)(float PosX, float PosY, float Width, float Height)) 0x0060DC30)
#define pDrawDamage				((void(__cdecl*)(int a1, int a2, int a3, float a4, char a5, char a6)) 0x0053DA80)
#define pDrawBar				((double(__cdecl*)(float a1, float a2, int a3, float a4, float a5)) 0x0060DA80)
#define pDrawTab				((int(__cdecl*)(signed int a1, signed int a2, LPCSTR lpMultiByteStr)) 0x005487E0)
#define pDrawInfo				((int(__cdecl*)(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)) 0x00548620)

#define pLoadImage				((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C1E0)
#define pLoadImageTga			((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C670)

#define	pCursorX				*(int*)0x7D17158
#define	pCursorY				*(int*)0x7D1715C

#define pSetMainEvent			((bool (__cdecl*)(DWORD dwEvent)) 0x0060FB20)
#define pPlayerState			*(int*)0x006C41C0
#define pPlayerOnline			*(DWORD *)0x57548F8
#define pCreateConnect			((bool(__cdecl*)(LPCSTR lpszIp, WORD wPort)) 0x004BBA20)
#define pActiveSocket			*(SOCKET*)(*(DWORD*)0x006B7264 + 0x0C)
#define pRefreshGame			((bool (__cdecl*)(int iPreview)) 0x004EA700)
#define pPShopSet				((void(__thiscall*)(LPVOID This, int Mode)) 0x0044BF70)
#define pPShopThis				((LPVOID(__cdecl*)()) 0x0044C850)

#define pSetBlend				((void(__cdecl*)(BYTE Mode)) 0x60CB90)
#define pGLSwitchBlend			((void(__cdecl*)()) 0x60CC20)
#define pGLSwitch				((void(__cdecl*)()) 0x60CB10)

#define pViewMonsterStruct		*(DWORD*)0x7424644
#define pGetViewPortId			((int(__cdecl*)(int aIndex)) 0x507C70)
#define pGetPosFromAngle		((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x60C740)
#define pMainState				*(int*)0x006C41C0

#define pClearGame_1			*(int*)0x77D86D8
#define pClearGame_2			*(int*)0x6B7D60
#define pClearGame_3			*(int*)0x710C30
#define pClearGame_4			*(int*)0x788C82C
#define pClearGame_5			*(int*)0x788C830
#define pClearGame_6			*(int*)0x6B7DBC
#define pClearGame_7			*(int*)0x6B7DC0
#define pClearGame_8			*(int*)0x6B7DC4
#define pClearGame_9			*(int*)0x6B7DC8
#define pClearGame_10			*(int*)0x6B7DCC
#define pClearGame_11			*(BYTE*)0x6B7DE1

struct VAngle
{
	float X;
	float Y;
	float Z;
};

enum eObjType
{
	Player		= 1,
	Monster		= 2,
	NPC			= 4,
	None		= 8,
};

#endif