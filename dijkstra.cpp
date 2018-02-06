#include "dijkstra.hpp"
#include <algorithm>

void dijkstra_via_adjacency_matrix(int source, matrix_int &adjacencyMatrix,
                                   std::vector<int> &dist,
                                   matrix_int &pathes)
{
    auto size = adjacencyMatrix.size();
    bool visited[size] {false};
    std::vector<int> prev;
    for(int i = 0; i < size; ++i)
        prev.push_back(-1);
    //int prev[size] = {-1};
    dist.clear();
    dist.reserve(size);
    for(int i = 0; i < int(size); ++i)
        dist.push_back(INT_MAX);
    if(source < 0) source = 0;
    if(source > int(size - 1)) source = size - 1;
    dist[source] = 0;
    int curr_index = INT_MAX;
    int curr_dist = INT_MAX;

    do
    {
        curr_index = INT_MAX;
        curr_dist = INT_MAX;
        for(int i = 0; i < int(size); ++i)
        {
            if(!visited[i] && dist[i] < INT_MAX)
            {
                curr_dist = dist[i];
                curr_index = i;
            }
        }

        if(curr_index != INT_MAX)
        {
           for(int i = 0; i < int(size); ++i)
           {
               if(adjacencyMatrix[i][curr_index] != INT_MAX)
               {
                   if(curr_dist + adjacencyMatrix[i][curr_index] < dist[i])
                   {
                       dist[i] = curr_dist + adjacencyMatrix[i][curr_index];
                       prev[i] = curr_index;
                   }
               }
           }
           visited[curr_index] = true;
        }

    } while(curr_index < INT_MAX);

    pathes.clear();

    for(size_t i {0}; i < size; ++i)
    {
        std::vector<int> path;
        int currVertex = i;
        path.push_back(currVertex);
        while(currVertex != source)
        {
            if(prev[currVertex] != -1)
            {
                path.push_back(prev[currVertex]);
                currVertex = prev[currVertex];
            }
            else
                break;
        }
        std::reverse(path.begin(), path.end());
        pathes.push_back(path);
    }

    for(int i = 0; i < prev.size(); ++i)
        std::cout << "prev[" << i << "]=" << prev[i] << std::endl;

}
