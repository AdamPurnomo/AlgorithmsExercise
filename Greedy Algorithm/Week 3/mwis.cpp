#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    vector<int> weight;
    vector<int> A; //value
    vector<int> B; //solution

    ifstream file;
    string line;
    file.open("mwis.txt");
    if(file.is_open())
    {
        while(file>>line)
        {
            weight.push_back(stoi(line));
        }
    }

    weight[0] = 0;

    //init 
    A.push_back(0);
    A.push_back(weight[1]);

    B.push_back(0);
    B.push_back(0);

    //execute
    for(int i=2; i<weight.size(); i++)
    {
        A.push_back(max(A[i-1],A[i-2]+weight[i]));
        B.push_back(0);
    }

    //reconstruct
    int i = A.size()-1;
    while(i>=2)
    {
        if(A[i-1] >= A[i-2] + weight[i]) i = i-1;
        else
        {
            B[i] = 1;
            i = i-2;
        }
    }
    if(i==1) B[i] = 1;

    //print
    cout << B[1] << B[2] << B[3] << B[4] << B[17] << B[117] << B[517] << B[997] << endl; 
    cout << A.size() << endl;

}
