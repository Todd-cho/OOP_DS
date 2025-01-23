#pragma once
#include <string>
using namespace std;

class SubtitleQueueNode
{

public:
	string text;
	SubtitleQueueNode* next;
	SubtitleQueueNode() {
		next = nullptr;
	}
	~SubtitleQueueNode(){}
};
