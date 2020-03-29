#ifndef _CONSOLE_H
#define _CONSOLE_H

class CConsole
{
public:
	void Load();
	// ---
    void LogAdd(char * szMsg, ...);
};

extern CConsole gConsole;

#endif