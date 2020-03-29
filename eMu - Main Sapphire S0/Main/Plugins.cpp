#include "StdAfx.h"

CPlugins gPlugins;

void CPlugins::Load()
{
	memset(this->m_Data, 0, sizeof(this->m_Data));
	// ---
	if(gEncode.Load(PLUGIN_FILE))
	{
		WZSMDToken Token = gEncode.GetToken();
		// ---
		if((Token == END) || (gEncode.GetInt() != 0))
		{
			MessageBox(NULL, "Error", "Error", MB_OK|MB_ICONERROR);
			::ExitProcess(0);
		}
		// ---
		for(int i = 0; i < MAX_PLUGINS; i++)
		{
			Token = gEncode.GetToken();
			// ---
			if(Token == END || lstrcmpi(gEncode.GetString(),"end") == 0) 
			{
				break;
			}
			// ---
			this->m_Data[i].Index		= gEncode.GetInt();
			// ---
			Token = gEncode.GetToken();
			memcpy(this->m_Data[i].dwName, gEncode.GetString(),sizeof(this->m_Data[i].dwName));
			// ---
			Token = gEncode.GetToken();
			memcpy(this->m_Data[i].dwApi, gEncode.GetString(),sizeof(this->m_Data[i].dwApi));
			// ---
			this->iCount++;
		}
		// ---
		gEncode.Close();
	}
	else
	{
		MessageBox(NULL, "Error", "Error", MB_OK|MB_ICONERROR);
		::ExitProcess(0);
	}
	// ---
	for(int i = 0; i < this->iCount; i++)
	{
		this->CheckFile(i);
	}
}

void CPlugins::CheckFile(int aIndex)
{
	HMODULE dwMod = LoadLibrary(this->m_Data[aIndex].dwName);
	// ---
	if(dwMod == 0)
	{
		ExitProcess(0);
	}
	// ---
	void (*EntryProc)() = (void(*)())GetProcAddress(dwMod, this->m_Data[aIndex].dwApi);
	// ---
	if(EntryProc != 0)
	{
		EntryProc();
	}
}