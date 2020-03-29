#include "StdAfx.h"

CDrawUserInfo gDrawUserInfo;

void CDrawUserInfo::Run()
{
	VAngle Angle;
	// ---
	int PosX, PosY;
	// ---
	for(int i = 0; i < 400; i++)
	{
		DWORD pViewPort = (pViewMonsterStruct + 1060 * i);
		// ---
		if((*(BYTE*)(pViewPort + 0x84) == eObjType::Player))
		{
			Angle.X = *(float*)(pViewPort + 16);
			// ---
			Angle.Y = *(float*)(pViewPort + 20);
			// ---
			Angle.Z = *(float*)(pViewPort + 308) + *(float*)(pViewPort + 24) + 100.0f;
			// ---
			pGetPosFromAngle(&Angle, &PosX, &PosY);
			// ---
			if((pCursorX >= PosX) && ((float)pCursorX <= (float)PosX + 38.0f) && (pCursorY >= PosY - 2) && (pCursorY < PosY + 6))
			{
				this->m_Data.bWindow = true;
			}
			else
			{
				this->m_Data.bWindow = false;
			}
		}
	}
	// ---
	this->InitView();
}

void CDrawUserInfo::InitView()
{
	if(this->m_Data.bWindow)
	{
		pSetBlend(true);
		// ---
		glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
		// ---
		pDrawBarForm(355.0f, 130.0f, 70.0f, 80.0f);
		// ---
		LPCSTR MyString[] = 
		{ 
			"Info Char",
		};
		// ---
		pDrawLegend(0, 0, "");
		glColor3f(1.0, 0.8, 0.0);
		pDrawText(390, 130, MyString[0]);
		// ---
		pDrawLegend(0, 0, "");
	}
}