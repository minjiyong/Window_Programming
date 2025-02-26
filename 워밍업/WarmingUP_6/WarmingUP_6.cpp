// 워밍업6. [함수 사용하기] 계산 순위 정하여 정해진 순위 따라 연산하기
#include <iostream>
#include <random>

using namespace std;


// 연산자를 판별하기 위한 함수
int is_operator(char c) {
	if (c == '+') return 43;
	else if (c == '-') return 45;
	else if (c == '*') return 42;
	else if (c == '/') return 47;
}

// 두 숫자를 주어진 연산자로 계산하는 함수
double apply_operator(double a, double b, char op) {
	switch (op) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0.0;
	}
};

// 연산자 우선순위를 반환하는 함수
int precedence(char op) {
	if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0; // 유효하지 않은 연산자인 경우
};


int main() 
{
	int number[5]{};
	char oper[4]{};

	// 숫자 5개와 연산자 4개를 랜덤하게 설정
	for (int i = 0; i < 5; ++i) number[i] = rand() % 8 + 1;
	for (int i = 0; i < 4; ++i) {
		switch (rand() % 4 + 1) {
		case 1: oper[i] = '+'; break;
		case 2: oper[i] = '-'; break;
		case 3: oper[i] = '*'; break;
		case 4: oper[i] = '/'; break;
		}
	}

	cout << "Numbers to calculate: ";
	for (int i = 0; i < 4; ++i) {
		cout << number[i] << " " << oper[i] << " ";
	}
	cout << number[4] << endl;

	char input{};
	char cal_sentence[9]{};
	double result{ 0 };

	while (true) {
		cout << "Input the calculating order: ";
		cin >> input;
		switch (input) {
		case '1': 
		{
			int record{ 0 };
			for (int i = 0; i < 4; ++i) {
				if (precedence(oper[i]) == 2) {
					if (result == 0) result = apply_operator(number[i], number[i + 1], oper[i]);
					else if(result != 0) result = apply_operator(result, number[i + 1], oper[i]);	
				}
			}
			for (int i = 0; i < 4; ++i) {
				if (precedence(oper[i]) == 1) {
					if (i != 0) result = apply_operator(result, number[i + 1], oper[i]);
					else if (i == 0) result = apply_operator(number[i], result, oper[i]);
				}
			}

			cout << "연산자 우선순위대로 계산하면: " << result << endl;

			result = 0;
			break;
		}
		case '2': 
			// 앞에서부터 순서대로 연산
		{
			for (int i = 0; i < 4; ++i) {
				if (oper[i] == '+') {
					if(i == 0) result = number[i] + number[i + 1];
					else if(i != 0) result += number[i + 1];
				}
				else if (oper[i] == '-') {
					if(i == 0)result = number[i] - number[i + 1];
					else if (i != 0) result -= number[i + 1];
				}
				else if (oper[i] == '*') {
					if (i == 0) result = number[i] * number[i + 1];
					else if (i != 0) result *= number[i + 1];
				}
				else if (oper[i] == '/') {
					if (i == 0) result = number[i] / number[i + 1];
					else if (i != 0) result /= number[i + 1];
				}
			}
			cout << "순서대로 계산하면: " << result << endl;

			result = 0;
			break;
		}
		case '3': 
			// 뒤에서부터 순서대로 연산
		{
			for (int i = 3; i >= 0; --i) {
				if (oper[i] == '+') {
					if (i == 3) result = number[i] + number[i + 1];
					else if (i != 3) result += number[i];
				}
				else if (oper[i] == '-') {
					if (i == 3)result = number[i] - number[i + 1];
					else if (i != 3) result -= number[i];
				}
				else if (oper[i] == '*') {
					if (i == 3) result = number[i] * number[i + 1];
					else if (i != 3) result *= number[i];
				}
				else if (oper[i] == '/') {
					if (i == 3) result = number[i] / number[i + 1];
					else if (i != 3) result /= number[i];
				}
			}
			cout << "역순으로 계산하면: " << result << endl;

			result = 0;
			break;
		}
		case '4': 
		{
			// 숫자 5개와 연산자 4개를 다시 랜덤하게 설정
			for (int i = 0; i < 5; ++i) number[i] = rand() % 8 + 1;
			for (int i = 0; i < 4; ++i) {
				switch (rand() % 4 + 1) {
				case 1: oper[i] = '+'; break;
				case 2: oper[i] = '-'; break;
				case 3: oper[i] = '*'; break;
				case 4: oper[i] = '/'; break;
				}
			}

			cout << "Numbers to calculate: ";
			for (int i = 0; i < 4; ++i) {
				cout << number[i] << " " << oper[i] << " ";
			}
			cout << number[4] << endl;

			cout << "숫자와 연산자를 랜덤하게 다시 설정했습니다." << endl;

			result = 0;
			break;
		}
		case 'q': 
		{
			exit(true);
		}


		}



	}


	return 0;
}