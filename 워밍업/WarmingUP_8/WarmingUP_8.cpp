// 워밍업8. 문자 기반의 게임 만들기
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;


class Yoot {
private:
	int x{ 0 };
	int y{ 0 };
	char shape{};

public:
	bool turn{ true };

	Yoot() {};
	Yoot(int yootx, int yooty, char s);
	~Yoot() {};

	int get_x() const { return x; };
	int get_y() const { return y; };
	char get_shape() const { return shape; };

	void go_right();
	void go_left();
	void go_up();
	void go_down();

	void go_z();
	void go_c();
};

Yoot::Yoot(int yootx, int yooty, char s) : x(yootx), y(yooty), shape(s) { }

void Yoot::go_right() {
	if (y == 6 && x == 2) x += 2;
	else if (y == 6) x++;
}

void Yoot::go_left() {
	if (y == 0 && x == 4) x -= 2;
	else if (y == 0) x--;
}

void Yoot::go_up() {
	if (x == 6 && y == 4) y -= 2;
	else if (x == 6) y--;
}

void Yoot::go_down() {
	if (x == 0 && y == 2) y += 2;
	else if (x == 0) y++;
}

void Yoot::go_z() {
	if (x + y == 6) {
		x--;
		y++;
	}
}

void Yoot::go_c() {
	if (x == y) {
		x++;
		y++;
	}
}



const int x_max{ 7 };
const int y_max{ 7 };

void sheet_clear(char sheet[][x_max]);
void sheet_print(char sheet[][x_max]);

void move_up(Yoot& y);
void move_down(Yoot& y);
void move_right(Yoot& y);
void move_left(Yoot& y);
void move_z(Yoot& y);
void move_c(Yoot& y);

void roll_yoot(string& y);


int main()
{
	string four_yoot[4]{};
	char yoot_sheet[y_max][x_max]{};
	Yoot y1(6, 6, 'o');
	Yoot y2(6, 6, 'x');
	y2.turn = false;
	int back_cnt{ 0 };

	cout << "게임을 시작하려면 p 버튼을 눌러주세요.";


	char input{};
	
	while (true) {
		cin >> input;

		switch (input) {
		case 'p': {
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			sheet_print(yoot_sheet);

			break;
		}
		case '1': {
			for (int i = 0; i < 4; ++i) roll_yoot(four_yoot[i]);
			back_cnt = 0;
			for (int i = 0; i < 4; ++i) {
				if (four_yoot[i] == "뒤") back_cnt++;
				cout << four_yoot[i] << "\t";
			}
			switch (back_cnt) {
			case 0: {
				cout << "모";
				break;
			}
			case 1: {
				cout << "도";
				break;
			}
			case 2: {
				cout << "개";
				break;
			}
			case 3: {
				cout << "걸";
				break;
			}
			case 4: {
				cout << "윷";
				break;
			}
			}
			break;
		}
		case '2': {
			for (int i = 0; i < 4; ++i) roll_yoot(four_yoot[i]);
			back_cnt = 0;
			for (int i = 0; i < 4; ++i) {
				if (four_yoot[i] == "뒤") back_cnt++;
				cout << four_yoot[i] << "\t";
			}
			switch (back_cnt) {
			case 0: {
				cout << "모";
				break;
			}
			case 1: {
				cout << "도";
				break;
			}
			case 2: {
				cout << "개";
				break;
			}
			case 3: {
				cout << "걸";
				break;
			}
			case 4: {
				cout << "윷";
				break;
			}
			}
			break;
		}
		case 'w': {
			if (y1.get_y() == 0) break;
			move_up(y1);
			move_up(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 's': {
			if (y1.get_y() == y_max) break;
			move_down(y1);
			move_down(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 'd': {
			if (y1.get_x() == x_max) break;
			move_right(y1);
			move_right(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 'a': {
			if (y1.get_x() == 0) break;
			move_left(y1);
			move_left(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 'z': {
			if (y1.get_y() == y_max) break;
			move_z(y1);
			move_z(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 'c': {
			if (y1.get_y() == y_max) break;
			move_c(y1);
			move_c(y2);
			system("cls");
			sheet_clear(yoot_sheet);
			yoot_sheet[y1.get_y()][y1.get_x()] = y1.get_shape();
			yoot_sheet[y2.get_y()][y2.get_x()] = y2.get_shape();
			sheet_print(yoot_sheet);
			break;
		}
		case 't': {
			back_cnt = 0;
			if (y1.turn == true) {
				y1.turn = false;
				y2.turn = true;
				cout << "2p 의 차례 입니다." << endl;
			}
			else if (y2.turn == true) {
				y1.turn = true;
				y2.turn = false;
				cout << "1p 의 차례 입니다." << endl;
			}
			break;
		}

		case '0': {
			exit(true);
		}

		}


	}


	return 0;
}

// 바둑판 초기화하기
void sheet_clear(char sheet[][x_max]) {
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			sheet[i][j] = '+';
		}
	}
	sheet[0][3] = ' ';		// 2번씩 이동해야 하는 포인트
	sheet[1][2] = ' ';
	sheet[1][3] = ' ';
	sheet[1][4] = ' ';
	sheet[2][1] = ' ';
	sheet[2][3] = ' ';
	sheet[2][5] = ' ';
	sheet[3][0] = ' ';		// 2번씩 이동해야 하는 포인트
	sheet[3][1] = ' ';
	sheet[3][2] = ' ';
	sheet[3][4] = ' ';
	sheet[3][5] = ' ';
	sheet[3][6] = ' ';		// 2번씩 이동해야 하는 포인트
	sheet[4][1] = ' ';
	sheet[4][3] = ' ';
	sheet[4][5] = ' ';
	sheet[5][2] = ' ';
	sheet[5][3] = ' ';
	sheet[5][4] = ' ';
	sheet[6][3] = ' ';		// 2번씩 이동해야 하는 포인트
}

// 윷 판 출력
void sheet_print(char sheet[][x_max]) {
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			cout << sheet[i][j] << " ";
		}
		cout << endl;
	}
}

// 말을 위로 이동하기
void move_up(Yoot &y) {
	if (y.turn == false) return;
	else y.go_up();
}

// 말을 아래로 이동하기
void move_down(Yoot& y) {
	if (y.turn == false) return;
	else y.go_down();
}

// 말을 오른쪽으로 이동하기
void move_right(Yoot& y) {
	if (y.turn == false) return;
	else y.go_right();
}

// 말을 왼쪽으로 이동하기
void move_left(Yoot& y) {
	if (y.turn == false) return;
	else y.go_left();
}

// 말을 좌측 하단으로 대각선 이동하기
void move_z(Yoot& y) {
	if (y.turn == false) return;
	else y.go_z();
}

// 말을 우측 하단으로 대각선 이동하기
void move_c(Yoot& y) {
	if (y.turn == false) return;
	else y.go_c();
}

// 윷 굴리기
void roll_yoot(string& y) {
	srand(static_cast<int>(time(NULL)));
	switch (rand() % 2) {
	case 0: {
		y = "앞";
		break;
	}
	case 1:
		y = "뒤";
		break;
	}
}
