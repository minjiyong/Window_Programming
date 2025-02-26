#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include<time.h>
#include<stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2023 Window Programming Exam 2반 한인혁";	//____________부분에 *반 이름을 넣으세요

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
int  WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_  LPSTR lpszCmdParam, _In_  int nCmdShow)
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
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	//--- 크기 변경 가능 (기존 (1024, 768))
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 1000, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct Me {
	int x;
	int y;
	int x2;
	int y2;
};
struct Me me;

struct Jang {
	int x;
	int y;
	int x2;
	int y2;
	int destroy;
};
struct Jang jang[400];

struct Enemy {
	int x;
	int y;
	int x2;
	int y2;
};
struct Bull {
	int x;
	int y;
	int x2;
	int y2;
};
struct Bull bull[400];
struct Enemy enemy[20];
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC	hdc;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static BOOL Drag;
	static int oldx;
	static int oldy;
	static int jangnum = 0;
	static int jangCheck = 0;
	static int lrudCheck[400] = { 0 };
	static int move = 0;
	static int bullnum = 0;


	srand(time(NULL));
	switch (iMessage) {
	case WM_CREATE:
		me.x = 335;
		me.y = 335;
		me.x2 = 355;
		me.y2 = 355;
		for (int i = 0; i < 400; i++)
		{
			jang[i].x = 0;
			jang[i].y = 0;
			jang[i].x2 = 0;
			jang[i].y2 = 0;
			jang[i].destroy = 0;
			bull[i].x = 0;
			bull[i].y = 0;
			bull[i].x2 = 0;
			bull[i].y2 = 0;
		}
		for (int i = 0; i < 20; i++)
		{
			enemy[i].x = 30 * (rand() % 20 + 1);
			enemy[i].y = 30 * (rand() % 20 + 1);
			enemy[i].x2 = enemy[i].x + 30;
			enemy[i].y2 = enemy[i].y + 30;
		}
		SetTimer(hWnd, 1, 30, NULL);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (int i = 0; i < 5; i++)
			{
				enemy[i].x += 5;
				enemy[i].x2 += 5;
				if (enemy[i].x2 > 630)
				{
					enemy[i].x -= 600;
					enemy[i].x2 -= 600;
				}
			}
			for (int i = 5; i < 10; i++)
			{
				enemy[i].x -= 5;
				enemy[i].x2 -= 5;
				if (enemy[i].x < 30)
				{
					enemy[i].x += 600;
					enemy[i].x2 += 600;
				}
			}
			for (int i = 10; i < 15; i++)
			{
				enemy[i].y += 5;
				enemy[i].y2 += 5;
				if (enemy[i].y2 > 630)
				{
					enemy[i].y -= 600;
					enemy[i].y2 -= 600;
				}
			}
			for (int i = 15; i < 20; i++)
			{
				enemy[i].y -= 5;
				enemy[i].y2 -= 5;
				if (enemy[i].y < 30)
				{
					enemy[i].y += 600;
					enemy[i].y2 += 600;
				}
			}


			break;


		case 2://총알
			switch (lrudCheck[move - 1])
			{
			case 1://왼쪽
				for (int i = 0; i < bullnum; i++) {
					bull[i].x -= 10;
					bull[i].x2 -= 10;
				}

				break;
			case 2://오른쪽
				for (int i = 0; i < bullnum; i++) {
					bull[i].x += 10;
					bull[i].x2 += 10;
				}
				break;
			case 3://위쪽
				for (int i = 0; i < bullnum; i++) {
					bull[i].y -= 10;
					bull[i].y2 -= 10;
				}
				break;
			case 4://아래쪽
				for (int i = 0; i < bullnum; i++) {
					bull[i].y += 10;
					bull[i].y2 += 10;
				}
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen);
		for (int i = 0; i < 21; i++) {//맵만들기

			MoveToEx(hdc, 630, 30 + 30 * i, NULL);
			LineTo(hdc, 30, 30 + 30 * i);
		}
		for (int i = 0; i < 21; i++) {

			MoveToEx(hdc, 30 + 30 * i, 630, NULL);
			LineTo(hdc, 30 + 30 * i, 30);
		}
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, me.x, me.y, me.x2, me.y2);//주인공 그리기
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);//장애물 만들기

		for (int i = 0; i < jangnum; i++)
		{
			if (jang[i].destroy == 1)//파괴된 장애물은 그리지 않음
				continue;
			jang[i].x2 = jang[i].x + 30;
			jang[i].y2 = jang[i].y + 30;
			Rectangle(hdc, jang[i].x, jang[i].y, jang[i].x2, jang[i].y2);
		}
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 200));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);//적 만들기
		for (int i = 0; i < 20; i++)
		{
			Ellipse(hdc, enemy[i].x, enemy[i].y, enemy[i].x2, enemy[i].y2);
		}
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);//총알 만들기
		for (int i = 0; i < bullnum; i++)
		{
			Rectangle(hdc, bull[i].x, bull[i].y, bull[i].x2, bull[i].y2);
		}

		for (int i = 0; i < jangnum; i++)
		{

		}


		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		if (jangCheck < 4)// 장애물을 4번 만들면 더이상 만들 수 없게 함
		{
			Drag = TRUE;

			oldx = LOWORD(lParam);
			oldy = HIWORD(lParam);
			jang[jangnum].x = oldx - oldx % 30;
			jang[jangnum].y = oldy - oldy % 30;
			jangnum++;
		}
		break;
	case WM_LBUTTONUP:
		Drag = FALSE;
		jangCheck++;
		break;
	case WM_MOUSEMOVE:
		if (Drag) {
			jang[jangnum].x = LOWORD(lParam) - (LOWORD(lParam) % 30);
			jang[jangnum].y = HIWORD(lParam) - (HIWORD(lParam) % 30);
			if (jang[jangnum].x != jang[jangnum - 1].x || jang[jangnum].y != jang[jangnum - 1].y)
			{
				jangnum++;
			}




		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			me.x -= 30;
			me.x2 -= 30;
			for (int i = 0; i < jangnum; i++)
			{
				if (me.x2 < jang[i].x2 && me.x>jang[i].x && me.y > jang[i].y && me.y2 < jang[i].y2)
				{
					me.x += 30;
					me.x2 += 30;
				}
			}
			lrudCheck[move] = 1;
			move++;
			break;
		case VK_RIGHT:
			me.x += 30;
			me.x2 += 30;
			for (int i = 0; i < jangnum; i++)
			{
				if (me.x2 < jang[i].x2 && me.x>jang[i].x && me.y > jang[i].y && me.y2 < jang[i].y2)
				{
					me.x -= 30;
					me.x2 -= 30;
				}
			}
			lrudCheck[move] = 2;
			move++;
			break;
		case VK_UP:
			me.y -= 30;
			me.y2 -= 30;
			for (int i = 0; i < jangnum; i++)
			{
				if (me.x2 < jang[i].x2 && me.x>jang[i].x && me.y > jang[i].y && me.y2 < jang[i].y2)
				{
					me.y += 30;
					me.y2 += 30;
				}
			}
			lrudCheck[move] = 3;
			move++;
			break;
		case VK_DOWN:
			me.y += 30;
			me.y2 += 30;
			for (int i = 0; i < jangnum; i++)
			{
				if (me.x2 < jang[i].x2 && me.x>jang[i].x && me.y > jang[i].y && me.y2 < jang[i].y2)
				{
					me.y -= 30;
					me.y2 -= 30;
				}
			}
			lrudCheck[move] = 4;
			move++;
			break;
		case VK_RETURN:


			bull[bullnum].x = (me.x + me.x2) / 2;
			bull[bullnum].y = (me.y + me.y2) / 2;
			bull[bullnum].x2 = bull[bullnum].x + 5;
			bull[bullnum].y2 = bull[bullnum].y + 5;
			SetTimer(hWnd, 2, 10, NULL);
			bullnum++;
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
