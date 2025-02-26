// [실습 2-14] 알파벳이나 숫자 변경하기
#include <vector>
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define board_x_max 20
#define board_y_max 20
#define board_aside 20

#define block_num 20
#define player_shape -1

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define DELETED_Shape -100

class Block {
public:
	int x{};
	int y{};
	int shape{ 0 };
	int dir{ 0 };

	Block() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
		shape = (rand() % 26 + 1) % 26;
	};
	~Block() {};

	void print_c_Block(HDC mDC) {
		TCHAR temp[80]{};
		wsprintf(temp, TEXT("%c"), shape + 65);
		TextOut(mDC, x + 2, y + 2, temp, lstrlen(temp));
	};
	void print_i_Block(HDC mDC) {
		TCHAR temp[80]{};
		wsprintf(temp, TEXT("%d"), shape);
		TextOut(mDC, x + 2, y + 2, temp, lstrlen(temp));
	};

	void block_initialize() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
		shape = (rand() % 26 + 1) % 26;
	};
};


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";


void Initialize();
void check_block();

void draw_pie(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_board(HDC mDC);

Block block_arr[block_num]{};


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
	RECT rt{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	HBITMAP hBitmap;
	HDC hDC, mDC;


	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		Initialize();
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'p') {
			Initialize();
		}

		else if (wParam == 'w') {
			if (block_arr[0].y == 0) block_arr[0].y = board_aside * (board_y_max - 1) ;
			else block_arr[0].y -= board_aside;
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

		for (int i = 1; i < block_num; ++i) {
			if (block_arr[0].x == block_arr[i].x && block_arr[0].y == block_arr[i].y) {
				// 플레이어의 위치와 블록의 위치가 같다면
				switch (block_arr[0].dir) {
				case UP:
					block_arr[i].y -= board_aside;
					break;
				case LEFT:
					block_arr[i].x -= board_aside;
					break;
				case DOWN:
					block_arr[i].y += board_aside;
					break;
				case RIGHT:
					block_arr[i].x += board_aside;
					break;
				}
			}
		}

		check_block();

		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

		draw_board(mDC);

		// 플레이어와 블럭들 그리기
		for (int i = 0; i < block_num; ++i) {
			if (i == 0) {
				draw_pie(mDC, block_arr[0].x, block_arr[0].y, block_arr[0].x + board_aside, block_arr[0].y + board_aside, RGB(0, 0, 0));
			}
			else if (block_arr[i].shape == DELETED_Shape) {
				continue;
			}
			else if(i % 2 == 0)block_arr[i].print_i_Block(mDC);
			else block_arr[i].print_c_Block(mDC);
		}

		//--- 마지막에 메모리 DC의 내용을 화면 DC로 복사한다.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- 생성한 메모리 DC 삭제
		DeleteObject(hBitmap); //--- 생성한 비트맵 삭제
		
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



void Initialize()
{
	block_arr[0].shape = player_shape;
	block_arr[0].x = 0;
	block_arr[0].y = 0;

	for (int i = 1; i < block_num; ++i) {
		block_arr[i].block_initialize();
	}
}

// 플레이어를 제외한 블럭 두개가 겹칠 때
void check_block() {
	for (int j = 0; j < block_num; ++j) {
		int temp_x = block_arr[j].x;
		int temp_y = block_arr[j].y;
		for (int i = j + 1; i < block_num; ++i) {
			if (temp_x == block_arr[i].x && temp_y == block_arr[i].y) {
				block_arr[j].shape = (block_arr[j].shape + block_arr[i].shape) % 26;
				block_arr[i].shape = DELETED_Shape;
				block_arr[i].x = DELETED_Shape;
			}
		}
	}
}

void draw_pie(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기

	Pie(mDC, x1, y1, x2, y2, x1, y1, x2, y1);

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