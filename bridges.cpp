#include "bridges.h"

/***************************************************************************//**
 * @par Description
 *    The constructor. Utilizes DFS to find bridges.
 *
 * @param[in] G - The graph.
 ******************************************************************************/
Bridges::Bridges(SnakeGraph *G) : ID(0)
{
    for ( int v : G->Vertices() )
        if ( !marked[ v ] )
            dfs( G, -1, v );
}

/***************************************************************************//**
 * @par Description
 *    This function returns the list of bridges, edges are illustrated as
 * vertices.
 *
 * @returns list<pair<int,int>>
 ******************************************************************************/
list<pair<int, int>> Bridges::bridges()
{
    return bridge;
}

/***************************************************************************//**
 * @par Description
 *    The DFS used to find the bridges.
 *
 * @param[in] G - The graph
 * @param[in] prev - The previous vertex
 * @param[in] v - The current vertex
 ******************************************************************************/
void Bridges::dfs(SnakeGraph *G, int prev, int v)
{
    marked[v] = true;
    low[ v ] = ID++;
    id[ v ] = ID++;
    
    for ( int w : G->adj( v ) )
    {
        if ( w == prev ) continue;
        if ( !marked[ w ] )
        {
            dfs( G, v, w );
            low[ v ] = min( low[ w ], low[ v ] );
            if ( id[ v ] < low[ w ] )
                bridge.push_back( pair<int,int>( v, w ) );
        }
        else
            low[ v ] = min( low[ v ], id[ w ] );
    }
}

/***************************************************************************//**
 * @par Description
 *    Returns the number of bridges in the graph.
 *
 * @returns Number of bridges in the graph.
 ******************************************************************************/
int Bridges::count() { return bridge.size(); };
