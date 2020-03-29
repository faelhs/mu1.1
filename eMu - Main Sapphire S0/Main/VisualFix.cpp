#include "StdAfx.h"

CVisualFix gVisualFix;

void CVisualFix::Load()
{
	this->aIndex = 0;
	this->AttackHP = 0;
	this->Life = 0;
	this->Mana = 0;
	this->AG = 0;
	this->MaxLife = 0;
	this->MaxMana = 0;
	this->MaxAG = 0;
	this->AttackRate = 0;
	this->DamageRate = 0;

	//gToolKit.SetOp((LPVOID)0x004C4375, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C4C01, (LPVOID)this->DrawDamageHP, ASM::CALL); - Miss
	//gToolKit.SetOp((LPVOID)0x004C4D66, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C4DB6, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C4E3F, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C4E8F, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C4EAE, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C83F1, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C8D46, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C8D7B, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C9828, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//gToolKit.SetOp((LPVOID)0x004C985D, (LPVOID)this->DrawDamageHP, ASM::CALL);

 	gToolKit.SetOp((LPVOID)0x0059A086, (LPVOID)this->DrawHp, ASM::CALL);
 	gToolKit.SetOp((LPVOID)0x0059A0AD, (LPVOID)this->DrawMp, ASM::CALL);
 	gToolKit.SetOp((LPVOID)0x00598978, (LPVOID)this->DrawAg, ASM::CALL);
 
 	gToolKit.SetOp((LPVOID)0x00599382, (LPVOID)this->DrawTabHP, ASM::CALL);
 	gToolKit.SetOp((LPVOID)0x0059944A, (LPVOID)this->DrawTabMP, ASM::CALL);
 	gToolKit.SetOp((LPVOID)0x005989D3, (LPVOID)this->DrawTabAG, ASM::CALL);
	
	gToolKit.SetOp((LPVOID)0x005DEE4E, (LPVOID)this->InfoHp, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x005DEB82, (LPVOID)this->InfoMp, ASM::CALL);
}

void CVisualFix::RecvIndex(PMSG_JOINRESULT * lpRecv)
{
	this->aIndex = MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL);
}

void CVisualFix::RecvDamage(PMSG_ATTACKRESULT * lpRecv)
{
	this->AttackHP = lpRecv->iAttackDamage;
	// ----
	if (this->aIndex == MAKE_NUMBERW(lpRecv->NumberH, lpRecv->NumberL))
	{
		this->Life	-= this->AttackHP;
		// ---
		if(this->Life < 0)
		{
			this->Life = 1;
		}
	}
}

void CVisualFix::RecvHP(PMSG_REFILL * lpRecv)
{
	if(lpRecv->IPos == 0xFF)
	{
		this->Life = lpRecv->iLife;
	}
	// ---
	else if(lpRecv->IPos == 0xFE)
	{
		this->MaxLife = lpRecv->iLife;
	}
	// ---
	if(this->Life > this->MaxLife)
	{
		this->Life = this->MaxLife;
	}
}

void CVisualFix::RecvMPAG(PMSG_MANASEND * lpRecv)
{
	if(lpRecv->IPos == 0xFF)
	{
		this->Mana = lpRecv->iMana;
		this->AG = lpRecv->iBP;
	}
	// ---
	else if(lpRecv->IPos == 0xFE)
	{
		this->MaxMana = lpRecv->iMana;
		this->MaxAG = lpRecv->iBP;
	}
	// ---
	if(this->Mana > this->MaxMana)
	{
		this->Mana = this->MaxMana;
	}
}

void CVisualFix::RecvRespawn()
{
	this->Life = this->MaxLife;
}

void CVisualFix::RecvKilledObject(PMSG_DIEPLAYER * Data)
{
	short tIndex =  MAKE_NUMBERW(Data->NumberH, Data->NumberL);
	// ----
	if(this->aIndex == tIndex)
	{
		this->Life = 1;
	}
}

void CVisualFix::DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6)
{
	pDrawDamage(a1, gVisualFix.AttackHP, a3, a4, a5, a6);
}

void CVisualFix::DrawHp(float a1, float a2, int Value, float a4, float a5)
{
	if(gVisualFix.Life >= 65535)
	{
		gVisualFix.Life = 65535;
	}
	// ---
	pDrawBar(a1, a2, gVisualFix.Life, a4, a5);
}

void CVisualFix::DrawMp(float a1, float a2, int Value, float a4, float a5)
{
	if(gVisualFix.Mana >= 65535)
	{
		gVisualFix.Mana = 65535;
	}
	// ---
	pDrawBar(a1, 450.0f, gVisualFix.Mana, a4, a5);
}

void CVisualFix::DrawAg(float a1, float a2, int a3, float a4, float a5)
{
	if(gVisualFix.AG >= 65535)
	{
		gVisualFix.AG = 65535;
	}
	// ---
	pDrawBar(a1, a2, gVisualFix.AG, a4, a5);
}

void CVisualFix::DrawTabHP(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	if(gVisualFix.Life >= 65535)
	{
		gVisualFix.Life = 65535;
	}
	// ---
	if(gVisualFix.MaxLife >= 65535)
	{
		gVisualFix.MaxLife = 65535;
	}
	// ---
	sprintf_s(gVisualFix.LifeTab, "Life: %d/%d", gVisualFix.Life, gVisualFix.MaxLife);
	// ---
	pDrawTab(a1, a2, gVisualFix.LifeTab);
}

void CVisualFix::DrawTabMP(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	if(gVisualFix.Mana >= 65535)
	{
		gVisualFix.Mana = 65535;
	}
	// ---
	if(gVisualFix.MaxMana >= 65535)
	{
		gVisualFix.MaxMana = 65535;
	}
	// ---
	sprintf_s(gVisualFix.ManaTab, "Mana: %d/%d", gVisualFix.Mana, gVisualFix.MaxMana);
	// ---
	pDrawTab(a1, a2, gVisualFix.ManaTab);
}

void CVisualFix::DrawTabAG(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	if(gVisualFix.AG >= 65535)
	{
		gVisualFix.AG = 65535;
	}
	// ---
	if(gVisualFix.MaxAG >= 65535)
	{
		gVisualFix.MaxAG = 65535;
	}
	// ---
	sprintf_s(gVisualFix.AGTab, "AG: %d/%d", gVisualFix.AG, gVisualFix.MaxAG);
	// ---
	pDrawTab(a1, a2, gVisualFix.AGTab);
}

void CVisualFix::InfoHp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	if(gVisualFix.Life >= 65535)
	{
		gVisualFix.Life = 65535;
	}
	// ---
	if(gVisualFix.MaxLife >= 65535)
	{
		gVisualFix.MaxLife = 65535;
	}
	// ---
	sprintf_s(gVisualFix.LifeTab2, "Life: %d/%d", gVisualFix.Life, gVisualFix.MaxLife);
	// ---
	pDrawInfo(a1, a2, gVisualFix.LifeTab2, a4, a5, a6);
}

void CVisualFix::InfoMp(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	if(gVisualFix.Mana >= 65535)
	{
		gVisualFix.Mana = 65535;
	}
	// ---
	if(gVisualFix.MaxMana >= 65535)
	{
		gVisualFix.MaxMana = 65535;
	}
	// ---
	sprintf_s(gVisualFix.ManaTab2, "Mana: %d/%d", gVisualFix.Mana, gVisualFix.MaxMana);
	// ---
	pDrawInfo(a1, a2, gVisualFix.ManaTab2, a4, a5, a6);
}