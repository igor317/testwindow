#include "Main.h"

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	cApplication App("ClassName","TestPlotter");
	App.Resize(640,480);
	return App.Run();
}