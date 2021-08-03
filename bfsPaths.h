/***************************************************************************//**
 * @file bfsPaths.h
 ******************************************************************************/
#ifndef __BFSPATHS_H
#define __BFSPATHS_H
#include <list>
#include <map>
#include <queue>
#include "snakeGraph.h"

using namespace std;

/***************************************************************************//**
 * @class BFSPaths
 ******************************************************************************/
class bfsPaths
{
   /// A boolean vector to indicate a vertex was visited during the BFS
   map<int, bool> marked;
   map<int, int> dist;
   map<int, int> prev;
   int s;

public:
   /// Given a graph and a start node, construct the client object
   bfsPaths(SnakeGraph *G, int s);

   /// Answers the question, is there a path from the start to vertex 'v'
   bool hasPath(int v);
   /// Returns the path (from start node to v) of the path if it exists
   std::list<int> pathTo(int v);
   /// Return the distance from the source to vertex 'v'
   int distance(int v);
   map<int, bool> Visited();
   int move( int v );
   
   void colorPath( vector<vector<int>> &grid, int v, int size );
private:
   /// Perform a breadth-first-search starting at node s
   void bfs(SnakeGraph *G, int s);
};
#endif

