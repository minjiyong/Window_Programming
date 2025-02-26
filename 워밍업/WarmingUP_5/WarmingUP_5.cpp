// ���־�5. [���ǹ� ����ϱ�] 109���� ���ǿ� �����ϱ�
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;


class Del {
private:
	

public:
	int del_num{};
	int class_num{};
	int vote{0};

	Del() {};
	~Del() {};

};

class Voter {
private:

public:
	int del_num{};

	Voter() {};
	~Voter() {  };
};


void static shuffle(int* arr, int num) {
	srand(time(NULL));
	int temp{};
	int rn{};
	for (int i = 0; i < num - 1; ++i) {
		rn = rand() % (num - i) + i;
		temp = arr[i];
		arr[i] = arr[rn];
		arr[rn] = temp;
	}
};

bool static upcompare_vote(const Del& a, const Del& b) {
	return a.vote < b.vote;
}

bool static downcompare_vote(const Del& a, const Del& b) {
	return a.vote > b.vote;
}

int main()
{
	int num_arr[13]{ 9, 12, 9, 13, 10, 6, 10, 6, 9, 5, 6, 7, 7 };
	
	// �� �ݿ� �����ؾ� �ϴ� ���ǿ� ���� ����
	shuffle(num_arr, 13);

	int num{};
	cout << "���ǿ� �ĺ��� ���ڸ� �Է��ϼ���: ";

	while (true) {
		cin >> num;

		if (150 <= num && num <= 250) break;
		else {
			cout << "150 ~ 250 ������ ���ڸ� �Է����ּ���" << endl;
		}
	}

	Del* del_candidate = new Del[num];
	Voter vot[1000]{};

	// �� ���ǿ� ���� ��� �ĺ����� ����
	for (int i = 0; i < num; ++i) {
		del_candidate[i].del_num = i + 1;
		del_candidate[i].class_num = rand() % 13 + 1;
	}

	// �ݺ� �̾ƾ� �ϴ� ���ǿ� �� ���
	for (int i = 0; i < num; ++i) {  
		cout << i + 1 << "�� - " << del_candidate[i].class_num << "��, ";
	}


	string input{};
	while (true) {
		cin >> input;
		char input_c = input[0];
		Del del_temp[13][250]{};		// �� ���ǿ� �ĺ� �迭
		int temp[13]{ 0 };				// �ݺ��� ��ǥ���� ���ǿ� �ĺ��� �������

		if (isalpha(input_c) != 0) {
			switch (input_c) {
			case 'p':
			{
				// �� �ݿ� �����ؾ� �ϴ� ���ǿ� ���� ���
				for (int i = 0; i < 13; ++i) {
					cout << num_arr[i] << " ";
				}
				cout << endl;

				// 1000���� �ο��� ���� ���ǿ����� ��ǥ
				// �Ѹ��� ����
				// 1���� ���ǿ� �ĺ� ����(N)�� �ϳ��� ����
				// �ش� ������ ���ǿ� �ĺ����� ��ǥ�� �Ѵ�
				// �̰� ������ ��ǥ �ο�(1000��° ���)���� ������
				for (int i = 0; i < 1000; ++i) {
					int temporary{ rand() % num + 1 };
					vot[i].del_num = temporary;
					del_candidate[vot[i].del_num].vote++;
				}
				break;

			}

			case 'a':
			{
				// �� ���� ��ǥ�� ���� ���ǿ� �ĺ��� ��ȣ�� �������� ����
				// �ڽ��� ���̶�� �ӽ� �迭�� ���� ����
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// ��ǥ���� �� ��� �������� ����
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], upcompare_vote);
				}
				// ���
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "��: ";
					for (int i = 0; i < temp[j]; ++i) {
						cout << del_temp[j][i].del_num << "�� - " << del_temp[j][i].vote << "ǥ, ";
					}
					cout << endl;
				}
				break;
			}

			case 'd':
			{
				// �� ���� ��ǥ�� ���� ���ǿ� �ĺ��� ��ȣ�� �������� ����
				// �ڽ��� ���̶�� �ӽ� �迭�� ���� ����
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// ��ǥ���� �� ��� �������� ����
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], downcompare_vote);
				}
				// ���
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "��: ";
					for (int i = 0; i < temp[j]; ++i) {
						cout << del_temp[j][i].del_num << "�� - " << del_temp[j][i].vote << "ǥ, ";
					}
					cout << endl;
				}

				break;
			}

			case 'm': {
				Del loser[150]{};
			
				// �ڽ��� ���̶�� �ӽ� �迭�� ���� ����
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// ��ǥ���� �� ��� �������� ����
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], downcompare_vote);
				}

				// �� �ݸ��� Ż���� ���ؼ� Ż���� �迭�� �ֱ�
				int cnt{ 0 };
				for (int j = 0; j < 13; ++j) {
					for (int i = num_arr[j]; i < temp[j]; ++i) {
						loser[cnt++] = del_temp[j][i];
					}
				}
				cnt = 0;

				// Ż���ڵ� ��ǥ������ �������� ����
				sort(begin(loser), end(loser), downcompare_vote);

				// Ż���ڸ� ����� ��� �ֱ�
				for (int j = 0; j < 13; ++j) {
					if (num_arr[j] > temp[j]) {
						for (int i = 0; i < num_arr[j] - temp[j] + 1; ++i) {
							del_temp[j][i + temp[j]] = loser[cnt++];
						}
					}
				}

				// ���
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "��: ";
					for (int i = 0; i < num_arr[j]; ++i) {
						cout << del_temp[j][i].del_num << "�� - " << del_temp[j][i].vote << "ǥ, ";
					}
					cout << endl;
				}

				break;
			}

			case 'n': 
			{
				// ��ü �ٵ�ǥ ������ 109���� ���ǿ� ��ȣ�� ���
				// �ڽ��� ���̶�� �ӽ� �迭�� ���� ����
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}

				// 2���� �迭�� 1���� �迭�� ��ħ
				Del all_Del[3250];
				int index{ 0 };
				for (int i = 0; i < 13; ++i) {
					for (int j = 0; j < 250; ++j) {
						all_Del[index++] = del_temp[i][j];
					}
				}

				// ��ǥ���� �� ��� �������� ����
				sort(begin(all_Del), end(all_Del), downcompare_vote);

				// ���
				for (int i = 0; i < 109; ++i) {
					cout << all_Del[i].del_num << "�� - " << all_Del[i].vote << "ǥ " << all_Del[i].class_num << "��, ";
				}
				
				break;
			}

			case 'r': {
				shuffle(num_arr, 13);
				cout << "���ǿ� �ĺ��� ���ڸ� �Է��ϼ���: ";
				while (true) {
					cin >> num;

					if (150 <= num && num <= 250) break;
					else {
						cout << "150 ~ 250 ������ ���ڸ� �Է����ּ���" << endl;
					}
				}

				for (int i = 0; i < num; ++i) {
					del_candidate[i].del_num = 0;
					del_candidate[i].class_num = 0;
					del_candidate[i].vote = 0;
				}

				// �� ���ǿ� ���� ��� �ĺ����� ����
				for (int i = 0; i < num; ++i) {
					del_candidate[i].del_num = i + 1;
					del_candidate[i].class_num = rand() % 13 + 1;
				}

				// �ݺ� �̾ƾ� �ϴ� ���ǿ� �� ���
				for (int i = 0; i < num; ++i) {
					cout << i + 1 << "�� - " << del_candidate[i].class_num << "��, ";
				}

				break;
			}

			case 'q':
			{
				exit(true);
				break;
			}


			}
		}
		else {
			int input_i = stoi(input);
			if (0 < input_i && input_i < 1001) {
				cout << "��ȣ" << vot[input_i].del_num << "�� " << del_candidate[vot[input_i].del_num].class_num << "�� " << endl;
			}
			else continue;
		}
	}


	return 0;
}