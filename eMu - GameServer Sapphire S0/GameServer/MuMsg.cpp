#include "StdAfx.H"
#include "Log.h"

CMsg lMsg;

CMsg::CMsg()
{
	this->Msghead = NULL;
	
	strcpy(this->szDefaultMsg, "Error Message <Can't Find Specific Message>.");
}
 
CMsg::~CMsg()
{
	this->lMsgFree();
}

void CMsg::XorBuffer(char* buff, int len)
{
	if (len <= 0) return;
	
	for( int iCounter = 0; iCounter < len; ++iCounter)
	{
		buff[iCounter] = buff[iCounter]^0xCA;
	}
}

void CMsg::DataFileLoad(FILE* filename)
{
	UCHAR	szTemp[256];
	SHORT	Index;
	USHORT	Len;
	
	int Max = this->LoadHeader.count;
	
	if (Max <= 0)
	{
		MessageBox(NULL, "Number of data reading error."	, "Error", MB_OK|MB_APPLMODAL); // Modification error data while reading
		return;
	}
	
	while (Max--)
	{
		memset(&szTemp, 0, sizeof(szTemp));
		
		fread(&Index, 2, 1, filename);
		fread(&Len, 2, 1, filename);
		fread(szTemp, Len, 1, filename);
		
		szTemp[Len] = 0;
		
		this->XorBuffer((CHAR*)szTemp, Len);
		this->lMsgListAdd(Index, (UCHAR*) szTemp);
	} 
}

void CMsg::LoadWTF(char* filename)
{
	FILE * WTFFile = 0;
	
	if (( WTFFile = fopen(filename, "rb")) == NULL) return;
	
	if (this->lMsgListInit() != 0)
	{
		fread(&this->LoadHeader, 28, 1, WTFFile);
		
		if (this->LoadHeader.headcode != 0xCC)
		{
			MessageBox(NULL, "TextCode Type Wrong.", "Error", MB_OK|MB_APPLMODAL);
		}
		else if ((this->LoadHeader.version -1) != 0)
		{
			MessageBox(NULL, "Version of data is not supported.", "Error", MB_OK|MB_APPLMODAL);
		}
		else
		{
			DataFileLoad(WTFFile);
		}
		
		fclose(WTFFile);
	}
}

bool CMsg::lMsgListInit()
{
	LPMSG_STRUCT Msg = new MSG_STRUCT;
	
	if ( Msg == NULL )
	{
		MessageBox(NULL, "Memory Allocation Error (MuMsg)", "Error", MB_OK);
		
		return false;
	}
	
	Msg->next	= NULL;
	Msg->number = 0;
	Msg->msg	= NULL;
	
	memset(this->MsgIndex, 0, sizeof(this->MsgIndex));
	// -----
	return true;
}

void CMsg::lMsgFree()
{
	for (int n = 0; n < 32768; n++)
	{
		if (this->MsgIndex[n] != 0)
		{
			delete[] this->MsgIndex[n]->msg;
			// -----
			delete this->MsgIndex[n];
		}
	}
}

LPMSG_STRUCT CMsg::lMsgListNew()
{
	return new MSG_STRUCT;
}

bool CMsg::lMsgListAdd(int index, UCHAR* cMsg)
{
	int		MsgLen		= strlen((CHAR*)cMsg);
	CHAR*	pPointer;
	
	if (MsgLen > 0)
	{
		this->MsgIndex[index] = this->lMsgListNew();
		
		if (this->MsgIndex[index] == 0)
		{
			MessageBox(NULL, "Memory Allocation Error #2(MuMsg)", "Error", MB_OK); // Me
			return false;
		}
		
		pPointer = new char[MsgLen+1];
		
		if (pPointer  != 0)
		{
			this->MsgIndex[index]->number = index;
			
			if (index >= 0 || index < 32767)
			{
				this->MsgIndex[index]->msg = (UCHAR*)pPointer;
				
				strcpy((CHAR*)this->MsgIndex[index]->msg, (CHAR*)cMsg);
				return true;
			}
			else
			{
				MessageBox(NULL, "Message Index Table Make Error", "Error", MB_OK);
				return false;
			}
		}
	}
	
	return true;
}

void CMsg::lMsgListPrint()
{
	for (int n = 0; n < 32768; ++n)
	{
		if (this->MsgIndex[n] != 0)
		{
			MessageBox(NULL, (char*)this->MsgIndex[n]->msg, "Message", MB_OK);
		}
	}
}

LPSTR CMsg::Get(int index)
{
	if (index >= 0 && index < 32768)
	{
		if (this->MsgIndex[index] == 0)
		{
			return this->szDefaultMsg;
		}
		
		if (this->MsgIndex[index]->msg == 0)
		{
			return this->szDefaultMsg;
		}
		
		if (*this->MsgIndex[index]->msg == 0)
		{
			return this->szDefaultMsg;
		}
		
		return (char*)this->MsgIndex[index]->msg;
	}
	
	return (char*)this->szDefaultMsg;	
}