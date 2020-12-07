#ifndef SYMBOL_SNAKETYPE
#define SYMBOL_SNAKETYPE
#include <bits/stdc++.h>
using namespace std;

#include "./ColorType.h"
#include "./Turn.h"

/*define*/
typedef int SnakeHandle;
typedef pair<int, int> pos;

class SnakeType
{
public:
    /*variables*/
    int orignLength;
    int orignSpeed;

    int Length;
    int Speed;

    double StepReward;

    ColorType Color;

    //if snake alive
    bool state;

    //pos
    vector<pos> bodys;

    //turn
    Turn turn;

    //health
    int health;

    /*functions*/
    SnakeType(int ol = 5, int os = 1, int h = 1, ColorType color = ColorType::Black, double sr = -0.5, Turn turn = Turn::NONE)
        : orignLength(ol), orignSpeed(os), StepReward(sr), StepRewards(0), Color(color), state(0)
    {
        this->Length = orignLength;
        this->Speed = orignSpeed;
        this->turn = turn;
        this->health = h;
    }

    SnakeType(SnakeType &s) { this->duplicate(s); }

    SnakeType &operator=(SnakeType &s)
    {
        this->duplicate(s);
        return *this;
    }

private:
    double StepRewards;

    void duplicate(SnakeType &s)
    {
        this->orignLength = s.orignLength;
        this->orignSpeed = s.orignSpeed;
        this->Length = s.Length;
        this->Speed = s.Speed;
        this->StepReward = s.StepReward;
        this->Color = s.Color;
    }
};

#endif