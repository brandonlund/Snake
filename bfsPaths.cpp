/***************************************************************************//**
 * @file bfsPaths.cpp
 ******************************************************************************/
#include "bfsPaths.h"

/***************************************************************************//**
 * @brief Breadth-first Search Path client
 *
 * @par Description
 *    A class which will take a Graph object and perform a graph-linear time
 *    breadth-first search from a starting node to collect path data.
 * 
 * @param[in] G - The graph in question
 * @param[in] s - The starting node (vertex)
 *
 ******************************************************************************/
bfsPaths::bfsPaths(SnakeGraph *G, int v) : s(v)
{
   bfs(G, s);
}

/***************************************************************************//**
 * @brief Is there a path from the start node 's' to the target 'v'?
 *
 * @par Description
 *    Constant time function to answer the question of whether or not a path
 * exists from the start node to node 'v'
 *
 * @param[in] v - The vertex in question
 ******************************************************************************/
bool bfsPaths::hasPath(int v) { return marked[v]; }

/***************************************************************************//**
 * @brief What is the distance (length) of the path from the start 's' to 'v'
 *
 * @par Description
 *    Constant time function to answer the question of the length of the path
 * from the start node to node 'v'
 *
 * @param[in] v - The vertex in question
 ******************************************************************************/
int bfsPaths::distance(int v)
{
   return dist[v];
}

/***************************************************************************//**
 * @brief What is the path from the start 's' to 'v'
 *
 * @par Description
 *    Return the path from the start node (s) to the target node (v) in time
 * proportional to the length of the path.
 *
 * @param[in] v - The vertex in question
 *
 * @returns a list of the nodes from the start node to the target node
 ******************************************************************************/
std::list<int> bfsPaths::pathTo(int v)
{
   std::list<int> path;
   if (!hasPath(v)) return path;
   for (int x = v ; x != s ; x = prev[x])
      path.push_front(x);
   path.push_front(s);
   return path;
}
/***************************************************************************//**
 * @brief Perform a breadth-first search on Graph G
 *
 * @par Description
 *    In graph-linear time, perform a breadth first search on the graph and
 * discover the connected components and their distance to the start node.
 *
 * @param[in] G - Graph to be searched
 * @param[in] s - The node from which the search should start
 ******************************************************************************/
void bfsPaths::bfs(SnakeGraph *G, int s)
{
   std::queue<int> frontier;
   frontier.push(s);
   marked[s] = true;
   dist[s] = 0;
   while (!frontier.empty())
   {
      int v = frontier.front();
      frontier.pop();
      for (int w : G->adj(v))
      {
         if (!marked[w])
         {
            frontier.push(w);
            marked[w] = true;
            prev[w] = v;
            dist[w] = dist[v] + 1;
         }
      }
   }
}

/***************************************************************************//**
 * @par Description
 *    Return the marked vertices.
 *
 * @returns Map of marked vertices.
 ******************************************************************************/
map<int, bool> bfsPaths::Visited() { return marked ; }

/***************************************************************************//**
 * @par Description
 *    Returns the the second vertex index from pathTo. This is the move the
 * player will make.
 *
 * @param[in] v - The destination vertex.
 *
 * @returns vertex
 ******************************************************************************/
int bfsPaths::move(int v)
{
    std::list<int> m = pathTo( v );
    m.pop_front();
    return m.front();
}


void bfsPaths::colorPath( vector<vector<int>> &grid, int v, int size )
{
    list<int> path = pathTo( v );
    bool isPartPath = false;
    
    for ( int i = 0; i < size; i++ )
        for ( int j = 0; j < size; j++ )
        {
            for ( int p : path )
            {
                int index = i * size + j;
                if ( index == p && grid[i][j] != FOOD_VALUE )
                {
                    grid[i][j] = PATH_VALUE;
                    isPartPath = true;
                }
                else if ( !isPartPath && grid[i][j] == PATH_VALUE )
                {
                    grid[i][j] = CLEAR_VALUE;
                }
            }
            isPartPath = false;
        }
}

