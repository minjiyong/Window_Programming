// [�ǽ� 2-9] ȭ�鿡 ���� �׸��� �� ������
#include <windows.h>			// ������ ��� ����
#include <TCHAR.H>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"shape";

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

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 950, 950, NULL, (HMENU)NULL, hInstance, NULL);

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
	HDC hDC;
	HBRUSH hBrush{}, oldBrush{};
	HPEN hPen{}, oldPen{};

	static int start_shape{ 0 };

	static POINT tri_point[6] = { {150,350}, {50,550}, {250,550} };
	static POINT sand_up_point[6] = { {350,50}, {550,50}, {450,150} };
	static POINT sand_down_point[6] = { {450,150}, {550,250}, {350,250} };
	static POINT pent_point[10] = { {750,350}, {850,435}, {800,550}, {700,550}, {650,435} };
	static int cir_left{ 350 };
	static int cir_up{ 650 };
	static int cir_right{ 550 };
	static int cir_down{ 850 };
	static int cir_x_start{ 450 };
	static int cir_y_start{ 650 };
	static int cir_x_end{ 550 };
	static int cir_y_end{ 750 };

	static POINT mid_tri_point[6] = { {450,300}, {600,600}, {300,600} };
	static POINT mid_sand_up_point[6] = { {300,300}, {600,300}, {450,450} };
	static POINT mid_sand_down_point[6] = { {450,450}, {600,600}, {300,600} };
	static POINT mid_pent_point[10] = { {450,300}, {600,435}, {530,600}, {370,600}, {300,435} };
	static int mid_cir_left{ 300 };
	static int mid_cir_up{ 300 };
	static int mid_cir_right{ 600 };
	static int mid_cir_down{ 600 };
	static int mid_cir_x_start{ 450 };
	static int mid_cir_y_start{ 300 };
	static int mid_cir_x_end{ 600 };
	static int mid_cir_y_end{ 450 };

	static int tri_locate{ 0 };
	static bool keydown_t{ false };
	static bool keyup_t{ false };
	static bool keydown_s{ false };
	static bool keyup_s{ false };
	static bool keydown_p{ false };
	static bool keyup_p{ false };
	static bool keydown_e{ false };
	static bool keyup_e{ false };

	COLORREF color{};
	

	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));

		start_shape = rand() % 4 + 1;
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		
		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == 't' || wParam == 'T') {
			if (keydown_t == false) keydown_t = true;
		}
		else if (wParam == 's' || wParam == 'S') {
			if (keydown_s == false) keydown_s = true;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (keydown_p == false) keydown_p = true;
		}
		else if (wParam == 'e' || wParam == 'E') {
			if (keydown_e == false) keydown_e = true;
		}

		else if (wParam == VK_LEFT) {
			if (tri_locate == 1) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x += 300;
					tri_point[i].y -= 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x += 300;
					sand_up_point[i].y += 300;
					sand_down_point[i].x += 300;
					sand_down_point[i].y += 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x -= 300;
					pent_point[i].y += 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left -= 300;
				cir_right -= 300;
				cir_x_start -= 300;
				cir_x_end -= 300;

				cir_up -= 300;
				cir_down -= 300;
				cir_y_start -= 300;
				cir_y_end -= 300;
				
				tri_locate = 2;
			}
			else if (tri_locate == 2) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x += 300;
					tri_point[i].y += 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x -= 300;
					sand_up_point[i].y += 300;
					sand_down_point[i].x -= 300;
					sand_down_point[i].y += 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x -= 300;
					pent_point[i].y -= 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left += 300;
				cir_right += 300;
				cir_x_start += 300;
				cir_x_end += 300;

				cir_up -= 300;
				cir_down -= 300;
				cir_y_start -= 300;
				cir_y_end -= 300;

				tri_locate = 3;
			}
			else if (tri_locate == 3) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x -= 300;
					tri_point[i].y += 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x -= 300;
					sand_up_point[i].y -= 300;
					sand_down_point[i].x -= 300;
					sand_down_point[i].y -= 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x += 300;
					pent_point[i].y -= 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left += 300;
				cir_right += 300;
				cir_x_start += 300;
				cir_x_end += 300;

				cir_up += 300;
				cir_down += 300;
				cir_y_start += 300;
				cir_y_end += 300;

				tri_locate = 4;
			}
			else if (tri_locate == 4) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x -= 300;
					tri_point[i].y -= 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x += 300;
					sand_up_point[i].y -= 300;
					sand_down_point[i].x += 300;
					sand_down_point[i].y -= 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x += 300;
					pent_point[i].y += 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left -= 300;
				cir_right -= 300;
				cir_x_start -= 300;
				cir_x_end -= 300;

				cir_up += 300;
				cir_down += 300;
				cir_y_start += 300;
				cir_y_end += 300;

				tri_locate = 1;
			}
			else if (tri_locate == 0) {
				tri_locate = 1;
				SendMessage(hWnd, WM_KEYDOWN, VK_LEFT, 0);
			}
		}
		else if (wParam == VK_RIGHT) {
			if (tri_locate == 1) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x += 300;
					tri_point[i].y += 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x -= 300;
					sand_up_point[i].y += 300;
					sand_down_point[i].x -= 300;
					sand_down_point[i].y += 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x -= 300;
					pent_point[i].y -= 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left += 300;
				cir_right += 300;
				cir_x_start += 300;
				cir_x_end += 300;

				cir_up -= 300;
				cir_down -= 300;
				cir_y_start -= 300;
				cir_y_end -= 300;

				tri_locate = 4;
			}
			else if (tri_locate == 2) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x -= 300;
					tri_point[i].y += 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x -= 300;
					sand_up_point[i].y -= 300;
					sand_down_point[i].x -= 300;
					sand_down_point[i].y -= 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x += 300;
					pent_point[i].y -= 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left += 300;
				cir_right += 300;
				cir_x_start += 300;
				cir_x_end += 300;

				cir_up += 300;
				cir_down += 300;
				cir_y_start += 300;
				cir_y_end += 300;

				tri_locate = 1;
			}
			else if (tri_locate == 3) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x -= 300;
					tri_point[i].y -= 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x += 300;
					sand_up_point[i].y -= 300;
					sand_down_point[i].x += 300;
					sand_down_point[i].y -= 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x += 300;
					pent_point[i].y += 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left -= 300;
				cir_right -= 300;
				cir_x_start -= 300;
				cir_x_end -= 300;

				cir_up += 300;
				cir_down += 300;
				cir_y_start += 300;
				cir_y_end += 300;

				tri_locate = 2;
			}
			else if (tri_locate == 4) {
				// �ﰢ�� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					tri_point[i].x += 300;
					tri_point[i].y -= 300;
				}
				// �𷡽ð� ��ġ �ٲٱ�
				for (int i = 0; i < 3; ++i) {
					sand_up_point[i].x += 300;
					sand_up_point[i].y += 300;
					sand_down_point[i].x += 300;
					sand_down_point[i].y += 300;
				}
				// ������ ��ġ �ٲٱ�
				for (int i = 0; i < 5; ++i) {
					pent_point[i].x -= 300;
					pent_point[i].y += 300;
				}
				// ���� ��ġ �ٲٱ�
				cir_left -= 300;
				cir_right -= 300;
				cir_x_start -= 300;
				cir_x_end -= 300;

				cir_up -= 300;
				cir_down -= 300;
				cir_y_start -= 300;
				cir_y_end -= 300;

				tri_locate = 3;
			}
			else if (tri_locate == 0) {
				tri_locate = 1;
				SendMessage(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
			}
		}

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_KEYUP:
		hDC = GetDC(hWnd);

		if (wParam == 't' || wParam == 'T') {
			if (keyup_t == false) keyup_t = true;
		}
		else if (wParam == 's' || wParam == 'S') {
			if (keyup_s == false) keyup_s = true;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (keyup_p == false) keyup_p = true;
		}
		else if (wParam == 'e' || wParam == 'E') {
			if (keyup_e == false) keyup_e = true;
		}

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		// �⺻ ��� �׵θ� �簢�� �����
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);

		Rectangle(hDC, 300, 300, 600, 600);

		// �� ��� �����
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		// ���� �ﰢ�� �����
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Polygon(hDC, tri_point, 3);

		// ���� �𷡽ð� �����
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Polygon(hDC, sand_up_point, 3);
		Polygon(hDC, sand_down_point, 3);

		// ������ ������ �����
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Polygon(hDC, pent_point, 5);

		// �Ʒ� ���� �����
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Pie(hDC, cir_left, cir_up, cir_right, cir_down, cir_x_start, cir_y_start, cir_x_end, cir_y_end);

		// ����� �� ���� �����
		switch (start_shape) {
		case 1:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_tri_point, 3);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_sand_up_point, 3);
			Polygon(hDC, mid_sand_down_point, 3);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_pent_point, 5);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Pie(hDC, mid_cir_left, mid_cir_up, mid_cir_right, mid_cir_down, mid_cir_x_start, mid_cir_y_start, mid_cir_x_end, mid_cir_y_end);
			break;
		}

		// ����, ������ ȭ��ǥ�� ���� �� ����� �� ���� ã��
		switch (tri_locate) {
		case 1:
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_sand_up_point, 3);
			Polygon(hDC, mid_sand_down_point, 3);
			break;
		case 2:
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_tri_point, 3);
			break;
		case 3:
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Pie(hDC, mid_cir_left, mid_cir_up, mid_cir_right, mid_cir_down, mid_cir_x_start, mid_cir_y_start, mid_cir_x_end, mid_cir_y_end);
			break;
		case 4:
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_pent_point, 5);
			break;
		}

		if (keydown_t == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �ﰢ�� ���
			hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Polygon(hDC, mid_tri_point, 3);
			Polygon(hDC, tri_point, 3);
			keydown_t = false;
		} 
		if (keyup_t == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			// �ﰢ�� ���
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_tri_point, 3);
			Polygon(hDC, tri_point, 3);
			keyup_t = false;
		}
		if (keydown_s == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �𷡽ð� ���
			hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_sand_up_point, 3);
			Polygon(hDC, mid_sand_down_point, 3);
			Polygon(hDC, sand_up_point, 3);
			Polygon(hDC, sand_down_point, 3);
			keydown_s = false;
		}
		if (keyup_s == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			// �𷡽ð� ���
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, mid_sand_up_point, 3);
			Polygon(hDC, mid_sand_down_point, 3);
			Polygon(hDC, sand_up_point, 3);
			Polygon(hDC, sand_down_point, 3);
			keyup_s = false;
		}
		if (keydown_p == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// ������ ���
			hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, pent_point, 5);
			Polygon(hDC, mid_pent_point, 5);
			keydown_p = false;
		}
		if (keyup_p == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			// ������ ���
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Polygon(hDC, pent_point, 5);
			Polygon(hDC, mid_pent_point, 5);
			keyup_p = false;
		}
		if (keydown_e == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);
			
			// ���� ���
			hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Pie(hDC, cir_left, cir_up, cir_right, cir_down, cir_x_start, cir_y_start, cir_x_end, cir_y_end);
			Pie(hDC, mid_cir_left, mid_cir_up, mid_cir_right, mid_cir_down, mid_cir_x_start, mid_cir_y_start, mid_cir_x_end, mid_cir_y_end);
			keydown_e = false;
		}
		if (keyup_e == true) {
			// �� ���� ���� ���� ����
			hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, 300, 300, 600, 600);

			// �� ��� �����
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			// ���� ���
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Pie(hDC, cir_left, cir_up, cir_right, cir_down, cir_x_start, cir_y_start, cir_x_end, cir_y_end);
			Pie(hDC, mid_cir_left, mid_cir_up, mid_cir_right, mid_cir_down, mid_cir_x_start, mid_cir_y_start, mid_cir_x_end, mid_cir_y_end);
			keyup_e = false;
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}