#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include <time.h>

#define marginX 16
#define marginY 200

#define board_x_max 20
#define board_y_max 20
#define board_aside 40


#define enemy_num 50
#define item_num 70
#define block_num 200

#define bullet_aside 5
#define bullet_num 20

#define item_aside 10

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define PLAYER 1
#define ENEMY 2
#define WALL 3
#define ITEM 4

#define rec 1
#define cir 2

#define DELETED_OBJ -200

class Block
{
public:
	int x{};
	int y{};
	int type{};
	int player_shape{ rec };
	int dir{};
	int hp{ 1 };
	COLORREF color{};

	Block() {};
	~Block() {};

	void item_initialize() {
		x = 20 + board_aside * (rand() % board_x_max);
		y = 20 + board_aside * (rand() % board_y_max);
		type = ITEM;
		color = RGB(rand() % 255, rand() % 255, rand() % 255);
	};

	void enemy_initialize() {
		x = -5000;
		y = -5000;
		type = ENEMY;
		color = RGB(0, 0, 255);
		dir = rand() % 4 + 1;
	};

	void wall_initialize() {
		type = WALL;
		color = RGB(100, 100, 100);
	}
};

class Bullet
{
public:
	int x{};
	int y{};
	int dir{};
	int hp{ 1 };

	Bullet() {
		x = -50;
		y = -50;
	};
	~Bullet() {};
};


Block block_arr[block_num]{};
Bullet bullet_arr[bullet_num]{};

void Initialize();

void draw_board(HDC mDC);
void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_rectangle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_circle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color);


HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"2024 Window Programming Exam";

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	//--- 크기 변경 가능 (기존 (1024, 768))
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1024 + marginX, 768 + marginY, NULL, (HMENU)NULL, hInstance, NULL);
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
	HDC	hDC, mDC;
	HBITMAP hBitmap;
	RECT rect{ 0, 0, 1024 + marginX, 768 + marginY };

	static int bullet_index{ 0 };
	static int enemy_index{ 1 };
	static int wall_index{ item_num };

	static bool check{ false };

	static bool pause{ true };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();
		SetTimer(hWnd, 1, 1000, NULL);
		SetTimer(hWnd, 2, 1, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1:
			for (int i = 1; i < enemy_num; ++i) {
				if (block_arr[i].type == ENEMY) {
					switch (block_arr[i].dir) {
					case UP:
						block_arr[i].y -= board_aside;
						if (block_arr[i].y < 0) block_arr[i].dir = DOWN;
						break;
					case LEFT:
						block_arr[i].x -= board_aside;
						if (block_arr[i].x < 0) block_arr[i].dir = RIGHT;
						break;
					case DOWN:
						block_arr[i].y += board_aside;
						if (block_arr[i].y > board_aside * (board_y_max - 2)) block_arr[i].dir = UP;
						break;
					case RIGHT:
						block_arr[i].x += board_aside;
						if (block_arr[i].x > board_aside * (board_x_max - 2)) block_arr[i].dir = LEFT;
						break;
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < bullet_num; ++i) {
				if (bullet_arr[i].dir == UP) bullet_arr[i].y -= 3;
				else if (bullet_arr[i].dir == LEFT) bullet_arr[i].x -= 3;
				else if (bullet_arr[i].dir == DOWN) bullet_arr[i].y += 3;
				else if (bullet_arr[i].dir == RIGHT) bullet_arr[i].x += 3;

				for (int j = 1; j < block_num; ++j) {
					if (bullet_arr[i].hp < 1) continue;
					if (bullet_arr[i].x > block_arr[j].x - bullet_aside && bullet_arr[i].x < block_arr[j].x + board_aside + bullet_aside
						&& bullet_arr[i].y > block_arr[j].y - bullet_aside && bullet_arr[i].y < block_arr[j].y + board_aside + bullet_aside) {
						block_arr[j].hp--;
						bullet_arr[i].hp--;

						if (block_arr[j].hp < 1) {
							block_arr[j].x = DELETED_OBJ;
							block_arr[j].y = DELETED_OBJ;
						}
					}
				}
			}

			for (int i = 1; i < block_num; ++i) {
				//적 충돌체크
				if (block_arr[i].type == ENEMY) {
					if (block_arr[0].x < block_arr[i].x + board_aside && block_arr[0].y < block_arr[i].y + board_aside
						&& block_arr[0].x + board_aside >  block_arr[i].x && block_arr[0].y + board_aside >  block_arr[i].y) {
						block_arr[0].hp = 0;
						KillTimer(hWnd, 1);
						KillTimer(hWnd, 2);
					}
				}
				// 아이템 충돌체크
				else if (block_arr[i].type == ITEM) {
					if (block_arr[0].x < block_arr[i].x + item_aside && block_arr[0].y < block_arr[i].y + item_aside
						&& block_arr[0].x + board_aside >  block_arr[i].x - item_aside && block_arr[0].y + board_aside >  block_arr[i].y - item_aside) {
						block_arr[0].color = block_arr[i].color;
						block_arr[0].player_shape = cir;
					}
				}
			}
			break;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:
		check = true;
		block_arr[wall_index].x = LOWORD(lParam) - LOWORD(lParam) % board_aside;
		block_arr[wall_index].y = HIWORD(lParam) - HIWORD(lParam) % board_aside;
		block_arr[wall_index].wall_initialize();
		wall_index++;
		if (wall_index == block_num) wall_index = item_num;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		check = false;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		if (check) {
			block_arr[wall_index].x = LOWORD(lParam) - LOWORD(lParam) % board_aside;
			block_arr[wall_index].y = HIWORD(lParam) - HIWORD(lParam) % board_aside;
			block_arr[wall_index].wall_initialize();
			wall_index++;
			if (wall_index == block_num) wall_index = item_num;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		else if (wParam == 't') {
			if (pause) {
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				pause = false;
			}
			else {
				SetTimer(hWnd, 1, 1000, NULL);
				SetTimer(hWnd, 2, 1, NULL);
				pause = true;
			}
		}

		else if (wParam == 'w') {
			if (block_arr[0].y == 0) block_arr[0].y = board_aside * (board_y_max - 1);
			else block_arr[0].y -= board_aside;
			block_arr[0].dir = UP;
		}
		else if (wParam == 'a') {
			if (block_arr[0].x == 0) block_arr[0].x = board_aside * (board_x_max - 1);
			else block_arr[0].x -= board_aside;
			block_arr[0].dir = LEFT;
		}
		else if (wParam == 's') {
			if (block_arr[0].y == board_aside * (board_y_max - 1)) block_arr[0].y = 0;
			else block_arr[0].y += board_aside;
			block_arr[0].dir = DOWN;
		}
		else if (wParam == 'd') {
			if (block_arr[0].x == board_aside * (board_x_max - 1)) block_arr[0].x = 0;
			else block_arr[0].x += board_aside;
			block_arr[0].dir = RIGHT;
		}

		else if (wParam == VK_SPACE) {
			bullet_arr[bullet_index].hp = 1;
			bullet_arr[bullet_index].x = block_arr[0].x + 20;
			bullet_arr[bullet_index].y = block_arr[0].y + 20;
			bullet_arr[bullet_index].dir = block_arr[0].dir;
			bullet_index++;
			if (bullet_index == bullet_num) bullet_index = 0;
		}

		for (int i = 0; i < block_num; ++i) {
			if (block_arr[i].type == WALL) {
				if (block_arr[0].x == block_arr[i].x && block_arr[0].y == block_arr[i].y) {
					if (block_arr[0].player_shape = cir) {
						block_arr[i].hp = 0;

						block_arr[0].player_shape = rec;
						block_arr[0].color = RGB(0, 255, 0);

						block_arr[enemy_index].x = board_aside * (rand() % board_x_max);
						block_arr[enemy_index].y = board_aside * (rand() % board_x_max);
						enemy_index++;
						if (enemy_index == enemy_num) enemy_index = 1;
					}

					else if (block_arr[0].player_shape = rec) {
						if (block_arr[0].dir == UP) block_arr[0].y += board_aside;
						else if (block_arr[0].dir == LEFT) block_arr[0].x += board_aside;
						else if (block_arr[0].dir == DOWN) block_arr[0].y -= board_aside;
						else if (block_arr[0].dir == RIGHT) block_arr[0].x -= board_aside;
					}
				}
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		SelectObject(mDC, (HBITMAP)hBitmap);
		Rectangle(mDC, 0, 0, rect.right, rect.bottom);


		draw_board(mDC);

		if (block_arr[0].player_shape == rec) {
			draw_rectangle(mDC, block_arr[0].x, block_arr[0].y, board_aside, block_arr[0].color);
		}
		else if (block_arr[0].player_shape == cir) {
			draw_circle(mDC, block_arr[0].x, block_arr[0].y, board_aside, block_arr[0].color);
		}

		for (int i = 1; i < enemy_num; ++i) {
			if (block_arr[i].hp < 1) continue;
			draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, board_aside, block_arr[i].color);
		}
		for (int i = enemy_num; i < item_num; ++i) {
			if (block_arr[i].hp < 1) continue;
			draw_rectangle_bymid(mDC, block_arr[i].x, block_arr[i].y, item_aside, block_arr[i].color);
		}
		for (int i = item_num; i < block_num; ++i) {
			if (block_arr[i].hp < 1) continue;
			draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, board_aside, block_arr[i].color);
		}

		for (int i = 0; i < bullet_num; ++i) {
			if (bullet_arr[i].hp < 1) continue;
			draw_circle_bymid(mDC, bullet_arr[i].x, bullet_arr[i].y, bullet_aside, RGB(0, 255, 0));
		}


		BitBlt(hDC, 0, 0, rect.right, rect.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC);
		DeleteObject(hBitmap);

		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


void Initialize() {
	block_arr[0].x = 0;
	block_arr[0].y = 0;
	block_arr[0].type = PLAYER;
	block_arr[0].player_shape = rec;
	block_arr[0].color = RGB(0, 255, 0);

	for (int i = 1; i < enemy_num; ++i) {
		block_arr[i].enemy_initialize();
	}
	for (int i = enemy_num; i < item_num; ++i) {
		block_arr[i].item_initialize();
	}
	for (int i = item_num; i < block_num; ++i) {
		block_arr[i].x = DELETED_OBJ;
		block_arr[i].y = DELETED_OBJ;
		block_arr[i].wall_initialize();
	}
}


void draw_board(HDC mDC) {
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	for (int j = 0; j < board_y_max; ++j) {
		for (int i = 0; i < board_x_max; ++i) {
			Rectangle(mDC, i * board_aside, j * board_aside, board_aside + i * board_aside, board_aside + j * board_aside);
		}
	}
}

void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Rectangle(mDC, x1, y1, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}

void draw_rectangle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Rectangle(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}

void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Ellipse(mDC, x1, y1, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}

void draw_circle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Ellipse(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}
