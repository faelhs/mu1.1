#ifndef _NEWS_H
#define _NEWS_H

#define MAX_NEWS 50

struct NEWS_DATA
{
	char szMessage[3][150];
};

class CNews
{
public:
	void Load();
	void CheckProcent(char * szMsg);
	static void Init(LPVOID lpParam);
	// ---
	int iEnabled;
	int iSections;
	int iInterval;
	// ---
	NEWS_DATA m_Data[MAX_NEWS];
};

extern CNews gNews;

#endif