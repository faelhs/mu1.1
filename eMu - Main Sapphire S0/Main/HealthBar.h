#ifndef _HEALTH_BAR_H
#define _HEALTH_BAR_H

#include "Packets.h"

#define MAX_VIEWPORT_MOBS 400

struct HEALTH_BAR_DATA
{
	int Class;
	bool Live;
	float Life;
	float MaxLife;
	float LifePercent;
	int Level;
};

struct PMSG_HEALTH_BAR_RECV
{
	PBMSG_HEAD2	h;
	int	NumberH;
	int NumberL;
	int Level;
	float Life;
	int MaxLife;
	int Class;
};

class CHealthBar
{
public:
	void Load();
	// ---
	void Info(PMSG_HEALTH_BAR_RECV * aRecv);
	static void DrawBar();
private:
	HEALTH_BAR_DATA m_Data[1000];
};

extern CHealthBar gHealthBar;

#endif