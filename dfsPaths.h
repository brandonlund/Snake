/***************************************************************************//**
 * @file dfsPaths.h
 ******************************************************************************/
#ifndef __DFSPATHS_H
#define __DFSPATHS_H
#include <queue>
#include <list>
#include <map>
#include <vector>
#include "defines.h"
#include "snakeGraph.h"

/***************************************************************************//**
 * @class BFSPaths
 ******************************************************************************/
class dfsPaths
{
    std::map<int, bool> marked;
    std::map<int, int> prev;
    int s;

public:
    dfsPaths(SnakeGraph *G, int s);

    bool hasPath(int v);
    std::list<int> pathTo(int v);
    int move( int v );
    void colorPath( std::vector<std::vector<int>> &grid, int v, int size );

private:
    void dfs(SnakeGraph *, int);
};


#endif
