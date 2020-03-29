#pragma once

#include "..\include\prodef.h"
#include "user.h"

typedef struct
{
	PBMSG_HEAD2	h;
	INT			NumberH;
	INT			NumberL;
	INT			Level;
	FLOAT		Life;
	INT			MaxLife;
	INT			Class;
} MSG_ANS_LIFEBAR_SEND, *LPMSG_ANS_LIFEBAR_SEND;

typedef struct
{
	PBMSG_HEAD2	h;
	INT			NumberH;
	INT			NumberL;
	INT			Level;
	FLOAT		Life;
	INT			MaxLife;
	INT			Class;
} MSG_ANS_LIFEBAR_SEND2, *LPMSG_ANS_LIFEBAR_SEND2;

class CHealthBar
{
public:
	void Info(LPOBJ lpObj);
	void Send(int aIndex,int tIndex);
};

extern CHealthBar gHealthBar;