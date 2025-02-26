// ���־�7. [����ü, �迭 ����ϱ�] �¾�� ���� �ٷ��
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Planet {
public:
	string name{};			// �༺�� �̸�
	int size{};				// �༺�� ũ��(����/������ ���� 10)
	int satelite{};			// ���� ����
	int revol{};			// ���� �ֱ� (����: ��)
	double rotate{};		// ���� �ֱ� (����: ��)
	int revol_speed{};		// ���� �ӵ� (����: km/s)
	double tilt{};			// ����
	double distance{};		// �¾���� �Ÿ� (�¾�� ���� ������ �Ÿ�: 1)

	double pl_dist{};		// ���� �༺������ �Ÿ�
	string before_name{};	// �¾�� �༺ ���� �ٷ� ���� �༺�� �̸�

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

// ���� �ӵ��� ���� ������������ ����
bool static upcompare_revspd(const Planet& a, const Planet& b) {
	return a.revol_speed < b.revol_speed;
}

// �༺�� ũ�⿡ ���� ������������ ����
bool static downcompare_size(const Planet& a, const Planet& b) {
	return a.size > b.size;
}

// ���� �༺������ �Ÿ��� ���� ������������ ����
bool static downcompare_pl_dist(const Planet& a, const Planet& b) {
	return a.pl_dist > b.pl_dist;
}

// ���⿡ ���� ������������ ����
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

	// ���� �༺������ �Ÿ� ���ؼ� �迭�� �Է�
	Solar[0].pl_dist = 0.38;
	for (int i = 1; i < 8; ++i) {
		Solar[i].pl_dist = Solar[i].distance - Solar[i - 1].distance;
	}

	// �¾�� �༺ ���� �ٷ� ���� �༺ �̸� �迭�� �Է�
	Solar[0].before_name = "Sun";
	for (int i = 1; i < 8; ++i) {
		Solar[i].before_name = Solar[i - 1].name;
	}

	// ���� �����ϱ�
	Planet origin_Solar[8]{};
	for (int i = 0; i < 8; ++i) {
		origin_Solar[i] = Solar[i];
	}

	char input{};

	while (true) {
		cout << "� ��ɾ �����ұ��?: ";
		cin >> input;

		switch (input) {

		case 'p': {
			// ��� �༺�� ������ ���
				// ���
			for (int i = 0; i < 8; ++i) {
				cout << origin_Solar[i].name << " | ũ��: " << origin_Solar[i].size << ", ���� ����: " << origin_Solar[i].satelite
					<< "��, ���� �ֱ�: " << origin_Solar[i].revol << "��, ���� �ֱ�: " << origin_Solar[i].rotate
					<< "��, ���� �ӵ�: " << origin_Solar[i].revol_speed << "km/s, �������� ����: " << origin_Solar[i].tilt
					<< "��, �¾���� �Ÿ�: " << origin_Solar[i].distance;
				cout << endl;
			}
			break;
		}

		case 'a': {
			// ���� �ӵ��� ���� ������������ ���
				// ������������ ����
			sort(begin(Solar), end(Solar), upcompare_revspd);

			// ���
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << " | ũ��: " << Solar[i].size << ", ���� ����: " << Solar[i].satelite
					<< "��, ���� �ֱ�: " << Solar[i].revol << "��, ���� �ֱ�: " << Solar[i].rotate
					<< "��, ���� �ӵ�: " << Solar[i].revol_speed << "km/s, �������� ����: " << Solar[i].tilt
					<< "��, �¾���� �Ÿ�: " << Solar[i].distance;
				cout << endl;
			}

			break;
		}

		case 'b': {
			// �༺�� ũ�⿡ ���� ������������ ���
				// ������������ ����
			sort(begin(Solar), end(Solar), downcompare_size);

			// ���
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << " | ũ��: " << Solar[i].size << ", ���� ����: " << Solar[i].satelite
					<< "��, ���� �ֱ�: " << Solar[i].revol << "��, ���� �ֱ�: " << Solar[i].rotate
					<< "��, ���� �ӵ�: " << Solar[i].revol_speed << "km/s, �������� ����: " << Solar[i].tilt
					<< "��, �¾���� �Ÿ�: " << Solar[i].distance;
				cout << endl;
			}

			break;
		}

		case 'c': {
			// ���� �༺������ �Ÿ��� ���� ������������ ���
				// ������������ ����
			sort(begin(Solar), end(Solar), downcompare_pl_dist);

			// ���
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].before_name << " ~ " << Solar[i].name << ": " << Solar[i].pl_dist << ", ";
			}
			cout << endl;

			break;
		}

		case 'd': {
			// ��� �༺�� ���� �ֱ⸦ �ð����� �ٲ㼭 ����Ѵ�.
			for (int i = 0; i < 8; ++i) {
				cout << origin_Solar[i].name << ": " << origin_Solar[i].rotate * 24 << "�ð�, ";
			}
			cout << endl;
			break;
		}

		case 'e': {
			// ���⸦ ������������ ���
			// �༺���� ���� ������ ������������ ����
			sort(begin(Solar), end(Solar), upcompare_tlit);

			// ���
			for (int i = 0; i < 8; ++i) {
				cout << Solar[i].name << ": " << Solar[i].tilt << "��, ";
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