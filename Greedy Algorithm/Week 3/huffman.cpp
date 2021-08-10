#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct node_t
{
    long long int key;
    struct node_t *left;
    struct node_t *right;
}node;

struct compare
{
    bool operator() (node* l, node* r)
    {
        return l->key > r->key;
    }
};

void printpq_key(priority_queue<node*, vector<node*>, compare> pq)
{
    while(!pq.empty())
    {
        cout << pq.top()->key << endl;
        pq.pop();
    }
}

int calculatemaxdepth(node* root)
{
    if(root == NULL) return -1;
    else
    {
        int leftdepth = calculatemaxdepth(root->left);
        int rightdepth = calculatemaxdepth(root->right);
        return max(leftdepth, rightdepth) + 1;
    }
}

int calculatemindepth(node* root)
{
    if(root == NULL) return -1;
    else
    {
        int leftdepth = calculatemindepth(root->left);
        int rightdepth = calculatemindepth(root->right);
        return min(leftdepth, rightdepth) + 1;
    }
}



int main()
{
    ifstream file;
    string line;
    priority_queue<node*, vector<node*>, compare> pq;
    int charnum;

    /*Reading data*/
    file.open("huffman.txt");
    if(file.is_open())
    {
        int i = 0;
        while(getline(file,line))
        {
            stringstream linestream(line);
            if(i==0) linestream >> charnum;
            else
            {
                int temp;
                linestream >> temp;

                node *leafnode = new node;
                leafnode->key = temp;
                leafnode->left = NULL;
                leafnode->right = NULL;
                
                pq.push(leafnode);
            }
            i++;
        }
    }


    while(pq.size() > 1)
    {
        // Remove two smallest elements in the heap
        node *t1 = pq.top();
        pq.pop();

        node *t2 = pq.top();
        pq.pop();

        //Merger tree and putting back to heap
        node *root = new node;
        root->key = t1->key + t2->key;
        //cout << t1->key << " " << t2->key << " " << root->key << endl;
        root->left = t1;
        root->right = t2;
        pq.push(root);
    }
    
    node *root = pq.top();

    cout << calculatemaxdepth(root) << endl;
    cout << calculatemindepth(root) << endl;


    return 0;
}
