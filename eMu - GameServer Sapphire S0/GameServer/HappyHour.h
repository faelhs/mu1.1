#ifndef _HAPPYHOUR_H
#define _HAPPYHOUR_H

struct HAPPY_HOUR_TIME
{
	int iHour;
	int iEndHour;
	int iMin;
	int iEndMin;
};

struct HAPPY_HOUR_DATA
{
	int iEnabled;
	int iExp;
	int iDrop;
	// ---
	bool btRunning;
};

class CHappyHour
{
public:
	void Load();
	void TimeTick();
	// ---
	int iCount;
	// ---
	HAPPY_HOUR_DATA m_Data;
	HAPPY_HOUR_TIME m_Time[255];
};

extern CHappyHour gHappyHour;

#endif