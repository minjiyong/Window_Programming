// [실습 2-1] 화면의 코너와 중앙에 문자 그리기
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
	TCHAR temp[100]{};
	int x[10]{};
	int y[10]{};

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		TextOut(hDC, 400, 300, TEXT("0: (400, 300)"), 13);
		
		for (int i = 0; i < 10; ++i) {
			x[i] = (rand() % 600);
			y[i] = (rand() % 550);
			for(int  j = i; j > 0; --j) {
				if (x[i] - x[j - 1] <= 10 && x[j - 1] - x[i] <= 10) continue;
				else if (y[i] - y[j - 1] <= 10 && y[j - 1] - y[i] <= 10) continue;
			}
			wsprintf(temp, TEXT("%d: (%d, %d)"), i + 1, x[i], y[i]);
			TextOut(hDC, x[i], y[i], temp, lstrlen(temp));
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}