#include "stdafx.h"
#include "ItemBagEx.h"
#include "gObjMonster.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "..\include\readscript.h"
#include "winutil.h"
#include "Log.h"
// GS-N 0.99.60T 0x0046A030
//	GS-N	1.00.18	JPN	0x0047CAA0	-	Completed
//	GS-CS	1.00.18	JPN	0x0047CAA0	-	Completed

CItemBagEx::CItemBagEx()
{
	return;
}

CItemBagEx::~CItemBagEx()
{
	return;
}

void CItemBagEx::Init(char* name)
{
	this->m_bLoad = FALSE;
	this->m_sEventName[0] = 0;
	this->m_iEventItemType = -1;
	this->m_iEventItemLevel = 0;
	this->m_iDropZen = 0;
	this->m_iEventItemDropRate = 0;
	this->m_iItemDropRate = 0;
	this->m_iExItemDropRate = 0;
	this->m_iBagObjectCount = 0;

	this->LoadItem(gDirPath.GetNewPath(name));
}

void CItemBagEx::LoadItem(char* script_file)
{
	int Token;

	this->m_bLoad = FALSE;
	SMDFile = fopen(script_file, "r");

	if ( SMDFile == NULL )
	{
		LogAdd(LOG_BLACK, lMsg.Get(MSGGET(1, 197)), script_file);
		return;
	}

	int n=0;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			int st = TokenNumber;	// script_type

			if ( st == 0 )
			{
				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					int map = TokenNumber;

					if ( MAX_MAP_RANGE(map) == FALSE )
					{
						MsgBox("ExEvent ItemBag LoadFail [%s]", script_file);
						return;
					}

					Token = GetToken();
					this->DropMapInfo[map].m_bIsDrop = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MinMonsterLevel = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MaxMonsterLevel = TokenNumber;
				}
			
			}
			else if ( st == 1 )
			{
				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					strcpy(this->m_sEventName, TokenString);

					Token = GetToken();
					this->m_iDropZen = TokenNumber;

					Token = GetToken();
					int type = TokenNumber;

					Token = GetToken();
					int index = TokenNumber;

					this->m_iEventItemType = ITEMGET(type, index);

					Token = GetToken();
					this->m_iEventItemLevel = TokenNumber;

					Token = GetToken();
					this->m_iEventItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iExItemDropRate = TokenNumber;

					char szTemp[256];

					wsprintf(szTemp, "[%s] Eventitemnum = %d,EventItemLevel = %d, EventItemDropRate = %d, ItemDropRate = %d, ExItemDropRate = %d",
						this->m_sEventName, this->m_iEventItemType, this->m_iEventItemLevel, this->m_iEventItemDropRate, this->m_iItemDropRate, this->m_iExItemDropRate);
					LogAdd(LOG_BLACK, szTemp);
				}
			}
			else if ( st == 2 )
			{
				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					this->BagObject[n].m_type = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_index = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_minLevel = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_maxLevel = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isskill = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isluck = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isoption = TokenNumber;

					Token = GetToken();
					this->BagObject[n].m_isexitem = TokenNumber;

					n++;
					this->m_iBagObjectCount++;

					if ( this->m_iBagObjectCount > MAX_ITEMBAG_ATTR-1 )
					{
						break;
					}
				}
			}
		}
	}

	fclose(SMDFile);
	LogAdd(LOG_BLACK, lMsg.Get(MSGGET(1, 198)), script_file);
	this->m_bLoad = TRUE;
}


BYTE CItemBagEx::GetLevel(int n)
{
	if ( n <0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	if ( this->BagObject[n].m_minLevel == this->BagObject[n].m_maxLevel )
	{
		return this->BagObject[n].m_minLevel;
	}

	int sub = (this->BagObject[n].m_maxLevel - this->BagObject[n].m_minLevel) + 1;
	int level = this->BagObject[n].m_minLevel + (rand()%sub);

	return level;
}

BOOL CItemBagEx::IsEnableEventItemDrop(int aIndex)
{
	int iMapNumber = gObj[aIndex].MapNumber;

	if ( this->DropMapInfo[iMapNumber].m_bIsDrop == FALSE )
	{
		return FALSE;
	}

	int iLevel = gObj[aIndex].Level;

	if  ( iLevel < this->DropMapInfo[iMapNumber].m_MinMonsterLevel || iLevel > this->DropMapInfo[iMapNumber].m_MaxMonsterLevel)
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CItemBagEx::DropEventItem(int aIndex)
{
	if ( this->m_bLoad == FALSE )
	{
		return FALSE;
	}

	if ( this->IsEnableEventItemDrop(aIndex) == FALSE )
	{
		return FALSE;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if ( (rand()%1000) < this->m_iEventItemDropRate )
	{
		int ei;
		int eil;
		int x;
		int y;
		float dur = 0;
		dur = 255.0;

		x = lpObj->X;
		y = lpObj->Y;
		eil = this->m_iEventItemLevel;
		ei = this->m_iEventItemType;

		int thdu = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x ,y, ei, eil, dur, 0, 0, 0, thdu, 0, 0);
		LogAdd(LOG_BLACK, "[%s][%s] [%s] MonsterEventItemDrop (%d)(%d/%d)", lpObj->AccountID, lpObj->Name, 
			this->m_sEventName, lpObj->MapNumber, x, y);
		return TRUE;
	}

	return FALSE;
}


BOOL CItemBagEx::DropItem(int aIndex)
{
	if ( this->m_bLoad == FALSE )
	{
		return FALSE;
	}

	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;
	LPOBJ lpObj = &gObj[aIndex];

	if ( this->GetBagCount() > 0 )
	{
		if ( (rand()%100) < this->m_iItemDropRate )
		{
			DropItemNum =  rand() % this->GetBagCount();
			dur = 0;
			x = lpObj->X;
			y = lpObj->Y;
			level = this->GetLevel(DropItemNum);
			type = ItemGetNumberMake(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);

			if ( type == -1 )
			{
				return FALSE;
			}

			if ( this->BagObject[DropItemNum].m_isskill != 0 )
			{
				Option1 = rand()%2;
			}

			if ( this->BagObject[DropItemNum].m_isluck != 0 )
			{
				Option2 = rand()%2;
			}

			if ( this->BagObject[DropItemNum].m_isoption != 0 )
			{
				if ( rand()%5 < 1 )
				{
					Option3 = 3;
				}
				else
				{
					Option3 = rand()%3;
				}
			}

			if ( this->BagObject[DropItemNum].m_isexitem != 0 )
			{
				ExOption = NewOptionRand(0);
				Option1 = 1;
			}

			if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14))	// Chaos, Bless, Soul
			{
				Option1 = 0;
				Option2 = 0;
				Option3 = 0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) || type == ITEMGET(13,1) || type ==ITEMGET(13,2) ||
				 type == ITEMGET(13,8) || type == ITEMGET(13,9) || type == ITEMGET(13,12) ||
				 type ==ITEMGET(13,13) )	// Angel, imp, unirioa, dino, r and pendant of ice, poisonm
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);
			LogAdd(LOG_BLACK, "[%s][%s] [%s] Event ItemDrop : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d",
				lpObj->AccountID, lpObj->Name, this->m_sEventName, lpObj->MapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3);
			return TRUE;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, x, y);
	return TRUE;
}


BYTE CItemBagEx::GetMinLevel(int n)
{
	if ( n<0 || n > MAX_ITEMBAG_ATTR-1 )
		return 0;

	return this->BagObject[n].m_minLevel;
}

BYTE CItemBagEx::GetMaxLevel(int n)
{
	if ( n<0 || n > MAX_ITEMBAG_ATTR-1 )
		return 0;

	return this->BagObject[n].m_maxLevel;
}


BOOL CItemBagEx::PickItem(CItem & objItem, int & nItemIndex)
{
	if ( this->m_bLoad == FALSE )
		return FALSE;

	int DropItemNum;

	if ( this->GetBagCount() > 0 )
	{
		DropItemNum = rand() % this->GetBagCount();
		nItemIndex = DropItemNum;
		objItem.m_Type = ItemGetNumberMake(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);
		objItem.m_Level = this->GetLevel(DropItemNum);

		if ( objItem.m_Type == -1 )
			return FALSE;

		if ( this->BagObject[DropItemNum].m_isskill != 0 )
			objItem.m_Option1 = 1;

		if ( this->BagObject[DropItemNum].m_isluck != 0 )
			objItem.m_Option2 = 1;

		if ( this->BagObject[DropItemNum].m_isoption != 0 )
			objItem.m_Option3 = 1;

		if ( this->BagObject[DropItemNum].m_isexitem != 0 )
		{
			objItem.m_NewOption = 1;
			objItem.m_Option1 = 0;
			objItem.m_Option2 = 0;
		}

		if ( objItem.m_Type == ITEMGET(12,15) ||
			 objItem.m_Type == ITEMGET(14,13) ||
			 objItem.m_Type == ITEMGET(14,14) )
		{
			objItem.m_Option1 = 0;
			objItem.m_Option2 = 0;
			objItem.m_Option3 = 0;
			objItem.m_Level = 0;
		}

		if ( objItem.m_Type == ITEMGET(13,0) ||
			 objItem.m_Type == ITEMGET(13,1) ||
			 objItem.m_Type == ITEMGET(13,2) ||
			 objItem.m_Type == ITEMGET(13,8) ||
			 objItem.m_Type == ITEMGET(13,9) ||
			 objItem.m_Type == ITEMGET(13,12) ||
			 objItem.m_Type == ITEMGET(13,13) )
		{
			objItem.m_Level = 0;
		}

		objItem.m_Durability = 0;

		return TRUE;
	}

	return FALSE;
}

BOOL CItemBagEx::DropKundunEventItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if ( this->m_bLoad == FALSE )
	{
		return FALSE;
	}

	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int iItemBagCount = this->GetBagCount();

	for(int i=0;i<iItemBagCount;i++)
	{
		type = ItemGetNumberMake(this->BagObject[i].m_type, this->BagObject[i].m_index);

		LogAdd(LOG_BLACK, "[¡ÛKUNDUN EVENT][KUNDUN ITEM BAG LIST] Item:(%s)%d Level:%d-%d op1:%d op2:%d op3:%d expo:%d",
			ItemAttribute[type].Name, type, this->BagObject[i].m_minLevel, BagObject[i].m_maxLevel,
			BagObject[i].m_isskill, BagObject[i].m_isluck, BagObject[i].m_isoption, BagObject[i].m_isexitem);
	}

	if ( this->GetBagCount() > 0 )
	{
		if ( true )
		{
			DropItemNum =  rand() % this->GetBagCount();
			dur = 0;
			
			if ( cX == 0 && cY == 0 )
			{
				x = lpObj->X;
				y = lpObj->Y;
			}
			else
			{
				x = cX;
				y = cY;
			}

			level = this->GetLevel(DropItemNum);
			type = ItemGetNumberMake(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);

			if ( type == -1 )
			{
				return FALSE;
			}

			if ( this->BagObject[DropItemNum].m_isskill != 0 )
			{
				Option1 =1;
			}

			if ( this->BagObject[DropItemNum].m_isluck != 0 )
			{
				Option2 = 0;

				if ( (rand()%2) == 0 )
				{
					Option2 = 1;
				}
			}

			if ( this->BagObject[DropItemNum].m_isoption != 0 )
			{
				if ( rand()%5 < 1 )
				{
					Option3 = 3;
				}
				else
				{
					Option3 = rand()%3;
				}
			}

			if ( this->BagObject[DropItemNum].m_isexitem != 0 )
			{
				ExOption = NewOptionRand(0);
				Option2 = 0;
				Option1 = 1;
			}

			if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14))	// Chaos, Bless, Soul
			{
				Option1 = 0;
				Option2 = 0;
				Option3 = 0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type ==ITEMGET(13,13) )	// Angel, imp, unirioa, dino, r and pendant of ice, poisonm
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);

			LogAdd(LOG_BLACK, "[¡ÛKundun EVENT] ¡ÚKUNDUN Event ItemDrop [%s][%s] [%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d",
				lpObj->AccountID, lpObj->Name, this->m_sEventName, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3);
			return TRUE;
		}
	}

	return TRUE;
}

#if GS_CASTLE == 1
BOOL CItemBagEx::DropCastleHuntZoneBossReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if ( this->m_bLoad == FALSE )
	{
		return FALSE;
	}

	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;
	LPOBJ lpObj = &gObj[aIndex];

	if ( this->GetBagCount() > 0 )
	{
		while ( true )
		{
			DropItemNum = rand() % this->GetBagCount();
			dur = 0;

			if ( cX == 0 && cY == 0 )
			{
				x = lpObj->X;
				y = lpObj->Y;
			}
			else
			{
				x = cX;
				y = cY;
			}

			level = this->GetLevel(DropItemNum);
			type = ItemGetNumberMake(this->BagObject[DropItemNum].m_type, this->BagObject[DropItemNum].m_index);

			if ( type == -1 )
				return FALSE;

			if ( this->BagObject[DropItemNum].m_isskill != 0 )
				Option1 = 1;

			if ( this->BagObject[DropItemNum].m_isluck != 0 )
			{
				Option2 = 0;

				if ( (rand()%2) == 0 )
				{
					Option2 = 1;
				}
			}

			if ( this->BagObject[DropItemNum].m_isoption != 0 )
			{
				if ( (rand()%5) < 1 )
				{
					Option3 = 3;
				}
				else
				{
					Option3 = rand() % 3;
				}
			}

			if ( this->BagObject[DropItemNum].m_isexitem )
			{
				ExOption = NewOptionRand(0);
				Option2 = 0;
				Option1 = 1;
			}

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14)  )
			{
				Option1 = 0;
				Option2 = 0;
				Option3 = 0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}
			
			ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);

			LogAdd(LOG_BLACK, "[Castle HuntZone] ¡ÚCastle HuntZone Boss ItemDrop [%s][%s] [%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d",
				lpObj->AccountID, lpObj->Name, this->m_sEventName,
				btMapNumber, x, y, ItemAttribute[type].Name,
				type, level, Option1, Option2, Option3);

			return TRUE;
		}
	}

	return TRUE;
}
#endif