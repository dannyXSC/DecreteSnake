#ifndef SYMBOL_CONFIG
#define SYMBOL_CONFIG

#include <bits/stdc++.h>
using namespace std;

#include "./RewardType.h"
#include "./SnakeType.h"
#include "./AgentType.h"

enum GameMode{Mode_Single=0,Mode_WithBot};

class Config{
public:
    int length,width;

    GameMode game_mode;

    vector<AgentType> agents;
    
    vector<SnakeType> snakes;

    Config(){}
    void set_mapsize(int length,int width){this->length=length;this->width=width;}
    void set_gamemode(GameMode game_mode){this->game_mode=game_mode;}
    void add_agent(AgentType &r);
    void add_snake(SnakeType &s);
};

void Config::add_agent(AgentType &r)
{
    agents.push_back(r);
}
void Config::add_snake(SnakeType &s)
{
    snakes.push_back(s);
}

#endif