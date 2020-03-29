#include "stdafx.h"
#include "ObjCalCharacter.h"
#include "Gamemain.h"
#include "DarkSpirit.h"
#include "SetItemOption.h"
#include "Log.h"

void gObjCalCharacter(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	// ---
	if(lpObj->Type != OBJ_USER)
	{
		return;
	}
	// ---
	CItem* Right  = &lpObj->pInventory[0];
	CItem* Left   = &lpObj->pInventory[1];
	CItem* Gloves = &lpObj->pInventory[5];
	CItem* Wings  = &lpObj->pInventory[7];
	CItem* Helper = &lpObj->pInventory[8];
	CItem* Amulet = &lpObj->pInventory[9];
	CItem* Ring1  = &lpObj->pInventory[10];
	CItem* Ring2  = &lpObj->pInventory[11];
	// ---
	float TotalHP = (lpObj->Life*100)/(lpObj->MaxLife+lpObj->AddLife);
	float TotalMP = (lpObj->Mana*100)/(lpObj->MaxMana+lpObj->AddMana);
	// ---
	lpObj->HaveWeaponInHand = 1;
	// ---
	if(Right->IsItem() == 0 && Left->IsItem() == 0)
	{
	    lpObj->HaveWeaponInHand = 0;
	}
	// ---
	else if(Left->IsItem() == 0 && Right->m_Type == ITEMGET(4,15)) //Arrow
	{
	    lpObj->HaveWeaponInHand = 0;
	}
	// ---
	else if(Right->IsItem() == 0)
	{
	    if(Left->m_Type == ITEMGET(4,7)) //Bolt
		{
		    lpObj->HaveWeaponInHand = 0;
		}
		else if(Left->m_Type >= ITEMGET(6,0) && Left->m_Type < ITEMGET(7,0)) //Shields
		{
		    lpObj->HaveWeaponInHand = 0;
		}
	}
	// ---
	lpObj->AddLife = 0;
	lpObj->AddMana = 0;
	lpObj->MonsterDieGetMoney = 0;
	lpObj->MonsterDieGetLife = 0;
	lpObj->MonsterDieGetMana = 0;
	lpObj->DamageReflect = 0;
	lpObj->DamageMinus = 0;
	lpObj->SkillLongSpearChange = 0;
	// ---
	for(int n = 0; n < 12; n++)
	{
	    if(lpObj->pInventory[n].IsItem() != 0)
		{
		    lpObj->pInventory[n].m_IsValidItem = 1;
		}
	}
	// ---
	bool change = 1;
	// ---
	while(change != 0)
	{
		change = 0;
		lpObj->AddStrength = 0;
		lpObj->AddDexterity = 0;
		lpObj->AddVitality = 0;
		lpObj->AddEnergy = 0;
		lpObj->AddBP = 0;
		lpObj->SetOpAddMaxAttackDamage = 0;
		lpObj->SetOpAddMinAttackDamage = 0;
		lpObj->SetOpAddDamage = 0;
		lpObj->SetOpIncAGValue = 0;
		lpObj->SetOpAddCriticalDamageSuccessRate = 0;
		lpObj->SetOpAddCriticalDamage = 0;
		lpObj->SetOpAddExDamageSuccessRate = 0;
		lpObj->SetOpAddExDamage = 0;
		lpObj->SetOpAddSkillAttack = 0;
		lpObj->SetOpAddAttackDamage = 0;
		lpObj->SetOpAddDefence = 0;
		lpObj->SetOpAddMagicPower = 0;
		lpObj->SetOpAddDefenceRate = 0;
		lpObj->SetOpIgnoreDefense = 0;
		lpObj->SetOpDoubleDamage = 0;
		lpObj->SetOpTwoHandSwordImproveDamage = 0;
		lpObj->SetOpImproveSuccessAttackRate = 0;
		lpObj->SetOpReflectionDamage = 0;
		lpObj->SetOpImproveSheldDefence = 0;
		lpObj->SetOpDecreaseAG = 0;
		lpObj->SetOpImproveItemDropRate = 0;
		lpObj->IsFullSetItem = 0;
		memset(lpObj->m_AddResistance,0,sizeof(lpObj->m_AddResistance));
		// ---
		gObjCalcSetItemStat(lpObj);
		gObjCalcSetItemOption(lpObj);
		// ---
		for(int n = 0; n < 12; n++)
		{
		    if(lpObj->pInventory[n].IsItem() != 0 && lpObj->pInventory[n].m_IsValidItem != 0)
			{
			    if(gObjValidItem(lpObj,&lpObj->pInventory[n],n) != 0)
				{
				    lpObj->pInventory[n].m_IsValidItem = 1;
				}
				else
				{
				    lpObj->pInventory[n].m_IsValidItem = 0;
					change = 1;
				}
			}
		}
	}
	// ---
	int Strength	= lpObj->Strength+lpObj->AddStrength;
	int Dexterity	= lpObj->Dexterity+lpObj->AddDexterity;
	int Vitality	= lpObj->Vitality+lpObj->AddVitality;
	int Energy		= lpObj->Energy+lpObj->AddEnergy;
	// ---
	int AttackPhysicToLog = 0;
	int AttackMagicToLog = 0;
	// ---
	if(lpObj->Class == 1) //DK
	{
		lpObj->m_AttackDamageMinRight = Strength/gServerInfo.m_Character.MinimumDamageDK; //6
		lpObj->m_AttackDamageMaxRight = Strength/gServerInfo.m_Character.MaximumDamageDK; //4

		lpObj->m_AttackDamageMinLeft  = Strength/gServerInfo.m_Character.MinimumDamageDK; //6
		lpObj->m_AttackDamageMaxLeft  = Strength/gServerInfo.m_Character.MaximumDamageDK; //4

		AttackMagicToLog = (lpObj->m_AttackDamageMaxRight);
	}
	// ---
	else if(lpObj->Class == 2) //ELF
	{
		if((Right->m_Type >= ITEMGET(4,0) && Right->m_Type < ITEMGET(5,0) && Right->m_Type != ITEMGET(4,15)) || (Left->m_Type >= ITEMGET(4,0) && Left->m_Type < ITEMGET(5,0) && Left->m_Type != ITEMGET(4,7)))
		{
	        if((Right->IsItem() != 0 && Right->m_IsValidItem == 0) || (Left->IsItem() != 0 && Left->m_IsValidItem == 0)) 
			{
			    //Sem arco ou flechas
				lpObj->m_AttackDamageMinRight = (Dexterity + Strength) / gServerInfo.m_Character.MinimumDamageFE_NoBow; //7
				lpObj->m_AttackDamageMaxRight = (Dexterity + Strength) / gServerInfo.m_Character.MaximumDamageFE_NoBow; //4

				lpObj->m_AttackDamageMinLeft  = (Dexterity + Strength) / gServerInfo.m_Character.MinimumDamageFE_NoBow; //7
				lpObj->m_AttackDamageMaxLeft  = (Dexterity + Strength) / gServerInfo.m_Character.MaximumDamageFE_NoBow; //4
			}
			else
			{
			    //Com arco e flechas
				lpObj->m_AttackDamageMinRight = (Dexterity / gServerInfo.m_Character.MinimumDamageFE_AgiBow) + (Strength / gServerInfo.m_Character.MinimumDamageFE_StrBow); //7 - 14
				lpObj->m_AttackDamageMaxRight = (Dexterity / gServerInfo.m_Character.MaximumDamageFE_AgiBow) + (Strength / gServerInfo.m_Character.MaximumDamageFE_StrBow); //4 - 8

				lpObj->m_AttackDamageMinLeft  = (Dexterity / gServerInfo.m_Character.MinimumDamageFE_AgiBow) + (Strength / gServerInfo.m_Character.MinimumDamageFE_StrBow); //7 - 14
				lpObj->m_AttackDamageMaxLeft  = (Dexterity / gServerInfo.m_Character.MaximumDamageFE_AgiBow) + (Strength / gServerInfo.m_Character.MaximumDamageFE_StrBow); //4 - 8
			}
		}
		else
		{
		    //Sem arco
			lpObj->m_AttackDamageMinRight = (Dexterity+Strength)/gServerInfo.m_Character.MinimumDamageFE_NoBow; //7
			lpObj->m_AttackDamageMaxRight = (Dexterity+Strength)/gServerInfo.m_Character.MaximumDamageFE_NoBow; //4

			lpObj->m_AttackDamageMinLeft  = (Dexterity+Strength)/gServerInfo.m_Character.MinimumDamageFE_NoBow; //7
			lpObj->m_AttackDamageMaxLeft  = (Dexterity+Strength)/gServerInfo.m_Character.MaximumDamageFE_NoBow; //4
		}
	}
	else if(lpObj->Class == 3) //MG
	{
	    lpObj->m_AttackDamageMinRight = (Strength / gServerInfo.m_Character.MinimumDamageMG_Str) + (Energy / gServerInfo.m_Character.MinimumDamageMG_Ene); //6 - 12
		lpObj->m_AttackDamageMaxRight = (Strength / gServerInfo.m_Character.MaximumDamageMG_Str) + (Energy / gServerInfo.m_Character.MaximumDamageMG_Ene); //4 - 8

		lpObj->m_AttackDamageMinLeft  = (Strength / gServerInfo.m_Character.MinimumDamageMG_Str) + (Energy / gServerInfo.m_Character.MinimumDamageMG_Ene); //6 - 12
		lpObj->m_AttackDamageMaxLeft  = (Strength / gServerInfo.m_Character.MaximumDamageMG_Str) + (Energy / gServerInfo.m_Character.MaximumDamageMG_Ene); //4 - 8
	}
	else if(lpObj->Class == 4) //DL
	{
	    lpObj->m_AttackDamageMinRight = (Strength / gServerInfo.m_Character.MinimumDamageDL_Str) + (Energy / gServerInfo.m_Character.MinimumDamageDL_Ene); //7 - 14
		lpObj->m_AttackDamageMaxRight = (Strength / gServerInfo.m_Character.MaximumDamageDL_Str) + (Energy / gServerInfo.m_Character.MaximumDamageDL_Ene); //5 - 10

		lpObj->m_AttackDamageMinLeft  = (Strength / gServerInfo.m_Character.MinimumDamageDL_Str) + (Energy / gServerInfo.m_Character.MinimumDamageDL_Ene); //7 - 14
		lpObj->m_AttackDamageMaxLeft  = (Strength / gServerInfo.m_Character.MaximumDamageDL_Str) + (Energy / gServerInfo.m_Character.MaximumDamageDL_Ene); //5 - 10
	}
	else //DW
	{
	    lpObj->m_AttackDamageMinRight = (Strength / gServerInfo.m_Character.MinimumDamageDW); //8
		lpObj->m_AttackDamageMaxRight = (Strength / gServerInfo.m_Character.MaximumDamageDW); //4

		lpObj->m_AttackDamageMinLeft  = (Strength / gServerInfo.m_Character.MinimumDamageDW); //8
		lpObj->m_AttackDamageMaxLeft  = (Strength / gServerInfo.m_Character.MaximumDamageDW); //4
	}
	// ---
	Wings->PlusSpecial(&lpObj->m_AttackDamageMinRight,80);
	Wings->PlusSpecial(&lpObj->m_AttackDamageMaxRight,80);
	Wings->PlusSpecial(&lpObj->m_AttackDamageMinLeft,80);
	Wings->PlusSpecial(&lpObj->m_AttackDamageMaxLeft,80);
	// ---
	int AddLeadership = 0;
	// ---
	if(Wings->IsItem() != 0 && Wings->m_IsValidItem != 0)
	{
	    AddLeadership += lpObj->pInventory[7].m_Leadership;
	}
	// ---
	lpObj->m_CriticalDamage = 0;
	lpObj->m_ExcelentDamage = 0;
	// ---
	if(lpObj->Class == 3) //MG
	{
		lpObj->m_MagicDamageMin = Energy/gServerInfo.m_Character.MinimumMagicDamageMG; //9
		lpObj->m_MagicDamageMax = Energy/gServerInfo.m_Character.MaximumMagicDamageMG; //4
	}
	else if(lpObj->Class == 0) //DW
	{
		lpObj->m_MagicDamageMin = Energy / gServerInfo.m_Character.MinimumMagicDamageDW; //9
		lpObj->m_MagicDamageMax = Energy / gServerInfo.m_Character.MaximumMagicDamageDW; //4
	}
	else if(lpObj->Class == 1) //DK
	{
		lpObj->m_MagicDamageMin = Energy / gServerInfo.m_Character.MinimumMagicDamageDK; //9
		lpObj->m_MagicDamageMax = Energy / gServerInfo.m_Character.MaximumMagicDamageDK; //4
	}
	else if(lpObj->Class == 2) //FE
	{
		lpObj->m_MagicDamageMin = Energy / gServerInfo.m_Character.MinimumMagicDamageFE; //9
		lpObj->m_MagicDamageMax = Energy / gServerInfo.m_Character.MaximumMagicDamageFE; //4
	}
	else //DL
	{
		lpObj->m_MagicDamageMin = Energy / gServerInfo.m_Character.MinimumMagicDamageDL; //9
		lpObj->m_MagicDamageMax = Energy / gServerInfo.m_Character.MaximumMagicDamageDL; //4
	}
	// ---
	lpObj->pInventory[0].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[1].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[2].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[3].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[4].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[5].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[6].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_CriticalDamage,84);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_MagicDamageMin,81);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_MagicDamageMax,81);
	// ---
	if(Right->IsItem() != 0)
	{
	    if(Right->m_IsValidItem != 0)
		{
			if(Right->m_Type >= ITEMGET(5,0) && Right->m_Type <= ITEMGET(6,0))
			{
			    lpObj->m_AttackDamageMinRight += Right->m_DamageMin/2;
				lpObj->m_AttackDamageMaxRight += Right->m_DamageMax/2;
			}
			else
			{
			    lpObj->m_AttackDamageMinRight += Right->m_DamageMin;
				lpObj->m_AttackDamageMaxRight += Right->m_DamageMax;
			}
		}
		// ---
		if(Right->m_SkillChange != 0)
		{
		    lpObj->SkillLongSpearChange = 1;
		}
		// ---
		if(Right->m_Type == ITEMGET(0,21) || Right->m_Type == ITEMGET(0,23) || Right->m_Type == ITEMGET(0,25) || Right->m_Type == ITEMGET(0,28) || Right->m_Type == ITEMGET(0,31)) 
		{
		    Right->PlusSpecial(&lpObj->m_MagicDamageMin,80);
			Right->PlusSpecial(&lpObj->m_MagicDamageMax,80);
		}
		else
		{
		    Right->PlusSpecial(&lpObj->m_MagicDamageMin,81);
			Right->PlusSpecial(&lpObj->m_MagicDamageMax,81);
		}
		// ---
		Right->PlusSpecial(&lpObj->m_AttackDamageMinRight,80);
		Right->PlusSpecial(&lpObj->m_AttackDamageMaxRight,80);
	}
	// ---
	if(Left->IsItem() != 0)
	{
	    if(Left->m_IsValidItem != 0)
		{
		    lpObj->m_AttackDamageMinLeft += Left->m_DamageMin;
			lpObj->m_AttackDamageMaxLeft += Left->m_DamageMax;
		}
		// ---
		Left->PlusSpecial(&lpObj->m_AttackDamageMinLeft,80);
		Left->PlusSpecial(&lpObj->m_AttackDamageMaxLeft,80);
	}
	// ---
	lpObj->m_AttackRating = (Strength+Dexterity)/2;
	// ---
	lpObj->m_AttackRating += lpObj->pInventory[5].ItemDefense();
	// ---
	if(lpObj->Class == 1) //DK
	{
	    lpObj->m_AttackSpeed = Dexterity/gServerInfo.m_Character.AttackSpeedDK; // 15
		lpObj->m_MagicSpeed  = Dexterity/gServerInfo.m_Character.MagicSpeedDK; // 20
	}
	else if(lpObj->Class == 2) // Elf
	{
		lpObj->m_AttackSpeed = Dexterity/gServerInfo.m_Character.AttackSpeedFE; // 50
		lpObj->m_MagicSpeed  = Dexterity/gServerInfo.m_Character.MagicSpeedFE; // 50
	}
	else if(lpObj->Class == 3) // MG
	{
		lpObj->m_AttackSpeed = Dexterity/gServerInfo.m_Character.AttackSpeedMG; // 15
		lpObj->m_MagicSpeed  = Dexterity/gServerInfo.m_Character.MagicSpeedMG; // 20
	}
	else if(lpObj->Class == 4) //DL
	{
	    lpObj->m_AttackSpeed = Dexterity/gServerInfo.m_Character.AttackSpeedDL; // 10
		lpObj->m_MagicSpeed  = Dexterity/gServerInfo.m_Character.MagicSpeedDL; // 10
	}
	else //DW
	{
	    lpObj->m_AttackSpeed = Dexterity/gServerInfo.m_Character.AttackSpeedDW; // 20
		lpObj->m_MagicSpeed  = Dexterity/gServerInfo.m_Character.MagicSpeedDW; // 10
	}
	// ---
    bool RightItem = 0;
	// ---
	if(Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(6,0) && Right->m_Type != ITEMGET(4,7) && Right->m_Type != ITEMGET(4,15))
	{
	    if(Right->m_IsValidItem != 0)
		{
            RightItem = 1;
		}
	}
	// ---
	bool LeftItem = 0;
	// ---
	if(Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(6,0) && Left->m_Type != ITEMGET(4,7) && Left->m_Type != ITEMGET(4,15))
	{
	    if(Left->m_IsValidItem != 0)
		{
		    LeftItem = 1;
		}
	}
	// ---
	if(RightItem != 0 && LeftItem != 0)
	{
	    lpObj->m_AttackSpeed += (Right->m_AttackSpeed+Left->m_AttackSpeed)/2;
		lpObj->m_MagicSpeed  += (Right->m_AttackSpeed+Left->m_AttackSpeed)/2;
	}
	// ---
	else if(RightItem != 0)
	{
	    lpObj->m_AttackSpeed += Right->m_AttackSpeed;
		lpObj->m_MagicSpeed  += Right->m_AttackSpeed;
	}
	// ---
	else if(LeftItem != 0)
	{
	    lpObj->m_AttackSpeed += Left->m_AttackSpeed;
		lpObj->m_MagicSpeed  += Left->m_AttackSpeed;
	}
	// ---
	if(Gloves->IsItem() != 0 && Gloves->m_IsValidItem != 0)
	{
	    lpObj->m_AttackSpeed += Gloves->m_AttackSpeed;
		lpObj->m_MagicSpeed  += Gloves->m_AttackSpeed;
	}
	// ---
	if(Helper->IsItem() != 0 && Helper->m_IsValidItem != 0)
	{
	    lpObj->m_AttackSpeed += Helper->m_AttackSpeed;
	    lpObj->m_MagicSpeed  += Helper->m_AttackSpeed;
	}
	// ---
	if(Amulet->IsItem() != 0 && Amulet->m_IsValidItem != 0)
	{
	    lpObj->m_AttackSpeed += Amulet->m_AttackSpeed;
		lpObj->m_MagicSpeed  += Amulet->m_AttackSpeed;
	}
	// ---
	bool RingOption[4] = {0,0,0,0};
	// ---
	for(int n=0;n < 2;n++)
	{
	    CItem* Ring = &lpObj->pInventory[10+n];
		// ---
		if(Ring->IsItem() == 0 || Ring->m_Durability == 0.0f)
		{
		    continue;
		}
		// ---
		if(Ring->m_Type == ITEMGET(13,20) && Ring->m_Level == 0)
		{
		    RingOption[0] = 1;
		}
	}
	// ---
    if(RingOption[0] == 1)
	{
        lpObj->m_AttackDamageMinRight += (lpObj->m_AttackDamageMinRight*10)/100;
		lpObj->m_AttackDamageMaxRight += (lpObj->m_AttackDamageMaxRight*10)/100;
		// ---
		lpObj->m_AttackDamageMinLeft  += (lpObj->m_AttackDamageMinLeft*10)/100;
		lpObj->m_AttackDamageMaxLeft  += (lpObj->m_AttackDamageMaxLeft*10)/100;
		// ---
		lpObj->m_MagicDamageMin += (lpObj->m_MagicDamageMin*10)/100;
		lpObj->m_MagicDamageMax += (lpObj->m_MagicDamageMax*10)/100;
		// ---
		lpObj->m_AttackSpeed += 10;
	    lpObj->m_MagicSpeed  += 10;
	}
	// ---
	if(RingOption[2] == 1)
	{
        lpObj->m_AttackDamageMinRight += 20;
		lpObj->m_AttackDamageMaxRight += 20;
		lpObj->m_AttackDamageMinLeft  += 20;
		lpObj->m_AttackDamageMaxLeft  += 20;
		lpObj->m_MagicDamageMin += 20;
		lpObj->m_MagicDamageMax += 20;
	}
	// ---
	if(RingOption[3] == 1)
	{
	    lpObj->m_AddResistance[0] = 255;
		lpObj->m_AddResistance[1] = 255;
		lpObj->m_AddResistance[2] = 255;
		lpObj->m_AddResistance[3] = 255;
		lpObj->m_AddResistance[4] = 255;
		lpObj->m_AddResistance[5] = 255;
		lpObj->m_AddResistance[6] = 255;
	}
	// ---
	if(lpObj->Class == 1) //DK
	{
	    lpObj->m_SuccessfulBlocking = Dexterity/gServerInfo.m_Character.BlockDK;
	}
	else if(lpObj->Class == 2) //Elf
	{
	    lpObj->m_SuccessfulBlocking = Dexterity/gServerInfo.m_Character.BlockFE;
	}
	else if(lpObj->Class == 3) //MG
	{
	    lpObj->m_SuccessfulBlocking = Dexterity/gServerInfo.m_Character.BlockMG;
	}
	else if(lpObj->Class == 4) // DL
	{
	    lpObj->m_SuccessfulBlocking = Dexterity/gServerInfo.m_Character.BlockDL;
	}
	else //DW
	{
	    lpObj->m_SuccessfulBlocking = Dexterity/gServerInfo.m_Character.BlockDW;
	}
	// ---
	if(Left->IsItem() != 0 && Left->m_IsValidItem != 0)
	{
	    lpObj->m_SuccessfulBlocking += Left->m_SuccessfulBlocking;
        Left->PlusSpecial(&lpObj->m_SuccessfulBlocking,82);
	}
	// ---
	bool FullItemSet	= 1;
	// ---
	int LastItemIndex	= -1;
	// ---
	for(int n=2;n <= 6;n++)
	{
	    if(n == 2 && lpObj->Class == 3) //MG
		{
		    continue;
		}
		// ---
		if(lpObj->pInventory[n].IsItem() == 0 || lpObj->pInventory[n].m_IsValidItem == 0 || (LastItemIndex >= 0 && lpObj->pInventory[n].m_Type != LastItemIndex))
		{
		    FullItemSet = 0;
			break;
		}
		// ---
	    LastItemIndex = lpObj->pInventory[n].m_Type; 
	}
	// ---
	int Level11Count = 0;
	int Level10Count = 0;
	int Level12Count = 0;
	int Level13Count = 0;
	int Level14Count = 0;
	int Level15Count = 0;
	// ---
	if(FullItemSet != 0)
	{
        for(int n=2;n <= 6;n++)
		{
			if(n == 2 && lpObj->Class == 3) //MG
			{
			    Level15Count++;
				continue;
			}
			// ---
			if(lpObj->pInventory[n].m_Level == 10)
			{
			    Level10Count++;
			}
			else if(lpObj->pInventory[n].m_Level == 11)
			{
			    Level11Count++;
			}
			else if(lpObj->pInventory[n].m_Level == 12)
			{
			    Level12Count++;
			}
			else if(lpObj->pInventory[n].m_Level == 13)
			{
			    Level13Count++;
			}
			else if(lpObj->pInventory[n].m_Level == 14)
			{
			    Level14Count++;
			}
			else if(lpObj->pInventory[n].m_Level == 15)
			{
			    Level15Count++;
			}
		}
		// ---
	    lpObj->m_SuccessfulBlocking += lpObj->m_SuccessfulBlocking/10;
	}
	// ---
	if(lpObj->Class == 1) //DK
	{
	    lpObj->m_Defense = Dexterity/gServerInfo.m_Character.DefenseDK; //3
	}
	else if(lpObj->Class == 2) //Elf
	{
	    lpObj->m_Defense = Dexterity/gServerInfo.m_Character.DefenseFE; //10
	}
	else if(lpObj->Class == 4) //DL
	{
	    lpObj->m_Defense = Dexterity/gServerInfo.m_Character.DefenseDL; //7
	}
	else if(lpObj->Class == 3) //MG
	{
	    lpObj->m_Defense = Dexterity/gServerInfo.m_Character.DefenseMG; //4
	}
	else //DW
	{
	    lpObj->m_Defense = Dexterity/gServerInfo.m_Character.DefenseDW; //4
	}
	// ---
	lpObj->m_Defense += lpObj->pInventory[1].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[2].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[3].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[4].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[5].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[6].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[7].ItemDefense();
	// ---
	if(Helper->IsItem() != 0 && Helper->m_Type == ITEMGET(13,4) && Helper->m_Durability > 0.0f) //Dark Horse
	{
	    lpObj->m_Defense += (Dexterity/20)+(Helper->m_PetItem_Level*2)+5;
	}
	// ---
	if(FullItemSet != 0 && (Level15Count+Level14Count+Level13Count+Level12Count+Level11Count+Level10Count) >= 5)
	{
		if(Level15Count == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*30)/100;
		}
		else if(Level14Count == 5 || (Level14Count+Level15Count) == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*25)/100;
		}
	    else if(Level13Count == 5 || (Level13Count+Level14Count+Level15Count) == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*20)/100;
		}
		else if(Level12Count == 5 || (Level12Count+Level13Count+Level14Count+Level15Count) == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*15)/100;
		}
		else if(Level11Count == 5 || (Level11Count+Level12Count+Level13Count+Level14Count+Level15Count) == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*10)/100;
		}
		else if(Level10Count == 5 || (Level10Count+Level11Count+Level12Count+Level13Count+Level14Count+Level15Count) == 5)
		{
		    lpObj->m_Defense += (lpObj->m_Defense*5)/100;
		}
	}
	// ---
	if(RingOption[1] == 1)
	{
	    lpObj->m_Defense += (lpObj->m_Defense*10)/100;
		lpObj->AddLife += lpObj->Level;
	}   
	// ---
	lpObj->m_Defense = (lpObj->m_Defense*10)/20;
	// ---
	if(Helper->IsItem() != 0 && Helper->m_Type == ITEMGET(13,37) && (Helper->m_NewOption & 4) != 0)
	{
	    lpObj->m_AttackDamageMinRight += lpObj->Level/12;
		lpObj->m_AttackDamageMaxRight += lpObj->Level/12;
		// ---
		lpObj->m_AttackDamageMinLeft  += lpObj->Level/12;
		lpObj->m_AttackDamageMaxLeft  += lpObj->Level/12;
		// ---
		lpObj->m_MagicDamageMin += lpObj->Level/25;
		lpObj->m_MagicDamageMax += lpObj->Level/25;
	    // ---
		lpObj->AddLife += lpObj->Level/2;
	    lpObj->AddMana += lpObj->Level/2;
	}
	// ---
	int AddLife = 0;
	int AddMana = 0;
	// ---
	Wings->PlusSpecial(&AddLife,100);
	// ---
	Wings->PlusSpecial(&AddMana,101);
	// ---
	Wings->PlusSpecial(&AddLeadership,105);
	// ---
	lpObj->AddLeadership	= AddLeadership;
	// ---
	lpObj->AddLife			+= AddLife;
	// ---
	lpObj->AddMana			+= AddMana;
	// ---
	if(Helper->IsItem() != 0 && Helper->m_Type == ITEMGET(13,3))
	{
	    Helper->PlusSpecial(&lpObj->AddBP,103);
	}
	// ---
	Amulet->PlusSpecialPercentEx(&lpObj->AddBP,lpObj->MaxBP,173);
	// ---
	Ring1->PlusSpecialPercentEx(&lpObj->AddMana,lpObj->MaxMana,172);
	Ring2->PlusSpecialPercentEx(&lpObj->AddMana,lpObj->MaxMana,172);
	// ---
    #define GET_MAX_RESISTANCE(x,y,z) (((((x) > (y))?(x):(y)) > (z))?(((x) > (y))?(x):(y)):(z))	
	// ---
	lpObj->m_Resistance[0] = GET_MAX_RESISTANCE(Amulet->m_Resistance[0],Ring1->m_Resistance[0],Ring2->m_Resistance[0]);
	lpObj->m_Resistance[1] = GET_MAX_RESISTANCE(Amulet->m_Resistance[1],Ring1->m_Resistance[1],Ring2->m_Resistance[1]);
	lpObj->m_Resistance[2] = GET_MAX_RESISTANCE(Amulet->m_Resistance[2],Ring1->m_Resistance[2],Ring2->m_Resistance[2]);
	lpObj->m_Resistance[3] = GET_MAX_RESISTANCE(Amulet->m_Resistance[3],Ring1->m_Resistance[3],Ring2->m_Resistance[3]);
	lpObj->m_Resistance[4] = GET_MAX_RESISTANCE(Amulet->m_Resistance[4],Ring1->m_Resistance[4],Ring2->m_Resistance[4]);
	lpObj->m_Resistance[5] = GET_MAX_RESISTANCE(Amulet->m_Resistance[5],Ring1->m_Resistance[5],Ring2->m_Resistance[5]);
	lpObj->m_Resistance[6] = GET_MAX_RESISTANCE(Amulet->m_Resistance[6],Ring1->m_Resistance[6],Ring2->m_Resistance[6]);
	// ---
	gObjExtItemApply(lpObj);
	gObjSetItemApply(lpObj);
	// ---
	gObjNextExpCal(lpObj);
	// ---
	if((Right->m_Type >= ITEMGET(4,8) && Right->m_Type <= ITEMGET(4,14)) || Right->m_Type == ITEMGET(14,16) || Right->m_Type == ITEMGET(4,18) || Right->m_Type == ITEMGET(4,19))
	{
		if(Left->m_Type == ITEMGET(4,7) && Left->m_Level > 0)
		{
		    lpObj->m_AttackDamageMinRight += ((lpObj->m_AttackDamageMinRight*((Left->m_Level*2)+1))/100)+1;
			lpObj->m_AttackDamageMaxRight += ((lpObj->m_AttackDamageMinRight*((Left->m_Level*2)+1))/100)+1;
		}
	}
	// ---
	else if((Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,6)) || Left->m_Type == ITEMGET(4,17) || (Left->m_Type >= ITEMGET(4,20) && Left->m_Type <= ITEMGET(4,24)))
	{
	    if(Right->m_Type == ITEMGET(4,15) && Right->m_Level > 0)
		{
		    lpObj->m_AttackDamageMinLeft += ((lpObj->m_AttackDamageMinLeft*((Right->m_Level*2)+1))/100)+1;
			lpObj->m_AttackDamageMaxLeft += ((lpObj->m_AttackDamageMinLeft*((Right->m_Level*2)+1))/100)+1;
		}
	}
	// ---
	if(lpObj->Class == CLASS_KNIGHT || lpObj->Class == CLASS_MAGUMSA || lpObj->Class == CLASS_DARKLORD)
	{
        if(Right->IsItem() != 0 && Left->IsItem() != 0)
		{
		    if(Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(4,0) && Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(4,0))
			{
			    lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight*55)/100;
				lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight*55)/100;
				lpObj->m_AttackDamageMinLeft  = (lpObj->m_AttackDamageMinLeft*55)/100;
			    lpObj->m_AttackDamageMaxLeft  = (lpObj->m_AttackDamageMaxLeft*55)/100;
			}
		}
	}
	// ---
	float MaxLife = lpObj->MaxLife+lpObj->AddLife;
	// ---
	lpObj->Life = (MaxLife*TotalHP)/100;
	// ---
	if(lpObj->Life > MaxLife)
	{
	    lpObj->Life = MaxLife;
	}
	// ---
	GCReFillSend(lpObj->m_Index, MaxLife, 0xFE, 0);
	GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0);
	// ---
	float MaxMana = lpObj->MaxMana+lpObj->AddMana;
	// ---
	lpObj->Mana = (MaxMana*TotalMP)/100;
	// ---
	if(lpObj->Mana > MaxMana)
	{
	    lpObj->Mana = MaxMana;
	}
	// ---
	float MaxBP = lpObj->MaxBP+lpObj->AddBP;
	// ---
	if(lpObj->BP > MaxBP)
	{
	    lpObj->BP = MaxBP;
	}
	// ---
	GCManaSend(aIndex, MaxMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
	GCManaSend(aIndex, lpObj->MaxMana + lpObj->AddMana, 0xFF, 0, lpObj->MaxBP + lpObj->AddBP);
	// ---
	gServerInfo.SendMain(aIndex);
}

void gObjExtItemApply(LPOBJ lpObj)
{

	int n;
	int i;
	int max_count = 0;
	int temp_n[3] = {0, 1, 9};
	int temp_n2[10] = {2, 3, 4, 5, 6, 7, 8, 10, 11, 1};
	int maxn2_loop = 9;

	for ( i=0;i<3;i++ )
	{
		n = temp_n[i];

		if ( lpObj->pInventory[n].m_Type >= ITEMGET(6, 0) && lpObj->pInventory[n].m_Type < ITEMGET(7, 0) )
			continue;

		if ( lpObj->pInventory[n].IsItem() == TRUE )
		{
			if ( lpObj->pInventory[n].m_Durability != 0.0f )
			{
				if ( lpObj->pInventory[n].m_IsValidItem == true )
				{
					if ( lpObj->pInventory[n].IsExtAttackRate() )
					{
						if ( ( lpObj->pInventory[n].m_Type >= ITEMGET(5, 0) && lpObj->pInventory[n].m_Type < ITEMGET(6, 0) ) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,12) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,25) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,27) )
						{
							lpObj->m_MagicDamageMax += lpObj->Level / 20;
							lpObj->m_MagicDamageMin += lpObj->Level / 20;
						}
						else 
						{
							if ( n == 0 || n == 9 )
							{
								lpObj->m_AttackDamageMinRight += lpObj->Level / 20;
								lpObj->m_AttackDamageMaxRight += lpObj->Level / 20;
							}
							
							if ( n == 1 || n == 9 )
							{
								lpObj->m_AttackDamageMinLeft += lpObj->Level / 20;
								lpObj->m_AttackDamageMaxLeft += lpObj->Level / 20;
							}
						}
					}

					if ( lpObj->pInventory[n].IsExtAttackRate2() )
					{
						if ( ( lpObj->pInventory[n].m_Type >= ITEMGET(5, 0) && lpObj->pInventory[n].m_Type < ITEMGET(6, 0) ) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,12) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,25) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,27) )
						{
							lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * lpObj->pInventory[n].IsExtAttackRate2() / 100;
						}
						else 
						{
							if ( n == 0 || n == 9 )
							{
								lpObj->m_AttackDamageMinRight += lpObj->m_AttackDamageMinRight * lpObj->pInventory[n].IsExtAttackRate2() / 100;
								lpObj->m_AttackDamageMaxRight += lpObj->m_AttackDamageMaxRight * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							}
							
							if ( n == 1 || n == 9 )
							{
								lpObj->m_AttackDamageMinLeft += lpObj->m_AttackDamageMinLeft * lpObj->pInventory[n].IsExtAttackRate2() / 100;
								lpObj->m_AttackDamageMaxLeft += lpObj->m_AttackDamageMaxLeft * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							}
						}
					}

					lpObj->m_ExcelentDamage += lpObj->pInventory[n].IsExtExcellentDamage();
					lpObj->m_AttackSpeed += lpObj->pInventory[n].IsExtAttackSpeed();
					lpObj->m_MagicSpeed += lpObj->pInventory[n].IsExtAttackSpeed();
					lpObj->MonsterDieGetLife += lpObj->pInventory[n].IsExtMonsterDieLife();
					lpObj->MonsterDieGetMana += lpObj->pInventory[n].IsExtMonsterDieMana();
				}
			}
		}
	}
		
	if ( lpObj->pInventory[1].IsItem() == TRUE )
	{
		if ( lpObj->pInventory[1].m_Type >= ITEMGET(6, 0) && lpObj->pInventory[1].m_Type <= ITEMGET(6, 16) )
		{
			maxn2_loop = 10;
		}
	}

	for ( i=0;i<maxn2_loop;i++)
	{
		n = temp_n2[i];

		if ( max_count < 8 )
		{
			if ( lpObj->pInventory[n].IsItem() == TRUE &&
				 lpObj->pInventory[n].IsExtItem() &&
				 lpObj->pInventory[n].m_Durability != 0.0f &&
				 lpObj->pInventory[n].m_IsValidItem == true )
			{
				if ( n != 7 )	// #warning this will unselect ONLY wings
				{
					lpObj->AddLife += (short)(lpObj->MaxLife * lpObj->pInventory[n].IsExtLifeAdd()  / 100.0f);	// #stat
					lpObj->AddMana += (short)(lpObj->MaxMana * lpObj->pInventory[n].IsExtManaAdd() / 100.0f);	// #stat
					lpObj->m_SuccessfulBlocking += lpObj->m_SuccessfulBlocking * lpObj->pInventory[n].IsExtDefenseSuccessfull() / 100;
					lpObj->MonsterDieGetMoney += lpObj->pInventory[n].IsExtMonsterMoney();
					lpObj->DamageMinus += lpObj->pInventory[n].IsExtDamageMinus();
					lpObj->DamageReflect += lpObj->pInventory[n].IsExtDamageReflect();
					max_count++;
				}
			}
		}
	}

	lpObj->AddLife += lpObj->m_SkillAddLife;
}



void gObjCalcSetItemStat(LPOBJ lpObj)
{
	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		if ( lpObj->pInventory[i].IsSetItem() && lpObj->pInventory[i].m_IsValidItem && lpObj->pInventory[i].m_Durability != 0.0f )
		{
			int AddStatType = lpObj->pInventory[i].GetAddStatType();

			switch ( AddStatType )
			{
				case 1:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddStrength, 196);
					break;
				case 2:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddDexterity, 197);
					break;
				case 3:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddEnergy, 198);
					break;
				case 4:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddVitality, 199);
					break;
			}
		}
	}
}





void gObjGetSetItemOption(LPOBJ lpObj, LPBYTE pSetOptionTable , LPBYTE pSetOptionCountTable , int * pSetOptionCount)
{
	*pSetOptionCount = 0;
	int RightSetOptionIndex = -1;
	int RightRingSetOptionIndex = -1;

	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		int iSetItemType = lpObj->pInventory[i].IsSetItem();

		if ( iSetItemType )
		{
			if ( lpObj->pInventory[i].m_IsValidItem )
			{
				int iSetItemOption = gSetItemOption.GetOptionTableIndex(lpObj->pInventory[i].m_Type, iSetItemType );

				if ( iSetItemOption != -1 )
				{
					if ( i == 0 )
					{
						RightSetOptionIndex = iSetItemOption;
					}
					else if ( i == 1  )
					{
						if (  RightSetOptionIndex == iSetItemOption )
						{
							if ( lpObj->pInventory[0].GetWeaponType() == lpObj->pInventory[1].GetWeaponType() && lpObj->pInventory[0].IsSetItem() )
							{
								LogAdd(LOG_BLACK, "양손에 같은 세트가 적용되었다 무시...");
								continue;
							}
						}
					}
					
					if ( i == 10 )
					{
						RightRingSetOptionIndex = iSetItemOption;
					}
					else if ( i == 11   )
					{
						if ( lpObj->pInventory[10].m_Type == lpObj->pInventory[11].m_Type && lpObj->pInventory[10].IsSetItem() )
						{
							LogAdd(LOG_BLACK, "반지에 같은 세트가 적용되었다 무시...");
							continue;
						}
					}

					BOOL bFound = FALSE;

					for ( int n=0;n<*pSetOptionCount;n++)
					{
						if ( pSetOptionTable[n] == iSetItemOption )
						{
							pSetOptionCountTable[n]++;
							bFound = TRUE;

							LogAdd(LOG_BLACK, "옵션 찾았다 %s, Count = %d",
								gSetItemOption.GetSetOptionName(iSetItemOption), pSetOptionCountTable[n]);

							break;
						}
					}

					if ( bFound == FALSE )
					{
						pSetOptionTable[*pSetOptionCount] = iSetItemOption;
						pSetOptionCountTable[*pSetOptionCount]++;

						LogAdd(LOG_BLACK, "옵션 찾았다 %s, Count = %d",
							gSetItemOption.GetSetOptionName(iSetItemOption), pSetOptionCountTable[*pSetOptionCount]);

						*pSetOptionCount += 1;
					}
				}
			}
		}
	}
}
void gObjCalcSetItemOption(LPOBJ lpObj)
{
	BYTE SetOptionTable[29];
	BYTE SetOptionCountTable[29];
	int SetOptionCount = 0;
	int op1;
	int op2;
	int op3;
	int op4;
	int op5;
	int opvalue1;
	int opvalue2;
	int opvalue3;
	int opvalue4;
	int opvalue5;

	memset(SetOptionTable, 0, sizeof(SetOptionTable));
	memset(SetOptionCountTable, 0, sizeof(SetOptionCountTable));
	gObjGetSetItemOption(lpObj, SetOptionTable, SetOptionCountTable, &SetOptionCount);

	for ( int optioncount=0;optioncount<SetOptionCount;optioncount++)
	{
		int OptionTableIndex = SetOptionTable[optioncount];
		int OptionTableCount = SetOptionCountTable[optioncount];

		if ( OptionTableCount >= 2 )
		{
			gSetItemOption.IsRequireClass(OptionTableIndex, lpObj->Class, lpObj->ChangeUP);

			for ( int tablecnt=0;tablecnt<(OptionTableCount-1);tablecnt++)
			{
				if ( gSetItemOption.GetSetOption(OptionTableIndex, tablecnt,
					op1, op2, opvalue1, opvalue2, lpObj->Class, lpObj->ChangeUP) )
				{
					gObjSetItemStatPlusSpecial(lpObj, op1, opvalue1);
					gObjSetItemStatPlusSpecial(lpObj, op2, opvalue2);
				}
			}

			if ( gSetItemOption.GetMaxSetOptionCount(OptionTableIndex) < OptionTableCount )
			{
				lpObj->IsFullSetItem = true;
				LogAdd(LOG_RED,  "풀옵션 적용");

				gSetItemOption.GetGetFullSetOption(OptionTableIndex,
					op1, op2, op3, op4, op5,
					opvalue1, opvalue2, opvalue3, opvalue4, opvalue5,
					lpObj->Class, lpObj->ChangeUP);

				gObjSetItemStatPlusSpecial(lpObj, op1, opvalue1);
				gObjSetItemStatPlusSpecial(lpObj, op2, opvalue2);
				gObjSetItemStatPlusSpecial(lpObj, op3, opvalue3);
				gObjSetItemStatPlusSpecial(lpObj, op4, opvalue4);
				gObjSetItemStatPlusSpecial(lpObj, op5, opvalue5);
			}		
		}
	}

	for (int optioncount=0;optioncount<SetOptionCount;optioncount++)
	{
		int OptionTableIndex = SetOptionTable[optioncount];
		int OptionTableCount = SetOptionCountTable[optioncount];

		if ( OptionTableCount >= 2 )
		{
			LogAdd(LOG_BLACK, "[%s][%s] 세트 %s옵션 적용",
				lpObj->AccountID, lpObj->Name, gSetItemOption.GetSetOptionName(OptionTableIndex));

			for ( int tablecnt=0;tablecnt<(OptionTableCount-1);tablecnt++)
			{
				if ( gSetItemOption.GetSetOption(OptionTableIndex, tablecnt,
					op1, op2, opvalue1, opvalue2, lpObj->Class, lpObj->ChangeUP) )
				{
					gObjSetItemPlusSpecial(lpObj, op1, opvalue1);
					gObjSetItemPlusSpecial(lpObj, op2, opvalue2);
				}
			}
				
			if ( gSetItemOption.GetMaxSetOptionCount(OptionTableIndex) < OptionTableCount )
			{
				LogAdd(LOG_RED,  "풀옵션 적용");
				lpObj->IsFullSetItem = true;

				gSetItemOption.GetGetFullSetOption(OptionTableIndex,
					op1, op2, op3, op4, op5,
					opvalue1, opvalue2, opvalue3, opvalue4, opvalue5,
					lpObj->Class, lpObj->ChangeUP);

				gObjSetItemPlusSpecial(lpObj, op1, opvalue1);
				gObjSetItemPlusSpecial(lpObj, op2, opvalue2);
				gObjSetItemPlusSpecial(lpObj, op3, opvalue3);
				gObjSetItemPlusSpecial(lpObj, op4, opvalue4);
				gObjSetItemPlusSpecial(lpObj, op5, opvalue5);
			}		
		}
	}
}




void gObjSetItemStatPlusSpecial(LPOBJ lpObj, int option, int ivalue)
{
	if ( option == -1 )
		return;

	switch ( option )	// #warning Add AT_SET_OPTION_IMPROVE_LEADERSHIP
	{
		case AT_SET_OPTION_IMPROVE_STRENGTH:
			lpObj->AddStrength += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEXTERITY:
			lpObj->AddDexterity += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ENERGY:
			lpObj->AddEnergy += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_VITALITY:
			lpObj->AddVitality += ivalue;
			break;
	}
}



void gObjSetItemPlusSpecial(LPOBJ lpObj, int option, int ivalue)
{
	if ( option == -1 )
		return;

	switch ( option )
	{
		case AT_SET_OPTION_DOUBLE_DAMAGE:
			lpObj->SetOpDoubleDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_SHIELD_DEFENCE:
			lpObj->SetOpImproveSheldDefence += ivalue;
			break;
		case AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE:
			lpObj->SetOpTwoHandSwordImproveDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MINATTACKDAMAGE:
			lpObj->SetOpAddMinAttackDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXATTACKDAMAGE:
			lpObj->SetOpAddMaxAttackDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAGICDAMAGE:
			lpObj->SetOpAddMagicPower += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DAMAGE:
			lpObj->SetOpAddDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKRATE:
			lpObj->SetOpImproveSuccessAttackRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE:
			lpObj->SetOpAddDefence += ivalue;
			break;
		case AT_SET_OPTION_DEFENCE_IGNORE:
			lpObj->SetOpIgnoreDefense += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXLIFE:
			lpObj->AddLife += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXMANA:
			lpObj->AddMana += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXAG:
			lpObj->AddBP += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_AG_VALUE:
			lpObj->SetOpIncAGValue += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_CRITICALDAMAGE:
			lpObj->SetOpAddCriticalDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_CRITICALDAMAGE_SUCCESS:
			lpObj->SetOpAddCriticalDamageSuccessRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_EX_DAMAGE:
			lpObj->SetOpAddExDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_EX_DAMAGE_SUCCESS:
			lpObj->SetOpAddExDamageSuccessRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_SKILLDAMAGE:
			lpObj->SetOpAddSkillAttack += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_DEX:
			lpObj->SetOpAddAttackDamage += ( lpObj->Dexterity + lpObj->AddDexterity ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_STR:
			lpObj->SetOpAddAttackDamage += ( lpObj->Strength + lpObj->AddStrength ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAGICDAMAGE_WITH_ENERGY:
			lpObj->SetOpAddMagicPower += ( lpObj->Energy + lpObj->AddEnergy ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE_WITH_DEX:
			lpObj->SetOpAddDefence += lpObj->Dexterity + ( lpObj->AddDexterity  / ivalue );
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE_WITH_VIT:
			lpObj->SetOpAddDefence += ( lpObj->Vitality + lpObj->AddVitality ) / ivalue;
			break;
		case AT_SET_OPTION_FIRE_MASTERY:
			lpObj->m_AddResistance[R_FIRE] += ivalue;
			break;
		case AT_SET_OPTION_ICE_MASTERY:
			lpObj->m_AddResistance[R_ICE] += ivalue;
			break;
		case AT_SET_OPTION_THUNDER_MASTERY:
			lpObj->m_AddResistance[R_LIGHTNING] += ivalue;
			break;
		case AT_SET_OPTION_POSION_MASTERY:
			lpObj->m_AddResistance[R_POISON] += ivalue;
			break;
		case AT_SET_OPTION_WATER_MASTERY:
			lpObj->m_AddResistance[R_WATER] += ivalue;
			break;
		case AT_SET_OPTION_WIND_MASTERY:
			lpObj->m_AddResistance[R_WIND] += ivalue;
			break;
		case AT_SET_OPTION_EARTH_MASTERY:
			lpObj->m_AddResistance[R_EARTH] += ivalue;
			break;
	}
}




void gObjSetItemApply(LPOBJ lpObj)
{
	lpObj->m_AttackDamageMinLeft += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMaxLeft += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMinRight += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMaxRight += lpObj->SetOpAddAttackDamage;

	lpObj->m_AttackDamageMinLeft += lpObj->SetOpAddMinAttackDamage;
	lpObj->m_AttackDamageMinRight += lpObj->SetOpAddMinAttackDamage;

	lpObj->m_AttackDamageMaxLeft += lpObj->SetOpAddMaxAttackDamage;
	lpObj->m_AttackDamageMaxRight += lpObj->SetOpAddMaxAttackDamage;

	lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * lpObj->SetOpAddMagicPower / 100;
	lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * lpObj->SetOpAddMagicPower / 100;

	lpObj->AddLife += INT(lpObj->AddVitality * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->AddMana += INT(lpObj->AddEnergy * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->m_CriticalDamage += lpObj->SetOpAddCriticalDamageSuccessRate;
	lpObj->m_ExcelentDamage += lpObj->SetOpAddExDamageSuccessRate;

	if ( lpObj->pInventory[10].IsSetItem() )
	{
		lpObj->pInventory[10].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->pInventory[11].IsSetItem() )
	{
		lpObj->pInventory[11].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->pInventory[9].IsSetItem() )
	{
		lpObj->pInventory[9].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->SetOpTwoHandSwordImproveDamage )
	{
		if ( !lpObj->pInventory[1].IsItem() && !lpObj->pInventory[0].IsItem() )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}

		if ( lpObj->pInventory[1].IsItem() && lpObj->pInventory[1].m_TwoHand == FALSE )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}

		if ( lpObj->pInventory[0].IsItem() && lpObj->pInventory[0].m_TwoHand == FALSE )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}
	}

	if ( (lpObj->MaxLife + lpObj->AddLife ) < lpObj->Life )
	{
		lpObj->Life = lpObj->MaxLife + lpObj->AddLife;
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0);
	}

	gObjSetBP(lpObj->m_Index);

	if ( (lpObj->MaxMana + lpObj->AddMana ) < lpObj->Mana )
	{
		lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
		GCManaSend(lpObj->m_Index, lpObj->Mana, 0xFF, 0, lpObj->BP);
	}

	lpObj->m_Defense += lpObj->SetOpAddDefence * 10 / 20;
	lpObj->m_Defense += lpObj->m_Defense * lpObj->SetOpAddDefenceRate / 100;

	if ( lpObj->pInventory[1].m_Type >= ITEMGET(6,0) && lpObj->pInventory[1].m_Type < ITEMGET(7,0) )
	{
		lpObj->m_Defense += lpObj->m_Defense * lpObj->SetOpImproveSheldDefence / 100;
	}
}





BOOL gObjValidItem(LPOBJ lpObj, CItem * lpItem, int pos)
{
	LPITEM_ATTRIBUTE p = &ItemAttribute[lpItem->m_Type];
	
	if ( p->RequireStrength != 0 )
	{
		if ( (lpObj->Strength + lpObj->AddStrength) < lpItem->m_RequireStrength)
		{
			return FALSE;
		}
	}

	if ( p->RequireDexterity != 0 )
	{
		if ( (lpObj->Dexterity + lpObj->AddDexterity) < lpItem->m_RequireDexterity)
		{
			return FALSE;
		}
	}


	if ( p->RequireEnergy != 0 )
	{
		if ( (lpObj->Energy + lpObj->AddEnergy) < lpItem->m_RequireEnergy )
		{
			return FALSE;
		}
	}

	if ( p->RequireLevel != 0 )
	{
		if ( (lpObj->Level) < lpItem->m_RequireLevel )
		{
			return FALSE;
		}
	}

	if ( lpItem->m_Type >= ITEMGET(0,0) && lpItem->m_Type <= ITEMGET(11, 0) )
	{
		if ( p->RequireVitality )
		{
			if ( (lpObj->Vitality + lpObj->AddVitality ) < lpItem->m_RequireVitality )
			{
				return FALSE;
			}
		}

		if ( p->RequireLeadership )
		{
			if ( (lpObj->Leadership + lpObj->AddLeadership ) < lpItem->m_RequireLeaderShip )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}