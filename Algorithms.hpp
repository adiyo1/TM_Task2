// 318725520
// adi.yohanann@gmail.com


#include <iostream>
#include "Graph.hpp"
#include <stack>

namespace ariel {
    class Algorithms {
        public:

            Algorithms();
            static bool isConnected(Graph g);
            static string shortestPath(Graph g, int x, int y);
            static bool isContainsCycle(Graph g);
            static string isBipartite(Graph g);
            //static vector<vector<int>> convert_graph_to_adjacency_list( Graph& graph);
            static bool bfs(Graph graph, size_t start);
            static bool negetiveEdge(Graph graph);
            static bool negativeCycle(Graph graph);
            //static bool dfs(Graph graph, size_t node, vector<bool>& visited, vector<bool>& inStack);
            static bool  dfs(Graph graph, size_t node, vector<bool> visited, vector<bool>& inStack, stack<size_t>& cycle_path);
            static string constructCycleString(stack<size_t> cycle_path);
            static bool dfs(Graph graph, int node, vector<bool> visited,
                      vector<bool> inStack, stack<int> current_path,
                      stack<int> cycle_path);
            static string constructCycleString(stack<int> cycle_path);
            static bool  belmanFord(Graph graph);

    };  
}