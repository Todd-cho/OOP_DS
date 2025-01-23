#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	int num1 = rand() % 10;
	int num2 = rand() % 10;
	while (num1 == num2) {
		num2 = rand() % 10;
	}
	int num3 = rand() % 10;
	while (num1 == num3 || num2 == num3) {
		num3 = rand() % 10;
	}
	int num4 = rand() % 10;
	while (num1 == num4 || num2 == num4 || num3 == num4) {
		num4 = rand() % 10;
	}
	int count = 0;
	while (1) {
		int strike = 0;
		int ball = 0;
		int foul = 0;
		int guessNum;
		cout << "Guess: ";
		cin >> guessNum;
		
		int n1, n2, n3, n4;

		n1 = guessNum / 1000;
		n2 = (guessNum % 1000) / 100;
		n3 = ((guessNum % 1000) % 100) / 10;
		n4 = ((guessNum % 1000) % 100) % 10;

		//check n1
		if (num1 == n1) {
			strike++;
		}
		else if (n1 == num2 || n1 == num3 || n1 == num4) ball++;
		else foul++;

		//check n2
		if (num2 == n2) {
			strike++;
		}
		else if (n2 == num1 || n2 == num3 || n2 == num4) ball++;
		else foul++;

		//check n3
		if (num3 == n3) {
			strike++;
		}
		else if (n3 == num1 || n3 == num2 || n3 == num4) ball++;
		else foul++;

		//check n4
		if (num4 == n4) {
			strike++;
		}
		else if (n4 == num1 || n4 == num2 || n4 == num3) ball++;
		else foul++;

		cout << endl << "Strike :" << strike << ", Ball: " << ball
			<< ", Foul: " << foul << endl << endl
			<< "----------------------" << endl << endl;

		if (strike == 4 && ball == 0 && foul == 0) {
			cout << "WIN!!!!!!!!!" << endl << endl;
			cout << "Answer: "<< num1 << num2 << num3 << num4 << endl;
			break;
		}
		else {
			strike = 0;
			ball = 0;
			foul = 0;
			count++;
		}

		if (count == 10) {
			cout << "LOOOOOOOSE คน" << endl << endl;
			cout << "Answer: " << num1 << num2 << num3 << num4 << endl;
			break;
		}

		if(guessNum == 10000) cout << num1 << num2 << num3 << num4 << endl;
	}
	return 0;
}