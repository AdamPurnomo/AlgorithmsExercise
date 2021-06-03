#include <iostream>
#include <fstream>
#include <sstream>

typedef struct node_t
{
    int key;
    struct node_t *child_r;
    struct node_t *child_l;
    struct node_t *parent;
    struct node_t *nextorder;
}node;

class heaptree
{
public:
    node *root;
    node *insertplace;
    node *currentnode;
    int order = 0;
public:
    heaptree()
    {
        root->parent = NULL;
        root->child_l = NULL;
        root->child_r = NULL;
        root->key = 0;
        root->nextorder = NULL;
        insertplace = root;
        currentnode = root;

    }
    void insert_node(int key)
    {
        order =+ 1;
        node *p = (struct node_t*)malloc(sizeof(node));
        p->key = key;
        p->nextorder = NULL;
        p->child_l = NULL;
        p->child_r = NULL;
        
        if(insertplace->child_l != NULL) 
        {
            insertplace->child_l = p;
        }
        else 
        {
            insertplace->child_r = p;
            //update insert node
            insertplace = insertplace->nextorder;
        }
        p->parent = insertplace;
        currentnode->nextorder = p;
        currentnode = p;
    }
};

int main()
{
    return 0;
}