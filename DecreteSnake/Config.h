#ifndef SYMBOL_CONFIG
#define SYMBOL_CONFIG

#include <bits/stdc++.h>
using namespace std;

#include "./RewardType.h"
#include "./SnakeType.h"
#include "./AgentType.h"

enum GameMode
{
    Mode_Single = 0,
    Mode_WithBot
};

class Config
{
private:
    void duplicate(const Config &config)
    {
        this->length = config.length;
        this->width = config.width;
        this->game_mode = config.game_mode;
        this->agents = config.agents;
        this->snakes = config.snakes;
    }

public:
    Config &operator=(const Config &config)
    {
        duplicate(config);
        return *this;
    }

    Config(const Config &config)
    {
        duplicate(config);
    }

    int length, width;

    GameMode game_mode;

    vector<AgentType> agents;

    vector<SnakeType> snakes;

    Config() {}
    void set_mapsize(int length, int width)
    {
        this->length = length;
        this->width = width;
    }
    void set_gamemode(GameMode game_mode) { this->game_mode = game_mode; }
    AgentHandle add_agent(AgentType &r);
    SnakeHandle add_snake(SnakeType &s);
};

AgentHandle Config::add_agent(AgentType &r)
{
    int pos = agents.size();
    agents.push_back(r);
    return pos;
}
SnakeHandle Config::add_snake(SnakeType &s)
{
    int pos = snakes.size();
    snakes.push_back(s);
    return pos;
}

#endif