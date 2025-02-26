// [실습 2-2] 화면을 등분하여 문자 그리기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program 4";

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
	TCHAR str[] = TEXT("Hello World ABCDEF !@&*(# EWHUJ HDNAWJDWIDUBQ");
	int x_div{0};
	int y_div{0};
	COLORREF text_color{};
	int int_rgb[3]{};
	RECT temp{};

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		x_div = (rand() % 9) + 2;
		y_div = (rand() % 9) + 2;

		for (int i = 0; i < y_div; ++i) {
			for (int j = 0; j < x_div; ++j) {

				SetBkColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
				SetTextColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));

				temp.left = 800 / x_div * j;
				temp.top = 600 / y_div * i;
				temp.right = 800 / x_div * (j + 1);
				temp.bottom = 600 / y_div * (i + 1);

				DrawText(hDC, str, lstrlen(str), &temp, DT_CENTER | DT_WORDBREAK);
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}