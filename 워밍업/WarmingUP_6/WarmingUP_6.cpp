// ���־�6. [�Լ� ����ϱ�] ��� ���� ���Ͽ� ������ ���� ���� �����ϱ�
#include <iostream>
#include <random>

using namespace std;


// �����ڸ� �Ǻ��ϱ� ���� �Լ�
int is_operator(char c) {
	if (c == '+') return 43;
	else if (c == '-') return 45;
	else if (c == '*') return 42;
	else if (c == '/') return 47;
}

// �� ���ڸ� �־��� �����ڷ� ����ϴ� �Լ�
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

// ������ �켱������ ��ȯ�ϴ� �Լ�
int precedence(char op) {
	if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0; // ��ȿ���� ���� �������� ���
};


int main() 
{
	int number[5]{};
	char oper[4]{};

	// ���� 5���� ������ 4���� �����ϰ� ����
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

			cout << "������ �켱������� ����ϸ�: " << result << endl;

			result = 0;
			break;
		}
		case '2': 
			// �տ������� ������� ����
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
			cout << "������� ����ϸ�: " << result << endl;

			result = 0;
			break;
		}
		case '3': 
			// �ڿ������� ������� ����
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
			cout << "�������� ����ϸ�: " << result << endl;

			result = 0;
			break;
		}
		case '4': 
		{
			// ���� 5���� ������ 4���� �ٽ� �����ϰ� ����
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

			cout << "���ڿ� �����ڸ� �����ϰ� �ٽ� �����߽��ϴ�." << endl;

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