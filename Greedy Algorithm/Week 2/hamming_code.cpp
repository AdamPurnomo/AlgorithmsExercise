#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

#include <cstdlib>
using namespace std;

class setunion
{
public:
    int *p; //parent
    int *size; //number of element is subtree i
    int elementsize;
    int n; //number of union in the set

public:
void init(int V)
{
    elementsize = V+1;
    n = V+1;
    p = new int[V+1];
    size = new int[V+1];

    for (int i=0; i<=V+1; i++)
    {
        p[i] = i;
        size[i] = 1;
    }
}

int find_root(int x)
{
    /*Find the root of node x*/
    if(p[x] == x) return x;
    else return find_root(p[x]);
}

void merge_union(int s1, int s2)
{
    /*Merge union in which s1 and s2 belong to*/
    int r1, r2;

    r1 = find_root(s1);
    r2 = find_root(s2);

    if (r1==r2) return;
    else
    {
        if(size[r1] >= size[r2])
        {
            size[r1] = size[r1] + size[r2];
            p[r2] = r1;
        }
        else
        {
            size[r2] = size[r1] + size[r2];
            p[r1] = r2;
        }
        n = n-1;
    }
}

bool same_component(int s1, int s2)
{
    return (find_root(s1) == find_root(s2));
}

};


typedef struct{
    vector<pair<int,int>> pairnodes;
    vector<int> edges;
    int nodesize;
}edgearray;

setunion clustering(edgearray *e, vector<int> &argsort)
{
    
    //initialize union data set
    setunion s;
    s.init(e->nodesize);

    int v,w;
    for (int k=0; k<e->edges.size(); k++)
    {
        int index = argsort[k];
        v = e->pairnodes[index].first;
        w = e->pairnodes[index].second;

        if(s.same_component(v, w)==false)
        {
            if(s.n > 5) s.merge_union(v,w);
            else 
            {
                cout << e->edges[index] << endl;
                break;
            }
        }
 
    }
    return s;
}

int BinarytoDecimal(string n)
{
    string binary = n;
    int decimal = 0;

    int base = 1; //base value 2^0
    int i = binary.length(); 
    while(i!=0)
    {
        int index = i - 1;
        int d = binary[index] - '0';
        decimal += d*base;
        base = 2*base;
        i--;
    }
    return decimal;
}

int main()
{
    ifstream file;
    string line;
    int num_nodes, bitlength;
    vector<string> binary;
    vector<int> decimal;

    file.open("hamming.txt");
    if(file.is_open())
    {
        int i = 0;
        while(getline(file, line))
        {
            stringstream linestream(line);
            if(i==0) linestream >> num_nodes >> bitlength;
            else 
            {
                string data;
                string temp;
                while((linestream >> data)) temp.append(data);
                binary.push_back(temp);
            }
            i++; 
        }
    }
    
    for(int i=0; i<binary.size(); i++)
    {
        int dec = BinarytoDecimal(binary[i]);
        decimal.push_back(dec);
    }
    
    
}