// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_SCREEN_FUNCTIONS_CPP__
#define __DEFINE_SCREEN_FUNCTIONS_CPP__

#include <iostream>
using namespace std;

#include "interactionFunctions.cpp"
#include "mapFunctions.cpp"
#include "playerFunctions.cpp"
#include "utilityFunctions.cpp"
#include "werewolfFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * SCREEN CONSTANTS AND SETTINGS
 */
const int SCREEN_MAP_RADIUS = 7;
const int SCREEN_MAP_WIDTH_HEIGHT = SCREEN_MAP_RADIUS * 2 + 1;
const int SCREEN_INVENTORY_WIDTH = 22;
const int SCREEN_PICTURE_WIDTH = SCREEN_MAP_WIDTH_HEIGHT + SCREEN_INVENTORY_WIDTH + 1; // 3 for the frame chars

/*
 * FUNCTION PROTOTYPES
 */
void clearScreen();
void printScreen();
// deleted void printChar(ostream&, const char, const int);

void clearScreen()
{
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
	}
}

void printScreen()
{
	const int SPECIALS_COUNT = 2;
	const int SPECIAL_XS[SPECIALS_COUNT] = { playerX, werewolfX };
	const int SPECIAL_YS[SPECIALS_COUNT] = { playerY, werewolfY };
	const char SPECIAL_CHARS[SPECIALS_COUNT] = { getPlayerSymbol(), getWerewolfSymbol() };

	const char FRAME_TOP_CORNER = ',';
	const char FRAME_MIDDLE_CORNER = '+';
	const char FRAME_BOTTOM_CORNER = '\'';
	const char FRAME_SIDE_HORIZONTAL = '-';
	const char FRAME_SIDE_VERTICAL = '|';

	if (twoLocationsVisibleToEachOther(playerX, playerY, werewolfX, werewolfY))
	{
		int leftMargin = (SCREEN_PICTURE_WIDTH - WEREWOLF_PICTURE_WIDTH) / 2;
		int rightMargin = SCREEN_PICTURE_WIDTH - WEREWOLF_PICTURE_WIDTH - leftMargin;

		// draw top of frame
		cout << FRAME_TOP_CORNER;
		printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_PICTURE_WIDTH);
		cout << FRAME_TOP_CORNER << endl;

		// draw werewolf picture
		for (int i = 0; i < WEREWOLF_PICTURE_HEIGHT; i++)
		{
			cout << FRAME_SIDE_VERTICAL;
			printChar(cout, ' ', leftMargin);
			cout << left << setw(WEREWOLF_PICTURE_WIDTH) << WEREWOLF_PICTURE[i].c_str();
			printChar(cout, ' ', rightMargin);
			cout << FRAME_SIDE_VERTICAL << endl;
		}
		
		// draw middle of frame
		cout << FRAME_MIDDLE_CORNER;
		printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_MAP_WIDTH_HEIGHT);
		cout << FRAME_MIDDLE_CORNER;
		printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_INVENTORY_WIDTH);
		cout << FRAME_MIDDLE_CORNER << endl;
	}
	else
	{
		// draw top of frame
		cout << FRAME_TOP_CORNER;
		printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_MAP_WIDTH_HEIGHT);
		cout << FRAME_TOP_CORNER;
		printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_INVENTORY_WIDTH);
		cout << FRAME_TOP_CORNER << endl;
	}

	// draw frame, map, and inventory
	for (int row = 0; row < SCREEN_MAP_WIDTH_HEIGHT; row++)
	{
		cout << FRAME_SIDE_VERTICAL;
		printMapRow(playerX, playerY, row, SCREEN_MAP_WIDTH_HEIGHT, SCREEN_MAP_RADIUS, SPECIAL_XS, SPECIAL_YS, SPECIAL_CHARS, SPECIALS_COUNT);
		cout << FRAME_SIDE_VERTICAL;
		if (!printInventoryRow(row, SCREEN_INVENTORY_WIDTH))
		{
			printChar(cout, ' ', SCREEN_INVENTORY_WIDTH);
		}
		cout << FRAME_SIDE_VERTICAL << endl;
	}

	// draw bottom of frame
	cout << FRAME_BOTTOM_CORNER;
	printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_MAP_WIDTH_HEIGHT);
	cout << FRAME_BOTTOM_CORNER;
	printChar(cout, FRAME_SIDE_HORIZONTAL, SCREEN_INVENTORY_WIDTH);
	cout << FRAME_BOTTOM_CORNER << endl;

	// messaging below frame
	cout << endl << lastMessage.c_str() << endl << endl << "You are at (" << playerX << "," << playerY << "). Enter a command: ";
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE