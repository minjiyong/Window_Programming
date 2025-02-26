// [숙제] 인버서스 만들기
#include <windows.h>			// 윈도우 헤더 파일
#include <TCHAR.H>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include "resource.h"

#pragma comment(lib, "winmm.lib")

#define WINDOW_WIDTH 1487
#define WINDOW_HEIGHT 820

#define Lv_HARD 3
#define Lv_NORMAL 2
#define Lv_EASY 1
#define Lv_NODAMAGE 0

#define block_aside 30
#define mini_aside 5

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

#define board_x_max 53
#define board_y_max 30

#define NORMAL 0
#define NODAMAGE 1

#define ROAD 1
#define NMOVEROAD 2
#define WALL 3

#define wall_num 10
#define bullet_num 6
#define bullet_aside 5

#define enemy_num 100
#define enemy_spd 0,1

#define deleted_obj -1000


class Player {
public:
	float x{};
	float y{};
	int aside{ block_aside };
	COLORREF color{ RGB(0, 0, 0) };
	int hp{ 1 };
	int life{ 3 };
	int condition{};
	int playerdir{};
	int bulletdir{};

	int rad{ 1 };
	float mini_x[bullet_num]{};
	float mini_y[bullet_num]{};

	Player() {};
	~Player() {};

	void player_initialize() {
		
	};

	void player_adjust() {
		
	};
};

class Block {
public:
	int x{};
	int y{};
	int aside{ block_aside };
	COLORREF color{ RGB(0, 0, 0) };
	int type{};

	Block() {};
	~Block() {};

	void block_initialize() {
		type = NMOVEROAD;
	};

	void wall_initialize() {
		x = rand() % board_x_max * block_aside;
		y = rand() % board_y_max * block_aside;
		type = WALL;
	};

	void block_adjust() {
		if (type == NMOVEROAD) color = RGB(111, 111, 111);
		else if (type == ROAD) color = RGB(255, 255, 255);
		else if (type == WALL) color = RGB(0, 0, 255);
	};
};

class Bullet {
public:
	int x{};
	int y{};
	int dir{};
	int hp{};
	int aside{ bullet_aside };

	Bullet() {};
	~Bullet() {};

	void bullet_initialize() {
		hp = 1;
		x = deleted_obj;
		y = deleted_obj;
	};

	void bullet_deleted() {
		if (hp <= 0) {
			x = deleted_obj;
			y = deleted_obj;
		}
	};
};

class Enemy {
public:
	float x{};
	float y{};
	int hp{ 1 };
	int aside{ block_aside };
	int deatheffect{};
	int deathaside{ 10 };

	Enemy() {};
	~Enemy() {};

	void enemy_initialize() {
		hp = 1;
		x = rand() % WINDOW_WIDTH;
		y = rand() % WINDOW_HEIGHT;
	};

	void enemy_deleted() {
		if (hp <= 0) {
			deatheffect = 5;
			deathaside = 20;
		}
	};
};


Player player{};
Block block[board_y_max][board_x_max]{};
Block wall[wall_num]{};
Bullet bullet[bullet_num]{};
Enemy enemy[enemy_num]{};
int score{ 0 };
int total_time{ 0 };
int combo{ 0 };


void Initialize();
float lerp(float p1, float p2, float d1);

void shoot_bullet(int& bullet_index);

void player_update(int& death_effectcnt);
void bullet_update();
void enemy_update();

void draw_player(HDC mDC, const int bullet_index, int death_aside);
void draw_block(HDC mDC);
void draw_wall(HDC mDC);
void draw_bullet(HDC mDC);
void draw_enemy(HDC mDC);
void print_status(HDC mDC);
void print_level(HDC mDC, int level);

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_framerectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color);
void draw_circle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color);


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"INVERSERS";

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //--- 메뉴 id 등록;;
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

	static int level{ Lv_NORMAL };

	static bool game_over{ false };
	static bool pause{ false };

	static int bullet_index{ 0 };
	static int enemy_index{ 0 };

	static int timer3{ 3000 };
	static int death_effectcnt{ 0 };
	static int death_aside{ 10 };


	switch (iMessage) {
	case WM_CREATE:
		srand(static_cast<int>(time(NULL)));
		SetTimer(hWnd, 1, 1, NULL);
		SetTimer(hWnd, 2, 1, NULL);
		SetTimer(hWnd, 3, timer3, NULL);
		SetTimer(hWnd, 4, 1, NULL);
		SetTimer(hWnd, 7, 1000, NULL);
		SetTimer(hWnd, 8, 1, NULL);
		SetTimer(hWnd, 9, 100, NULL);

		Initialize();
		//D:\\산기대\\2 - 1\\윈도우프로그래밍\\WndProg\\wndprog_inversers\\

		PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LEVEL_HARD:
			level = Lv_HARD;
			Initialize();
			game_over = false;
			pause = false;

			bullet_index = 0;
			enemy_index = 0;

			timer3 = 3000;
			death_effectcnt = 0;
			death_aside = 10;
			player.condition = NORMAL;
			PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		case ID_LEVEL_NORMAL:
			level = Lv_NORMAL;
			Initialize();
			game_over = false;
			pause = false;

			bullet_index = 0;
			enemy_index = 0;

			timer3 = 3000;
			death_effectcnt = 0;
			death_aside = 10;
			player.condition = NORMAL;
			PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		case ID_LEVEL_EASY:
			level = Lv_EASY;
			Initialize();
			game_over = false;
			pause = false;

			bullet_index = 0;
			enemy_index = 0;

			timer3 = 3000;
			death_effectcnt = 0;
			death_aside = 10;
			player.condition = NORMAL;
			PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		case ID_LEVEL_NODAMAGE:
			level = Lv_NODAMAGE;
			Initialize();
			game_over = false;
			pause = false;

			bullet_index = 0;
			enemy_index = 0;

			timer3 = 3000;
			death_effectcnt = 0;
			death_aside = 10;
			player.condition = NODAMAGE;
			PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam) {
			//총알 타이머
		case 1: {
			for (int i = 0; i < bullet_num; ++i) {
				if (bullet[i].dir == UP) bullet[i].y -= 15;
				else if (bullet[i].dir == LEFT) bullet[i].x -= 15;
				else if (bullet[i].dir == DOWN) bullet[i].y += 15;
				else if (bullet[i].dir == RIGHT) bullet[i].x += 15;
			}
			bullet_update();

			break;
		}
			//적 이동 타이머
		case 2: {
			for (int i = 0; i < enemy_num; ++i) {
				float spd{ 0.01 };

				float x = lerp(enemy[i].x, player.x, spd);
				float y = lerp(enemy[i].y, player.y, spd);

				enemy[i].x = x;
				enemy[i].y = y;
			}
			if (player.hp < 1) SetTimer(hWnd, 5, 1, NULL);
			player_update(death_effectcnt);
			enemy_update();

			break;
		}
			//적 리스폰 타이머
		case 3: {
			enemy[enemy_index].enemy_initialize();
			enemy_index++;
			enemy[enemy_index].enemy_initialize();
			enemy_index++;
			if (enemy_index >= enemy_num) enemy_index = 0;

			if (level == Lv_HARD) {
				if (timer3 < 300) {
					timer3 = 300;
				}
				else {
					timer3 -= 100;
				}
			}
			else if (level == Lv_NORMAL || level == Lv_NODAMAGE) {
				if (timer3 < 1000) {
					timer3 = 1000;
				}
				else {
					timer3 -= 100;
				}
			}
			else if (level == Lv_EASY) {
				if (timer3 < 1500) {
					timer3 = 1500;
				}
				else {
					timer3 -= 100;
				}
			}
			
			SetTimer(hWnd, 3, timer3, NULL);
			break;
		}
			//플레이어 몸 안에서 총알 돌리기 타이머
		case 4:{
			float playermidx{ player.x + player.aside / 2 };
			float playermidy{ player.y + player.aside / 2 };
			float temp_rad = player.rad * (M_PI / 180);
			float rad60 = 60 * (M_PI / 180);
			
			for (int i = 0; i < bullet_num; ++i) {
				player.mini_x[i] = playermidx + 10 * cos(temp_rad + i * rad60);
				player.mini_y[i] = playermidy + 10 * sin(temp_rad + i * rad60);
			}
			player.rad += 10;
			break;
		}

			  // 플레이어 사망 이펙트, 리스폰 타이머
		case 5: {
			++death_effectcnt;	// 해당 타이머 실행 횟수 체크
			death_aside += 5;
			player.hp = 1;
			player.condition = NODAMAGE;
			player.x = 720;
			player.y = 360;

			// 부활 후 주변 칸 빈칸으로 바꾸기
			float hitbox_x = player.x - player.aside;
			float hitbox_y = player.y - player.aside;
			float hitbox_endx = player.x + player.aside * 2;
			float hitbox_endy = player.y + player.aside * 2;

			for (int i = 0; i < enemy_num; ++i) {
				if (enemy[i].hp < 1) continue;
				if (hitbox_x < enemy[i].x + enemy[i].aside && hitbox_y < enemy[i].y + enemy[i].aside
					&& hitbox_endx > enemy[i].x && hitbox_endy > enemy[i].y) {
					enemy[i].deatheffect = 5;
					--enemy[i].hp;
					enemy[i].enemy_deleted();
				}
			}

			for (int i = 0; i < board_y_max; ++i) {
				for (int j = 0; j < board_x_max; ++j) {
					if (hitbox_x < block[i][j].x + block[i][j].aside && hitbox_y < block[i][j].y + block[i][j].aside
						&& hitbox_endx > block[i][j].x && hitbox_endy > block[i][j].y) {
						block[i][j].type = ROAD;
						block[i][j].block_adjust();
					}
				}
			}

			if (death_effectcnt == 5) {
				death_effectcnt = 0;
				death_aside = 10;
				SetTimer(hWnd, 6, 2000, NULL);	// 부활 후 무적시간 타이머 실행
				KillTimer(hWnd, 5);
			}
			break;
		}

			  // 부활 후 무적시간 타이머
		case 6: {
			player.condition = NORMAL;
			KillTimer(hWnd, 6);
			break;
		}

			  // 시간 타이머
		case 7: {
			++total_time;
			break;
		}

			  // 점수, 게임오버 체크 타이머
		case 8: {
			++score;
			if (player.life < 0) {
				game_over = true;
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
				KillTimer(hWnd, 6);
				KillTimer(hWnd, 7);
				KillTimer(hWnd, 8);
				KillTimer(hWnd, 9);
				MessageBox(NULL, TEXT("게임오버!"), TEXT("system"), MB_OK);
				PlaySound(NULL, 0, 0);
			}
			break;
		}

			  // 적 처치 후 이펙트 타이머
		case 9: {
			for (int i = 0; i < enemy_num; ++i) {
				if (enemy[i].deatheffect != 0) {
					enemy[i].deathaside += 5;
					--enemy[i].deatheffect;
				}
				else if (enemy[i].deatheffect <= 0) {
					enemy[i].deatheffect = 0;
					enemy[i].deathaside = 20;
				}
			}
			break;
		}

		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'n' || wParam == 'N') {
			Initialize();
			level = Lv_NORMAL;
			game_over = false;
			pause = false;

			bullet_index = 0;
			enemy_index = 0;

			timer3 = 3000 ;
			death_effectcnt = 0 ;
			death_aside = 10 ;
		}
		else if (wParam == 'p' || wParam == 'P') {
			if (!pause) {
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
				KillTimer(hWnd, 6);
				KillTimer(hWnd, 7);
				KillTimer(hWnd, 8);
				KillTimer(hWnd, 9);
				PlaySound(NULL, 0, 0);
				pause = true;
			}
			else if (pause) {
				SetTimer(hWnd, 1, 1, NULL);
				SetTimer(hWnd, 2, 1, NULL);
				SetTimer(hWnd, 3, timer3, NULL);
				SetTimer(hWnd, 4, 1, NULL);
				SetTimer(hWnd, 7, 1000, NULL);
				SetTimer(hWnd, 8, 1, NULL);
				SetTimer(hWnd, 9, 1, NULL);
				PlaySound(TEXT("seobuvillage.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				pause = false;
			}
		}

		if (!pause) {
			if (wParam == 'w' || wParam == 'W') {
				player.y -= 15;
				player.playerdir = UP;
			}
			else if (wParam == 'a' || wParam == 'A') {
				player.x -= 15;
				player.playerdir = LEFT;
			}
			else if (wParam == 's' || wParam == 'S') {
				player.y += 15;
				player.playerdir = DOWN;
			}
			else if (wParam == 'd' || wParam == 'D') {
				player.x += 15;
				player.playerdir = RIGHT;
			}

			else if (wParam == VK_UP) {
				player.bulletdir = UP;
				shoot_bullet(bullet_index);
			}
			else if (wParam == VK_LEFT) {
				player.bulletdir = LEFT;
				shoot_bullet(bullet_index);
			}
			else if (wParam == VK_DOWN) {
				player.bulletdir = DOWN;
				shoot_bullet(bullet_index);
			}
			else if (wParam == VK_RIGHT) {
				player.bulletdir = RIGHT;
				shoot_bullet(bullet_index);
			}
			else if (wParam == 'r' || wParam == 'R') {
				if (bullet_index == bullet_num) bullet_index = 0;
				for (int i = 0; i < bullet_num; ++i) {
					bullet[i].hp = 1;
				}
			}
		}
		player_update(death_effectcnt);


		InvalidateRect(hWnd, NULL, FALSE); //--- 화면에 다시그리기를 할 때 기존의 내용을 삭제하지 않는다.

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mDC, (HBITMAP)hBitmap); //--- 메모리 DC와 비트맵 연결하기
		Rectangle(mDC, 0, 0, rt.right, rt.bottom); //--- 화면에 비어있기 때문에 화면 가득히 사각형을 그려 배경색으로 설정하기


		draw_block(mDC);
		draw_wall(mDC);
		draw_enemy(mDC);
		draw_bullet(mDC);
		draw_player(mDC, bullet_index, death_aside);

		print_status(mDC);
		print_level(mDC, level);


		//--- 마지막에 메모리 DC의 내용을 화면 DC로 복사한다.
		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC); //--- 생성한 메모리 DC 삭제
		DeleteObject(hBitmap); //--- 생성한 비트맵 삭제

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		KillTimer(hWnd, 6);
		KillTimer(hWnd, 7);
		KillTimer(hWnd, 8);
		KillTimer(hWnd, 9);
		PlaySound(NULL, 0, 0);
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



void Initialize()
{
	score = 0;
	total_time = 0;

	player.hp = 1;
	player.life = 3;
	player.x = 720;
	player.y = 360;

	float hitbox_x = player.x - player.aside;
	float hitbox_y = player.y - player.aside;
	float hitbox_endx = player.x + player.aside * 2;
	float hitbox_endy = player.y + player.aside * 2;

	for (int i = 0; i < board_y_max; ++i) {
		for (int j = 0; j < board_x_max; ++j) {
			block[i][j].x = j * block[i][j].aside;
			block[i][j].y = i * block[i][j].aside;
			if (hitbox_x < block[i][j].x + block[i][j].aside && hitbox_y < block[i][j].y + block[i][j].aside
				&& hitbox_endx > block[i][j].x && hitbox_endy > block[i][j].y) {
				block[i][j].type = ROAD;
			}
			else block[i][j].block_initialize();
			block[i][j].block_adjust();
		}
	}

	for (int i = 0; i < wall_num; ++i) {
		wall[i].wall_initialize();
		wall[i].block_adjust();
	}

	for (int i = 0; i < bullet_num; ++i) {
		bullet[i].bullet_initialize();
	}

	for (int i = 0; i < enemy_num; ++i) {
		enemy[i].hp = 0;
		enemy[i].deatheffect = 0;
	}
}

float lerp(float p1, float p2, float d1)
{
	float result;
	result = p1 + d1 * (p2 - p1);
	return result;
}

void shoot_bullet(int& bullet_index) {
	if (bullet_index == bullet_num) return;
	bullet[bullet_index].x = player.x + player.aside / 2;
	bullet[bullet_index].y = player.y + player.aside / 2;
	bullet[bullet_index].dir = player.bulletdir;
	bullet_index++;
}

void player_update(int& death_effectcnt) {
	for (int i = 0; i < board_y_max; ++i) {
		for (int j = 0; j < board_x_max; ++j) {
			// 회색 블록 과 충돌했을 때
			if (block[i][j].type == NMOVEROAD) {
				if (block[i][j].x < player.x + player.aside && block[i][j].y < player.y + player.aside
					&& block[i][j].x + block[i][j].aside > player.x && block[i][j].y + block[i][j].aside > player.y) {
					switch (player.playerdir) {
					case UP:
						player.y += 15;
						break;
					case LEFT:
						player.x += 15;
						break;
					case DOWN:
						player.y -= 15;
						break;
					case RIGHT:
						player.x -= 15;
						break;
					}
				}
			}
		}
	}

	// 벽과 충돌했을 때
	for (int i = 0; i < wall_num; ++i) {
		if (wall[i].type == WALL) {
			if (wall[i].x < player.x + player.aside && wall[i].y < player.y + player.aside
				&& wall[i].x + wall[i].aside > player.x && wall[i].y + wall[i].aside > player.y) {
				switch (player.playerdir) {
				case UP:
					player.y += 15;
					break;
				case LEFT:
					player.x += 15;
					break;
				case DOWN:
					player.y -= 15;
					break;
				case RIGHT:
					player.x -= 15;
					break;
				}
			}
		}
	}

	// 적과 충돌했을 때
	for (int i = 0; i < enemy_num; ++i) {
		if (player.condition == NODAMAGE) continue;
		if (enemy[i].hp < 1) continue;
		if (enemy[i].x < player.x + player.aside && enemy[i].y < player.y + player.aside
			&& enemy[i].x + enemy[i].aside > player.x && enemy[i].y + enemy[i].aside > player.y) {
			death_effectcnt = 0;
			--enemy[i].hp;
			--player.hp;
			--player.life;
		}
	}
}

void bullet_update() {
	for (int k = 0; k < bullet_num; ++k) {
		for (int i = 0; i < board_y_max; ++i) {
			for (int j = 0; j < board_x_max; ++j) {
				// 총알이 회색 블럭과 충돌했을 때
				if (block[i][j].type == NMOVEROAD) {
					if (block[i][j].x - bullet[k].aside < bullet[k].x && block[i][j].y - bullet[k].aside < bullet[k].y
						&& block[i][j].x + block[i][j].aside + bullet[k].aside > bullet[k].x
						&& block[i][j].y + block[i][j].aside + bullet[k].aside > bullet[k].y) {
						block[i][j].type = ROAD;
						block[i][j].block_adjust();
					}
				}
			}
		}

		// 총알이 적과 충돌했을 때
		for (int i = 0; i < enemy_num; ++i) {
			if (enemy[i].hp < 1) continue;
			if (enemy[i].x - bullet[k].aside < bullet[k].x && enemy[i].y - bullet[k].aside < bullet[k].y
				&& enemy[i].x + enemy[i].aside + bullet[k].aside > bullet[k].x
				&& enemy[i].y + enemy[i].aside + bullet[k].aside > bullet[k].y) {
				--bullet[k].hp;
				bullet[k].bullet_deleted();

				float hitbox_x = enemy[i].x - enemy[i].aside;
				float hitbox_y = enemy[i].y - enemy[i].aside;
				float hitbox_endx = enemy[i].x + enemy[i].aside;
				float hitbox_endy = enemy[i].y + enemy[i].aside;

				for (int k = 0; k < board_y_max; ++k) {
					for (int j = 0; j < board_x_max; ++j) {
						if (hitbox_x < block[k][j].x + block[k][j].aside && hitbox_y < block[k][j].y + block[k][j].aside
							&& hitbox_endx > block[k][j].x && hitbox_endy > block[k][j].y) {
							block[k][j].type = ROAD;
							block[k][j].block_adjust();
						}
					}
				}

				score += 100;
				enemy[i].deatheffect = 5;
				--enemy[i].hp;
				enemy[i].enemy_deleted();
				++combo;
			}
		}

		// 총알이 파란색 벽과 충돌했을 때
		for (int i = 0; i < wall_num; ++i) {
			if (wall[i].type == WALL) {
				if (wall[i].x - bullet[k].aside < bullet[k].x && wall[i].y - bullet[k].aside < bullet[k].y
					&& wall[i].x + wall[i].aside + bullet[k].aside > bullet[k].x
					&& wall[i].y + wall[i].aside + bullet[k].aside > bullet[k].y) {
					--bullet[k].hp;
					bullet[k].bullet_deleted();
				}
			}
		}
	}
}

void enemy_update() {
	for (int k = 0; k < enemy_num; ++k) {
		if (enemy[k].hp < 1) continue;
		for (int i = 0; i < board_y_max; ++i) {
			for (int j = 0; j < board_x_max; ++j) {
				if (enemy[k].x < block[i][j].x + block[i][j].aside && enemy[k].y < block[i][j].y + block[i][j].aside
					&& enemy[k].x + enemy[k].aside > block[i][j].x && enemy[k].y + enemy[k].aside > block[i][j].y) {
					if (block[i][j].type == ROAD) {
						block[i][j].type = NMOVEROAD;
						block[i][j].block_adjust();
					}
				}
			
			}
		}
	}
}

void draw_player(HDC mDC, const int bullet_index, int death_aside) {
	if (player.hp < 1) {
		for (int i = 0; i < bullet_num; ++i) {
			draw_circle_bymid(mDC, player.mini_x[i], player.mini_y[i], death_aside, RGB(255, 255, 255));
		}
		return;
	}

	if(player.condition == NODAMAGE) draw_rectangle(mDC, player.x, player.y, player.x + player.aside, player.y + player.aside, RGB(0, 255, 0));
	else draw_rectangle(mDC, player.x, player.y, player.x + player.aside, player.y + player.aside, player.color);

	for (int i = 0; i < bullet_num; ++i) {
		if (bullet_index > i) continue;
		draw_circle_bymid(mDC, player.mini_x[i], player.mini_y[i], mini_aside, RGB(255, 255, 255));
	}
}

void draw_block(HDC mDC) {
	for (int i = 0; i < board_y_max; ++i) {
		for (int j = 0; j < board_x_max; ++j) {
			draw_rectangle(mDC, block[i][j].x, block[i][j].y, block[i][j].x + block[i][j].aside, block[i][j].y + block[i][j].aside, block[i][j].color);
		}
	}
}

void draw_wall(HDC mDC) {
	for (int i = 0; i < wall_num; ++i) {
		draw_rectangle(mDC, wall[i].x, wall[i].y, wall[i].x + wall[i].aside, wall[i].y + wall[i].aside, wall[i].color);
	}
}

void draw_bullet(HDC mDC) {
	for (int i = 0; i < bullet_num; ++i) {
		if (bullet[i].hp <= 0) continue;
		draw_circle_bymid(mDC, bullet[i].x, bullet[i].y, bullet[i].aside, RGB(255, 255, 255));
		
		switch (bullet[i].dir) {
		case DOWN:
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y - 10, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y - 20, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y - 30, bullet[i].aside - 2, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y - 40, bullet[i].aside - 3, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y - 50, bullet[i].aside - 3, RGB(255, 255, 255));
			break;
		case RIGHT:
			draw_circle_bymid(mDC, bullet[i].x - 10, bullet[i].y, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x - 20, bullet[i].y, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x - 30, bullet[i].y, bullet[i].aside - 2, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x - 40, bullet[i].y, bullet[i].aside - 3, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x - 50, bullet[i].y, bullet[i].aside - 3, RGB(255, 255, 255));
			break;
		case UP:
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y + 10, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y + 20, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y + 30, bullet[i].aside - 2, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y + 40, bullet[i].aside - 3, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x, bullet[i].y + 50, bullet[i].aside - 3, RGB(255, 255, 255));
			break;
		case LEFT:
			draw_circle_bymid(mDC, bullet[i].x + 10, bullet[i].y, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x + 20, bullet[i].y, bullet[i].aside - 1, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x + 30, bullet[i].y, bullet[i].aside - 2, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x + 40, bullet[i].y, bullet[i].aside - 3, RGB(255, 255, 255));
			draw_circle_bymid(mDC, bullet[i].x + 50, bullet[i].y, bullet[i].aside - 3, RGB(255, 255, 255));
			break;
		}
	}
}

void draw_enemy(HDC mDC) {
	for (int i = 0; i < enemy_num; ++i) {
		if (enemy[i].hp > 0) draw_rectangle(mDC, enemy[i].x, enemy[i].y, enemy[i].x + enemy[i].aside, enemy[i].y + enemy[i].aside, RGB(255, 0, 0));

		if (enemy[i].deatheffect != 0) {
			float midx = enemy[i].x + enemy[i].aside / 2;
			float midy = enemy[i].y + enemy[i].aside / 2;
			draw_circle_bymid(mDC, midx, midy, enemy[i].deathaside, RGB(255, 0, 0));
		}
	}

	for (int i = 0; i < enemy_num; ++i) {
		if (enemy[i].hp <= 0) continue;
		float hitbox_x = enemy[i].x - enemy[i].aside;
		float hitbox_y = enemy[i].y - enemy[i].aside;
		float hitbox_endx = enemy[i].x + enemy[i].aside;
		float hitbox_endy = enemy[i].y + enemy[i].aside;

		for (int k = 0; k < board_y_max; ++k) {
			for (int j = 0; j < board_x_max; ++j) {
				if (hitbox_x < block[k][j].x + block[k][j].aside && hitbox_y < block[k][j].y + block[k][j].aside
					&& hitbox_endx > block[k][j].x && hitbox_endy > block[k][j].y) {
					draw_framerectangle(mDC, block[k][j].x, block[k][j].y, block[k][j].x + block[k][j].aside, block[k][j].y + block[k][j].aside, RGB(255, 0, 0));
				}
			}
		}
	}
}

void print_status(HDC mDC) {
	TCHAR temp[80]{};
	wsprintf(temp, TEXT("생명: %d개 | 시간: %d초 | 점수: %d"), player.life, total_time, score);
	TextOut(mDC, 620, 40, temp, lstrlen(temp));
}

void print_level(HDC mDC, int level) {
	TCHAR temp[80]{};

	switch (level) {
	case Lv_HARD:
		wsprintf(temp, TEXT("난이도: 어려움"));
		break;
	case Lv_NORMAL:
		wsprintf(temp, TEXT("난이도: 중간"));
		break;
	case Lv_EASY:
		wsprintf(temp, TEXT("난이도: 쉬움"));
		break;
	case Lv_NODAMAGE:
		wsprintf(temp, TEXT("난이도: 무적"));
		break;
	}

	TextOut(mDC, 620, 60, temp, lstrlen(temp));
}

void draw_rectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Rectangle(mDC, x1, y1, x2, y2);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void draw_framerectangle(HDC mDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	RECT rt{ x1, y1, x2, y2 };
	FrameRect(mDC, &rt, hBrush);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}

void draw_circle_bymid(HDC mDC, int x1, int y1, int aside, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color); // GDI: 브러시 만들기
	HBRUSH oldBrush = (HBRUSH)SelectObject(mDC, hBrush); // 새로운 브러시 선택하기
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(mDC, hPen);

	Ellipse(mDC, x1 - aside, y1 - aside, x1 + aside, y1 + aside);

	hBrush = (HBRUSH)SelectObject(mDC, oldBrush); // 새로운 펜 선택하기
	DeleteObject(hBrush);
	hPen = (HPEN)SelectObject(mDC, oldPen);
	DeleteObject(hPen);
}