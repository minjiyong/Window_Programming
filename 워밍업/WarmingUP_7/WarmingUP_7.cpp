// 워밍업7. [구조체, 배열 사용하기] 태양계 정보 다루기
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Planet {
public:
	string name{};			// 행성의 이름
	int size{};				// 행성의 크기(지름/지구의 지름 10)
	int satelite{};			// 위성 개수
	int revol{};			// 공전 주기 (단위: 일)
	double rotate{};		// 자전 주기 (단위: 일)
	int revol_speed{};		// 공전 속도 (단위: km/s)
	double tilt{};			// 기울기
	double distance{};		// 태양과의 거리 (태양과 지구 사이의 거리: 1)

	double pl_dist{};		// 다음 행성까지의 거리
	string before_name{};	// 태양계 행성 순서 바로 이전 행성의 이름

	Planet() {};
	Planet(string n, int sz, int sate, int rev, double rot, int rev_spd, double ti, double dist);
	~Planet() {};
};

Planet::Planet(string n, int sz, int sate, int rev, double rot, int rev_spd, double ti, double dist) {
	name = n;
	size = sz;
	satelite = sate;
	revol = rev;
	rotate = rot;
	revol_speed = rev_spd;
	tilt = ti;
	distance = dist;
};

// 공전 속도에 따라 오름차순으로 정렬
bool static upcompare_revspd(const Planet& a, const Planet& b) {
	return a.revol_speed < b.revol_speed;
}

// 행성의 크기에 따라 내림차순으로 정렬
bool static downcompare_size(const Planet& a, const Planet& b) {
	return a.size > b.size;
}

// 다음 행성까지의 거리에 따라 내림차순으로 정렬
bool static downcompare_pl_dist(const Planet& a, const Planet& b) {
	return a.pl_dist > b.pl_dist;
}

// 기울기에 따라 오름차순으로 정렬
bool static upcompare_tlit(const Planet& a, const Planet& b) {
	return a.tilt < b.tilt;
}

int main()
{
	Planet Solar[8]{};
	Planet a("Mercury", 48790 / 12756, 0, 88, 59, 48, 0.0352, 0.38);
	Planet b("Venus", 121030 / 12756, 0, 225, 243, 35, 177.3, 0.72);
	Planet c("Earth", 10, 1, 365, 1, 30, 23.439, 1);
	Planet d("Mars", 67790 / 12756, 2, 687, 1, 24, 25.19, 1.52);
	Planet e("Jupiter", 1429840 / 12756, 95, 4332, 0.41, 13, 3.13, 5.2);
	Planet f("Saturn", 1205630 / 12756, 146, 10759, 0.44, 10, 26.73, 9.54);
	Planet g("Uranus", 511180 / 12756, 28, 30688, 0.71, 7, 97.77, 19.2);
	Planet h("Neptune", 492440 / 12756, 16, 60182, 0.67, 5, 28.32, 30.1);

	Solar[0] = a;
	Solar[1] = b;
	Solar[2] = c;
	Solar[3] = d;
	Solar[4] = e;
	Solar[5] = f;
	Solar[6] = g;
	Solar[7] = h;

	// 다음 행성까지의 거리 구해서 배열에 입력
	Solar[0].pl_dist = 0.38;
	for (int i = 1; i < 8; ++i) {
		Solar[i].pl_dist = Solar[i].distance - Solar[i - 1].distance;
	}

	// 태양계 행성 순서 바로 이전 행성 이름 배열에 입력
	Solar[0].before_name = "Sun";
	for (int i = 1; i < 8; ++i) {
		Solar[i].before_name = Solar[i - 1].name;
	}

	// 원본 복사하기
	Planet origin_Solar[8]{};
	for (int i = 0; i < 8; ++i) {
		origin_Solar[i] = Solar[i];
	}

	char input{};

	while (true) {
		cout << "어떤 명령어를 수행할까요?: ";
		cin >> input;

		switch (input) {

		case 'p': {
			// 모든 행성의 데이터 출력
				// 출력
			for (int i = 0; i < 8; ++i) {
				cout << origin_Solar[i].name << " | 크기: " << origin_Solar[i].size << ", 위성 개수: " << origin_Solar[i].satelite
					<< "개, 공전 주기: " << origin_Solar[i].revol << "일, 자전 주기: " << origin_Solar[i].rotate
					<< "일, 공전 속도: " << origin_Solar[i].revol_speed << "km/s, 자전축의 기울기: " << origin_Solar[i].tilt
					<< "도, 태양과의 거리: " << origin_Solar[i].distance;
				cout << endl;
			}
			break;
		}

		case 'a': {
			// 공전 속도에 따라 오름차순으로 출력
				// 오름차순으로 정렬
			sort(begin(Solar), end(Solar), upcompare_revspd);

			// 출력
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << " | 크기: " << Solar[i].size << ", 위성 개수: " << Solar[i].satelite
					<< "개, 공전 주기: " << Solar[i].revol << "일, 자전 주기: " << Solar[i].rotate
					<< "일, 공전 속도: " << Solar[i].revol_speed << "km/s, 자전축의 기울기: " << Solar[i].tilt
					<< "도, 태양과의 거리: " << Solar[i].distance;
				cout << endl;
			}

			break;
		}

		case 'b': {
			// 행성의 크기에 따라 내림차순으로 출력
				// 내림차순으로 정렬
			sort(begin(Solar), end(Solar), downcompare_size);

			// 출력
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << " | 크기: " << Solar[i].size << ", 위성 개수: " << Solar[i].satelite
					<< "개, 공전 주기: " << Solar[i].revol << "일, 자전 주기: " << Solar[i].rotate
					<< "일, 공전 속도: " << Solar[i].revol_speed << "km/s, 자전축의 기울기: " << Solar[i].tilt
					<< "도, 태양과의 거리: " << Solar[i].distance;
				cout << endl;
			}

			break;
		}

		case 'c': {
			// 다음 행성까지의 거리에 따라 내림차순으로 출력
				// 내림차순으로 정렬
			sort(begin(Solar), end(Solar), downcompare_pl_dist);

			// 출력
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].before_name << " ~ " << Solar[i].name << ": " << Solar[i].pl_dist << ", ";
			}
			cout << endl;

			break;
		}

		case 'd': {
			// 모든 행성의 자전 주기를 시간으로 바꿔서 출력한다.
			for (int i = 0; i < 8; ++i) {
				cout << origin_Solar[i].name << ": " << origin_Solar[i].rotate * 24 << "시간, ";
			}
			cout << endl;
			break;
		}

		case 'e': {
			// 기울기를 오름차순으로 출력
			// 행성들을 기울기 순으로 오름차순으로 정렬
			sort(begin(Solar), end(Solar), upcompare_tlit);

			// 출력
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << ": " << Solar[i].tilt << "도, ";
			}
			cout << endl;

			break;
		}

		case 'q': {
			exit(true);
		}


		
		}
	}

	return 0;
};