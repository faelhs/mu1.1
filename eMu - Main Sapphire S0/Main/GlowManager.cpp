#include "StdAfx.h"
// ---
CGlowManager gGlowManager;
// ---
void CGlowManager::Load()
{
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(""), Class);
	// ---
	if(Class.GetSection(0, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Data[i].iType				= Section.Rows[i].GetInt(0);
			this->m_Data[i].iIndex				= Section.Rows[i].GetInt(1);
			// ---
			this->m_Data[i].fRed				= Section.Rows[i].GetFloat(2);
			this->m_Data[i].fGreen				= Section.Rows[i].GetFloat(3);
			this->m_Data[i].fBlue				= Section.Rows[i].GetFloat(4);
			// ---
			this->iCount++;
		}
	}
	// ---
	for(int i = 0; i < this->iCount; i++)
	{
		gToolKit.SetHook((LPVOID)&this->gObjItemGlowEx,(LPVOID)0x005069A2, ASM::CALL);
		gToolKit.SetHook((LPVOID)&this->gObjItemGlowEx,(LPVOID)0x005F8445, ASM::CALL);
	}
}

void CGlowManager::gObjItemGlowEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode)
{
	for(int i = 0; i <= gGlowManager.iCount; i++)
	{
		if(ObjectId == ITEM_ID(gGlowManager.m_Data[i].iType, gGlowManager.m_Data[i].iIndex))
		{
			Vector(gGlowManager.m_Data[i].fRed, gGlowManager.m_Data[i].fGreen, gGlowManager.m_Data[i].fBlue, Color);
			break;
		}
		else
		{
			gObjItemGlow(ObjectId,Arg2,Arg3,Color,BalrogMode);
		}
	}
}