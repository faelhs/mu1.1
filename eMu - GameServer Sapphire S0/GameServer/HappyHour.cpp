#include "StdAfx.h"
#include "TNotice.h"

CHappyHour gHappyHour;

void CHappyHour::Load()
{
	memset(&this->m_Data, 0, sizeof(this->m_Data));
	// ---
	memset(&this->m_Time, 0, sizeof(this->m_Time));
	// ---
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(HAPPYHOUR_FILE), Class);
	// ---	
	if(Class.GetSection(0, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Data.iEnabled			= Section.Rows[i].GetInt(0);
			this->m_Data.iDrop				= Section.Rows[i].GetInt(1);
			this->m_Data.iExp				= Section.Rows[i].GetInt(2);
		}
	}
	// ---	
	if(Class.GetSection(1, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			this->m_Time[iCount].iHour		= Section.Rows[i].GetInt(0);
			this->m_Time[iCount].iEndHour	= Section.Rows[i].GetInt(1);
			this->m_Time[iCount].iMin		= Section.Rows[i].GetInt(2);
			this->m_Time[iCount].iEndMin	= Section.Rows[i].GetInt(3);
			// ---
			this->iCount++;
		}
	}
	// ---
	this->m_Data.btRunning = false;
}

void CHappyHour::TimeTick()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	// ---
	if(this->m_Data.iEnabled == 0)
	{
		return;
	}
	// ---
	else if(time.wSecond == 00)
	{
		for(int i = 0; i < iCount; i++)
		{
			if(this->m_Time[i].iHour == time.wHour && this->m_Time[i].iMin == time.wMinute)
			{
				this->m_Data.btRunning = true;
				// ---
				MsgAllUser(0, "[Happy Hour] Evento Iniciado!");
				MsgAllUser(0, "[Happy Hour] Exp: +%d Drop: +%d", this->m_Data.iExp, this->m_Data.iDrop);
				break;
			}
			// ---
			if(this->m_Time[i].iEndHour == time.wHour && this->m_Time[i].iEndMin == time.wMinute)
			{
				this->m_Data.btRunning = false;
				// ---
				MsgAllUser(0, "[Happy Hour] Evento Finalizado!");
				break;
			}
		}
	}
}