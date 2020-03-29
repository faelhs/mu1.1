#include "StdAfx.h"

CMiniMap gMiniMap;

int *iMap = (int*)0x006B8D48;

BYTE *btMiniMapShow = (BYTE*)0x004105F6;

void CMiniMap::Load()
{
	gToolKit.SetOp((LPVOID)0x00598FB9, this->LoadMiniMap, ASM::CALL);
}

void CMiniMap::ViewType(int Type)
{
	switch(Type)
	{
	case 1:
		{
			this->bSelect = !this->bSelect;
			// ---
			this->bEnabled = true;
		}
		break;
	case 2:
		{
			this->bSelect = !this->bSelect;
			// ---
			this->bEnabled = false;
		}
		break;
	};
}

void CMiniMap::LoadMiniMap()
{
	char szPatch[64];
	// ---
	char szBuffer[MAX_PATH];
	// ---
	gMiniMap.iLastMap = 100;
	// ---
	if (gMiniMap.iLastMap != *iMap)
	{
		sprintf_s(szPatch, "Customs\\Maps\\map%d.jpg", *iMap + 1);
		// ---
		gInterface.LoadImage(0, szPatch, 0x690);
		// ---
		gMiniMap.bEnabled = true;
		// ---
		gMiniMap.iLastMap = *iMap;
	}
	// ---
	if (gMiniMap.bEnabled == true)
	{
		*btMiniMapShow = 0xEB;
	}
	else
	{
		*btMiniMapShow = 0x74;
	}
	// ---
	pSetBlend(true);
}