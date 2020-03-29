#ifndef _PLUGINS_H
#define _PLUGINS_H

#define MAX_PLUGINS 50

struct PLUGIN_INFO_DATA
{
	int Index;
	char dwName[50];
	char dwApi[50];
};

class CPlugins
{
public:
	void Load();
	void CheckFile(int aIndex);
	// ---
	int iCount;
	// ---
	PLUGIN_INFO_DATA m_Data[MAX_PLUGINS];
};

extern CPlugins gPlugins;

#endif