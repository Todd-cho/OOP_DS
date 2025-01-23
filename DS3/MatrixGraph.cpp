#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int* [size];
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int) * size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	if (vertex >= 0 && vertex < m_Size) {
		for (int j = 0; j < m_Size; j++) {
			if (m_Mat[vertex][j] != 0) { // If an edge exists
				(*m)[j] = m_Mat[vertex][j]; // Add edge and weight
			}
		}
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	if (from >= 0 && from < m_Size && to >= 0 && to < m_Size) {
		if (m_Mat[from][to] == 0) { // If the value does not exist (not inserted yet)
			m_Mat[from][to] = weight; // Set weight for the edge from 'from' to 'to'
		}
		else return;
	}
}

bool MatrixGraph::printGraph() // Output function
{
	ofstream fout;
	fout.open("log.txt", ios::app);

	if (m_Size < 0)
		return 0;

	fout << "=========== PRINT ============" << endl;
	fout << '\t';
	for (int i = 0; i < m_Size; i++)
	{
		fout << "[" << i << "]" << '\t';
	}
	fout << endl;

	for (int i = 0; i < m_Size; i++)
	{
		fout << "[" << i << "]";
		for (int j = 0; j < m_Size && fout << '\t'; j++)
		{
			fout << m_Mat[i][j];
		}
		fout << endl;
	}
	fout << "============================" << endl;
	return 1;
}