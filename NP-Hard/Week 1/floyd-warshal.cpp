#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

void print_graph(vector<pair<int, int>> *g, int V)
{
    for(int v=1; v<=V; v++)
    {
        cout << endl;
        cout << v << " -> ";
        for(int j=0; j<g[v].size(); j++)
        {
            cout << "(" << g[v][j].first << "," << g[v][j].second << ")" << " ";
        }
        cout << endl;
    }
}

int main()
{
    ifstream file;
    file.open("g1.txt");
    int V, E;
    file >> V >> E;

    /* init graph */
    unordered_map<int, int> *g;
    vector<pair<int, int>> *g1;
    vector<pair<int, int>> *g2;
    vector<pair<int, int>> *g3;

    g1 = new vector<pair<int, int>>[V+1];
    g2 = new vector<pair<int, int>>[V+1];
    g3 = new vector<pair<int, int>>[V+1];
    
    /*Read graph from file*/
    if(file.is_open())
    {
        int v, w, c;
        while (file >> v >> w >> c)
        {
            g1[v].push_back(make_pair(w, c));
        }
    }
    
    // g2 graph
    ifstream file1;
    file1.open("g2.txt");
    file1 >> V >> E;
    if(file1.is_open())
    {
        int v, w, c;
        while (file1 >> v >> w >> c)
        {
            g2[v].push_back(make_pair(w, c));
        }
    }

    // g3 graph
    ifstream file2;
    file2.open("g3.txt");
    file2 >> V >> E;
    if(file2.is_open())
    {
        int v, w, c;
        while (file2 >> v >> w >> c)
        {
            g3[v].push_back(make_pair(w, c));
        }
    }

    /* init 3D array */
    int ***A = new int **[V+1];
    for (int i=0; i<=V; i++) 
    {
        A[i] = new int*[V+1];
        for (int j=0; j<=V; j++)
        {
           A[i][j] = new int[V+1];
        }
    }

    
    for (int i = 1; i<=V; i++)
    {
        for (int j = 1; j<=V; j++)
        {
            /*check if an edge between i, j exist*/
            bool exist = g[i].find(j)!=g[i].end();
                        
            if(i==j)
            {
                A[i][j][0] = 0;
            }
            else if(exist)
            {
                A[i][j][0] = g[i][j];
            }

            
        }
    }
    

    //print_graph(g3, V);
}
