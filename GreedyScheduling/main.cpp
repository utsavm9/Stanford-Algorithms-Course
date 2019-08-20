#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

bool sortFunc(pair<int, int> a, pair<int, int> b) {
    float score1 = ((float) a.first) / a.second;
    float score2 = ((float) b.first) / b.second;

    return (score1 > score2);
}

int main() {
    freopen("jobs.txt", "r", stdin);
    
    int tests = 0;
    vector<pair<int, int>> jobs;
    cin >> tests;

    while (tests-- > 0) {
        int w, l;
        cin >> w >> l;
        jobs.push_back(make_pair(w, l));
    }

    sort(jobs.begin(), jobs.end(), sortFunc);

    long long int sum = 0;
    long long time = 0;
    for (pair<int, int> p: jobs) {
        time += p.second;
        sum += time * p.first;
    }

    cout << sum;

    return 0;
}