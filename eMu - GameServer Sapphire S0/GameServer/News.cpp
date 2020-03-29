#include "StdAfx.h"
#include "TNotice.h"

CNews gNews;

void CNews::Load()
{
	this->iEnabled	= GetPrivateProfileInt("News", "IsEnabled", NULL, NEWS_FILE);
	this->iSections = GetPrivateProfileInt("News", "IsSections", NULL, NEWS_FILE);
	this->iInterval = GetPrivateProfileInt("News", "IsInterval", NULL, NEWS_FILE) * 60000;
	// ---
	char szBuffer[50] = {0};
	char szTemp[50] = {0};
	// ---
	ZeroMemory(this->m_Data, sizeof(this->m_Data));
	// ---
	for(int i = 1; i <= this->iSections; i++)
    {
        wsprintf(szBuffer, "Section%d", i);
		// ---
        for(int n = 0; n < 3; n++)
        { 
            wsprintf(szTemp, "News%d", n+1);
			// ---
            GetPrivateProfileString(szBuffer, szTemp, NULL, this->m_Data[i].szMessage[n], 150, NEWS_FILE);
        }
    }
	// ---
	_beginthread(this->Init, NULL, NULL);
	// ---
	LogAdd(LOG_GOLD, "[NEWS FILE] Carregado !");
}

void CNews::CheckProcent(char * szMsg)
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
void CNews::Init(LPVOID lpParam)
{
	while(gNews.iEnabled)
    {
        for(int i = 1; i <= gNews.iSections; i++)
        {
			Sleep(gNews.iInterval);
			// ---
            for(int n = 0; n < 3; n++)
            {
				gNews.CheckProcent(gNews.m_Data[i].szMessage[n]);
				// ---
				MsgAllUser(0, gNews.m_Data[i].szMessage[n]);
            }
        }
    }
	// ---
    _endthread();
}