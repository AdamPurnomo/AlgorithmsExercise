#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

int sortcountsplit(vector<int> &a, int l, int r, int m)
{   
    int n1 = m-l + 1;
    int n2 = r-m;
    int counts = 0;

    //Temporary vectors to copy the left part, right part, and the sorted part
    vector<int> temp;
    vector<int> L;
    vector<int> R;
    
    int i=l;
    int j=m+1;
    int k;

    while(i<=m) 
    {
        L.push_back(a[i]); 
        i++;
    }
    while(j<=r) 
    {
        R.push_back(a[j]); 
        j++;
    }

    i = 0;
    j = 0;
    k = 0;

    //Copying the smallest one between L and R to temp until 
    //one of R or L is empty
    while(i<n1 && j<n2)
    {
        if(L[i] < R[j])
        {
            temp.push_back(L[i]);
            i++;
        }
        else
        {
            temp.push_back(R[j]);
            j++;
            counts += n1-i;
        }
    }

    //Copying the leftover array
    while(i<n1) 
    {
        temp.push_back(L[i]); 
        i++;
    }
    while(j<n2) 
    {
        temp.push_back(R[j]); 
        j++;
    }

    while(k<n1+n2)
    {
        a[l] = temp[k];
        k++;
        l++;
    }
    return counts;
}

int sortcount(vector<int> &a, int l, int r)
{   
    int countl;
    int countr;
    int counts;
    int m = l + (r-l)/2;

    //If the length of array is equal to one, returns 0
    if(l >= r) 
    {   
        return 0;
    }
    else
    {
        countl = sortcount(a, l, m);
        countr = sortcount(a, m+1, r);
        counts = sortcountsplit(a, l, r, m);
        return countl + countr + counts;
    }
}


int main()
{
    //Reading text file and copying it into vector
    vector<int> arr;
    string num;
    ifstream myReadfile;
    myReadfile.open("integer.txt");
    if(myReadfile.is_open())
    {
        while (getline(myReadfile, num))
        {
            arr.push_back(stoi(num));
        }
        myReadfile.close();
    }
    else cout << "Unable to open file";
    
    //Calculating inversion
    long unsigned int countinv;
    int n = arr.size();
    countinv = sortcount(arr, 0, n-1);
    cout << countinv << endl;
    return 0;
}