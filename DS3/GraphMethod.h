#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* NDgraph, int startvertex,vector<int>* bfs);
bool DFS(Graph* NDgraph, int startvertex,vector<int>* dfs);
bool DFS_R(Graph* NDgraph, vector<bool>* visit, int vertex,vector<int>* dfs_r);
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, int vertex);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex);
bool FLOYD(Graph* graph);
#endif
