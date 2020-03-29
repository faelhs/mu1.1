#ifndef _CONTROLLER_H
#define _CONTROLLER_H

class CController
{
public:
	CController();
	virtual ~CController();
	// ---
	bool Load();
	// ---
	static LRESULT CALLBACK MouseProc(int Code, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam);
	// ---
	HINSTANCE hModule;
	// ---
private:
	// ---
	bool bBSelect;
	// ---
	HHOOK MouseHook;
	HHOOK KeyboardHook;
};

extern CController gController;

#endif