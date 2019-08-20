#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Element
{
    int leader;
    int rank;
};

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

    int numberOfSets() { return numSets - 1; }

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
        cout << "Numsets: " << numSets - 1 << endl
             << endl;
    }
};

int main()
{
    freopen("clustering_big.txt", "r", stdin);
    int numV, bits;
    cin >> numV >> bits;

    DisjointSet s(numV + 1);
    vector<string> distances;
    unordered_map<string, vector<int>> nodes;

    int nodeNum = 1;
    string val;
    for (int i = 0; i < numV; ++i)
    {
        val = "";
        char bit = 0;
        for (int j = 0; j < bits; ++j)
        {
            cin >> bit;
            val += bit;
        }
        distances.push_back(val);
        nodes[val].push_back(nodeNum++);
    }

    s.print();

    //Include all zero-length edges
    for (string distance : distances)
    {
        for (int i : nodes[distance])
            for (int j : nodes[distance])
                s.unionSet(i, j);
    }
    s.print();

    //Include all one-length edges
    int nodeProcessed = 0;
    for (string distance : distances)
    {
        for (int i : nodes[distance])
        {
            int len = distance.length();
            for (int k = 0; k < len; ++k)
            {
                string oneBitChanged = distance.substr(0, k) + (char)(!(distance[k] - '0') + '0') + distance.substr(k + 1, len - k - 1);
                for (int j : nodes[oneBitChanged])
                    s.unionSet(i, j);
            }
        }
    }
    s.print();

    //Include all two-length edges
    nodeProcessed = 0;
    for (string distance : distances)
    {
        if (nodes[distance].size() == 0)
            continue;
        if (nodeProcessed++ % 1000 == 0)
            cout << "Processing " << nodeProcessed << "\n";

        for (int i : nodes[distance])
        {
            int len = distance.length();
            for (int k = 0; k < len; ++k)
            {
                string obc = distance.substr(0, k) + (char)(!(distance[k] - '0') + '0') + distance.substr(k + 1, len - k - 1);
                for (int l = k + 1; l < len; ++l)
                {
                    string twoBitChanged = obc.substr(0, l) + (char)(!(obc[l] - '0') + '0') + obc.substr(l + 1, len - l - 1);
                    for (int j : nodes[twoBitChanged])
                        s.unionSet(i, j);
                }
            }
        }
    }
    s.print();

    return 0;
}