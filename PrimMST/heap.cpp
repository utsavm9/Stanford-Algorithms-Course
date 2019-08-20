#include <iostream>
#include <utility>
using namespace std;

const int V = 605;

struct Vertex
{
    int num;
    int key;
};

class Heap
{
    Vertex array[V];
    int heapIndex[V];
    int count;

    int parent(int i) { return (i - 1) / 2; }
    int lChild(int i) { return 2 * i + 1; }
    int rChild(int i) { return 2 * i + 2; }

    void reheapify(int i)
    {
        if (i == 0 || array[i].key > array[parent(i)].key)
        {
            //Down pushing
            while (1)
            {
                int l = lChild(i), r = rChild(i);
                bool lExists = l < count;
                bool rExists = r < count;

                if (!lExists && !rExists)
                    break;
                else if (lExists && !rExists)
                {
                    //Only left child exists
                    if (array[l].key < array[i].key)
                    {
                        swap(heapIndex[array[l].num], heapIndex[array[i].num]);
                        swap(array[l], array[i]);
                        i = l;
                        continue;
                    }
                    break;
                }
                else
                {
                    //Both left and right child exist
                    if (array[l].key <= array[r].key && array[l].key < array[i].key)
                    {
                        swap(heapIndex[array[l].num], heapIndex[array[i].num]);
                        swap(array[l], array[i]);
                        i = l;
                        continue;
                    }
                    else if (array[r].key <= array[l].key && array[r].key < array[i].key)
                    {
                        swap(heapIndex[array[r].num], heapIndex[array[i].num]);
                        swap(array[r], array[i]);
                        i = r;
                        continue;
                    }
                    break;
                }
            }
        }
        else
        {
            //Up pushing
            for (int p = parent(i); array[p].key > array[i].key && i > 0; p = parent(i))
            {
                swap(heapIndex[array[p].num], heapIndex[array[i].num]);
                swap(array[p], array[i]);
                i = p;
            }
        }
    }

public:
    Heap() : count(0)
    {
        for (int i = 0; i < V; ++i)
            heapIndex[i] = -1;
    }

    void insert(Vertex v)
    {
        int i;
        if (heapIndex[v.num] == -1)
        {
            //New node
            i = count;
            array[i] = v;
            heapIndex[v.num] = i;
            ++count;
        }
        else
        {
            //Update existing node
            i = heapIndex[v.num];
            if (array[i].key > v.key)
                array[i].key = v.key;
            else
                return;
        }

        reheapify(i);
        //print();
    }

    pair<int, int> pop()
    {
        if (count < 1)
            return make_pair(-1, -1);
        pair<int, int> p;
        p.first = array[0].num;
        p.second = remove(array[0].num);
        return p;
    }

    int remove(int vnum)
    {
        int i = heapIndex[vnum];
        if (i == -1)
            return -1;
        int ret = array[i].key;

        swap(heapIndex[array[count - 1].num], heapIndex[vnum]);
        swap(array[count - 1], array[i]);
        heapIndex[vnum] = -1;
        count--;

        reheapify(i);

        //print();
        return ret;
    }

    void print()
    {
        cout << "Heap Index: ";
        for (int i = 0; i < 10; ++i)
            cout << heapIndex[i] << " ";
        cout << "Heap Array (" << count << "): ";
        for (int i = 0; i < count; ++i)
            cout << array[i].num << "-" << array[i].key << " ";
        cout << endl;
    }
};

// int main()
// {
//     cout << "Initialized..." << endl;
//     Heap h;
//     h.insert({0, 8});
//     h.insert({1, 4});
//     h.insert({2, 2});
//     h.insert({3, 4});
//     h.insert({4, 9});
//     h.insert({5, 1});
//     h.insert({6, 5});
//     h.remove(6);

//     return 0;
// }