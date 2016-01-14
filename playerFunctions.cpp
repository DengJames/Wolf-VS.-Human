// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_PLAYER_FUNCTIONS_CPP__
#define __DEFINE_PLAYER_FUNCTIONS_CPP__

#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

#include "mapFunctions.cpp"
#include "utilityFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * PLAYER STATE CONSTANTS
 */
const char LOOKING_UP = '^';
const char LOOKING_DOWN = 'v';
const char LOOKING_LEFT = '<';
const char LOOKING_RIGHT = '>';
const char LOOKING_DEAD = 'X';
const int INVENTORY_INDEX_HEALTH = 0;
const int INVENTORY_INDEX_KEYS = 1;
const int INVENTORY_INDEX_PEBBLES = 2;
const int INVENTORY_INDEX_PLANK = 3;
const int INVENTORY_INDEX_ROPE = 4;
const int INVENTORY_INDEX_SLINGSHOT = 5;
const int INVENTORY_LENGTH = 6;
const int SLINGSHOT_DISTANCE = 4;
const int SLINGSHOT_MAX_DAMAGE = 3;

/*
 * PLAYER STATE
 */
int playerX, playerY;
char playerSymbol;
int INVENTORY_ARRAY[INVENTORY_LENGTH] = { 0, 0, 0, 0, 0, 0 };

/*
 * FUNCTION PROTOTYPES
 */
int getlookingatdirection(const int, const int, const char, int&, int&);
void inventoryAdd(const char);
bool inventoryHas(const char);
bool inventoryUse(const char);
void inventorySet(const char[], const int[], const int);
bool printInventoryRow(const int, const int);
int convertMapSquareToInventoryIndex(const char);
char convertInventoryIndexToItemChar(const int);

void getLookingAtLocation(const int currentX, const int currentY, const char currentSymbol, int& lookingAtX, int& lookingAtY)	//reference because need to return values
{
	// DO NOT CHANGE THE FUNCTION NAME OR RETURN TYPE.
	// DO NOT CHANGE THE LEFT THREE PARAMETERS.

	// ADD NECESSARY PARAMETERS.
	// ADD MISSING CODE.
	switch(currentSymbol)
	{
		case LOOKING_LEFT:
			lookingAtX = currentX;	//lookingAtX and lookingAtY need to first get values from currentX and currentY
			lookingAtX -= 1;
			break;
		case LOOKING_RIGHT:
			lookingAtX = currentX;
			lookingAtX += 1;
			break;
		case LOOKING_UP:
			lookingAtY = currentY;
			lookingAtY -= 1;
			break;
		case LOOKING_DOWN:
			lookingAtY = currentY;
			lookingAtY += 1;
			break;
		default:
			lookingAtX = currentX;
			lookingAtY = currentY;
	}
}

int doPlayerHit(const int hitpoints)
{
	INVENTORY_ARRAY[INVENTORY_INDEX_HEALTH] = max(0, INVENTORY_ARRAY[INVENTORY_INDEX_HEALTH] - hitpoints);
	return INVENTORY_ARRAY[INVENTORY_INDEX_HEALTH];
}

bool playerIsAlive()
{
	return (INVENTORY_ARRAY[INVENTORY_INDEX_HEALTH] > 0);
}

char getPlayerSymbol()
{
	return (playerIsAlive() ? playerSymbol : LOOKING_DEAD);
}

void inventoryAdd(const char item)
{
	int inventoryIndex = convertMapSquareToInventoryIndex(item);
	if (inventoryIndex >= 0)
	{
		switch(item)
		{
			case MAP_SQUARE_HEALTH:
			case MAP_SQUARE_KEY:
			case MAP_SQUARE_PEBBLE:
			case MAP_SQUARE_PLANK:
			case MAP_SQUARE_ROPE:
				INVENTORY_ARRAY[inventoryIndex] += 1;
				break;
			case MAP_SQUARE_PEBBLES:
				INVENTORY_ARRAY[inventoryIndex] += 2;
				break;
			case MAP_SQUARE_SLINGSHOT:
				INVENTORY_ARRAY[inventoryIndex] = 1;
				break;
		}
	}
}

bool inventoryHas(const char item, const int count)
{
	int inventoryIndex = convertMapSquareToInventoryIndex(item);
	return (inventoryIndex >= 0 && INVENTORY_ARRAY[inventoryIndex] >= count);
}

bool inventoryHas(const char item)
{
	return inventoryHas(item, 1);
}

bool inventoryUse(const char item, const int count)
{
	bool success = false;

	int inventoryIndex = convertMapSquareToInventoryIndex(item);
	if (inventoryIndex >= 0)
	{
		switch(inventoryIndex)
		{
			case INVENTORY_INDEX_HEALTH:
			case INVENTORY_INDEX_KEYS:
			case INVENTORY_INDEX_PEBBLES:
			case INVENTORY_INDEX_PLANK:
			case INVENTORY_INDEX_ROPE:
				if (INVENTORY_ARRAY[inventoryIndex] > 0)
				{
					INVENTORY_ARRAY[inventoryIndex] -= count;
					success = true;
				}
				break;
			case INVENTORY_INDEX_SLINGSHOT:
				if (INVENTORY_ARRAY[inventoryIndex] > 0)
				{
					success = true;
				}
				break;
		}
	}

	return success;
}

bool inventoryUse(const char item)
{
	return inventoryUse(item, 1);
}

void inventorySet(const char newInventoryItems[], const int newInventoryValues[], const int count)
{
	for (int i = 0; i < INVENTORY_LENGTH; i++)
	{
		bool itemIsInNewList = false;

		for (int j = 0; j < count; j++)
		{
			int index = convertMapSquareToInventoryIndex(newInventoryItems[j]);
			if (index == i)
			{
				INVENTORY_ARRAY[index] = newInventoryValues[j];
				itemIsInNewList = true;
				break;
			}
		}

		if (!itemIsInNewList)
		{
			INVENTORY_ARRAY[i] = 0;
		}
	}
}

bool printInventoryRow(const int row, const int displayWidth)
{
	bool success = false;

	const int extraSpaceWidth = 1;
	const int symbolWidth = max(0, min(2, displayWidth));
	const int numberWidth = max(0, min(4, displayWidth - symbolWidth));
	const int nameWidth = max(0, displayWidth - (numberWidth + symbolWidth + extraSpaceWidth));

	switch(row)
	{
		case 1:
		{
			int itemIndex = INVENTORY_INDEX_KEYS;
			int count = INVENTORY_ARRAY[itemIndex];
			if (count > 0)
			{
				cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) << setw(nameWidth) << "Key";
				success = true;
			}
			break;
		}
		case 2:
		{
			int itemIndex = INVENTORY_INDEX_ROPE;
			int count = INVENTORY_ARRAY[itemIndex];
			if (count > 0)
			{
				cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) << setw(nameWidth) << "Rope";
				success = true;
			}
			break;
		}
		case 3:
		{
			int itemIndex = INVENTORY_INDEX_PLANK;
			int count = INVENTORY_ARRAY[itemIndex];
			if (count > 0)
			{
				cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) << setw(nameWidth) << "Wood Plank";
				success = true;
			}
			break;
		}
		case 5:
		{
			bool hasSlingshot = INVENTORY_ARRAY[INVENTORY_INDEX_SLINGSHOT] > 0;
			int itemIndex = INVENTORY_INDEX_PEBBLES;
			int count = INVENTORY_ARRAY[itemIndex];
			if (hasSlingshot)
			{
				cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << MAP_SQUARE_SLINGSHOT << setw(nameWidth) << "Slingshot";
				success = true;
			}
			else if (count > 0)
			{
				cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) << setw(nameWidth) << "Pebble";
				success = true;
			}
			break;
		}
		case 9:
		{
			int itemIndex = INVENTORY_INDEX_HEALTH;
			int count = INVENTORY_ARRAY[itemIndex];
			cout << right << setw(numberWidth) << count << left << ' ' << setw(symbolWidth) << convertInventoryIndexToItemChar(itemIndex) << setw(nameWidth) << "Health";
			success = true;
			break;
		}
	}

	return success;
}

int convertMapSquareToInventoryIndex(const char mapSquare)
{
	switch(mapSquare)
	{
		case MAP_SQUARE_HEALTH:
			return INVENTORY_INDEX_HEALTH;
		case MAP_SQUARE_KEY:
			return INVENTORY_INDEX_KEYS;
		case MAP_SQUARE_PEBBLE:
		case MAP_SQUARE_PEBBLES:
			return INVENTORY_INDEX_PEBBLES;
		case MAP_SQUARE_PLANK:
			return INVENTORY_INDEX_PLANK;
		case MAP_SQUARE_ROPE:
			return INVENTORY_INDEX_ROPE;
		case MAP_SQUARE_SLINGSHOT:
			return INVENTORY_INDEX_SLINGSHOT;
	}
	return -1;
}

char convertInventoryIndexToItemChar(const int index)
{
	switch(index)
	{
		case INVENTORY_INDEX_HEALTH:
			return MAP_SQUARE_HEALTH;
		case INVENTORY_INDEX_KEYS:
			return MAP_SQUARE_KEY;
		case INVENTORY_INDEX_PEBBLES:
			return MAP_SQUARE_PEBBLE;
		case INVENTORY_INDEX_PLANK:
			return MAP_SQUARE_PLANK;
		case INVENTORY_INDEX_ROPE:
			return MAP_SQUARE_ROPE;
		case INVENTORY_INDEX_SLINGSHOT:
			return MAP_SQUARE_SLINGSHOT;
	}
	return ' ';
}

void getFarthestActionableLocation(const int maxActionDistance, const bool mustBeEmpty, int &locationX, int &locationY)
{
	locationX = playerX;
	locationY = playerY;
	int nextX, nextY, farthestEmptyX = playerX, farthestEmptyY = playerY;
	for (int i = 0; i < maxActionDistance; i++)
	{
		/* _SEE_ HOW FAR YOU CAN THROW SOMETHING. */
		do
		{
		++farthestEmptyX;
		++farthestEmptyY;
		} while (canSeePast(farthestEmptyX, farthestEmptyY));	//keep testing farther if can see that far
		
		/* IF YOU NEED IT EMPTY AND YOU CAN _SEE_ THAT FAR, TRY FARTHER. */
		if (canSeePast(farthestEmptyX, farthestEmptyY) && mustBeEmpty)
		{
			++farthestEmptyX;
			++farthestEmptyY;
		}
		/* IF YOU CANNOT SEE THAT FAR, STOP. */
		if (!canSeePast(farthestEmptyX, farthestEmptyY))
			break;
	}

	if (mustBeEmpty)
	{
		locationX = farthestEmptyX;
		locationY = farthestEmptyY;
	}
}

bool playerIsLookingAt(const int x, const int y)
{
	if(canSeePast(x, y) && (x == playerX || y == playerY))	//player's x needs to be in the same line with the location's x; same for y
	{
		return true;
	}
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE