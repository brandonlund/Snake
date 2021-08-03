/***************************************************************************//**
 * @file astar.h
 ******************************************************************************/
#ifndef __ASTAR_H
#define __ASTAR_H
#include <list>
#include <map>
#include <queue>
#include <limits>
#include <cmath>
#include <iostream>
#include "snakeGraph.h"

using namespace std;

struct Node
{
    int vertex;
    double overallDist;
    Node(int v, double o) : vertex(v), overallDist(o) {}
};

/***************************************************************************//**
 * @class nodeCompare
 ******************************************************************************/
class nodeCompare
{
    public:
        bool operator()(const Node &lhs, const Node &rhs)
        {
            return (lhs.overallDist< rhs.overallDist);
        }
};

/***************************************************************************//**
 * @class AStar
 ******************************************************************************/
class AStar
{
    map<int, bool> marked;
    map<int, int> prev;
    map<int, int> dist;
    map<int, double> heuristic;
    priority_queue<Node, vector<Node>, nodeCompare> heap;
    int start, finish, columns;
    
    public:
        AStar( SnakeGraph *, int, int );
        bool hasPath(int);
        list<int> pathTo(int);
        int move( int v );
        void colorPath( vector<vector<int>> &grid, int v, int size );
        
    private:
        void relax( int, int, SnakeGraph * );
        double straightLineDistance( int, int, int );
};

#endif
