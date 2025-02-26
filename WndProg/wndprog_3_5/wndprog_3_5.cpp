// [실습 3-5] 도형 회전하기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define poly_start_num 10
#define poly_num 20

#define clock 1
#define revclock 2

#define mini_aside 5


class Poly {
public:
	int x{};
	int y{};
	int aside{};
	int dir{};
	COLORREF color{ RGB(0, 0, 0) };
	bool select{ false };

	int rad{ 1 };
	int mini_x{};
	int mini_y{};

	int line1_endx{};
	int line1_endy{};

	int line2_sx{};
	int line2_sy{};
	int line2_endx{};
	int line2_endy{};

	int line3_sx{};
	int line3_sy{};
	int line3_endx{};
	int line3_endy{};

	Poly() {};
	~Poly() {};

	void poly_initialize() {
		x = 100 + rand() % (WINDOW_WIDTH - 200);
		y = 100 + rand() % (WINDOW_HEIGHT - 200);
		aside = 20 + rand() % 30;
		color = RGB(rand() % 255, rand() % 255, rand() % 255);
		dir = rand() % 2 + 1;
	};

	void poly_initialize_xy(int px, int py) {
		x = px;
		y = py;
		aside = 20 + rand() % 30;
		color = RGB(rand() % 255, rand() % 255, rand() % 255);
		dir = rand() % 2 + 1;
	}

	void poly_delete() {
		x = -1000;
		y = -1000;
	}
};


Poly poly_arr[poly_num]{};


void Initialize();
void swap(int& a, int& b);

void draw_poly(HDC mDC);
void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_line(HDC mDC, int x1, int y1, int x2, int y2);


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
	WndClass.lpszMenuName = NULL;
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

	static bool timer_stop{ false };

	static bool left_drag_check{ false };
	static bool right_drag_check{ false };
	static int temp_x{};
	static int temp_y{};

	static int poly_index{ poly_start_num };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		SetTimer(hWnd, 1, 10, NULL);
		Initialize();
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1번 아이디 타이머: 0.5초 간격으로 실행
			for (int i = 0; i < poly_num; ++i) {
				double temp_rad = poly_arr[i].rad * (M_PI / 180);
				poly_arr[i].mini_x = poly_arr[i].x + poly_arr[i].aside * cos(temp_rad);
				poly_arr[i].mini_y = poly_arr[i].y + poly_arr[i].aside * sin(temp_rad);

				poly_arr[i].line1_endx = 2 * poly_arr[i].x - poly_arr[i].mini_x;
				poly_arr[i].line1_endy = 2 * poly_arr[i].y - poly_arr[i].mini_y;

				int relX{ poly_arr[i].mini_x - poly_arr[i].x };
				int relY{ poly_arr[i].mini_y - poly_arr[i].y };
				poly_arr[i].line2_sx = poly_arr[i].x + relX * cos(M_PI / 4) - relY * sin(M_PI / 4);
				poly_arr[i].line2_sy = poly_arr[i].y + relX * sin(M_PI / 4) + relY * cos(M_PI / 4);
				poly_arr[i].line2_endx = 2 * poly_arr[i].x - poly_arr[i].line2_sx;
				poly_arr[i].line2_endy = 2 * poly_arr[i].y - poly_arr[i].line2_sy;

				relX =  poly_arr[i].line2_sx - poly_arr[i].x;
				relY =  poly_arr[i].line2_sy - poly_arr[i].y;
				poly_arr[i].line3_sx = poly_arr[i].x + relX * cos(M_PI / 4) - relY * sin(M_PI / 4);
				poly_arr[i].line3_sy = poly_arr[i].y + relX * sin(M_PI / 4) + relY * cos(M_PI / 4);
				poly_arr[i].line3_endx = 2 * poly_arr[i].x - poly_arr[i].line3_sx;
				poly_arr[i].line3_endy = 2 * poly_arr[i].y - poly_arr[i].line3_sy;

				if(poly_arr[i].dir == clock) ++poly_arr[i].rad;
				else if(poly_arr[i].dir == revclock) --poly_arr[i].rad;
			}

			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'r' || wParam == 'R') {
			Initialize();
			SetTimer(hWnd, 1, 10, NULL);
		}

		else if (wParam == 's' || wParam == 'S') {
			if (timer_stop) {
				SetTimer(hWnd, 1, 10, NULL);
				timer_stop = false;
			}
			else {
				KillTimer(hWnd, 1);
				timer_stop = true;
			}
		}
		else if (wParam == 'c' || wParam == 'C') {
			for (int i = 0; i < poly_num; ++i) {
				poly_arr[i].color = RGB(255, 255, 255) - poly_arr[i].color;
			}
		}
		
		else if (wParam == '1') {
			for (int i = 0; i < poly_num; ++i) {
				if (poly_arr[i].dir == clock) poly_arr[i].dir = revclock;
				else if (poly_arr[i].dir == revclock) poly_arr[i].dir = clock;
			}
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_LBUTTONDOWN:
		left_drag_check = true;
		
		temp_x = LOWORD(lParam);
		temp_y = HIWORD(lParam);
		for (int i = 0; i < poly_num; ++i) {
			if (poly_arr[i].x - poly_arr[i].aside < LOWORD(lParam) && poly_arr[i].x + poly_arr[i].aside > LOWORD(lParam)
				&& poly_arr[i].y - poly_arr[i].aside < HIWORD(lParam) && poly_arr[i].y + poly_arr[i].aside > HIWORD(lParam)) {
				poly_arr[i].select = true;
			}
			else poly_arr[i].select = false;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		left_drag_check = false;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_RBUTTONDOWN:
		right_drag_check = true;

		temp_x = LOWORD(lParam);
		temp_y = HIWORD(lParam);
		poly_arr[poly_index].poly_initialize_xy(temp_x, temp_y);
		++poly_index;
		if (poly_index == poly_num) poly_index = poly_start_num;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_RBUTTONUP:
		right_drag_check = false;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		if (left_drag_check) {
			int deltaX = LOWORD(lParam) - temp_x;
			int deltaY = HIWORD(lParam) - temp_y;

			for (int i = 0; i < poly_num; ++i) {
				if (poly_arr[i].select) {
					poly_arr[i].x += deltaX;
					poly_arr[i].y += deltaY;
				}
			}

			temp_x = LOWORD(lParam);
			temp_y = HIWORD(lParam);
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기


		draw_poly(mDC);


		//--- 마지막에 메모리 DC의 내용을 화면 DC로 복사한다.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- 생성한 메모리 DC 삭제
		DeleteObject(hBitmap); //--- 생성한 비트맵 삭제

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
	for (int i = 0; i < poly_start_num; ++i) {
		poly_arr[i].poly_initialize();
	}
	for (int i = poly_start_num; i < poly_num; ++i) {
		poly_arr[i].poly_delete();
	}
}

void swap(int& a, int& b) {
	int temp{};
	temp = a;
	a = b;
	b = temp;
}

void draw_poly(HDC mDC) {
	for(int i = 0; i < poly_num; ++i){
		draw_circle(mDC, poly_arr[i].x, poly_arr[i].y, poly_arr[i].aside, poly_arr[i].color);
		draw_circle(mDC, poly_arr[i].mini_x, poly_arr[i].mini_y, mini_aside, RGB(255, 255, 0));
		draw_line(mDC, poly_arr[i].mini_x, poly_arr[i].mini_y, poly_arr[i].line1_endx, poly_arr[i].line1_endy);
		draw_line(mDC, poly_arr[i].line2_sx, poly_arr[i].line2_sy, poly_arr[i].line2_endx, poly_arr[i].line2_endy);
		draw_line(mDC, poly_arr[i].line3_sx, poly_arr[i].line3_sy, poly_arr[i].line3_endx, poly_arr[i].line3_endy);
	}
}

void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Ellipse(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
}

void draw_line(HDC mDC, int x1, int y1, int x2, int y2) {
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	LPPOINT lppt{};
	MoveToEx(mDC, x1, y1, lppt);
	LineTo(mDC, x2, y2);

	hPen = (HPEN)SelectObject(mDC, oldPen); // 새로운 펜 선택하기
	DeleteObject(hPen);
}