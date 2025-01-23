#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	if (vertex >= 0 && vertex < m_Size) { // Check if the vertex is valid
		*m = m_List[vertex]; // Copy the adjacent edges of the vertex to the map
	}
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	if (from >= 0 && from < m_Size && to >= 0 && to < m_Size) { // Check if the vertices are valid
		m_List[from][to] = weight; // Set the weight for the edge from 'from' to 'to'
	}
}

bool ListGraph::printGraph() // Output function
{
	ofstream fout;
	fout.open("log.txt", ios::app);

	fout << "========= PRINT =========" << endl;

	for (int i = 0; i < m_Size; i++)
	{
		fout << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && fout << " -> "; it_++)
		{
			fout << "(" << it_->first << "," << it_->second << ")";
		}
		fout << endl;
	}
	fout << "=======================" << endl;
	fout << endl;
	return 1;
}