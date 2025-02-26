// [�ǽ� 4-2] �޴��� �ִ� �׸��� �����
#include <windows.h>			// ������ ��� ����
#include <TCHAR.H>
#include <ctime>
#include "resource.h"

#define WINDOW_WIDTH 815
#define WINDOW_HEIGHT 860

#define board_x_max 40
#define board_y_max 40
#define board_aside 20

#define poly_num 5
#define border_on 5
#define border_off 0

#define RIGHT 1
#define LEFT 2

#define DOWN 1
#define UP 2



class Poly {
public:
	int x{};
	int y{};
	int endx{};
	int endy{};
	COLORREF color{RGB(0, 0, 0)};
	bool select{ false };

	Poly() {};
	~Poly() {};

	void poly_initialize() {
		x = NULL;
		y = NULL;
	};

	void poly_adjust() {
		x = x - x % board_aside;
		y = y - y % board_aside;
		endx = endx - endx % board_aside;
		endy = endy - endy % board_aside;
	};
};


Poly poly_arr[poly_num]{};


void Initialize();
void swap(int& a, int& b);

void poly_select_check(int n);
void poly_overlap(HDC mDC);

void print_status(HDC mDC);
void draw_poly(HDC mDC, bool border);
void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color, COLORREF border_color, int border);
void draw_board(HDC mDC, int pen);


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //--- �޴� id ���;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

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
	RECT rt{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	HBITMAP hBitmap;
	HDC hDC, mDC;
	
	static int board_line_type{ PS_SOLID };
	static bool border{ true };
	static bool status{ false };
	static bool move_on{ true };

	static int temp_x{};
	static int temp_y{};

	static int poly_index{ 0 };
	static int selected_poly_index{};

	static bool left_drag_check{ false };
	static bool right_drag_check{ false };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case ID_GRID_LINE:
			board_line_type = PS_SOLID;
			break;
		case ID_GRID_DOT:
			board_line_type = PS_DOT;
			break;

		case ID_COLOR_RED:
			poly_arr[poly_index].color = RGB(255, 0, 0);
			break;
		case ID_COLOR_GREEN:
			poly_arr[poly_index].color = RGB(0, 255, 0);
			break;
		case ID_COLOR_BLUE:
			poly_arr[poly_index].color = RGB(0, 0, 255);
			break;
		case ID_COLOR_YELLOW:
			poly_arr[poly_index].color = RGB(255, 255, 0);
			break;
		case ID_COLOR_MAGENTA:
			poly_arr[poly_index].color = RGB(255, 0, 255);
			break;
		case ID_COLOR_CYAN:
			poly_arr[poly_index].color = RGB(0, 255, 255);
			break;

		case ID_MOVE_ON:
			move_on = true;
			break;
		case ID_MOVE_OFF:
			move_on = false;
			break;

		case ID_BORDER_ON:
			border = true;
			break;
		case ID_BORDER_OFF:
			border = false;
			break;

		case ID_INFORM_ON:
			status = true;
			break;
		case ID_INFORM_OFF:
			status = false;
			break;

		}
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		for (int i = 0; i < poly_num; ++i) {
			if (poly_arr[i].select) {
				selected_poly_index = i;
			}
		}

		if (wParam == VK_UP) {
			if (poly_arr[selected_poly_index].y == 0) {
				int poly_aside{ poly_arr[selected_poly_index].endy - poly_arr[selected_poly_index].y };
				poly_arr[selected_poly_index].y = board_aside * (board_y_max - 1);
				poly_arr[selected_poly_index].endy = poly_arr[selected_poly_index].y + poly_aside;
			}
			else {
				poly_arr[selected_poly_index].endy -= board_aside;
				poly_arr[selected_poly_index].y -= board_aside;
			}
		}
		else if (wParam == VK_LEFT) {
			if (poly_arr[selected_poly_index].x == 0) {
				int poly_aside{ poly_arr[selected_poly_index].endx - poly_arr[selected_poly_index].x };
				poly_arr[selected_poly_index].x = board_aside * (board_x_max - 1);
				poly_arr[selected_poly_index].endx = poly_arr[selected_poly_index].x + poly_aside;
			}
			else {
				poly_arr[selected_poly_index].endx -= board_aside;
				poly_arr[selected_poly_index].x -= board_aside;
			}
		}
		else if (wParam == VK_DOWN) {
			if (poly_arr[selected_poly_index].endy == board_aside * board_y_max) {
				int poly_aside{ poly_arr[selected_poly_index].endy - poly_arr[selected_poly_index].y };
				poly_arr[selected_poly_index].y = 0 - poly_aside;
				poly_arr[selected_poly_index].endy = 0;
			}
			else {
				poly_arr[selected_poly_index].endy += board_aside;
				poly_arr[selected_poly_index].y += board_aside;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (poly_arr[selected_poly_index].endx == board_aside * board_x_max) {
				int poly_aside{ poly_arr[selected_poly_index].endx - poly_arr[selected_poly_index].x };
				poly_arr[selected_poly_index].x = 0 - poly_aside;
				poly_arr[selected_poly_index].endx = 0;
			}
			else {
				poly_arr[selected_poly_index].endx += board_aside;
				poly_arr[selected_poly_index].x += board_aside;
			}
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'n' || wParam == 'N') {
			Initialize();
		}

		else if (wParam == '1') {
			int num = 1;
			poly_select_check(num);
		}
		else if (wParam == '2') {
			int num = 2;
			poly_select_check(num);
		}
		else if (wParam == '3') {
			int num = 3;
			poly_select_check(num);
		}
		else if (wParam == '4') {
			int num = 4;
			poly_select_check(num);
		}
		else if (wParam == '5') {
			int num = 5;
			poly_select_check(num);
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_LBUTTONDOWN:
		left_drag_check = true;
		poly_arr[poly_index].x = LOWORD(lParam);
		poly_arr[poly_index].y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		left_drag_check = false;
		poly_arr[poly_index].endx = LOWORD(lParam);
		poly_arr[poly_index].endy = HIWORD(lParam);
		poly_arr[poly_index].poly_adjust();

		if (poly_arr[poly_index].x > poly_arr[poly_index].endx) swap(poly_arr[poly_index].x, poly_arr[poly_index].endx);
		if (poly_arr[poly_index].y > poly_arr[poly_index].endy) swap(poly_arr[poly_index].y, poly_arr[poly_index].endy);

		poly_index++;
		if (poly_index == poly_num) poly_index = 0;
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_RBUTTONDOWN:
		right_drag_check = true;
		temp_x = LOWORD(lParam);
		temp_y = HIWORD(lParam);
		for (int i = 0; i < poly_num; ++i) {
			if (poly_arr[i].x < LOWORD(lParam) && poly_arr[i].endx > LOWORD(lParam)
				&& poly_arr[i].y < HIWORD(lParam) && poly_arr[i].endy > HIWORD(lParam)) {
				poly_arr[i].select = true;
			}
			else poly_arr[i].select = false;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_RBUTTONUP:
		right_drag_check = false;
		for (int i = 0; i < poly_num; ++i) {
			poly_arr[i].poly_adjust();
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		if (left_drag_check) {
			poly_arr[poly_index].endx = LOWORD(lParam);
			poly_arr[poly_index].endy = HIWORD(lParam);
		}

		if (right_drag_check) {
			if (move_on) {
				int deltaX = LOWORD(lParam) - temp_x;
				int deltaY = HIWORD(lParam) - temp_y;

				for (int i = 0; i < poly_num; ++i) {
					if (poly_arr[i].select) {
						poly_arr[i].x += deltaX;
						poly_arr[i].y += deltaY;
						poly_arr[i].endx += deltaX;
						poly_arr[i].endy += deltaY;
					}
				}

				temp_x = LOWORD(lParam);
				temp_y = HIWORD(lParam);
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- �޸� DC �����
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- �޸� DC�� ������ ��Ʈ�� �����
		SelectObject(mDC, (HBITMAP)hBitmap); //--- �޸� DC�� ��Ʈ�� �����ϱ�
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- ȭ�鿡 ����ֱ� ������ ȭ�� ������ �簢���� �׷� �������� �����ϱ�

		
		draw_board(mDC, board_line_type);

		draw_poly(mDC, border);
		poly_overlap(mDC);

		if (status) print_status(mDC);


		//--- �������� �޸� DC�� ������ ȭ�� DC�� �����Ѵ�.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- ������ �޸� DC ����
		DeleteObject(hBitmap); //--- ������ ��Ʈ�� ����

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



void Initialize()
{
	for (int i = 0; i < poly_num; ++i) {
		poly_arr[i].poly_initialize();
	}
}

void swap(int& a, int& b) {
	int temp{};
	temp = a;
	a = b;
	b = temp;
}

void poly_select_check(int n) {
	for (int i = 0; i < poly_num; ++i) {
		if (i == (n - 1)) {
			poly_arr[i].select = true;
			continue;
		}
		poly_arr[i].select = false;
	}
}

void poly_overlap(HDC mDC) {
	for (int i = 0; i < poly_num; ++i) {
		for (int j = 0; j < poly_num; ++j) {
			RECT rc1 = { poly_arr[j].x, poly_arr[j].y , poly_arr[j].endx , poly_arr[j].endy };
			RECT rc2 = { poly_arr[i].x, poly_arr[i].y , poly_arr[i].endx , poly_arr[i].endy };
			RECT ovrc{};

			if (poly_arr[j].x == poly_arr[i].x && poly_arr[j].y == poly_arr[i].y && poly_arr[j].endx == poly_arr[i].endx && poly_arr[j].endy == poly_arr[i].endy) continue;

			if (IntersectRect(&ovrc, &rc1, &rc2)) {
				draw_rectangle(mDC, ovrc.left, ovrc.top, ovrc.right, ovrc.bottom, poly_arr[j].color + poly_arr[i].color, RGB(255, 255, 255), border_off);
			}
		}
	}
}

void print_status(HDC mDC) {
	TCHAR temp[80]{};
	TCHAR temp1[80]{};
	TCHAR temp2[80]{};
	TCHAR temp3[80]{};
	TCHAR temp4[80]{};
	TCHAR temp5[80]{};
	int poly_n{ 0 };
	int poly_x_aside[poly_num]{};
	int poly_y_aside[poly_num]{};
	TCHAR poly_color[poly_num][80]{};

	for (int i = 0; i < poly_num; ++i) {
		if (poly_arr[i].x != NULL) {
			++poly_n;

			poly_x_aside[i] = (poly_arr[i].endx - poly_arr[i].x) / board_aside;
			poly_y_aside[i] = (poly_arr[i].endy - poly_arr[i].y) / board_aside;
			if (poly_x_aside[i] < 0) poly_x_aside[i] = -poly_x_aside[i];
			if (poly_y_aside[i] < 0) poly_y_aside[i] = -poly_y_aside[i];

			switch (poly_arr[i].color) {
			case RGB(0, 0, 0):
				wsprintf(poly_color[i], TEXT("BLACK"));
				break;
			case RGB(255, 0, 0):
				wsprintf(poly_color[i], TEXT("RED"));
				break;
			case RGB(0, 255, 0):
				wsprintf(poly_color[i], TEXT("GREEN"));
				break;
			case RGB(0, 0, 255):
				wsprintf(poly_color[i], TEXT("BLUE"));
				break;
			case RGB(255, 255, 0):
				wsprintf(poly_color[i], TEXT("YELLOW"));
				break;
			case RGB(255, 0, 255):
				wsprintf(poly_color[i], TEXT("MAGENTA"));
				break;
			case RGB(0, 255, 255):
				wsprintf(poly_color[i], TEXT("CYAN"));
				break;
			}
		}
	}

	wsprintf(temp, TEXT("������ ����: %d��"), poly_n);
	wsprintf(temp1, TEXT("���� 1 | ����: %dĭ, ���� : %dĭ"), poly_x_aside[0], poly_y_aside[0]);
	wsprintf(temp2, TEXT("���� 2 | ����: %dĭ, ���� : %dĭ"), poly_x_aside[1], poly_y_aside[1]);
	wsprintf(temp3, TEXT("���� 3 | ����: %dĭ, ���� : %dĭ"), poly_x_aside[2], poly_y_aside[2]);
	wsprintf(temp4, TEXT("���� 4 | ����: %dĭ, ���� : %dĭ"), poly_x_aside[3], poly_y_aside[3]);
	wsprintf(temp5, TEXT("���� 5 | ����: %dĭ, ���� : %dĭ"), poly_x_aside[4], poly_y_aside[4]);
	
	TextOut(mDC, 250, 600, temp, lstrlen(temp));
	TextOut(mDC, 250, 620, temp1, lstrlen(temp1));
	TextOut(mDC, 470, 620, poly_color[0], lstrlen(poly_color[0]));

	TextOut(mDC, 250, 640, temp2, lstrlen(temp2));
	TextOut(mDC, 470, 640, poly_color[1], lstrlen(poly_color[1]));

	TextOut(mDC, 250, 660, temp3, lstrlen(temp3));
	TextOut(mDC, 470, 660, poly_color[2], lstrlen(poly_color[2]));

	TextOut(mDC, 250, 680, temp4, lstrlen(temp4));
	TextOut(mDC, 470, 680, poly_color[3], lstrlen(poly_color[3]));

	TextOut(mDC, 250, 700, temp5, lstrlen(temp5));
	TextOut(mDC, 470, 700, poly_color[4], lstrlen(poly_color[4]));
}

void draw_poly(HDC mDC, bool border) {
	if (border) {
		for (int i = 0; i < poly_num; ++i) {
			if (poly_arr[i].select) {
				draw_rectangle(mDC, poly_arr[i].x, poly_arr[i].y, poly_arr[i].endx, poly_arr[i].endy, poly_arr[i].color, RGB(255, 255, 255), border_on);
			}
			else {
				draw_rectangle(mDC, poly_arr[i].x, poly_arr[i].y, poly_arr[i].endx, poly_arr[i].endy, poly_arr[i].color, RGB(0, 0, 0), border_on);
			}
		}
	}
	else {
		for (int i = 0; i < poly_num; ++i) {
			if (poly_arr[i].select) {
				draw_rectangle(mDC, poly_arr[i].x, poly_arr[i].y, poly_arr[i].endx, poly_arr[i].endy, poly_arr[i].color, RGB(255, 255, 255), border_off);
			}
			else {
				draw_rectangle(mDC, poly_arr[i].x, poly_arr[i].y, poly_arr[i].endx, poly_arr[i].endy, poly_arr[i].color, RGB(0, 0, 0), border_off);
			}
		}
	}
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color, COLORREF border_color, int border)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�
	HPEN hPen = CreatePen(PS_SOLID, border, border_color);
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void draw_board(HDC mDC, int pen) {
	// ������ �׸���
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);
	HPEN hPen = CreatePen(pen, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	for (int j = 0; j < board_y_max; ++j) {
		for (int i = 0; i < board_x_max; ++i) {
			Rectangle(mDC, i * board_aside, j * board_aside, board_aside + i * board_aside, board_aside + j * board_aside);
		}
	}
}