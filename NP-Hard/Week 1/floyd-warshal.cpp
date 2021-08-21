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

void print_graph(unordered_map<int, int> *g, int V)
{
    for(int v=1; v<=V; v++)
    {
        cout << endl;
        cout << v << " -> ";
        for(auto it: g[v])
        {
            cout << "(" << it.first << "," << it.second << ") ";
        }
        cout << endl;
    }
}

int floyd_warshal(unordered_map<int, int> *g, int V)
{
    /* init 3D array */
    int minval = 100000;

    int ***A = new int **[V+1];
    for (int i=0; i<=V; i++) 
    {
        A[i] = new int*[V+1];
        for (int j=0; j<=V; j++)
        {
           A[i][j] = new int[V+1];
        }
    }

    
    /* base case */
    for (int i = 1; i<=V; i++)
    {
        for (int j = 1; j<=V; j++)
        {
            /*check if an edge between i, j exist*/
            bool exist = (g[i].find(j)!=g[i].end());
                        
            if(i==j) A[i][j][0] = 0;
            else if(exist) A[i][j][0] = g[i][j];
            else A[i][j][0] = 100000;
        }
    }
    
    /*Populate solution*/
    for (int k=1; k<=V; k++)
    {
        for (int i=1; i<=V; i++)
        {
            for (int j=1; j<=V; j++)
            {
                A[i][j][k] = min(A[i][j][k-1], A[i][k][k-1] + A[k][j][k-1]);
                if(k==V)
                {
                    if(A[i][j][k]<minval) minval = A[i][j][k];
                }
            }
        }
        
    }

    /*check negative cycle*/
    for(int i=1; i<=V; i++)
    {
        if(A[i][i][V]<0) 
        {
            cout << "There is a negative cycle" << endl;
            break;
        }
    }

    return minval;
}

int main()
{
    ifstream file;
    file.open("g1.txt");
    int V, E;
    file >> V >> E;

    /* init graph */
    unordered_map<int, int> *g1;
    unordered_map<int, int> *g2;
    unordered_map<int, int> *g3;

    g1 = new unordered_map<int, int>[V+1];
    g2 = new unordered_map<int, int>[V+1];
    g3 = new unordered_map<int, int>[V+1];
    
    /*Read graph from file*/
    if(file.is_open())
    {
        int v, w, c;
        while (file >> v >> w >> c)
        {
            g1[v][w] = c;
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
            g2[v][w] = c;
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
            g3[v][w] = c;
        }
    }

    int min_g1 = floyd_warshal(g1, V);
    cout << min_g1 << endl;

    int min_g2 = floyd_warshal(g2, V);
    cout << min_g2 << endl;

    int min_g3 = floyd_warshal(g3, V);
    cout << min_g3 << endl;
    //print_graph(g3, V);
}
