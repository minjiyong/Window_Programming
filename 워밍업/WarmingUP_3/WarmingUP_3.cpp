// ���־�3. [2���� �迭 ����ϱ�] 4 X 5 ��� ����� ����� ���� �����ϱ�
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

	// 1���� �迭�� ���� �� ����
	for (int i = 0; i < numAlls; ++i) {
		onedim_random_number[i] = rand() % 50 + 1;

		// �ߺ�üũ
		for (int j = 0; j < i; ++j) {
			if (onedim_random_number[i] == onedim_random_number[j]) i--;
		}
	}

	// 1���� �迭 �� ���
	for (int i = 0; i < numAlls; ++i) {
		cout << onedim_random_number[i] << " ";
	}
	cout << endl;
	
	// 1���� �迭 ���� 2���� �迭�� ����
	int temp{ 0 };
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			random_number[i][j] = onedim_random_number[temp++];
		}
	}
	temp = 0;

	// ����, �ӽ� 1���� �迭 ����
	for (int i = 0; i < numAlls; ++i) {
		origin_onedim_random_number[i] = onedim_random_number[i];
		temp_onedim_random_number[i] = onedim_random_number[i];
	}
	
	// ���� 2���� �迭 ����
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			origin_random_number[i][j] = random_number[i][j];
		}
	}

	// ���
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
		cout << "��ɾ� �Է�: ";
		cin >> input;
		
		switch (input) {
		// 1�� 1���� �������� ���� ���� ������������ ����
		case 'a':
			if (checka == false) {
				// 1���� �迭�� ������������ ����
				for (int i = 0; i < numAlls - 1; ++i) {
					for (int j = 0; j < numAlls - 1 - i; ++j) {
						if (onedim_random_number[j] > onedim_random_number[j + 1]) {
							int temp{ onedim_random_number[j + 1] };
							onedim_random_number[j + 1] = onedim_random_number[j];
							onedim_random_number[j] = temp;
						}
					}
				}
				// 1���� �迭 ���� 2���� �迭�� ����
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ ���󺹱�
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number ���󺹱�
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

		// 1�� 5���� �������� ���� ���� ������������ ����
		case 'd':
			if (checkd == false) {
				// 1���� �迭�� ������������ ����
				for (int i = 0; i < numAlls - 1; ++i) {
					for (int j = 0; j < numAlls - 1 - i; ++j) {
						if (onedim_random_number[j] < onedim_random_number[j + 1]) {
							int temp{ onedim_random_number[j + 1] };
							onedim_random_number[j + 1] = onedim_random_number[j];
							onedim_random_number[j] = temp;
						}
					}
				}
				// 1���� �迭 ���� 2���� �迭�� ����
				for (int j = numCols - 1; j >= 0; --j) {
					for (int i = 0; i < numRows; ++i) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ ���󺹱�
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number ���󺹱�
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

		// ¦���� ����ϱ�
		case'e':
			if (checke == false) {
				for (int i = 0; i < numAlls; i++) {
					if (onedim_random_number[i] % 2 == 1) {
						onedim_random_number[i] = 0;
					}
				}
				// 1���� �迭 ���� 2���� �迭�� ����
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ ���󺹱�
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number ���󺹱�
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

		// Ȧ���� ����ϱ�
		case'o':
			if (checko == false) {
				for (int i = 0; i < numAlls; i++) {
					if (onedim_random_number[i] % 2 == 0) {
						onedim_random_number[i] = 0;
					}
				}
				// 1���� �迭 ���� 2���� �迭�� ����
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// onedim_ ���󺹱�
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = origin_onedim_random_number[i];
				}
				// random_number ���󺹱�
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

		// �ִ밪�� ã�� ��� ���� ���� ���� ���
		case 'm':
			if (checkm == false) {
				// 1���� �迭 �� �ִ밪 ã��
				int max{0};
				for (int i = 0; i < numAlls; ++i) {
					if (origin_onedim_random_number[i] > max) max = origin_onedim_random_number[i];
				}
				cout << "�ִ밪��: " << max << endl;

				// 1���� �迭 ���� 2���� �迭�� ����
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++] + max;
					}
				}
				temp = 0;

				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number ���󺹱�
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

		// �ּҰ��� ã�� ��� ���� ���� ���� ���
		case 'n':
			if (checkn == false) {
				// 1���� �迭 �� �ּҰ� ã��
				int min{ 50 };
				for (int i = 0; i < numAlls; ++i) {
					if (origin_onedim_random_number[i] < min) min = origin_onedim_random_number[i];
				}
				cout << "�ּҰ���: " << min << endl;

				// 1���� �迭 ���� 2���� �迭�� ����
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++] - min;
					}
				}
				temp = 0;

				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number ���󺹱�
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

		// �� ���� ���� ��� ���� �� ���� 1���� ����
		case 'p':
			if (checkp == false) {
				int sum[numRows]{ 0 };
				for (int i = 0; i < numRows; ++i) {
						for (int j = 0; j < numCols; ++j) {
							sum[i] += random_number[i][j];
						}
						random_number[i][0] = sum[i];
				}
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number ���󺹱�
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

		// �� ���� ���� ��� ���� �� ���� 4�࿡ ����
		case 'u':
			if (checku == false) {
				int mult[numCols]{1, 1, 1, 1, 1};
				for (int j = 0; j < numCols; ++j) {
					for (int i = 0; i < numRows; ++i) {
						mult[j] *= random_number[i][j];
					}
					random_number[3][j] = mult[j];
				}
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number ���󺹱�
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

		// ���� ���ڸ� �����ϰ� ������
		case 'r':
			if (checkr == false) {
				int f_rand{};
				int s_rand{};
				int temp_rand{};

				// 1���� �迭�� �����ϰ� �ٽ� �����ؼ� ����
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
				// ���
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						cout.width(10);
						cout << random_number[i][j];
					}
					cout << endl;
				}
				// random_number ���󺹱�
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

		// ���ο� ���ڸ� �ٽ� �ڵ��Է�(����)
		case 's':
			if (checks == false) {
				// 1���� �迭�� ���� �� ����
				for (int i = 0; i < numAlls; ++i) {
					onedim_random_number[i] = rand() % 50 + 1;

					// �ߺ�üũ
					for (int j = 0; j < i; ++j) {
						if (onedim_random_number[i] == onedim_random_number[j]) i--;
					}
				}
				// 1���� �迭 ���� 2���� �迭�� ����
				int temp{ 0 };
				for (int i = 0; i < numRows; ++i) {
					for (int j = 0; j < numCols; ++j) {
						random_number[i][j] = onedim_random_number[temp++];
					}
				}
				temp = 0;
				// ���
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

		//���α׷� ����
		case'q':
			exit(true);
		}
	}

	return 0;
}