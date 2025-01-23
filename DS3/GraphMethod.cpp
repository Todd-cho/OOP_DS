#include "GraphMethod.h"
#include <queue>
#include <algorithm>
#include <fstream>
#include <stack>
#include <vector>

bool BFS(Graph* NDgraph, int startvertex, vector<int>* bfs)
{
	if (NDgraph->getSize() == 0) return false; // Check if the undirected graph is empty
	int size = NDgraph->getSize(); // Get the size of the graph
	vector <bool> visited(size, false); // Vector to mark visited nodes
	queue<int> q; // Queue for operations

	visited[startvertex] = true; // Mark the starting vertex as visited
	q.push(startvertex);

	while (!q.empty()) {
		int vertex = q.front(); // Current vertex = front of the queue
		bfs->push_back(q.front()); // Add to the output vector for use in the manager function
		q.pop(); // Remove the front node
		map<int, int> adjacentEdges;
		NDgraph->getAdjacentEdges(vertex, &adjacentEdges); // Get adjacent vertices
		for (const auto& edges : adjacentEdges) {
			if (!visited[edges.first]) { // If the adjacent vertex has not been visited
				visited[edges.first] = true; // Mark as visited
				q.push(edges.first); // Push to the queue
			}
		}
	}
	return true; // Exit when all nodes have been visited and the queue is empty
}

bool DFS(Graph* NDgraph, int startvertex, vector<int>* dfs)
{
	if (NDgraph->getSize() == 0) return false; // Check if the undirected graph is empty

	int size = NDgraph->getSize();
	vector<bool> visited(size, false);
	stack<int> s;
	visited[startvertex] = true;
	s.push(startvertex);
	dfs->push_back(startvertex);

	while (!s.empty()) {
		int vertex = s.top(); // Get the vertex from the stack
		s.pop(); // Remove from the stack

		map<int, int> adjacentEdges;
		NDgraph->getAdjacentEdges(vertex, &adjacentEdges); // Get adjacent vertices
		for (const auto& edge : adjacentEdges) { // Visit the smallest unvisited vertex first
			if (!visited[edge.first]) {
				visited[edge.first] = true; // Mark as visited
				dfs->push_back(edge.first);
				s.push(vertex); // Push back to the stack to indicate it has been visited
				s.push(edge.first); // Push the newly visited vertex
				break; // Exit if there are no more nodes to move to
			}
		}
	}
	return true;
}

bool DFS_R(Graph* NDgraph, vector<bool>* visit, int vertex, vector<int>* dfs_r)
{
	(*visit)[vertex] = true; // Mark the current node as visited
	dfs_r->push_back(vertex); // Save to the output vector
	map<int, int> adjacentEdges; // Get adjacent vertices
	NDgraph->getAdjacentEdges(vertex, &adjacentEdges);
	for (const auto& edges : adjacentEdges) {
		if (!(*visit)[edges.first]) {
			DFS_R(NDgraph, visit, edges.first, dfs_r); // Recursive call
		}
	}
	return true;
}

bool Kruskal(Graph* graph)
{
	int cost = 0;  // Variable to store the minimum cost
	vector<pair<int, pair<int, int>>> edges; // Vector to store the edges of the graph
	int size = graph->getSize();

	for (int i = 0; i < size; i++) { // Get all edges of the graph
		map<int, int> adjacentEdges;
		graph->getAdjacentEdges(i, &adjacentEdges);
		for (const auto& edge : adjacentEdges) {
			edges.push_back({ edge.second, { i, edge.first } }); // {weight, {from, to}}
		}
	}
	sort(edges.begin(), edges.end()); // Sort by weight in ascending order

	// Use Union-Find structure to prevent cycles
	vector<int> parent(size); // Parent vector: points to the previous node
	for (int i = 0; i < size; i++) {
		parent[i] = i;
	}

	// Select edges
	vector<pair<int, pair<int, int>>> result; // Store the final MST edges
	for (const auto& edge : edges) {
		int weight = edge.first;
		int from = edge.second.first;
		int to = edge.second.second;

		// Find function
		while (parent[from] != from) {
			from = parent[from];
		}
		while (parent[to] != to) {
			to = parent[to];
		}

		// If no cycle occurs, add the edge
		if (from != to) {
			result.push_back({ edge.first ,{ edge.second.first, edge.second.second } });
			cost += weight;
			parent[from] = to; // Union
		}
	}

	// Output results
	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << "======== KRUSKAL ========" << endl;

	vector<pair<int, pair<int, int>>> printresult; // Variable to store result for output in from to weight order
	for (const auto& edge : result) {
		printresult.push_back({ edge.second.first, {edge.second.second, edge.first} });
		printresult.push_back({ edge.second.second, {edge.second.first, edge.first} });
	}
	auto compare = [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) { // Lambda function for sorting
		if (a.first == b.first)
			return a.second.first < b.second.first; // If from is the same, sort by to
		return a.first < b.first; // Sort by from value
		};

	if (result.size() < graph->getSize() - 1) {
		return false;
	}
	sort(printresult.begin(), printresult.end(), compare); // Sort in ascending order by vertex
	int preFrom = -1;
	for (const auto& edge : printresult) {
		if (preFrom == edge.first) { // Output
			fout << edge.second.first << "(" << edge.second.second << ") ";
		}
		else {
			fout << endl << "[" << edge.first << "] ";
			fout << edge.second.first << "(" << edge.second.second << ") ";
			preFrom = edge.first;
		}
	}
	fout << endl << "cost: " << cost << endl;
	fout << "=======================" << endl << endl;

	return true;
}

bool Dijkstra(Graph* graph, int startvertex)
{
	int size = graph->getSize();
	if (startvertex >= size) return false;
	vector<int> dist(size, INT8_MAX); // Initialize values
	vector<bool> visited(size, false); // Vector to mark visited nodes
	dist[startvertex] = 0; // The priority of the starting node is the minimum

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Use a min heap, priority queue
	pq.push({ 0, startvertex }); // {distance, vertex}
	vector<int> parent(size, -1); // Vector to store the path taken

	while (!pq.empty()) {
		int vertex = pq.top().second;
		pq.pop(); // The smallest value is popped

		if (visited[vertex]) continue; // If visited, skip
		else visited[vertex] = true;  // Otherwise, mark as visited

		map<int, int> adjacentEdges;
		graph->getAdjacentEdges(vertex, &adjacentEdges);
		for (const auto& edge : adjacentEdges) {
			if (edge.second < 0) return false; // Check for negative weights
			int neighbor = edge.first;
			int weight = edge.second;

			if (dist[vertex] + weight < dist[neighbor]) { // Find the minimum path
				dist[neighbor] = dist[vertex] + weight; // If it's the minimum path, update dist
				parent[neighbor] = vertex; // Save the path taken
				pq.push({ dist[neighbor], neighbor }); // Push to the priority queue
			}
		}
	}

	// Output results

	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << "======== DIJKSTRA ========" << endl;
	fout << "startvertex: " << startvertex << endl;

	for (int i = 0; i < size; i++) {
		if (i == startvertex) continue;
		fout << "[" << i << "] ";
		if (dist[i] == INT8_MAX) {
			fout << "x"; // If unreachable
		}
		else {
			// Output the path
			stack<int> path; // Stack to store the path
			for (int v = i; v != -1; v = parent[v]) {
				path.push(v); // Add to the stack following the parent nodes
			}
			while (!path.empty()) {
				fout << path.top();
				path.pop();
				if (!path.empty()) {
					fout << " -> "; // Path separator
				}
			}
			fout << " (" << dist[i] << ")"; // Output the shortest distance
		}
		fout << endl;
	}

	fout << "==========================" << endl << endl;

	return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{
	int size = graph->getSize();
	bool IsNflag = false;
	vector<int> distances(size, INT8_MAX); // Initialize the vector to store shortest distances
	vector<int> parents(size, -1); // Vector to store previous nodes
	distances[s_vertex] = 0; // Initialize the starting index
	parents[s_vertex] = -1; // Initialize the starting point for path storage
	for (int i = 0; i < size - 1; i++) { // Repeat n-1 times for n nodes to find the shortest distance
		for (int u = 0; u < size; u++) { // Visit all nodes each time
			map<int, int> adjacentEdges;
			graph->getAdjacentEdges(u, &adjacentEdges);
			for (const auto& edge : adjacentEdges) {
				int v = edge.first; // Vertex
				int weight = edge.second; // Value
				if (distances[u] != INT8_MAX && distances[u] + weight < distances[v]) { // Update if a shorter path is found
					distances[v] = distances[u] + weight;
					parents[v] = u; // Save the path in the parent vector
				}
			}
		}
	}

	// Check for negative cycles
	for (int u = 0; u < size; u++) { // Check all vertices one more time
		map<int, int> adjacentEdges;
		graph->getAdjacentEdges(u, &adjacentEdges);
		for (const auto& edge : adjacentEdges) {
			int v = edge.first;
			int weight = edge.second;
			if (distances[u] != INT8_MAX && distances[u] + weight < distances[v]) {
				IsNflag = true; // If an update occurs, set to true => negative cycle exists
			}
		}
	}

	// Output results
	if (IsNflag) return false;
	int cost = distances[e_vertex];
	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << "======== BELLMAN-FORD ========" << endl;
	stack<int> s;
	s.push(e_vertex);
	for (int i = e_vertex; i != -1; i = parents[i]) { // From start to end vertex
		s.push(i);
	}
	if (s.top() != s_vertex) {
		fout << "x" << endl;
	}
	else {
		for (int i = 0; i < s.size(); i++) {
			fout << s.top();
			s.pop();
			if (!s.empty())
				fout << " -> ";
		}
		fout << s.top();
		s.pop();
		fout << endl << "cost: " << cost << endl;
	}
	fout << "==========================" << endl << endl;

	return true;
}

bool FLOYD(Graph* graph)
{
	int size = graph->getSize();
	vector<vector<int>> dist(size, vector<int>(size, INT8_MAX));

	// Initialization
	for (int i = 0; i < size; i++) {
		dist[i][i] = 0;
		map<int, int> adjacentEdges;
		graph->getAdjacentEdges(i, &adjacentEdges);
		for (const auto& edge : adjacentEdges) {
			dist[i][edge.first] = edge.second;
		}
	}


	for (int k = 0; k < size; k++) { // Floyd algorithm
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (dist[i][k] != INT8_MAX && dist[k][j] != INT8_MAX) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	for (int i = 0; i < size; i++) {  // Check for negative cycles
		if (dist[i][i] < 0) return false;
	}

	// Output results
	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << "======== FLOYD ========" << endl;
	fout << "\t";
	for (int i = 0; i < size; i++)
	{
		fout << "[" << i << "]" << '\t';
	}
	fout << endl;

	for (int i = 0; i < size; i++) {
		fout << "[" << i << "]";
		for (int j = 0; j < size && fout << '\t'; j++) {
			if (dist[i][j] == INT8_MAX) {
				fout << "x";
			}
			else {
				fout << dist[i][j];
			}
		}
		fout << endl;
	}
	fout << "==========================" << endl;
	return true;
}