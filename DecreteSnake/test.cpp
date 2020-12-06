#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Human
{
protected:
    int x;
public:
    virtual void fun() = 0;
};
class Man : public Human
{
public:
    Man()
    {
        cout << "initialize man!" << endl;
    }
    ~Man()
    {
        cout << "destory man!" << endl;
    }
    virtual void fun()
    {
        x =100;
        cout << x << endl;
    }
};

int main()
{
    Man man;
    Human *human;
    human = &man;
    human->fun();
}