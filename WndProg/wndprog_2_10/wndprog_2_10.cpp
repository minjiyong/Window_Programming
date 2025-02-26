// [실습 2-10] 돌 이동하여 원하는 위치에 원하는 모양과 원하는 색상으로 도착하기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

// 끝나는 색깔들	
COLORREF color1 = RGB(255, 0, 255);		// 보라
COLORREF color2 = RGB(255, 255, 0);		// 노랑
COLORREF color3 = RGB(0, 255, 255);		// 하늘

COLORREF color_red = RGB(255, 0, 0);	// 빨강, 장애물
COLORREF color_blue = RGB(0, 0, 255);		// 파랑, 축소
COLORREF color_green = RGB(0, 255, 0);		// 초록, 확대
COLORREF color_black = RGB(0, 0, 0);		// 검정, 모양 변경

#define UP 1;
#define LEFT 2;
#define DOWN 3;
#define RIGHT 4;

class Block
{
public:
	int x{};
	int y{};
	COLORREF color{};
	int shape{ 0 };

	Block() {
		x = 20 * (rand() % 40);
		y = 20 * (rand() % 40);
		shape = 0;
		int temp{ 0 };
		temp = rand() % 7 + 1;
		switch (temp) {
		case 1:
			color = color1;
			break;
		case 2:
			color = color2;
			break;
		case 3:
			color = color3;
			break;
		case 4:
			color = color_red;
			break;
		case 5:
			color = color_blue;
			break;
		case 6:
			color = color_green;
			break;
		case 7:
			color = color_black;
			temp = rand() % 4;
			switch (temp) {
			case 0:
				shape = 0;		// 네모
				break;
			case 1:
				shape = 1;		// 원
				break;
			case 2:
				shape = 2;		// 파이
				break;
			case 3:
				shape = 3;		// 반원
				break;
			}
			break;
		}
	};
	Block(int b_x, int b_y, COLORREF c) : x(b_x), y(b_y), color(c){};
	~Block() {};

	void intialize_block() {
		x = 20 * (rand() % 40);
		y = 20 * (rand() % 40);
		shape = 0;
		int temp{ 0 };
		temp = rand() % 7 + 1;
		switch (temp) {
		case 1:
			color = color1;
			break;
		case 2:
			color = color2;
			break;
		case 3:
			color = color3;
			break;
		case 4:
			color = color_red;
			break;
		case 5:
			color = color_blue;
			break;
		case 6:
			color = color_green;
			break;
		case 7:
			color = color_black;
			temp = rand() % 4;
			switch (temp) {
			case 0:
				shape = 0;
				break;
			case 1:
				shape = 1;
				break;
			case 2:
				shape = 2;
				break;
			case 3:
				shape = 3;
				break;
			}
			break;
		}
	};
};

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Hello~";

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

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 900, 900, NULL, (HMENU)NULL, hInstance, NULL);

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
	HBRUSH hBrush{}, oldBrush{};
	HPEN hPen{}, oldPen{};


	static int p_x{ 0 };
	static int p_y{ 0 };
	static int p_size{ 0 };
	static int p_shape{ 0 };
	static int p_color{ 0 };

	static int p_dir{ 0 };

	static int end_x{ 780 };
	static int end_color{ 0 };
	static int end_shape{ 0 };

	static Block arr_block[20]{};

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));

		end_color = rand() % 3 + 1;
		end_shape = rand() % 3 + 1;

		for (int i = 0; i < 20; ++i) {
			arr_block[i].intialize_block();
		}
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		
		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'r') {
			ExitWindowsEx(EWX_REBOOT, 0);
			end_color = rand() % 5 + 1;
		}

		else if (wParam == 'w') {
			if (p_y == 0) p_y = 780;
			else p_y -= 20;
			p_dir = UP;
		}
		else if (wParam == 'a') {
			if (p_x == 0) p_x = 780;
			else p_x -= 20;
			p_dir = LEFT;
		}
		else if (wParam == 's') {
			if (p_y == 780) p_y = 0;
			else p_y += 20;
			p_dir = DOWN;
		}
		else if (wParam == 'd') {
			if (p_x == 780) p_x = 0;
			else p_x += 20;
			p_dir = RIGHT;
		}

		// 이동 후 체크하기
		for (int i = 0; i < 20; ++i) {
			if (p_x == arr_block[i].x && p_y == arr_block[i].y) {
				// 플레이어의 위치와 블럭의 좌표가 같다면

				if (arr_block[i].color == color_red) {				// 빨강, 장애물
					switch (p_dir)
					{
					case (1):
						p_y += 20;
						break;
					case (2):
						p_x += 20;
						break;
					case (3):
						p_y -= 20;
						break;
					case (4):
						p_x -= 20;
						break;
					}
				}

				else if (arr_block[i].color == color_blue) {			// 파랑, 축소
					p_size++;
				}

				else if (arr_block[i].color == color_green) {			// 초록, 확대
					p_size--;
				}

				else if (arr_block[i].color == color_black) {			// 검정, 모양 변경
					switch (arr_block[i].shape) {
					case 0:
						p_shape = 0;
						break;
					case 1:
						p_shape = 1;
						break;
					case 2:
						p_shape = 2;
						break;
					case 3:
						p_shape = 3;
						break;
					}
				}

				else if (arr_block[i].color == color1) {
					p_color = 1;
				}
				else if (arr_block[i].color == color2) {
					p_color = 2;
				}
				else if (arr_block[i].color == color3) {
					p_color = 3;
				}

			}
			// 도착지점에 도달하면
			if (p_x == end_x && p_y == end_x) {
				if (p_color == end_color) {
					if (p_shape == end_shape) {
						PostQuitMessage(0);
					}
					else break;
				}
				else break;
			}
		}

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		// 40 X 40 판 그리기
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);

		for (int j = 0; j < 40; ++j) {
			for (int i = 0; i < 40; ++i) {
				Rectangle(hDC, 0 + i * 20, 0 + j * 20, 20 + i * 20, 20 + j * 20);
			}
		}
		
		// 목표 지점 그리기
		switch (end_shape) {
		case 1:
			switch (end_color) {
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Ellipse(hDC, end_x, end_x, end_x + 20, end_x + 20);
			break;
		case 2:
			switch (end_color) {
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Pie(hDC, end_x, end_x, end_x + 20, end_x + 20, end_x + 10, end_x, end_x + 20, end_x + 10);
			break;
		case 3:
			switch (end_color) {
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Pie(hDC, end_x, end_x, end_x + 20, end_x + 20, end_x + 10, end_x, end_x + 10, end_x + 20);
			break;
		}
		

		// 플레이어 그리기
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		
		switch (p_shape) {
		case 0:
			switch (p_color) {
			case 0:
				hBrush = CreateSolidBrush(color_black);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Rectangle(hDC, p_x + p_size, p_y + p_size, p_x + 20 - p_size, p_y + 20 - p_size);
			break;
		case 1:
			switch (p_color) {
			case 0:
				hBrush = CreateSolidBrush(color_black);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Ellipse(hDC, p_x + p_size, p_y + p_size, p_x + 20 - p_size, p_y + 20 - p_size);
			break;
		case 2:
			switch (p_color) {
			case 0:
				hBrush = CreateSolidBrush(color_black);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Pie(hDC, p_x + p_size, p_y + p_size, p_x + 20 - p_size, p_y + 20 - p_size, p_x + 10, p_y + p_size, p_x + 20 - p_size, p_y + 10);
			break;
		case 3:
			switch (p_color) {
			case 0:
				hBrush = CreateSolidBrush(color_black);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 1:
				hBrush = CreateSolidBrush(color1);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 2:
				hBrush = CreateSolidBrush(color2);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			case 3:
				hBrush = CreateSolidBrush(color3);
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				break;
			}
			Pie(hDC, p_x + p_size, p_y + p_size, p_x + 20 - p_size, p_y + 20 - p_size, p_x + 10, p_y + p_size, p_x + 10, p_y + 20 - p_size);
			break;
		}

		// 20개의 블럭들 그리기
		for (int i = 0; i < 20; ++i) {
			RECT temp = { arr_block[i].x, arr_block[i].y, arr_block[i].x + 20, arr_block[i].y + 20 };
			hBrush = CreateSolidBrush(arr_block[i].color);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			if (arr_block[i].shape == 0) {
				FillRect(hDC, &temp, hBrush);
			}
			else if (arr_block[i].shape == 1) {
				Ellipse(hDC, arr_block[i].x, arr_block[i].y, arr_block[i].x + 20, arr_block[i].y + 20);
			}
			else if (arr_block[i].shape == 2) {
				Pie(hDC, arr_block[i].x, arr_block[i].y, arr_block[i].x + 20, arr_block[i].y + 20, arr_block[i].x + 10, arr_block[i].y, arr_block[i].x + 20, arr_block[i].y + 10);
			}
			else if (arr_block[i].shape == 3) {
				Pie(hDC, arr_block[i].x, arr_block[i].y, arr_block[i].x + 20, arr_block[i].y + 20, arr_block[i].x + 10, arr_block[i].y, arr_block[i].x + 10, arr_block[i].y + 20);
			}
		}


		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		EndPaint(hWnd, &ps);
		break;



	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}