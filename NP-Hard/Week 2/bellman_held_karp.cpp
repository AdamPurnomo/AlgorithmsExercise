#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

double TSPutil(int combmask, int dest, double **adjmat, int n);
double TSPval(double **adjmat);


void print_adjmatrix(double **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    
}

void decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];
 
    // counter for binary array
    int i = 0;
    while (n > 0) {
 
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order
    for (int j = n; j >= 0; j--)
        cout << binaryNum[j];
}

double TSPval(double **adjmat, int n)
{   
    //Start with all vertices included in subset S
    int combmask = int(pow(2,n)) - 1;
    double minval = INT_MAX;

    //looking the optimal value from source to other dest where dest !=0
    for(int dest=1; dest<n;dest++)
    {
        double newval = TSPutil(combmask, dest, adjmat, n) + adjmat[dest][0];
        minval = min(newval, minval);
    }
    return minval;
}

double TSPutil(int combmask, int dest, double **adjmat, int n)
{
    double minval = INT_MAX;
    int newcomb = combmask&~(1<<dest);
    //cout << dest << " " << combmask  << " " << newcomb << endl;
    if(combmask==1)
    {
        return 0;
    }
    for (int k = 0; k < n; k++)
    {
        if((newcomb&(1<<k))!=0)
        {
            double newval = TSPutil(newcomb, k, adjmat, n) + adjmat[k][dest];
            minval = min(minval, newval);
        }
    }
    return minval;
}

int main()
{
    
    ifstream file;
    file.open("TSP.txt");    
    int n;
    file >> n;

    double **adjmat = new double*[n];
    for (int i = 0; i<n; i++)
    {
        adjmat[i] = new double[n];
    }

    vector<pair<double, double>> citycoord;
    if(file.is_open())
    {
        double x, y;
        while(file >> x >> y)
        {
            citycoord.push_back(make_pair(x, y));
        }
    }

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            double distx, disty;
            distx = pow(citycoord[i].first - citycoord[j].first, 2);
            disty = pow(citycoord[i].second - citycoord[j].second, 2);
            adjmat[i][j] = sqrt(distx + disty);
        }  
    }

    print_adjmatrix(adjmat, n);
    cout << endl;

    auto start = high_resolution_clock::now();
    cout << TSPval(adjmat, n) << endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start);
    cout<< duration.count() << endl;   



   /*
   ## Debugging ##
   double A[4][4] = {
            {0,20,42,25},
            {20,0,30,34},
            {42,30,0,10},
            {25,34,10,0}
    };

    int n=4;
    double **adjmat= new double*[n];;
    for (int i = 0; i<n; i++)
    {
        adjmat[i] = new double[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjmat[i][j] = A[i][j];
        }
        
    }
    cout << TSPval(adjmat, 4) << endl;
    */
}