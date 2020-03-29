#include "stdafx.h"

CProtect gProtect;

bool CProtect::Load(char* szName)
{
	CCRC32 CRC32;
	// ---
	if(CRC32.FileCRC(szName,&this->m_FileCrc,1024) == 0)
	{
		return 0;
	}
	// ---
	HANDLE szFile = CreateFile(szName,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);
	// ---
	if(szFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	// ---
	if(GetFileSize(szFile, NULL) != sizeof(PROTECT_DATA))
	{
		CloseHandle(szFile);
		return 0;
	}
	// ---
	DWORD OutSize = 0;
	// ---
	if(ReadFile(szFile, &this->m_Data, sizeof(PROTECT_DATA), &OutSize, NULL) == NULL)
	{
		CloseHandle(szFile);
		return 0;
	}
	// ---
	for(int n = 0; n < sizeof(PROTECT_DATA); n++)
	{
		((BYTE*)&this->m_Data)[n] += (BYTE)(0x95^HIBYTE(n));
		((BYTE*)&this->m_Data)[n] ^= (BYTE)(0xCA^LOBYTE(n));
	}
	// ---
	CloseHandle(szFile);
	return 1;
}