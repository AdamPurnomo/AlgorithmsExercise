#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
    bool min; //is it a minimum heaptree or a maximum heaptree?
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
        //create a new node
        size += 1;
        node *p = (struct node_t*)malloc(sizeof(node));
        p->key = key;
        p->nextorder = NULL;
        p->prevorder =  NULL;
        p->child_l = NULL;
        p->child_r = NULL;
        
        //shifting pointer to a new node
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
        /*swap only the key*/
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
        /*Choose the approriate children node for extract minmax operation*/
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
        /*Extracting (removing) min or max key from heap (depending on the type of the heap)*/
        int res = root->key;
        node *tparent = leafnode->parent;
        swapkey(root, leafnode);
        size -= 1;
        
        //deleting the current leaf
        if(tparent->child_l == leafnode) tparent->child_l = NULL;   
        else if(tparent->child_r == leafnode) tparent->child_r = NULL;

        //shift leafnode
        leafnode = leafnode->prevorder;
        leafnode->nextorder = NULL;

        bubble_down();
        return res;
    }

    int pass_minmax()
    {
        /*Only return the min or max value (this operiation does no remove the minmax value from the heap)*/
        return root->key;
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
    string line;
    ifstream file;
    int x;
    vector<int> data;
    file.open("data.txt");
    if(file.is_open())
    {
        while(getline(file, line))
        {
            x = stoi(line);
            data.push_back(x);
        }
    }

    //initializing heap
    heaptree H1(data[1], false);
    heaptree H2(data[0], true);

    int summedian = 0;
    int median = 0;

    for(int i=0; i<data.size(); i++)
    {   
        //the first two values have been initialized
        if(i==0) median = data[i];
        else if(i==1) median = H1.pass_minmax();
        else if(i>1)
        {
            cout << data[i];
            //insert data to the heap according to its root key
            if(data[i]<H1.root->key) H1.insert_node(data[i]);
            else H2.insert_node(data[i]);


            //check if the heap is not balance, and balance the heap
            int t;
            if((H1.size-H2.size)>=2)
            {
                t = H1.extract_minmax();
                H2.insert_node(t);
            }
            else if((H2.size-H1.size)>=2)
            {
                t = H2.extract_minmax();
                H1.insert_node(t);
            }
        
            //extracting median
            if(H1.size==H2.size) median = H1.pass_minmax();
            else if(H1.size>H2.size) median = H1.pass_minmax();
            else if(H2.size>H1.size) median = H2.pass_minmax();
        }

        summedian += median;
    }

    cout << summedian%10000 << endl;

    /*
    //for the sake of debugging
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

    cout << endl;

    H2.print_heap();

    cout << endl;
    H2.insert_node(24);
    H2.print_heap();

    cout << endl;
    int t = H2.extract_minmax();
    H2.print_heap();
    */



    return 0;
}
