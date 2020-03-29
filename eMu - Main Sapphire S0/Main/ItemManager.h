#ifndef _ITEM_MANAGER_H
#define _ITEM_MANAGER_H

enum Color
{
	White	   = 0x00,
	Blue	   = 0x01,
	Red		   = 0x02,
	Gold	   = 0x03,
	Green	   = 0x04,
	WhiteRed   = 0x05,
	Violet	   = 0x06,
	WhiteBlue  = 0x07,
	WhiteBeige = 0x08,
	GreenBlue  = 0x09,
	Gray	   = 0x0A,
	DarkViolet = 0x0B,
};

enum Font
{
	Bold	   = 0x01,
	Normal     = 0x00,
};

class CItemManager
{
public:
	void Load();
	// ---
	char szSet[30];
	char szItem[15];
	// ---
	void TextColor(char * Text, int Color, int Weight, ...);
	// ---
	static void LoadTitleColor();
	static void LoadJewelUpgrade();
	static void LoadJewelApply();
	static void LoadDescription();
	static void LoadModels();
	static void LoadTextures();
};

extern CItemManager gItemManager;

#endif