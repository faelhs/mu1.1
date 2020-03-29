#include "StdAfx.h"

CConsole gConsole;

void __stdcall LoggerCore(PVOID pVoid)
{
        char title[100];
        sprintf(title,"Debugger :: HGTeam");
        AllocConsole();
        system("color E");
        SetConsoleTitleA(title);
        while(true)
		{
		   Sleep(100);
		}
}

void CConsole::Load()
{
	    DWORD PiD;
        CreateThread(0,0,(LPTHREAD_START_ROUTINE) LoggerCore,0,0,&PiD); 
}

void CConsole::LogAdd(char * szMsg, ...)
{
        char Message[1024];
        DWORD dwBytesWritten;
        HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
        va_list pArguments;
        va_start(pArguments, szMsg);
        vsprintf(Message,szMsg, pArguments);
        va_end(pArguments);
        char outputmsg[2048];
        sprintf(outputmsg,"%s\n", Message);
        WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten,0);

        SYSTEMTIME t;
        GetLocalTime(&t);

        char FileName[255];
        sprintf(FileName,".\\Log\\(%02d.%02d.%02d).log", t.wDay, t.wMonth, t.wYear);

        FILE *logfile = fopen(FileName,"a+");
        fputs(outputmsg,logfile);
        fclose(logfile);
}