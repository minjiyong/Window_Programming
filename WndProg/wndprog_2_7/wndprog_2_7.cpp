// [실습 2-7] 실습 2-5를 이어 캐럿을 이용한 메모장 만들기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"메모장~";

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

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

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
	static TCHAR str[10][80]{};
	static TCHAR temp_str[800]{};
	static int county{ 0 };
	static int countx{ 0 };

	static SIZE size[80]{};
	static int c_count{ 0 };
	static bool large_eng{ false };
	static bool insert{ false };

	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_DELETE) {
			int temp_cx{ countx };
			for (int i = temp_cx; str[county][i] != ' '; i--) {
				str[county][i] = 10;
			}
			for (int i = temp_cx + 1; str[county][i] != ' ' && str[county][i] != '\0'; i++) {
				str[county][i] = 10;
			}
			for (int i = 0; i < lstrlen(str[county]); ++i) {
				if (str[county][i] == 10) {
					for (int j = i; j < lstrlen(str[county]) + 1; ++j) {
						str[county][j] = str[county][j + 1];
					}
					i--;
				}
			}
		} 
		else if (wParam == VK_HOME) {
			countx = 0;
			c_count = 0;
		}
		else if (wParam == VK_END) {
			countx = lstrlen(str[county]);
			c_count = countx;
		}
		else if (wParam == VK_INSERT) {
			if (insert == false) insert = true;
			else if (insert == true) insert = false;
		}
		else if (wParam == VK_LEFT) {
			if (countx == 0) break;
			countx--;
			c_count--;
		}
		else if (wParam == VK_RIGHT) {
			if (countx == lstrlen(str[county])) break;
			countx++;
			c_count++;
		}
		else if (wParam == VK_UP) {
			if (county == 0) break;
			if (countx > lstrlen(str[county - 1])) {
				countx = lstrlen(str[county - 1]);
				c_count = countx;
			}
			county--;
		}
		else if (wParam == VK_DOWN) {
			if (county == 10) break;
			else if (str[county + 1][0] == '\0') break;
			if (countx > lstrlen(str[county + 1])) {
				countx = lstrlen(str[county + 1]);
				c_count = countx;
			}
			county++;
		}
		else if (wParam == VK_F1) {
			if (large_eng == false) large_eng = true;
			else if (large_eng == true) large_eng = false;
		}
		
		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_BACK) {
			if (countx == 0) break;
			countx--;
			for (int i = countx; i < lstrlen(str[county]) + 1; ++i) {
				str[county][i] = str[county][i + 1];
			}
			c_count--;
		}
		else if (wParam == VK_RETURN) {
			countx = 0;
			county++;
			c_count = 0;
		}
		else if (wParam == VK_ESCAPE) {
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 80; ++j) {
					str[i][j] = '\0';
				}
			}
			countx = 0; 
			county = 0; 
			c_count = 0;
		}
		else if (wParam == VK_TAB) {
			for (int i = 0; i < 5; ++i) {
				str[county][countx] = ' ';
				countx++;
				c_count++;
			}
		}
		else {
			if (insert == true) {
				if (large_eng == true) {
					if (wParam >= 97 && wParam <= 122) {
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							temp_str[i] = str[county][i];
						}
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							str[county][i + 1] = temp_str[i];
							str[county][30] = '\0';
						}
						str[county][countx++] = wParam - 32;
						c_count++;
					}
					else if (wParam >= 65 && wParam <= 90) {
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							temp_str[i] = str[county][i];
						}
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							str[county][i + 1] = temp_str[i];
							str[county][30] = '\0';
						}
						str[county][countx++] = wParam + 32;
						c_count++;
					}
					else {
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							temp_str[i] = str[county][i];
						}
						for (int i = countx; i < lstrlen(str[county]); ++i) {
							str[county][i + 1] = temp_str[i];
							str[county][30] = '\0';
						}
						str[county][countx++] = wParam;
						c_count++;
					}
				}
				else if (large_eng == false) {
					for (int i = countx; i < lstrlen(str[county]); ++i) {
						temp_str[i] = str[county][i];
					}
					for (int i = countx; i < lstrlen(str[county]); ++i) {
						str[county][i + 1] = temp_str[i];
						str[county][30] = '\0';
					}
					str[county][countx++] = wParam;
					c_count++;
				}
			}
			else if (insert == false) {
				if (large_eng == true) {
					if (wParam >= 97 && wParam <= 122) {
						str[county][countx++] = wParam - 32;
						c_count++;
					}
					else if (wParam >= 65 && wParam <= 90) {
						str[county][countx++] = wParam + 32;
						c_count++;
					}
					else {
						str[county][countx++] = wParam;
						c_count++;
					}
				}
				else if (large_eng == false) {
					str[county][countx++] = wParam;
					c_count++;
				}
			}
		}

		if (countx == 30) {
			countx = 0;
			county++;
			c_count = 0;
		} 
		
		if (county == 10) {
			countx = 0;
			county = 0;
			c_count = 0;
		}
		
		for (int i = 0; i < 80; ++i) {
			temp_str[i] = '\0';
		}

		InvalidateRect(hWnd, NULL, true);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 10; ++i) {
			TextOut(hDC, 0, 0 + 20 * i, str[i], lstrlen(str[i]));
		}


		GetTextExtentPoint32(hDC, str[county], c_count, &size[c_count]);


		SetCaretPos(size[c_count].cx, 0 + 20 * county);

		EndPaint(hWnd, &ps);
		break;



	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);

		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}