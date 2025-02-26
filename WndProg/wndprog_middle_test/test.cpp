// [윈플 중간고사 연습]
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define board_x_max 40
#define board_y_max 40
#define board_aside 20

#define bullet_aside 3

#define block_num 100
#define enemy_num 20
#define bullet_num 30

#define PLAYER 1
#define ENEMY 2
#define WALL 3
#define DELETED_OBJ -100

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4


class Block {
public:
	int x{-50};
	int y{-50};
	int type{};
	int dir{};
	int hp{ 1 };
	COLORREF color{};

	Block() {};
	~Block() {};

	void enemy_initialize() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);

		type = ENEMY;
		dir = rand() % 4 + 1;
	}

	void wall_initialize() {
		type = WALL;
	}

	void color_set() {
		if (type == ENEMY) color = RGB(255, 0, 0);
		else if (type == WALL) color = RGB(0, 0, 255);
	}

	void make_deleted() {
		x = DELETED_OBJ;
		y = DELETED_OBJ;
	}
};

class Bullet {
public:
	int x{};
	int y{};
	int dir{};
	int hp{1};

	Bullet() {};
	~Bullet() {};
};


void Initialize();

void draw_block(HDC mDC);
void draw_bullet(HDC mDC);
void draw_board(HDC mDC);
void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color);

void player_win(HDC mDC);
void player_lose(HDC mDC);

Block block_arr[block_num]{};
Bullet bullet_arr[bullet_num]{};


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program test";

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

	static int bullet_index{ 0 };
	static int wall_index{ enemy_num };

	static bool check{ false };

	static bool win_check{ false };
	static bool lose_check{ false };

	switch (iMessage) {

	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();
		SetTimer(hWnd, 1, 1, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1:
			for (int i = 0; i < bullet_num; ++i) {
				if (bullet_arr[i].dir == UP) bullet_arr[i].y -= 3;
				else if (bullet_arr[i].dir == LEFT) bullet_arr[i].x -= 3;
				else if (bullet_arr[i].dir == DOWN) bullet_arr[i].y += 3;
				else if (bullet_arr[i].dir == RIGHT) bullet_arr[i].x += 3;
				
				for (int j = 1; j < block_num; ++j) {
					if (bullet_arr[i].hp < 1)continue;
					if (bullet_arr[i].x > block_arr[j].x - bullet_aside && bullet_arr[i].x < block_arr[j].x + board_aside + bullet_aside
						&& bullet_arr[i].y > block_arr[j].y - bullet_aside && bullet_arr[i].y < block_arr[j].y + board_aside + bullet_aside) {
						bullet_arr[i].hp--;
						block_arr[j].hp--;

						if (block_arr[j].hp < 1) {
							block_arr[j].x = DELETED_OBJ;
							block_arr[j].y = DELETED_OBJ;
						}
					}
				}
			}

			for (int i = 1; i < block_num; ++i) {
				if (block_arr[i].type == ENEMY) {
					switch (block_arr[i].dir) {
					case UP:
						block_arr[i].y--;
						if (block_arr[i].y <= 0) block_arr[i].dir = DOWN;
						break;
					case LEFT:
						block_arr[i].x--;
						if (block_arr[i].x <= 0) block_arr[i].dir = RIGHT;
						break;
					case DOWN:
						block_arr[i].y++;
						if (block_arr[i].y >= board_aside * (board_y_max - 1)) block_arr[i].dir = UP;
						break;
					case RIGHT:
						block_arr[i].x++;
						if (block_arr[i].x >= board_aside * (board_x_max - 1)) block_arr[i].dir = LEFT;
						break;
					}

					if (block_arr[0].x < block_arr[i].x + board_aside && block_arr[0].y < block_arr[i].y + board_aside
						&& block_arr[0].x + board_aside > block_arr[i].x && block_arr[0].y + board_aside > block_arr[i].y) {
						KillTimer(hWnd, 1);
						lose_check = true;
					}
				}
			}

			int enemy_check{ 1 };
			for (int i = 0; i < block_num; ++i) {
				if (block_arr[i].type == ENEMY) {
					if (block_arr[i].hp < 1) enemy_check++;
				}
			}
			if (enemy_check == enemy_num) {
				KillTimer(hWnd, 1);
				win_check = true;
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
		block_arr[wall_index].color_set();
		wall_index++;
		if (wall_index == block_num) wall_index = enemy_num;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		check = false;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		if (check) {
			int temp_x{};
			int temp_y{};
			temp_x = LOWORD(lParam) - LOWORD(lParam) % board_aside;
			temp_y = HIWORD(lParam) - HIWORD(lParam) % board_aside;

			if (block_arr[wall_index - 1].x == temp_x && block_arr[wall_index - 1].y == temp_y) {
				block_arr[wall_index].make_deleted();
			}
			else {
				block_arr[wall_index].x = temp_x;
				block_arr[wall_index].y = temp_y;
				block_arr[wall_index].wall_initialize();
				block_arr[wall_index].color_set();
				wall_index++;
				if (wall_index == block_num) wall_index = enemy_num;
			}

			InvalidateRect(hWnd, NULL, FALSE);
		}

		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q') {
			PostQuitMessage(0);
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

		else if (wParam == 'e') {
			bullet_arr[bullet_index].hp = 1;
			bullet_arr[bullet_index].x = block_arr[0].x + 10;
			bullet_arr[bullet_index].y = block_arr[0].y + 10;
			bullet_arr[bullet_index].dir = block_arr[0].dir;
			bullet_index++;
			if (bullet_index == bullet_num) bullet_index = 0;
		}

		for (int i = 1; i < block_num; ++i) {
			if (block_arr[i].type == WALL) {
				if (block_arr[0].x == block_arr[i].x && block_arr[0].y == block_arr[i].y) {
					switch (block_arr[0].dir) {
					case UP:
						block_arr[0].y += board_aside;
						break;
					case LEFT:
						block_arr[0].x += board_aside;
						break;
					case DOWN:
						block_arr[0].y -= board_aside;
						break;
					case RIGHT:
						block_arr[0].x -= board_aside;
						break;
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
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
		SelectObject(mDC, (HBITMAP)hBitmap);
		Rectangle(mDC, 0, 0, rt.right, rt.bottom);


		draw_board(mDC);
		draw_block(mDC);
		draw_bullet(mDC);

		if (win_check) player_win(mDC);
		if (lose_check) player_lose(mDC);

		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC);
		DeleteObject(hBitmap);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


void Initialize() {
	block_arr[0].x = 0;
	block_arr[0].y = 0;
	block_arr[0].type = PLAYER;
	block_arr[0].color = RGB(0, 255, 0);

	for (int i = 1; i < enemy_num; ++i) {
		block_arr[i].enemy_initialize();
		block_arr[i].color_set();
	}
	
	for (int i = enemy_num; i < block_num; ++i) {
		block_arr[i].wall_initialize();
		block_arr[i].color_set();
	}
}

void draw_block(HDC mDC) {
	
	for (int i = 0; i < block_num; ++i) {
		//if (block_arr[i].type == PLAYER) {
		draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, board_aside, block_arr[i].color);
		//}
	}

}

void draw_bullet(HDC mDC) {
	for (int i = 0; i < bullet_num; ++i) {
		if (bullet_arr[i].hp < 1) continue;
		draw_circle(mDC, bullet_arr[i].x, bullet_arr[i].y, bullet_aside, RGB(0, 255, 0));
	}
}

void draw_board(HDC mDC) {
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	for (int j = 0; j < board_y_max; ++j) {
		for (int i = 0; i < board_x_max; ++i) {
			Rectangle(mDC, i * board_aside, j * board_aside, board_aside + i * board_aside, board_aside + j * board_aside);
		}
	}
}

// 좌측 상단 기준
void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Rectangle(mDC, x1, y1, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}

// 원점 기준
void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

	Ellipse(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush);
	DeleteObject(hBrush);
}

void player_win(HDC mDC) {
	TCHAR temp[80] = TEXT("Player Win");
	TextOut(mDC, 400, 400, temp, lstrlen(temp));
}

void player_lose(HDC mDC) {
	TCHAR temp[80] = TEXT("Player Losed");
	TextOut(mDC, 400, 400, temp, lstrlen(temp));
}