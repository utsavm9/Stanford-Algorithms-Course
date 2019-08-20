#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <limits>
using namespace std;

const int infinity = numeric_limits<int>::max();

struct Element
{
    int leader;
    int rank;
};

struct Edge
{
    int v1, v2, w;
};

bool edgeSorter(Edge &a, Edge &b)
{
    return a.w < b.w;
}

class DisjointSet
{
    Element *vertices;
    int numSets;

    int findLeaderHelper(int i, vector<int> &v)
    {
        if (vertices[i].leader == i)
            return i;

        v.push_back(i);
        return findLeaderHelper(vertices[i].leader, v);
    }

public:
    DisjointSet(int v) : numSets(v)
    {
        vertices = new Element[v];
        for (int i = 0; i < v; ++i)
        {
            vertices[i].leader = i;
            vertices[i].rank = 0;
        }
    }

    ~DisjointSet()
    {
        delete[] vertices;
    }

    int findLeader(int i)
    {
        vector<int> pathTraversed;
        int ret = findLeaderHelper(i, pathTraversed);

        for (int nodes : pathTraversed)
            vertices[nodes].leader = ret;

        return ret;
    }

    void unionSet(int a, int b)
    {
        int l1 = findLeader(a);
        int l2 = findLeader(b);

        if (l1 == l2)
            return;

        --numSets;
        if (vertices[l1].rank > vertices[l2].rank)
            vertices[l2].leader = vertices[l1].leader;

        else if (vertices[l1].rank < vertices[l2].rank)
            vertices[l1].leader = vertices[l2].leader;
        else
        {
            vertices[l1].leader = vertices[l2].leader;
            ++vertices[l2].rank;
        }
    }

    void print()
    {
        for (int i = 0; i < 10; ++i)
            cout << i << " ";
        cout << endl;
        for (int i = 0; i < 10; ++i)
            cout << vertices[i].leader << " ";
        cout << endl;
        for (int i = 0; i < 10; ++i)
            cout << vertices[i].rank << " ";
        cout << "Numsets: " << numSets << endl
             << endl;
    }
};

int main()
{
    freopen("clustering1.txt", "r", stdin);

    int numV;
    cin >> numV;
    //Assuming a node 0 which will remain disconnected
    DisjointSet s(numV + 1);
    vector<Edge> edges;

    int a, b, c;
    while (cin >> a >> b >> c)
        edges.push_back({a, b, c});

    sort(edges.begin(), edges.end(), edgeSorter);

    //for (Edge &e : edges)
    // cout << e.v1 << " " << e.v2 << " " << e.w << " - ";
    //cout << endl;

    const int clusters = 4;
    int reqEdges = clusters;
    int count = edges.size();
    int i;

    //Kruskal's algorithm
    for (i = 0; i < count && reqEdges < numV; ++i)
    {
        Edge &e = edges[i];

        if (s.findLeader(e.v1) != s.findLeader(e.v2))
        {
            //cout << e.v1 << " " << e.v2 << " " << e.w << "\n";
            s.unionSet(e.v1, e.v2);
            ++reqEdges;
        }
    }

    //Spacings of the clustering
    unordered_map<int, int> leaderToIndex;
    int unusedIndex = 0;
    auto spacing = new int[clusters][clusters];

    for (int r = 0; r < clusters; ++r)
        for (int c = 0; c < clusters; ++c)
            spacing[r][c] = infinity;

    while (i < count)
    {
        Edge &e = edges[i];
        int l1 = s.findLeader(e.v1), l2 = s.findLeader(e.v2);

        if (l1 != l2)
        {
            if (leaderToIndex.find(l1) == leaderToIndex.end())
                leaderToIndex[l1] = unusedIndex++;
            if (leaderToIndex.find(l2) == leaderToIndex.end())
                leaderToIndex[l2] = unusedIndex++;

            int index1 = leaderToIndex[l1], index2 = leaderToIndex[l2];
            spacing[index1][index2] = spacing[index2][index1] = min(spacing[index1][index2], e.w);
        }
        ++i;
    }

    // Maximum Spacing is the minimum distance between two clusters
    int maxSpacing = infinity;
    for (int r = 0; r < clusters; ++r)
        for (int c = 0; c < clusters; ++c)
            maxSpacing = min(spacing[r][c], maxSpacing);

    // for (int r = 0; r < clusters; ++r)
    // {
    //     for (int c = 0; c < clusters; ++c)
    //         cout << spacing[r][c] << " ";
    //     cout << endl;
    // }

    //s.print();
    cout << "Maximum spacing: " << maxSpacing << endl;
    s.print();

    delete[] spacing;
    return 0;
}