//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//
//using namespace std;
//
//int main() {
//	int num;
//	srand((unsigned int)time(NULL));
//	cout << "Size of the array: ";
//	cin >> num;
//	int *ary = new int[num];
//
//	for (int i = 0; i < num; i++) {
//		ary[i] = rand() % 101;
//	}
//
//	int min = ary[0];
//	int max = ary[0];
//
//	for (int i = 1; i < num; i++) {
//		if (min > ary[i]) min = ary[i];
//		if (max < ary[i]) max = ary[i];
//	}
//	cout << "Random numbers: ";
//	for (int i = 0; i < num; i++) cout << ary[i] << " ";
//	cout << endl;
//
//	cout << "Maximum values: " << max << "\t";
//	for (int i = 0; i < num; i++) {
//		if (max == ary[i]) cout << ",Address: " << &ary[i] << endl;
//	}
//	cout << "Minimum values: " << min << "\t";
//	for (int i = 0; i < num; i++) {
//		if (min == ary[i]) cout << ",Address: " << &ary[i] << endl;
//	}
//}