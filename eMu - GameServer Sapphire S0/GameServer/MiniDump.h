#pragma once

#include <DbgHelp.h>
#pragma comment(lib,"DbgHelp.lib")

class CMiniDump
{
public:
	static void Start();
	static void Clean();
};