#ifndef SYMBOL_DECRETESNAKE
#define SYMBOL_DECRETESNAKE

#include <bits/stdc++.h>
using namespace std;

#include "./Config.h"

class DecreteSnake{
private:
    int length,width;
    GameMode game_mode;
    vector<AgentType> agents;
    vector<SnakeType> snakes;
public:
    DecreteSnake(Config config);
};

DecreteSnake::DecreteSnake(Config config)
{
    this->length=config.length;
    this->width=config.width;
    this->game_mode=config.game_mode;
    this->agents=config.agents;
    this->snakes=config.snakes;
}

#endif
