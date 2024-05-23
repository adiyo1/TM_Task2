// 318725520
// adi.yohanann@gmail.com

#include "Graph.hpp"
#include <set>

using namespace std;

namespace ariel
{

    Graph::Graph() {}
    vector<vector<int>> &Graph::getNei()
    {
        return this->_nei;
    }

    void Graph::loadGraph(vector<vector<int>> graph)
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (graph[i].size() != graph.size())
                throw std::runtime_error("An error occurred.");
        }
        this->_nei = graph;
        this->_isSim = this->isSim();
    }

    size_t Graph::get_size()
    {
        // Check if the adjacency matrix has been loaded
        if (this->_nei.empty())
        {
            return 0; // Return 0 if no graph loaded
        }
        else
        {
            // Return the number of rows (assuming square matrix)
            return this->_nei.size();
        }
    }
    size_t Graph::countEdges(const Graph &g)
    {
        size_t numOfdges = 0;
        for (size_t i = 0; i < g._nei.size(); ++i)
        {
            for (size_t j = 0; j < g._nei.size(); ++j)
            {
                if (g._nei[i][j] != 0)
                {
                    numOfdges++;
                }
            }
        }
        return numOfdges;
    }
    void Graph::printGraph()
    {

        int edges = 0;
        // for(int neighbor=0; neighbor<this->get_size();neighbor++)
        // {
        //     cout << neighbor << ", ";
        // }
        // cout << endl;
        for (size_t i = 0; i < this->get_size(); i++)
        {
            for (size_t j = 0; j < this->get_size(); j++)
            {
                if (this->get_nei(i, j) != 0)
                    edges++;
            }
        }
        cout << "Graph with " << this->get_size() << " vertices and " << edges << " edges." << endl;
    }

    int Graph::get_nei(size_t i, size_t j)
    {
        // Validate indices within graph dimensions
        if (i < 0 || i >= this->_nei.size() || j < 0 || j >= this->_nei.size())
        {
            return 0; // Indicate invalid indices
        }

        // Access the value at the specified row (i) and column (j)
        return this->_nei[i][j];
    }

    bool Graph::isSim()
    {

        for (size_t i = 0; i < this->_nei.size(); i++)
        {
            for (size_t j = 0; j < this->_nei.size(); j++)
            {
                if (this->_nei[i][j] != this->_nei[j][i])
                    return false;
            }
        }
        return true;
    }

    ////////OPERATORS///////////

    std::ostream &operator<<(std::ostream &os, const Graph &g)
    {

        for (size_t i = 0; i < g._nei.size(); ++i)
        {
            os << "[";
            for (size_t j = 0; j < g._nei.size(); ++j)
            {
                os << g._nei[i][j];
                if (j < g._nei.size() - 1)
                    os << ", ";
            }
            os << "]";
            if (i < g._nei.size() - 1)
                os << ", ";
            // os << std::endl;
        }
        return os;
    }

    Graph Graph::operator+(const Graph &other)
    {
        size_t num_vertices_other = other._nei.size();
        size_t num_vertices_this = _nei.size();
        size_t total_vertices = num_vertices_other + num_vertices_this;
        if (num_vertices_other != num_vertices_this)
        {
            throw("not same size");
        }

        vector<vector<int>> newMat(num_vertices_other, vector<int>(num_vertices_other, 0));
        Graph g3;

        // Copy edges from g1
        for (size_t i = 0; i < num_vertices_other; ++i)
        {
            for (size_t j = 0; j < num_vertices_other; ++j)
            {
                newMat[i][j] = other._nei[i][j] + _nei[i][j];
            }
        }
        g3.loadGraph(newMat);

        // Optionally, add edges between vertices from different graphs here
        // based on your specific criteria (disjoint union)

        return g3;
    }

    Graph Graph::operator-(const Graph &other)
    {
        // size_t num_vertices_other = other._nei.size();
        // size_t num_vertices_this = _nei.size();
        // size_t total_vertices = other._nei.size() + num_vertices_this;
        if (other._nei.size() != _nei.size())
        {
            throw("not same size");
        }

        vector<vector<int>> newMat(other._nei.size(), vector<int>(other._nei.size(), 0));
        Graph g3;

        // Copy edges from g1
        for (size_t i = 0; i < other._nei.size(); ++i)
        {
            for (size_t j = 0; j < other._nei.size(); ++j)
            {
                newMat[i][j] = _nei[i][j] - other._nei[i][j];
            }
        }
        g3.loadGraph(newMat);

        // Optionally, add edges between vertices from different graphs here
        // based on your specific criteria (disjoint union)

        return g3;
    }

    Graph Graph::operator*(const Graph &other)
    {
        if (checkSameSize(other) == false)
        {
            throw("the matrixs is not in the same size");
            exit(1);
        }
        // size_t num_vertices_other = other._nei.size();
        // size_t num_vertices_this = _nei.size();
        // size_t total_vertices = num_vertices_other + num_vertices_this;
        // if (other._nei.size() != _nei.size())
        // {
        //     throw("not same size");
        // }

        vector<vector<int>> newMat(other._nei.size(), vector<int>(other._nei.size(), 0));
        Graph g3;
        for (size_t i = 0; i < other._nei.size(); ++i)
        {
            for (size_t j = 0; j < other._nei.size(); ++j)
            {
                newMat[i][j] = 0;
                for (size_t k = 0; k < other._nei.size(); ++k)
                {
                    newMat[i][j] += _nei[i][k] * other._nei[k][j];
                }
            }
        }

        g3.loadGraph(newMat);

        // Optionally, add edges between vertices from different graphs here
        // based on your specific criteria (disjoint union)

        return g3;
    }

    Graph operator*(const Graph &g1, const Graph &g2)
    {
        // size_t num_vertices_other = g1._nei.size();
        // size_t num_vertices_this = g2._nei.size();
        // // size_t total_vertices = num_vertices_other + num_vertices_this;
        if (g1._nei.size() != g2._nei.size())
        {
            throw("not same size");
        }

        vector<vector<int>> newMat(g1._nei.size(), vector<int>(g1._nei.size(), 0));
        Graph g3;
        for (size_t i = 0; i < g1._nei.size(); ++i)
        {
            for (size_t j = 0; j < g1._nei.size(); ++j)
            {
                newMat[i][j] = 0;
                for (size_t k = 0; k < g1._nei.size(); ++k)
                {
                    newMat[i][j] += g1._nei[i][k] * g2._nei[k][j];
                }
            }
        }

        g3.loadGraph(newMat);
        return g3;
    }

    void Graph::operator+=(int num)
    {
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] + num;
            }
        }
    }

    void Graph::operator-=(int num)
    {
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] - num;
            }
        }
    }

    // Graph& Graph::operator*=(const Graph& other)
    // {
    //     *this= (*this)*(other);
    //     return *this;
    // }

    void Graph::operator*=(const Graph &other)
    {
        if (checkSameSize(other) == false)
        {
            throw("the matrixs is not in the same size");
            exit(1);
        }
        vector<vector<int>> newMat(this->get_size(), vector<int>(this->get_size(), 0));
        Graph g3;
        for (size_t i = 0; i < this->get_size(); ++i)
        {
            for (size_t j = 0; j < this->get_size(); ++j)
            {
                newMat[i][j] = 0;
                for (size_t k = 0; k < this->get_size(); ++k)
                {
                    newMat[i][j] += _nei[i][k] * other._nei[k][j];
                }
            }
        }

        // g3.loadGraph(newMat);
        for (size_t i = 0; i < this->get_size(); ++i)
        {
            for (size_t j = 0; j < this->get_size(); ++j)
            {
                this->_nei[i][j] = newMat[i][j];
            }
        }
    }

    bool Graph::checkSameSize(const Graph &other)
    {
        if (this->get_size() != other._nei.size())
        {
            return false;
        }
        return true;
    }

    void Graph::operator+=(const Graph &other)
    {
        if (checkSameSize(other) == false)
        {
            throw("the matrixs is not in the same size");
            exit(1);
        }
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] + other._nei[i][j];
            }
        }
    }

    void Graph::operator-=(const Graph &other)
    {
        if (checkSameSize(other) == false)
        {
            throw("the matrixs is not in the same size");
            exit(1);
        }
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] - other._nei[i][j];
            }
        }
    }

    void Graph::operator*=(int num)
    {
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] * num;
            }
        }
    }

    void Graph::operator/=(int num)
    {
        for (size_t i = 0; i < _nei.size(); ++i)
        {
            for (size_t j = 0; j < _nei.size(); ++j)
            {
                _nei[i][j] = _nei[i][j] / num;
            }
        }
    }

    void Graph::operator+() const
    {
        return;
    }
    void Graph::operator-()
    {
        operator*=(-1);
    }

    // void Graph:: operator++()
    // {
    //     operator+=(1);
    // }

    Graph &Graph::operator++()
    {
        *this+=(1);
        // operator+=(1);
        return *this;
    }

    Graph Graph::operator++(int num)
    {
        // Graph copy = *this;
        // for (size_t i = 0; i < _nei.size(); ++i)
        // {
        //     for (size_t j = 0; j < _nei.size(); ++j)
        //     {
        //         _nei[i][j] =_nei[i][j]+num;
               
        //     }
        // }
        // return *this;
        Graph copy = *this;
        operator+=(1);
        return copy;
    }

    // void Graph:: operator(int num)++
    // {
    //     operator+=(1);
    // }

    Graph& Graph::operator--()
    {
        // operator-=(1);
        *this-=(1);
        return *this;
    }
    Graph Graph::operator--(int num)
    {
        Graph copy = *this;
        operator-=(1);
        return copy;
    }

    // bool Graph::operator=(const Graph &other)
    // {

    //     if (checkSameSize(other) == false)
    //     {
    //         return false;
    //         throw("the matrixs is not in the same size");
    //         exit(1);
    //     }
    //     // size_t num_vertices_other = other._nei.size();
    //     // size_t num_vertices_this = _nei.size();

    //     // if (num_vertices_other != num_vertices_this)
    //     // {
    //     //     return false;
    //     // }
    //     int counter = 0;
    //     for (size_t i = 0; i < _nei.size(); ++i)
    //     {
    //         for (size_t j = 0; j < _nei.size(); ++j)
    //         {
    //             if (_nei[i][j] == other._nei[i][j])
    //             {
    //                 counter++;
    //             }
    //         }
    //     }
    //     if (counter == _nei.size() * _nei.size())
    //     {
    //         return true;
    //     }
    //     if (*this > other == false && *this < other == false)
    //     {
    //         return true;
    //     }
    //     return false;
    // }

    bool Graph::operator>(const Graph &other)
    {
        if (_nei.size() < other._nei.size())
        {
            return false;
        }
        size_t minG=0;
        if(this->_nei.size()>other._nei.size()) 
        {
            minG = other._nei.size();
        }
        else{
            minG=other._nei.size();
        }
        int count = 0;
        for (size_t i = 0; i < minG; ++i)
        {
            for (size_t j = 0; j < minG; ++j)
            {
                if (_nei[i][j] == other._nei[i][j])
                {
                    count++;
                    //cout<<"1234"<<endl;
                }
            }
        }
        if(minG*minG==count&&other._nei.size()!=_nei.size())
        {
            return true;
        }
        size_t thisNumEdges = countEdges(*this);
        size_t otherNumEdges = countEdges(other);
        cout << "thisNumEdges: " << thisNumEdges << endl;
        cout << "otherNumEdges: " << otherNumEdges << endl;
        if(thisNumEdges>otherNumEdges)
        {
            return true;
        }
        if(thisNumEdges<otherNumEdges)
        {
            return false;
        }
        
        return _nei.size()>other._nei.size();

    }
    bool Graph::operator!=(const Graph& other)
    {
        if((*this==other)==false)
        {
            return true;
        }
        return false;
    }

    //     // if (_nei.size() < other._nei.size() || operator=(other))
    //     if (_nei.size() < other._nei.size())
    //     {
    //         return false;
    //     }else if (_nei.size() > other._nei.size()) {
    //         return true;
    //     }
    //     int count = 0;
    //     for (size_t i = 0; i < other._nei.size(); ++i)
    //     {
    //         for (size_t j = 0; j < other._nei.size(); ++j)
    //         {
    //             if (_nei[i][j] == other._nei[i][j])
    //             {
    //                 count++;
    //                 cout<<"1234"<<endl;
    //             }
    //         }
    //     }
    //     if (count == other._nei.size() * other._nei.size())
    //     {
    //         return true;
    //     }
    //     size_t thisNumEdges = countEdges(*this);
    //     size_t otherNumEdges = countEdges(other);
    //     // if (!operator=(other))
    //     // {

    //     cout << "thisNumEdges: " << thisNumEdges << endl;
    //     cout << "otherNumEdges: " << otherNumEdges << endl;
    //     if (otherNumEdges > thisNumEdges)
    //     {
            
    //         return false;
    //         cout << "1111" << endl;
    //     }
    //     else if (otherNumEdges < thisNumEdges)
    //     {
    //         cout << "2222" << endl;
    //         return true;
    //     }
    //     // else if (otherNumEdges == thisNumEdges)
    //     // {
    //     if (_nei.size() > other._nei.size())
    //     {
    //         return true;
    //     }
    //     cout << "2222" << endl;
    //     return false;
    //     // }

    //     // return false;
    // }

    bool Graph:: operator>=(const Graph &other)
    {
        if (*this==other || operator>(other))
        {
            return true;
        }
        return false;
    }

    bool Graph::operator<=(const Graph &other)
    {
        if (operator>(other))
        {
            return false;
        }
        return true;
    }

    bool Graph::operator<(const Graph &other)
    {
        if (operator>=(other))
        {
            cout << "4444" << endl;
            return false;
        }
        cout << "5555" << endl;
        return true;
    }
    bool operator==(const Graph &g1, const Graph &g2)
    {
        if(g1._nei.size()!=g2._nei.size())
        {
            return false;
        }
        for (size_t i = 0; i < g2._nei.size(); ++i)
        {
            for (size_t j = 0; j < g2._nei.size(); ++j)
            {
                if (g1._nei[i][j] != g2._nei[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    Graph& Graph::operator=(const Graph &other)
    {
        // *this= other;
        // return *this;
        Graph g;
        vector<vector<int>> graph= other._nei;
        this->loadGraph(graph);
        return *this;
    }

}
