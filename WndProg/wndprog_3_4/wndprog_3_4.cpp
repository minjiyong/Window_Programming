// [실습 3-4] 윷놀이 만들기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1100

#define block_big_aside 30
#define block_small_aside 20

#define block_num 29

#define DIR_Z 1
#define DIR_C 2

#define FRONT_YOOT 0
#define BACK_YOOT 1

#define DO 1
#define GAE 2
#define GUL 3
#define YOOT 4
#define MO 5

#define WIN 3


class Player {
public:
	int x{};
	int y{};
	COLORREF color{};
	int dir{};
	bool turn{ false };

	int move{};
	bool stopped{ false };

	Player() {};
	Player(int b_x, int b_y, COLORREF color) :x(b_x), y(b_y), color(color) {};
	~Player() {};

	void player_initialize() {
		x = 950;
		y = 950;
		stopped = false;
		turn = false;
	};
};

class Block {
public:
	int x{};
	int y{};
	bool corner{ false };

	Block() {};
	Block(int b_x, int b_y) :x(b_x), y(b_y) {};
	Block(int b_x, int b_y, bool b_corner) :x(b_x), y(b_y), corner(b_corner) {};
	~Block() {};

	void block_initialize() {
	
	};
}; 


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";

// 보드판 배열
Block block_arr[block_num]{
	{50, 50, true}, {230, 50}, {410, 50}, {590, 50}, {770, 50},		// 위
	{950, 50, true}, {950, 230}, {950, 410}, {950, 590}, {950, 770},		// 오른쪽
	{950, 950, true}, {770, 950}, {590, 950}, {410, 950}, {230, 950},		// 아래
	{50, 950, true}, {50, 770}, {50, 590}, {50, 410}, {50, 230},		// 왼쪽
	{200, 200}, {350, 350},			// 좌상단
	{800, 200}, {650, 350},			// 우상단
	{350, 650}, {200, 800},			// 좌하단
	{650, 650}, {800, 800},			// 우하단
	{500, 500, true}				// 중앙
};

Player p1{ 1200 , 400, RGB(255, 0, 0) };
Player p2{ 1300 , 400, RGB(0, 0, 255)};

int win_check{ 0 };


void Initialize();

int roll_yoot();
void check_yoot(int& yoot);
void draw_yoot(HDC mDC, const int yoot);

void check_p(Player& p);
void p_win_check(Player p);

void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_board_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color);
void draw_player(HDC mDC);
void draw_board(HDC mDC);

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

	
	static int yoot{};

	static bool player1_start{ false };
	static bool player2_start{ false };

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();

		SetTimer(hWnd, 1, 500, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1번 아이디 타이머: 0.5초 간격으로 실행
			if(p1.move != 0){
				check_p(p1);
				p1.stopped = false;
				--p1.move;
			}
			else if (p1.move == 0) {
				p1.stopped = true;
			}
			if (p2.move != 0) {
				check_p(p2);
				p2.stopped = false;
				--p2.move;
			}
			else if (p2.move == 0) {
				p2.stopped = true;
			}

			//// 끝났는지 체크
			//if(p1.turn == true) p_win_check(p1);
			//else if (p2.turn == true) p_win_check(p2);
			//if (win_check == WIN) KillTimer(hWnd, 1);

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
			player1_start = false;
			player2_start = false;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (player1_start == false) p1.player_initialize();
			player1_start = true;
			p1.turn = true;
		}
		else if (wParam == '1') {
			if (p1.turn == true) {
				if (player2_start == false) p2.player_initialize();
				player2_start = true;
				check_yoot(yoot);
				p1.move = yoot;
				if (yoot == YOOT || yoot == MO) {
					break;
				}
				else {
					p1.turn = false;
					p2.turn = true;
				}

			}
		}
		else if (wParam == '2') {
			if (p2.turn == true) {
				check_yoot(yoot);
				p2.move = yoot;
				if (yoot == YOOT || yoot == MO) {
					break;
				}
				else {
					p2.turn = false;
					p1.turn = true;
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
		draw_player(mDC);

		draw_yoot(mDC, yoot);


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
	p1.x = 1200;
	p1.y = 400;
	p2.x = 1300;
	p2.y = 400;
}

void check_yoot(int& yoot) {
	int four_yoot[4]{};
	int back_cnt{};
	for (int i = 0; i < 4; ++i) {
		four_yoot[i] = roll_yoot();
		if (four_yoot[i] == BACK_YOOT) back_cnt++;
	}
	switch (back_cnt) {
	case 0: {
		yoot = MO;
		break;
	}
	case 1: {
		yoot = DO;
		break;
	}
	case 2: {
		yoot = GAE;
		break;
	}
	case 3: {
		yoot = GUL;
		break;
	}
	case 4: {
		yoot = YOOT;
		break;
	}
	}
}
int roll_yoot() {
	switch (rand() % 2 + 1) {
	case FRONT_YOOT: {
		return FRONT_YOOT;
	}
	case BACK_YOOT:
		return BACK_YOOT;
	}
}
void draw_yoot(HDC mDC, const int yoot) {
	TCHAR temp[80] = TEXT("윷을 굴립니다 : ");
	TextOut(mDC, 1150, 150, temp, lstrlen(temp));
	switch (yoot) {
	case DO: {
		TCHAR temp[80] = TEXT("도!!!");
		TextOut(mDC, 1300, 150, temp, lstrlen(temp));
		break;
	}
	case GAE: {
		TCHAR temp[80] = TEXT("개!!!");
		TextOut(mDC, 1300, 150, temp, lstrlen(temp));
 		break;
	}
	case GUL: {
		TCHAR temp[80] = TEXT("걸!!!");
		TextOut(mDC, 1300, 150, temp, lstrlen(temp));
		break;
	}
	case YOOT: {
		TCHAR temp[80] = TEXT("윷!!!");
		TextOut(mDC, 1300, 150, temp, lstrlen(temp));		
		break;
	}
	case MO: {
		TCHAR temp[80] = TEXT("모!!!");
		TextOut(mDC, 1300, 150, temp, lstrlen(temp));
		break;
	}
	}
}

void check_p(Player& p) {
	if (p.x == 950 && p.y == 50) {
		if (p.stopped == true) {
			p.x -= 150;
			p.y += 150;
		}
		else if (p.stopped == false) {
			p.x -= 180;
		}
	}
	else if (p.x == 50 && p.y == 50) {
		if (p.stopped == true) {
			p.x += 150;
			p.y += 150;
		}
		else if (p.stopped == false) {
			p.y += 180;
		}
	}
	else if (p.x == 500 && p.y == 500) {
		if (p.stopped == true) {
			p.x += 150;
			p.y += 150;
		}
		else if (p.stopped == false) {
			if (p.dir == DIR_Z) {
				p.x -= 150;
				p.y += 150;
			}
			else if(p.dir == DIR_C) {
				p.x += 150;
				p.y += 150;
			}
		}
	}

	else if (p.x - p.y == 300 || p.x - p.y == 600 || p.x - p.y == -300 || p.x - p.y == -600) {
		p.dir = DIR_Z;
		p.x -= 150;
		p.y += 150;
	}
	else if (p.x == 200 && p.y == 200) {
		p.dir = DIR_C;
		p.x += 150;
		p.y += 150;
	}
	else if (p.x == 350 && p.y == 350) {
		p.dir = DIR_C;
		p.x += 150;
		p.y += 150;
	}
	else if (p.x == 650 && p.y == 650) {
		p.dir = DIR_C;
		p.x += 150;
		p.y += 150;
	}
	else if (p.x == 800 && p.y == 800) {
		p.dir = DIR_C;
		p.x += 150;
		p.y += 150;
	}

	else if (p.x == 950 && p.y != 50)p.y -= 180;
	else if (p.y == 50 && p.x != 50)p.x -= 180;
	else if (p.x == 50 && p.y != 950)p.y += 180;
	else if (p.y == 950 && p.x != 950)p.x += 180;
}
void p_win_check(Player p) {
	if (p.x == 950 && p.y == 950) ++win_check;
}

void draw_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Rectangle(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
}
void draw_board_rectangle(HDC mDC, int x1, int y1, int aside, COLORREF color)
{
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Rectangle(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}
void draw_player(HDC mDC) {
	draw_rectangle(mDC, p1.x, p1.y, block_small_aside, p1.color);
	draw_rectangle(mDC, p2.x, p2.y, block_small_aside, p2.color);
}
void draw_board(HDC mDC) {
	for (int i = 0; i < block_num; ++i) {
		if (block_arr[i].corner == true) {
			draw_board_rectangle(mDC, block_arr[i].x, block_arr[i].y, block_big_aside, RGB(0, 0, 0));
		}
		else if (block_arr[i].corner == false) {
			draw_board_rectangle(mDC, block_arr[i].x, block_arr[i].y, block_small_aside, RGB(0, 0, 0));
		}
	}
}

