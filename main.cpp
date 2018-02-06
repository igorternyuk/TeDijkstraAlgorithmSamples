#include "dijkstra.hpp"
#include <string>
#include <fstream>
#include <sstream>

void readGraphFromFile(const std::string &pathToFile, Graph<std::string> &graph);
void writeResultsToFile(const std::string &pathToFile, Graph<std::string> &graph);

int main()
{
    Graph<std::string> graph;
    readGraphFromFile("inputGraph.txt", graph);
    graph.printAjacencyLists();
    graph.dijkstra("A");
    writeResultsToFile("outputA.txt", graph);
    graph.addEdge("G", "H", 7);
    graph.dijkstra("B");
    writeResultsToFile("outputB.txt", graph);

    matrix_int adj_mtr =
    {
    //0  1  2  3  4  5
     {0,       INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, //0
     {10,      0,       INT_MAX, INT_MAX, INT_MAX, INT_MAX}, //1
     {20,      15,      0,       INT_MAX, INT_MAX, INT_MAX}, //2
     {INT_MAX, INT_MAX, 10,      0,       INT_MAX, INT_MAX}, //3
     {INT_MAX, 20,      25,      INT_MAX, 0,       INT_MAX}, //4
     {INT_MAX, INT_MAX, INT_MAX, 5,       10,      0      }  //5
    };

    std::vector<int> dist;
    matrix_int pathes;

    dijkstra_via_adjacency_matrix(1, adj_mtr, dist, pathes);

    for(size_t i {0}; i < dist.size(); ++i)
    {
        std::cout << "El camino mas corto desde vertice 1 hasta vertice "
        << i << " es " << dist[i] << std::endl;
        std::cout << "La ruta: ";
        for(size_t j {0}; j < pathes[i].size(); ++j)
        {
            std::cout << pathes[i][j];
            if(j < pathes[i].size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

void readGraphFromFile(const std::string &pathToFile,
                       Graph<std::string> &graph)
{
    std::ifstream fi(pathToFile);
    if(fi.is_open())
    {
        while(!fi.eof())
        {
            std::string str;
            std::getline(fi, str);
            std::stringstream ss;
            ss << str;
            std::string u, v;
            int dist;
            bool isBiDir;
            ss >> u >> v >> dist >> isBiDir;
            graph.addEdge(u, v, dist, isBiDir);
        }
        fi.close();
    }
    else
    {
        std::cout << "Could not open input file" << std::endl;
    }
}

void writeResultsToFile(const std::string &pathToFile, Graph<std::string> &graph)
{
    std::ofstream fo(pathToFile);
    if(fo.is_open())
    {
        fo << graph.getResult();
        fo.close();
    }
    else
    {
        std::cout << "Could not create output file" << std::endl;
    }
}
