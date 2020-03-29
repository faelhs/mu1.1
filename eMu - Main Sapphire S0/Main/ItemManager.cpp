#include "StdAfx.h"

CItemManager gItemManager;

WORD  wItemTitleColor_Pointer;
DWORD dwItemTitleColor_Set;
DWORD dwItemTitleColor_Buff;
WORD  wItemDescriptionText_Pointer;
WORD  wItemDescriptionText_Buff;
DWORD dwJewelUpgradeAllow_Buff;
DWORD dwJewelApplyAllow_Buff;



void CItemManager::Load()
{
	gToolKit.SetRange((LPVOID)0x005A2279, 11, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005A2279, this->LoadTitleColor);
	// ---
	gToolKit.SetRange((LPVOID)0x005B8E6D, 7, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005B8E6D, this->LoadJewelUpgrade); // 006318D2
	// ---
	gToolKit.SetRange((LPVOID)0x005C6CF2, 7, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005C6CF2, this->LoadJewelApply); // 00644F73
	// ---
	gToolKit.SetRange((LPVOID)0x005A50F6, 59, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005A50F6, this->LoadDescription); // 006178B5
	// ---
	gToolKit.SetOp((LPVOID)0x0060ABBB, this->LoadModels, ASM::CALL);
	gToolKit.SetOp((LPVOID)0x0060ABC0, this->LoadTextures, ASM::CALL);
}

void CItemManager::TextColor(char * Text, int Color, int Weight, ...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, Text);
	// ---
	vsprintf(szBuffer, Text, pArguments);
	// ---
	va_end(pArguments);
	// ---
	*(&*(DWORD*)0x785B2A8 /*79F3F04*/ + *(DWORD*)0x788C850 /* 7A25A60*/) = Color;
	*(&*(DWORD*)0x7889F60 /*7A22F00*/+ *(DWORD*)0x788C850) = Weight;
	// ---
	pTextDescription(100 * (*(DWORD*)0x788C850) + 0x0785A110 /* 79F2D68*/, szBuffer);
	// ---
	*(DWORD*)0x788C850 += 1;
}

__declspec(naked) void CItemManager::LoadTitleColor()
{
	dwItemTitleColor_Set = Color::White;
	// ---
	_asm
	{
		MOV wItemTitleColor_Pointer, CX
	}
	// ---
	if(wItemTitleColor_Pointer == ITEM(12, 15))
	{
		dwItemTitleColor_Set = Color::Gold;
	}
	else if(wItemTitleColor_Pointer == ITEM(14, 200) || wItemTitleColor_Pointer == ITEM(14, 205) ||
		    wItemTitleColor_Pointer == ITEM(14, 201) || wItemTitleColor_Pointer == ITEM(14, 202) || 
			wItemTitleColor_Pointer == ITEM(14, 203) || wItemTitleColor_Pointer == ITEM(14, 204))
	{
		dwItemTitleColor_Set = Color::Gold;
	}
	// ---
	_asm
	{
		JE ColorSet
		MOV dwItemTitleColor_Buff, 0x005A2284
		JMP dwItemTitleColor_Buff
		// ---
		ColorSet:
		MOV EDI, dwItemTitleColor_Set
		MOV DWORD PTR SS:[EBP-0x1C], EDI
		// ---
		MOV dwItemTitleColor_Buff, 0x005A2378
		JMP dwItemTitleColor_Buff
	}
}

__declspec(naked) void CItemManager::LoadJewelUpgrade()
{
	_asm
	{
		CMP SI, ITEM(14, 14)
		JE Exit
		// ---
		CMP SI, ITEM(14, 200)
		JE Exit
		// ---
		CMP SI, ITEM(14, 201)
		JE Exit
		// ---
		CMP SI, ITEM(14, 202)
		JE Exit
		// ---
		CMP SI, ITEM(14, 203)
		JE Exit
		// ---
		CMP SI, ITEM(14, 204)
		JE Exit
		// ---
		CMP SI, ITEM(14, 205)
		JE Exit
		// ---
		CMP SI, ITEM(14, 206)
		JE Exit
		// ---
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E74 // 006318D9
		JMP dwJewelUpgradeAllow_Buff
		// ---
		Exit:
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E92 // 00631913
		JMP dwJewelUpgradeAllow_Buff
	}
}

__declspec(naked) void CItemManager::LoadJewelApply()
{
	_asm
	{
		CMP DX, ITEM(14, 14)
		JE Exit
		// ---
		CMP DX, ITEM(14, 200)
		JE Exit
		// ---
		CMP DX, ITEM(14, 201)
		JE Exit
		// ---
		CMP DX, ITEM(14, 202)
		JE Exit
		// ---
		CMP DX, ITEM(14, 203)
		JE Exit
		// ---
		CMP DX, ITEM(14, 204)
		JE Exit
		// ---
		CMP DX, ITEM(14, 205)
		JE Exit
		// ---
		CMP DX, ITEM(14, 206)
		JE Exit
		// ---
		MOV dwJewelApplyAllow_Buff, 0x005C6CF9 // 00644F7A
		JMP dwJewelApplyAllow_Buff
		// ---
		Exit:
		MOV dwJewelApplyAllow_Buff, 0x005C6D04 // 00644F9A
		JMP dwJewelApplyAllow_Buff
	}
}

__declspec(naked) void CItemManager::LoadDescription()
{
	_asm
	{
		MOV wItemDescriptionText_Buff, AX
		// ---
		MOV AX, WORD PTR SS:[ESI] // EBP
		MOV wItemDescriptionText_Pointer, AX
	}
	// ---
	if(wItemDescriptionText_Pointer == ITEM(12, 15))
	{
		gItemManager.TextColor("Para ser usado(a) na Chaos Machine.", Color::White, Font::Normal);
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,200))
	{
		gItemManager.TextColor("Usada para adicionar excelentes opções em itens", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White,Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,201))
	{
		gItemManager.TextColor("Usada para adicionar Level em itens +9 ~ +15", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White,Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,202))
	{
		gItemManager.TextColor("Usada para adicionar Opção +28 em itens", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White, Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,203))
	{
		gItemManager.TextColor("Usada para adicionar Luck em itens", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White, Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,204))
	{
		gItemManager.TextColor("Usada para adicionar skill em Armas e Shields", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White, Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	else if(wItemDescriptionText_Pointer == ITEM(14,205))
	{
		gItemManager.TextColor("Usada para adicionar ancients opções em itens", Color::White, Font::Normal);
		gItemManager.TextColor("Taxa de Sucesso: 100%%", Color::White, Font::Normal);
		gItemManager.TextColor("Custom Jewel", Color::WhiteBlue, Font::Normal);
		
	}
	// ---
	_asm
	{
		MOV AX, wItemDescriptionText_Buff
		// ---
		MOV ESI, 0x005A5131 // 006178F1
		JMP ESI
	}
}

void CItemManager::LoadModels()
{
	pInitModelData();
	// ---
	for(int pSlot = 50; pSlot < 255; pSlot++)
	{
		sprintf_s(gItemManager.szItem, "Sword%d", pSlot + 1);
		pAccessModel(ITEM_ID(0, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szItem, "Axe%d", pSlot + 1);
		pAccessModel(ITEM_ID(1, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szItem, "Mace%d", pSlot + 1);
		pAccessModel(ITEM_ID(2, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szItem, "Spear%d", pSlot + 1);
		pAccessModel(ITEM_ID(3, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szItem, "Staff%d", pSlot + 1);
		pAccessModel(ITEM_ID(5, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szItem, "Shield%d", pSlot + 1);
		pAccessModel(ITEM_ID(6, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		// ---
		sprintf_s(gItemManager.szSet, "HelmMale%d", pSlot + 1);
		pAccessModel(ITEM_ID(7, pSlot), "Data\\Player\\", gItemManager.szSet, -1);
		// ---
		sprintf_s(gItemManager.szSet, "ArmorMale%d", pSlot + 1);
		pAccessModel(ITEM_ID(8, pSlot), "Data\\Player\\", gItemManager.szSet, -1);
		// ---
		sprintf_s(gItemManager.szSet, "PantMale%d", pSlot + 1);
		pAccessModel(ITEM_ID(9, pSlot), "Data\\Player\\", gItemManager.szSet, -1);
		// ---
		sprintf_s(gItemManager.szSet, "GloveMale%d", pSlot + 1);
		pAccessModel(ITEM_ID(10, pSlot), "Data\\Player\\", gItemManager.szSet, -1);
		// ---
		sprintf_s(gItemManager.szSet, "BootMale%d", pSlot + 1);
		pAccessModel(ITEM_ID(11, pSlot), "Data\\Player\\", gItemManager.szSet, -1);
		// ---
		if(pSlot > 50 && pSlot < 60)
		{
			sprintf_s(gItemManager.szItem, "Ring%d", pSlot + 1);
			pAccessModel(ITEM_ID(13, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		}
		// ---
		if(pSlot > 99 && pSlot < 170)
		{
			sprintf_s(gItemManager.szItem, "Wing%d", pSlot + 1);
			pAccessModel(ITEM_ID(12, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		}
		// ---
		if(pSlot > 199 && pSlot < 230)
		{
			sprintf_s(gItemManager.szItem, "Jewel%d", pSlot + 1);
			pAccessModel(ITEM_ID(14, pSlot), "Data\\Item\\", gItemManager.szItem, -1);
		}
	}
}

void CItemManager::LoadTextures()
{
	pInitTextureData();
	// ---
	for(int pSlot = 50; pSlot < 255; pSlot++)
	{
		pOpenTexture(ITEM_ID(0, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(1, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(2, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(3, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(5, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(6, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(7, pSlot), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(8, pSlot), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(9, pSlot), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(10, pSlot), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(11, pSlot), "Player\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(12, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(13, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
		pOpenTexture(ITEM_ID(14, pSlot), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	}
}