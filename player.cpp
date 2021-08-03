/********************************************************************//**
* @file player.cpp
***********************************************************************/
#include "player.h"
#include "iostream"

using namespace std;

/***************************************************************************//**
 * @par Description
 *    Constructor
 ******************************************************************************/
Player::Player() { }

/***************************************************************************//**
 * @par Description
 *    Quite a simple snake algorithm. Uses A* as long as there are no bridges
 * which then reverts to BFS if there are bridges. Otherwise, it basically
 * ends up being brute force tail management until there is a path available.
 * 
 * @param[in] pf - The playing field.
 *
 ******************************************************************************/
ValidMove Player::makeMove( Playfield *pf)
{
    std::vector<std::vector<int>> grid = pf->getGrid();
    std::pair<int, int> head = pf->headPosition();
    std::pair<int, int> food = pf->foodPosition();

    int head_index = head.first * grid[0].size() + head.second;
    int food_index = food.first * grid[0].size() + food.second;
    int dY = head.first - food.first;
    int dX = head.second - food.second;
    SnakeGraph *G = new SnakeGraph(grid);
    bfsPaths bfs(G, head_index);
    AStar astar( G, head_index, food_index );
    dfsPaths dfs( G, head_index );
    Bridges bridges( G );
    
    if ( astar.hasPath( food_index ) && bridges.count() <= 1 )
    {
        int move_index = astar.move( food_index );
        
        // color the path
        astar.colorPath( grid, food_index, grid[0].size() );
        pf->grid = grid;
        
        if ( move_index == head_index - 1 )
        {
            delete G;
            return LEFT;
        }
        if ( move_index == head_index + 1 )
        {
            delete G;
            return RIGHT;
        }
        if ( move_index == (int)(head_index - grid[0].size()) )
        {
            delete G;
            return UP;
        }
        if ( move_index == (int)(head_index + grid[0].size()) )
        {
            delete G;
            return DOWN;
        }
    }
    
    if ( bfs.hasPath( food_index ) )
    {
        int move_index = bfs.move( food_index );
        
        // color the path
        bfs.colorPath( grid, food_index, grid[0].size() );
        pf->grid = grid;
        
        if ( move_index == head_index - 1 )
        {
            delete G;
            return LEFT;
        }
        if ( move_index == head_index + 1 )
        {
            delete G;
            return RIGHT;
        }
        if ( move_index == (int)(head_index - grid[0].size()) )
        {
            delete G;
            return UP;
        }
        if ( move_index == (int)(head_index + grid[0].size()) )
        {
            delete G;
            return DOWN;
        }
    }
    
    delete G;
    
    // Don't go to the food if the food is trapped.... That's stupid!
    // This first part leaves a space on the edges of the board so it can get
    // out if it gets to a side.
    if ( head.first > 1
        && grid[head.first-1][head.second] != 1
        && grid[head.first-1][head.second] != 8
        && grid[head.first-1][head.second] != 16
        && grid[head.first-2][head.second] != 1
        && grid[head.first-2][head.second] != 8
        && grid[head.first-2][head.second] != 16 )
        return UP;
    if ( head.first < (int)grid.size() - 3
        && grid[head.first+1][head.second] != 1
        && grid[head.first+1][head.second] != 8
        && grid[head.first+1][head.second] != 16
        && grid[head.first+2][head.second] != 1
        && grid[head.first+2][head.second] != 8
        && grid[head.first+2][head.second] != 16 )
        return DOWN;
    if ( head.second > 1
        && grid[head.first][head.second-1] != 1
        && grid[head.first][head.second-1] != 8
        && grid[head.first][head.second-1] != 16
        && grid[head.first][head.second-2] != 1
        && grid[head.first][head.second-2] != 8
        && grid[head.first][head.second-2] != 16 )
        return LEFT;
    if ( head.second < (int)grid[0].size() - 3
        && grid[head.first][head.second+1] != 1
        && grid[head.first][head.second+1] != 8
        && grid[head.first][head.second+1] != 16
        && grid[head.first][head.second+2] != 1
        && grid[head.first][head.second+2] != 8
        && grid[head.first][head.second+2] != 16 )
        return RIGHT;
        
    // This second part is basically last resort and uses the edges closest
    // to the border to return to a larger playing field.
    if ( head.first > 0
        && grid[head.first-1][head.second] != 1
        && grid[head.first-1][head.second] != 8
        && grid[head.first-1][head.second] != 16 )
        return UP;
    if ( head.first < (int)grid.size()-2
        && grid[head.first+1][head.second] != 1
        && grid[head.first+1][head.second] != 8
        && grid[head.first+1][head.second] != 16 )
        return DOWN;
    if ( head.second > 0
        && grid[head.first][head.second-1] != 1
        && grid[head.first][head.second-1] != 8
        && grid[head.first][head.second-1] != 16 )
        return LEFT;
    if ( head.second < (int)grid[0].size()-2
        && grid[head.first][head.second+1] != 1
        && grid[head.first][head.second+1] != 8
        && grid[head.first][head.second+1] != 16 )
        return RIGHT;
    
    
    if (dX == 0) // in the correct column
    {
        if (dY > 0) // Above the food
            return UP;
        else
            return DOWN;
    }
    else // Not in the correct column
    { 
        if (dX > 0) // I'm to the right of the food
            return LEFT;
        else // I'm to the left of the food
            return RIGHT;
    }
    return NONE;
}

