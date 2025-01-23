#pragma once

#include "SectionListNode.h"

class SectionList
{
private:
	SectionListNode* head;

public:
	SectionList();
	~SectionList();

	SectionListNode* getHead();

	void Insert(SectionListNode* Node, SubtitleListNode* subNdoe, int sNum, string stext);
	SectionListNode* Search(int searchNum);
};
