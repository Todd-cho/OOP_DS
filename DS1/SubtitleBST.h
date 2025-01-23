#pragma once

#include "SubtitleBSTNode.h"
#include <sstream>
#include <string>


class SubtitleBST
{
private:
	SubtitleBSTNode* root;

public:
	SubtitleBST();
	~SubtitleBST();

	SubtitleBSTNode* getRoot();

	SubtitleBSTNode* Insert(int data, std::string addtext);
	void Print(SubtitleBSTNode* Node);
	void Search(SubtitleBSTNode* Node, int target1, int target2, string textString[], int& index);
	SubtitleBSTNode* Delete1(SubtitleBSTNode* delNode, int target, bool& check);
	SubtitleBSTNode* Delete2(SubtitleBSTNode* delNode, int target, bool& check);
	SubtitleBSTNode* getMax(SubtitleBSTNode* maxNode);
};
