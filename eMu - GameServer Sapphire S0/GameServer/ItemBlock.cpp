#include "StdAfx.h"
// ---
CItemBlock gItemBlock;
// ---
void CItemBlock::Load()
{
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(ITEMBLOCK_FILE), Class);
	// ---	
	if(Class.GetSection(0, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Data[this->iCount].Type			= Section.Rows[i].GetInt(0);
			this->m_Data[this->iCount].ID			= Section.Rows[i].GetInt(1);
			this->m_Data[this->iCount].Level		= Section.Rows[i].GetInt(2);
			// ---
			this->iCount++;
		}
	}
}
// ---
bool CItemBlock::IsEnableToTrade(LPOBJ lpObj) 
{
	BOOL bTrade = 1;
	// ---
	for(int n = 0; n < TRADE_BOX_SIZE; n++)
	{
		if(lpObj->Trade[n].IsItem() == 1)
		{
			if(this->IsCheckItem(&lpObj->Trade[n]) == 1)
			{
				bTrade = 0;
			}
		}
	}
	// ---
	return bTrade;
}
// ---
bool CItemBlock::IsCheckItem(CItem * pItem)
{
	for(int i = 0; i < this->iCount; i++)
	{
		if(pItem->m_Type == ITEMGET(this->m_Data[i].Type, this->m_Data[i].ID))
		{
			if(pItem->m_Level == this->m_Data[i].Level)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	// ---
	return 0;
}