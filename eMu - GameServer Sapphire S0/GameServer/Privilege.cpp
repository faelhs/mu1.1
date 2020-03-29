#include "StdAfx.h"
#include "TNotice.h"
#include "GameMain.h"
#include "Shop.h"
#include "DSProtocol.h"

CPrivilege gPrivilege;

void CPrivilege::Load()
{
	this->iCount = 0;
	// ---
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	Tokenizer          token;
	TokenizerGroup     Class;
	TokenizerSection   Section;
	// ---
	token.ParseFile(std::string(PRIVILEGE_FILE), Class);
	// ---	
	if(Class.GetSection(0, Section))
	{	
		for(int i = 0; i < Section.RowCount; i++)
		{
			strcpy_s(this->m_Data[this->iCount].szName, sizeof(this->m_Data[this->iCount].szName), (Section.Rows[i].GetStringPtr(0)));
			// ---
			this->m_Data[this->iCount].iType							= Section.Rows[i].GetInt(1);
			this->m_Data[this->iCount].iCommand[COMMAND_RELOAD]			= Section.Rows[i].GetInt(2);
			this->m_Data[this->iCount].iCommand[COMMAND_DISCONNECT]		= Section.Rows[i].GetInt(3);
			this->m_Data[this->iCount].iCommand[COMMAND_BLOCK]			= Section.Rows[i].GetInt(4);
			this->m_Data[this->iCount].iCommand[COMMAND_UNBLOCK]		= Section.Rows[i].GetInt(5);
			this->m_Data[this->iCount].iCommand[COMMAND_SKIN]			= Section.Rows[i].GetInt(6);
			this->m_Data[this->iCount].iCommand[COMMAND_MAKE]			= Section.Rows[i].GetInt(7);
			this->m_Data[this->iCount].iCommand[COMMAND_GMOVE]			= Section.Rows[i].GetInt(8);
			this->m_Data[this->iCount].iCommand[COMMAND_MOVEALL]		= Section.Rows[i].GetInt(9);
			this->m_Data[this->iCount].iCommand[COMMAND_REWARD]			= Section.Rows[i].GetInt(10);
			this->m_Data[this->iCount].iCommand[COMMAND_SETLEVEL]		= Section.Rows[i].GetInt(11);
			this->m_Data[this->iCount].iCommand[COMMAND_SETZEN]			= Section.Rows[i].GetInt(12);
			this->m_Data[this->iCount].iCommand[COMMAND_SETPK]			= Section.Rows[i].GetInt(13);
			this->m_Data[this->iCount].iCommand[COMMAND_SETDROP]		= Section.Rows[i].GetInt(14);
			this->m_Data[this->iCount].iCommand[COMMAND_HIDE]			= Section.Rows[i].GetInt(15);
			// ---
			this->iCount++;
		}
	}
	// ---
	GetPrivateProfileString("Commands", "Command_Reload_Sintax", NULL, this->m_Data[COMMAND_RELOAD].szSintax, sizeof(this->m_Data[COMMAND_RELOAD].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Disconnect_Sintax", NULL, this->m_Data[COMMAND_DISCONNECT].szSintax, sizeof(this->m_Data[COMMAND_DISCONNECT].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Block_Sintax", NULL, this->m_Data[COMMAND_BLOCK].szSintax, sizeof(this->m_Data[COMMAND_BLOCK].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_UnBlock_Sintax", NULL, this->m_Data[COMMAND_UNBLOCK].szSintax, sizeof(this->m_Data[COMMAND_UNBLOCK].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Skin_Sintax", NULL, this->m_Data[COMMAND_SKIN].szSintax, sizeof(this->m_Data[COMMAND_SKIN].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Make_Sintax", NULL, this->m_Data[COMMAND_MAKE].szSintax, sizeof(this->m_Data[COMMAND_MAKE].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_GMMove_Sintax", NULL, this->m_Data[COMMAND_GMOVE].szSintax, sizeof(this->m_Data[COMMAND_GMOVE].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_MoveAll_Sintax", NULL, this->m_Data[COMMAND_MOVEALL].szSintax, sizeof(this->m_Data[COMMAND_MOVEALL].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Reward_Sintax", NULL, this->m_Data[COMMAND_REWARD].szSintax, sizeof(this->m_Data[COMMAND_REWARD].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_SetZen_Sintax", NULL, this->m_Data[COMMAND_SETZEN].szSintax, sizeof(this->m_Data[COMMAND_SETZEN].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_SetLevel_Sintax", NULL, this->m_Data[COMMAND_SETLEVEL].szSintax, sizeof(this->m_Data[COMMAND_SETLEVEL].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_SetPk_Sintax", NULL, this->m_Data[COMMAND_SETPK].szSintax, sizeof(this->m_Data[COMMAND_SETPK].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_SetDrop_Sintax", NULL, this->m_Data[COMMAND_SETDROP].szSintax, sizeof(this->m_Data[COMMAND_SETDROP].szSintax), COMMANDS_FILE);
	GetPrivateProfileString("Commands", "Command_Hide_Sintax", NULL, this->m_Data[COMMAND_HIDE].szSintax, sizeof(this->m_Data[COMMAND_HIDE].szSintax), COMMANDS_FILE);
}
// ---
int CPrivilege::IsCheck(LPOBJ lpObj)
{
	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		for(int i = 0; i < this->iCount; i++)
		{
			if(!strcmp(this->m_Data[i].szName, lpObj->Name))
			{
				LogAdd(LOG_GREEN, "[PRIVILEGE] (%s)(%s) GameMaster Connected.", lpObj->AccountID, lpObj->Name);
				// ---
				switch(this->m_Data[i].iType)
				{
				case 1:
					return 1;
				case 2:
					return 2;
				}
			}
		}
	}
	// ---
	return -1;
}
// ---
bool CPrivilege::IsCommand(LPOBJ lpObj, int Command)
{
	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		for(int i = 0; i < this->iCount; i++)
		{
			if(!strcmp(this->m_Data[i].szName, lpObj->Name))
			{
				switch(Command)
				{
				case 0:
					return this->m_Data[i].iCommand[COMMAND_RELOAD];
				case 1:
					return this->m_Data[i].iCommand[COMMAND_DISCONNECT];
				case 2:
					return this->m_Data[i].iCommand[COMMAND_BLOCK];
				case 3:
					return this->m_Data[i].iCommand[COMMAND_UNBLOCK];
				case 4:
					return this->m_Data[i].iCommand[COMMAND_SKIN];
				case 5:
					return this->m_Data[i].iCommand[COMMAND_MAKE];
				case 6:
					return this->m_Data[i].iCommand[COMMAND_GMOVE];
				case 7:
					return this->m_Data[i].iCommand[COMMAND_MOVEALL];
				case 8:
					return this->m_Data[i].iCommand[COMMAND_REWARD];
				case 9:
					return this->m_Data[i].iCommand[COMMAND_SETZEN];
				case 10:
					return this->m_Data[i].iCommand[COMMAND_SETLEVEL];
				case 11:
					return this->m_Data[i].iCommand[COMMAND_SETPK];
				case 12:
					return this->m_Data[i].iCommand[COMMAND_SETDROP];
				case 13:
					return this->m_Data[i].iCommand[COMMAND_HIDE];
				}
			}
		}
	}
	// ---
	return false;
}

void CPrivilege::Reload(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_RELOAD))
	{
		return;
	}
	// ---
	int szType;
	// ---
	char *szNone = "NULL";
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "Opções Reload:");
		MsgUser(aIndex, 1, "Opção: <1> Monsters");
		MsgUser(aIndex, 1, "Opção: <2> Shops");
		MsgUser(aIndex, 1, "Opção: <3> Emulator");
		return;
	}
	// ---
	sscanf(szMsg, "%d", &szType);
	// ---
	if(szType < 1 || szType > 10)
	{
		MsgUser(aIndex, 1, "Selecione um numero das opções !");
		return;
	}
	// ---
	switch (szType)
	{
	case 1:
		// ---
		GameMonsterAllCloseAndReLoad();
		// ---
		szNone = "Mobs";
		// ---
		break;
	case 2:
		// ---
		ShopDataLoad();
		// ---
		szNone = "Shops";
		// ---
		break;
	case 3:
		// ---
		gServerInfo.Load();
		// ---
		gVip.Load();
		// ---
		gPrivilege.Load();
		// ---
		gCommands.Load();
		// ---
		gNews.Load();
		// ---
		gTips.Load();
		// ---
		gReset.Load();
		// ---
		gMasterReset.Load();
		// ---
		gMoves.Load();
		// ---
		gHappyHour.Load();
		// ---
		gLottery.Load();
		// ---
		szNone = "Emulator";
		// ---
		break;
	default:
		return;
		break;
	}
	// ---
	MsgUser(aIndex, 1,"[Reload] Opção: %s foi Recarregada!", szNone);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (RELOAD) | Option : (%d) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, szType);
}

void CPrivilege::Disconnect(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_DISCONNECT))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Uso : /dc <name>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1] = {0};
	// ---
	sscanf(szMsg, "%s", &szName);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	CloseClientEx(iTarget);
	// ---
	MsgUser(aIndex, 1, "[%s] %s Foi desconectado ! ", gObj[aIndex].Name, gObj[iTarget].Name);
	// ---
	MsgAllUser(0, "%s Foi desconectado", gObj[iTarget].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (DISCONNECT) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::Block(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_BLOCK))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Uso : /block <name>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1] = {0};
	// ---
	sscanf(szMsg, "%s", &szName);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	gSQLManager.Execute("UPDATE Character SET CtlCode = 1 WHERE Name ='%s'", gObj[iTarget].Name);
	// ---
	CloseClientEx(iTarget);
	// ---
	MsgUser(aIndex, 1, "[%s] %s Foi bloqueado ! ", gObj[aIndex].Name, gObj[iTarget].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (BLOCK) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::UnBlock(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_UNBLOCK))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Uso : /unblock <name>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1] = {0};
	// ---
	sscanf(szMsg, "%s", &szName);
	// ---
	int iTarget = gObjGetIndex(szName); 
	// ---
	gSQLManager.Execute("UPDATE Character SET CtlCode = 0 WHERE Name ='%s'", gObj[iTarget].Name);
	// ---
	CloseClientEx(iTarget);
	// ---
	MsgUser(aIndex, 1, "[%s] %s Foi desbloqueado ! ", gObj[aIndex].Name, gObj[iTarget].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (UNBLOCK) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::Skin(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_SKIN))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Uso : /Skin <name><number>", gObj[aIndex].Name);
		return;
	}
	// ---
	int iSkin = 0;
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	sscanf(szMsg, "%s %d", &szName, &iSkin);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	gObj[iTarget].m_Change = iSkin;
	gObjViewportListProtocolCreate(&gObj[iTarget]);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (SKIN) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::Make(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_MAKE))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Uso : /make <type><index><level><luck><skill><opt><dur><exc><anc>", gObj[aIndex].Name);
		return;
	}
	// ---
	int iType,iIndex,iLevel,iLuck,iSkill,iOpt,iDur,iExe,iAnc = 0;
	// ---
	sscanf(szMsg,"%d %d %d %d %d %d %d %d %d",&iType,&iIndex,&iLevel,&iLuck,&iSkill,&iOpt,&iDur,&iExe,&iAnc);
	// ---
	ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, ITEMGET(iType, iIndex), iLevel, iDur, iSkill, iLuck, iOpt, aIndex, iExe, iAnc);
	//ItemSerialCreateSend(aIndex, 0xEB, 0, 0, ITEMGET(iType, iIndex), iLevel, iDur, iSkill, iLuck, iOpt, aIndex, iExe, iAnc);
	// ---
	MsgUser(aIndex, 1, "[%s] Item criado em seu inventário.", gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (MAKE) | Item (Type : %d | Index : %d) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, iType, iIndex);
}

void CPrivilege::Move(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_GMOVE))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1) 
	{
		MsgUser(aIndex, 1, "Uso : /gmove <name> <map> <x> <y>");
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	int Map, CordX, CordY;
	// ---
	sscanf(szMsg,"%s %d %d %d", &szName, &Map, &CordX, &CordY);
	// ---
	int iIndex = gObjGetIndex(szName);
	// ---
	gObjTeleport(iIndex, Map, CordX, CordY);
	// ---
	MsgUser(aIndex, 1, "[%s] Você foi movido.", gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) Usou o Comando (GMOVE) \n", gObj[aIndex].AccountID, gObj[aIndex].Name);
}

void CPrivilege::MoveAll(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_MOVEALL))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1) 
	{
		MsgUser(aIndex, 1, "Uso : /moveall <map> <x> <y>");
		return;
	}
	// ---
	int Map, X, Y;
	// ---
	sscanf(szMsg,"%d %d %d", &Map, &X, &Y);
	// ---
	for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if(gObj[i].Connected > 2 && gObj[i].Authority == 1)
		{
			gObjTeleport(i, Map, X, Y);
		}
	}
	// ---	
	MsgUser(aIndex, 1, "[%s] Todos os players foram movidos.", gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (MOVEALL) \n", gObj[aIndex].AccountID, gObj[aIndex].Name);
}

void CPrivilege::Reward(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_REWARD))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo: /reward <gold/cash><name><value>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	int iReward = 0;
	// ---
	char szTemp[256] = {0};
	// ---
	sscanf(szMsg, "%s %s %d", &szTemp, &szName, &iReward);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	if(iReward < 0 || iReward > 1000)
	{
		MsgUser(aIndex, 1, "Aviso, Comando Reward Varia de 0 até 1000.", gObj[aIndex].Name);
	}
	// ---
	if(gObj[iTarget].Connected < 3)
	{
		MsgUser(aIndex, 1, "[%s] User %s se encontra offline ou não existe.", gObj[aIndex].Name, gObj[iTarget].Name);
		return;
	}
	// ---
	if(strcmp(szTemp, "gold") == 0)
	{
		gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Gold, gSQLManager.m_Data.Coluna_Gold, gSQLManager.m_Data.Coluna_Gold, iReward, gObj[iTarget].AccountID);
		// ---
		MsgUser(aIndex, 1, "Player %s premiado com %d gold(s).", gObj[iTarget].Name, iReward);
		MsgUser(iTarget, 1, "Você foi premiado com %d gold(s).", iReward);
		// ---
		MsgAllUser(0, "Player %s foi premiado." , szName);
	}
	else if(strcmp(szTemp, "cash") == 0)
	{
		gSQLManager.Execute(gSQLManager.m_Data.Query_Update_Cash, gSQLManager.m_Data.Coluna_Cash, gSQLManager.m_Data.Coluna_Cash, iReward, gObj[iTarget].AccountID);
		// ---
		MsgUser(aIndex, 1, "Player %s premiado com %d cash(s).", gObj[iTarget].Name, iReward);
		MsgUser(iTarget, 1, "Você foi premiado com %d cash(s).", iReward);
		// ---
		MsgAllUser(0, "Player %s foi premiado." , szName);
	}
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (REWARD) | Char : (%s) | Quantia : (%d) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name, iReward);
}

void CPrivilege::SetZen(int aIndex, char * szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_SETZEN))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo: /setzen <name><value>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	DWORD dwZen = 0;
	// ---
	sscanf(szMsg, "%s %d", &szName, &dwZen);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	if(dwZen <= 0 || dwZen > 2000000000)
	{
		MsgUser(aIndex, 1, "[%s] Não pode ser menor do que 1 e mais do que 2000000000!", gObj[aIndex].Name);
		return;
	}
	// ---
	if(gObj[iTarget].Connected < 3)
	{
		MsgUser(aIndex, 1, "Player se encontra offline ou não existe.");
		return;
	}
	// ---
	gObj[iTarget].Money = dwZen;
	// ---
	GCMoneySend(gObj[iTarget].m_Index, dwZen);
	// ---
	MsgUser(aIndex, 1, "[%s] Você alterou o zen do user %s com sucesso.", gObj[aIndex].Name, gObj[iTarget].Name);
	MsgUser(aIndex, 3, "[%s] O seu zen foi alterado por %s.", gObj[iTarget].Name, gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (SETZEN) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::SetLevel(int aIndex, char * szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_SETLEVEL))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo: /setlevel <name><value>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	short sLevel = 0;
	// ---
	sscanf(szMsg, "%s %d", &szName, &sLevel);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	if(sLevel <= 1 || sLevel > 400)
	{
		MsgUser(aIndex, 1, "[%s] Não pode ser menor do que 1 e mais do que 400!", gObj[aIndex].Name);
		return;
	}
	// ---
	if(gObj[iTarget].Connected < 3)
	{
		MsgUser(aIndex, 1, "Player se encontra offline ou não existe.");
		return;
	}
	// ---
	gObj[iTarget].Level = sLevel;
	// ---
	GCLevelUpMsgSend(aIndex, true);
	// ---
	MsgUser(aIndex, 1, "[%s] Você alterou o level do user %s com sucesso.", gObj[aIndex].Name, gObj[iTarget].Name);
	MsgUser(aIndex, 1, "[%s] O seu level foi alterado por %s.", gObj[iTarget].Name, gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (SETLEVEL) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::SetPKLevel(int aIndex, char * szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_SETPK))
	{
		return;
	}
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo: /setpk <name><value>", gObj[aIndex].Name);
		return;
	}
	// ---
	char szName[MAX_ACCOUNT_LEN+1];
	// ---
	int PKLevel = 0;
	// ---
	sscanf(szMsg, "%s %d", &szName, &PKLevel);
	// ---
	int iTarget = gObjGetIndex(szName);
	// ---
	if(PKLevel <= 0 || PKLevel > 100)
	{
		MsgUser(aIndex, 1, "[%s] Não pode ser menor do que 1 e mais do que 100!", gObj[aIndex].Name);
		return;
	}
	// ---
	if(gObj[iTarget].Connected < 3)
	{
		MsgUser(aIndex, 1, "Player se encontra offline ou não existe.");
		return;
	}
	// ---
	gObj[iTarget].m_PK_Level = PKLevel;
	// ---
	if (PKLevel >= 3)
	{
		gObj[iTarget].m_PK_Count = PKLevel - 3;
	}
	// ---
	GCPkLevelSend(gObj[iTarget].m_Index, PKLevel);
	// ---
	GCLevelUpMsgSend(aIndex, true);
	// ---
	MsgUser(aIndex, 1, "[%s] Você alterou o PK do user %s com sucesso.", gObj[aIndex].Name, gObj[iTarget].Name);
	MsgUser(aIndex, 1, "[%s] O seu PK foi alterado por %s.", gObj[iTarget].Name, gObj[aIndex].Name);
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (SETPK) | Char : (%s) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, gObj[iTarget].Name);
}

void CPrivilege::SetDrop(int aIndex, char *szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_SETDROP))
	{
		return;
	} 
	// ---
	if(strlen(szMsg) < 1) 
	{
		MsgUser(aIndex, 1, "Uso : /setdrop <id> <level> <luck> <opt> <exc>");
		return;
	}
	// ---
	int iIndex = 0,
	iLevel = 0,
	iDur   = 255,
	iSkill = 0,
	iLuck  = 0,
	iOpt   = 0,
	iExc   = 0;
	// ---
	if(iIndex < 0 || (iLevel < 0 || iLevel > 15) ||  (iOpt   < 0 || iOpt > 7)  ||   (iLuck  < 0 || iLuck > 1)   || (iExc   < 0 || iExc > 63))
	{
		MsgUser(aIndex, 1, "Uso : /setdrop <id> <level> <luck> <opt> <exc>");
		return;
	}
	else
	{
		sscanf(szMsg,"%d %d %d %d %d ",&iIndex,&iLevel,&iLuck,&iOpt,&iExc);
		// ---
		for(int x = 7; x < 12; x++)
		{
			int iItem = x * 512 + iIndex;
			// ---
			srand(static_cast<int>(time(NULL)));
			// ---
			int Rand = rand() % 3;
			// ---
			ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X + Rand, gObj[aIndex].Y + Rand, iItem, iLevel, iDur, iSkill, iLuck, iOpt, -1, iExc, 0);
			// ---
			MsgUser(aIndex, 1, "[%s] Set criado.", gObj[aIndex].Name);
		}
	}
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (SETDROP) | SetId : (%d) \n", gObj[aIndex].AccountID, gObj[aIndex].Name, iIndex);
}

void CPrivilege::Hide(int aIndex, char * szMsg)
{
	if(!this->IsCommand(&gObj[aIndex], COMMAND_HIDE))
	{
		return;
	} 
	// ---
	int pResult = -1;
	// ---
	char szTemp[256] = {0};
	// ---
	if(strlen(szMsg) < 1)
	{
		MsgUser(aIndex, 1, "[%s] Modo: /hide <on/off>", gObj[aIndex].Name);
		return;
	}
	// ---
	sscanf(szMsg, "%s", &szTemp);
	// ---
	if(!strcmp(szTemp, "on"))
	{
		gObj[aIndex].m_Change = 255;
		// ---
		gObjViewportListProtocolCreate(&gObj[aIndex]);
		// ---
		GCMagicAttackNumberSend(&gObj[aIndex],0x46,aIndex,1);
		// ---
		MsgUser(aIndex, 1, "[%s] Você ficou invisivel.", gObj[aIndex].Name);
	}
	else if(!strcmp(szTemp, "off"))
	{
		GCMagicAttackNumberSend(&gObj[aIndex],0x46,aIndex,1);
		// ---
		gObj[aIndex].m_Change = -1;
		// ---
		gObjViewportListProtocolCreate(&gObj[aIndex]);
		// ---
		MsgUser(aIndex, 1, "[%s] Você ficou visivel.", gObj[aIndex].Name);
	}
	// ---
	LogAdd(LOG_GOLD, "[GM INFO] Account ID - (%s) | Name - (%s) | Usou o Comando (HIDE) \n", gObj[aIndex].AccountID, gObj[aIndex].Name);
}