// 318725520
// adi.yohanann@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test operators")
{
    ariel::Graph g1, g2,g3,g4;
    vector<vector<int>> mat1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(mat1);

    vector<vector<int>> mat2 = {
        {0, 1, -8,  0,  0},
        {1, 0,  1,  0,  0},
        {1, 1,  0,  1, -4},
        {0, 0,  1,  0,  0},
        {2, 0,  0, -5,  0}};
    g2.loadGraph(mat2);
    bool ans= g1<=g2;
    CHECK(ans == true);

    vector<vector<int>> mat3 = {
        {0, 1, 0, 7},
        {1, 0, 1, 8},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
    g3.loadGraph(mat1);
    bool ans2= g2>=g3;
    CHECK(ans2 == true);

    g3++;
    CHECK(ariel::Algorithms::isConnected(g3) == true);
    
    vector<vector<int>> mat4 = {
        {0, 1, 4},
        {1, 0, 1},
        {4, 1, 0}};
    g4.loadGraph(mat4);
    CHECK(ariel::Algorithms::isContainsCycle(g4) == false);
    CHECK(ariel::Algorithms::shortestPath(g4, 0, 2) == "0->1->2");
    g4-=4;
    cout << g4 <<endl;
    CHECK(ariel::Algorithms::isContainsCycle(g4) == true);
    CHECK(ariel::Algorithms::negativeCycle(g4) == true);

    CHECK(ariel::Algorithms::shortestPath(g4, 0, 2) == "-1");
    g4+=3;
    CHECK(ariel::Algorithms::isConnected(g4) == false);
    cout << g4 <<endl;
    CHECK(ariel::Algorithms::shortestPath(g4, 0, 2) == "-1");
    CHECK(ariel::Algorithms::isConnected(g4) == false);
    g1*=g4;
    g1++;
    cout << g1 <<endl;
    CHECK(ariel::Algorithms::isConnected(g1) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g1) == true);
    CHECK(ariel::Algorithms::negativeCycle(g1) == false);
    CHECK(ariel::Algorithms::shortestPath(g1, 0, 2) == "0->2");
}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, -8, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, -4},
        {0, 0, 1, 0, 0},
        {2, 0, 0, -5, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g,g4;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph3 = {
        {0, 1, -8, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, -4},
        {0, 0, 1, 0, 0},
        {2, 0, 0, -5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");

    vector<vector<int>> graph4 = {
        {0, 1, 1, 0, 0},
        {1, 0, 22, 0, 0},
        {1, -11, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph5 = {
        {0, 3, 0, 0, 0},
        {1, 0, 2, 0, 0},
        {0, 3, 0, 1, -2},
        {0, 0, 1, 0, 0},
        {0, 12, 7, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 3) == "1->2->3");

    vector<vector<int>> graph6 = {
        {0, 3, 0, 0, 0},
        {1, 0, 2, 0, 0},
        {0, 3, 0, 4, -2},
        {0, 0, -3, 0, 0},
        {0, 12, 7, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->4");
    vector<vector<int>> mat4 = {
        {0, 1, 4},
        {1, 0, 1},
        {4, 1, 0}};
    g4.loadGraph(mat4);
    CHECK(ariel::Algorithms::shortestPath(g4, 0, 2) == "0->1->2");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

     vector<vector<int>> graph3 = {
        {0, 1, -8, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, -4},
        {0, 0, 1, 0, 0},
        {2, 0, 0, -5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, -8, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, -4},
        {0, 0, 1, 0, 0},
        {2, 0, 0, -5, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);
    vector<vector<int>> graph4 = {
        {0, 1, -8, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, -4},
        {0, 0, 1, 0, 0},
        {2, 0, 0, -5, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    vector<vector<int>> graph5 = {
        {0, 11, 0, 0, 0},
        {11, 0, -11, 0, 0},
        {1, -11, 0, 11, 0},
        {0, 0, 11, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    vector<vector<int>> graph6 = {
        {0, 3, 0, 0, 0},
        {1, 0, -2, 0, 0},
        {0, 2, 0, 1, -3},
        {0, 0, 1, 0, 0},
        {0, 12, 7, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);


    
}





