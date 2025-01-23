#pragma once
#include "SubtitleListNode.h"

class SectionListNode
{
private:
	SectionListNode* next;
	
public:
	int sectionNum;
	SubtitleListNode* subNode;

	SectionListNode() : next(nullptr),subNode(nullptr) {
		sectionNum = 0;
	}
	~SectionListNode() {}

	SectionListNode* getNext() { return next; }

	void setNext(SectionListNode* next) { this->next = next; }
};
