#include "StdAfx.h"
#include "DSProtocol.h"
#include "EDSProtocol.h"
#include "TNotice.h"

CToolKit gToolKit;

void CToolKit::Refresh(DWORD aIndex)
{	
	PMSG_REFRESH_CHAR lpMsg = {0};
	// ---
	lpMsg.h.c			= 0xC3;
	lpMsg.h.headcode	= 0xF3;
	lpMsg.h.size		= sizeof(PMSG_REFRESH_CHAR);
	lpMsg.subcode		= 0x03;
	// ---
	lpMsg.MapX			= gObj[aIndex].X;
	lpMsg.MapY			= gObj[aIndex].Y;
	lpMsg.MapNumber		= gObj[aIndex].MapNumber;
	lpMsg.Dir			= gObj[aIndex].Dir;
	lpMsg.Exp			= gObj[aIndex].Experience;
	lpMsg.NextExp		= gObj[aIndex].NextExp;
	lpMsg.LevelUpPoint	= gObj[aIndex].LevelUpPoint;
	lpMsg.Str			= gObj[aIndex].Strength;
	lpMsg.Dex			= gObj[aIndex].Dexterity;
	lpMsg.Vit			= gObj[aIndex].Vitality;
	lpMsg.Energy		= gObj[aIndex].Energy;
	lpMsg.Money			= gObj[aIndex].Money;
	lpMsg.PkLevel		= gObj[aIndex].m_PK_Level;
	lpMsg.Life			= (short)gObj[aIndex].Life;
	lpMsg.MaxLife		= (short)((double)gObj[aIndex].AddLife + gObj[aIndex].MaxLife);
	lpMsg.Mana			= (short)gObj[aIndex].Mana;
	lpMsg.MaxMana		= (short)((double)gObj[aIndex].AddMana + gObj[aIndex].MaxMana);
	lpMsg.CtlCode		= (short)gObj[aIndex].Authority;
	lpMsg.BP			= gObj[aIndex].BP;
	lpMsg.MaxBP			= gObj[aIndex].AddBP + gObj[aIndex].MaxBP;
	lpMsg.Leadership	= gObj[aIndex].Leadership;
	// ---
	DataSend(aIndex, &lpMsg.h.c, (DWORD)lpMsg.h.size);
	// ---
	PMSG_REFRESH_REGEN pMsg = {0};
	// ---
	pMsg.h.c			= 0xC3;
	pMsg.h.headcode		= 0xF3;
	pMsg.h.size			= sizeof(PMSG_REFRESH_REGEN);
	pMsg.subcode		= 0x04;
	// ---
	pMsg.Dir			= gObj[aIndex].Dir;
	pMsg.MapX			= LOBYTE(gObj[aIndex].X);
	pMsg.MapY			= LOBYTE(gObj[aIndex].Y);
	pMsg.Life			= (float)gObj[aIndex].Life;
	pMsg.Mana			= (float)gObj[aIndex].Mana;
	pMsg.Exp			= gObj[aIndex].Experience;
	pMsg.MapNumber		= gObj[aIndex].MapNumber;
	pMsg.Money			= gObj[aIndex].Money;
	pMsg.BP				= LOWORD(gObj[aIndex].BP);
	// ---
	gObj[aIndex].PathCount = 0;
	// ---
	DataSend(aIndex, &pMsg.h.c, (DWORD)pMsg.h.size);
	// ---
	gObjTeleport(aIndex,gObj[aIndex].MapNumber,gObj[aIndex].X,gObj[aIndex].Y);
	// ---
	GCItemListSend(aIndex);
	// ---
	GCMagicListMultiSend(&gObj[aIndex],0);
	// ---
	CGRequestQuestInfo(aIndex);
	// ---
	DGGuildMemberInfoRequest(aIndex);
	// ---
	FriendListRequest(aIndex);
	// ---
	gObjCalCharacter(aIndex);
}

void CToolKit::SendMsg(int iColor, char * szMsg, ...)
{
	switch(iColor)
	{
	case 1:
		ChatMsgSend("~%s", szMsg);
		break;
	case 2:
		ChatMsgSend("@%s", szMsg);
		break;
	case 3:
		ChatMsgSend("@@%s", szMsg);
	    break;
	default:
		ChatWisperServer("%s", szMsg);
		break;
	}
}

char * CToolKit::GetMapName(int iMapNumber)
{
	switch(iMapNumber)
	{
	case MAP_INDEX_LORENCIA:
		return "Lorencia";
		// ---
	case MAP_INDEX_DUNGEON:
		return "Dungeon";
		// ---
	case MAP_INDEX_DEVIAS:
		return "Devias";
		// ---
	case MAP_INDEX_NORIA:
		return "Noria";
		// ---
	case MAP_INDEX_LOSTTOWER:
		return "Losttower";
		// ---
	case MAP_INDEX_RESERVED:
		return "Null";
		// ---
	case MAP_INDEX_BATTLESOCCER:
		return "Arena";
		// ---
	case MAP_INDEX_ATHLANSE:
		return "Atlans";
		// ---
	case MAP_INDEX_TARKAN:
		return "Tarkan";
		// ---
	case MAP_INDEX_DEVILSQUARE:
		return "Devil Square";
		// ---
	case MAP_INDEX_ICARUS:
		return "Icarus";
		// ---
	case MAP_INDEX_BLOODCASTLE1:
		return "Blood Castle 1";
		// ---
	case MAP_INDEX_BLOODCASTLE2:
		return "Blood Castle 2";
		// ---
	case MAP_INDEX_BLOODCASTLE3:
		return "Blood Castle 3";
		// ---
	case MAP_INDEX_BLOODCASTLE4:
		return "Blood Castle 4";
		// ---
	case MAP_INDEX_BLOODCASTLE5:
		return "Blood Castle 5";
		// ---
	case MAP_INDEX_BLOODCASTLE6:
		return "Blood Castle 6";
		// ---
	case MAP_INDEX_BLOODCASTLE7:
		return "Blood Castle 7";
		// ---
	case MAP_INDEX_CHAOSCASTLE1:
		return "Chaos Castle 1";
		// ---
	case MAP_INDEX_CHAOSCASTLE2:
		return "Chaos Castle 2";
		// ---
	case MAP_INDEX_CHAOSCASTLE3:
		return "Chaos Castle 3";
		// ---
	case MAP_INDEX_CHAOSCASTLE4:
		return "Chaos Castle 4";
		// ---
	case MAP_INDEX_CHAOSCASTLE5:
		return "Chaos Castle 5";
		// ---
	case MAP_INDEX_CHAOSCASTLE6:
		return "Chaos Castle 6";
		// ---
	case MAP_INDEX_KALIMA1:
		return "Kalima 1";
		// ---
	case MAP_INDEX_KALIMA2:
		return "Kalima 2";
		// ---
	case MAP_INDEX_KALIMA3:
		return "Kalima 3";
		// ---
	case MAP_INDEX_KALIMA4:
		return "Kalima 4";
		// ---
	case MAP_INDEX_KALIMA5:
		return "Kalima 5";
		// ---
	case MAP_INDEX_KALIMA6:
		return "Kalima 6";
		// ---
	case MAP_INDEX_CASTLESIEGE:
		return "Valley of Loren";
		// ---
	case MAP_INDEX_CASTLEHUNTZONE:
		return "Land of Trial";
		// ---
	case MAP_INDEX_AIDA:
		return "Aida";
	}
	// ---
	return "Null";
}

float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float fDefault, LPCSTR lpFileName)
{
	char szBuffer[256] = {0};
	char szDefault[256] = {0};
	// ---
	float fValue;
	// ---
	sprintf(szDefault, "%f", fDefault);
	// ---
	GetPrivateProfileStringA(lpAppName, lpKeyName, szDefault, szBuffer, 256, lpFileName);
	// ---
    fValue = atof(szBuffer); 
	// --
    return fValue; 
}

int CToolKit::ExcOpt(int amount)
{
	if (amount > 6) amount = 6;
	if (amount < 1) amount = 1;

	srand(time(NULL));

	amount = rand() % amount + 1;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	int opt_done[6] = { 0 };

	for(int n=0; n < amount; n++)
	{
		int SearchExc = 0;

		srand(time(NULL));

		if( n == 0 )
		{
			SearchExc = opt_db[rand()%6];
			opt_done[n] = SearchExc;
		}
		else
		{
			while(true)
			{
				SearchExc = opt_db[rand()%6];
				bool bOpt = true;

				for(int i=0; i<amount; i++)
				{
					if(SearchExc == opt_done[i])
					{
						bOpt = false;
					}
				}

				if(bOpt == true)
				{
					opt_done[n] = SearchExc;
					break;
				}
			}
		}

		exc += SearchExc;
	}

	return exc;
}