#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int total = 0;
int countQuickSort(vector<int> &arr, int l, int r);
int ChoosePivot(vector<int> &arr, int l, int r);
int partition(vector<int> &arr, int l, int r, int p);
int medianofthree(vector<int> &arr,int l, int r, int m);

int countQuickSort(vector<int> &arr, int l, int r)
{
    int x, y, z;
    if(l >= r) 
    {
        z = 0;
        return z;
    }
    z = r - l;
    total += z;

    //int p = r;
    float m = l + ceil(((float)r+1-(float)l)/2) -1;
    m = (int)m;
    int p = medianofthree(arr,l,r,m);

    p = partition(arr, l, r, p);
    x = countQuickSort(arr,l,p-1);
    y = countQuickSort(arr,p+1,r);
    return z+x+y;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 int partition(vector<int> &arr, int l, int r, int p)
 {
    swap(&arr[p], &arr[l]);
    int pivot = arr[l];

    int i = l + 1;
    for(int j=l+1;j<=r;j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[j], &arr[i]);
            i+=1;
        }
    }
    swap(&arr[l], &arr[i-1]);
    return i-1;
 }

int medianofthree(vector<int> &arr,int l, int r, int m)
{
    if((arr[l]<=arr[m] && arr[m]<=arr[r]) || (arr[r]<=arr[m] && arr[m]<=arr[l])) return m;
    else if((arr[m]<=arr[l] && arr[l]<=arr[r]) || (arr[r]<=arr[l] && arr[l]<=arr[m])) return l;
    else return r;
}


int main()
{

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
   
    long unsigned int res;
    int n = arr.size();
    res = countQuickSort(arr, 0, n-1);
    cout << res << endl;
    cout << total << endl;
    

    /*
    vector<int> test = {7, 1, 3, 6, 2, 5, 4, 9, 8};
    int l = 0;
    int r = test.size()-1;
    float m = ceil(((float)r+1-(float)l)/2) - 1;
    m = (int)m;
    cout << m << endl;

    int p = medianofthree(test,l,r,m);
    cout << test[l] << endl<< test[m] << endl << test[r] << endl;
    cout << test[p] << endl;    
    */
    
    return 0;
}
