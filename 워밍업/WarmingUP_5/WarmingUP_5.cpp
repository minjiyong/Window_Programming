// 워밍업5. [조건문 사용하기] 109명의 대의원 선출하기
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
	
	// 각 반에 선출해야 하는 대의원 숫자 배정
	shuffle(num_arr, 13);

	int num{};
	cout << "대의원 후보자 숫자를 입력하세요: ";

	while (true) {
		cin >> num;

		if (150 <= num && num <= 250) break;
		else {
			cout << "150 ~ 250 사이의 숫자를 입력해주세요" << endl;
		}
	}

	Del* del_candidate = new Del[num];
	Voter vot[1000]{};

	// 각 대의원 마다 몇반 후보인지 배정
	for (int i = 0; i < num; ++i) {
		del_candidate[i].del_num = i + 1;
		del_candidate[i].class_num = rand() % 13 + 1;
	}

	// 반별 뽑아야 하는 대의원 수 출력
	for (int i = 0; i < num; ++i) {  
		cout << i + 1 << "번 - " << del_candidate[i].class_num << "반, ";
	}


	string input{};
	while (true) {
		cin >> input;
		char input_c = input[0];
		Del del_temp[13][250]{};		// 총 대의원 후보 배열
		int temp[13]{ 0 };				// 반별로 투표받은 대의원 후보가 몇명인지

		if (isalpha(input_c) != 0) {
			switch (input_c) {
			case 'p':
			{
				// 각 반에 선출해야 하는 대의원 숫자 출력
				for (int i = 0; i < 13; ++i) {
					cout << num_arr[i] << " ";
				}
				cout << endl;

				// 1000명의 인원이 각각 대의원에게 투표
				// 한명이 나와
				// 1부터 대의원 후보 숫자(N)중 하나를 고른다
				// 해당 숫자의 대의원 후보에게 투표를 한다
				// 이걸 마지막 투표 인원(1000번째 사람)까지 돌린다
				for (int i = 0; i < 1000; ++i) {
					int temporary{ rand() % num + 1 };
					vot[i].del_num = temporary;
					del_candidate[vot[i].del_num].vote++;
				}
				break;

			}

			case 'a':
			{
				// 반 별로 투표를 받은 대의원 후보의 번호를 오름차순 정렬
				// 자신의 반이라면 임시 배열에 값을 저장
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// 투표받은 수 대로 오름차순 정렬
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], upcompare_vote);
				}
				// 출력
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "반: ";
					for (int i = 0; i < temp[j]; ++i) {
						cout << del_temp[j][i].del_num << "번 - " << del_temp[j][i].vote << "표, ";
					}
					cout << endl;
				}
				break;
			}

			case 'd':
			{
				// 반 별로 투표를 받은 대의원 후보의 번호를 내림차순 정렬
				// 자신의 반이라면 임시 배열에 값을 저장
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// 투표받은 수 대로 내림차순 정렬
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], downcompare_vote);
				}
				// 출력
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "반: ";
					for (int i = 0; i < temp[j]; ++i) {
						cout << del_temp[j][i].del_num << "번 - " << del_temp[j][i].vote << "표, ";
					}
					cout << endl;
				}

				break;
			}

			case 'm': {
				Del loser[150]{};
			
				// 자신의 반이라면 임시 배열에 값을 저장
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}
				// 투표받은 수 대로 내림차순 정렬
				for (int j = 0; j < 13; ++j) {
					sort(&del_temp[j][0], &del_temp[j][temp[j]], downcompare_vote);
				}

				// 각 반마다 탈락자 구해서 탈락자 배열에 넣기
				int cnt{ 0 };
				for (int j = 0; j < 13; ++j) {
					for (int i = num_arr[j]; i < temp[j]; ++i) {
						loser[cnt++] = del_temp[j][i];
					}
				}
				cnt = 0;

				// 탈락자들 투표순으로 내림차순 정렬
				sort(begin(loser), end(loser), downcompare_vote);

				// 탈락자를 빈곳에 쏙쏙 넣기
				for (int j = 0; j < 13; ++j) {
					if (num_arr[j] > temp[j]) {
						for (int i = 0; i < num_arr[j] - temp[j] + 1; ++i) {
							del_temp[j][i + temp[j]] = loser[cnt++];
						}
					}
				}

				// 출력
				for (int j = 0; j < 13; ++j) {
					cout << j + 1 << "반: ";
					for (int i = 0; i < num_arr[j]; ++i) {
						cout << del_temp[j][i].del_num << "번 - " << del_temp[j][i].vote << "표, ";
					}
					cout << endl;
				}

				break;
			}

			case 'n': 
			{
				// 전체 다득표 순으로 109명의 대의원 번호를 출력
				// 자신의 반이라면 임시 배열에 값을 저장
				for (int j = 0; j < 13; ++j) {
					for (int i = 0; i < num; ++i) {
						if (del_candidate[i].class_num == j + 1) {
							del_temp[j][temp[j]] = del_candidate[i];
							temp[j]++;
						}
					}
				}

				// 2차원 배열을 1차원 배열로 펼침
				Del all_Del[3250];
				int index{ 0 };
				for (int i = 0; i < 13; ++i) {
					for (int j = 0; j < 250; ++j) {
						all_Del[index++] = del_temp[i][j];
					}
				}

				// 투표받은 수 대로 내림차순 정렬
				sort(begin(all_Del), end(all_Del), downcompare_vote);

				// 출력
				for (int i = 0; i < 109; ++i) {
					cout << all_Del[i].del_num << "번 - " << all_Del[i].vote << "표 " << all_Del[i].class_num << "반, ";
				}
				
				break;
			}

			case 'r': {
				shuffle(num_arr, 13);
				cout << "대의원 후보자 숫자를 입력하세요: ";
				while (true) {
					cin >> num;

					if (150 <= num && num <= 250) break;
					else {
						cout << "150 ~ 250 사이의 숫자를 입력해주세요" << endl;
					}
				}

				for (int i = 0; i < num; ++i) {
					del_candidate[i].del_num = 0;
					del_candidate[i].class_num = 0;
					del_candidate[i].vote = 0;
				}

				// 각 대의원 마다 몇반 후보인지 배정
				for (int i = 0; i < num; ++i) {
					del_candidate[i].del_num = i + 1;
					del_candidate[i].class_num = rand() % 13 + 1;
				}

				// 반별 뽑아야 하는 대의원 수 출력
				for (int i = 0; i < num; ++i) {
					cout << i + 1 << "번 - " << del_candidate[i].class_num << "반, ";
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
				cout << "기호" << vot[input_i].del_num << "번 " << del_candidate[vot[input_i].del_num].class_num << "반 " << endl;
			}
			else continue;
		}
	}


	return 0;
}