#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main()
{
    default_random_engine random;
    random.seed(time(0));
    for(int i=0;i<10000;i++)
    {
        cout<<random()%256<<endl;
        usleep(100);
    }
}