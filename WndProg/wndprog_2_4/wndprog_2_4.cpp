// [실습 2-4] 키보드 입력하여 구구단 출력하기
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
	static TCHAR ment[] = TEXT("명령어를 입력하세요 : ");
	static TCHAR str[80]{};
	static int count{};
	static int y_pos{ 20 };
	
	static int num[4]{};
	static int num_cnt{0};

	static TCHAR gugudan[80]{};

	static SIZE size{};

	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_BACK)
			count--;
		else if (wParam == VK_RETURN) {
			_stscanf_s(str, TEXT("%d %d %d %d"), &num[0], &num[1], &num[2], &num[3]);
			count = 0;
		}
		else if (wParam == 'q') {
			PostQuitMessage(0);
		}
		else
			str[count++] = wParam;
		str[count] = '\0';


		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		TextOut(hDC, 0, 0, ment, lstrlen(ment));
		TextOut(hDC, 0, y_pos, str, lstrlen(str));

		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);
		SetCaretPos(size.cx, 20);
		
		for (int i = 0; i < num[3]; ++i) {
			wsprintf(gugudan, TEXT("%d: * %d = %d"), num[2], i + 1, num[2] * (i + 1));
			TextOut(hDC, num[0], num[1] + 20 * i, gugudan, lstrlen(gugudan));
		}
	

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