#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

const float infinity = numeric_limits<float>::infinity();

void reportError(string message)
{
    cout << message << endl;
    exit(0);
}

float distance(pair<float, float> a, pair<float, float> b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

float tsp(float **distances, int set, int lastPos, float **arrayMemo, int numCities)
{
    if (arrayMemo[lastPos][set] == infinity)
    {
        // for (int j = 1; j < numCities; ++j)
        //     if (set & (1 << (numCities - 1 - j)))
        //     {
        int setMinusJ = set ^ (1 << (numCities - 1 - lastPos));
        float min = tsp(distances, setMinusJ, 0, arrayMemo, numCities) + distances[0][lastPos];
        for (int k = 1; k < numCities; ++k)
            if (setMinusJ & (1 << (numCities - 1 - k)))
            {
                float calcValue = tsp(distances, setMinusJ, k, arrayMemo, numCities) + distances[k][lastPos];
                if (calcValue < min)
                    min = calcValue;
            }
        arrayMemo[lastPos][set] = min;
    }
    return arrayMemo[lastPos][set];

    // }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        reportError("File name required.");
    if (!freopen(argv[1], "r", stdin))
        reportError("File not found.");

    int numCities;
    cin >> numCities;
    vector<pair<float, float>> coords;

    //Input
    for (int i = 0; i < numCities; ++i)
    {
        float x, y;
        cin >> x >> y;
        coords.push_back(make_pair(x, y));
    }

    //Distances
    float **distances = new float *[numCities];
    for (int i = 0; i < numCities; ++i)
    {
        distances[i] = new float[numCities];
        for (int j = 0; j < numCities; ++j)
            distances[i][j] = distance(coords[i], coords[j]);
    }

    //Memoisation array
    float **arrayMemo = new float *[numCities];
    int arrayLength = (1 << numCities);
    for (int j = 0; j < numCities; ++j)
    {
        arrayMemo[j] = new float[arrayLength];
        for (int k = 0; k < arrayLength; ++k)
            arrayMemo[j][k] = infinity;
    }
    for (int k = 0; k < arrayLength; ++k)
    {
        arrayMemo[0][k] = infinity;
    }
    arrayMemo[0][0] = 0.;

    float minTSP = infinity;
    int allSet = (1 << (numCities - 1)) - 1;
    for (int j = 1; j < numCities; ++j)
    {
        float testValue = tsp(distances, allSet, j, arrayMemo, numCities) + distances[j][0];
        if (testValue < minTSP)
            minTSP = testValue;
        cout << testValue << " ";
    }

    cout << endl
         << minTSP << endl;

    for (int i = 0; i < numCities; ++i)
    {
        for (int j = 0; j < arrayLength; ++j)
            cout << arrayMemo[i][j] << " ";
        cout << endl;
    }

    //Output distances;
    // for (int i = 0; i < numCities; ++i)
    // {
    //     for (int j = 0; j < numCities; ++j)
    //         cout << distances[i][j] << " ";
    //     cout << endl;
    // }

    //Deleting everything
    for (int i = 0; i < numCities; ++i)
    {
        delete[] distances[i];
        delete[] arrayMemo[i];
    }
    delete[] distances;
    delete[] arrayMemo;

    return 0;
}