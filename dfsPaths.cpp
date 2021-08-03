/***************************************************************************//**
 * @file dfsPaths.cpp
 ******************************************************************************/
#include "dfsPaths.h"

/***************************************************************************//**
 * @par Description
 *    Constructor, runs DFS.
 * 
 * @param[in] G - The graph
 * @param[in] s - The start vertex
 *
 ******************************************************************************/
dfsPaths::dfsPaths(SnakeGraph *G, int s) : s(s)
{
    dfs( G, s );
}

/***************************************************************************//**
 * @par Description
 *    The DFS function. Finds the path from the start vertex to the end vertex
 * via depth first search.
 * 
 * @param[in] G - The graph
 * @param[in] v - The end vertex
 *
 ******************************************************************************/
void dfsPaths::dfs(SnakeGraph *G, int v)
{
    marked[ v ] = true;
    for (int w : G->adj(v))
    {
        if ( !marked[ w ] )
        {
            dfs( G, w );
            prev[ w ] = v;
        }
    }
}

/***************************************************************************//**
 * @par Description
 *    This function returns true if the DFS has found a path from the beginning
 * vertex to the end vertex and false otherwise.
 * 
 * @param[in] v - The vertex in question
 *
 * @returns true if v has a path, false otherwise
 ******************************************************************************/
bool dfsPaths::hasPath(int v)
{
    return marked[ v ];
}

/***************************************************************************//**
 * @par Description
 *    This function returns the path from the start vertex to the end vertex.
 * 
 * @param[in] v - The vertex to find a path for.
 *
 * @returns list<int> of the path. The list is empty if there is no path.
 ******************************************************************************/
std::list<int> dfsPaths::pathTo(int v)
{
    std::list<int> path;
    if ( !hasPath( v ) ) return path;
    for ( int x = v ; x != s ; x = prev[ x ] )
       path.push_front( x );
    path.push_front( s );
    return path;
}

/***************************************************************************//**
 * @par Description
 *    Returns the the second vertex index from pathTo. This is the move the
 * player will make.
 *
 * @param[in] v - The destination vertex.
 *
 * @returns vertex
 ******************************************************************************/
int dfsPaths::move(int v)
{
    std::list<int> m = pathTo( v );
    m.pop_front();
    return m.front();
}


void dfsPaths::colorPath( std::vector<std::vector<int>> &grid, int v, int size )
{
    std::list<int> path = pathTo( v );
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
