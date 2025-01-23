#pragma once
#include "FlightData.h"
#include "AVLTree.h"
#include "BpTree.h"
#include <algorithm>

using namespace std;
class Manager {
private:
	ifstream	fcmd;
	ofstream	flog;

	AVLTree* avl;	// AVL tree
	BpTree* bp;		// B+ tree
	vector<FlightData*> Print_vector;
	FlightData* data;

public:
	Manager(int bpOrder = 3); //b+ node map size == bpOrder
	~Manager(); //memory free only on newly allocated avl and bp
	void	run(const char* command_txt);
	bool	LOAD();
	bool	VLOAD();
	bool	ADD(string Airline,string FlightNumber, string Destination, string Status);
	bool	SEARCH_BP(string name);
	bool	SEARCH_BP(string start, string end);
	bool	SEARCH_AVL(string name);
	bool	VPRINT();
	bool	VPRINTB();
	void	printErrorCode(int n);
	void	PrintSuccess(string cmd);
};

