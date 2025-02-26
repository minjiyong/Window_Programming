#include<windows.h>
#include<tchar.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
int wsprintf(LPTSTR lpOut, LPCTSTR lpFmt);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR IpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	srand(time(NULL));
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct rect {
	int shape;
	int x, y;
	int x1, y1;
	int r, g, b;
	int r1, g1, b1;
	int tin;
	int  nerby1 = 0, nerby2 = 0;
};
struct rect re[10];
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static TCHAR str[50];
	static SIZE size;
	POINT point0[8] = { {0,530},{0,560}, {600, 560} ,{600, 530} };
	static int x, y, x1, y1;
	static int shape;
	static int tin;
	static int count2 = 0;
	static int r, g, b, r1, g1, b1;
	static int m = 0, n = 0;
	static int i = 0, k = 0;
	static int end = 0;
	switch (iMsg) {
	case WM_CREATE:
		count2 = 0;
		CreateCaret(hwnd, NULL, 2, 15);
		ShowCaret(hwnd);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		if (wParam == VK_RIGHT) {
			re[k].x++;
			re[k].x1++;
			m++;
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_LEFT) {
			re[k].x--;
			re[k].x1--;
			m--;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_UP) {
			re[k].y--;
			re[k].y1--;
			n--;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_DOWN) {
			re[k].y++;
			re[k].y1++;
			n++;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '1') {
			re[k].r = rand() % 255;
			re[k].g = rand() % 255;
			re[k].b = rand() % 255;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == '2') {
			re[k].r1 = rand() % 255;
			re[k].g1 = rand() % 255;
			re[k].b1 = rand() % 255;
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_F1) {
			k--;
			if (k < 0) {
				k = 0;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_F2) {
			k++;
			if (k > i - 1) {
				k--;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		else if (wParam == VK_F3) {
			end++;
			if (end > 1) {
				end = 0;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_BACK) {
			count2--;
			if (count2 <= 0) {
				count2 = 0;
			}
		}
		else if (wParam == VK_RETURN) {
			if (i > 9) {
				for (int i = 8; i > -1; i--) {
					re[i + 1] = re[i];
				}
			}
			_stscanf_s(str, L"%d %d %d %d %d %d", &re[i].shape, &re[i].x, &re[i].y, &re[i].x1, &re[i].y1, &re[i].tin);
			count2 = 0;
			re[i].r = rand() % 255;
			re[i].g = rand() % 255;
			re[i].b = rand() % 255;
			re[i].r1 = rand() % 255;
			re[i].g1 = rand() % 255;
			re[i].b1 = rand() % 255;
			k = i;
			i++;
		}
		else if (wParam == '+') {
			re[k].tin++;
			if (re[k].tin > 10) {
				re[k].tin = 10;
				re[k].nerby1++;
				re[k].nerby2++;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		}
		else if (wParam == '-') {
			re[k].tin--;
			if (re[k].tin < 1) {
				re[k].tin = 1;
				re[k].nerby1--;
				re[k].nerby2--;
			}
			InvalidateRgn(hwnd, NULL, TRUE);
			break;
		}
		else {
			str[count2++] = wParam;
		}
		str[count2] = '\0';
		InvalidateRect(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		Polygon(hdc, point0, 4);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		if (re[k].shape == 1) {
			POINT point1[4] = { {re[k].x - re[k].nerby1,re[k].y - re[k].nerby2},{re[k].x1 + re[k].nerby1,re[k].y1 + re[k].nerby2} };
			hPen = CreatePen(PS_SOLID, re[k].tin, RGB(re[k].r, re[k].g, re[k].b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point1, 2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hBrush = CreateSolidBrush(RGB(re[k].r1, re[k].g1, re[k].b1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point1, 2);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (re[k].shape == 3) {
			POINT point1[6] = { {re[k].x - re[k].nerby1,re[k].y + re[k].nerby2},{re[k].x1 + re[k].nerby1,re[k].y1 + re[k].nerby2}, {50 + m, 50 + n} };
			hPen = CreatePen(PS_SOLID, re[k].tin, RGB(re[k].r, re[k].g, re[k].b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Polygon(hdc, point1, 3);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hBrush = CreateSolidBrush(RGB(re[k].r1, re[k].g1, re[k].b1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, point1, 3);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (re[k].shape == 4) {
			hPen = CreatePen(PS_SOLID, re[k].tin, RGB(re[k].r, re[k].g, re[k].b));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			Rectangle(hdc, re[k].x - re[k].nerby1, re[k].y - re[k].nerby2, re[k].x1 + re[k].nerby1, re[k].y1 + re[k].nerby2);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			hBrush = CreateSolidBrush(RGB(re[k].r1, re[k].g1, re[k].b1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, re[k].x - re[k].nerby1, re[k].y - re[k].nerby2, re[k].x1 + re[k].nerby1, re[k].y1 + re[k].nerby2);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (re[k].shape == 6) {
			hBrush = CreateSolidBrush(RGB(re[k].r1, re[k].g1, re[k].b1));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, re[k].x - re[k].nerby1, re[k].y - re[k].nerby2, re[k].x1 + re[k].nerby1, re[k].y1 + re[k].nerby2);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		if (end == 1) {
			for (int j = 0; j < k; j++) {
				if (re[j].shape == 1) {
					POINT point1[4] = { {re[j].x - re[j].nerby1,re[j].y - re[j].nerby2},{re[j].x1 + re[j].nerby1,re[j].y1 + re[j].nerby2} };
					hPen = CreatePen(PS_SOLID, re[j].tin, RGB(re[j].r, re[j].g, re[j].b));
					oldPen = (HPEN)SelectObject(hdc, hPen);
					Polygon(hdc, point1, 2);
					SelectObject(hdc, oldPen);
					DeleteObject(hPen);
					hBrush = CreateSolidBrush(RGB(re[j].r1, re[j].g1, re[j].b1));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Polygon(hdc, point1, 2);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[j].shape == 2) {
					POINT point1[6] = { {re[j].x - re[j].nerby1,re[j].y + re[j].nerby2},{re[j].x1 + re[j].nerby1,re[j].y1 + re[j].nerby2}, {50 + m, 50 + n} };
					hPen = CreatePen(PS_SOLID, re[j].tin, RGB(re[j].r, re[j].g, re[j].b));
					oldPen = (HPEN)SelectObject(hdc, hPen);
					Polygon(hdc, point1, 3);
					SelectObject(hdc, oldPen);
					DeleteObject(hPen);
					hBrush = CreateSolidBrush(RGB(re[j].r1, re[j].g1, re[j].b1));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Polygon(hdc, point1, 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[j].shape == 3) {
					hPen = CreatePen(PS_SOLID, re[j].tin, RGB(re[j].r, re[j].g, re[j].b));
					oldPen = (HPEN)SelectObject(hdc, hPen);
					Rectangle(hdc, re[j].x - re[j].nerby1, re[j].y - re[j].nerby2, re[j].x1 + re[j].nerby1, re[j].y1 + re[j].nerby2);
					SelectObject(hdc, oldPen);
					DeleteObject(hPen);
					hBrush = CreateSolidBrush(RGB(re[j].r1, re[j].g1, re[j].b1));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, re[j].x - re[j].nerby1, re[j].y - re[j].nerby2, re[j].x1 + re[j].nerby1, re[j].y1 + re[j].nerby2);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				if (re[j].shape == 4) {
					hPen = CreatePen(PS_SOLID, re[j].tin, RGB(re[j].r, re[j].g, re[j].b));
					oldPen = (HPEN)SelectObject(hdc, hPen);
					Ellipse(hdc, re[j].x - re[j].nerby1, re[j].y - re[j].nerby2, re[j].x1 + re[j].nerby1, re[j].y1 + re[j].nerby2);
					SelectObject(hdc, oldPen);
					DeleteObject(hPen);
					hBrush = CreateSolidBrush(RGB(re[j].r1, re[j].g1, re[j].b1));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, re[j].x - re[j].nerby1, re[j].y - re[j].nerby2, re[j].x1 + re[j].nerby1, re[j].y1 + re[j].nerby2);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}
		TextOut(hdc, 10, 540, str, lstrlen(str));
		GetTextExtentPoint32(hdc, str, lstrlen(str), &size);
		SetCaretPos(size.cx + 10, 540);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}