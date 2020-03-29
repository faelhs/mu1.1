#include "StdAfx.h"

CWingManager gWingManager;


WORD	WingsAddExcellentStatus_Lv2_Pointer;
DWORD	WingsAddExcellentStatus_Lv2_Buff;
// ---
WORD	WingsAdd28Option_Pointer;
DWORD	WingsAdd28Option_Buff;
// ---

void CWingManager::Load()
{
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x00491F31, ASM::CALL);
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x004BC6D7, ASM::CALL);
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x004C1F87, ASM::CALL);
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x004C2D98, ASM::CALL);
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x004DA13F, ASM::CALL);
	gToolKit.SetHook((LPVOID)this->MakePreviewCharSet, (LPVOID)0x004DBE44, ASM::CALL);
	// ---
	gToolKit.SetRange((LPVOID)0x00541252, 5, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x00541252, this->AddExcellentStatus_Lv2);
	// ---
	//gToolKit.SetRange((LPVOID)0x00541703, 7, ASM::NOP);
	//gToolKit.SetJmp((LPVOID)0x00541703, this->Add28Option);

	//*(BYTE*)(0x00540A98+2) = 0x64;
	//*(BYTE*)(0x00540EC6+2) = 0x64;
	//*(BYTE*)(0x00540FA3+3) = 0x64;
	//  *(BYTE*)(0x0054222B+3) = 0x64;
	//  *(BYTE*)(0x00542292+3) = 0x64;
	//  *(BYTE*)(0x0054236B+4) = 0x64;
	//	 *(BYTE*)(0x00542AF5+3) = 0x64;
	//  *(BYTE*)(0x00542B4F+3) = 0x64;
	//  *(BYTE*)(0x00542C00+3) = 0x64;
	//  *(BYTE*)(0x00542D95+2) = 0x64;
	//  *(BYTE*)(0x0058A06B+2) = 0x64;
	//  *(BYTE*)(0x005A1381+3) = 0x64;
	//  *(BYTE*)(0x005A1917+1) = 0x64;
	//  *(BYTE*)(0x005A2382+3) = 0x64;
	//*(BYTE*)(0x005A3945+3) = 0x64; // Remove Excellent Name
	//	*(BYTE*)(0x005A5317+3) = 0x64;
	//	*(BYTE*)(0x005A5FF8+3) = 0x64;
	//	*(BYTE*)(0x005A7708+2) = 0x64;
	//	*(BYTE*)(0x005A7D77+3) = 0x64;
	//	*(BYTE*)(0x005AB4AA+2) = 0x64;
	//	*(BYTE*)(0x005B1843+2) = 0x64;
	//	*(BYTE*)(0x005B1880+3) = 0x64;
	//	*(BYTE*)(0x005C6D27+2) = 0x64;
	//	*(BYTE*)(0x005CD77D+3) = 0x64;
	//	*(BYTE*)(0x005CDE8A+3) = 0x64;
	//	*(BYTE*)(0x005D049A+2) = 0x64;
	//	*(BYTE*)(0x005EBB71+2) = 0x64;
	//	*(BYTE*)(0x005EBDFC+2) = 0x64;
	// *(BYTE*)(0x0040C278+2) = 0x64; 
	//*(BYTE*)(0x0054176A+2) = 0x64; 
	// *(BYTE*)(0x005AA341+2) = 0x64;
}

void CWingManager::MakePreviewCharSet(int aIndex, BYTE * CharSet, int PreviewObject, int Mode, int Agr5, int Agr6, int Agr7)
{
	pMakePreviewCharSet(aIndex, CharSet, PreviewObject, Mode, Agr5, Agr6, Agr7);
	// ---
	BYTE NewWings = CharSet[16] >> 2;
	// ---
	if(NewWings > 0)
	{
		switch(NewWings)
		{
		case 1:
			*(WORD*)(1060 * aIndex + *(DWORD*)0x7424644 + 744) = ITEM_ID(12, 100);
			break;
		case 2:
			*(WORD*)(1060 * aIndex + *(DWORD*)0x7424644 + 744) = ITEM_ID(12, 101);
			break;
		}
	}
}

void __declspec(naked) CWingManager::AddExcellentStatus_Lv2()
{
	_asm
	{
		MOV WingsAddExcellentStatus_Lv2_Pointer, CX
	}
	// ----
	if(WingsAddExcellentStatus_Lv2_Pointer == ITEM(12, 6) || WingsAddExcellentStatus_Lv2_Pointer >= ITEM(12, 100) && WingsAddExcellentStatus_Lv2_Pointer <= ITEM(12, 120))
	{
		_asm
		{
			mov WingsAddExcellentStatus_Lv2_Buff, 0x0054125D
			jmp WingsAddExcellentStatus_Lv2_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsAddExcellentStatus_Lv2_Buff, 0x00541257
			jmp WingsAddExcellentStatus_Lv2_Buff
		}
	}
}

void __declspec(naked) CWingManager::Add28Option()
{
	_asm
	{
		MOV WingsAdd28Option_Pointer, AX
	}
	// ---
	if( WingsAdd28Option_Pointer == ITEM(12, 6) || WingsAdd28Option_Pointer >= ITEM(12, 100) && WingsAdd28Option_Pointer <= ITEM(12, 130))
	{
		_asm
		{
			MOV WingsAdd28Option_Buff, 0x00541711
			JMP WingsAdd28Option_Buff
		}
	}
	else
	{
		_asm
		{
			MOV WingsAdd28Option_Buff, 0x00541726
			JMP WingsAdd28Option_Buff
		}
	}
}
