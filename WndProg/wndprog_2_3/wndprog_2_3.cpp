// [실습 2-3] 화면에 문자 그리기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program 3";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static TCHAR temp[10]{};
	static int x{};
	static int y{};
	static int n{};
	static int count{};

	static SIZE size{};
	static int origin_x{};

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetBkColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetTextColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));

		for (int i = 0; i < count; ++i) {
			for (int j = 0; j < count; ++j) {
				TextOut(hDC, x, y, temp, lstrlen(temp));
				GetTextExtentPoint32W(hDC, temp, lstrlen(temp), &size);
				x += size.cx;
			}
			x = origin_x;
			y += size.cy;
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_RETURN) {

			x = rand() % 600;
			y = rand() % 400;
			n = rand() % 10;
			count = rand() % 16 + 5;
			origin_x = x;
			wsprintf(temp, TEXT("%d"), n);
		}
		else if (wParam == 'q') PostQuitMessage(0);

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}