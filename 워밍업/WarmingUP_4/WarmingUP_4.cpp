// ���־�4. [����ü ����ϱ�] �ؽ�Ʈ�� ����Ͽ� 2�� �� �̵��ϱ�
#include <iostream>
#include <random>
#include <windows.h>

using namespace std;


const int x_max{ 10 };
const int y_max{ 10 };

class Go {
private:
	int x{0};
	int y{0};
	char shape{'o'};
	

public:
	bool turn{ true };
	
	Go(int xgo, int ygo);
	~Go();

	int Go_x() const;
	int Go_y() const;
	char Go_shape() const;

	void Go_move_right();
	void Go_move_left();
	void Go_move_up();
	void Go_move_down();

	void shape_change(char);
	void go_rand_loc();
};

Go::Go(int xgo, int ygo) {
	x = xgo;
	y = ygo;
	turn = true;
	switch (rand() % 5 + 1) {
	case 1:
		shape = 'o';
		break;
	case 2:
		shape = 'x';
		break;
	case 3:
		shape = '#';
		break;
	case 4:
		shape = '@';
		break;
	case 5:
		shape = '%';
		break;
	}
}

Go::~Go() {
	
}

int Go::Go_x() const { return x; }
int Go::Go_y() const { return y; }
char Go::Go_shape() const { return shape; }

void Go::Go_move_right() {
	if (x < x_max - 1) x++;
	else if (x == x_max - 1) x = 0;
}

void Go::Go_move_left() {
	if (x > 0) x--;
	else if (x == 0) x = x_max - 1;
}

void Go::Go_move_up() {
	if (y > 0) y--;
	else if (y == 0) y = y_max - 1;
}

void Go::Go_move_down() {
	if (y < y_max - 1) y++;
	else if (y == y_max - 1) y = 0;
}


void Go::shape_change(char a) {
	shape = a;
}

void Go::go_rand_loc() {
	x = rand() % x_max - 1;
	y = rand() % x_max - 1;
}

void sheet_clear(char sheet[][10]);
void sheet_print(char sheet[][10]);
void check_shape(Go &go1, Go &go2);

int main() {
	char go_sheet[10][10]{};
	Go go1( 0, 0 );
	Go go2(5, 4);
	go2.turn = false;

	// �ٵ��� �����
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			go_sheet[i][j] = '+';
		}
	}

	go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();		// go1 �� ��ġ �ٵ��ǿ� �Է�
	go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();		// go2 �� ��ġ �ٵ��ǿ� �Է�

	// ���
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			cout << go_sheet[i][j] << " ";
		}
		cout << endl;
	}

	char input{};

	while (true) {
		cin >> input;
		if (go1.turn && !go2.turn) {
			switch (input) {
			case 'd':
				go1.Go_move_right();
				if (go1.Go_x() == 0) check_shape(go1, go2);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					check_shape(go2, go1);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = false;
				go2.turn = true;
				sheet_print(go_sheet);
				break;
			case 'a':
				go1.Go_move_left();
				if (go1.Go_x() == x_max - 1) check_shape(go1, go2);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					check_shape(go2, go1);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = false;
				go2.turn = true;
				sheet_print(go_sheet);
				break;
			case 'w':
				go1.Go_move_up();
				if (go1.Go_y() == y_max - 1) check_shape(go1, go2);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					check_shape(go2, go1);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = false;
				go2.turn = true;
				sheet_print(go_sheet);
				break;
			case 's':
				go1.Go_move_down();
				if (go1.Go_y() == 0) check_shape(go1, go2);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					check_shape(go2, go1);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = false;
				go2.turn = true;
				sheet_print(go_sheet);
				break;
			case 'j':
			case 'k':
			case 'l':
			case 'i':
				cout << "���� �����Դϴ�" << endl;
				break;
				// ���α׷� ����
			case'r':
				sheet_clear(go_sheet);
				go1.go_rand_loc();
				go2.go_rand_loc();
				check_shape(go1, go2);
				check_shape(go2, go1);
				go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
				go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case'q':
				exit(true);
			}
		}
		else if (!go1.turn && go2.turn) {
			switch (input) {
			case 'l':
				go2.Go_move_right();
				if (go2.Go_x() == 0) check_shape(go2, go1);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
					check_shape(go1, go2);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case 'j':
				go2.Go_move_left();
				if (go2.Go_x() == x_max - 1) check_shape(go2, go1);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
					check_shape(go1, go2);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case 'i':
				go2.Go_move_up();
				if (go2.Go_y() == y_max - 1) check_shape(go2, go1);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
					check_shape(go1, go2);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case 'k':
				go2.Go_move_down();
				if (go2.Go_y() == 0) check_shape(go2, go1);
				if (go1.Go_x() == go2.Go_x() && go1.Go_y() == go2.Go_y()) {
					Beep(1500, 300);
					sheet_clear(go_sheet);
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
					check_shape(go1, go2);
				}
				else {
					sheet_clear(go_sheet);
					go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
					go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				}
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case 'a':
			case 's':
			case 'd':
			case 'w':
				cout << "���� �����Դϴ�" << endl;
				break;
			// ���α׷� ����
			case'r':
				sheet_clear(go_sheet);
				go1.go_rand_loc();
				go2.go_rand_loc();
				check_shape(go1, go2);
				check_shape(go2, go1);
				go_sheet[go1.Go_y()][go1.Go_x()] = go1.Go_shape();
				go_sheet[go2.Go_y()][go2.Go_x()] = go2.Go_shape();
				go1.turn = true;
				go2.turn = false;
				sheet_print(go_sheet);
				break;
			case'q':
				exit(true);
			}
		}

	}

	return 0;
}

// �ٵ��� �ʱ�ȭ�ϱ�
void sheet_clear(char sheet[][10]) {
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			sheet[i][j] = '+';
		}
	}
}

// ���
void sheet_print(char sheet[][10]) {
	for (int i = 0; i < y_max; ++i) {
		for (int j = 0; j < x_max; ++j) {
			cout << sheet[i][j] << " ";
		}
		cout << endl;
	}
}

// ���üũ�ϱ�
void check_shape(Go &go1, Go &go2) {
	char a = go1.Go_shape(); //1��
	char b = go2.Go_shape(); //2��
	char temp = a;
	switch (rand() % 5 + 1) {
	case 1:
		a = 'o';
		break;
	case 2:
		a = 'x';
		break;
	case 3:
		a = '#';
		break;
	case 4:
		a = '@';
		break;
	case 5:
		a = '%';
		break;
	}
	if (a == b) check_shape(go1, go2);
	else if (a == temp) check_shape(go1, go2);
	else go1.shape_change(a);
}