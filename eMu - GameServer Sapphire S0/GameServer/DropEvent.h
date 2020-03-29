#ifndef _DROP_EVENT_H
#define _DROP_EVENT_H

#define DROP_EVENT_MAX	256

struct DROPEVENT_DATA
{
	int Map;
	int X;
	int Y;
	int Hour;
	int Min;
};

struct DROPEVENT_ITEM_DATA
{
	int Index;
	int Type;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exc;
	int Anc;
};

class CDropEvent
{
public:
	void Load();
	void Init();
	void TimeTick();
	// ---
	int iEnabled;
	// ---
	int iCount[4];
	// ---
	DROPEVENT_DATA m_Data[DROP_EVENT_MAX];
	DROPEVENT_ITEM_DATA m_Item[DROP_EVENT_MAX];
};

extern CDropEvent gDropEvent;

#endif