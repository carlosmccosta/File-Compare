#ifndef __linux__

#include "stdafx.h"
#include "WinConsole.h"





static int current_text_colors = 07;

int getTextcolor()
{
	return current_text_colors & 0x0F;
}

int getTextBackground()
{
	return (current_text_colors >> 4) & 0x0F;
}

void setTextColor( int color )
{
	current_text_colors = (current_text_colors & 0xF0) | (color & 0x0F);
	SetConsoleTextAttribute(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		current_text_colors
		);
}

void setTextBackground( int color )
{
	current_text_colors = (current_text_colors & 0x0F) | ((color & 0x0F) << 4);
	SetConsoleTextAttribute(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		current_text_colors
		);
}

void setCursorPosition(int x, int y)
{
	COORD coord = {x, y};
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, coord); 
}


//Para apagar todo o conteúdo da consola
void clearConsole()
{
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

     //Faz reset do cursor para o canto superior esquerdo
     COORD coord = {0, 0};

     DWORD count;    
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //Vai usar a cor actual
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {          
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
		            
          SetConsoleCursorPosition(hStdOut, coord);
     }
}

#endif
