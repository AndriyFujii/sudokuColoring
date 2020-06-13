#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>

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

//Prints vector and a colored version, receives the vector and board size
void showVector(std::vector<int> vector, int N, int startingPos)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i];
        //Properly spaces the numbers
        if (N == 4 || N == 9)
            std::cout << ' ';
        else
        {
            if (vector[i] < 10)
                std::cout << "  ";
            else
                std::cout << " ";
        }
        if (i % N == N - 1)
        {
            std::cout << '\n';
        }
    }

    if (N == 4 || N == 9)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            textcolor(WHITE, vector[i]);
            std::cout << ' ';
            textcolor(WHITE, BLACK);
            std::cout << ' ';
            //Properly spaces the numbers*
            if (i % N == N - 1)
            {

                std::cout << '\n';
            }
        }
    }
}

/* textcolor(WHITE, vector[i]);
        std::cout << vector[i];
        textcolor(WHITE, BLACK);*/

//Shows the possible starting positions for the sudoku
void printMatrix(int N)
{
    for (int i = 0; i < N * N; i++)
    {
        std::cout << i;
        //Properly spaces the numbers
        if (N == 4 || N == 9)
        {
            if (i < 10)
                std::cout << "  ";
            else
                std::cout << " ";
        }
        else
        {
            if (i < 10)
                std::cout << "   ";
            else if (i < 100)
                std::cout << "  ";
            else
                std::cout << " ";
        }
        if (i % N == N - 1)
        {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

//Returns true if every position of the sudoku board has been colored, false otherwise
bool isCompleted(std::vector<int> color)
{
    for (int i = 0; i < color.size(); i++)
        if (color[i] == 0)
            return false;

    return true;
}

//Jumps to position x,y in the cmd
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
