#include "StdAfx.h"

CHealthBar gHealthBar;

void CHealthBar::Load()
{
	gToolKit.SetOp((LPVOID)0x00596CEA, (LPVOID)this->DrawBar, ASM::CALL);
}

void CHealthBar::Info(PMSG_HEALTH_BAR_RECV * aRecv)
{
	short dwIndex = MAKE_NUMBERW(aRecv->NumberH,aRecv->NumberL);
	// ---
	if(pGetViewPortId(dwIndex) < 400)
	{
		this->m_Data[dwIndex].Class			= aRecv->Class;
		this->m_Data[dwIndex].Live			= (aRecv->Life <= 0.0f) ? FALSE : TRUE; 
		this->m_Data[dwIndex].Life			= aRecv->Life;
		this->m_Data[dwIndex].MaxLife		= aRecv->MaxLife;
		this->m_Data[dwIndex].LifePercent	= ((aRecv->Life / aRecv->MaxLife) * 100.0f);
		this->m_Data[dwIndex].Level			= aRecv->Level;
	}
}

void CHealthBar::DrawBar()
{
	((void(*)())0x00598350)();

	int PosX, PosY, LifeProgress;
	float LifeBarWidth = 38.0f;
	char LifeDisplay[20];

	VAngle Angle;

	for(int n = 0; n < MAX_VIEWPORT_MOBS; n++)
	{
		DWORD pViewPort = (pViewMonsterStruct + 1060 * n);

		if((*(BYTE*)pViewPort != 0) && (*(BYTE*)(pViewPort + 0x84) == eObjType::Monster))
		{
			int LifePercent = 100;

			Angle.X = *(float*)(pViewPort + 16);

			Angle.Y = *(float*)(pViewPort + 20);

			Angle.Z = *(float*)(pViewPort + 308) + *(float*)(pViewPort + 24) + 100.0f;

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			PosX -= (int)floor(LifeBarWidth / (double)2.0);

			if((pCursorX >= PosX) && ((float)pCursorX <= (float)PosX + LifeBarWidth) && (pCursorY >= PosY - 2) && (pCursorY < PosY + 6))
			{
				/*wsprintf(LifeDisplay, "HP : %d0%%", LifePercent);
				pSetTextColor(pTextThis(), RGB(0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX, PosY - 6, LifeDisplay, 0, 0, (LPINT)1, 0);*/
			}

			pSetBlend(true);

			glColor4f(0.0, 0.0, 0.0, 0.5);
			pDrawBarForm((float)(PosX + 1), (float)(PosY + 1), LifeBarWidth + 4.0f, 5.0f);
			pGLSwitchBlend();

			glColor3f(0.2f, 0.0, 0.0);
			pDrawBarForm((float)PosX, (float)PosY, LifeBarWidth + 4.0f, 5.0f);

			glColor3f(0.19607843f, 0.039215688f, 0.0);
			pDrawBarForm((float)(PosX + 2), (float)(PosY + 2), LifeBarWidth, 1.0f);

			if(LifePercent > 10)
			{
				LifeProgress = 10;
			}
			else
			{
				LifeProgress = LifePercent;
			}

			glColor3f(0.98039216f, 0.039215688f, 0.0);

			for(int i = 0; i < LifeProgress; i++)
			{
				pDrawBarForm((float)(i * 4 + PosX + 2), (float)(PosY + 2), 3.0, 2.0);
			}

			pGLSwitch();
		}
		else if((*(BYTE*)pViewPort != 0) && (*(BYTE*)(pViewPort + 0x84) == eObjType::Player))
		{
			Angle.X = *(float*)(pViewPort + 16);

			Angle.Y = *(float*)(pViewPort + 20);

			Angle.Z = *(float*)(pViewPort + 308) + *(float*)(pViewPort + 24) + 100.0f;

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			bool bMouse = false;

			if((pCursorX >= PosX) && ((float)pCursorX <= (float)PosX) && (pCursorY >= PosY - 2) && (pCursorY < PosY + 6))
			{
				bMouse = true;
			}

			if(bMouse)
			{
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
				pDrawLegend(0, 0, ""); // -> Evitar Bugs
			}
		}
	}

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}