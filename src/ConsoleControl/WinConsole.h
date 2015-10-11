/*****************************************************************
 * WinConsole.c: Demonstrates using the Win32 console API to 
 * manipulate console output.
 * Program by: NickDMax
 *****************************************************************/

enum ConsoleColor { 
	BLACK=0,
	DBLUE,
	GREEN,
	GREY,
	DRED,
	DPURP,
	BROWN,
	LGREY,
	DGREY,
	BLUE,
	LIMEG,
	TEAL, 
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	B_B };


#ifndef __linux__

#include <windows.h>
#include <stdio.h>




void clearConsole();

int getTextcolor();

int getTextBackground();

void setTextColor(int color);

void setTextBackground( int color );

void setCursorPosition(int x, int y);

#endif
