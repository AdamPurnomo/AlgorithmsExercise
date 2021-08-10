#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

long long int knapsack(int i, int c, vector <pair<int, int>>& data, unordered_map<string, long long int>& kmap)
{
    
    string currentkey = to_string(i) + "," + to_string(c);
    string lookupkey1 = to_string(i-1) + "," + to_string(c);
    string lookupkey2 = to_string(i-1) + "," + to_string(c - data[i-1].second);

    //cout << currentkey << " " << lookupkey1 << " " << lookupkey2 << endl;
    
    if (i==0 || c==0) 
    {
        kmap[currentkey] = 0;
        return kmap[currentkey];
    }

    if(data[i-1].second > c)
    {
        // check on hash tables
        if(kmap.find(lookupkey1)!=kmap.end())
        {
            kmap[currentkey] = kmap[lookupkey1];
            return kmap[currentkey];
        } 
        else 
        {
            kmap[lookupkey1] = knapsack(i-1, c, data, kmap);
            kmap[currentkey] = kmap[lookupkey1];
            return kmap[currentkey];
        }
    }

    else
    {       
        long long int x;
        if(kmap.find(lookupkey1) != kmap.end())  x = kmap[lookupkey1];
        else 
        {
            kmap[lookupkey1] = knapsack(i-1, c, data, kmap);
            x = kmap[lookupkey1];
        }

        long long int y;
        if(kmap.find(lookupkey2) != kmap.end()) y = kmap[lookupkey2] + data[i-1].first;
        else
        {
            kmap[lookupkey2] = knapsack(i-1, c - data[i-1].second, data, kmap);
            y = kmap[lookupkey2] + data[i-1].first;
        }

        kmap[currentkey] = max(x,y);
        return kmap[currentkey];
    }
}

void print_map(std::unordered_map<string, long long int>&m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main()
{   
    auto start = high_resolution_clock::now();

    ifstream file;
    string line;
    vector <pair<int, int>> data;
    unordered_map<string, long long int> knapsackmap;

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

    long long int opval = knapsack(n, C, data, knapsackmap);
    cout << opval << endl;

    //print_map(knapsackmap);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout<< duration.count() << endl;
}