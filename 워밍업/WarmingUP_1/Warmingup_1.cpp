// ���־�1. [1���� �迭 ����ϱ�] ���ڿ� �ٷ��
#include <iostream>
#include <random>

using namespace std;

int main()
{
	const int size{ 100 };
	char* input_sentence = new char[size + 1];
	int input_sentence_size{0};

	cout << "������ �Է����ּ���: ";
	cin.getline(input_sentence, size, '.');

	// size �޾ƿ���
	for (int i = 0; i < size; ++i) {
		input_sentence_size++;
		if (input_sentence[i] == '\0') break;
	}
	input_sentence_size--;

	// ���� �ߺ�üũ
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == ' ' && input_sentence[i + 1] == ' ') {
			for (int j = i + 1; j < input_sentence_size; ++j) {
				input_sentence[j] = input_sentence[j + 1];
			}
			i--;
		}
	}

	/*
	// ���� ���� . ���
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == '\0') {
			input_sentence[i + 1] = '\0';
			input_sentence[i] = '.';
			break;
		}
		// �������� ������ ���
		else if (input_sentence[i] == ' ' && input_sentence[i + 1] == '\0') {
			input_sentence[i] = '.';
			break;
		}
	}*/

	// �������� �����ٸ� ���� ���ֱ�
	for (int i = 0; i < size; ++i) {
		if (input_sentence[i] == ' ' && input_sentence[i + 1] == '\0') input_sentence[i] = '\0';
	}

	// ���
	for (int i = 0; i < size; ++i) {
		cout << input_sentence[i];
		if (input_sentence[i] == '\0') break;
	}
	cout << ".";

	char input;

	while (true) {
		cout << endl << "�޴��� �Է��Ͻÿ�. :";
		cin >> input;

		// a ~ z ����ڰ� �Է��ϴ� ���ڸ� *�� �ٲٱ�. ���Է½� *�� �Է¹��� ���ڷ� �ٲٱ�
		if (input >= 97 && input <= 122) {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == '*') input_sentence[i] = input;
				else if (input_sentence[i] == input) input_sentence[i] = '*';
			}
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		} 
		// A ~ Z ����ڰ� �Է��ϴ� ���ڸ� *�� �ٲٱ�. ���Է½� *�� �Է¹��� ���ڷ� �ٲٱ�
		if (input >= 65 && input <= 90) {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == '*') input_sentence[i] = input;
				else if (input_sentence[i] == input) input_sentence[i] = '*';
			}
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// ��� ���鿡 (@,%,#,.)�� �ϳ��� ���ڸ� �־ ���
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
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// �ܾ��� ���� ���
		else if (input == '2') {
			int cnt{0};
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] == ' ') cnt++;
			}
			cnt++;
			
			cout << "�ܾ��� ������: " << cnt << "�� �Դϴ�.";
		}
		// �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� �ٲٱ�
		else if (input == '3') {
			for (int i = 0; i < input_sentence_size; ++i) {
				if (input_sentence[i] >= 97 && input_sentence[i] <= 122) input_sentence[i] -= 32;
				else if (input_sentence[i] >= 65 && input_sentence[i] <= 90) input_sentence[i] += 32;
			}
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// ������ ���ڸ� �������� �� ���ھ� �̵��ϱ�
		else if (input == '4') {
			char temp = input_sentence[0];
			for (int i = 0; i < input_sentence_size; ++i) {
				input_sentence[i] = input_sentence[i + 1];
			}
			input_sentence[input_sentence_size - 1] = temp;
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// ������ ���ڸ� �������� �� ���ھ� �̵��ϱ�
		else if (input == '5') {
			char temp = input_sentence[input_sentence_size - 1];
			for (int i = input_sentence_size; i >= 0; --i) {
				input_sentence[i + 1] = input_sentence[i];
			}
			input_sentence[0] = temp;
			input_sentence[input_sentence_size] = '\0';
			// ���
			for (int i = 0; i < size; ++i) {
				cout << input_sentence[i];
				if (input_sentence[i] == '\0') break;
			}
			cout << ".";
		}
		// ����
		else if (input == '0'){
			delete[] input_sentence;
			exit(true);
		}
	}

	delete[] input_sentence;

	return 0;
}