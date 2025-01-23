#pragma once
#include "SubtitleQueueNode.h"

class SubtitleQueue
{
private:
	SubtitleQueueNode* front;
	SubtitleQueueNode* back;
public:
	SubtitleQueue();
	~SubtitleQueue();

	bool IsEmpty();
	bool IsFull();
	void Push(SubtitleQueueNode* node);
	void print();
	string Pop();
	SubtitleQueueNode* Front();
};
