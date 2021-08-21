#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define n 25

int VISITED_ALL = (1 << n) - 1;

double tsp(double dist[n][n], int mask, int s) {
    if (mask == VISITED_ALL) {
        return dist[s][0];
    }
    double ans = INT_MAX;

    for (int city = 0; city < n; city++) {
        if((mask&(1<<city))==0) {
            double newAns = dist[s][city] + tsp(dist, mask|(1<<city), city);
            ans = min(ans, newAns);
        }
    }
    return ans;
}

int main() {
    double dist[n][n];
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0.0;
    }
    int cities;
    ifstream file("TSP.txt");
    file >> cities;
    vector<pair <double, double>> v;
    double x, y;
    while (file >> x >> y) {
        v.push_back(make_pair(x, y));
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
                double d = sqrt((v[j].first - v[i].first) * (v[j].first - v[i].first) + (v[j].second - v[i].second) * (v[j].second - v[i].second));
                dist[i][j] = d;
                dist[j][i] = d;
        }
    }

    auto start = high_resolution_clock::now();

    cout << tsp(dist, 1, 0) << endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<< duration.count() << endl;
}


