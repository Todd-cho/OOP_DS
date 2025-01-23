#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Node {
public:
	Node* next = nullptr;
	int values = 0;
};

Node* head = nullptr;

void Insert(int num) {
	Node* node;
	node = new Node;
	node->values = num;
	if (head == nullptr) {
		head = node;
	}
	else {
		node->next = head;
		head = node;
	}
	return;
}

void Delete(int num) {
	Node* curNode;
	Node* preNode;

	if (head == nullptr) {
		cout << "It's empty!" << endl;
		return;
	}
	if (head->values == num) {
		curNode = head;
		head = head->next;
		delete curNode;
		return;
	}
	else {
		curNode = head->next;
		preNode = head;

		while (curNode->next != nullptr) {
			if (curNode->values == num) {
				preNode->next = curNode->next;
				delete curNode;
				return;
			}
			curNode = curNode->next;
			preNode = preNode->next;
		}
	}
}

int main() {

	while (1) {
		string command;
		cout << "Enter the command: ";
		getline(cin, command);
		stringstream com(command);
		vector<string> tokens;
		string comm;
		while (getline(com, comm, ' ')) {
			tokens.push_back(comm);
		}

		if (tokens[0] == "insert") {
			int num = stoi(tokens[1]);
			Insert(num);
			cout << "Linked list: ";
			Node* curNode;
			curNode = head;
			while (head != nullptr) {
				cout << curNode->values;
				if (curNode->next != nullptr) {
					cout << " -> ";
					curNode = curNode->next;
				}
				else {
					cout << endl;
					break;
				}
			}
		}
		else if (tokens[0] == "delete") {
			int num = stoi(tokens[1]);
			Delete(num);
		}
		else if (tokens[0] == "exit") {
			cout << "Exit the program" << endl;
			return 0;
		}
		else cout << "Wrong command" << endl;
	}
}