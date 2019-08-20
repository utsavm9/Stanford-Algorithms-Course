#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;

void reportError(string message)
{
    cout << message << endl;
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        reportError("Filename required.");
    if (!freopen(argv[1], "r", stdin))
        reportError("File not found.");

    const int infinity = numeric_limits<int>::max();

    //Implementing Floyd-Warshell's Algorithm
    int numV, numE;
    cin >> numV >> numE;

    //Allocating memory
    int ***array = new int **[2];
    for (int k = 0; k < 2; ++k)
    {
        array[k] = new int *[numV];
        for (int i = 0; i < numV; ++i)
        {
            array[k][i] = new int[numV];
            for (int j = 0; j < numV; ++j)
                array[k][i][j] = infinity;
        }
    }

    //Initializing diagonal
    for (int v = 0; v < numV; ++v)
        array[0][v][v] = 0;

    //Initializing present edges
    for (int e = 0; e < numE; ++e)
    {
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        array[0][v1 - 1][v2 - 1] = weight;
    }

    //Floyd-Warshell Algorithm
    int current, past;
    for (int k = 0; k < numV; ++k)
    {
        past = k % 2;
        current = !past;
        for (int i = 0; i < numV; ++i)
        {
            for (int j = 0; j < numV; ++j)
            {
                int gotShortest = array[past][i][j], newShortest;
                if (array[past][i][k] == infinity || array[past][k][j] == infinity)
                    newShortest = infinity;
                else
                    newShortest = array[past][i][k] + array[past][k][j];

                array[current][i][j] = (gotShortest <= newShortest) ? gotShortest : newShortest;
            }
        }
    }

    //Testing for negative cycle
    bool negCyc = false;
    for (int i = 0; i < numV; ++i)
        if (array[current][i][i] < 0)
        {
            negCyc = true;
            break;
        }

    if (negCyc)
        cout << "Negative cycle" << endl;
    else
    {
        int min = infinity;
        for (int i = 0; i < numV; ++i)
            for (int j = 0; j < numV; ++j)
                if (i == j)
                    continue;
                else if (array[current][i][j] < min)
                    min = array[current][i][j];
        cout << "Shortest shortest path: " << min << endl;
    }
    


    //Output
    for (int i = 0; i < numV; ++i)
    {
        for (int j = 0; j < numV; ++j)
            if (array[current][i][j] == infinity)
                cout << "∞ ";
            else
                cout << array[current][i][j] << " ";
        cout << endl;
    }

    return 0;
}