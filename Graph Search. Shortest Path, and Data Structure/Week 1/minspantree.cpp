//#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Graph
{
public:
    int V;
    int E;
    vector<pair<int, int>> *adjnode;

public:
    void init(int V, int E)
    {
        this-> V = V;
        this-> E = E;
        adjnode = new vector<pair<int, int>>[V];
    }
};

int main()
{
    ifstream file;
    string line;
    Graph g;

    file.open("edges.txt");
    if(file.is_open())
    {
        int i=0;
        while(getline(file, line))
        {
            stringstream linestream(line);
            if(i==0)
            {
                int v,e;
                linestream >> v >> e;
                g.init(v,e);
            }
            else
            {
                int v,w,c;
                linestream >> v >> w >> c;
                g.adjnode[v].push_back(make_pair(w, c));
                g.adjnode[w].push_back(make_pair(v,c));
            }
            i++;
        }
    }
}
