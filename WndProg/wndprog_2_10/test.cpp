#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <iostream>

#include "MyH.h"

HINSTANCE g_hInst;

LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
HDC hDC;

void Initialize();
void DrawObject();
void KeyDownEvents(HWND hWnd, WPARAM wParam);
void KeyUpEvents(HWND hWnd, WPARAM wParam);

void MakeLine(float x1, float y1, float x2, float y2);
void Triangle(float midbottom_x, float midbottom_y, float height);
void MakeButterFly_Rotated(float x1, float y1, float x2, float y2, COLORREF color);
void MakeTriangle(float x1, float y1, float x2, float y2, COLORREF color);
void MakePentagon(float x1, float y1, float x2, float y2, COLORREF color);
void MakePishape(float x1, float y1, float x2, float y2, COLORREF color);
void MakeDiamond(float x1, float y1, float x2, float y2, COLORREF color);

void DrawBoard();

void UpdatePlayer();

#define shape_butterfly 1
#define shape_pi 2
#define shape_fiveangle 3
#define shape_triangle 4
#define shape_diamond 5

#define howmanyshapes 8

struct Shapes {
    std::string type;
    int shape{};
    int x{ 0 };
    int y{ 0 };
    int size{ 0 };
    COLORREF color;

    int dir{ 0 };

    float BoardX()
    {
        return (WINDOW_WIDTH / 40 * x) + WINDOW_WIDTH / 80;
    }
    float BoardY()
    {
        return (WINDOW_HEIGHT / 40 * y) + WINDOW_HEIGHT / 80;
    }
};

Shapes shapes[howmanyshapes];

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASSEX WindowClass;

    g_hInst = hInstance;

    WindowClass.cbSize = sizeof(WindowClass);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = (WNDPROC)WndProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = lpszClass;
    WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WindowClass);

    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    //--- 메시지 처리하기
    switch (uMsg)
    {
    case WM_CREATE:

        Initialize();

        break;

    case WM_CHAR:
        break;

    case WM_KEYDOWN:
        hDC = GetDC(hWnd);

        KeyDownEvents(hWnd, wParam);

        ReleaseDC(hWnd, hDC);
        break;

    case WM_KEYUP:
        hDC = GetDC(hWnd);

        KeyUpEvents(hWnd, wParam);

        ReleaseDC(hWnd, hDC);
        break;

    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);

        UpdatePlayer();
        DrawObject();

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}

void DrawObject()
{
    DrawBoard();

    for (int i{}; i < howmanyshapes; ++i)
    {
        int x1 = shapes[i].BoardX() - shapes[i].size;
        int y1 = shapes[i].BoardY() - shapes[i].size;
        int x2 = shapes[i].BoardX() + shapes[i].size;
        int y2 = shapes[i].BoardY() + shapes[i].size;

        switch (shapes[i].shape)
        {
        case(shape_pi):
            MakePishape(x1, shapes[i].BoardY() - shapes[i].size, shapes[i].BoardX() + shapes[i].size, shapes[i].BoardY() + shapes[i].size, shapes[i].color);
            break;

        case(shape_butterfly):
            MakeButterFly_Rotated(shapes[i].BoardX() - shapes[i].size, shapes[i].BoardY() - shapes[i].size, shapes[i].BoardX() + shapes[i].size, shapes[i].BoardY() + shapes[i].size, shapes[i].color);
            break;

        case(shape_triangle):
            MakeTriangle(shapes[i].BoardX() - shapes[i].size, shapes[i].BoardY() - shapes[i].size, shapes[i].BoardX() + shapes[i].size, shapes[i].BoardY() + shapes[i].size, shapes[i].color);
            break;

        case(shape_diamond):
            MakeDiamond(shapes[i].BoardX() - shapes[i].size, shapes[i].BoardY() - shapes[i].size, shapes[i].BoardX() + shapes[i].size, shapes[i].BoardY() + shapes[i].size, shapes[i].color);
            break;

        case(shape_fiveangle):
            MakePentagon(shapes[i].BoardX() - shapes[i].size, shapes[i].BoardY() - shapes[i].size, shapes[i].BoardX() + shapes[i].size, shapes[i].BoardY() + shapes[i].size, shapes[i].color);
            break;
        }
    }
}

void Initialize()
{
    shapes[0].type = "Player";
    shapes[0].shape = shape_pi;
    shapes[0].x = 0;
    shapes[0].y = 0;
    shapes[0].size = 7;
    shapes[0].color = RGB(0, 0, 255);

    shapes[1].type = "End";
    shapes[1].shape = shape_butterfly;
    shapes[1].x = 30;
    shapes[1].y = 30;
    shapes[1].size = 7;
    shapes[1].color = RGB(255, 0, 0);

    shapes[2].type = "Huddle";
    shapes[2].shape = shape_triangle;
    shapes[2].x = MyH::Randint(0, 39);
    shapes[2].y = MyH::Randint(0, 39);
    shapes[2].size = 7;
    shapes[2].color = RGB(255, 0, 0);

    shapes[3].type = "SizeUp";
    shapes[3].shape = shape_diamond;
    shapes[3].x = MyH::Randint(0, 39);
    shapes[3].y = MyH::Randint(0, 39);
    shapes[3].size = 7;
    shapes[3].color = RGB(0, 255, 0);

    shapes[4].type = "SizeDown";
    shapes[4].shape = shape_diamond;
    shapes[4].x = MyH::Randint(0, 39);
    shapes[4].y = MyH::Randint(0, 39);
    shapes[4].size = 7;
    shapes[4].color = RGB(255, 255, 0);

    shapes[5].type = "ChangeShape";
    shapes[5].shape = shape_diamond;
    shapes[5].x = MyH::Randint(0, 39);
    shapes[5].y = MyH::Randint(0, 39);
    shapes[5].size = 7;
    shapes[5].color = RGB(0, 0, 0);

    shapes[6].type = "ChangeColor1";
    shapes[6].shape = shape_diamond;
    shapes[6].x = MyH::Randint(0, 39);
    shapes[6].y = MyH::Randint(0, 39);
    shapes[6].size = 7;
    shapes[6].color = RGB(100, 100, 100);

    shapes[7].type = "ChangeColor2";
    shapes[7].shape = shape_diamond;
    shapes[7].x = MyH::Randint(0, 39);
    shapes[7].y = MyH::Randint(0, 39);
    shapes[7].size = 7;
    shapes[7].color = RGB(255, 0, 0);
}

void KeyDownEvents(HWND hWnd, WPARAM wParam)
{

    switch (wParam)
    {
    case 'W':
    case 'w':
        if (shapes[0].y > 0) shapes[0].y -= 1;
        shapes[0].dir = 1;
        break;

    case 'S':
    case 's':
        if (shapes[0].y < 40 - 1)shapes[0].y += 1;
        shapes[0].dir = 2;
        break;

    case 'A':
    case 'a':
        if (shapes[0].x > 0) shapes[0].x -= 1;
        shapes[0].dir = 3;
        break;

    case 'D':
    case 'd':
        if (shapes[0].x < 40 - 1) shapes[0].x += 1;
        shapes[0].dir = 4;
        break;

    case 'R':
    case 'r':
        Initialize();
        break;

    case 'Q':
    case 'q':
        PostQuitMessage(0);
        break;
    }


    InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
}

void KeyUpEvents(HWND hWnd, WPARAM wParam)
{
    InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
}

void UpdatePlayer()
{
    for (int i{}; i < howmanyshapes; ++i)
    {
        if (shapes[i].type == "End")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                PostQuitMessage(0);
            }
        }

        if (shapes[i].type == "Huddle")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                switch (shapes[0].dir)
                {
                case (1):
                    shapes[0].y += 1;
                    break;
                case (2):
                    shapes[0].y -= 1;
                    break;
                case (3):
                    shapes[0].x += 1;
                    break;
                case (4):
                    shapes[0].x -= 1;
                    break;
                }
            }
        }

        if (shapes[i].type == "SizeUp")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                shapes[0].size += 1;
            }
        }

        if (shapes[i].type == "SizeDown")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                shapes[0].size -= 1;
            }
        }

        if (shapes[i].type == "ChangeShape")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                shapes[0].shape = MyH::Randint(1, 5);
            }
        }

        if (shapes[i].type == "ChangeColor1")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                shapes[0].color = shapes[i].color;
            }
        }

        if (shapes[i].type == "ChangeColor2")
        {
            if (shapes[0].x == shapes[i].x && shapes[0].y == shapes[i].y)
            {
                shapes[0].color = shapes[i].color;
            }
        }
    }
}


void Triangle(float midbottom_x, float midbottom_y, float height)
{
    POINT point[] = {
       {midbottom_x - height / sqrt(3), midbottom_y},
       {midbottom_x + height / sqrt(3), midbottom_y},
       {midbottom_x, midbottom_y - height}
    };
    Polygon(hDC, point, 3);
}

void MakeLine(float x1, float y1, float x2, float y2)
{
    MoveToEx(hDC, x1, y1, NULL);
    LineTo(hDC, x2, y2);
}

void MakeButterFly_Rotated(float x1, float y1, float x2, float y2, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush); // 새로운 브러시 선택하기

    POINT point[] = {
       {x1,y1},
       {x2,y2},
       {x1,y2},
       {x2,y1}
    };
    Polygon(hDC, point, 4);

    hBrush = (HBRUSH)SelectObject(hDC, oldBrush); // 새로운 펜 선택하기
    DeleteObject(hBrush);
}

void MakeTriangle(float x1, float y1, float x2, float y2, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush); // 새로운 브러시 선택하기

    float height = y2 - y1;

    Triangle(x1 + (x2 - x1) / 2, y2, height);

    hBrush = (HBRUSH)SelectObject(hDC, oldBrush); // 새로운 펜 선택하기
    DeleteObject(hBrush);
}

void MakePentagon(float x1, float y1, float x2, float y2, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color);  // GDI: 브러시 만들기
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush); // 새로운 브러시 선택하기

    POINT point[] = {
       {x1 + (x2 - x1) / 2,y1},
       {x1,y1 + (y2 - y1) / 3},
       {x1 + (x2 - x1) / 3,y2},
       {x1 + (x2 - x1) / 3 * 2,y2},
       {x2,y1 + (y2 - y1) / 3}
    };
    Polygon(hDC, point, 5);

    hBrush = (HBRUSH)SelectObject(hDC, oldBrush); // 새로운 펜 선택하기
    DeleteObject(hBrush);
}

void MakePishape(float x1, float y1, float x2, float y2, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush); // 새로운 브러시 선택하기

    Pie(hDC, x1, y1, x2, y2, x1, y1, x2, y1);

    hBrush = (HBRUSH)SelectObject(hDC, oldBrush); // 새로운 펜 선택하기
    DeleteObject(hBrush);
}

void MakeDiamond(float x1, float y1, float x2, float y2, COLORREF color)
{
    HBRUSH hBrush = CreateSolidBrush(color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush); // 새로운 브러시 선택하기

    POINT point[] = {
       {x1 + (x2 - x1) / 2,            y1},
       {x1            ,y1 + (y2 - y1) / 2},
       {x1 + (x2 - x1) / 2,            y2},
       {x2           ,  y1 + (y2 - y1) / 2}
    };
    Polygon(hDC, point, 4);

    hBrush = (HBRUSH)SelectObject(hDC, oldBrush); // 새로운 펜 선택하기
    DeleteObject(hBrush);
}

void DrawBoard()
{
    float gap_x = WINDOW_WIDTH / 40;
    float gap_y = WINDOW_HEIGHT / 40;

    for (int i{}; i < 40 + 1; ++i)
    {
        MakeLine(0, gap_y * i, WINDOW_HEIGHT, gap_y * i);
    }

    for (int i{}; i < 40 + 1; ++i)
    {
        MakeLine(gap_x * i, 0, gap_x * i, WINDOW_WIDTH);
    }

}
