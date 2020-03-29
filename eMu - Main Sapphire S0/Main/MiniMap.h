#ifndef _MINI_MAP_H
#define _MINI_MAP_H

class CMiniMap
{
public:
	void Load();
	void ViewType(int Type);
	static void LoadMiniMap();
	// ---
	bool bEnabled;
	bool bSelect;
	int iLastMap;
};

extern CMiniMap gMiniMap;

#endif