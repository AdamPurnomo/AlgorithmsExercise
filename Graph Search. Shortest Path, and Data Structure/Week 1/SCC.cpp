#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    int V;
    vector<int> *adjlist;

public:
    Graph(int V)
    {
        this-> V = V;
        adjlist = new vector<int>[V];
    }

    void add_edge (int v, int w)
    {
        adjlist[v].push_back(w);
    }
    
    Graph get_transpose()
    {
        Graph g(V);
        for (int v=0;v<V;v++)
        {
            //iterate over all adjlist
            vector<int>::iterator it;
            //apparently iterator is an address or a pointer
            for(it = adjlist[v].begin(); it != adjlist[v].end(); it++)
            {
                g.adjlist[*it].push_back(v);
            }

        }

        return g;

    }

    void DFS_sort(int v, bool* visited, vector<int>& f)
    {
        visited[v]= true;
        for(vector<int>::iterator i = adjlist[v].begin(); i!=adjlist[v].end(); i++)
        {
            if(visited[*i]==false)
            {
                DFS_sort(*i, visited, f);
            }
        }
        f.push_back(v);
    }

    void DFS_countsize(int v, bool* visited, int& size)
    {
        visited[v] = true;
        for(vector<int>::iterator i = adjlist[v].begin(); i!=adjlist[v].end(); i++)
        {
            if(visited[*i]==false)
            {
                DFS_countsize(*i, visited, size);
            }
           
        }
        size++;
    }
    
    void countscc()
    {
        bool *visited = new bool[V];
        vector<int> finishing_order;
        vector<int> scc_size;
        int size;

        Graph gt = get_transpose();

        for (int v = 1; v < V; v++)
            visited[v] = false;

        //first DFS pass on transposed graph
        for (int i = 1; i < V; i++)
            if(visited[i]==false)
                gt.DFS_sort(i, visited, finishing_order);

        for (int v = 1; v < V; v++)
            visited[v] = false;

        //second DFS pass on actual graph
        for(vector<int>::iterator i = finishing_order.end(); i!= finishing_order.begin(); i--)
        {   
            size=0;
            if(visited[*i]==false)
            {
                DFS_countsize(*i, visited,size);
                scc_size.push_back(size);
            }    
        }

        std::sort(scc_size.begin(),scc_size.end(), greater<int>());

        for(int i=0; i<8 ; i++)
            cout << scc_size[i] << endl;
    }

    void print_graph()
    {
        for(int v = 0; v < V; v++)
        {
            cout << v << "->";
            
            for (vector<int>::iterator i = adjlist[v].begin(); i != adjlist[v].end(); i++)
            {
                cout << *i << " ";
            }
            cout << endl;
            
        }
        
    }

    void print_transposed_graph()
    {
        Graph gT = get_transpose();
        for(int v = 0; v < V; v++)
        {
            cout << v << "->";
            
            for (vector<int>::iterator i = gT.adjlist[v].begin(); i != gT.adjlist[v].end(); i++)
            {
                cout << *i << " ";
            }
            cout << endl;
            
        }
        
    }

};

int main()
{
    //Initializing graph
    Graph g(900000);
    
    //reading data from line
    //Gotta study string buddy
    string line;
    ifstream myReadfile;
    int v, w;
    myReadfile.open("edges.txt");
    if(myReadfile.is_open())
    {
        while(getline(myReadfile, line))
        {
            stringstream linestream(line);
            linestream << line;
            linestream >> v >> w;

            g.add_edge(v, w);
        }
    }

    g.countscc();
   


    return 0;
}



/*
//debugging DFS_sort

     bool visited[6];
    vector<int> finishing_order;
    vector<int> scc_size;

    Graph gt = g.get_transpose();
    g.print_graph();
    cout << endl;
    g.print_transposed_graph();
    cout << endl;

    //first DFS pass
    for (int v = 0; v < 6; v++)
        visited[v] = false;

    for (int i = 0; i < 6; i++)
        if(visited[i]==false)
            gt.DFS_sort(i, visited, finishing_order);

    for(vector<int>::iterator it = finishing_order.begin(); it != finishing_order.end(); it++)
        cout << *it << endl;
    
    cout << endl;
    
    //second DFS pass
    for (int v = 0; v < 6; v++)
        visited[v] = false;

    for(vector<int>::iterator i = finishing_order.end(); i!= finishing_order.begin(); i--)
    {
        if(visited[*i]==false)
        {
            int size = 0;
            g.DFS_countsize(*i, visited,size);
            scc_size.push_back(size);
        }
    }

    for(vector<int>::iterator it = scc_size.begin(); it != scc_size.end(); it++)
        cout << *it << endl;
    
*/
