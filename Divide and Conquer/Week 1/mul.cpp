#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int countdigit(unsigned long long int n)
{
    unsigned long long int count = 0;
    while ( n!= 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}

int max(long long  x, long long int y)
{
    if(x > y) return x;
    else return y;
}

int karatsuba_mul(unsigned long long int x, unsigned long long int y)
{
    if (x < 10 && y < 10)
    {
        double z = x*y;
        return z;
    }

    int n = ceil(max(countdigit(x), countdigit(y))/2);

    unsigned long long int xh = floor(x/pow(10,n));
    unsigned long long int yh = floor(y/pow(10,n));
    unsigned long long int xl = x % (int)pow(10,n);
    unsigned long long int yl = y % (int)pow(10,n);
    
    unsigned long long int a = karatsuba_mul(xh, yh);
    unsigned long long int d = karatsuba_mul(xl, yl);
    unsigned long long int e = karatsuba_mul(xh+xl, yh+yl) - a - d;

    long long int result = a*pow(10,2*n) + e*pow(10,n) + d;
    return result;
}

int main()
{
    unsigned long long int i = 1234;
    unsigned long long int j = 5678;
    cout << karatsuba_mul(i,j);
}