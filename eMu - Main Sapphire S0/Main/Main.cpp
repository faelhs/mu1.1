#include "StdAfx.h"

extern "C" __declspec (dllexport) void __cdecl EntryProc()
{
	DWORD OldProtect;
	// ---
	if (VirtualProtect(LPVOID(0x401000), 4452946, PAGE_EXECUTE_READWRITE, &OldProtect))
	{
		EmptyWorkingSet(GetCurrentProcess());
		// ---
		if(gProtect.Load("Main.hgt") == 0)
		{
			ExitProcess(0);
		}
		// ---
		gMainInfo.Load();
		//gFont.Load();
		gProtocol.Load();
		gItemManager.Load();
		gController.Load();
		gMemory.Load();
		gPoints.Load();
		gVisualFix.Load();
		gUser.Load();
		gInterface.Load();
		//gReconnect.Load();
		//gHealthBar.Load();
		gWingManager.Load();
		gGlowManager.Load();
		//gConsole.Load();
		//gMonster.Load();
		//gMiniMap.Load();
		// ---
		//gPlugins.Load();
		// ---
		if(gToolKit.Registry("WindowMode") > 0)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
			DetourAttach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
			DetourTransactionCommit();
		}
	}
	else
	{
		MessageBoxA(NULL, "Arquivo 'Main.dll' não foi carregado !'", "Main.exe - Erro !", MB_OK);
		ExitProcess(0);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// ---
		EntryProc();
		// ---
		break;
	case DLL_PROCESS_DETACH:
		// ---
		if(gToolKit.Registry("WindowMode") > 0)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourDetach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
			DetourDetach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
			DetourTransactionCommit();
		}
		// ---
		gController.Load();
		// ---
		break;
	}
	// ---
	return TRUE;
}