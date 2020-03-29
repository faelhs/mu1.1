#include "StdAfx.h"
#include "TNotice.h"
// ---
CLottery gLottery;
// ---
void CLottery::Load()
{
	memset(&this->m_Data, 0, sizeof(this->m_Data));
	// ---
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(LOTTERY_FILE), Class);
	// ---	
	if(Class.GetSection(0, Section))
	{	
		this->m_Data.Enabled		=	Section.Rows[0].GetInt(0);
		this->m_Data.Time			=	Section.Rows[0].GetInt(1);
		this->m_Data.iType			=	Section.Rows[0].GetInt(2);
	}
	// ---
	if(Class.GetSection(1, Section))
	{	
		this->m_Data.Gold			=	Section.Rows[0].GetInt(0);
		this->m_Data.Cash			=	Section.Rows[0].GetInt(1);
		this->m_Data.LevelUpPoints	=	Section.Rows[0].GetInt(2);
	}
	// ---
	_beginthread(&this->TimeTick, 0, 0);
}
// ---
void CLottery::TimeTick(LPVOID lpTime)
{
	while(gLottery.m_Data.Enabled)
	{
		Sleep(gLottery.m_Data.Time * 60000);
		// ---
		gLottery.Init();
	}
	// ---
	_endthread();
}
// ---
void CLottery::Init()
{
	int iTarget = 0;
	// ---
	for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if(gObj[i].Connected >= PLAYER_PLAYING)
		{
			this->m_Data.pRecv[iTarget++] = i;
		}
	}
	// ---
	if(iTarget > 0)
	{
		int Index = rand() % iTarget;
		// ---
		int Target = this->m_Data.pRecv[Index];
		// ---
		switch(this->m_Data.iType)
		{
		case 1:
			{
				gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Cash, gSQLManager.m_Data.Coluna_Cash, gSQLManager.m_Data.Coluna_Cash, this->m_Data.Cash, gObj[Target].AccountID);
				// ---
				MsgAllUser(0, "%s Foi Sorteado Com %d Cash(s).", gObj[Target].Name, this->m_Data.Cash);
				// ---
				MsgUser(gObj[Target].m_Index, 1, "Você Foi Sorteado Com %d Cash(s).", this->m_Data.Cash);
			}
			break;
		case 2:
			{
				gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Gold, gSQLManager.m_Data.Coluna_Gold, gSQLManager.m_Data.Coluna_Gold, this->m_Data.Gold, gObj[Target].AccountID);
				// ---
				MsgAllUser(0, "%s Foi Sorteado Com %d Gold(s).", gObj[Target].Name, this->m_Data.Gold);
				// ---
				MsgUser(gObj[Target].m_Index, 1, "Você Foi Sorteado Com %d Gold(s).", this->m_Data.Gold);
			}
			break;
		case 3:
			{
				gObj[Target].LevelUpPoint += this->m_Data.LevelUpPoints;
				// ---
				MsgAllUser(0, "%s Foi Sorteado Com %d UpPoints(s).", gObj[Target].Name, this->m_Data.LevelUpPoints);
				// ---
				MsgUser(gObj[Target].m_Index, 1, "Você Foi Sorteado Com %d UpPoints(s).", this->m_Data.LevelUpPoints);
			}
			break;
		}
	}
}