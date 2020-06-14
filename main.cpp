#include "main.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//Receives the sudoku matrix and its size and fills it with the graph conectivity
//Two nodes are in the same grid if (i/n) == (i'/n) and (j/n) == (j'/n)
void fillBoard(vector<vector<int>> &connectivityMatrix, int N)
{
    //For for every node in matrix, i and j
    for (int i = 0; i < connectivityMatrix.size(); i++)
    {
        for (int j = 0; j < connectivityMatrix.size(); j++)
        {
            int nodeiPosi = i / N;
            int nodeiPosj = i % N;

            int nodejPosi = j / N;
            int nodejPosj = j % N;

            int nodeiGridi = nodeiPosi / sqrt(N);
            int nodeiGridj = nodeiPosj / sqrt(N);

            int nodejGridi = nodejPosi / sqrt(N);
            int nodejGridj = nodejPosj / sqrt(N);

            if (i == j)
                connectivityMatrix[i][j] = -1;
            //If both nodes are in the same column, row or grid
            else if (nodeiPosi == nodejPosi || nodeiPosj == nodejPosj || nodeiGridi == nodejGridi && nodeiGridj == nodejGridj)
                connectivityMatrix[i][j] = 1;
            else
                connectivityMatrix[i][j] = 0;
        }
    }
}

//Returns the node with the highest saturation
int highestSaturation(vector<vector<int>> connectivityMatrix, vector<int> colorVector)
{
    vector<int> saturationVector(colorVector.size(), 0);

    //Looks for colored nodes, and adds to the saturation vector
    for (int i = 0; i < colorVector.size(); i++)
    {
        if (colorVector[i] != 0)
        {
            for (int j = 0; j < colorVector.size(); j++)
            {
                if (connectivityMatrix[j][i] == 1)
                {
                    saturationVector[j]++;
                }
            }
        }
    }
    int highestSaturation = 0;
    int highestSaturationPos = 0;
    //Sets already colored nodes to -1 and finds the highest saturation node
    for (int i = 0; i < colorVector.size(); i++)
    {
        if (colorVector[i] != 0)
        {
            saturationVector[i] = -1;
        }
        if (saturationVector[i] > highestSaturation)
        {
            highestSaturation = saturationVector[i];
            highestSaturationPos = i;
        }
    }

    return highestSaturationPos;
}

//Coloring with backtracking
bool coloring(vector<vector<int>> connectivityMatrix, vector<int> &colorVector, int pos, int N)
{
    int color = 1;
    while (!isCompleted(colorVector))
    {
        //Next position is the one with the highest saturation
        pos = highestSaturation(connectivityMatrix, colorVector);
        for (int i = 0; i < colorVector.size(); i++)
        {
            if (connectivityMatrix[i][pos] == 1 && colorVector[i] == color)
            {
                color++;
                //Failed, backtrack and try again
                if (color > N)
                    return false;

                i = -1;
            }
        }
        colorVector[pos] = color;
        //If failed, remove last color added and moves to the next color
        if (!coloring(connectivityMatrix, colorVector, pos, N))
        {
            colorVector[pos] = 0;
            color++;
            if (color > N)
                return false;
        }
    }

    return true;
}

int main()
{
    header();

    bool tryAgain;
    do
    {
        system("cls");

        int N = selectBoardSize();

        vector<vector<int>> connectivityMatrix(N * N, vector<int>(N * N));
        vector<int> colorVector(N * N, 0);

        system("cls");

        printOnGrid(colorVector, N, 0, 0);
        cout << "Enter the starting position for the sudoku:\n";

        int startingPos;
        bool exit;
        //Validates the input
        do
        {
            cin >> startingPos;

            exit = true;
            //Positions go from 0 to N^2-1
            if (startingPos < 0 || startingPos > N * N - 1)
            {
                system("cls");

                printOnGrid(colorVector, N, 0, 0);
                cout << "Invalid position! Try again:\n";
                exit = false;
            }
        } while (!exit);

        system("cls");

        //Fills the connectivity matrix
        fillBoard(connectivityMatrix, N);
        //Sets the starting position as color 1 and starts the coloring
        colorVector[startingPos] = 1;
        coloring(connectivityMatrix, colorVector, 0, N);

        //Prints all boards
        printOnGrid(colorVector, N, 0, 0);
        cout << "Starting position: " << startingPos << '\n';
        cout << "Solved sudoku:" << '\n';
        printOnGrid(colorVector, N, N + sqrt(N) + 2, 1);
        printOnGrid(colorVector, N, 2 * (N + sqrt(N)) + 2, 2);

        char choice;
        //If the program should run again or close
        do
        {
            cout << "Finished! Try again? (Y/N) ";
            cin >> choice;
            choice = tolower(choice);

            exit = false;
            //Only leaves the loop if Y or N are typed
            if (choice == 'y')
            {
                tryAgain = true;
                exit = true;
            }
            else if (choice == 'n')
            {
                tryAgain = false;
                exit = true;
            }
        } while (!exit);
    } while (tryAgain);

    system("pause");
}