#ifndef SYMBOL_REWARDTYPE
#define SYMBOL_REWARDTYPE

#include <bits/stdc++.h>
using namespace std;

#include "./ColorType.h"

/*define*/
typedef int RewardHandle;

struct RewardType{
public:
    /*----------------------------------------------------------------------------
    variables
    ----------------------------------------------------------------------------*/
    //0 not change
    //- decrease
    //+ increase
    int Length_change;
    //if multiply?
    double Length_multiply;

    //change speed
    int Speed_change;
    //if multiply
    double Speed_multiply;

    //add a life
    int add_life;

    //add the score
    int add_score;

    /*----------------------------------------------------------------------------
    functions
    ----------------------------------------------------------------------------*/
    RewardType(int lc=0,double lm=0,int sc=0,double sm=0,int al=0,int as=0)
    :Length_change(lc),Length_multiply(lm),Speed_change(sc),Speed_multiply(sm),
    add_life(al),add_score(as){};

    RewardType(RewardType &r){this->duplicate(r);}

    RewardType& operator=(RewardType& r){this->duplicate(r);return *this;}
private:
    void duplicate(RewardType &r)
    {
        this->Length_change=r.Length_change;
        this->Length_multiply=r.Length_multiply;
        this->Speed_change=r.Speed_change;
        this->Speed_multiply=r.Speed_multiply;
        this->add_life=r.add_life;
        this->add_score=r.add_score;
    }
};

#endif