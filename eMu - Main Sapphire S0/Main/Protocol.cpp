#include "StdAfx.h"

CProtocol gProtocol;

void CProtocol::Load()
{
	gToolKit.SetOp((LPVOID)0x004DB63D, (LPVOID)this->DataRecvEx, ASM::CALL);
	// ---
	gToolKit.HookThis((DWORD)&this->LevelUp, 0x4CC3C1); // 004F58BD   A1 486E7A07      MOV EAX,DWORD PTR DS:[77A6E48]
}

void CProtocol::DataRecvEx(DWORD protoNum, LPBYTE lpMsg, int Len, int aIndex)
{
	gConsole.LogAdd("HeadCode = 0x%X", protoNum);
	// ---
	switch(protoNum)
	{
		case 0x17:
			{
				gVisualFix.RecvKilledObject((PMSG_DIEPLAYER*)lpMsg);
			}
			break;
			// --
		case 0x26:
			{
				gVisualFix.RecvHP((PMSG_REFILL*)lpMsg);
			}
			break;
			// --
		case 0x27:
			{
				gVisualFix.RecvMPAG((PMSG_MANASEND*)lpMsg);
			}
			break;
		case 0xF1:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)lpMsg;
				// ----
				switch(lpDef->subcode)
				{
				case 0x00:
					{
						gVisualFix.RecvIndex((PMSG_JOINRESULT*)lpMsg);
					}
					break;
				}
			}
			break;
		case 0xF3:
	    {
		    PMSG_DEFAULT2 * lpMsg2 = (PMSG_DEFAULT2*)lpMsg;
			// ---
			switch(lpMsg2->subcode)
			{
				//case 0x02:
				//	{
				//		gHealthBar.Info((PMSG_HEALTH_BAR_RECV*) lpMsg);
				//	}
				//	break;
				//	// ---
				case 0x03:
					{
						gPoints.RecvPoint((PMSG_CHARMAPJOINRESULT*) lpMsg);
						// ---
						AgilityFix();
						// ---
						gReconnect.RestoreGame();
					}
					break;
					// ---
				case 0x04:
					{
						gVisualFix.RecvRespawn();
					}
					break;
					// ---
				case 0x05:
					{
						gPoints.RecvLevel((PMSG_LEVELUP*) lpMsg);
					}
					break;
					// ---
				case 0x06:
					{
						gPoints.RecvDownPoint((PMSG_LVPOINTADDRESULT*) lpMsg);
					}
					break;
				
			}
		}
		// ---
		case 0xFB:
		{
			PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)lpMsg;
			// ----
			switch(lpDef->subcode)
			{
			case 0xC:
				{
					gReconnect.iConnectState = eReconnectType::OnForceDisconnect;
				}
				break;
			}
		}
		break;
		// ---
		case 0xFE:
	    {
		    PMSG_DEFAULT2 * lpMsg2 = (PMSG_DEFAULT2*)lpMsg;
			// ---
			switch(lpMsg2->subcode)
			{
				case 0x07:
				{
					PMSG_CHARINFOMAIN* Info = (PMSG_CHARINFOMAIN*)(lpMsg);

					gProtocol.m_Data.Class = Info->Class;
					gProtocol.m_Data.Dexterity = Info->Dexterity;
					gProtocol.m_Data.AttackSpeed = Info->AttackSpeed;
					gProtocol.m_Data.MagicSpeed = Info->MagicSpeed;
					
					AgilityFix();
				}
				break;
			}
		}  
	}
	// ---
	pDataRecv(protoNum, lpMsg, Len, aIndex);
}

__declspec(naked) void CProtocol::LevelUp()
{
	static DWORD Local = 0x4CC416;
	// ---
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP + 0x08];
		MOV EAX, DWORD PTR DS : [0x7666A78];
		// ---
		//MOV DX, WORD PTR DS : [ECX + 0x16];
		//MOV WORD PTR DS : [EAX + 0x18], DX; // -> Strength
		//// ---
		//MOV DX, WORD PTR DS : [ECX + 0x18];
		//MOV WORD PTR DS : [EAX + 0x1A], DX; // -> Dexterity
		//// ---
		//MOV DX, WORD PTR DS : [ECX + 0x1A];
		//MOV WORD PTR DS : [EAX + 0x1C], DX; // -> Vitality
		//// ---
		//MOV DX, WORD PTR DS : [ECX + 0x1C];
		//MOV WORD PTR DS : [EAX + 0x1E], DX; // -> Energy
		//// ---
		//MOV DX, WORD PTR DS : [ECX + 0x1E];
		//MOV WORD PTR DS : [EAX + 0x20], DX; // -> Leadership
		// ---
		MOV DX, WORD PTR DS : [ECX + 0x04];
		MOV WORD PTR DS : [EAX + 0xE], DX; // -> Level
		// ---
		MOV DX, WORD PTR DS : [ECX + 0x06];
		MOV WORD PTR DS : [EAX + 0x68], DX; // -> LevelUpPoint
		// ---
		MOV DX, WORD PTR DS : [ECX + 0x08];
		MOV WORD PTR DS : [EAX + 0x22], DX; // -> Life
		MOV WORD PTR DS : [EAX + 0x26], DX; // -> MaxLife
		MOV SI, WORD PTR DS : [ECX + 0x0A];
		MOV WORD PTR DS : [EAX + 0x24], SI; // -> Mana
		MOV WORD PTR DS : [EAX + 0x28], SI; // -> MaxMana
		MOV DX, WORD PTR DS : [ECX + 0x0C];
		MOV WORD PTR DS : [EAX + 0x38], DX; // -> BP
		MOV WORD PTR DS : [EAX + 0x3A], DX; // -> MaxBP
		MOV DX, WORD PTR DS : [ECX + 0x0E];
		MOV WORD PTR DS : [EAX + 0x44], DX; // -> MaxStatPoint
		MOV DX, WORD PTR DS : [ECX + 0x10];
		MOV WORD PTR DS : [EAX + 0x46], DX; // -> MaxStatPoint
		MOV DX, WORD PTR DS : [ECX + 0x12];
		MOV WORD PTR DS : [EAX + 0x48], DX;
		MOV CX, WORD PTR DS : [ECX + 0x14];
		MOV WORD PTR DS : [EAX + 0x4A], CX;
		// ---
		JMP Local;
	}
}

void AgilityFix()
{
	switch (gProtocol.m_Data.Class)
	{
	case 0:
		{
			if (gProtocol.m_Data.MagicSpeed >= 455 && gProtocol.m_Data.MagicSpeed <= 479)
			{
				*pMainSpeedFrameTwo = 0.0024700f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 605 && gProtocol.m_Data.MagicSpeed <= 636)
			{
				*pMainSpeedFrameTwo = 0.0019000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 637 && gProtocol.m_Data.MagicSpeed <= 668)
			{
				*pMainSpeedFrameTwo = 0.0018000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 669 && gProtocol.m_Data.MagicSpeed <= 688)
			{
				*pMainSpeedFrameTwo = 0.0017000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 855 && gProtocol.m_Data.MagicSpeed <= 1040)
			{
				*pMainSpeedFrameTwo = 0.0016300f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1041 && gProtocol.m_Data.MagicSpeed <= 1104)
			{
				*pMainSpeedFrameTwo = 0.0015500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1301 && gProtocol.m_Data.MagicSpeed <= 1500)
			{
				*pMainSpeedFrameTwo = 0.0017500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1501 && gProtocol.m_Data.MagicSpeed <= 1524)
			{
				*pMainSpeedFrameTwo = 0.0015000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1525 && gProtocol.m_Data.MagicSpeed <= 1800)
			{
				*pMainSpeedFrameTwo = 0.0014500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1801 && gProtocol.m_Data.MagicSpeed <= 1999)
			{
				*pMainSpeedFrameTwo = 0.0013000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2000 && gProtocol.m_Data.MagicSpeed <= 2167)
			{
				*pMainSpeedFrameTwo = 0.0012500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2168 && gProtocol.m_Data.MagicSpeed <= 2354)
			{
				*pMainSpeedFrameTwo = 0.0011500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2855 && gProtocol.m_Data.MagicSpeed <= 3011)
			{
				*pMainSpeedFrameTwo = 0.0009000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 3011)
			{
				*pMainSpeedFrameTwo = 0.0008100f;
			}
			else
			{
				*pMainSpeedFrameTwo = 0.0020000f;
			}
		}
		break;
	case 1:
		{
			*pMainSpeedFrameOne = 0.0040000f;
			*pMainSpeedFrameTwo = 0.0020000f;
		}
		break;
	case 2:
		{
			if (gProtocol.m_Data.AttackSpeed >= 509 && gProtocol.m_Data.AttackSpeed <= 549)
			{
				*pMainSpeedFrameOne = 0.0026000f;
			} 
			else if (gProtocol.m_Data.AttackSpeed >= 550 && gProtocol.m_Data.AttackSpeed <= 750) 
			{
				*pMainSpeedFrameOne = 0.0017000f;
			} 
			else 
			{
				*pMainSpeedFrameOne = 0.0040000f;
			}
		}
		break;
	case 3:
		{
			if (gProtocol.m_Data.Dexterity >= 11001 && gProtocol.m_Data.Dexterity <= 12000)
			{
				*pMainSpeedFrameOne = 0.001800000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 16000 && gProtocol.m_Data.Dexterity <= 17000)
			{
				*pMainSpeedFrameOne = 0.001800000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 17001 && gProtocol.m_Data.Dexterity <= 19000)
			{
				*pMainSpeedFrameOne = 0.001700000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 19001 && gProtocol.m_Data.Dexterity <= 20000)
			{
				*pMainSpeedFrameOne = 0.001600000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 20001 && gProtocol.m_Data.Dexterity <= 21000)
			{
				*pMainSpeedFrameOne = 0.001500000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 21001 && gProtocol.m_Data.Dexterity <= 23000)
			{
				*pMainSpeedFrameOne = 0.001400000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 26000 && gProtocol.m_Data.Dexterity <= 27000)
			{
				*pMainSpeedFrameOne = 0.001900000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 27001 && gProtocol.m_Data.Dexterity <= 29000)
			{
				*pMainSpeedFrameOne = 0.001900000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 29001 && gProtocol.m_Data.Dexterity <= 30000)
			{
				*pMainSpeedFrameOne = 0.001900000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 30001 && gProtocol.m_Data.Dexterity <= 32767)
			{
				*pMainSpeedFrameOne = 0.001600000f;
			}
			else
			{
				*pMainSpeedFrameOne = 0.002000000f;
			}

			if (gProtocol.m_Data.MagicSpeed >= 455 && gProtocol.m_Data.MagicSpeed <= 479)
			{
				*pMainSpeedFrameTwo = 0.0024700f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 605 && gProtocol.m_Data.MagicSpeed <= 636)
			{
				*pMainSpeedFrameTwo = 0.0019000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 637 && gProtocol.m_Data.MagicSpeed <= 668)
			{
				*pMainSpeedFrameTwo = 0.0018000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 669 && gProtocol.m_Data.MagicSpeed <= 688)
			{
				*pMainSpeedFrameTwo = 0.0017000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 855 && gProtocol.m_Data.MagicSpeed <= 1040)
			{
				*pMainSpeedFrameTwo = 0.0016300f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1041 && gProtocol.m_Data.MagicSpeed <= 1104)
			{
				*pMainSpeedFrameTwo = 0.0015500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1301 && gProtocol.m_Data.MagicSpeed <= 1500)
			{
				*pMainSpeedFrameTwo = 0.0017500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1501 && gProtocol.m_Data.MagicSpeed <= 1524)
			{
				*pMainSpeedFrameTwo = 0.0015000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1525 && gProtocol.m_Data.MagicSpeed <= 1800)
			{
				*pMainSpeedFrameTwo = 0.0014500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 1801 && gProtocol.m_Data.MagicSpeed <= 1999)
			{
				*pMainSpeedFrameTwo = 0.0013000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2000 && gProtocol.m_Data.MagicSpeed <= 2167)
			{
				*pMainSpeedFrameTwo = 0.0012500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2168 && gProtocol.m_Data.MagicSpeed <= 2354)
			{
				*pMainSpeedFrameTwo = 0.0011500f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 2855 && gProtocol.m_Data.MagicSpeed <= 3011)
			{
				*pMainSpeedFrameTwo = 0.0009000f;
			}
			else if (gProtocol.m_Data.MagicSpeed >= 3011)
			{
				*pMainSpeedFrameTwo = 0.0008100f;
			}
			else
			{
				*pMainSpeedFrameTwo = 0.0020000f;
			}
		}
		break;
	case 4:
		{
			if (gProtocol.m_Data.Dexterity >= 2000 && gProtocol.m_Data.Dexterity < 4900)
			{
				*pMainSpeedFrameOne = 0.0038000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 4900 && gProtocol.m_Data.Dexterity < 5050)
			{
				*pMainSpeedFrameOne = 0.0037000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5050 && gProtocol.m_Data.Dexterity < 5200)
			{
				*pMainSpeedFrameOne = 0.0036000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5200 && gProtocol.m_Data.Dexterity < 5350)
			{
				*pMainSpeedFrameOne = 0.0035000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5350 && gProtocol.m_Data.Dexterity < 5550)
			{
				*pMainSpeedFrameOne = 0.0034000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5550 && gProtocol.m_Data.Dexterity < 5700)
			{
				*pMainSpeedFrameOne = 0.0033000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5700 && gProtocol.m_Data.Dexterity < 5900)
			{
				*pMainSpeedFrameOne = 0.0032000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 5900 && gProtocol.m_Data.Dexterity < 6100)
			{
				*pMainSpeedFrameOne = 0.0031000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 6100 && gProtocol.m_Data.Dexterity < 6300)
			{
				*pMainSpeedFrameOne = 0.0030000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 6300 && gProtocol.m_Data.Dexterity < 6500)
			{
				*pMainSpeedFrameOne = 0.0029000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 6500 && gProtocol.m_Data.Dexterity < 6750)
			{
				*pMainSpeedFrameOne = 0.0028000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 6750 && gProtocol.m_Data.Dexterity < 7000)
			{
				*pMainSpeedFrameOne = 0.0027000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 7000 && gProtocol.m_Data.Dexterity < 7300)
			{
				*pMainSpeedFrameOne = 0.0026000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 7300 && gProtocol.m_Data.Dexterity < 7600)
			{
				*pMainSpeedFrameOne = 0.0025000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 7600 && gProtocol.m_Data.Dexterity < 7900)
			{
				*pMainSpeedFrameOne = 0.0024000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 7900 && gProtocol.m_Data.Dexterity < 8250)
			{
				*pMainSpeedFrameOne = 0.0023000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 8250 && gProtocol.m_Data.Dexterity < 8650)
			{
				*pMainSpeedFrameOne = 0.0022000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 8650 && gProtocol.m_Data.Dexterity < 9050)
			{
				*pMainSpeedFrameOne = 0.0021000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 9050 && gProtocol.m_Data.Dexterity < 9500)
			{
				*pMainSpeedFrameOne = 0.0020000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 9500 && gProtocol.m_Data.Dexterity < 10000)
			{
				*pMainSpeedFrameOne = 0.0019000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 10000 && gProtocol.m_Data.Dexterity < 10550)
			{
				*pMainSpeedFrameOne = 0.0018000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 10550 && gProtocol.m_Data.Dexterity < 11150)
			{
				*pMainSpeedFrameOne = 0.0017000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 11150 && gProtocol.m_Data.Dexterity < 11850)
			{
				*pMainSpeedFrameOne = 0.0016000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 11850 && gProtocol.m_Data.Dexterity < 12600)
			{
				*pMainSpeedFrameOne = 0.0015000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 12600 && gProtocol.m_Data.Dexterity < 13450)
			{
				*pMainSpeedFrameOne = 0.0014000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 13450 && gProtocol.m_Data.Dexterity < 16600)
			{
				*pMainSpeedFrameOne = 0.0010000f;
			}
			else if (gProtocol.m_Data.Dexterity >= 16600)
			{
				*pMainSpeedFrameOne = 0.0008000f;
			}
			else
			{
				*pMainSpeedFrameOne = 0.0040000f;
			}
		}
		break;
	}
}