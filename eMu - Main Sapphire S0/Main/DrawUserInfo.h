#ifndef _DRAW_USER_INFO_H
#define _DRAW_USER_INFO_H

struct DRAW_USER_DATA
{
	bool bEnabled;
	bool bSelect;
	bool bLayout;
	bool bWindow;
};

class CDrawUserInfo
{
public:
	void Run();
	void InitView();
	// ---
	DRAW_USER_DATA m_Data;
};

extern CDrawUserInfo gDrawUserInfo;

#endif