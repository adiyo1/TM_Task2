// 318725520
// adi.yohanann@gmail.com

#include "Algorithms.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <array>
#define INT_MAX __INT_MAX__

namespace ariel
{

	Algorithms::Algorithms() {}

	bool Algorithms::bfs(Graph graph, size_t start)
	{
		// Get the number of nodes from the Graph object
		size_t num_nodes = graph.get_size();

		// Create a visited vector to track visited nodes
		vector<bool> visited(num_nodes, false);

		// Queue to store nodes for BFS exploration
		queue<size_t> q;

		// Mark the starting node as visited and enqueue it
		visited[start] = true;
		q.push(start);

		while (!q.empty())
		{
			// Dequeue a node from the queue
			size_t current_node = q.front();
			q.pop();

			// Explore all unvisited neighbors of the current node
			// for (size_t neighbor : graph.getNei()[current_node]) {
			size_t num_nodes = graph.get_size(); // Assuming get_size() exists

			for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
			{
				if (graph.getNei()[current_node][neighbor] != 0)
				{
					// Process neighbor (code to be executed for each neighbor)
					if (!visited[neighbor])
					{
						visited[neighbor] = true;
						q.push(neighbor);
					}
				}
			}
		}

		// Check if all nodes are visited (connected)
		for (bool v : visited)
		{
			if (!v)
			{
				return false; // Unvisited node found, graph is not connected
			}
		}

		return true; // All nodes visited, graph is connected
	}

	bool Algorithms::isConnected(Graph g)
	{
		// cout << "graph size is: " << g.get_size() << endl;

		// if (g.isSim() == false)
		// {
		// 	if (bfs(g, 0))
		// 	{
		// 		return true;
		// 	}
		// 	return false;
		// }
		// else
		// {
			int flag = 0;
			for (size_t i = 0; i < g.get_size(); i++)
			{
				if (bfs(g, i))
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				return false;
			}
			return true;
		// }
	}

	bool Algorithms::negetiveEdge(Graph graph)
	{
		for (size_t i = 0; i < graph.get_size(); i++)
		{
			for (size_t j = 0; j < graph.get_size(); j++)
			{
				if (graph.get_nei(i, j) < 0)
					return true;
			}
		}
		return false;
	}

	bool negativeCycle(Graph graph)
	{
		// Initialize distances to positive infinity (INT_MAX represents positive infinity)
		vector<int> dist(graph.get_size(), INT_MAX);

		// Bellman-Ford algorithm for shortest paths with negative edges
		for (size_t node = 0; node < graph.get_size(); ++node)
		{
			for (size_t neighbor = 0; neighbor < graph.get_size(); ++neighbor)
			{
				// Check if there's an edge (non-zero weight)
				if (graph.get_nei(node, neighbor) != 0)
				{
					int weight = graph.get_nei(node, neighbor);
					if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor])
					{
						dist[neighbor] = dist[node] + weight;
					}
				}
			}
		}

		// Check for negative cycle (if distance keeps decreasing)
		for (size_t node = 0; node < graph.get_size(); ++node)
		{
			for (size_t neighbor = 0; neighbor < graph.get_size(); ++neighbor)
			{
				// Check if there's an edge (non-zero weight)
				if (graph.get_nei(node, neighbor) != 0)
				{
					int weight = graph.get_nei(node, neighbor);
					if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor])
					{
						return true; // Negative cycle detected
					}
				}
			}
		}

		// No negative cycle found
		return false;
	}

	string Algorithms::shortestPath(Graph graph, int start, int end)
	{
		if (negativeCycle(graph))
			return "-1";

		if (start < 0 || start >= graph.get_size() || end < 0 || end >= graph.get_size())
		{
			// return "Invalid start or end node";
			return "-1";
		}

		// Check for negative cycle (if the graph is not simple or might have negative cycles)
		// if (!graph.isSim() || negativeCycle(graph)) {
		// 	// return "Negative cycle detected. Shortest path cannot be determined.";
		// 	return "-1";
		// }

		size_t num_nodes = graph.get_size();
		int dist[num_nodes];						// Array to store distances from start to each node
		std::fill(dist, dist + num_nodes, INT_MAX); // Initialize distances to infinity

		dist[start] = 0; // Distance from start to itself is 0

		// Parent array to track the previous node in the shortest path
		int parent[num_nodes]; // Array to store parent nodes in the shortest path
		std::fill(parent, parent + num_nodes, -1);
		for (size_t node = 0; node < graph.get_size(); ++node)
		{
			for (size_t neighbor = 0; neighbor < graph.get_size(); ++neighbor)
			{
				// Check if there's an edge (non-zero weight)
				if (graph.get_nei(node, neighbor) != 0)
				{
					int weight = graph.get_nei(node, neighbor);
					if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor])
					{
						dist[neighbor] = dist[node] + weight;
						parent[neighbor] = node; // Update parent for path reconstruction
					}
				}
			}
		}
		if (dist[end] == INT_MAX)
		{
			// return "No path found from start to end";
			return "-1";
		}
		// 	string path = "";
		// 	int curr = end;
		// 	// Build the path by traversing from end to start using the parent array
		// 	while (curr != start && curr != -1) {
		// 		path = std::to_string(curr) + "->" + path;
		// 		curr = parent[curr];
		// 	}

		// 	if (curr == -1) {
		// 		// path = "No unique path found (multiple shortest paths possible).";
		// 		path= "-1";
		// 	}
		// 	else {
		// // Add the starting node to the path
		// 		path = std::to_string(start) + " -> " + path;
		// 	}
		//  	// return path + " (Distance: " + std::to_string(dist[end]) + ")";
		// 	return path;
		string path = "";
		int curr = end;

		// Build the path forward, starting from the end node
		while (curr != start && curr != -1)
		{
			path = "->" + std::to_string(curr) + path; // Prepend node with arrow if not empty
			// path = std::to_string(curr) + (path.empty() ? "" : "->") + path;
			curr = parent[curr];
		}
		if (curr == -1)
		{
			// path = "No unique path found (multiple shortest paths possible).";
			path = "-1";
		}
		else
		{
			// Add the starting node to the path
			path = std::to_string(start) + path;
		}

		return path;
	}

	string Algorithms::isBipartite(Graph g)
	{
		// Check if the graph is connected
		if (isConnected(g) == false)
		{
			// return "The graph is not bipartite (not connected).";
			return "0";
		}
		size_t num_nodes = g.get_size();

		// Initialize color array (0: uncolored, 1: color A, 2: color B)
		size_t color[num_nodes] = {0}; // Initialize all colors to 0

		// Start coloring from an arbitrary node
		color[0] = 1; // Assign color A to the starting node

		// Process each node using a queue
		queue<size_t> q;
		q.push(0);

		while (!q.empty())
		{
			size_t curr = q.front();
			q.pop();

			// Check neighbors of the current node
			for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
			{
				// Skip diagonal (self-loops) and non-existent edges
				if (neighbor == curr || g.get_nei(curr, neighbor) == 0)
				{
					continue;
				}

				// If neighbor is uncolored, assign opposite color and enqueue
				if (color[neighbor] == 0)
				{
					color[neighbor] = 3 - color[curr];
					q.push(neighbor);
				}

				// Detect cycle with same color (not bipartite)
				else if (color[neighbor] == color[curr])
				{
					// return "The graph is not bipartite.";
					return "0";
				}
			}
		}
		// Construct color sets (A and B) based on the color array
		string colorA = "{";
		string colorB = "{";
		for (int i = 0; i < num_nodes; ++i)
		{
			if (color[i] == 1)
			{
				colorA += to_string(i) + ", ";
			}
			else if (color[i] == 2)
			{
				colorB += to_string(i) + ", ";
			}
		}
		// Remove trailing commas and curly braces
		colorA.pop_back();
		colorA.pop_back();
		colorB.pop_back();
		colorB.pop_back();

		return "The graph is bipartite: A=" + colorA + "}, B=" + colorB + "}";
	}

	string Algorithms::constructCycleString(stack<size_t> cycle_path)
	{
		// string cycle_str2;
		// size_t top1 = cycle_path.top();
		// cycle_str2 = to_string(top1);
		if (cycle_path.size() <= 3)
			return "0";

		string cycle_str;
		while (!cycle_path.empty())
		{
			size_t top = cycle_path.top();
			cycle_path.pop();
			cycle_str = to_string(top) + (cycle_str.empty() ? "" : "->") + cycle_str;
		}
		return cycle_str;
	}

	bool Algorithms::isContainsCycle(Graph graph)
	{

		if (negativeCycle(graph))
			return true;
		// static string findAndPrintCycle(Graph& graph) {

		size_t num_nodes = graph.get_size();

		// Visited and inStack vectors for tracking exploration
		vector<bool> visited(num_nodes, false);
		vector<bool> inStack(num_nodes, false);
		stack<size_t> cycle_path; // Stack to store nodes in the cycle path

		// Start DFS from each node (handle disconnected graphs)
		for (size_t i = 0; i < num_nodes; ++i)
		{
			if (!visited[i])
			{
				if (dfs(graph, i, visited, inStack, cycle_path))
				{
					if (graph.get_size() == 3 && cycle_path.size() != 3 && graph.isSim())
					{
						return false;
					}
					// cout<< "lala: "<<constructCycleString(cycle_path)<<endl;
					if (cycle_path.size() > 3)
					{
						return true;
					}
					// return constructCycleString(cycle_path); // Construct and return cycle string
				}
			}
		}

		return false; // No cycle in the entire graph
	}

	bool Algorithms::negativeCycle(Graph graph)
	{
		if (negetiveEdge(graph) && graph.isSim())
		{
			// cout<<"1::"<<endl;
			return true;
		}
		if (negetiveEdge(graph) == false)
			return false;
		size_t num_nodes = graph.get_size();
		int cycle_path[num_nodes];
		// Initialize distances to positive infinity (INT_MAX represents positive infinity)
		vector<int> dist(num_nodes, INT_MAX);
		dist[0] = 0;
		// Bellman-Ford algorithm for shortest paths with negative edges
		for (size_t n = 0; n < num_nodes - 1; ++n)
		{
			for (size_t node = 0; node < num_nodes; ++node)
			{
				for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
				{
					// Check if there's an edge (non-zero weight)
					if (graph.get_nei(node, neighbor) != 0)
					{
						int weight = graph.get_nei(node, neighbor);
						cycle_path[node]++;
						// dist[node]=weight;
						if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor])
						{
							dist[neighbor] = dist[node] + weight;
						}
					}
				}
			}
		}

		// Check for negative cycle (if distance keeps decreasing)
		for (size_t node = 0; node < num_nodes; ++node)
		{
			for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
			{
				// Check if there's an edge (non-zero weight)
				if (graph.get_nei(node, neighbor) != 0)
				{
					int weight = graph.get_nei(node, neighbor);
					// if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor]) {
					if (dist[node] + weight < dist[neighbor])
					{
						// Negative cycle detected, print "1"
						// cout <<"1"<<endl;
						// if(graph.get_nei(node, neighbor)==graph.get_nei(neighbor, node)&&(graph.get_nei(neighbor, node)<0)||graph.get_nei(node, neighbor)<0)
						// cout<<"2::"<<endl;
						return true;
					}
				}
			}
		}

		// No negative cycle found
		// cout <<"0"<<endl;
		return false;
	}

	bool Algorithms::belmanFord(Graph graph)
	{
		size_t num_nodes = graph.get_size();

		// Initialize distances to positive infinity (INT_MAX represents positive infinity)
		vector<int> dist(num_nodes, INT_MAX);

		// Bellman-Ford algorithm for shortest paths with negative edges
		for (size_t n = 0; n < num_nodes - 1; ++n)
		{
			for (size_t node = 0; node < num_nodes; ++node)
			{
				for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
				{
					// Check if there's an edge (non-zero weight)
					if (graph.get_nei(node, neighbor) != 0)
					{
						int weight = graph.get_nei(node, neighbor);
						if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor])
						{
							dist[neighbor] = dist[node] + weight;
						}
					}
				}
			}
		}

		// Check for negative cycle (if distance keeps decreasing)
		for (size_t node = 0; node < num_nodes; ++node)
		{
			for (size_t neighbor = 0; neighbor < num_nodes; ++neighbor)
			{
				// Check if there's an edge (non-zero weight)
				if (graph.get_nei(node, neighbor) != 0)
				{
					int weight = graph.get_nei(node, neighbor);
					// if (dist[node] != INT_MAX && dist[node] + weight < dist[neighbor]) {
					if (dist[node] + weight < dist[neighbor])
					{
						// Negative cycle detected, print "1"
						// cout <<"1"<<endl;
						return true;
					}
				}
			}
		}

		// No negative cycle found
		// cout <<"0"<<endl;
		return false;
	}

	bool Algorithms::dfs(Graph graph, size_t node, vector<bool> visited, vector<bool> &inStack, stack<size_t> &cycle_path)
	{
		visited[node] = true;
		inStack[node] = true;
		cycle_path.push(node); // Add current node to the potential cycle path

		// Explore unvisited neighbors
		// for (size_t neighbor = 0; neighbor < graph.get_size(); ++neighbor)
		for (size_t neighbor = 0; neighbor < graph.get_size(); ++neighbor)
		{
			{
				if (graph.get_nei(node, neighbor) != 0)
				{

					if (!visited[neighbor])
					{
						if (dfs(graph, neighbor, visited, inStack, cycle_path))
						{
							return true; // Cycle found
						}
					}
					else if (inStack[neighbor])
					{							   // Back edge detected (cycle)
						cycle_path.push(neighbor); // Add neighbor to the cycle path
						return true;			   // Cycle found
					}
				}
			}
		}
		// Leaving this node (no cycle found in this branch)
		inStack[node] = false;
		cycle_path.pop(); // Remove current node from potential path
		return false;	  // No cycle found
	}

}

