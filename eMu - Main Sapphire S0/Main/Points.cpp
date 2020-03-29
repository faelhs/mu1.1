#include "StdAfx.h"

CPoints gPoints;

DWORD dwPoints;

void CPoints::Load()
{
	gToolKit.SetRange((LPVOID)0x005DEE8E, 6, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005DEE89, this->gObjFix);
}

void CPoints::RecvPoint(PMSG_CHARMAPJOINRESULT * aRecv)
{
	dwPoints = aRecv->iUpPoint;
}

void CPoints::RecvLevel(PMSG_LEVELUP * aRecv)
{
	dwPoints = aRecv->iUpPoint;
}

void CPoints::RecvDownPoint(PMSG_LVPOINTADDRESULT * aRecv)
{
	if(aRecv->ResultType != 0)
	{
		dwPoints--;
	}
}

void __declspec(naked) CPoints::gObjFix()
{
	_asm
	{
		MOV EAX, dwPoints
		PUSH EAX
		PUSH 0x76B1BF0
		PUSH EDX
		MOV EDI, 0x005DEE94
		JMP EDI
	}
}