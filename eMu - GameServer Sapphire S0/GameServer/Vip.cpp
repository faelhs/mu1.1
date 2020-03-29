#include "StdAfx.h"
#include "user.h"
#include "ReadScript.h"

CVip gVip;

void CVip::Load()
{
	SMDToken Token;
	SMDFile = fopen(VIP_FILE, "r");
	// --- 
	if(!SMDFile)
	{
		//MsgBox("Arquivo '%s' Não Encontrado !", VIP_FILE);
		ExitProcess(0);
	}
	// ---
	int VipIndex;
	// ---
	char szTemp[100];
	// ---
	memset(szTemp, 0, sizeof(szTemp));
	// ---
	while (true)
	{
		Token = GetToken();
		// ---
		if (Token == END)
		{
			break;
		}
		// ---
		if (Token == NUMBER)
		{
			int Section = TokenNumber;
			// ---
			if (Section == 0)
			{
				while (true)
				{
					Token = GetToken();
					// ---
					if (Token == NAME)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}
					// ---
					VipIndex = TokenNumber;
					// ---
					Token = GetToken();
					memcpy(this->m_Data[VipIndex].iVipName, TokenString, sizeof(this->m_Data[VipIndex].iVipName));
					// ---
					Token = GetToken();
					this->m_Data[VipIndex].iExperience = TokenNumber;
					// ---
					Token = GetToken();
					this->m_Data[VipIndex].iItemDrop = TokenNumber;
				}
			}
		}
	}
	// ---
	LogAdd(LOG_GOLD, "[VIP FILE] Carregado !");
}

char * CVip::GetName(int VipNumber)
{
	if(this->m_Data[VipNumber].iVipName != NULL)
	{
		return m_Data[VipNumber].iVipName;
	}
	// ---
	return "Null";
}

float CVip::GetDropRate(int VipNumber)
{
	if(this->m_Data[VipNumber].iItemDrop != -1)
	{
		return m_Data[VipNumber].iItemDrop;
	}
	// ---
	return 0.0f;
}

float CVip::GetExperience(int VipNumber)
{
	if(this->m_Data[VipNumber].iExperience != -1)
	{
		return m_Data[VipNumber].iExperience;
	}
	// ---
	return 0.0f;
}