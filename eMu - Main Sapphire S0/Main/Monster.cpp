#include "StdAfx.h"

CMonster gMonster;

void CMonster::Load()
{
	gToolKit.SetOp((LPVOID)0x004C2EEC, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x004C352C, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x004C3939, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x004D9D1A, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x0050DB29, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x005431D0, this->LoadMonster, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x0059C513, this->LoadMonster, ASM::CALL);
}

int CMonster::LoadMonster(int iObjectId, int iPositionX, int iPositionY, int iKey)
{
	pLoadMonster(iObjectId, iPositionX, iPositionY, iKey);
	// ---
	int iMonster;
	// ---
	switch(iObjectId)
	{
	case 550:
		{
			gMonster.LoadModel(1021);
			// ---
			iMonster = pCreateMonster(iKey, 1021, iPositionX, iPositionY, 0);
		}
		break;
	}
	// ---
	return pMonsterStruct(iMonster, iObjectId);
}

void CMonster::LoadModel(int iObjectId)
{
	switch(iObjectId)
	{
	case 1021:
		{
			pAccessModel(1021, "Data\\Customs\\Npc\\", "Mixer", -1);
			pOpenTexture(1021, "Customs\\Npc\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		}
		break;
	}
}