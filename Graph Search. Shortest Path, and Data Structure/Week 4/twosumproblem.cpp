#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAXINT 2000000

class table
{
public:
    vector<long long int> *tables = new vector<long long int>[MAXINT];;
    vector<long long int> data;
    int a;
    int b;
    int n = MAXINT;
public:
    void init()
    {
        srand((unsigned) time(0));
        a = rand()%(MAXINT-1) + 1;
        b = rand()%(MAXINT-1) + 1;
    }
    
    int hashingfunction(long long int key)
    {
        int res = abs((a*key + b) % n);
        return res;
    }

    void insert()
    {
        int index;
        for(int i=0; i<data.size(); i++) 
        {
            index = hashingfunction(data[i]);
            if (index > MAXINT) cout << data[i] << " " << index << endl;
            tables[index].push_back(data[i]);
        }        
    }

    bool lookup(long long int key)
    {
        int index = hashingfunction(key);
        for(int i=0; i<tables[index].size(); i++)
        {
            if(tables[index][i]==key) return true;
        }
        return false; 
    }

    int twosumprob(int min, int max)
    {
        long long int y;
        bool in;
        int num=0;
        for(int t=min; t<=max ;t++)
        {
            for(int i=0; i<data.size(); i++)
            {
                y = t - data[i];
                in = lookup(y);
                if(in==true) 
                {
                    num += 1;
                    i = data.size();
                }
            }
        }
        return num;
    }

    void printhashtables()
    {
        for(int i=0; i<MAXINT; i++)
        {
            cout << "key : " << i << " Data : ";
            for(int j=0; j<tables[i].size(); j++) 
            {
                cout << tables[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    ifstream file;
    string line;
    table T;
    file.open("data.txt");
    cout << "Reading data . . ." << endl;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            T.data.push_back(strtoll(line.c_str(), nullptr, 10));
        }
    }

    //insertind data to hash tables
    T.insert(); 

    //sanity check
    //T.printhashtables();

    int res = T.twosumprob(-10000, 10000);
    cout << res << endl;

    return 0;
}