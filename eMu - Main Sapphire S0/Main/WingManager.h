#ifndef _WING_MANAGER_H
#define _WING_MANAGER_H

class CWingManager
{
public:
	void Load();
	// ---
	static void MakePreviewCharSet(int aIndex, BYTE * CharSet, int PreviewObject, int Mode, int Agr5, int Agr6, int Agr7);
	static void AddExcellentStatus_Lv2();
	static void Add28Option();
};

extern CWingManager gWingManager;

#endif