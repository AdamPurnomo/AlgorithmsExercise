#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{   
    auto start = high_resolution_clock::now();

    ifstream file;
    string line;
    vector <pair<int, int>> data;

    file.open("knapsackbig.txt");
    int n, C;
    file >> C >> n;
    if(file.is_open())
    {
        int v, w;
        while (file >> v >> w)
        {
            data.push_back(make_pair(v, w));
        }
    }


    //initialize 2D array
    int** A = new int*[n+1];
    for(int i=0; i<(n+1);i++) A[i] = new int[C+1];

    //base case i=0
    
    for(int c=0; c<=C;c++) A[0][c] = 0;

    
    for(int i=1; i<=n; i++)
    {
        for (int c = 0; c <=C; c++)
        {
            if(data[i-1].second > c) A[i][c] = A[i-1][c];
            else
            {
                A[i][c] = max(A[i-1][c], A[i-1][c - data[i-1].second] + data[i-1].first); 
            }
        }
    }

    cout << A[n][C] << endl;
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<< duration.count() << endl;
}
