#ifndef _MAIN_INFO_H
#define _MAIN_INFO_H

#define pMain_IP		0x006B6694
#define pMain_Version	0x006B7248
#define pMain_Serial	0x006B7250

class CMainInfo
{
public:
	void Load();
	void Connect();
	void Fixes();
	void Brightness();
};

extern CMainInfo gMainInfo;

#endif