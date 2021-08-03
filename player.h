/***************************************************************************//**
 * @file player.h
 ******************************************************************************/

#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include <queue>
#include <map>
#include <limits>
#include "playfield.h"
#include "dfsPaths.h"
#include "bfsPaths.h"
#include "bridges.h"
#include "astar.h"
#include "biconnected.h"

/***************************************************************************//**
 * @class Player
 ******************************************************************************/
class Player
{
public:
    Player();
    ValidMove makeMove( Playfield *);
private:
};
#endif
