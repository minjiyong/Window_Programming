// [실습 2-6] 화면에 문자 그리기
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
	
	int x_div{ 0 };
	int y_div{ 0 };

	COLORREF color{};
	int num{};
	RECT temp{};

	HBRUSH hBrush{};

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		x_div = (rand() % 6) + 2;
		y_div = (rand() % 6) + 2;

		for (int i = 0; i < y_div; ++i) {
			for (int j = 0; j < x_div; ++j) {

				SetTextColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
				color = RGB(rand() % 256, rand() % 256, rand() % 256);
				SetBkColor(hDC, color);
				hBrush = CreateSolidBrush(color);

				temp.left = 800 / x_div * j;
				temp.top = 600 / y_div * i;
				temp.right = 800 / x_div * (j + 1);
				temp.bottom = 600 / y_div * (i + 1);

				FillRect(hDC, &temp, hBrush);

				num = rand() % 6;
				switch (num) {
				case 0:

					for (int i = 0; i < 5; ++i) {

						for (int k = 0; k < i; ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < 2 * 5 - (i * 2 + 1); ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;

					}
					for (int i = 1; i < 5; ++i) {
						for (int k = 0; k < 5 - (i + 1); ++k) {
							temp.left += 10;
						}
						for (int j = 0; j < (i + 1) * 2 - 1; ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}
						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					break;

				case 1:
					for (int i = 0; i < 5; ++i) {

						for (int j = 0; j < 5 * 2; ++j) {

							if ((j < i + 1) || (j >= (2 * 5) - i - 1)) {
								TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
								temp.left += 10;
							}
							else
								temp.left += 10;

						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					for (int i = 1; i < 5; ++i) {

						for (int j = 0; j < 5 * 2; ++j) {

							if ((j < 5 - i) || (j > (5 + (i - 1)))) {
								TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
								temp.left += 10;
							}
							else
								temp.left += 10;

						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}


					break;

				case 2:

					for(int i = 0; i < 5; ++i) {

						for (int k = 0; k < 5 - (i + 1); ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < (i + 1) * 2 - 1; ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}


					for (int i = 1; i < 5; ++i) {

						for (int k = 0; k < i; ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < 2 * 5 - (i * 2 + 1); ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					break;
				case 3:
					
					for (int i = 0; i < 5; ++i) {


						for (int k = 0; k < 5 - (i + 1); ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < (i + 1) * 2 - 1; ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}
					for (int i = 0; i < 5; ++i) {


						for (int k = 0; k < 5 - (i + 1); ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < (i + 1) * 2 - 1; ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					break;
				case 4:
					
					for (int i = 0; i < 5; ++i) {


						for (int k = 0; k < i; ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < 2 * 5 - (i * 2 + 1); ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}
					for (int i = 0; i < 5; ++i) {


						for (int k = 0; k < i; ++k) {
							temp.left += 10;
						}

						for (int j = 0; j < 2 * 5 - (i * 2 + 1); ++j) {
							TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
							temp.left += 10;
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					break;
				case 5:
					
					for (int i = 0; i < 11; ++i) {

						for (int j = 0; j < 11; ++j) {
							if (j == i || j + i == 10) {
								TextOut(hDC, temp.left, temp.top, TEXT("*"), 1);
								temp.left += 10;
							} 
							else temp.left += 10;
	
						}

						temp.top += 8;
						temp.left = 800 / x_div * j;
					}

					break;
				}
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hBrush);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}