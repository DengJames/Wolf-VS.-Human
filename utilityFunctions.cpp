// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_UTILITY_FUNCTIONS_CPP__
#define __DEFINE_UTILITY_FUNCTIONS_CPP__

#include <iostream>
#include <cstdio>
using namespace std;
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

int max(int a, int b)
{
	// returns the maximum of a and b
	return (a >= b ? a : b);
}

int min(const int a, const int b)
{
	// returns the minimum of a and b
	return (a <= b ? a : b);
}

int abs(const int a)
{
	if( a > 0)	//can't use abs(a) because then it would repeated call the function itself
		return a;
	else if ( a < 0 )
		return (-1 * a);
	else
		return 0;
}

int sign(const int a)
{
	if (a > 0)
		return 1;	//positive then 1
	else if (a < 0)
		return -1;	//negative then -1
	else if (a == 0)
		return 0;	// 0 stays the same
}

int manhattanDistance(const int firstX, const int firstY, const int secondX, const int secondY)
{
	// returns the "Manhattan distance" between two points:
	// the difference in their x-coordinates plus the difference in their y-coordinates.
	// this is the equivalent to picking two squares on a chessboard and counting the number of squares between them (without diagonals).
	return (abs(firstX - secondX) + abs(firstY - secondY));
}

void printChar(ostream &stream, const char c, const int times)
{
	// print a character to the screen a certain number of times
	for (int i = 0; i < times; i++)
	{
		stream << c;
	}
}

void intToString(const int value, string &output)
{
	char buffer[11];
	sprintf(buffer, "%d", value);
	output = buffer;
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE