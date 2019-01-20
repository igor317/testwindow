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

	m_wndclass.cbSize = sizeof(WNDCLASSEX);							// ������ ��������� WNDCLASSEX � ������
	m_wndclass.style = CS_HREDRAW | CS_VREDRAW;						// ����� ����
	m_wndclass.lpfnWndProc = fnMessageProcessor;						// ��������� �� ���������� ���������
	m_wndclass.cbClsExtra = 0;										// ����������� ������ ��������� � ������ (�� ��� ����, ��������)
	m_wndclass.cbWndExtra = 0;										// ����������� ������ ���� � ������ (��������)
	m_wndclass.hInstance = m_hInst;									// ���������� ����
	m_wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// ���������� ������ ������: ������ �������� - ���������� �� ������, 
																		// ������� �������� ������ - ���� NULL, �� ����� ������������ ����������� ������. 
																		// ������ �������� - ��������� �� ������, ���������� ��� ������
	m_wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);					// ���������� ������ ��������� (��������� ����� ��, ��� � � ������)
	m_wndclass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	// ������ ��� // GetStockObject - �������, ������� �������� �����
	m_wndclass.lpszMenuName = NULL;									// ��� ������� ����
	m_wndclass.lpszClassName = m_className;						// ��� ������ ����
	m_wndclass.hIconSm = LoadIcon(NULL, IDI_ERROR);					// ������ ������ ����, ��������� hIcon
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

	// ������������ ����� �����
	if (!RegisterClassEx(&m_wndclass))
		return FALSE;

	// ������� ����
	m_hWnd = CreateWindow(m_className, m_winName,
		m_Style,
		m_XPos, m_YPos,
		m_Width, m_Height,
		NULL, NULL, m_hInst, NULL);
	if (!m_hWnd)
		return FALSE;

	// ���������� � ��������� ����
	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);

	// �������� ������ ��� ������
	Resize(m_Width, m_Height);

	if (Init() == TRUE)	// ���� ������������� ������
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

	// ������ �������
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
	case WM_CREATE:	// �������� ����
		return (0);
	case WM_PAINT: // ��������� ����
		return (0);
	case WM_DESTROY: // �������� ����
		PostQuitMessage(0);	// ������� ���������� ��������� Windows
		return(0);
	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam); // ���� ��������� ��� � ������, ������������ � ������� WinMain � ������� ���� �������

	}
}
