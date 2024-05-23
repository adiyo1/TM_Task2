// 318725520
// adi.yohanann@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

namespace ariel
{

    class Graph
    {

        vector<vector<int>> _nei;
        bool _isSim;

    public:
        Graph();
        vector<vector<int>> &getNei();
        void loadGraph(vector<vector<int>> graph);
        void printGraph();
        size_t get_size();
        int get_nei(size_t i, size_t j);
        bool isSim();
        bool  checkSameSize(const Graph& other);
        friend std::ostream &operator<<(std::ostream &os, const Graph &g);
        friend bool operator==(const Graph &g1, const Graph &g2);
        //bool operator=(const Graph &other);
        bool operator>(const Graph &other);
        bool operator<(const Graph &other);
        bool operator>=(const Graph &other);
        // bool operator>=(const Graph &other);
        bool operator<=(const Graph &other);
        Graph operator+(const Graph &g);
        Graph operator-(const Graph &g);
        Graph operator*(const Graph &g);
        friend Graph operator*(const Graph& g1, const Graph& g2);
        void operator+=(int num);
        void operator+=(const Graph &other);
        void operator-=(int num);
        void operator-=(const Graph &other);
        void operator*=(int num);
        // Graph& operator*=(const Graph& other);
        void operator*=(const Graph& other);
        void operator/=(int num);
        void operator+() const;
        void operator-() ;
        //void operator++();
        Graph& operator++();
        Graph operator++(int num);
        Graph& operator--();
        Graph operator--(int num);
        // void operator(int num)++ ;
        // void operator--();
        bool operator!=(const Graph& other);
        size_t countEdges(const Graph &g);
        Graph& operator=(const Graph &other);
    };
}

#endif