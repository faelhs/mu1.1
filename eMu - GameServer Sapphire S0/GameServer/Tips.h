#ifndef _TIPS_H
#define _TIPS_H

#define MAX_TIPS 50

struct TIPS_DATA
{
	int iColor;
	char szMessage[150];
};

class CTips
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
	TIPS_DATA m_Data[MAX_NEWS];
};

extern CTips gTips;

#endif