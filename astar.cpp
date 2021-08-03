/***************************************************************************//**
 * @file astar.cpp
 ******************************************************************************/
#include "astar.h"


/***************************************************************************//**
 * @par Description
 *    The constructor. Does the A* algorithm.
 * 
 * @param[in] G - The graph
 * @param[in] s - The starting vertex
 * @param[in] f - The finish/end vertex
 *
 ******************************************************************************/
AStar::AStar( SnakeGraph *G, int s, int f ) : start(s), finish(f)
{
    for ( int v : G->Vertices() )
        dist[ v ] = numeric_limits<int>::max();
    
    dist[start] = 0.0;
    heap.push( Node( start, straightLineDistance( start, finish, G->Columns() ) ) );
    
    while ( !heap.empty() )
    {
        Node node = heap.top();
        heap.pop();
        
        for ( int w : G->adj( node.vertex ) )
            relax( node.vertex, w, G );
    }
}


/***************************************************************************//**
 * @par Description
 *    The relax function. Relax's a vertices' distance if it is lower than its
 * previous.
 * 
 * @param[in] v - The current vertex
 * @param[in] w - The vertex being updated
 * @param[in] G - The graph
 *
 ******************************************************************************/
void AStar::relax( int v, int w, SnakeGraph *G )
{
    if ( dist[ w ] > dist[ v ] + 1 )
    {
        dist[ w ] = dist[ v ] + 1;
        prev[ w ] = v;
        marked[ w ] = true;
        heap.push( Node( w, straightLineDistance( w, finish, G->Columns() ) ) );
    }
}


/***************************************************************************//**
 * @par Description
 *    Returns whether or not the A* algorithm found a path.
 * 
 * @param[in] v - The vertex in question
 *
 * @returns True if there is a path, false otherwise
 *
 ******************************************************************************/
bool AStar::hasPath( int v )
{
    return dist[ v ] != numeric_limits<int>::max();
}


/***************************************************************************//**
 * @par Description
 *    Returns the path to the finish vertex.
 * 
 * @param[in] v - The vertex in question
 *
 * @returns list<int> List will be empty if there is no path.
 *
 ******************************************************************************/
list<int> AStar::pathTo( int v )
{
    std::list<int> path;
    if ( !hasPath( v ) ) return path;
    for ( int x = v ; x != start ; x = prev[ x ] )
       path.push_front( x );
    path.push_front( start );
    return path;
}


/***************************************************************************//**
 * @par Description
 *    Calculates the straight line distance between the start and end nodes
 * using Pythagorean's theorem.
 * 
 * @param[in] s - The start vertex
 * @param[in] f - The end vertex
 * @param[in] width - The width of the playing field/graph
 *
 * @returns The straight line distance from s to f.
 *
 ******************************************************************************/
double AStar::straightLineDistance( int s, int f, int width )
{
    int sx = s % width;
    int sy = s / width;
    int fx = f % width;
    int fy = f / width;
    int dx = fx - sx;
    int dy = fy - sy;
    int d_squ = (dx*dx) + (dy*dy);
    
    return sqrt((double)d_squ);
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
int AStar::move(int v)
{
    std::list<int> m = pathTo( v );
    m.pop_front();
    return m.front();
}

void AStar::colorPath( vector<vector<int>> &grid, int v, int size )
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

