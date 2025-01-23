#pragma once
#include <string>
using namespace std;

class SubtitleBSTNode
{
private:
	SubtitleBSTNode* left;
	SubtitleBSTNode* right;

public:
	string text;
	int value;
	SubtitleBSTNode() : left(nullptr), right(nullptr) {
		value = 0;
	}
	~SubtitleBSTNode() {}

	SubtitleBSTNode* getLeft() { return left; }
	SubtitleBSTNode* getRight() { return right; }

	void setLeft(SubtitleBSTNode* left) { this->left = left; }
	void setRight(SubtitleBSTNode* right) { this->right = right; }
};
