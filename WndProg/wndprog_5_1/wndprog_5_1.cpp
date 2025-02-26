// [�ǽ� 5-1] �����쿡 ��� �׸� �ֱ�
#include <windows.h>			// ������ ��� ����
#include <TCHAR.H>
#include <ctime>
#include "atlimage.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define img_num 4


void Initialize();
void swap(int& a, int& b);

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
	static CImage img[img_num]{};
	static int img_width[img_num]{};
	static int img_height[img_num]{};
	static int img_left[img_num]{};
	static int img_top[img_num]{};
	static int img_right[img_num]{};
	static int img_bottom[img_num]{};

	static int selected_img{ -1 };

	static int border_x{};
	static int border_y{};

	static bool check_invert{ false };
	static bool timer_stop{ false };

	static bool left_drag_check{ false };
	static int temp_x{};
	static int temp_y{};

	

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		
		border_x = WINDOW_WIDTH;
		border_y = WINDOW_HEIGHT;

		for (int i = 0; i < img_num; ++i) {
			img[i].Load(L"waffle.jpg");
			img_width[i] = img[i].GetWidth();
			img_height[i] = img[i].GetHeight();
		}

		img_left[0] = 0;
		img_top[0] = 0;
		img_right[0] = border_x;
		img_bottom[0] = border_y;

		img_left[1] = border_x;
		img_top[1] = 0;
		img_right[1] = rt.right;
		img_bottom[1] = border_y;

		img_left[2] = 0;
		img_top[2] = border_y;
		img_right[2] = border_x;
		img_bottom[2] = rt.bottom;

		img_left[3] = border_x;
		img_top[3] = border_y;
		img_right[3] = rt.right;
		img_bottom[3] = rt.bottom;

		selected_img = -1;

		break;

	case WM_TIMER:
		switch (wParam) {
		case 1: //--- 1�� ���̵� Ÿ�̸�: 0.5�� �������� ����
			

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
			if (check_invert) check_invert = false;
			else check_invert = true;
		}

		else if (wParam == '-') {
			if (border_x <= 100 && border_y <= 100) break;
			
			border_x -= 100;
			border_y -= 100;

			img_right[0] = border_x;
			img_bottom[0] = border_y;

			img_left[1] = border_x;
			img_bottom[1] = border_y;

			img_top[2] = border_y;
			img_right[2] = border_x;

			img_left[3] = border_x;
			img_top[3] = border_y;
		}
		else if (wParam == '+') {
			if (border_x >= WINDOW_WIDTH && border_y >= WINDOW_HEIGHT) break;

			border_x += 100;
			border_y += 100;

			img_right[0] = border_x;
			img_bottom[0] = border_y;

			img_left[1] = border_x;
			img_bottom[1] = border_y;

			img_top[2] = border_y;
			img_right[2] = border_x;

			img_left[3] = border_x;
			img_top[3] = border_y;
		}

		else if (wParam == 'p') {
			for (int i = 0; i < img_num; ++i) {
				img_left[i] -= 40;
				img_right[i] -= 40;
			}
		}
		else if (wParam == 'o') {
			for (int i = 0; i < img_num; ++i) {
				img_left[i] += 40;
				img_right[i] += 40;
			}
		}

		/*img_left[0] = 0;
		img_top[0] = 0;
		img_right[0] = border_x;
		img_bottom[0] = border_y;

		img_left[1] = border_x;
		img_top[1] = 0;
		img_right[1] = rt.right;
		img_bottom[1] = border_x;

		img_left[2] = 0;
		img_top[2] = border_y;
		img_right[2] = border_x;
		img_bottom[2] = rt.bottom;

		img_left[3] = border_x;
		img_top[3] = border_y;
		img_right[3] = rt.right;
		img_bottom[3] = rt.bottom;*/

		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == VK_LEFT) {
			img_right[selected_img] -= 40;
			img_left[selected_img] -= 40;
		}
		else if (wParam == VK_RIGHT) {
			img_right[selected_img] += 40;
			img_left[selected_img] += 40;
		}

		InvalidateRect(hWnd, NULL, FALSE); //--- ȭ�鿡 �ٽñ׸��⸦ �� �� ������ ������ �������� �ʴ´�.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_LBUTTONDOWN:
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
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- �޸� DC �����
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- �޸� DC�� ������ ��Ʈ�� �����
		SelectObject(mDC, (HBITMAP)hBitmap); //--- �޸� DC�� ��Ʈ�� �����ϱ�
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- ȭ�鿡 ����ֱ� ������ ȭ�� ������ �簢���� �׷� �������� �����ϱ�

		for (int i = 0; i < img_num; ++i) {
			if (check_invert == false) {
				img[i].StretchBlt(mDC, img_left[i], img_top[i], img_right[i], img_bottom[i], 0, 0, img_width[i], img_height[i], SRCCOPY);
			}
			else if (check_invert) {
				img[i].StretchBlt(mDC, img_left[i], img_top[i], img_right[i], img_bottom[i], 0, 0, img_width[i], img_height[i], NOTSRCCOPY);
			}
		}

		if (selected_img != -1) {
			draw_rectangle(mDC, img_left[selected_img], img_top[selected_img], img_right[selected_img], img_bottom[selected_img], RGB(255, 0, 0));
		}

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
	
}

void swap(int& a, int& b) {
	int temp{};
	temp = a;
	a = b;
	b = temp;
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: �귯�� �����
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // ���ο� �귯�� �����ϱ�
	HPEN hPen = CreatePen(PS_SOLID, 10, color);
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	RECT rt{ x1, y1, x2, y2 };

	FrameRect(mDC, &rt, hBrush);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // ���ο� �� �����ϱ�
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}
