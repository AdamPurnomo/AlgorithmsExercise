#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define MAXV 500
#define MAXINT 1000000000000

typedef struct edgenode_t
{
    int node;
    int weight;
    struct edgenode_t *next;
} edgenode;

typedef struct node_t
{
    edgenode *adjnode;
    int vertex; //the label of the node
    bool processed; //has been processed?
    int degree; //num of adj nodes
    int dist; //distance of this node from source
} node;

class graph
{
public:
    node *vertices[MAXV];
public:
    int nedges;
    int nvertexes;

public:
    graph()
    {
        //initializing the graph
        nvertexes = 0;
        nedges = 0;

        
        for(int i=0; i<MAXV; i++)
        {
            node *p = (struct node_t*)malloc(sizeof(node));
            p->adjnode = NULL;
            p->degree = 0;
            p->processed = false; 
            p->vertex = i+1;
            p->dist = MAXINT;
            vertices[i+1] = p;            
        } 
        
    }
    
    void add_edge(int v, int w, int weight)
    {
        //adding edge to the graph
        //v is the source
        edgenode *p = (struct edgenode_t*)malloc(sizeof(edgenode)); //allocating pointer memory
        p->node = w;
        p->weight = weight;
        p->next = vertices[v]->adjnode;
        //inserting at the head of the linked list
        vertices[v]->adjnode = p;
        //incrementing the number of degree in the source vertex
        vertices[v]->degree += 1;
        //incrementing the total number of edges in the graph
        nedges += 1;

    }
    void print_graph()
    {
        edgenode* p; //temporary pointer
        for(int v = 1; v <= nvertexes; v++)
        {   
            p = vertices[v]->adjnode;
            cout << v << "->";
            
            for (int w = 0; w < vertices[v]->degree; w++)
            {
                cout << p->node << "," << p->weight << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

    void dijkstra(int s)
    {
        int v; //current processed node
        //initialize the distance of the source
        vertices[s]->dist = 0;
    }
};

int main()
{
     //Initializing graph
     graph g;

    //reading data from line
    //Gotta study string buddy
    string line;
    ifstream myReadfile;
    string data, num;
    int v, w, weight;
    myReadfile.open("data.txt");
    if(myReadfile.is_open())
    {
        while(getline(myReadfile, line))
        {
            stringstream linestream(line);

            int i = 0;    
            while((linestream >> data))
            {   
                if(i == 0)
                {
                    v = stoi(data);
                } 
                else
                {   
                    stringstream datastream(data);
                    getline(datastream, num, ',');
                    w = stoi(num);
                    getline(datastream, num, ',');
                    weight = stoi(num);
                    g.add_edge(v, w, weight);
                }
                i++;
            }
            g.nvertexes+=1;
        }
    }
}
