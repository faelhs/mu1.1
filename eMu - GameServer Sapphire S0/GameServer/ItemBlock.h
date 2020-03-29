#ifndef _ITEM_BLOCK_H
#define _ITEM_BLOCK_H
// ---
#define MAX_ITEM_BLOCK 100
// ---
#define TRADE_BOX_SIZE 32
// ---
struct ITEM_BLOCK_DATA
{
	int Type;
	int ID;
	int Level;
};
// ---
class CItemBlock
{
public:
	void Load();
	bool IsEnableToTrade(LPOBJ lpObj);
	bool IsCheckItem(CItem * pItem);
	// ---
	int iCount;
	// ---
	ITEM_BLOCK_DATA m_Data[MAX_ITEM_BLOCK];
};
// ---
extern CItemBlock gItemBlock;
// ---
#endif