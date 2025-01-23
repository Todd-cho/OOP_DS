#pragma once
#include <string>
using namespace std;

class SubtitleListNode
{
private:
	SubtitleListNode* next;

public:
	string stext;
	SubtitleListNode() : next(nullptr) {}
	~SubtitleListNode() {}

	SubtitleListNode* getNext() { return next; }

	void setNext(SubtitleListNode* next) { this->next = next; }
};
