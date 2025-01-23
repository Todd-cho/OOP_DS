#include <iostream>
using namespace std;

int main() {
	int num[5];
	cout << "Enter the five numbers: ";
	for (int i = 0; i < 5; i++) {
		cin >> num[i];
	}
	int min = num[0];
	int max = num[0];
	double avg = num[0];
	for (int i = 1; i < 5; i++) {
		if (min > num[i])
			min = num[i];
		if (max < num[i])
			max = num[i];
		avg += num[i];
	}
	avg /= 5;
	avg = round(avg);
	cout << "MIN: " << min << endl
		<< "MAX: " << max << endl
		<< "AVG: " << avg;
}