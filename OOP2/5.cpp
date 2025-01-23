//#include <iostream>
//using namespace std;
//
//void MakeHarray(int** Harray, int count,int numcount) {
//	int two = 2;
//	int num = 1;
//	for (int i = 1; i < numcount; i++) {
//		two = two * 2;
//		num = num * 2;
//	}
//	int cnt = num;
//	for (int i = 0; i < cnt; i++) {
//		for (int j = 0; j < cnt; j++) {
//			*(*(Harray + i) + j + num) = *(*(Harray + i) + j);
//			*(*(Harray + i + num) + j) = *(*(Harray + i) + j);
//			*(*(Harray + i + num) + j + num) = - *(*(Harray + i) + j);
//		}
//	}
//	if (numcount == count) return;
//	else {
//		numcount++;
//		MakeHarray(Harray, count, numcount);
//	}
//}
//
//int main() {
//	int num;
//	int two = 2;
//	cout << "Enter the value of n for Hadamard matrix (2^n x 2^n): ";
//	cin >> num;
//
//	if (num == 0) {
//		int Harray = 1;
//		cout << "Hadamard Matrix of size" << num << "x" << num << ":" << endl
//			<< Harray;
//	}
//	for (int i = 1; i < num; i++) {
//		two = two * 2;
//	}
//
//	int** array = new int *[two];
//	for (int i = 0; i < two; i++) {
//		array[i] = new int[two];
//	}
//	for (int i = 0; i < two; i++) {
//		for (int j = 0; j < two; j++) {
//			array[i][j] = 0;
//		}
//	}
//	array[0][0] = 1;
//	MakeHarray(array,num,1);
//
//	cout << "Hadamard Matrix of size" << num << "x" << num << ":" << endl;
//	for (int i = 0; i < two; i++) {
//		for (int j = 0; j < two; j++) {
//			cout << array[i][j] << "\t";
//		}
//		cout << endl;
//	}
//	for (int i = 0; i < two; i++) {
//		delete[] array[i];
//	}
//	delete[] array;
//
//}