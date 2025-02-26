// [윈플 중간고사 연습]
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define board_x_max 40
#define board_y_max 40
#define board_aside 20

#define block_aside 20

#define block_num 400
#define bullet_num 20

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define PLAYER 1
#define ENEMY 2
#define WALL 3

#define DELETED_BLOCK -1000


class Block {
public:
	int x{};
	int y{};
	int type{};
	int dir{};
	int hp{ 1 };
	COLORREF color{};

	Block() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
	};
	~Block() {};

	void initialize() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);

		type = ENEMY;
		//type = rand() % 2 + 2;
		if (type == ENEMY) color = RGB(255, 0, 0);
		else if (type == WALL) color = RGB(0, 0, 255);

		dir = rand() % 4 + 1;
	}

	void make_deleted() {
		x = -50;
		y = -50;
	}

	void color_set(){
		if (type == ENEMY) color = RGB(255, 0, 0);
		else if (type == WALL) color = RGB(0, 0, 255);
	}
};

class Bullet {
public:
	int x{ -100 };
	int y{-100 };
	int dir{0};
	int hp{ 1 };

	Bullet() {};
	~Bullet() {}
};

void Initialize();

void draw_block(HDC mDC);
void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_board(HDC mDC);


Block block_arr[block_num]{};
Bullet bullet_arr[bullet_num]{};


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
	static int wall_index{ 10 };

	static bool select{ false };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();
		SetTimer(hWnd, 1, 1, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1번 아이디 타이머: 0.005초 간격으로 실행
			for (int i = 0; i < bullet_num; ++i) {
				if (bullet_arr[i].dir == UP) bullet_arr[i].y-=3;
				else if (bullet_arr[i].dir == LEFT) bullet_arr[i].x-=3;
				else if (bullet_arr[i].dir == DOWN) bullet_arr[i].y+=3;
				else if (bullet_arr[i].dir == RIGHT) bullet_arr[i].x+=3;
			
				for (int j = 1; j < block_num; ++j) {
					if (bullet_arr[i].hp < 1)continue;
					if (bullet_arr[i].x > block_arr[j].x - 5 && bullet_arr[i].x < block_arr[j].x + block_aside + 5
						&& bullet_arr[i].y > block_arr[j].y - 5 && bullet_arr[i].y < block_arr[j].y + block_aside + 5) {
						block_arr[j].hp--;
						bullet_arr[i].hp--;

						if (block_arr[j].hp < 1) block_arr[j].x = DELETED_BLOCK;
					}
				}
			}

			for (int i = 1; i < block_num; ++i) {
				if (block_arr[i].type == ENEMY) {
					switch (block_arr[i].dir) {
					case UP:
						block_arr[i].y--;
						if (block_arr[i].y < 0) block_arr[i].dir = DOWN;
						break;
					case LEFT:
						block_arr[i].x--;
						if (block_arr[i].x < 0) block_arr[i].dir = RIGHT;
						break;
					case DOWN:
						block_arr[i].y++;
						if (block_arr[i].y > 780) block_arr[i].dir = UP;
						break;
					case RIGHT:
						block_arr[i].x++;
						if (block_arr[i].x > 780) block_arr[i].dir = LEFT;
						break;
					}
				}
			}
			

			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:
		block_arr[wall_index].x = LOWORD(lParam) - (LOWORD(lParam) % board_aside);
		block_arr[wall_index].y = HIWORD(lParam) - (HIWORD(lParam) % board_aside);
		block_arr[wall_index].type = WALL;
		block_arr[wall_index].color_set();
		wall_index++;
		if (wall_index == block_num) wall_index = 10;

		select = true;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		select = false;

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		if(select)
		{
			int temp_x, temp_y;
			temp_x = LOWORD(lParam) - (LOWORD(lParam) % board_aside);
			temp_y = HIWORD(lParam) - (HIWORD(lParam) % board_aside);

			if (block_arr[wall_index - 1].x == temp_x && block_arr[wall_index - 1].y == temp_y) {
					block_arr[wall_index].make_deleted();
			}
			else{
				block_arr[wall_index].x = temp_x;
				block_arr[wall_index].y = temp_y;
				block_arr[wall_index].type = WALL;
				block_arr[wall_index].color_set();
				wall_index++;
			}

			
			if (wall_index == block_num) wall_index = 10;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'n' || wParam == 'N') {
		}

		else if (wParam == 'w') {
			if (block_arr[0].y == 0) block_arr[0].y = board_aside * (board_y_max - 1);
			else block_arr[0].y -= block_aside;
			block_arr[0].dir = UP;
		}
		else if (wParam == 'a') {
			if (block_arr[0].x == 0) block_arr[0].x = board_aside * (board_y_max - 1);
			else block_arr[0].x -= board_aside;
			block_arr[0].dir = LEFT;
		}
		else if (wParam == 's') {
			if (block_arr[0].y == board_aside * (board_y_max - 1)) block_arr[0].y = 0;
			else block_arr[0].y += board_aside;
			block_arr[0].dir = DOWN;
		}
		else if (wParam == 'd') {
			if (block_arr[0].x == board_aside * (board_y_max - 1)) block_arr[0].x = 0;
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
			if (block_arr[0].x == block_arr[i].x && block_arr[0].y == block_arr[i].y) {
				if (block_arr[i].type == WALL) {
					if (block_arr[0].dir == UP) block_arr[0].y += block_aside;
					if (block_arr[0].dir == LEFT) block_arr[0].x += block_aside;
					if (block_arr[0].dir == DOWN) block_arr[0].y -= block_aside;
					if (block_arr[0].dir == RIGHT) block_arr[0].x -= block_aside;
				}
				if (block_arr[i].type == ENEMY) {
					block_arr[0].hp--;
				}
			}
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

		draw_board(mDC);
		draw_block(mDC);
		
		for (int i = 0; i < bullet_num; ++i) {
			if (bullet_arr[i].hp <= 0) continue;
			draw_circle(mDC, bullet_arr[i].x, bullet_arr[i].y, 5, RGB(0, 255, 0));
		}



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


void Initialize() {
	block_arr[0].x = 0;
	block_arr[0].y = 0;
	block_arr[0].color = RGB(0, 255, 0);

	for (int i = 1; i < 10; ++i) {
		block_arr[i].initialize();
	}

	for (int i = 10; i < block_num; ++i) {
		block_arr[i].make_deleted();
	}
}

void draw_block(HDC mDC) {
	for (int i = 0; i < block_num; ++i) {
		if (block_arr[i].hp <= 0) continue;
		draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, block_aside, block_arr[i].color);
	}
}

void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Rectangle(mDC, x1, y1, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
}

void draw_circle(HDC mDC, int x1, int y1, int aside, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Ellipse(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
}

void draw_board(HDC mDC) {
	// 20 X 20 판 그리기
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