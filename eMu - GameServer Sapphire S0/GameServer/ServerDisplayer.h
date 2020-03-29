#ifndef _SERVER_DISPLAY_H_
#define _SERVER_DISPLAY_H_
// ---
#define MAX_LOG_TEXT_LINE       30
#define MAX_LOG_TEXT_SIZE       110
// ---
enum eLogColor
{
	LOG_BLACK,
	LOG_RED,
	LOG_ORANGE,
	LOG_GREEN,
	LOG_BLUE,
	LOG_GOLD,
	LOG_PINK,
};
// ---
struct LOG_DISPLAY_INFO
{
	char szText[MAX_LOG_TEXT_SIZE];
	eLogColor Color;
};
// ---
class CServerDisplayer
{
public:
	CServerDisplayer();
	virtual ~CServerDisplayer();
	// ---
	void Load(HWND hWnd);
	// ---
	void Run();
	void PaintTopInfo();
	void PaintAllInfo();
	// ---
	void LogTextPaint();
	void LogAddText(eLogColor color, char* text, int size);
	// ---
	int m_PaintIndex;
	// ---
private:
	HFONT Font;
	// ---
	HBRUSH Background;
	// --
	int m_count;
	// ---
	LOG_DISPLAY_INFO m_log[MAX_LOG_TEXT_LINE];
	// ---
	HWND m_hWnd;
};
extern CServerDisplayer gServerDisplayer;
// ---
#endif