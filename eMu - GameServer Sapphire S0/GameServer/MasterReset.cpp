#include "StdAfx.h"
#include "TNotice.h"
#include "QuestInfo.h"

CMasterReset gMasterReset;

void CMasterReset::Load()
{
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;
	// ---
	Token.ParseFile(std::string(MASTERRESET_FILE), Group);
	// ---
	if(Group.GetSection(0, Section))
	{
		strcpy_s(this->szSintax, sizeof(this->szSintax), (Section.Rows[0].GetStringPtr(0)));
	}
	// ---
	if(Group.GetSection(1, Section))
	{
		this->m_Data[0].bEnabled			= Section.Rows[0].GetInt(0);
		this->m_Data[1].bEnabled			= Section.Rows[1].GetInt(0);
		this->m_Data[2].bEnabled			= Section.Rows[2].GetInt(0);
		this->m_Data[3].bEnabled			= Section.Rows[3].GetInt(0);
		// ---
		this->m_Data[0].iResetStatus		= Section.Rows[0].GetInt(1);
		this->m_Data[1].iResetStatus		= Section.Rows[1].GetInt(1);
		this->m_Data[2].iResetStatus		= Section.Rows[2].GetInt(1);
		this->m_Data[3].iResetStatus		= Section.Rows[3].GetInt(1);
		// ---
		this->m_Data[0].iMover				= Section.Rows[0].GetInt(2);
		this->m_Data[1].iMover				= Section.Rows[1].GetInt(2);
		this->m_Data[2].iMover				= Section.Rows[2].GetInt(2);
		this->m_Data[3].iMover				= Section.Rows[3].GetInt(2);
		// ---
		this->m_Data[0].iRelogar			= Section.Rows[0].GetInt(3);
		this->m_Data[1].iRelogar			= Section.Rows[1].GetInt(3);
		this->m_Data[2].iRelogar			= Section.Rows[2].GetInt(3);
		this->m_Data[3].iRelogar			= Section.Rows[3].GetInt(3);
		// ---
		this->m_Data[0].iGold				= Section.Rows[0].GetInt(4);
		this->m_Data[1].iGold				= Section.Rows[1].GetInt(4);
		this->m_Data[2].iGold				= Section.Rows[2].GetInt(4);
		this->m_Data[3].iGold				= Section.Rows[3].GetInt(4);
		// ---
		this->m_Data[0].iCash				= Section.Rows[0].GetInt(5);
		this->m_Data[1].iCash				= Section.Rows[1].GetInt(5);
		this->m_Data[2].iCash				= Section.Rows[2].GetInt(5);
		this->m_Data[3].iCash				= Section.Rows[3].GetInt(5);
		// ---
		this->m_Data[0].iResetQuest			= Section.Rows[0].GetInt(6);
		this->m_Data[1].iResetQuest			= Section.Rows[1].GetInt(6);
		this->m_Data[2].iResetQuest			= Section.Rows[2].GetInt(6);
		this->m_Data[3].iResetQuest			= Section.Rows[3].GetInt(6);
		// ---
		this->m_Data[0].iResetSkills		= Section.Rows[0].GetInt(7);
		this->m_Data[1].iResetSkills		= Section.Rows[1].GetInt(7);
		this->m_Data[2].iResetSkills		= Section.Rows[2].GetInt(7);
		this->m_Data[3].iResetSkills		= Section.Rows[3].GetInt(7);
	}
	// ---
	if(Group.GetSection(2, Section))
	{
		this->m_Data[0].iResets			= Section.Rows[0].GetInt(0);
		this->m_Data[1].iResets			= Section.Rows[1].GetInt(0);
		this->m_Data[2].iResets			= Section.Rows[2].GetInt(0);
		this->m_Data[3].iResets			= Section.Rows[3].GetInt(0);
		// ---
		this->m_Data[0].iLevel			= Section.Rows[0].GetInt(1);
		this->m_Data[1].iLevel			= Section.Rows[1].GetInt(1);
		this->m_Data[2].iLevel			= Section.Rows[2].GetInt(1);
		this->m_Data[3].iLevel			= Section.Rows[3].GetInt(1);
		// ---
		this->m_Data[0].iMoney			= Section.Rows[0].GetInt(2);
		this->m_Data[1].iMoney			= Section.Rows[1].GetInt(2);
		this->m_Data[2].iMoney			= Section.Rows[2].GetInt(2);
		this->m_Data[3].iMoney			= Section.Rows[3].GetInt(2);
		// ---
		this->m_Data[0].wStrength		= Section.Rows[0].GetInt(3);
		this->m_Data[1].wStrength		= Section.Rows[1].GetInt(3);
		this->m_Data[2].wStrength		= Section.Rows[2].GetInt(3);
		this->m_Data[3].wStrength		= Section.Rows[3].GetInt(3);
		// ---
		this->m_Data[0].wDexterity		= Section.Rows[0].GetInt(4);
		this->m_Data[1].wDexterity		= Section.Rows[1].GetInt(4);
		this->m_Data[2].wDexterity		= Section.Rows[2].GetInt(4);
		this->m_Data[3].wDexterity		= Section.Rows[3].GetInt(4);
		// ---
		this->m_Data[0].wVitality		= Section.Rows[0].GetInt(5);
		this->m_Data[1].wVitality		= Section.Rows[1].GetInt(5);
		this->m_Data[2].wVitality		= Section.Rows[2].GetInt(5);
		this->m_Data[3].wVitality		= Section.Rows[3].GetInt(5);
		// ---
		this->m_Data[0].wEnergy			= Section.Rows[0].GetInt(6);
		this->m_Data[1].wEnergy			= Section.Rows[1].GetInt(6);
		this->m_Data[2].wEnergy			= Section.Rows[2].GetInt(6);
		this->m_Data[3].wEnergy			= Section.Rows[3].GetInt(6);
		// ---
		this->m_Data[0].wLeadership		= Section.Rows[0].GetInt(7);
		this->m_Data[1].wLeadership		= Section.Rows[1].GetInt(7);
		this->m_Data[2].wLeadership		= Section.Rows[2].GetInt(7);
		this->m_Data[3].wLeadership		= Section.Rows[3].GetInt(7);
		// ---
		this->m_Data[0].iLevelReborn	= Section.Rows[0].GetInt(8);
		this->m_Data[1].iLevelReborn	= Section.Rows[1].GetInt(8);
		this->m_Data[2].iLevelReborn	= Section.Rows[2].GetInt(8);
		this->m_Data[3].iLevelReborn	= Section.Rows[3].GetInt(8);
	}
}

void CMasterReset::Init(LPOBJ lpObj)
{
	if(!this->m_Data[lpObj->m_Vip].bEnabled)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Comando Desativado.", lpObj->Name);
		return;
	}
	// ---
	else if(lpObj->Level < this->m_Data[lpObj->m_Vip].iLevel)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Level necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].iLevel);
		return;
	}
	// ---
	else if(lpObj->Money < this->m_Data[lpObj->m_Vip].iMoney)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Zen necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].iMoney);
		return;
	}
	// ---
	else if(lpObj->Strength < this->m_Data[lpObj->m_Vip].wStrength)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Força necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].wStrength);
		return;
	}
	// ---
	else if(lpObj->Dexterity < this->m_Data[lpObj->m_Vip].wDexterity)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Agilidade necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].wDexterity);
		return;
	}
	// ---
	else if(lpObj->Vitality < this->m_Data[lpObj->m_Vip].wVitality)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Vitalidade necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].wVitality);
		return;
	}
	// ---
	else if(lpObj->Energy < this->m_Data[lpObj->m_Vip].wEnergy)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Energia necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].wEnergy);
		return;
	}
	// ---
	else if(lpObj->Class == CLASS_DARKLORD)
	{
		if(lpObj->Leadership < this->m_Data[lpObj->m_Vip].wLeadership)
		{
			MsgUser(lpObj->m_Index, 1, "[%s] Carisma necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].wLeadership);
			return;
		}
	}
	// ---
	else if(lpObj->m_Resets < this->m_Data[lpObj->m_Vip].iResets)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Reset necessario %d.", lpObj->Name, this->m_Data[lpObj->m_Vip].iResets);
		return;
	}
	else
	{
		lpObj->m_Resets			-= this->m_Data[lpObj->m_Vip].iResets;
		// ---
		lpObj->Level			= this->m_Data[lpObj->m_Vip].iLevelReborn;
		lpObj->NextExp			= 1;
		lpObj->Experience		= 1;
		lpObj->BP				= 1;
		lpObj->MaxBP			= 1;
		// ---
		lpObj->m_MasterResets++;
		// ---
		if(this->m_Data[lpObj->m_Vip].iResetStatus == 1)
		{
			lpObj->Strength		= 15;
			lpObj->Dexterity	= 15;
			lpObj->Vitality		= 15;
			lpObj->Energy	    = 15;
			// ---
			if(lpObj->Class == CLASS_DARKLORD)
			{
				lpObj->Leadership	= 15;
			}
		}
		// ---
		if(this->m_Data[lpObj->m_Vip].iMover == 1)
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
		if(this->m_Data[lpObj->m_Vip].iGold > 0)
		{
			gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Gold, gSQLManager.m_Data.Coluna_Gold, gSQLManager.m_Data.Coluna_Gold, this->m_Data[lpObj->m_Vip].iGold, lpObj->AccountID);
		}
		// ---
		if(this->m_Data[lpObj->m_Vip].iCash > 0)
		{
			gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Cash, gSQLManager.m_Data.Coluna_Cash, gSQLManager.m_Data.Coluna_Cash, this->m_Data[lpObj->m_Vip].iCash, lpObj->AccountID);
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
		GCReFillSend(lpObj->m_Index, (int)lpObj->MaxLife + lpObj->AddLife, 0xFE, 0);
		// ---
		GCLevelUpMsgSend(lpObj->m_Index, true);
		// ---
		gObjSetBP(lpObj->m_Index);
		// ---
		GCManaSend(lpObj->m_Index,(int)lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
		// ---
		MsgUser(lpObj->m_Index, 1, "[%s] Resetou, você tem %d master reset (s).", lpObj->Name, lpObj->m_MasterResets);
		// ---
		gSQLManager.UpdateMasterReset(lpObj->m_Index);
		// ---
		return;
	}
}