#include "StdAfx.h"
#include "TNotice.h"
#include "DSProtocol.h"

CDropEvent gDropEvent;

void CDropEvent::Load()
{
	for(int i = 0; i < 4; i++)
	{
		this->iCount[i] = 0;
	}
	// ---
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	memset(this->m_Item, 0, sizeof(this->m_Item));
	// ---
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(DROPEVENT_FILE), Class);
	// ---	
	if(Class.GetSection(0, Section))
	{	
		this->iEnabled		= Section.Rows[0].GetInt(0);
	}
	// ---	
	if(Class.GetSection(1, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Data[this->iCount[1]].Hour	= Section.Rows[i].GetInt(0);
			this->m_Data[this->iCount[1]].Min	= Section.Rows[i].GetInt(1);
			// ---
			this->iCount[1]++;
		}
	}
	// ---
	if(Class.GetSection(2, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Data[this->iCount[2]].Map	= Section.Rows[i].GetInt(0);
			this->m_Data[this->iCount[2]].X		= Section.Rows[i].GetInt(1);
			this->m_Data[this->iCount[2]].Y		= Section.Rows[i].GetInt(2);
			// ---
			this->iCount[2]++;
		}
	}
	// ---
	if(Class.GetSection(3, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Item[this->iCount[3]].Type		= Section.Rows[i].GetInt(0);
			this->m_Item[this->iCount[3]].Index		= Section.Rows[i].GetInt(1);
			this->m_Item[this->iCount[3]].Level		= Section.Rows[i].GetInt(2);
			this->m_Item[this->iCount[3]].Skill		= Section.Rows[i].GetInt(3);
			this->m_Item[this->iCount[3]].Luck		= Section.Rows[i].GetInt(4);
			this->m_Item[this->iCount[3]].Opt		= Section.Rows[i].GetInt(5);
			this->m_Item[this->iCount[3]].Exc		= Section.Rows[i].GetInt(6);
			this->m_Item[this->iCount[3]].Anc		= Section.Rows[i].GetInt(7);
			// ---
			this->iCount[3]++;
		}
	}
}

void CDropEvent::Init()
{
	MsgAllUser(0, "[Drop Hour] Evento Iniciado!");
	// ---
	for(int i = 0; i < this->iCount[3]; i++)
	{
		int iRand = rand()% this->iCount[1];
		// ---
		int NewExl = 0;
		int NewAnc = 0;
		// ---
		int DropItem = ITEMGET(this->m_Item[iRand].Type, this->m_Item[iRand].Index);
		// ---
		if(this->m_Item[iRand].Exc > 0)
		{
			NewExl = gToolKit.ExcOpt(this->m_Item[iRand].Exc);
		}
		// ---
		if(this->m_Item[iRand].Anc == 5 || this->m_Item[iRand].Anc == 10)
		{
			NewAnc = this->m_Item[iRand].Anc;
		}
		// ---
		int CordMap = this->m_Data[i].Map;
		int CordX	= this->m_Data[i].X;
		int CordY	= this->m_Data[i].Y;
		// ---
		ItemSerialCreateSend(NULL,CordMap,CordX,CordY,DropItem,this->m_Item[iRand].Level,0,this->m_Item[iRand].Skill,this->m_Item[iRand].Luck,this->m_Item[iRand].Opt,NULL,NewExl,NewAnc);
	}
}

void CDropEvent::TimeTick()
{
	if(!this->iEnabled)
	{
		return;
	}
	// ---
	SYSTEMTIME t;
	GetLocalTime(&t);
	// ---
	if(t.wSecond == 00)
	{
		for(int i = 0; i < this->iCount[2]; i++)
		{
			if(this->m_Data[i].Hour == t.wHour && this->m_Data[i].Min == t.wMinute)
			{
				this->Init();
				return;
			}
		}
	}
}