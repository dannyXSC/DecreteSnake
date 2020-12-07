#ifndef SYMBOL_SINGLESERVER
#define SYMBOL_SINGLESERVER

#include <bits/stdc++.h>
using namespace std;

#include "./Server.h"
#include "./DecreteSnake.h"
#include "Config.h"

#define SINGLESERVER_MAPSIZE 100
#define FOOD_SECOND 10

class SingleServer : public Server
{
protected:
    void duplicate(const SingleServer &ss)
    {
    }

public:
    SingleServer();
    ~SingleServer() { delete game; }
    Config MyConfig();
    void Add_wall();

    Map &get_map();
    int get_width() { return SINGLESERVER_MAPSIZE; }
    int get_length() { return SINGLESERVER_MAPSIZE; }

    bool initial();
    void KeyDown(char c);

    void End();

    void Step();
};

void SingleServer::Step()
{
    int speed = game->get_speed(snake_handles[0]);
    for (int i = 0; i < speed; i++)
        game->step(snake_handles[0], CleanMode::EMPTY);
}

void SingleServer::End()
{
    cout << "you lose!" << endl;
}

void SingleServer::KeyDown(char c)
{
    SnakeHandle SingleSnake = snake_handles[0];
    switch (c)
    {
    case ('w'):
    case ('W'):
    {
        game->adjust_snake(SingleSnake, Turn::UP);
        break;
    }
    case ('s'):
    case ('S'):
    {
        game->adjust_snake(SingleSnake, Turn::DOWN);
        break;
    }
    case ('a'):
    case ('A'):
    {
        game->adjust_snake(SingleSnake, Turn::LEFT);
        break;
    }
    case ('d'):
    case ('D'):
    {
        game->adjust_snake(SingleSnake, Turn::RIGHT);
        break;
    }
    }
}

bool SingleServer::initial()
{
    SnakeHandle SingleSnake = snake_handles[0];
    AgentHandle food_handle = agent_handles[1];
    if (game->init_snake(SingleSnake, pos(SINGLESERVER_MAPSIZE / 2, SINGLESERVER_MAPSIZE / 2), Turn::UP) == false)
    {
        return false;
    }
    return game->random_add_food(FOOD_SECOND, food_handle);
}

Map &SingleServer::get_map()
{
    return game->get_map();
}

SingleServer::SingleServer()
{
    Config config = MyConfig();
    game = new DecreteSnake(config);
    state = 1; //good
    this->Add_wall();
}

void SingleServer::Add_wall()
{
    AgentHandle wall_handle = agent_handles[0];
    for (int i = 0; i < SINGLESERVER_MAPSIZE; i++)
    {
        game->add_wall(pos(0, i), wall_handle);
        game->add_wall(pos(i, 0), wall_handle);
        game->add_wall(pos(SINGLESERVER_MAPSIZE - 1, i), wall_handle);
        game->add_wall(pos(i, SINGLESERVER_MAPSIZE - 1), wall_handle);
    }
}

Config SingleServer::MyConfig()
{
    Config config;
    config.set_mapsize(SINGLESERVER_MAPSIZE, SINGLESERVER_MAPSIZE);
    config.set_gamemode(GameMode::Mode_Single);

    RewardType re_wall(0, 0, 0, 0, -1, 0);
    RewardType re_food(1, 0, 0, 0, 0, 0);

    SnakeType snake(5, 1, 1, ColorType::Red, 0);
    AgentType wall(ColorType::Black, re_wall, false);
    AgentType food(ColorType::Blue, re_food, true);

    agent_handles.push_back(config.add_agent(wall));
    agent_handles.push_back(config.add_agent(food));
    snake_handles.push_back(config.add_snake(snake));

    return config;
}

#endif