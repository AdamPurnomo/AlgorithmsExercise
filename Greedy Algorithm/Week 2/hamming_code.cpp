#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <unordered_map>

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

void twocombi(int n, vector<vector<int>> &combi)
{
   
    for(int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
             vector<int> temp;
             temp.push_back(i);
             temp.push_back(j);
             combi.push_back(temp);
        }
    }
}



/*
##Will be donw later
void combine_util(int n, int st, int r)
{
    if(r==0) return;
    for(int i=st; i<=n; i++)
    {
        cout << st-1 << " " << i << " ";
        combine_util(n, st+1, r-1);
        cout << endl;
    }
}

void combination(int n, int r)
{
    ##Generate a r combination of integer natural number up to n 
    
    for(int i=1; i<=n; i++)
    {
        combine_util(n,i+1,r-1);
    }
}
*/

int main()
{
    ifstream file;
    string line;
    int num_nodes, bitlength;
    vector<string> binary;
    vector<int> decimal;
    unordered_map<string, int> bmap;

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
                bmap[temp] = 1;
            }
            i++; 
        }
    }
    
    for(int i=0; i<binary.size(); i++)
    {
        int dec = BinarytoDecimal(binary[i]);
        decimal.push_back(dec);
    }

    /*Create combination of 1 and 2 number*/
    vector<int> oneid(24);
    iota(oneid.begin(), oneid.end(), 0);
    vector<vector<int>> twoid;
    twocombi(bitlength,twoid);

    /*Generate combination*/
    for (int i = 0; i<1; i++)
    {
        //check one id
        for (int j=0; j<oneid.size() ; j++)
        {
            //replace with one different value
            string temp = binary[i];
            int idx = oneid[j];
            char c =  (binary[i][idx] - '0')^1 + '0' ;
            temp[idx] = c;

            //find the temp in the hashmap
            if(bmap.find(temp) != bmap.end())
            {
                /*merge binary i with temp*/
            }
        }

        //check two id
        for (int j=0; j<twoid.size(); j++)
        {
            //replace with two different values
            string temp = binary[i];
            int idx1 = twoid[j][0];
            int idx2 = twoid[j][1];
            char c =  (binary[i][idx1] - '0')^1 + '0' ;
            char d = (binary[i][idx2] - '0')^1 + '0';
            temp[idx1] = c;
            temp[idx2] = d;

            //find the temp in the hashmap
            if(bmap.find(temp) != bmap.end())
            {
                /*merge binary i with temp*/
            }

        }
        
    }
    

          
}