#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct node_t
{
    int key;
    struct node_t *left;
    struct node_t *right;
}node;



int main()
{
    ifstream file;
    string line;
    vector<int> charfreq;
    int charnum;

    /*Reading data*/
    file.open("huffman.txt");
    if(file.is_open())
    {
        while(getline(file,line))
        {
            int i = 0;
            stringstream linestream(line);
            if(i==0) linestream >> charnum;
            else
            {
                int temp;
                linestream >> temp;
                charfreq.push_back(temp);
            }
        }
    }

    //turn into heap
    node *leafnode = new node[charnum];
    make_heap(charfreq.begin(), charfreq.end(), greater<>{});
    
    return 0;
}
