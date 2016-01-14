// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_MAP_FUNCTIONS_CPP__
#define __DEFINE_MAP_FUNCTIONS_CPP__

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#include "utilityFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * MAP CONSTANTS
 */
const char MAP_SQUARE_CHASM     = 'O';
const char MAP_SQUARE_EMPTY     = ' ';
const char MAP_SQUARE_HEALTH    = '+';
const char MAP_SQUARE_KEY       = 'k';
const char MAP_SQUARE_LOCK      = '@';
const char MAP_SQUARE_PEBBLE    = '.';
const char MAP_SQUARE_PEBBLES   = ':';
const char MAP_SQUARE_PLANK     = '=';
const char MAP_SQUARE_PLANK_SET = 'I';
const char MAP_SQUARE_ROCK      = '#';
const char MAP_SQUARE_ROPE      = '&';
const char MAP_SQUARE_ROPE_TIED = '~';
const char MAP_SQUARE_SLINGSHOT = 'Y';

/*
 * MAP STATE
 */
const int MAP_MAX_WIDTH_HEIGHT = 255;
int MAP_WIDTH;
int MAP_HEIGHT;
char MAP[MAP_MAX_WIDTH_HEIGHT][MAP_MAX_WIDTH_HEIGHT] = {{ MAP_SQUARE_EMPTY }};

/*
 * FILE CONSTANTS
 */
const int FILE_INVENTORY_LENGTH = 10;
const char FILE_INVENTORY_ITEM_EMPTY = '\0';
const int FILE_INVENTORY_VALUE_EMPTY = 0;

/*
 * FILE STATE
 */
int FILE_START_LOCATION_X;
int FILE_START_LOCATION_Y;
char FILE_START_LOOKING_DIRECTION;
char FILE_INVENTORY_ITEMS[FILE_INVENTORY_LENGTH];
int FILE_INVENTORY_VALUES[FILE_INVENTORY_LENGTH];
int FILE_WEREWOLF_START_X;
int FILE_WEREWOLF_START_Y;
int FILE_WEREWOLF_START_HEALTH;
int FILE_WEREWOLF_START_STUN_COUNT;

/*
 * FUNCTION PROTOTYPES
 */
void printMapRow(const int, const int, const int, const int, const int, const char,  const int[], const int[], const char[], const int);
char getMapSquare(const int, const int);
bool setMapSquare(const int, const int, const char, const char);
bool clearMapSquare(const int, const int, const char);
bool isOpenSpace(const int, const int);
//deleted bool loadMapFile(string);
bool loadGame(string fileName);
bool saveGame(string fileName, const int, const int, const char, const char[], const int[], const int, const int, const int, const int, const int);	//updated werewolf info

/*
 * FUNCTION IMPLEMENTATIONS
 */

char getMapSquare(const int x, const int y)
{
	char result = MAP_SQUARE_ROCK;
	if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
	{
		result = MAP[x][y];	//might not be this simple..maybe use 2-d array
	}
	return result;
}

bool setMapSquare(const int x, const int y, const char currentValue, const char newValue)
{
	bool result = false;

	if (x >= 0 && x < MAP_WIDTH &&
		y >= 0 && y < MAP_HEIGHT &&
		getMapSquare(x, y) == currentValue)
	{
		MAP[x][y] = newValue;	//set the map to newValue
		result = true;
	}

	return result;
}

bool clearMapSquare(const int x, const int y, const char currentValue)
{
	return setMapSquare(x, y, currentValue, MAP_SQUARE_EMPTY);
}

bool isOpenSpace(const int x, const int y)
{
	char mapSquare = getMapSquare(x, y);
	return (mapSquare == MAP_SQUARE_EMPTY     ||
			mapSquare == MAP_SQUARE_PLANK_SET ||
			mapSquare == MAP_SQUARE_ROPE_TIED);
}

bool canSeePast(const int x, const int y)
{
	char mapSquare = getMapSquare(x, y);
	if (mapSquare == MAP_SQUARE_EMPTY ||
		mapSquare == MAP_SQUARE_CHASM ||
		mapSquare == MAP_SQUARE_KEY ||
		mapSquare == MAP_SQUARE_PEBBLE ||
		mapSquare == MAP_SQUARE_PEBBLES ||
		mapSquare == MAP_SQUARE_PLANK ||
		mapSquare == MAP_SQUARE_PLANK_SET ||
		mapSquare == MAP_SQUARE_ROPE ||
		mapSquare == MAP_SQUARE_ROPE_TIED ||
		mapSquare == MAP_SQUARE_SLINGSHOT)	//only things listed here can be seen through
	{
		return true;
	}
	else
	{
		return false;
	}
}

void printMapRow(const int centerX, const int centerY, const int rowOffset, const int screenWidth, const int screenRadius, const int specialXs[], const int specialYs[], const char specialChars[], const int specialsLength)
{
	const int row = centerY - screenRadius + rowOffset;
	for (int col = centerX - screenRadius; col <= centerX + screenRadius; col++)
	{
		bool isSpecial = false;
		for (int i = 0; i < specialsLength; i++)
		{
			if (row == specialYs[i] && col == specialXs[i])
			{
				cout << specialChars[i];
				isSpecial = true;
				break;
			}
		}
		if (!isSpecial)
		{
			if (row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH)
			{
				cout << MAP[row][col];
			}
			else
			{
				cout << MAP_SQUARE_ROCK;
			}
		}
	}
}

bool loadGame(string fileName)
{
	bool success = false;

	ifstream file;
	file.open(fileName.c_str());
	if (!file.fail())
	{
		int mapWidth, mapHeight, playerLocationX, playerLocationY, werewolfX, werewolfY, werewolfHealth, werewolfStunCount;	//werewolf information added
		char lookingDirection;
		file >> mapWidth >> mapHeight >> playerLocationX >> playerLocationY >> lookingDirection >> werewolfX >> werewolfY >> werewolfHealth >> werewolfStunCount;
		if (mapWidth > 0 && mapHeight > 0)
		{
			char buffer = ' ';
			char tempMap[MAP_MAX_WIDTH_HEIGHT][MAP_MAX_WIDTH_HEIGHT];
			int charactersRead = 0;

			for (int i = 0; i < mapWidth * mapHeight; i++)
			{

				file.get(buffer);	//read each element of the 2-d array to the buffer
				if (file.fail())
				{
					break;
				}
				else if (buffer == '\0' || buffer == '\n' || buffer == '\r')
				{
					i--;
					continue;
				}
				
				int row = i / mapHeight;	//keep track on the row
				int col = i % mapWidth;		//keep track on the col
				tempMap[row][col] = buffer; 
				charactersRead++;
			}

			if (charactersRead == mapWidth * mapHeight)
			{
				for (int i = 0; i < mapHeight; i++)
				{
					for (int j = 0; j < mapWidth; j++)
					{
						MAP[i][j] = tempMap[i][j];
					}
				}
				MAP_WIDTH = mapWidth;
				MAP_HEIGHT = mapHeight;
				FILE_START_LOCATION_X = playerLocationX;
				FILE_START_LOCATION_Y = playerLocationY;
				FILE_START_LOOKING_DIRECTION = lookingDirection;
				FILE_WEREWOLF_START_X = werewolfX;
				FILE_WEREWOLF_START_Y = werewolfY;
				FILE_WEREWOLF_START_HEALTH = werewolfHealth;
				FILE_WEREWOLF_START_STUN_COUNT = werewolfStunCount;

				if (!file.fail())
				{
					char item;
					int value;

					for (int i = 0; i < FILE_INVENTORY_LENGTH; i++)
					{
						if (file.fail())
						{
							FILE_INVENTORY_ITEMS[i] = FILE_INVENTORY_ITEM_EMPTY;
							FILE_INVENTORY_VALUES[i] = FILE_INVENTORY_VALUE_EMPTY;
							continue;
						}

						file >> item;
						if (file.fail())
						{
							i--;
							continue;
						}

						file >> value;
						if (file.fail())
						{
							i--;
							continue;
						}

						FILE_INVENTORY_ITEMS[i] = item;
						FILE_INVENTORY_VALUES[i] = value;
					}
				}

				success = true;
			}
		}
	}

	file.close();

	return success;
}

bool saveGame(string fileName, const int playerX, const int playerY, const char lookingDirection,
			  const char inventoryItems[], const int inventoryValues[], const int inventoryLength,
			  const int werewolfX, const int werewolfY, const int werewolfHealth, const int werewolfStunnedCount)	//werewolf info added to saveGame
{
	bool success = false;

	ofstream file;
	file.open(fileName.c_str());
	if (!file.fail())
	{
		// write map dimensions and player location and other necessary information
		file << MAP_WIDTH << ' ' << MAP_HEIGHT << ' ' << playerX << ' ' << playerY << ' ' << lookingDirection
			 << ' ' << werewolfX << ' ' << werewolfY << ' ' << werewolfHealth << ' ' << werewolfStunnedCount << endl;

		// write map
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				file << MAP[i][j];	//save in each element of the 2-d array
			}
			file << endl;
		}

		// write inventory
		for (int i = 0; i < inventoryLength; i++)
		{
			file << inventoryItems[i] << ' ' << inventoryValues[i] << endl;
		}

		success = !file.fail();
	}

	file.close();

	return success;
}

void loadDefaultMap()
{
	MAP_WIDTH = 5;
	MAP_HEIGHT = 3;
	strcpy(MAP[0], "&.@:=");
	strcpy(MAP[1], "     ");
	strcpy(MAP[2], "OYO k");
	FILE_START_LOCATION_X = 4;
	FILE_START_LOCATION_Y = 1;
	FILE_START_LOOKING_DIRECTION = '<';
	FILE_WEREWOLF_START_X = 0;
	FILE_WEREWOLF_START_Y = 1;
	FILE_WEREWOLF_START_HEALTH = 1;
	FILE_WEREWOLF_START_STUN_COUNT = 0;
}

bool getRandomEmptyLocation(const int playerX, const int playerY, const int minDistanceFromPlayer, int& emptyLocationX, int& emptyLocationY) //last two pass by reference
{
	int numberOfEmptyLocations = 0;
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int col = 0; col < MAP_WIDTH; col++)
		{
			if (MAP[row][col] == MAP_SQUARE_EMPTY && manhattanDistance(playerX, playerY, col, row) >= minDistanceFromPlayer)
			{
				numberOfEmptyLocations++;
			}
		}
	}

	if (numberOfEmptyLocations == 0)
	{
		return false;
	}

	srand(time(NULL));	// seed random number
	const int stopAfterThisMany = (rand() % numberOfEmptyLocations);	//random # picked from the possible # of empty locations
	numberOfEmptyLocations = 0;
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int col = 0; col < MAP_WIDTH; col++)
		{
			if (MAP[row][col] == MAP_SQUARE_EMPTY && manhattanDistance(playerX, playerY, col, row) >= minDistanceFromPlayer)
			{
				numberOfEmptyLocations++;
				if (numberOfEmptyLocations == stopAfterThisMany)
				{
					emptyLocationX = col;
					emptyLocationY = row;
					return true;
				}
			}
		}
	}

	return false;
}

bool twoLocationsVisibleToEachOther(const int firstX, const int firstY, const int secondX, const int secondY)
{
	bool areVisible = true;
	if (firstX == secondX)
	{
		int direction = sign(secondY - firstY);
		for (int i = firstY + direction; i != secondY; i += direction)
		{
			if (!canSeePast(secondX, secondY))	//player and werewolf need to be able to see each other so that they can be visible to each other
			{
				areVisible = false;
				break;
			}
		}
	}
	else if (firstY == secondY)
	{
		int direction = sign(secondX - firstX);
		for (int i = firstX + direction; i != secondX; i += direction)
		{
			if (!canSeePast(secondX, secondY))	//player and werewolf need to be able to see each other so that they can be visible to each other
			{
				areVisible = false;
				break;
			}
		}
	}
	else
	{
		areVisible = false;
	}
	return areVisible;
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE