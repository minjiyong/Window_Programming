// [실습 2-5] 캐럿을 이용한 메모장 만들기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>

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
	static TCHAR str[10][80]{};
	static int county{ 0 };
	static int countx{ 0 };

	static SIZE size[80]{};
	static int c_count{ 0 };

	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_BACK) {
			countx--;
			for (int i = countx; i < lstrlen(str[county]) + 1; ++i) {
				str[county][i] = str[county][i + 1];
			}
			c_count--;
		}
		else if (wParam == VK_RETURN) {		
			countx = 0;
			county++;
			c_count = 0;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		else {
			str[county][countx++] = wParam;
			c_count++;
		}

		if (countx == 30) {
			countx = 0;
			county++;
			c_count = 0;
		}
		if (county == 10) {
			countx = 0;
			county = 0;
			c_count = 0;
		}

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 10; ++i) {
			TextOut(hDC, 0, 0 + 20 * i, str[i], lstrlen(str[i]));
		}

		
		GetTextExtentPoint32(hDC, str[county], c_count, &size[c_count]);
		

		SetCaretPos(size[c_count].cx, 0 + 20 * county);

		EndPaint(hWnd, &ps);
		break;



	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}