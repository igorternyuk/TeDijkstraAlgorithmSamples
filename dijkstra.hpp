#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <climits>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <sstream>
#include <iostream>

using matrix_int = std::vector<std::vector<int>>;

void dijkstra_via_adjacency_matrix(int source, matrix_int &adjacencyMatrix,
                                   std::vector<int> &dist,
                                   matrix_int &pathes);

template<class T>
class Graph
{
public:
    void addEdge(T u, T v, int distance, bool isBidirectional = false);
    void removeEdge(T startVertex, T destVertex);
    void printAjacencyLists();
    void dijkstra(T source);
    const std::unordered_map<T, int>& getDistances() const;
    const std::unordered_map<T, std::deque<T>>& getPathes() const;
    const std::string& getResult() const { return mResult; }
private:
    std::unordered_map<T, std::list<std::pair<T, int>>> mVertices;
    std::unordered_map<T, T> mPrevVerteces;
    std::unordered_map<T, int> mDistances;
    std::unordered_map<T, std::deque<T>> mPathes;
    std::string mResult;
    //std::stringstream ss;
};

template<class T>
void Graph<T>::addEdge(T u, T v, int distance, bool isBidirectional)
{
    mVertices[u].push_back({v, distance});
    if(isBidirectional)
        mVertices[v].push_back({u, distance});
    mDistances[u] = INT_MAX;
    mDistances[v] = INT_MAX;
}

template<class T>
void Graph<T>::removeEdge(T startVertex, T destVertex)
{
    auto prevVetecesToRemove = mPrevVerteces.find(destVertex);
    if(prevVetecesToRemove != mPrevVerteces.end())
        mPrevVerteces.erase(prevVetecesToRemove);

    auto distToRemove = mDistances.find(destVertex);
    if(distToRemove != mDistances.end())
        mDistances.erase(distToRemove);

    auto pathesToRemove = mPathes.find(destVertex);
    if(pathesToRemove != mPathes.end())
        mPathes.erase(pathesToRemove);

    auto &vertex = mVertices[startVertex];
    for(auto it = vertex.begin();it != vertex.end(); it++)
    {
        if((*it).first == destVertex)
        {
            it = vertex.erase(it);
            break;
        }
    }
}

template<class T>
void Graph<T>::printAjacencyLists()
{
    for(const auto &v: mVertices)
    {
        std::cout << v.first << " -> ";
        for(const auto &neighbour: v.second)
            std::cout << "(" << neighbour.first << ", " << neighbour.second << ") ";
        std::cout << std::endl;
    }
}

template<class T>
void Graph<T>::dijkstra(T source)
{
    for(auto &v: mVertices)
        mDistances[v.first] = INT_MAX;
    mDistances[source] = 0;
    std::set<std::pair<int, T>> cola;
    cola.insert({0, source});

    while(!cola.empty())
    {
        auto p = *(cola.begin());
        auto currNodeDistance = p.first;
        T currNodeName = p.second;
        cola.erase(cola.begin());

        //Here we look all node's neigbours up
        for(auto &neighbours: mVertices[currNodeName])
        {
            auto nName = neighbours.first;
            auto nDistance = neighbours.second;
            if(currNodeDistance +  nDistance < mDistances[nName])
            {
                auto f = cola.find({mDistances[nName], nName});
                if(f != cola.end())
                    cola.erase(f);
                mDistances[nName] = currNodeDistance +  nDistance;
                cola.insert({mDistances[nName], nName});
                mPrevVerteces[nName] = currNodeName;
            }
        }
    }

    std::stringstream ss;

    for(const auto &d: mDistances)
    {
        std::deque<T> deque;
        auto curr = d.first;
        bool pathExists {true};
        deque.push_front(curr);
        while(curr != source)
        {
            if(mPrevVerteces.find(curr) != mPrevVerteces.end())
            {
                curr = mPrevVerteces[curr];
                deque.push_front(curr);
            }
            else
            {
                pathExists = false;
                break;
            }
        }

        if(pathExists)
        {
            ss << "Shortest distance from " <<  source << " to " <<
            d.first << " = " << d.second << " Path: ";
            mPathes[d.first] = deque;
            for(const auto &v: deque)
                ss << v << "->";
        }
        else
        {
            ss << "There is no path from " <<  source << " to " << d.first;
        }
        ss << std::endl;
    }
    ss << std::endl;
    mResult = ss.str();
    std::cout << ss.str();
}



#endif // DIJKSTRA_HPP
