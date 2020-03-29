#include "StdAfx.h"

CMemory gMemory;

void CMemory::Load()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->Init, 0, 0, 0);
}

void CMemory::Init(LPVOID lpThreadParameter)
{
	HANDLE v1;
	HANDLE v2; 
	// ---
	while(TRUE)
	{
		Sleep(5000);
		v1 = GetCurrentProcess();
		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);
		v2 = GetCurrentProcess();
		SetThreadPriority(v2, -2);
	}
}