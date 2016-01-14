// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_WEREWOLF_FUNCTIONS_CPP__
#define __DEFINE_WEREWOLF_FUNCTIONS_CPP__

#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

#include "mapFunctions.cpp"
#include "utilityFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * WEREWOLF CONSTANTS
 */
const char WEREWOLF_SYMBOL_NORMAL = 'W';
const char WEREWOLF_SYMBOL_STUNNED = 'w';
const char WEREWOLF_SYMBOL_DEAD = 'm';
const int WEREWOLF_MAX_DAMAGE = 5;
const int WEREWOLF_POST_DAMAGE_TELEPORT_DISTANCE = 6;
const int WEREWOLF_PICTURE_WIDTH = 36;
const int WEREWOLF_PICTURE_HEIGHT = 12;
const string WEREWOLF_PICTURE[WEREWOLF_PICTURE_HEIGHT] = {
	"             /\\",
	"            ( ;`~v/~~~ ;._",
	"         ,/'\"/^) ' < o\\  '\".~'\\\\\\--,",
	"       ,/\",/W  u '`. ~  >,._..,   )'",
	"      ,/'  w  ,U^v  ;//^)/')/^\\;~)'",
	"   ,/\"'/   W` ^v  W |;         )/'",
	" ;''  |  v' v`\" W }  \\\\",
	"\"    .'\\    v  `v/^W,) '\\)\\.)\\/)",
	"         `\\   ,/,)'   ''')/^\"-;'",
	"              \\",
	"               '\". _",
	"                    \\" };

/*
 * WEREWOLF STATE
 */
int werewolfX;
int werewolfY;
int werewolfHealth = 0;
int werewolfStunnedCount = 0;

/*
 * FUNCTION PROTOTYPES
 */
bool isOpenSpaceForWerewolf(const int, const int);

bool werewolfIsAlive()
{
	if (werewolfHealth > 0)   // If the werewolf has health that is greater than 0,
		return true; // then it will return true.
	else // if <=0, then dead
		return false;

}

bool werewolfIsStunned()
{
	if (werewolfStunnedCount > 0)   // If the werewolf has stun count that is greater than 0,
		return true;   //then it will return true.
	else
		return false;
}

char getWerewolfSymbol()
{
	if (werewolfHealth > 0 && werewolfStunnedCount > 0) // Alive but stunned
		return WEREWOLF_SYMBOL_STUNNED;
	else if (werewolfHealth <= 0) // Dead
		return WEREWOLF_SYMBOL_DEAD;
	else //Normal
		return WEREWOLF_SYMBOL_NORMAL;

}

int doWerewolfHit(const int hitpoints)
{
	if (werewolfHealth > 0)
	{
		werewolfHealth -= hitpoints; //minus hitpoints from werewolf's health
		werewolfStunnedCount += 2;	//then stunnedcount + 2
	}

	return werewolfHealth;
}

void doWerewolfNextMove(const int playerX, const int playerY)
{
	if (werewolfHealth <= 0)	//if dead, can't make any move
		return;
	if (werewolfStunnedCount > 0)	//alive then stunnedcount - 1
	{
		werewolfStunnedCount -= 1;
		return;
	}


	int deltaX = playerX - werewolfX; // distance from werewolf to player in X direction
	int deltaY = playerY - werewolfY; // distance from werewolf to player in Y direction

	int possibleNextX = werewolfX + sign(deltaX); // one square closer to player in X direction
	int possibleNextY = werewolfY + sign(deltaY); // one square closer to player in Y direction

	bool xDirectionMovePossible = (deltaX != 0 && isOpenSpaceForWerewolf(possibleNextX, werewolfY));
	bool yDirectionMovePossible = (deltaY != 0 && isOpenSpaceForWerewolf(werewolfX, possibleNextY));

	if (xDirectionMovePossible && !yDirectionMovePossible)
	{
		werewolfX = possibleNextX;
	}
	else if (!xDirectionMovePossible && yDirectionMovePossible)
	{
		werewolfY = possibleNextY;
	}
	else if (xDirectionMovePossible && yDirectionMovePossible)
	{
		if (abs(deltaX) > abs(deltaY))
		{
			werewolfX = possibleNextX;
		}
		else if (abs(deltaX) < abs(deltaY))
		{
			werewolfY = possibleNextY;
		}
		else
		{
			srand(time(NULL));	//seed random number
			bool randomlyPickX = (rand()%2);	//either 0 or 1 will come out as a result
			if (randomlyPickX)
			{
				werewolfX = possibleNextX;
			}
			else
			{
				werewolfY = possibleNextY;
			}
		}
	}
}

bool isOpenSpaceForWerewolf(const int x, const int y)
{
	char mapSquare = getMapSquare(x, y);
	if (mapSquare == MAP_SQUARE_EMPTY ||	//these are things that the werewolf can talk over
		mapSquare == MAP_SQUARE_KEY ||
		mapSquare == MAP_SQUARE_PEBBLE ||
		mapSquare == MAP_SQUARE_PEBBLES ||
		mapSquare == MAP_SQUARE_PLANK ||
		mapSquare == MAP_SQUARE_PLANK_SET ||
		mapSquare == MAP_SQUARE_ROPE)
	{
		return true;
	}
	else if (mapSquare == MAP_SQUARE_ROCK || mapSquare == MAP_SQUARE_ROPE_TIED)	//werewolf can't walk over rock or tied rope
	{
		return false;
	}

}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE