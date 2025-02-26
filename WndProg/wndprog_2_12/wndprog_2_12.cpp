// [�ǽ� 2-12] Ű���� ��ɿ� ���� �׸� �׸��� ���α׷�
#include <windows.h>			// ������ ��� ����
#include <TCHAR.H>
#include <ctime>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

int board_x_max{ 40 };
int board_y_max{ 40 };
#define board_aside 20

#define block_num 10

#define shape_circle 1
#define shape_triangle 2
#define shape_rectangle 3

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define player_shape -1
#define DELETED_Shape -100

class Block {
public:
	int x{};
	int y{};
	int shape{ 0 };
	int dir{ 0 };
	int size{ 0 };
	bool select{ false };

	Block() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
	};
	~Block() {};

	void block_initialize() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
		shape = 0;
		size = 0;
	};

	void block_initialize_xy() {
		x = board_aside * (rand() % board_x_max);
		y = board_aside * (rand() % board_y_max);
	};
};


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"windows program";


void Initialize();
void check_block();

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_circle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_triangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_diamond(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_board(HDC mDC);
void win_game(HDC mDC);

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
	RECT rt{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	HBITMAP hBitmap;
	HDC hDC, mDC;

	static int arr_index{ -1 };

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
			arr_index = -1;
		}

		else if (wParam == 'b') {
			board_x_max = 20;
			board_y_max = 20;
		}
		else if (wParam == 'n') {
			board_x_max = 30;
			board_y_max = 30;
		}
		else if (wParam == 'm') {
			board_x_max = 40;
			board_y_max = 40;
		}

		else if (wParam == 'w') {
			if (block_arr[arr_index].y == 0) block_arr[arr_index].y = board_aside * (board_y_max - 1);
			else block_arr[arr_index].y -= board_aside;
			block_arr[arr_index].dir = UP;
		}
		else if (wParam == 'a') {
			if (block_arr[arr_index].x == 0) block_arr[arr_index].x = board_aside * (board_y_max - 1);
			else block_arr[arr_index].x -= board_aside;
			block_arr[arr_index].dir = LEFT;
		}
		else if (wParam == 's') {
			if (block_arr[arr_index].y == board_aside * (board_y_max - 1)) block_arr[arr_index].y = 0;
			else block_arr[arr_index].y += board_aside;
			block_arr[arr_index].dir = DOWN;
		}
		else if (wParam == 'd') {
			if (block_arr[arr_index].x == board_aside * (board_y_max - 1)) block_arr[arr_index].x = 0;
			else block_arr[arr_index].x += board_aside;
			block_arr[arr_index].dir = RIGHT;
		
		}

		else if (wParam == 'e') {
			arr_index = (arr_index + 1) % 10;
			block_arr[arr_index].shape = shape_circle;
			block_arr[arr_index].block_initialize_xy();
		}
		else if (wParam == 't') {
			arr_index = (arr_index + 1) % 10;
			block_arr[arr_index].shape = shape_triangle;
			block_arr[arr_index].block_initialize_xy();
		}
		else if (wParam == 'r') {
			arr_index = (arr_index + 1) % 10;
			block_arr[arr_index].shape = shape_rectangle;
			block_arr[arr_index].block_initialize_xy();
		}

		else if (wParam == '+') {
			block_arr[arr_index].size++;
		}
		else if (wParam == '-') {
			block_arr[arr_index].size--;
		}

		else if (wParam == 'c') {
			for (int i = 0; i < block_num; ++i) {
				if (block_arr[i].shape == block_arr[arr_index].shape) {
					block_arr[i].select = true;
				}
			}
		}

		else if (wParam == 'z') {
			for (int i = arr_index; i < block_num - 1; ++i) {
				block_arr[i] = block_arr[i + 1];
			}
			block_arr[9].block_initialize();
		}


		// 0 ~ 1 Ű�� ������ �迭�� �ε��� ��(�� ��° ���Ҹ� ������ ������) ����
		else if (wParam >= 48 && wParam <= 57) {
			arr_index = wParam - 48;
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- �޸� DC �����
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- �޸� DC�� ������ ��Ʈ�� �����
		SelectObject(mDC, (HBITMAP)hBitmap); //--- �޸� DC�� ��Ʈ�� �����ϱ�
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- ȭ�鿡 ����ֱ� ������ ȭ�� ������ �簢���� �׷� �������� �����ϱ�

		draw_board(mDC);

		// �÷��̾�� ���� �׸���
		for (int i = 0; i < block_num; ++i) {
			COLORREF temp_color = RGB(rand() % 256, rand() % 256, rand() % 256);
			HPEN hPen, oldPen{};
			// ���õǾ����� üũ
			if (i == arr_index) {
				hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
				oldPen = (HPEN)SelectObject(mDC, hPen);
			}
			// ������ ����̸� ��� X
			if (block_arr[i].shape == DELETED_Shape) {
				continue;
			}
			// 'c' Ű���� �ԷµǾ����� üũ, ���� ����̸� ���ٲٱ�
			else if (block_arr[i].select == true) {
				draw_diamond(mDC, block_arr[i].x - block_arr[i].size, block_arr[i].y - block_arr[i].size, block_arr[i].x + board_aside + block_arr[i].size, block_arr[i].y + board_aside + block_arr[i].size, temp_color);
			}
			// ��翡 ���� ����ϱ�
			else if (block_arr[i].shape == shape_circle) {
				draw_circle(mDC, block_arr[i].x - block_arr[i].size, block_arr[i].y - block_arr[i].size, block_arr[i].x + board_aside + block_arr[i].size, block_arr[i].y + board_aside + block_arr[i].size, temp_color);
			}
			else if (block_arr[i].shape == shape_triangle) {
				draw_triangle(mDC, block_arr[i].x - block_arr[i].size, block_arr[i].y - block_arr[i].size, block_arr[i].x + board_aside + block_arr[i].size, block_arr[i].y + board_aside + block_arr[i].size, temp_color);
			}
			else if (block_arr[i].shape == shape_rectangle) {
				draw_rectangle(mDC, block_arr[i].x - block_arr[i].size, block_arr[i].y - block_arr[i].size, block_arr[i].x + board_aside + block_arr[i].size, block_arr[i].y + board_aside + block_arr[i].size, temp_color);
			}
			
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(mDC, hPen);
		}

		// �� �� ����ϰ� ���� 'c' ��ɾ� ���� ����
		for (int i = 0; i < block_num; ++i) {
			block_arr[i].select = false;
		}

		//--- �������� �޸� DC�� ������ ȭ�� DC�� �����Ѵ�.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- ������ �޸� DC ����
		DeleteObject(hBitmap); //--- ������ ��Ʈ�� ����

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
	for (int i = 0; i < block_num; ++i) {
		block_arr[i].block_initialize();
	}
}

// �÷��̾ ������ �� �ΰ��� ��ĥ ��
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

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�

	Rectangle (mDC, x1, y1, x2, y2);

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

void draw_triangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�

	POINT point[] = {
	   {(x1 + x2) / 2, y1},
	   {x2, y2},
	   {x1, y2}
	};
	Polygon(mDC, point, 3);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
}

void draw_diamond(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�

	POINT point[] = {
	   {x1 + (x2 - x1) / 2,            y1},
	   {x1            ,y1 + (y2 - y1) / 2},
	   {x1 + (x2 - x1) / 2,            y2},
	   {x2           ,  y1 + (y2 - y1) / 2}
	};
	Polygon(mDC, point, 4);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
}

void draw_board(HDC mDC) {
	// 40 X 40 �� �׸���
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

void win_game(HDC mDC) {
	TCHAR temp[80] = TEXT("�¸�!!!");
	TextOut(mDC, 160, WINDOW_HEIGHT - 80, temp, lstrlen(temp));
}