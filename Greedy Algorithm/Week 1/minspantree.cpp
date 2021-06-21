//#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
using namespace std;
#define MAXINT 10000000

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
        adjnode = new vector<pair<int, int>>[V+1];
    }

    void printgraph()
    {
        for(int v=0;v<V+1;v++)
        {   
            cout << v << " -> ";
            if(adjnode[v].empty()==false)
            {
                for (vector<pair<int, int>>::iterator i = adjnode[v].begin(); i!=adjnode[v].end(); i++)
                {
                    cout << "(" << (*i).first << "," << (*i).second <<")" << " ";
                }
            }
            cout << endl;
        }
    }

    int min_span_tree(int start)
    {
        bool visited[V+1];
        int dist[V+1];
        int parent[V+1];

        int v; //currently processed vertex
        int w; //adj node of currently processed vertex
        int cost; // cost to adj node from currently processed vertex
        int tempdist; //temporary variablye to find minimum distance from processed vertices to unprocessed vertices
        int sumdistance = 0; //cost of the whole minimum spanning tree

        //initializing variables
        for(int i=0; i<V+1 ;i++)
        {
            visited[i] = false;
            dist[i] = MAXINT;
            parent[i] = -1;
        }
        v = start;
        dist[start] = 0;

        while(visited[v]==false)
        {
            // updating distance from processed vertices to unprocessed node w to the minimum value 
            visited[v] = true;
            for (vector<pair<int, int>>::iterator i = adjnode[v].begin(); i!=adjnode[v].end(); i++)
            {
                w = (*i).first;
                cost = (*i).second;
                if((visited[w]==false) && (dist[w] > cost))
                {
                    dist[w] = cost;
                    parent[w] = v;
                }
            }

            //choosing the minimum distance of edges from processed vertices to unprocessed vertices
            tempdist = MAXINT;
            int increment = 0;
            for(int j=0; j<V+1 ; j++)
            {
                if((visited[j]==false) && (tempdist > dist[j]))
                {
                    v = j;
                    tempdist = dist[j];
                    increment = dist[j];
                }
            }
            sumdistance += increment;
        }
        return sumdistance;
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

    int totalcost = g.min_span_tree(1);
    cout << totalcost << endl;

}
