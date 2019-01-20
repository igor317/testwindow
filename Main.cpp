#include "Main.h"
cApplication::cApplication(LPCSTR className, LPCSTR winName)
{
	g_pApplication = this;
	m_hInst = GetModuleHandle(NULL);

	m_className = className;
	m_winName = winName;

	m_Style = WS_OVERLAPPEDWINDOW;
	m_XPos = 0;
	m_YPos = 0;
	m_Width = 256;
	m_Height = 256;

	m_wndclass.cbSize = sizeof(WNDCLASSEX);							// Размер структуры WNDCLASSEX в байтах
	m_wndclass.style = CS_HREDRAW | CS_VREDRAW;						// Стиль окна
	m_wndclass.lpfnWndProc = fnMessageProcessor;						// Указатель на обработчик сообщений
	m_wndclass.cbClsExtra = 0;										// Инзачальный размер структуры в байтах (хз для чего, зануляем)
	m_wndclass.cbWndExtra = 0;										// Изначальный размер окна в байтах (зануляем)
	m_wndclass.hInstance = m_hInst;									// Дескриптор окна
	m_wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// Дескриптор класса значка: Первый параметр - Дескриптор на модуль, 
																		// который содержит значок - если NULL, то можем использовать стандартные значки. 
																		// Второй параметр - Указатель на строку, содержащий имя значка
	m_wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);					// Дескрипток класса указателя (Параметры такие же, что и у иконки)
	m_wndclass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	// Задний фон // GetStockObject - функция, которая получает кисть
	m_wndclass.lpszMenuName = NULL;									// Имя ресурса меню
	m_wndclass.lpszClassName = m_className;						// Имя класса окна
	m_wndclass.hIconSm = LoadIcon(NULL, IDI_ERROR);					// Значок самого окна, идентично hIcon
}

HWND cApplication::GethWnd()
{
	return m_hWnd;
}

HINSTANCE cApplication::GethInst()
{
	return m_hInst;
}

BOOL cApplication::Run()
{
	MSG Msg;

	// Регистрируем новый класс
	if (!RegisterClassEx(&m_wndclass))
		return FALSE;

	// Создаем окно
	m_hWnd = CreateWindow(m_className, m_winName,
		m_Style,
		m_XPos, m_YPos,
		m_Width, m_Height,
		NULL, NULL, m_hInst, NULL);
	if (!m_hWnd)
		return FALSE;

	// Показываем и обновляем окно
	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);

	// Изменяем размер под нужный
	Resize(m_Width, m_Height);

	if (Init() == TRUE)	// Если инициализация прошла
	{
		ZeroMemory(&Msg, sizeof(MSG));
		while (Msg.message != WM_QUIT) 
		{
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) 
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
	}

	DelVariable();

	// Чистим ресурсы
	UnregisterClass(m_className, m_hInst);

	return TRUE;
}

BOOL cApplication::Move(long XPos, long YPos)
{
	RECT ClientRect;

	GetClientRect(m_hWnd, &ClientRect);
	MoveWindow(m_hWnd, XPos, YPos, ClientRect.right, ClientRect.bottom, TRUE);

	return TRUE;
}


BOOL cApplication::Resize(long Width, long Height)
{
	m_Width = Width;
	m_Height = Height;
	return TRUE;
}

LRESULT CALLBACK fnMessageProcessor(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:	// Создание окна
		return (0);
	case WM_PAINT: // Отрисовка окна
		return (0);
	case WM_DESTROY: // Закрытие окна
		PostQuitMessage(0);	// Функция завершения программы Windows
		return(0);
	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam); // Если сообщение нет в списке, возвращаемся к функции WinMain с помощью этой функции

	}
}
