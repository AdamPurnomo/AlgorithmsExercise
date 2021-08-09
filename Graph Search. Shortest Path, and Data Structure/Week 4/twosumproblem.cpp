#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
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

    void insert_from_key(long long int key)
    {
        int index = hashingfunction(key);
        tables[index].push_back(key);
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
    vector<long long int> A;
    file.open("data.txt");
    cout << "Reading data . . ." << endl;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            A.push_back(strtoll(line.c_str(), nullptr, 10));
        }
    }



    sort(A.begin(), A.end());


    //still slow actually, around one minute
    //how can we get it down to few seconds?
    
    int i=0;
    int j=A.size()-1;
    int max = 10000;
    int min = -10000;
    long long int sum = A[i] + A[j];
    int num = 0;

   

    while(i<j)
    {   
        if(sum < min) 
        {
            i++;
            sum = A[i] + A[j];
        }
        else if(sum > max) 
        {
            j--;
            sum = A[i] + A[j];
        }
        else
        {
            while((sum >= min) && (i<j))
            {
                
                if(T.lookup(sum)==false)
                {
                    T.insert_from_key(sum);
                    num +=1;
                }
                j--;
                sum = A[i] + A[j];
            }
            i++;
            j=A.size()-1;
            sum = A[i] + A[j];
        }
        
    }


    cout << num << endl;
    
    /*
    too slow for many targets (more than 1 hour)
    
    /insert data to hash tables
    T.insert(); 

    //int res = T.twosumprob(min, max);
    cout << res << endl;
    */

    return 0;
}