// 워밍업3. [2차원 배열 사용하기] 4 X 5 행렬 만들고 행렬의 연산 구현하기
#include <iostream>
#include <random>

using namespace std;

int main()
{
	const int numRows = 4;
	const int numCols = 5;
	const int numAlls = numRows * numCols;

	int random_number[numRows][numCols]{};
	int origin_random_number[numRows][numCols]{};

	int onedim_random_number[numAlls]{};
	int origin_onedim_random_number[numAlls]{};
	int temp_onedim_random_number[numAlls]{};

	// 1차원 배열에 랜덤 값 대입
	for (int i = 0; i < numAlls; ++i) {
		onedim_random_number[i] = rand() % 50 + 1;

		// 중복체크
		for (int j = 0; j < i; ++j) {
			if (onedim_random_number[i] == onedim_random_number[j]) i--;
		}
	}

	// 1차원 배열 값 출력
	for (int i = 0; i < numAlls; ++i) {
		cout << onedim_random_number[i] << " ";
	}
	cout << endl;
	
	// 1차원 배열 값을 2차원 배열에 대입
	int temp{ 0 };
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			random_number[i][j] = onedim_random_number[temp++];
		}
	}
	temp = 0;

	// 원본, 임시 1차원 배열 저장
	for (int i = 0; i < numAlls; ++i) {
		origin_onedim_random_number[i] = onedim_random_number[i];
		temp_onedim_random_number[i] = onedim_random_number[i];
	}
	
	// 원본 2차원 배열 저장
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			origin_random_number[i][j] = random_number[i][j];
		}
	}

	// 출력
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			cout.width(10);
			cout << random_number[i][j];
		}
		cout << endl;
	}

	char input{};
	bool checka = false;
	bool checkd = false;
	bool checke = false;
	bool checko = false;
	bool checkm = false;
	bool checkn = false;
	bool checkp = false;
	bool checku = false;
	bool checkr = false;
	bool checks = false;

	while (true) {
		cout << "명령어 입력: ";
		cin >> input;
		
		switch (input) {
		// 1행 1열을 시작으로 행을 따라 오름차순으로 정렬
		case 'a':
			if (checka == false) {
				// 1차원 배열을 오름차순으로 정렬
				for (int i = 0; i < numAlls - 1; ++i) {
					for (int j = 0; j < numAlls - 1 - i; ++j) {
						if (onedim_random_number[j] > onedim_random_number[j + 1]) {
							int temp{ onedim_random_number[j + 1] };
							onedim_random_number[j + 1] = onedim_random_number[j];
							onedim_random_number[j] = temp;
						}
					}
				}
				// 1차원 배열 값을 2차원 배열에 대입
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ 원상복구
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checka = true;
				break;
			}
			else if (checka == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checka = false;
				break;
			}

		// 1행 5열을 시작으로 열을 따라 내림차순으로 정렬
		case 'd':
			if (checkd == false) {
				// 1차원 배열을 내림차순으로 정렬
				for (int i = 0; i < numAlls - 1; ++i) {
					for (int j = 0; j < numAlls - 1 - i; ++j) {
						if (onedim_random_number[j] < onedim_random_number[j + 1]) {
							int temp{ onedim_random_number[j + 1] };
							onedim_random_number[j + 1] = onedim_random_number[j];
							onedim_random_number[j] = temp;
						}
					}
				}
				// 1차원 배열 값을 2차원 배열에 대입
				for (int j = numCols - 1; j >= 0; --j) {
					for (int i = 0; i < numRows; ++i) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ 원상복구
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checkd = true;
				break;
			}
			else if (checkd == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checkd = false;
				break;
			}

		// 짝수만 출력하기
		case'e':
			if (checke == false) {
				for (int i = 0; i < numAlls; i++) {
					if (onedim_random_number[i] % 2 == 1) {
						onedim_random_number[i] = 0;
					}
				}
				// 1차원 배열 값을 2차원 배열에 대입
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ 원상복구
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checke = true;
				break;
			} 
			else if (checke == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checke = false;
				break;
			}

		// 홀수만 출력하기
		case'o':
			if (checko == false) {
				for (int i = 0; i < numAlls; i++) {
					if (onedim_random_number[i] % 2 == 0) {
						onedim_random_number[i] = 0;
					}
				}
				// 1차원 배열 값을 2차원 배열에 대입
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ 원상복구
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checko = true;
				break;
			}
			else if (checko == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checko = false;
				break;
			}

		// 최대값을 찾아 모든 값에 더한 값을 출력
		case 'm':
			if (checkm == false) {
				// 1차원 배열 중 최대값 찾기
				int max{0};
				for (int i = 0; i < numAlls; ++i) {
					if (origin_onedim_random_number[i] > max) max = origin_onedim_random_number[i];
				}
				cout << "최대값은: " << max << endl;

				// 1차원 배열 값을 2차원 배열에 대입
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++] + max;
					}
				}
				temp = 0;

				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checkm = true;
				break;
			}
			else if (checkm == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checkm = false;
				break;
			}

		// 최소값을 찾아 모든 값에 더한 값을 출력
		case 'n':
			if (checkn == false) {
				// 1차원 배열 중 최소값 찾기
				int min{ 50 };
				for (int i = 0; i < numAlls; ++i) {
					if (origin_onedim_random_number[i] < min) min = origin_onedim_random_number[i];
				}
				cout << "최소값은: " << min << endl;

				// 1차원 배열 값을 2차원 배열에 대입
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++] - min;
					}
				}
				temp = 0;

				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checkn = true;
				break;
			}
			else if (checkn == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checkn = false;
				break;
			}

		// 한 행의 값을 모두 더해 각 행의 1열에 저장
		case 'p':
			if (checkp == false) {
				int sum[numRows]{ 0 };
				for (int i = 0; i < numRows; ++i) {
						for (int j = 0; j < numCols; ++j) {
							sum[i] += random_number[i][j];
						}
						random_number[i][0] = sum[i];
				}
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checkp = true;
				break;
			}
			else if (checkp == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checkp = false;
				break;
			}

		// 한 열의 값을 모두 곱해 각 열의 4행에 저장
		case 'u':
			if (checku == false) {
				int mult[numCols]{1, 1, 1, 1, 1};
				for (int j = 0; j < numCols; ++j) {
					for (int i = 0; i < numRows; ++i) {
						mult[j] *= random_number[i][j];
					}
					random_number[3][j] = mult[j];
				}
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checku = true;
				break;
			}
			else if (checku == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checku = false;
				break;
			}

		// 기존 숫자를 랜덤하게 재정렬
		case 'r':
			if (checkr == false) {
				int f_rand{};
				int s_rand{};
				int temp_rand{};

				// 1차원 배열을 랜덤하게 다시 정렬해서 대입
				for (int i = 0; i < numAlls; ++i) {
					f_rand = rand() % numAlls;
					s_rand = rand() % numAlls;

					temp_rand = onedim_random_number[f_rand];
					onedim_random_number[f_rand] = onedim_random_number[s_rand];
					onedim_random_number[s_rand] = temp_rand;
				}
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number 원상복구
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = origin_random_number[i][j];
					}
				}
				checkr = true;
				break;
			}
			else if (checkr == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checkr = false;
				break;
			}

		// 새로운 숫자를 다시 자동입력(리셋)
		case 's':
			if (checks == false) {
				// 1차원 배열에 랜덤 값 대입
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = rand() % 50 + 1;

					// 중복체크
					for (int j = 0; j < i; ++j) {
						if (onedim_random_number[i] == onedim_random_number[j]) i--;
					}
				}
				// 1차원 배열 값을 2차원 배열에 대입
				int temp{ 0 };
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// 출력
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				checks = true;
				break;
			}
			else if (checks == true) {
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << origin_random_number[i][j];
					}
					cout << endl;
				}
				checks = false;
				break;
			}

		//프로그램 종료
		case'q':
			exit(true);
		}
	}

	return 0;
}