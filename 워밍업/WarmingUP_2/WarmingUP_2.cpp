// 워밍업2. [1차원 배열 사용하기] 숫자 다루기
#include <iostream>
#include <random>

using namespace std;

int main() 
{
	const int size{50};
	int random_number[size]{};
	int origin_number[size]{};
	int input_number{};

	// 숫자 입력받기
	while (true) {
		cout << "Input number: ";
		cin >> input_number;

		if (input_number > 100) break;
		else cout << "100보다 큰 수를 입력하세요" << endl;
	}

	// 입력받은 숫자보다 작은 랜덤한 수 50개 생성
	for (int i = 0; i < size; ++i) {
		random_number[i] = (rand() % input_number) + 1;

		// 중복체크
		for (int j = 0; j < i; ++j) {
			if (random_number[i] == random_number[j]) i--;
		}
	}

	// 초기에 생성한 랜덤 수 저장
	for (int i = 0; i < size; ++i) {
		origin_number[i] = random_number[i];
	}
	
	// 출력
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
		// 오름차순 정렬
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
			// 출력
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// 내림차순 정렬
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
			// 출력
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// 3의 배수 출력하고 3의 배수를 모두 더한 값도 출력한다.
		case 'e':
			for (int i = 0; i < size; ++i) {
				if ( random_number[i] % 3  == 0) {
					sum += random_number[i];
					cout << random_number[i] << " ";
				}
			}
			// 출력
			cout << endl;
			cout << "3의 배수의 총합은: " << sum << endl;
			sum = 0;
			break;
		// 5의 배수 출력하고 3의 배수를 모두 더한 값도 출력한다.
		case 'f':
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 5 == 0) {
					sum += random_number[i];
					cout << random_number[i] << " ";
				}
			}
			// 출력
			cout << endl;
			cout << "5의 배수의 총합은: " << sum << endl;
			sum = 0;
			break;
		// 3의 배수 이거나 5의 배수인 숫자를 출력하고 그 숫자에 1을 더한 숫자도 출력한다.
		case 'm':
			// 3의 배수 이거나 5의 배수인 숫자 출력
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 || random_number[i] % 5 == 0) {
					cout << random_number[i] << " ";
				}
			}
			cout << endl;
			// 그 숫자에 1을 더한 숫자 출력
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 || random_number[i] % 5 == 0) {
					cout << random_number[i] + 1 << " ";
				}
			}
			cout << endl;
			break;
		// 3의 배수 이고 5의 배수인 숫자를 출력하고 그 숫자에 1을 뺀 숫자도 출력한다.
		case 'n':
			// 3의 배수 이고 5의 배수인 숫자 출력
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 && random_number[i] % 5 == 0) {
					cout << random_number[i] << " ";
				}
			}
			cout << endl;
			// 그 숫자에 1을 뺀 숫자 출력
			for (int i = 0; i < size; ++i) {
				if (random_number[i] % 3 == 0 && random_number[i] % 5 == 0) {
					cout << random_number[i] - 1 << " ";
				}
			}
			cout << endl;
			break;
		// 다시 재정렬
		case 'r':
			cout << "Origin numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << origin_number[i] << " ";
			}
			cout << endl;
			break;
		// 다시 숫자를 입력받고 그 숫자보다 큰 랜덤 숫자 50개 만들고 출력하기
		case 'p':
			// 숫자 입력받기
			while (true) {
				cout << "Input number: ";
				cin >> input_number;

				if (input_number > 100) break;
				else cout << "100보다 큰 수를 입력하세요" << endl;
			}
			// 입력받은 숫자보다 큰 랜덤한 수 50개 생성
			for (int i = 0; i < size; ++i) {
				random_number[i] = (rand() % input_number) + input_number + 1;

				// 중복체크
				for (int j = 0; j < i; ++j) {
					if (random_number[i] == random_number[j]) i--;
				}
			}
			// 출력
			cout << "Generated numbers: ";
			for (int i = 0; i < size; ++i) {
				cout << random_number[i] << " ";
			}
			cout << endl;
			break;
		// 프로그램 종료
		case 'q':
			exit(true);

		}
	
	}

	return 0;
}