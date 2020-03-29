#include "StdAfx.h"
#include <WinCon.h>

CController gController;

CController::CController()
{
	this->MouseHook		= NULL;
	this->KeyboardHook	= NULL;
}

CController::~CController(){}

bool CController::Load()
{
	if(!this->MouseHook)
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE,(HOOKPROC)this->MouseProc, gController.hModule,GetCurrentThreadId());
		// ---
		if(!this->MouseHook)
		{
			return false;
		}
	}
	// ---
	if(!this->KeyboardHook)
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)this->KeyboardProc, gController.hModule,GetCurrentThreadId());
		// ---
		if(!this->KeyboardHook)
		{
			return false;
		}
	}
	// ---
	return true;
}

LRESULT CALLBACK CController::MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND MuWnd = FindWindow(gProtect.m_Data.szTitle, NULL);
	// ---
	if(GetForegroundWindow() != MuWnd )
	{
		return CallNextHookEx(gController.MouseHook,nCode,wParam,lParam);
	}
	// ---
	MOUSEHOOKSTRUCTEX * Mouse = (MOUSEHOOKSTRUCTEX*)lParam;
	// ---
	gCamera.Run(Mouse, wParam);
	// ---
	switch(wParam)
	{
	}
	// ---
	return CallNextHookEx(gController.MouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK CController::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(((lParam >> 31) & 1) && (nCode == HC_ACTION))
	{
		switch(wParam)
		{
			case VK_TAB: // -> MiniMap
				if(!gMiniMap.bSelect)
				{
					gMiniMap.ViewType(1);
				}
				else
				{
					gMiniMap.ViewType(2);
				}
				break;
			case VK_F6: // -> Camera 3D
				if(!gCamera.bSelect)
				{
					gCamera.ViewType(1);
				}
				else
				{
					gCamera.ViewType(2);
				}
				break;
			case VK_F7: // -> Resetar Camera
				gCamera.Reset();
				break;
		}
	} 
	// ---
	return CallNextHookEx(gController.KeyboardHook, nCode, wParam, lParam);
}