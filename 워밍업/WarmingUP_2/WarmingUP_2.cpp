// ���־�2. [1���� �迭 ����ϱ�] ���� �ٷ��
#include <iostream>
#include <random>

using namespace std;

int main() 
{
	const int size{50};
	int random_number[size]{};
	int origin_number[size]{};
	int input_number{};

	// ���� �Է¹ޱ�
	while (true) {
		cout << "Input number: ";
		cin >> input_number;

		if (input_number > 100) break;
		else cout << "100���� ū ���� �Է��ϼ���" << endl;
	}

	// �Է¹��� ���ں��� ���� ������ �� 50�� ����
	for (int i = 0; i < size; ++i) {
		random_number[i] = (rand() % input_number) + 1;

		// �ߺ�üũ
		for (int j = 0; j < i; ++j) {
			if (random_number[i] == random_number[j]) i--;
		}
	}

	// �ʱ⿡ ������ ���� �� ����
	for (int i = 0; i < size; ++i) {
		origin_number[i] = random_number[i];
	}
	
	// ���
	cout << "Generated numbers: ";
	for (int i = 0; i < size; ++i) {
		cout << random_number[i] << " ";
	}
	cout << endl;

	char menu{};
	int sum{ 0 };

	while (true) {
		cout << "Command: ";
		cin >> menu;

		switch (menu) {
		// �������� ����
		case 'a':
			for (int i = 0; i < size - 1; ++i) {
				for (int j = 0; j < size - 1 - i; ++j) {
					if (random_number[j] > random_number[j + 1]) {
						int temp{ random_number[j + 1] };
						random_number[j + 1] = random_number[j];
						random_number[j] = temp;
					}
				}
			}
			// ���
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// �������� ����
		case 'd':
			for (int i = 0; i < size - 1; ++i) {
				for (int j = 0; j < size - 1 - i; ++j) {
					if (random_number[j] < random_number[j + 1]) {
						int temp{ random_number[j + 1] };
						random_number[j + 1] = random_number[j];
						random_number[j] = temp;
					}
				}
			}
			// ���
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// 3�� ��� ����ϰ� 3�� ����� ��� ���� ���� ����Ѵ�.
		case 'e':
			for (int i = 0; i < size; ++i) {
				if ( random_number[i] % 3  == 0) {
					sum += random_number[i];
					cout << random_number[i] << " ";
				}
			}
			// ���
			cout << endl;
			cout << "3�� ����� ������: " << sum << endl;
			sum = 0;
			break;
		// 5�� ��� ����ϰ� 3�� ����� ��� ���� ���� ����Ѵ�.
		case 'f':
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 5 == 0) {
					sum += random_number[i];
					cout << random_number[i] << " ";
				}
			}
			// ���
			cout << endl;
			cout << "5�� ����� ������: " << sum << endl;
			sum = 0;
			break;
		// 3�� ��� �̰ų� 5�� ����� ���ڸ� ����ϰ� �� ���ڿ� 1�� ���� ���ڵ� ����Ѵ�.
		case 'm':
			// 3�� ��� �̰ų� 5�� ����� ���� ���
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 || random_number[i] % 5 == 0) {
					cout << random_number[i] << " ";
				}
			}
			cout << endl;
			// �� ���ڿ� 1�� ���� ���� ���
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 || random_number[i] % 5 == 0) {
					cout << random_number[i] + 1 << " ";
				}
			}
			cout << endl;
			break;
		// 3�� ��� �̰� 5�� ����� ���ڸ� ����ϰ� �� ���ڿ� 1�� �� ���ڵ� ����Ѵ�.
		case 'n':
			// 3�� ��� �̰� 5�� ����� ���� ���
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 && random_number[i] % 5 == 0) {
					cout << random_number[i] << " ";
				}
			}
			cout << endl;
			// �� ���ڿ� 1�� �� ���� ���
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 && random_number[i] % 5 == 0) {
					cout << random_number[i] - 1 << " ";
				}
			}
			cout << endl;
			break;
		// �ٽ� ������
		case 'r':
			cout << "Origin numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << origin_number[i] << " ";
			}
			cout << endl;
			break;
		// �ٽ� ���ڸ� �Է¹ް� �� ���ں��� ū ���� ���� 50�� ����� ����ϱ�
		case 'p':
			// ���� �Է¹ޱ�
			while (true) {
				cout << "Input number: ";
				cin >> input_number;

				if (input_number > 100) break;
				else cout << "100���� ū ���� �Է��ϼ���" << endl;
			}
			// �Է¹��� ���ں��� ū ������ �� 50�� ����
			for (int i = 0; i < size; ++i) {
				random_number[i] = (rand() % input_number) + input_number + 1;

				// �ߺ�üũ
				for (int j = 0; j < i; ++j) {
					if (random_number[i] == random_number[j]) i--;
				}
			}
			// ���
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// ���α׷� ����
		case 'q':
			exit(true);

		}
	
	}

	return 0;
}