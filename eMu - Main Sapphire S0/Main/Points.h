#ifndef _POINTS_H
#define _POINTS_H

#include "Packets.h"

class CPoints
{
public:
	void Load();
	// ---
	void RecvPoint(PMSG_CHARMAPJOINRESULT * aRecv);
	void RecvLevel(PMSG_LEVELUP * aRecv);
	void RecvDownPoint(PMSG_LVPOINTADDRESULT * aRecv);
	// ---
	static void gObjFix();
};

extern DWORD dwPoints;

extern CPoints gPoints;

#endif