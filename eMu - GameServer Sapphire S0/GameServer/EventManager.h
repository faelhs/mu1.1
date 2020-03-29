#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

struct EVENT_DATA_INFO
{
	char szSintax[50];
	char szEnter[50];
	// ---
	int iMap;
	int iCordX;
	int iCordY;
	int iTime;
	// ---
	bool bMove;
	bool bEventOn;
};

class CEventManager
{
public:
	void CommandInit(int aIndex, char * szMsg);
	void CommandEnter(int aIndex);
	static void TimeTick(LPVOID lpParam);
	// ---
	EVENT_DATA_INFO m_Data;
};

extern CEventManager gEventManager;

#endif