#include "Manager.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "GraphMethod.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

Manager::Manager()
{
	graph = nullptr; // Directed graph
	NDgraph = nullptr; // Undirected graph
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if (load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt) {
	ifstream fin;
	fin.open(command_txt);

	if (!fin)
	{
		printErrorCode(1000); //If file is not open, error
		return;
	}
	string line;

	while (getline(fin, line)) {  // Read file line by line
		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1);

		if (line.empty()) continue;

		vector<string> split; // Vector to store parsed commands
		stringstream sstr(line);  // Create stream from line
		string token;

		// Split by tab
		while (getline(sstr, token, '\t')) {
			if (!token.empty()) {  // Ignore empty token
				split.push_back(token);
			}
		}
		// Skip if no command
		if (split.empty()) continue;

		// Process command
		string command = split[0];

		// LOAD
		if (command == "LOAD" && split.size() == 2) { // Argument error handling
			// List format
			if (split[1] == "graph_L.txt") {
				string filename = "graph_L.txt";
				if (LOAD(filename)) {
					fout << "======== LOAD ========" << endl;
					fout << "Success" << endl;
					fout << "=====================" << endl << endl;
				}
				else printErrorCode(100);
			}
			// Matrix format
			else if (split[1] == "graph_M.txt") {
				string filename = "graph_M.txt";
				if (LOAD(filename)) {
					fout << "======== LOAD ========" << endl;
					fout << "Success" << endl;
					fout << "=====================" << endl << endl;
				}
				else printErrorCode(100);
			}
			else printErrorCode(100); // Argument error handling
		}
		// PRINT
		else if (command == "PRINT") {
			if (!PRINT()) printErrorCode(200);
		}

		// BFS
		else if (command == "BFS") {
			if (split.size() != 2)
				printErrorCode(300);
			mBFS(stoi(split[1]));
		}
		// DFS
		else if (command == "DFS") {
			if (split.size() != 2)
				printErrorCode(400);
			mDFS(stoi(split[1]));
		}
		// DFS_R
		else if (command == "DFS_R") {
			if (split.size() != 2)
				printErrorCode(500);
			mDFS_R(stoi(split[1]));
		}

		// KRUSKAL
		else if (command == "KRUSKAL") {
			if (split.size() != 1) printErrorCode(600);
			if (!mKRUSKAL()) printErrorCode(600);
		}
		// DIJKSTRA
		else if (command == "DIJKSTRA") {
			if (split.size() != 2) printErrorCode(700);
			if (!mDIJKSTRA(stoi(split[1]))) printErrorCode(700);
		}
		// BELLMANFORD
		else if (command == "BELLMANFORD") {
			if (split.size() != 3) printErrorCode(800);
			if (!mBELLMANFORD(stoi(split[1]), stoi(split[2]))) printErrorCode(800);
		}
		// FLOYD
		else if (command == "FLOYD") {
			if (split.size() != 1) printErrorCode(900);
			if (!mFLOYD()) printErrorCode(900);
		}
		// EXIT
		else if (command == "EXIT") return;
		// Error handling for other commands
		else printErrorCode(1000);
	}
	fin.close();
}

bool Manager::LOAD(string filename)
{
	ifstream file;
	if (filename == "graph_L.txt") { // graph_L.txt
		file.open("graph_L.txt");

		if (!file)
		{
			printErrorCode(100); // Error if the file does not exist
			return false;
		}
		if (graph != nullptr) { // If the graph already exists
			delete graph; // Delete the graph
			delete NDgraph;
		}
		else {
			string line;
			int i = 0;
			int from = 0;
			int to = 0;
			int weight = 0;

			while (getline(file, line)) { // Read L.txt line by line
				if (!line.empty() && line[line.length() - 1] == '\r')
					line.erase(line.length() - 1);

				if (line.empty()) continue;
				vector<string> Liststring;
				stringstream sstr(line);
				string token;
				while (getline(sstr, token, ' ')) { // Split by whitespace
					if (!token.empty())
						Liststring.push_back(token);
				}
				if (Liststring[0] == "L") { // Read graph type
					i++;
					continue;
				}
				else if (i == 1) { // Read graph size
					int a = stoi(Liststring[0]);
					graph = new ListGraph(false, a); // Create List graph
					NDgraph = new ListGraph(false, a); // Create ND (no direction) graph
					i = 0;
				}
				else { // Start inserting edges
					if (Liststring.size() == 1) { // If it's 'from'
						from = stoi(Liststring[0]);
					}
					else {
						to = stoi(Liststring[0]);
						weight = stoi(Liststring[1]);
					}
					if (to == 0 && weight == 0) continue;
					else {
						graph->insertEdge(from, to, weight);
						NDgraph->insertEdge(from, to, weight);
						NDgraph->insertEdge(to, from, weight);
					}
					to = 0;
					weight = 0;
				}
			}
		}
		file.close();
		return true;
	}

	else {
		file.open("graph_M.txt");  // graph_M.txt
		if (!file)
		{
			printErrorCode(100);
			return false;
		}
		if (graph != nullptr) {
			delete graph;
			delete NDgraph;
		}
		else {
			string line;
			int i = 0;  // j counter
			int from = 0; // i counter
			int to = 0;
			int weight = 0;

			while (getline(file, line)) { // Read line by line
				if (!line.empty() && line[line.length() - 1] == '\r')
					line.erase(line.length() - 1);

				if (line.empty()) continue;
				vector<string> Matstring;
				stringstream sstr(line);
				string token;
				while (getline(sstr, token, ' ')) { // Split by whitespace
					if (!token.empty())
						Matstring.push_back(token);
				}
				if (Matstring[0] == "M") { // Read graph type
					i++;
					continue;
				}
				else if (i == 1) { // Read graph size
					int a = stoi(Matstring[0]);
					graph = new MatrixGraph(false, a); // Create Matrix graph
					NDgraph = new MatrixGraph(false, a); // Create ND graph
					i = 0;
					continue;
				}
				else { // Start inserting edges
					for (int i = 0; i < Matstring.size(); i++) {
						to = i;
						weight = stoi(Matstring[i]);
						graph->insertEdge(from, to, weight);
						NDgraph->insertEdge(from, to, weight);
						NDgraph->insertEdge(to, from, weight);
					}
				}
				from++;
			}
		}
		file.close();
		return true;
	}
}

bool Manager::PRINT()
{
	if (graph->printGraph()) { // Graph output function
		return true;
	}
	return false;
}

bool Manager::mBFS(int vertex)
{
	vector<int> mbfs;
	if (BFS(NDgraph, vertex, &mbfs)) {
		if (mbfs.empty()) return false; // Error handling if BFS result is empty
		fout << "========= BFS =========" << endl // Output
			<< "startvertex: " << vertex << endl;
		for (int i = 0; i < mbfs.size() - 1; i++) {
			fout << mbfs.at(i) << " -> ";
		}
		fout << mbfs.back() << endl
			<< "=====================" << endl << endl;
	}
	else { // Error if BFS did not work properly
		printErrorCode(300);
		return false;
	}
	return true;
}

bool Manager::mDFS(int vertex)
{
	vector<int> mdfs;
	if (DFS(NDgraph, vertex, &mdfs)) {
		if (mdfs.empty()) return false; // Error handling if DFS result is empty
		fout << "========= DFS =========" << endl
			<< "startvertex: " << vertex << endl;
		for (int i = 0; i < mdfs.size() - 1; i++) {
			fout << mdfs.at(i) << " -> ";
		}
		fout << mdfs.back() << endl
			<< "=====================" << endl << endl;
	}
	else { // Error if DFS did not work properly
		printErrorCode(400);
		return false;
	}
	return true;
}

bool Manager::mDFS_R(int vertex)
{
	vector<int> mdfs_r;
	vector<bool> visited(NDgraph->getSize(), false); // Node visit confirmation
	if (DFS_R(NDgraph, &visited, vertex, &mdfs_r)) {
		if (mdfs_r.empty()) return false; // Error handling if DFS_R result is empty
		fout << "======== DFS_R ========" << endl
			<< "startvertex: " << vertex << endl;
		for (int i = 0; i < mdfs_r.size() - 1; i++) {
			fout << mdfs_r.at(i) << " -> ";
		}
		fout << mdfs_r.back() << endl
			<< "=====================" << endl << endl;
	}
	else { // Error if DFS_R did not process properly
		printErrorCode(500);
		return false;
	}
	return true;
}

bool Manager::mDIJKSTRA(int vertex) // Dijkstra
{
	if (!Dijkstra(graph, vertex)) return false;
	return true;
}

bool Manager::mKRUSKAL() // Kruskal
{
	if (!Kruskal(NDgraph)) {
		printErrorCode(600);
		return false;
	}
	return true;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex) // Bellman-Ford
{
	if (!Bellmanford(graph, s_vertex, e_vertex)) return false;
	return true;
}

bool Manager::mFLOYD()  // Floyd
{
	if (!FLOYD(graph)) return false;
	return true;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl << endl;
}