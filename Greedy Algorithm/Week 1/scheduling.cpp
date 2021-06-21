#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

#include <cstdlib>

using namespace std;

int main()
{
    ifstream file;
    string line;
    int size;
    vector<int> length;
    vector<int> weight;
    vector<float> greedyindex;

    file.open("jobs.txt");

    if(file.is_open())
    {   
        int i = 0;
        while(getline(file, line))
        {   
            stringstream linestream(line);
            float l, w;
            float g;
            if(i==0) size = stoi(line);
            else 
            {
                linestream >> w >> l;
                g = w / l;
                length.push_back(l);
                weight.push_back(w);
                greedyindex.push_back(g);
            }
            i++;                                                    
        }

    }

    // sorting based on greedy index    
    vector<int> argsort(size);
    iota(argsort.begin(), argsort.end(),0);

    sort(argsort.begin(), argsort.end(), 
    [&](int i, int j){
        if(greedyindex[i] == greedyindex[j]) return weight[i] > weight[j];
        else return greedyindex[i] > greedyindex[j];
        });


    // calculating total time
    
    long long int total_performanceindex = 0;
    long long int total_time = 0;
    for (int i=0; i<size ; i++)
    {
        total_time += length[argsort[i]];
        total_performanceindex += weight[argsort[i]]*total_time;
        cout << length[argsort[i]] << "," <<weight[argsort[i]] << "  " << total_time << "," << total_performanceindex << endl;
        }

    cout << total_performanceindex << endl;
    

    // sanity check
    /*    
    for(int i=0;i<size;i++)
    {
        cout << argsort[i] << "," << greedyindex[argsort[i]] << "," << weight[argsort[i]] << "," << length[argsort[i]] << endl;
    }
    */
   
}   