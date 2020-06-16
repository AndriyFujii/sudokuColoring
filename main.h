#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <math.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define KEY_ENTER 13

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

//Changes writing color
void textcolor(int text, int background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(text | background << 4));
}

//Jumps to position x,y in the cmd
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Prints the sudoku grids
void printGrid(int N)
{
    if (N == 4)
    {
        std::cout << " n  n | n  n " << '\n';
        std::cout << " n  n | n  n " << '\n';
        std::cout << "------|------" << '\n';
        std::cout << " n  n | n  n " << '\n';
        std::cout << " n  n | n  n " << '\n';
    }
    else if (N == 9)
    {
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << "---------|---------|---------" << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << "---------|---------|---------" << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
        std::cout << " n  n  n | n  n  n | n  n  n " << '\n';
    }
    else
    {
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << "----------------|----------------|----------------|----------------" << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << "----------------|----------------|----------------|----------------" << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << "----------------|----------------|----------------|----------------" << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
        std::cout << " n   n   n   n  | n   n   n   n  | n   n   n   n  | n   n   n   n  " << '\n';
    }
}

//Prints on the sudoku grid, option chooses what
//0 for the starting positions
//1 for the solved sudoku with numbers
//2 for the solved sudoku with colors
void printOnGrid(std::vector<int> colorVector, int N, int posY, int option)
{
    gotoxy(0, posY);
    printGrid(N);

    int newPosY = posY;
    int newPosX = 1;
    int gridCounterX = 0;
    int gridCounterY = 0;

    for (int i = 0; i < N * N; i++)
    {
        gotoxy(newPosX, newPosY);
		
		//What to print on the grid
        switch (option)
        {
        case 0:
            std::cout << i;
            break;
        case 1:
            std::cout << colorVector[i];
            break;
        case 2:
            textcolor(WHITE, colorVector[i]-1);
            std::cout << ' ';
            textcolor(WHITE, BLACK);
            break;
        default:
            break;
        }

        gridCounterX++;
        if (gridCounterX == sqrt(N))
        {
            if (N == 4 || N == 9)
                newPosX += 4;
            else
                newPosX += 5;
            gridCounterX = 0;
        }
        else
        {
            if (N == 4 || N == 9)
                newPosX += 3;
            else
                newPosX += 4;
        }

        if (i % N == N - 1)
        {
            newPosY++;
            newPosX = 1;

            gridCounterY++;
            if (gridCounterY == sqrt(N))
            {
                newPosY++;
                gridCounterY = 0;
            }
        }
    }
    std::cout << "\n\n";
}

//Returns true if every position of the sudoku board has been colored, false otherwise
bool isCompleted(std::vector<int> color)
{
    for (int i = 0; i < color.size(); i++)
        if (color[i] == 0)
            return false;

    return true;
}

//Select board size, arrow keys to move and enter to confirm
int selectBoardSize()
{
    int key, selected = 0;
    do
    {
        textcolor(WHITE, BLACK);
        gotoxy(0, 0);
        std::cout << "Select the board size (arrow keys to select, enter to confirm):";

        gotoxy(5, 2);
        std::cout << "4";

        gotoxy(8, 2);
        std::cout << "9";

        gotoxy(11, 2);
        std::cout << "16";

        textcolor(WHITE, BLUE);
        switch (selected)
        {
        case 0:
            gotoxy(5, 2);
            std::cout << "4";
            break;
        case 1:
            gotoxy(8, 2);
            std::cout << "9";
            break;
        case 2:
            gotoxy(11, 2);
            std::cout << "16";
            break;
        }
        textcolor(WHITE, BLACK);

        key = getch();

        switch (key)
        {
        case KEY_RIGHT:
            if (selected != 0)
                selected--;
            break;
        case KEY_LEFT:
            if (selected != 2)
                selected++;
            break;
        }

    } while (key != KEY_ENTER);

    if (selected == 0)
        return 4;
    else if (selected == 1)
        return 9;
    else
        return 16;
}

void header()
{
    gotoxy(0, 0);
    textcolor(LIGHTYELLOW, BLACK);
    std::cout << "Sudoku solver that uses a coloring heuristic";
    gotoxy(0, 1);
    textcolor(YELLOW, BLACK);
    std::cout << "Engenharia de Computacao - UNIVALI";
    gotoxy(0, 2);
    std::cout << "Graphs";
    gotoxy(0, 3);
    std::cout << "Andriy Fujii Pendloski";

    textcolor(BLACK, WHITE);
    gotoxy(0, 5);
    system("pause");
    textcolor(BRIGHTWHITE, BLACK);
}
