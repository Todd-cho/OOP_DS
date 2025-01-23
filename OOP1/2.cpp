//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//
//using namespace std;
//
//int main() {
//	srand((unsigned int)time(NULL));
//	int num[5][10];
//	int result[5] = { 0, };
//	double avg[5];
//
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 10; j++) {
//			num[i][j] = (rand() % 99) + 1;
//		}
//	}
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 10; j++) {
//			result[i] += num[i][j];
//		}
//	}
//	for (int i = 0; i < 5; i++) {
//		avg[i] = result[i];
//		avg[i] = avg[i] / 10;
//		avg[i] = round(avg[i]);
//	}
//	cout.width(2);
//	cout << num[0][0];
//	for (int i = 1; i < 10; i++) {
//		cout.width(4);
//		cout << num[0][i];
//	}
//	cout << " | ";
//	cout.width(3);
//	cout << result[0];
//	cout << " | ";
//	cout.width(2);
//	cout << avg[0] << endl;
//
//	cout.width(2);
//	cout << num[1][0];
//	for (int i = 1; i < 10; i++) {
//		cout.width(4);
//		cout << num[1][i];
//	}
//	cout << " | ";
//	cout.width(3);
//	cout << result[1];
//	cout << " | ";
//	cout.width(2);
//	cout << avg[1] << endl;
//
//	cout.width(2);
//	cout << num[2][0];
//	for (int i = 1; i < 10; i++) {
//		cout.width(4);
//		cout << num[2][i];
//	}
//	cout << " | ";
//	cout.width(3);
//	cout << result[2];
//	cout << " | ";
//	cout.width(2);
//	cout << avg[2] << endl;
//
//	cout.width(2);
//	cout << num[3][0];
//	for (int i = 1; i < 10; i++) {
//		cout.width(4);
//		cout << num[3][i];
//	}
//	cout << " | ";
//	cout.width(3);
//	cout << result[3];
//	cout << " | ";
//	cout.width(2);
//	cout << avg[3] << endl;
//
//	cout.width(2);
//	cout << num[4][0];
//	for (int i = 1; i < 10; i++) {
//		cout.width(4);
//		cout << num[4][i];
//	}
//	cout << " | ";
//	cout.width(3);
//	cout << result[4];
//	cout << " | ";
//	cout.width(2);
//	cout << avg[4] << endl;
//}