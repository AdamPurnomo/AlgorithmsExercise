#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

typedef struct node_t
{
    int key;
    struct node_t *child_r;
    struct node_t *child_l;
    struct node_t *parent;
    struct node_t *nextorder; //the subsequence node (in the insert order)
    struct node_t *prevorder; //the previous node (in the insert order)
}node;

class heaptree
{
public:
    node *root = (struct node_t*)malloc(sizeof(node)); 
    node *insertplace; //node location to insert new node
    node *leafnode; // the bottom right most node in the tree
    int size = 1; //size of the tree
    bool min;
public:
    heaptree(int i, bool min)
    {
        root->parent = NULL;
        root->child_l = NULL;
        root->child_r = NULL;
        root->key = i;
        root->nextorder = NULL;
        root->prevorder = NULL;
        insertplace = root;
        leafnode = root;
        this->min = min;

    }

    void insert_node(int key)
    {
        size += 1;
        node *p = (struct node_t*)malloc(sizeof(node));
        p->key = key;
        p->nextorder = NULL;
        p->prevorder =  NULL;
        p->child_l = NULL;
        p->child_r = NULL;
        
        if(insertplace->child_l == NULL) 
        {
            insertplace->child_l = p;
            p->parent = insertplace;
        }
        else 
        {
            insertplace->child_r = p;
            p->parent = insertplace;
            //update insert node
            insertplace = insertplace->nextorder;
        }
        
        //updating leafnode 
        leafnode->nextorder = p;
        p->prevorder = leafnode;
        leafnode = p;
        bubble_up();
    }
    
    void swapkey(node* a, node* b)
    {
        int t = a->key;
        a->key = b->key;
        b->key = t;
    }

    void bubble_up()
    {
        /*bubbling up to maintain invariant during insert operation*/
        node *p = leafnode;
        if(min==true)
        {
            while((p->parent!=NULL) && (p->key < p->parent->key))
            {
                swapkey(p, p->parent);
                p = p->parent;
            }
        }
        else if(min==false)
        {
            while((p->parent!=NULL) && (p->key > p->parent->key))
            {
                swapkey(p, p->parent);
                p = p->parent;
            }
        }        
    }

    void bubble_down()
    {
        /*bubbling down to maintain invariant during exract operation*/
        node *p = root;
        node *chosenchild = minmax_key(root->child_l, root->child_r);
        

        if(min==true)
        {
            while((chosenchild!=NULL) && (p->key > chosenchild->key))
            {
                swapkey(p, chosenchild);
                p = chosenchild;
                if((p->child_l != NULL) && (p->child_r != NULL)) chosenchild = minmax_key(chosenchild->child_l, chosenchild->child_r);
                else if(p->child_l != NULL) chosenchild = p->child_l;
                else chosenchild = NULL;
            }
        }
        else if(min==false)
        {
            while((chosenchild!=NULL) && (p->key < chosenchild->key))
            {
                swapkey(p, chosenchild);
                p = chosenchild;
                if((p->child_l != NULL) && (p->child_r != NULL)) chosenchild = minmax_key(chosenchild->child_l, chosenchild->child_r);
                else if(p->child_l != NULL) chosenchild = p->child_l;
                else chosenchild = NULL;
            }
        }        
    }

    node* minmax_key(node* a, node* b)
    {
        if(min==true)
        {
            if(a->key < b->key) return a;
            else return b;
        }
        else
        {
            if(a->key > b->key) return a;
            else return b; 
        }
    }

    int extract_minmax()
    {
        int res = root->key;
        swapkey(root, leafnode);
        size -= 1;
        
        //deleting the current leaf
        if(leafnode->parent->child_l == leafnode) leafnode->parent->child_l == NULL;
        else if(leafnode->parent->child_r == leafnode) leafnode->parent->child_r = NULL;

        //shift leafnode
        leafnode = leafnode->prevorder;
        leafnode->nextorder = NULL;

        bubble_down();
        return res;
    }
    void print_heap()
    {
        node *p = root;
        while(p != NULL)
        {
            if(p->child_r != NULL) cout << p->key << "," << p->child_l->key << "," << p->child_r->key << endl;
            else if (p->child_l != NULL) cout << p->key << "," << p->child_l->key << endl;
            else cout << p->key << endl;
            
            p = p->nextorder;

        }
    }
};

int main()
{
    heaptree H(9, true);
    H.insert_node(1);
    H.insert_node(2);
    H.insert_node(3);
    H.insert_node(4);
    H.insert_node(5);
    H.insert_node(6);
    H.insert_node(7);
    H.insert_node(8);
    H.print_heap();
    int t = H.extract_minmax();
    cout << "Extracting min " << t << endl;
    H.print_heap();



    return 0;
}
