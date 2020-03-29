#ifndef _MEMORY_H
#define _MEMORY_H
// ---
class CMemory
{
public:
	void Load();
	static void Init(LPVOID lpThreadParameter);
};
// ---
extern CMemory gMemory;
// ---
#endif