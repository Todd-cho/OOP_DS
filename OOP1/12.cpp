//#include <iostream>
//using namespace std;
//
////non-recursive
////int main() {
////	int count;
////	cout << "Enter the number: ";
////	cin >> count;
////
////	int fst = 0;
////	int sec = 1;
////	int result = fst + sec;
////	for (int i = 1; i < count; i++) {
////		fst = sec;
////		sec = result;
////		result = fst + sec;
////		
////	}
////	cout << "Fibonacci_iter(" << count << "): " << fst;
////}
//
////recursive
//int fib(int cnt, int count, int fst, int sec, int thd) {
//	count++;
//	if (cnt == count) return fst;
//	fib(cnt, count, sec, thd, sec + thd);
//
//}
//
//int main() {
//	int count;
//	cout << "Enter the number: ";
//	cin >> count;
//	int num;
//	num = fib(count,0, 0, 1, 1);
//	cout << num;
//}