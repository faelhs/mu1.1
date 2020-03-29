#ifndef _PRIVILEGE_H
#define _PRIVILEGE_H
// ---
enum GM_MANAGER_COMMANDS
{
	COMMAND_RELOAD,
	COMMAND_DISCONNECT,
	COMMAND_BLOCK,
	COMMAND_UNBLOCK,
	COMMAND_SKIN,
	COMMAND_MAKE,
	COMMAND_GMOVE,
	COMMAND_MOVEALL,
	COMMAND_REWARD,
	COMMAND_SETZEN,
	COMMAND_SETLEVEL,
	COMMAND_SETPK,
	COMMAND_SETDROP,
	COMMAND_HIDE,
};
// ---
struct PRIVILEGE_DATA
{
	int   iType;
	char  szName[11];
	int   iCommand[40];
	// ---
	char szSintax[50];
};
// ---
class CPrivilege
{
public:
	void Load();
	// ---
	int  IsCheck(LPOBJ lpObj);
	// ---
	bool IsCommand(LPOBJ lpObj, int Command);
	// ---
	int  iCount;
	// ---
	void Reload(int aIndex, char *szMsg);
	void Disconnect(int aIndex, char *szMsg);
	void Block(int aIndex, char *szMsg);
	void UnBlock(int aIndex, char *szMsg);
	void Skin(int aIndex, char *szMsg);
	void Make(int aIndex, char *szMsg);
	void Move(int aIndex, char *szMsg);
	void MoveAll(int aIndex, char *szMsg);
	void Reward(int aIndex, char *szMsg);
	void SetZen(int aIndex, char * szMsg);
	void SetLevel(int aIndex, char * szMsg);
	void SetPKLevel(int aIndex, char * szMsg);
	void SetDrop(int aIndex, char *szMsg);
	void Hide(int aIndex, char * szMsg);
	// ---
	PRIVILEGE_DATA m_Data[30];
};
// ---
extern CPrivilege gPrivilege;
// ---
#endif