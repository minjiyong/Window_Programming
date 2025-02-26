// [실습 5-4] 이동하며 마우스에 반응하는 캐릭터 애니메이션
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>
#include <atlImage.h>
#include "IMAGE.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define twin_num 5
#define img_num 6

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4


IMAGE Animation[twin_num][img_num]{};
IMAGE Background{};


void Initialize();
void InitializeBackground();
void InitializeAnimation(int TwinIndex);
void AnimationUpdate(int TwinIndex);

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);


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

	static bool left_drag_check{ false };
	static bool e_button_check{ false };
	static bool s_button_check{ false };

	static int TwinIndex{ 0 };
	static int CreateIndex{ 0 };
	static int AnimationIndex{ 0 };

	int box_left = Animation[TwinIndex][0].img_left;
	int box_top = Animation[TwinIndex][0].img_top;
	int box_right = Animation[TwinIndex][0].img_right;
	int box_bottom = Animation[TwinIndex][0].img_bottom;


	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		SetTimer(hWnd, 1, 300, NULL);
		SetTimer(hWnd, 2, 1, NULL);
		InitializeBackground();
		InitializeAnimation(CreateIndex);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: { //--- 1번 아이디 타이머: 0.3초 간격으로 실행
			++AnimationIndex;
			if (AnimationIndex == img_num) AnimationIndex = 0;
			break;
		}

		case 2: {
			for (int i = 0; i < img_num; ++i) {
				switch (Animation[TwinIndex][i].dir) {
				case UP:
					--Animation[TwinIndex][i].img_top;
					--Animation[TwinIndex][i].img_bottom;
					break;
				case LEFT:
					--Animation[TwinIndex][i].img_left;
					--Animation[TwinIndex][i].img_right;
					break;
				case DOWN:
					++Animation[TwinIndex][i].img_top;
					++Animation[TwinIndex][i].img_bottom;
					break;
				case RIGHT:
					++Animation[TwinIndex][i].img_left;
					++Animation[TwinIndex][i].img_right;
					break;
				}
			}
			AnimationUpdate(TwinIndex);
			break;
		}

		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}

		else if (wParam == 'e' || wParam == 'E') {
			if (!s_button_check) {
				for (int i = 0; i < img_num; ++i) {
					Animation[TwinIndex][i].img_right += 50;
					Animation[TwinIndex][i].img_bottom += 50;
				}
				s_button_check = true;
			}
			else if (s_button_check) {
				for (int i = 0; i < img_num; ++i) {
					Animation[TwinIndex][i].img_right -= 50;
					Animation[TwinIndex][i].img_bottom -= 50;
				}
				s_button_check = false;
			}
		}
		else if (wParam == 's' || wParam == 'S') {
			if (!e_button_check) {
				for (int i = 0; i < img_num; ++i) {
					Animation[TwinIndex][i].img_right -= 50;
					Animation[TwinIndex][i].img_bottom -= 50;
				}
				e_button_check = true;
			}
			else if (e_button_check) {
				for (int i = 0; i < img_num; ++i) {
					Animation[TwinIndex][i].img_right += 50;
					Animation[TwinIndex][i].img_bottom += 50;
				}
				e_button_check = false;
			}
		}

		else if (wParam == 't' || wParam == 'T') {
			if (CreateIndex == twin_num - 1) break;
			++CreateIndex;
			InitializeAnimation(CreateIndex);
		}

		else if (wParam == '0') {
			if (TwinIndex > CreateIndex) break;
			TwinIndex = 0;
		}
		else if (wParam == '1') {
			if (TwinIndex > CreateIndex) break;
			TwinIndex = 1;
		}
		else if (wParam == '2') {
			if (TwinIndex > CreateIndex) break;
			TwinIndex = 2;
		}
		else if (wParam == '3') {
			if (TwinIndex > CreateIndex) break;
			TwinIndex = 3;
		}
		else if (wParam == '4') {
			if (TwinIndex > CreateIndex) break;
			TwinIndex = 4;
		}


		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == VK_UP) {
			for (int i = 0; i < img_num; ++i) {
				Animation[TwinIndex][i].dir = UP;
			}
		}
		else if (wParam == VK_LEFT) {
			for (int i = 0; i < img_num; ++i) {
				Animation[TwinIndex][i].dir = LEFT;
			}
		}
		else if (wParam == VK_DOWN) {
			for (int i = 0; i < img_num; ++i) {
				Animation[TwinIndex][i].dir = DOWN;
			}
		}
		else if (wParam == VK_RIGHT) {
			for (int i = 0; i < img_num; ++i) {
				Animation[TwinIndex][i].dir = RIGHT;
			}
		}

		
		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	/*case WM_LBUTTONDOWN:
		left_drag_check = true;

		temp_x = LOWORD(lParam);
		temp_y = HIWORD(lParam);

		for (int i = 0; i < img_num; ++i) {
			if (temp_x > img_left[i] && temp_y > img_top[i] && temp_x < img_right[i] && temp_y < img_bottom[i]) {
				selected_img = i;
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		left_drag_check = false;

		InvalidateRect(hWnd, NULL, FALSE);
		break;*/

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기

		Background.img.StretchBlt(mDC, Background.img_left, Background.img_top, Background.img_right - Background.img_left, Background.img_bottom - Background.img_top, 0, 0, Background.img_width, Background.img_height, SRCCOPY);
		
		for (int i = 0; i < twin_num; ++i) {
			Animation[i][AnimationIndex].img.TransparentBlt(mDC, Animation[i][AnimationIndex].img_left, Animation[i][AnimationIndex].img_top, Animation[i][AnimationIndex].img_right - Animation[i][AnimationIndex].img_left, Animation[i][AnimationIndex].img_bottom - Animation[i][AnimationIndex].img_top, 0, 0, Animation[i][AnimationIndex].img_width, Animation[i][AnimationIndex].img_height, RGB(8, 57, 99));
		}

		draw_rectangle(mDC, box_left, box_top, box_right, box_bottom, RGB(255, 0, 0));


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
	for (int j = 0; j < twin_num; ++j) {
		Animation[j][0].img.Load(L"Chang Koehan_52.png");
		Animation[j][1].img.Load(L"Chang Koehan_53.png");
		Animation[j][2].img.Load(L"Chang Koehan_54.png");
		Animation[j][3].img.Load(L"Chang Koehan_55.png");
		Animation[j][4].img.Load(L"Chang Koehan_56.png");
		Animation[j][5].img.Load(L"Chang Koehan_57.png");

		int rand_X = rand() % (WINDOW_WIDTH - 400);
		int rand_Y = rand() % (WINDOW_HEIGHT - 400);
		for (int i = 0; i < img_num; ++i) {
			Animation[j][i].img_left = rand_X;
			Animation[j][i].img_top = rand_Y;
			Animation[j][i].ImageInitialize();
		}
	}
}

void InitializeAnimation(int TwinIndex)
{
	Animation[TwinIndex][0].img.Load(L"Chang Koehan_52.png");
	Animation[TwinIndex][1].img.Load(L"Chang Koehan_53.png");
	Animation[TwinIndex][2].img.Load(L"Chang Koehan_54.png");
	Animation[TwinIndex][3].img.Load(L"Chang Koehan_55.png");
	Animation[TwinIndex][4].img.Load(L"Chang Koehan_56.png");
	Animation[TwinIndex][5].img.Load(L"Chang Koehan_57.png");

	int rand_X = rand() % WINDOW_WIDTH;
	int rand_Y = rand() % WINDOW_HEIGHT;
	for (int i = 0; i < img_num; ++i) {
		Animation[TwinIndex][i].img_left = rand_X;
		Animation[TwinIndex][i].img_top = rand_Y;
		Animation[TwinIndex][i].ImageInitialize();
	}
	
}

void InitializeBackground() {
	Background.img.Load(L"background.png");
	Background.img_left = 0;
	Background.img_top = 0;
	Background.img_right = WINDOW_WIDTH;
	Background.img_bottom = WINDOW_HEIGHT;

	Background.img_width = Background.img.GetWidth();
	Background.img_height = Background.img.GetHeight();
}


void AnimationUpdate(int TwinIndex) {
	for (int i = 0; i < img_num; ++i) {
		if (Animation[TwinIndex][i].img_left <= 0) {
			Animation[TwinIndex][i].dir = RIGHT;
		}
		else if (Animation[TwinIndex][i].img_left >= WINDOW_WIDTH - Animation[TwinIndex][i].img_width) {
			Animation[TwinIndex][i].dir = LEFT;
		}
		else if (Animation[TwinIndex][i].img_top <= 0) {
			Animation[TwinIndex][i].dir = DOWN;
		}
		else if (Animation[TwinIndex][i].img_top >= WINDOW_HEIGHT - Animation[TwinIndex][i].img_height) {
			Animation[TwinIndex][i].dir = UP;
		}
	}
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 10, color);
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	RECT rt{ x1, y1, x2, y2 };

	FrameRect(mDC, &rt, hBrush);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}
