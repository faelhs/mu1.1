#include "StdAfx.h"
#include "TNotice.h"

CMoves gMoves;

void CMoves::Load()
{
	this->iCount = 0;
	// ---
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;
	// ---
	Token.ParseFile(std::string(MOVES_FILE), Group);
	// ---
	if(Group.GetSection(0, Section))
	{
		for(int i = 0; i < Section.RowCount; i++)
		{
			strcpy_s(this->m_Data[this->iCount].szSintax, sizeof(this->m_Data[this->iCount].szSintax), (Section.Rows[i].GetStringPtr(0)));
			// ---
			this->m_Data[this->iCount].bEnabled		= Section.Rows[i].GetInt(1);
			this->m_Data[this->iCount].szVip		= Section.Rows[i].GetInt(2);
			this->m_Data[this->iCount].szPK			= Section.Rows[i].GetInt(3);
			this->m_Data[this->iCount].sLevel		= Section.Rows[i].GetInt(4);
			this->m_Data[this->iCount].sMap			= Section.Rows[i].GetInt(5);
			this->m_Data[this->iCount].sCordX		= Section.Rows[i].GetInt(6);
			this->m_Data[this->iCount].sCordY		= Section.Rows[i].GetInt(7);
			// ---
			this->iCount++;
		}
	}
	// ---
	LogAdd(LOG_GOLD, "[MOVES FILE] Carregado !");
}

void CMoves::Init(LPOBJ lpObj, bool bEnabled, char szVip, char szPK, short sLevel, short sMap, short sCordX, short sCordY)
{
	if(!bEnabled)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Comando Desativado.", lpObj->Name);
		return;
	}
	// ---
	if(lpObj->Level < sLevel)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Level necessario %d.", lpObj->m_Vip, sLevel);
		return;
	}
	// ---
	if(lpObj->m_Vip < szVip)
	{
		MsgUser(lpObj->m_Index, 1, "[%s] Você não é vip", lpObj->m_Vip);
		return;
	}
	// ---
	if(szPK == 1)
	{
	    if(lpObj->m_PK_Level > 3)
	    {
			MsgUser(lpObj->m_Index, 1, "[%s] Você está PK", lpObj->Name);
			return;
	    }
	}
	// ---
	if(lpObj->m_IfState.use == 1)
	{
		return;
	}
	// ---
	if(lpObj->m_bPShopOpen == true)
	{
		return;
	}
	// ---
	gObjTeleport(lpObj->m_Index, sMap, sCordX, sCordY);
}