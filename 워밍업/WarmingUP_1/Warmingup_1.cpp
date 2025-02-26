// 워밍업1. [1차원 배열 사용하기] 문자열 다루기
#include <iostream>
#include <random>

using namespace std;

int main()
{
	const int size{ 100 };
	char* input_sentence = new char[size + 1];
	int input_sentence_size{0};

	cout << "문장을 입력해주세요: ";
	cin.getline(input_sentence, size, '.');

	// size 받아오기
	for (int i = 0; i < size; ++i) {
		input_sentence_size++;
		if (input_sentence[i] == '\0') break;
	}
	input_sentence_size--;

	// 띄어쓰기 중복체크
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == ' ' && input_sentence[i + 1] == ' ') {
			for (int j = i + 1; j < input_sentence_size; ++j) {
				input_sentence[j] = input_sentence[j + 1];
			}
			i--;
		}
	}

	/*
	// 문장 끝에 . 찍기
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == '\0') {
			input_sentence[i + 1] = '\0';
			input_sentence[i] = '.';
			break;
		}
		// 공백으로 끝나는 경우
		else if (input_sentence[i] == ' ' && input_sentence[i + 1] == '\0') {
			input_sentence[i] = '.';
			break;
		}
	}*/

	// 공백으로 끝난다면 공백 없애기
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == ' ' && input_sentence[i + 1] == '\0') input_sentence[i] = '\0';
	}

	// 출력
	for (int i = 0; i < size; ++i) {
		cout << input_sentence[i];
		if (input_sentence[i] == '\0') break;
	}
	cout << ".";

	char input;

	while (true) {
		cout << endl << "메뉴를 입력하시오. :";
		cin >> input;

		// a ~ z 사용자가 입력하는 문자를 *로 바꾸기. 재입력시 *을 입력받은 문자로 바꾸기
		if (input >= 97 && input <= 122) {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == '*') input_sentence[i] = input;
				else if (input_sentence[i] == input) input_sentence[i] = '*';
			}
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		} 
		// A ~ Z 사용자가 입력하는 문자를 *로 바꾸기. 재입력시 *을 입력받은 문자로 바꾸기
		if (input >= 65 && input <= 90) {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == '*') input_sentence[i] = input;
				else if (input_sentence[i] == input) input_sentence[i] = '*';
			}
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// 모든 공백에 (@,%,#,.)중 하나의 문자를 넣어서 출력
		else if (input == '1') {
			char mark{};

			for (int i = 0; i < input_sentence_size - 1; ++i) {
				switch (rand() % 4) {
				case 0:
					mark = '@';
					break;
				case 1:
					mark = '%';
					break;
				case 2:
					mark = '#';
					break;
				case 3:
					mark = '.';
					break;
				}
				if (input_sentence[i] == ' ') input_sentence[i] = mark;
				else if (input_sentence[i] == '@'|| input_sentence[i] == '%' || input_sentence[i] == '.' || input_sentence[i] == '#') input_sentence[i] = ' ';
			}
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// 단어의 개수 출력
		else if (input == '2') {
			int cnt{0};
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == ' ') cnt++;
			}
			cnt++;
			
			cout << "단어의 개수는: " << cnt << "개 입니다.";
		}
		// 대문자는 소문자로, 소문자는 대문자로 바꾸기
		else if (input == '3') {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] >= 97 && input_sentence[i] <= 122) input_sentence[i] -= 32;
				else if (input_sentence[i] >= 65 && input_sentence[i] <= 90) input_sentence[i] += 32;
			}
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// 문장의 문자를 좌측으로 한 문자씩 이동하기
		else if (input == '4') {
			char temp = input_sentence[0];
			for (int i = 0; i < input_sentence_size; ++i) {
				input_sentence[i] = input_sentence[i + 1];
			}
			input_sentence[input_sentence_size - 1] = temp;
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// 문장의 문자를 우측으로 한 문자씩 이동하기
		else if (input == '5') {
			char temp = input_sentence[input_sentence_size - 1];
			for (int i = input_sentence_size; i >= 0; --i) {
				input_sentence[i + 1] = input_sentence[i];
			}
			input_sentence[0] = temp;
			input_sentence[input_sentence_size] = '\0';
			// 출력
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// 종료
		else if (input == '0'){
			delete[] input_sentence;
			exit(true);
		}
	}

	delete[] input_sentence;

	return 0;
}