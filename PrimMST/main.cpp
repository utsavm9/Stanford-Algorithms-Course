#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include "heap.cpp"
using namespace std;

struct element
{
    int v1, v2, w;
};

int main()
{
    freopen("test.txt", "r", stdin);
    int vertices = 0, edges = 0;
    cin >> vertices >> edges;

    vector<pair<int, int>> graph[V];
    bool inX[V];
    for (bool &b : inX)
        b = false;

    int v1, v2, w;
    for (int i = 0; i < edges; ++i)
    {
        cin >> v1 >> v2 >> w;

        graph[v1].push_back(make_pair(v2, w));
        graph[v2].push_back(make_pair(v1, w));
    }

    long int spanningSum = 0;
    Heap h;

    inX[v1] = true;
    int lastV = v1;
    cout << "Starting from " << lastV << endl;
    int spannedVertices = 1;
    while (spannedVertices++ < vertices)
    {
        for (pair<int, int> p : graph[lastV])
        {
            if (!inX[p.first])
                h.insert({p.first, p.second});
        }

        pair<int, int> poppedV = h.pop();
        int incommingV = poppedV.first;
        spanningSum += poppedV.second;

        cout << incommingV << " from " << poppedV.second << " edge" << endl;

        inX[incommingV] = true;
        lastV = incommingV;
    }

    cout << "MST Sum:" << spanningSum << endl;

    return 0;
}