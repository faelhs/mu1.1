#ifndef _INTERFACE_H
#define _INTERFACE_H

class CInterface
{
public:
	void Load();
	static void Work();
	void CordRun();
	// ---
	void DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
	void LoadImage(int Type, char * Folder, int ImageID);
};

extern CInterface gInterface;

#endif