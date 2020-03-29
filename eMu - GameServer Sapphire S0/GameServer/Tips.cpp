#include "StdAfx.h"
#include "TNotice.h"

CTips gTips;

void CTips::Load()
{
	this->iEnabled	= GetPrivateProfileInt("Tips", "IsEnabled", NULL, TIPS_FILE);
	this->iSections = GetPrivateProfileInt("Tips", "IsSections", NULL, TIPS_FILE);
	this->iInterval = GetPrivateProfileInt("Tips", "IsInterval", NULL, TIPS_FILE) * 60000;
	// ---
	char szBuffer[50] = {0};
	// ---
	ZeroMemory(this->m_Data, sizeof(this->m_Data));
	// ---
	for(int i = 1; i <= this->iSections; i++)
    {
        wsprintf(szBuffer, "Section%d", i);
		// ---
        GetPrivateProfileString(szBuffer, "String", NULL, this->m_Data[i].szMessage, 150, TIPS_FILE);
		this->m_Data[i].iColor	= GetPrivateProfileInt(szBuffer, "Color", NULL, TIPS_FILE);
    }
	// ---
	_beginthread(this->Init, NULL, NULL);
	// ---
	LogAdd(LOG_GOLD, "[TIPS FILE] Carregado !");
}

void CTips::CheckProcent(char * szMsg)
{
	for(int i = 0; i <= strlen(szMsg); i++)
	{                          						   
		if(szMsg[i] == '%')		  
		{
			for(int x = strlen(szMsg); x >= i; x--)	
			{
				szMsg[x + 1] = szMsg[x];
			}
			// ---
			i++;
		}
	}
}
void CTips::Init(LPVOID lpParam)
{
	while(gTips.iEnabled)
    {
        for(int i = 1; i <= gTips.iSections; i++)
        {
			Sleep(gTips.iInterval);
			// ---
			gTips.CheckProcent(gTips.m_Data[i].szMessage);
			// ---
			gToolKit.SendMsg(gTips.m_Data[i].iColor, gTips.m_Data[i].szMessage);
        }
    }
	// ---
    _endthread();
}