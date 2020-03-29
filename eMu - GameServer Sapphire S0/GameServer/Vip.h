#ifndef _VIP_H
#define _VIP_H

#define VIP_COUNT 4

struct VIP_DATA_INFO
{
	char  iVipName[50];
	float iExperience;
	float iItemDrop;
};

class CVip
{
public:
	void Load();
	// ---
	char* GetName(int VipNumber);
	// ---
	float GetDropRate(int VipNumber);
	float GetExperience(int VipNumber);
	// ---
	VIP_DATA_INFO m_Data[VIP_COUNT];
};

extern CVip gVip;

#endif