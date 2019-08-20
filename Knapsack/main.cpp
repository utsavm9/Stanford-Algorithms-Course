#include <iostream>
using namespace std;

int main()
{
    freopen("knapsack_big.txt", "r", stdin);
    int capacity, items;
    cin >> capacity >> items;

    int *knapsack = new int[capacity + 1]();

    for (int i = 1; i <= items; ++i)
    {
        int value, weight;
        cin >> value >> weight;
        for (int w = capacity; w > weight; --w)
        {
            int included = knapsack[w - weight] + value;
            if (included > knapsack[w])
                knapsack[w] = included;
        }
    }

    cout << knapsack[capacity] << endl;

    delete[] knapsack;
    return 0;
}