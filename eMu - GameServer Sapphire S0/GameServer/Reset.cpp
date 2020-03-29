#include "StdAfx.h"
#include "TNotice.h"
#include "QuestInfo.h"

CReset gReset;

void CReset::Load()
{
	this->iCount = 0;
	// ---
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;
	// ---
	Token.ParseFile(std::string(RESET_FILE), Group);
	// ---
	if(Group.GetSection(0, Section))
	{
		strcpy_s(this->szSintax, sizeof(this->szSintax), (Section.Rows[0].GetStringPtr(0)));
	}
	// ---
	if(Group.GetSection(1, Section))
	{
		this->m_Data[0].iEnabled				= Section.Rows[0].GetInt(0);
		this->m_Data[1].iEnabled				= Section.Rows[1].GetInt(0);
		this->m_Data[2].iEnabled				= Section.Rows[2].GetInt(0);
		this->m_Data[3].iEnabled				= Section.Rows[3].GetInt(0);
		// ---
		this->m_Data[0].iType					= Section.Rows[0].GetInt(1);
		this->m_Data[1].iType					= Section.Rows[1].GetInt(1);
		this->m_Data[2].iType					= Section.Rows[2].GetInt(1);
		this->m_Data[3].iType					= Section.Rows[3].GetInt(1);
		// ---
		this->m_Data[0].iMove					= Section.Rows[0].GetInt(2);
		this->m_Data[1].iMove					= Section.Rows[1].GetInt(2);
		this->m_Data[2].iMove					= Section.Rows[2].GetInt(2);
		this->m_Data[3].iMove					= Section.Rows[3].GetInt(2);
		// ---
		this->m_Data[0].iRelogar				= Section.Rows[0].GetInt(3);
		this->m_Data[1].iRelogar				= Section.Rows[1].GetInt(3);
		this->m_Data[2].iRelogar				= Section.Rows[2].GetInt(3);
		this->m_Data[3].iRelogar				= Section.Rows[3].GetInt(3);
		// ---
		this->m_Data[0].iResetQuest				= Section.Rows[0].GetInt(4);
		this->m_Data[1].iResetQuest				= Section.Rows[1].GetInt(4);
		this->m_Data[2].iResetQuest				= Section.Rows[2].GetInt(4);
		this->m_Data[3].iResetQuest				= Section.Rows[3].GetInt(4);
		// ---
		this->m_Data[0].iResetSkills			= Section.Rows[0].GetInt(5);
		this->m_Data[1].iResetSkills			= Section.Rows[1].GetInt(5);
		this->m_Data[2].iResetSkills			= Section.Rows[2].GetInt(5);
		this->m_Data[3].iResetSkills			= Section.Rows[3].GetInt(5);
	}
	// ---
	if(Group.GetSection(2, Section))
	{
		for(int i = 0; i < Section.RowCount; i++)
		{ 
			this->m_Data[this->iCount].iVip					= Section.Rows[i].GetInt(0);
			this->m_Data[this->iCount].iResetMin			= Section.Rows[i].GetInt(1);
			this->m_Data[this->iCount].iResetMax			= Section.Rows[i].GetInt(2);
			this->m_Data[this->iCount].sLevel				= Section.Rows[i].GetInt(3);
			this->m_Data[this->iCount].iMoney				= Section.Rows[i].GetInt(4);
			this->m_Data[this->iCount].iPoints				= Section.Rows[i].GetInt(5);
			this->m_Data[this->iCount].iReturnLevel			= Section.Rows[i].GetInt(6);
			// ---
			this->m_Data[this->iCount].wReturnStrength       = Section.Rows[i].GetInt(7);
			this->m_Data[this->iCount].wReturnDexterity      = Section.Rows[i].GetInt(8);
			this->m_Data[this->iCount].wReturnVitality       = Section.Rows[i].GetInt(9);
			this->m_Data[this->iCount].wReturnEnergy		 = Section.Rows[i].GetInt(10);
			this->m_Data[this->iCount].wReturnLeadership     = Section.Rows[i].GetInt(11);
			// ---
			this->iCount++;
		}
	}
}

void CReset::Init(LPOBJ lpObj)
{
	for(int i = 0; i < this->iCount; i++)
	{
		if(lpObj->m_Vip == this->m_Data[i].iVip)
		{
			if(lpObj->m_Resets >= this->m_Data[i].iResetMin && lpObj->m_Resets <= this->m_Data[i].iResetMax)
			{
				if(lpObj->Level < this->m_Data[i].sLevel)
				{
					MsgUser(lpObj->m_Index, 1, "[%s] Level necessário %d.", lpObj->Name, this->m_Data[i].sLevel);
					return;
				}
				// ---
				if(lpObj->Money < this->m_Data[i].iMoney)
				{
					MsgUser(lpObj->m_Index, 1, "[%s] Zen necessário %d.", lpObj->Name, this->m_Data[i].iMoney);
					return;
				}
				// ---
				lpObj->Experience        = 1;
				lpObj->NextExp           = 100;
				lpObj->Level             = this->m_Data[i].iReturnLevel;
				lpObj->Money            -= this->m_Data[i].iMoney;
				// ---
				lpObj->m_Resets++;
				// ---
				if(this->m_Data[lpObj->m_Vip].iType == 1)
				{
					lpObj->LevelUpPoint = lpObj->m_Resets * this->m_Data[i].iPoints;
					lpObj->Strength     = this->m_Data[lpObj->m_Vip].wReturnStrength;
					lpObj->Dexterity    = this->m_Data[lpObj->m_Vip].wReturnDexterity;
					lpObj->Vitality     = this->m_Data[lpObj->m_Vip].wReturnVitality;
					lpObj->MaxLife      = lpObj->VitalityToLife * 25;
					lpObj->Energy       = this->m_Data[lpObj->m_Vip].wReturnEnergy;
					lpObj->MaxMana      = lpObj->EnergyToMana * 25;
					// ---
					if(this->m_Data[lpObj->m_Vip].wReturnLeadership != -1 && lpObj->Class == CLASS_DARKLORD)
					{
						lpObj->Leadership = this->m_Data[lpObj->m_Vip].wReturnLeadership;
					}
					// ---
	                GCReFillSend(lpObj->m_Index,(WORD)lpObj->MaxLife + lpObj->AddLife,0xFE, 0);
                    gObjSetBP(lpObj->m_Index);
	                GCManaSend(lpObj->m_Index,(short)lpObj->MaxMana + lpObj->AddMana,0xFE,0,lpObj->MaxBP + lpObj->AddBP);
				}
				// ---
				if(this->m_Data[lpObj->m_Vip].iMove == 1)
				{
		            if(lpObj->DbClass == 0 || lpObj->DbClass == 1 || lpObj->DbClass == 16 || lpObj->DbClass == 17 || lpObj->DbClass == 48 || lpObj->DbClass == 64)
		            {
			            gObjTeleport(lpObj->m_Index, 0, 140, 135);
		            }
					// ---
		            if(lpObj->DbClass == 32 || lpObj->DbClass == 33)
		            {
			            gObjTeleport(lpObj->m_Index, 3, 174, 114);
					}
				}
				// ---
				if(this->m_Data[lpObj->m_Vip].iResetQuest == 1)
				{
					g_QuestInfo.ReSetQuestState(lpObj, 2);
					g_QuestInfo.ReSetQuestState(lpObj, 3);
				}
				// ---
				if(this->m_Data[lpObj->m_Vip].iResetSkills == 1)
				{
					for(int n = 0; n < MAGIC_SIZE;n++)
					{
						if(lpObj->Magic[n].IsMagic() == 1)
						{
							lpObj->Magic[n].Clear();
						}
					}
				}
				// ---
				if(this->m_Data[lpObj->m_Vip].iRelogar == 1)
				{
					lpObj->CloseType  = 1;
					lpObj->CloseCount = 5;
				}
				else
				{
					gToolKit.Refresh(lpObj->m_Index);
				}
				// ---
				GCMoneySend(lpObj->m_Index, lpObj->Money);
				// ---
				gObjCalCharacter(lpObj->m_Index);
				// ---
				GCLevelUpMsgSend(lpObj->m_Index, true);
				// ---
				MsgUser(lpObj->m_Index, 1, "[%s] Resetou, você tem %d reset (s).", lpObj->Name, lpObj->m_Resets);
				// ---
				gSQLManager.UpdateReset(lpObj->m_Index);
				// ---
				//if(hgtObj->m_AutoAddStr > 0)
				//{
				//	if(lpObj->LevelUpPoint < hgtObj->m_AutoAddStr || hgtObj->m_AutoAddStr < 0 || hgtObj->m_AutoAddStr == 0)
				//	{
				//		return;
				//	}
				//	// ---
				//	lpObj->Strength += hgtObj->m_AutoAddStr;
				//	lpObj->LevelUpPoint -= hgtObj->m_AutoAddStr;
				//}
				//// ---
				//if(hgtObj->m_AutoAddAgi > 0)
				//{
				//	if(lpObj->LevelUpPoint < hgtObj->m_AutoAddAgi || hgtObj->m_AutoAddAgi < 0 || hgtObj->m_AutoAddAgi == 0)
				//	{
				//		return;
				//	}
				//	// ---
				//	lpObj->Strength += hgtObj->m_AutoAddAgi;
				//	lpObj->LevelUpPoint -= hgtObj->m_AutoAddAgi;
				//}
				//// ---
				//if(hgtObj->m_AutoAddVit > 0)
				//{
				//	if(lpObj->LevelUpPoint < hgtObj->m_AutoAddVit || hgtObj->m_AutoAddVit < 0 || hgtObj->m_AutoAddVit == 0)
				//	{
				//		return;
				//	}
				//	// ---
				//	lpObj->Strength += hgtObj->m_AutoAddVit;
				//	lpObj->LevelUpPoint -= hgtObj->m_AutoAddVit;
				//}
				//// ---
				//if(hgtObj->m_AutoAddEne > 0)
				//{
				//	if(lpObj->LevelUpPoint < hgtObj->m_AutoAddEne || hgtObj->m_AutoAddEne < 0 || hgtObj->m_AutoAddEne == 0)
				//	{
				//		return;
				//	}
				//	// ---
				//	lpObj->Strength += hgtObj->m_AutoAddEne;
				//	lpObj->LevelUpPoint -= hgtObj->m_AutoAddEne;
				//}
				//// ---
				//if(hgtObj->m_AutoAddCmd > 0)
				//{
				//	if(lpObj->LevelUpPoint < hgtObj->m_AutoAddCmd || hgtObj->m_AutoAddCmd < 0 || hgtObj->m_AutoAddCmd == 0)
				//	{
				//		return;
				//	}
				//	// ---
				//	lpObj->Strength += hgtObj->m_AutoAddCmd;
				//	lpObj->LevelUpPoint -= hgtObj->m_AutoAddCmd;
				//}
			}
			// ---
			return;
		}
	}
	// ---
	MsgUser(lpObj->m_Index, 1, "[%s] Você alcançou o máximo de resets.", lpObj->Name);
}