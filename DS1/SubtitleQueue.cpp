#include "SubtitleQueue.h"
#include "SubtitleQueueNode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

SubtitleQueue::SubtitleQueue()
{
	front = nullptr;
	back = nullptr;
}
SubtitleQueue::~SubtitleQueue()
{
	while (!IsEmpty()) {
		Pop(); // Release all memory
	}
}

bool SubtitleQueue::IsEmpty()
{
	if (front == nullptr) // If the node at the front is null
		return true;

	else
		return false;
}

bool SubtitleQueue::IsFull()
{
	int size = 0;
	SubtitleQueueNode* currentNode = new SubtitleQueueNode; // Create a node to check how many nodes are created
	currentNode = front;
	if (front == nullptr) { // If the first node is empty, return false
		return false;
	}
	else {
		while (currentNode != back) { // Iterate until the last node
			currentNode = currentNode->next; // Move to the next node
			size++; // Increment the size counter
		}
		if (size == 98) { // If the size limit is reached
			return true;
		}
		return false;
	}
}

void SubtitleQueue::Push(SubtitleQueueNode* node)
{
	if (IsFull() == true) exit(-1); // If full, exit the program
	node = new SubtitleQueueNode; // Create a new node
	if (front == nullptr) { // If the queue is empty
		front = node; // Link the newly created node
		back = node;
	}
	else {
		back->next = node; // If not empty, link the back pointer to the new node
		back = node;
	}
	int size = 0; // Variable to read the appropriate text for the node
	SubtitleQueueNode* currentNode = front; // Variable for node traversal
	if (front == nullptr) size = 0; // If empty, set size to 0
	else {
		while (currentNode != back) { // Traverse until the end
			currentNode = currentNode->next;
			size++; // Increment size with each traversal
		}
	}
	string str;
	ifstream file("subtitle.txt"); // Open the file
	if (file.is_open()) {
		for (int i = 0; i <= size; i++) {
			getline(file, str);
			node->text = str; // Copy the text into the queue data
		}
		file.close();
	}
	else return;
}

string SubtitleQueue::Pop()
{
	if (IsEmpty()) exit(-1); // If empty, exit the program

	SubtitleQueueNode* delNode = front; // Variable to hold the node to be deleted
	front = front->next; // Move the front pointer to the next node

	SubtitleQueueNode* textNode = new SubtitleQueueNode; // Variable to copy text data
	textNode->text = delNode->text; // Copy the text information from the node to be deleted

	delete delNode;  // Delete the node

	if (front == nullptr) // If the front is empty, the queue is empty
		back = nullptr; // Set the back pointer to null
	return textNode->text; // Return the stored text data
}

SubtitleQueueNode* SubtitleQueue::Front()
{
	return front;
}

void SubtitleQueue::print() {
	ofstream log("log.txt");

	SubtitleQueueNode* curNode = front; // Create a pointer node pointing to the current node and point it to the first node
	if (front == nullptr)
		return;
	else { // If not empty
		log << "===== " << "LOAD" << " =====" << endl;
		while (curNode != back) { // Traverse the queue until the end
			log << curNode->text << endl; // Print
			curNode = curNode->next; // Move to the next node
		}
		log << curNode->text << endl; // After the loop ends, one node remains, print the remaining node
		log << "===============\n" << endl;
	}
	log.close();
}
