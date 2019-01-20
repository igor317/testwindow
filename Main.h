#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>
class cApplication
{
private:
	HINSTANCE     m_hInst;
	HWND          m_hWnd;
protected:
	LPCSTR m_className;
	LPCSTR m_winName;
	WNDCLASSEX m_wndclass;

	DWORD m_Style;
	DWORD m_XPos;
	DWORD m_YPos;
	DWORD m_Width;
	DWORD m_Height;
public:
	cApplication(LPCSTR className, LPCSTR winName);
	HWND      GethWnd();
	HINSTANCE GethInst();

	BOOL Run();
	BOOL Move(long Xpos,long Ypos);
	BOOL Resize(long Width, long Height);

	virtual BOOL Init() { return TRUE; }
	virtual BOOL DelVariable() { return TRUE; }
};
static cApplication *g_pApplication = NULL;
static LRESULT CALLBACK fnMessageProcessor(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
#endif