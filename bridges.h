/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef BRIDGES_H
#define BRIDGES_H
#include <list>
#include <map>
#include "snakeGraph.h"

using namespace std;

/********************************************************************//**
 * @class Bridges
 **********************************************************************/
class Bridges
{
   map<int, int> id;
   map<int, int> low;
   map<int, bool> marked;
   list<pair<int, int>> bridge;
   int ID;
public:
   Bridges(SnakeGraph *);
   int count();
   list<pair<int, int>> bridges();

private:
   void dfs(SnakeGraph *, int, int);
};
#endif

