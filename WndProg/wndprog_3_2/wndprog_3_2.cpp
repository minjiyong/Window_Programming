// [실습 3-2] 벽돌깨기 게임 만들기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

#define board_x_max 10
#define board_y_max 3
#define block_x_aside 60
#define block_y_aside 20
#define ball_aside 20

#define block_num 30
#define player_shape -1

#define RIGHT 1
#define LEFT 2

#define DOWN 1
#define UP 2

#define DELETED_X -300
#define DELETED_Y 2000

class Ball {
public:
	int x{400};
	int y{50};
	int speed{0};
	int dir1{ RIGHT };
	int dir2{ DOWN };

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
};


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";

Block block_arr[block_num]{};
Ball ball{};

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

	static bool print_deleted{ false };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();

		SetTimer(hWnd, 1, 10, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1번 아이디 타이머: 0.01초 간격으로 실행
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

		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

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
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

		draw_circle(mDC, ball.x, ball.y, ball.x + ball_aside, ball.y + ball_aside, RGB(0, 255, 0));

		for (int i = 0; i < block_num; ++i) {
			if (block_arr[i].hp <= 0) continue;
			draw_rectangle(mDC, block_arr[i].x, block_arr[i].y, block_arr[i].x + block_x_aside, block_arr[i].y + block_y_aside, RGB(255, 255, 0));
		}

		if (print_deleted) print_deleted_block(mDC);

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
	int x_index{ 0 };
	int y_index{ 0 };
	for (int j = 0; j < board_y_max; ++j) {
		for (int i = 0; i < board_x_max; ++i) {
			block_arr[x_index].x = 130 + i * block_x_aside;
			block_arr[y_index].y = 700 + j * block_y_aside;
			x_index++;
			y_index++;
		}
	}
	for (int i = 0; i < block_num; ++i) block_arr[i].block_initialize();
	ball.ball_initialize();
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
}

void draw_circle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Ellipse(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
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
	wsprintf(temp, TEXT("없어진 벽돌: %d개"), deleted_block);
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