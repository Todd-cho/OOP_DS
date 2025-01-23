#pragma once

#include "SubtitleQueue.h"
#include "SubtitleQueueNode.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include "SubtitleBSTNode.h"
#include <fstream>
#include <string>

using namespace std;

class Manager
{
private:

	ifstream		fcmd;
	ofstream		flog;
	ifstream		text;

	SubtitleBST bst;
	SubtitleBSTNode* bstNode;
	SubtitleQueue que;
	SubtitleQueueNode* qNode;
	SubtitleBSTNode* managerRoot;
	SubtitleListNode* subNode;
	SectionList section;
	SectionListNode* secNode;
	string textArr[28];
	
public:
	Manager();
	~Manager();

	

	void Run(const char* command);

	void PrintSuccess(string cmd);
	void PrintErrorCode(int num);

	void LOAD(SubtitleQueue& Node);
	void QPOP(SubtitleBST& bst);
	void PRINT();
	void PRINT(int sectionNum);

	void SECTION(int SectionNum, string time1, string time2);
	void DELETE1(string time);
	void DELETE2(string time);
};
