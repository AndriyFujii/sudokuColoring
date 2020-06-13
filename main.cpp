#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//Receives the sudoku matrix and its size and fills it with the graph conectivity
//Two nodes are in the same grid if (i/n) == (i'/n) and (j/n) == (j'/n)
void fillBoard(vector<vector<int>> &connectivity, int N)
{
    //For for every node in matrix, i and j
    for (int i = 0; i < N * N; i++)
    {
        for (int j = 0; j < N * N; j++)
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
                connectivity[i][j] = -1;
            //If both nodes are in the same column, row or grid
            else if (nodeiPosi == nodejPosi || nodeiPosj == nodejPosj || nodeiGridi == nodejGridi && nodeiGridj == nodejGridj)
                connectivity[i][j] = 1;
            else
                connectivity[i][j] = 0;
        }
    }
}

void showMatrix(vector<vector<int>> matrix)
{
    for (int i = 0; i < 81; i++)
    {
        for (int j = 0; j < 81; j++)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

//Returns the node with the highest saturation
int highestSaturation(vector<vector<int>> connectivity, vector<int> color, int N)
{
    vector<int> saturationVector(N * N, 0);

    //Looks for colored nodes, and adds to the saturation vector
    for (int i = 0; i < N * N; i++)
    {
        if (color[i] != 0)
        {
            for (int j = 0; j < N * N; j++)
            {
                if (connectivity[j][i] == 1)
                {
                    saturationVector[j]++;
                }
            }
        }
    }
    int highestSaturation = 0;
    int highestSaturationPos = 0;
    //Sets already colored nodes to -1
    //Melhorar isso depois, provavelmente pode ser feito no laço for anterior com -1
    for (int i = 0; i < N * N; i++)
    {
        if (color[i] != 0)
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

//Returns true if every position of the sudoku board has been colored, false otherwise
bool isCompleted(vector<int> color, int N)
{
    for (int i = 0; i < N * N; i++)
    {
        if (color[i] == 0)
        {
            return false;
        }
    }
    return true;
}

//Prints vector, receives the vector and board size
void showVector(vector<int> vector, int N)
{
    for (int i = 0; i < N*N; i++)
    {
        cout << vector[i] << ' ';
        if (i % N == N-1)
        {
            cout << '\n';
        }
        
    }
    
}

//Coloring with backtracking
bool coloring(vector<vector<int>> connectivityMatrix, vector<int> &colorVector, int N, int pos)
{
    int color = 1;
    while(!isCompleted(colorVector, N))
    {
        pos = highestSaturation(connectivityMatrix, colorVector, N);
        for (int i = 0; i < N * N; i++)
        {
            if (connectivityMatrix[i][pos] == 1 && colorVector[i] == color)
            {
                color++;
                //Failed, backtrack and try again
                if (color>9)
                    return false;
                
                i = 0;
            }
        }
        colorVector[pos] = color;
        if(!coloring(connectivityMatrix, colorVector, N, pos))
        {
            colorVector[pos] = 0;
            color++;
            if (color>9)
                return false;
        }
        
    }

    return true;
}

int main()
{

    int N = 9;
    vector<vector<int>> connectivityMatrix(N * N, vector<int>(N * N));
    vector<int> colorVector(N * N, 0);

    fillBoard(connectivityMatrix, N);

    //Positions go from 0 to N^2-1
    int pos = 0;

    colorVector[pos] = 1;

    coloring(connectivityMatrix, colorVector, N, pos);

    showVector(colorVector, N);

    system("pause");
}