// [�ǽ� 4-1] �������� �ǽ��� �޴� ���̱�
#include <windows.h>			// ������ ��� ����
#include <TCHAR.H>
#include <ctime>
#include "resource.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

#define board_x_max 10
#define board_y_max 5
#define block_x_aside 60
#define block_y_aside 20

#define block_num 50
#define player_shape -1

#define RIGHT 1
#define LEFT 2

#define DOWN 1
#define UP 2

#define DELETED_X -300
#define DELETED_Y -2000

int current_block{ 30 };

class Ball {
public:
	int x{ 400 };
	int y{ 50 };
	int speed{ 0 };
	int dir1{ RIGHT };
	int dir2{ DOWN };
	COLORREF color{};

	Ball() {
		speed = rand() % 3 + 1;
	};
	~Ball() {};

	void ball_initialize() {
		speed = rand() % 3 + 1;
		x = 400;
		y = 50;
		dir1 = RIGHT;
		dir2 = DOWN;
		color = RGB(0, 255, 0);
	};
};

class Block {
public:
	int x{};
	int y{};
	int hp{ 1 };
	int dir1{ RIGHT };

	Block() {};
	Block(int b_x, int b_y) :x(b_x), y(b_y) {};
	~Block() {};

	void block_initialize() {
		hp = 1;
	};

	void delete_block() {
		hp = 0;
		x = DELETED_X;
		y = DELETED_Y;
	}
};


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";

Block block_arr[block_num]{};
Ball ball{};
int ball_aside = 20;

void Initialize();
bool check_hit();
void ball_spd_check();
void block_border_check();

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_circle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void print_deleted_block(HDC mDC);

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

	static bool print_deleted{ false };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case ID_GAME_START:
			SetTimer(hWnd, 1, 10, NULL);
			break;
		case ID_GAME_RESET:
			KillTimer(hWnd, 1);
			Initialize();
			break;
		case ID_GAME_END:
			PostQuitMessage(0);
			break;

		case ID_SPEED_FAST:
			ball.speed = 3;
			break;
		case ID_SPEED_MEDIUM:
			ball.speed = 2;
			break;
		case ID_SPEED_SLOW:
			ball.speed = 1;
			break;

		case ID_COLOR_CYAN:
			ball.color = RGB(0, 255, 255);
			break;
		case ID_COLOR_MAGENTA:
			ball.color = RGB(255, 0, 255);
			break;
		case ID_COLOR_YELLOW:
			ball.color = RGB(255, 255, 0);
			break;

		case ID_SIZE_SMALL:
			ball_aside = 10;
			break;
		case ID_SIZE_BIG:
			ball_aside = 20;
			break;
		
		case ID_NUMBER_3:
			current_block = 30;
			Initialize();
			for (int i = current_block; i < block_num; ++i) block_arr[i].delete_block();
			break;
		case ID_NUMBER_4:
			current_block = 40;
			Initialize();
			for (int i = current_block; i < block_num; ++i) block_arr[i].delete_block();
			break;
		case ID_NUMBER_5:
			current_block = 50;
			Initialize();
			for (int i = current_block; i < block_num; ++i) block_arr[i].delete_block();
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1�� ���̵� Ÿ�̸�: 0.01�� �������� ����
			ball_spd_check();
			block_border_check();
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;


	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'n' || wParam == 'N') {
			Initialize();
		}

		else if (wParam == 'p' || wParam == 'P') {
			KillTimer(hWnd, 1);
			print_deleted = true;
		}
		else if (wParam == 's' || wParam == 'S') {
			SetTimer(hWnd, 1, 10, NULL);
			print_deleted = false;
		}

		else if (wParam == '+') {
			if (ball.speed == 3) ball.speed = 1;
			else ball.speed++;
		}
		else if (wParam == '-') {
			if (ball.speed == 1) ball.speed = 3;
			else ball.speed--;
		}

		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_LBUTTONDOWN:
		for (int i = 0; i < block_num; ++i) {
			block_arr[i].x -= 20;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		for (int i = 0; i < block_num; ++i) {
			block_arr[i].x += 20;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- �޸� DC �����
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- �޸� DC�� ������ ��Ʈ�� �����
		SelectObject(mDC, (HBITMAP)hBitmap); //--- �޸� DC�� ��Ʈ�� �����ϱ�
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- ȭ�鿡 ����ֱ� ������ ȭ�� ������ �簢���� �׷� �������� �����ϱ�

		draw_circle(mDC, ball.x, ball.y, ball.x + ball_aside, ball.y + ball_aside, ball.color);

		for (int i = 0; i < block_num; ++i) {
			if (block_arr[i].hp <= 0) continue;
			draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, block_arr[i].x + block_x_aside, block_arr[i].y + block_y_aside, RGB(255, 255, 0));
		}

		if (print_deleted) print_deleted_block(mDC);

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
	int index{ 0 };
	for (int j = 0; j < board_y_max; ++j) {
		for (int i = 0; i < board_x_max; ++i) {
			block_arr[index].x = 130 + i * block_x_aside;
			block_arr[index].y = 700 + j * block_y_aside;
			index++;
		}
	}
	for (int i = 0; i < block_num; ++i) block_arr[i].block_initialize();
	ball.ball_initialize();
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
}

void draw_circle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�

	Ellipse(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
}

void print_deleted_block(HDC mDC) {
	int deleted_block{ 0 };
	for (int i = 0; i < block_num; ++i) {
		if (block_arr[i].hp <= 0) {
			deleted_block++;
		}
	}
	TCHAR temp[80]{};
	wsprintf(temp, TEXT("������ ����: %d��"), deleted_block);
	TextOut(mDC, 350, WINDOW_HEIGHT - 80, temp, lstrlen(temp));
}

bool check_hit() {
	int ball_r = ball_aside / 2;
	for (int i = 0; i < block_num; ++i) {
		int ball_x_middle{ ball.x + ball_r };
		int ball_y_middle{ ball.y + ball_r };
		if (block_arr[i].x - ball_r <= ball_x_middle && block_arr[i].x + block_x_aside + ball_r >= ball_x_middle && block_arr[i].y - ball_r <= ball_y_middle && block_arr[i].y + block_y_aside + ball_r >= ball_y_middle) {
			block_arr[i].hp--;
			block_arr[i].x = DELETED_X;
			block_arr[i].y = DELETED_Y;
			return true;
		}
	}
	return false;
}

void ball_spd_check() {
	if (ball.speed == 1) {
		if (ball.dir1 == RIGHT && ball.dir2 == DOWN) {
			ball.x += 3;
			ball.y += 1;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == DOWN) {
			ball.x -= 3;
			ball.y += 1;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
		else if (ball.dir1 == RIGHT && ball.dir2 == UP) {
			ball.x += 3;
			ball.y -= 1;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == UP) {
			ball.x -= 3;
			ball.y -= 1;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
	}
	else if (ball.speed == 2) {
		if (ball.dir1 == RIGHT && ball.dir2 == DOWN) {
			ball.x += 3;
			ball.y += 3;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == DOWN) {
			ball.x -= 3;
			ball.y += 3;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
		else if (ball.dir1 == RIGHT && ball.dir2 == UP) {
			ball.x += 3;
			ball.y -= 3;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == UP) {
			ball.x -= 3;
			ball.y -= 3;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
	}
	else if (ball.speed == 3) {
		if (ball.dir1 == RIGHT && ball.dir2 == DOWN) {
			ball.x += 3;
			ball.y += 5;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == DOWN) {
			ball.x -= 3;
			ball.y += 5;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
		else if (ball.dir1 == RIGHT && ball.dir2 == UP) {
			ball.x += 3;
			ball.y -= 5;
			if (ball.x >= 865) {
				ball.dir1 = LEFT;
			}
		}
		else if (ball.dir1 == LEFT && ball.dir2 == UP) {
			ball.x -= 3;
			ball.y -= 5;
			if (ball.x <= 0) {
				ball.dir1 = RIGHT;
			}
		}
	}

	if (ball.y <= 0) ball.dir2 = DOWN;
	else if (check_hit()) {
		ball.dir2 = UP;
	}
}

void block_border_check() {
	if (block_arr[0].dir1 == LEFT) {
		for (int i = 0; i < block_num; ++i) {
			block_arr[i].x--;
		}
		if (block_arr[0].x <= 0) block_arr[0].dir1 = RIGHT;
	}
	if (block_arr[0].dir1 == RIGHT) {
		for (int i = 0; i < block_num; ++i) {
			block_arr[i].x++;
		}
		if (block_arr[block_num - 1].x + block_x_aside >= 880) block_arr[0].dir1 = LEFT;
	}
}