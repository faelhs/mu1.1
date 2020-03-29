#ifndef _GLOW_H
#define _GLOW_H

#include "MathLib.h"

#define gObjItemGlow		((void(__cdecl*)(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool Mode)) 0x005F6220)

struct GLOW_DATA_INFO
{
	int iType;
	int iIndex;
	float fRed;
	float fGreen;
	float fBlue;
};

class CGlowManager
{
public:
	void Load();
	static void gObjItemGlowEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode);
	// ---
	int iCount;
	// ---
	GLOW_DATA_INFO m_Data[512];
};

extern CGlowManager gGlowManager;

#endif