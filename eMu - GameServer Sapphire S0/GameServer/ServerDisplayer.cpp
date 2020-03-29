#include "StdAfx.h"
#include "user.h"
#include "Log.h"
#include "GameServer.h"
#include "ServerDisplayer.h"

CServerDisplayer gServerDisplayer;

char * TitleText[1] =
{
#if(GS_CASTLE==0)
	"[- GameServer -]"
#else
	"[- GameCastle -]"
#endif
};

CServerDisplayer::CServerDisplayer()
{
	for(int n = 0; n < MAX_LOG_TEXT_LINE; n++)
	{
		memset(&this->m_log[n], 0, sizeof(this->m_log[n]));
	}
	// ---
	this->Font = CreateFontA(80, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, 1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Impact");
	// ---
	this->Background = CreateSolidBrush(RGB(0, 76, 153));
}

CServerDisplayer::~CServerDisplayer()
{
	DeleteObject(this->Font);
	DeleteObject(this->Background);
}

void CServerDisplayer::Load(HWND hWnd)
{
	this->m_hWnd = hWnd;
	// ---
	gLog.AddLog(true, "Log\\NORMAL_LOG");
	// ---
	gLog.AddLog(false, "Log\\GAME_SHOP_LOG");
	gLog.AddLog(false, "Log\\COMMAND_LOG");
	gLog.AddLog(false, "Log\\BOT_MANAGER_LOG");
	gLog.AddLog(false, "Log\\CHAT_LOG");
	gLog.AddLog(false, "Log\\TRADE_LOG");
}

void CServerDisplayer::Run()
{
	this->LogTextPaint();
	this->PaintAllInfo();
	this->PaintTopInfo();
}

void CServerDisplayer::PaintTopInfo()
{
	if(!OBJMAX_RANGE(this->m_PaintIndex))
	{
		return;
	}
	// ---
	HDC hDC = GetDC(this->m_hWnd);
	// ---
	char szBuffer[256] = {0};
	// ---
	int TotalPlayer = 0;
	int TotalMonster = 0;
	int BotCount = 0;
	int VipCount = 0;
	// ---
	for(int i = 0; i < OBJMAX; i++)
	{
		if(gObj[i].Type == OBJ_USER && gObj[i].Connected != PLAYER_EMPTY)
		{
			TotalPlayer++;
		}
		else if(gObj[i].Connected != PLAYER_EMPTY)
		{
			TotalMonster++;
		}
	}
	// ---
	gObjTotalUser = TotalPlayer;
	// ---
	wsprintf(szBuffer, "Monster Count: [%d / %d] | Users Online: [%d / %d] | Bots Online: [%d] | Vips Online: [%d]", TotalMonster, OBJ_MAXMONSTER, TotalPlayer, gServerMaxUser, BotCount, VipCount);
	// ---
	SetBkMode(hDC, TRANSPARENT);
	// ---
	SetTextColor(hDC, RGB(171,171,171));
	// ---
	TextOut(hDC, GAMESERVER_WIDTH / 2 - 280, 1, szBuffer, strlen(szBuffer));
	// ---
	ReleaseDC(this->m_hWnd, hDC);
}

void CServerDisplayer::PaintAllInfo()
{
	HDC hDC = GetDC(this->m_hWnd);
	// --
	RECT rect;
	// --
	GetClientRect(this->m_hWnd, &rect);
	// --
	rect.top = 20;
	rect.bottom = 100;
	// ---
	FillRect(hDC, &rect, this->Background);
	// ---
	HFONT pOldFont = (HFONT)SelectObject(hDC, this->Font);
	// ---
	SetTextColor(hDC, RGB(250, 250, 250));
	// ---
	int iOldBkMode = SetBkMode(hDC, TRANSPARENT);
	// ---
	TextOutA(hDC, 140, 20, TitleText[0], strlen(TitleText[0]));
	// ---
	SelectObject(hDC, pOldFont);
	// ---
	SetBkMode(hDC, iOldBkMode);
	// ---
	ReleaseDC(this->m_hWnd, hDC);
}

void CServerDisplayer::LogTextPaint()
{
	RECT rect;
	// ---
	GetClientRect(this->m_hWnd, &rect);
	// ---
	HDC hdc = GetDC(this->m_hWnd);
	// ---
	HBRUSH brush = CreateSolidBrush(RGB(24, 24, 24));
	// ---
	FillRect(hdc, &rect, brush);
	// ---
	int line = MAX_LOG_TEXT_LINE;
	// ---
	int count = (((this->m_count-1) >= 0) ? (this->m_count-1):(MAX_LOG_TEXT_LINE-1));
	// ---
	SetBkMode(hdc, TRANSPARENT);
	// ---
	for(int n = 0; n < MAX_LOG_TEXT_LINE; n++)
	{
		switch(this->m_log[count].Color)
		{
		case LOG_BLACK:
			SetTextColor(hdc,RGB(171, 171, 171));
			break;
		case LOG_RED:
			SetTextColor(hdc,RGB(240, 25, 25));
			break;
		case LOG_ORANGE:
			SetTextColor(hdc,RGB(255, 69, 0));
			break;
		case LOG_GREEN:
			SetTextColor(hdc,RGB(127, 255, 0));
			break;
		case LOG_BLUE:
			SetTextColor(hdc,RGB(0, 255, 255));
			break;
		case LOG_GOLD:
			SetTextColor(hdc,RGB(255, 215, 0));
			break;
		case LOG_PINK:
			SetTextColor(hdc,RGB(255, 93, 233));
			break;
		}
		// ---
		int size = strlen(this->m_log[count].szText);
		// ---
		if(size > 1)
		{
			TextOut(hdc, 2 ,((line * 15) + 90), this->m_log[count].szText, size);
			// ---
			line--;
		}
		// ---
		count = (((--count) >= 0) ? count:(MAX_LOG_TEXT_LINE-1));
	}
	// ---
	ReleaseDC(this->m_hWnd, hdc);
	// ---
	DeleteObject(brush);
}

void CServerDisplayer::LogAddText(eLogColor color, char* text, int size)
{
	size = ((size>=MAX_LOG_TEXT_SIZE)?(MAX_LOG_TEXT_SIZE-1):size);
	// ---
	memset(&this->m_log[this->m_count].szText, 0, sizeof(this->m_log[this->m_count].szText));
	// ---
	memcpy(&this->m_log[this->m_count].szText, text, size);
	// ---
	this->m_log[this->m_count].Color = color;
	// ---
	this->m_count = (((++this->m_count) >= MAX_LOG_TEXT_LINE)?0:this->m_count);
	// ---
	gLog.Output(LOG_GENERAL, "%s", &text[9]);
}