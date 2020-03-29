#include "StdAfx.h"

CInterface gInterface;

void CInterface::Load()
{
	gToolKit.SetHook((LPVOID)this->Work, (LPVOID)0x00596E7F, ASM::CALL);
}

void CInterface::Work()
{
	gReconnect.Run();
	gDrawUserInfo.Run();
	// ---
	gInterface.CordRun();
	// ---
	pDrawInterface();
}

void CInterface::CordRun()
{
	char szBuffer[256] = {0};
	// ---
	pSetBlend(true);
	// ---
	sprintf(szBuffer, "Cord X : %d | Cord Y : %d", pCursorX, pCursorY);
	// ---
	pDrawText(0, 0, szBuffer);
}

void CInterface::DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY)
{
	pDrawGUI(ObjectId, X, Y, Width, Height, 0, 0, ScaleX, ScaleY, 1, 1);
}

void CInterface::LoadImage(int Type, char * Folder, int ImageID)
{
	switch(Type)
	{
	case 0:
		{
			pLoadImage(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> JPG
		}
		break;
	case 1:
		{
			pLoadImageTga(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> TGA
		}
		break;
	}
}