#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAXINT 3000000

class hashtable
{

public:
    vector<long long int> tables[MAXINT];
    vector<long long int> data;
    int a;
    int b;
    int n = MAXINT;
public:
    hashtable()
    {
        srand((unsigned) time(0));
        a = rand()%(MAXINT-1) + 1;
        b = rand()%(MAXINT-1) + 1;
    }
    int hashingfunction(long long int key)
    {
        int res = (a*key + b) % n;
        return 0;
    }

    void insert()
    {
        int index;
        for(int i=0; i<data.size(); i++) index = hashingfunction(data[i]);        
    }

    bool lookup(long long int key)
    {
        int index = hashingfunction(key);
        for(int i=0; i<tables[index].size(); i++)
        {
            if(tables[index][i]==key) return true;
            else return false;
        } 
    }

    void twosumprob()
    {
        long long int y;
        bool in;
        int num=0;
        for(int t = -10000; t<=10000;t++)
        {
            for(int i=0; i<data.size(); i++)
            {
                y = t - data[i];
                in = lookup(y);
                if(in) num += 1;
            }
        }
    }
};


int main()
{
    ifstream file;
    string line;
    //hashtable H;

    cout << "Hello world" << endl;
}