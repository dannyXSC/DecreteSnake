#ifndef SYMBOL_DECRETESNAKE
#define SYMBOL_DECRETESNAKE

#include <bits/stdc++.h>
using namespace std;

#include "./Config.h"
#include "./Map.h"

class DecreteSnake
{
private:
    int length, width;
    GameMode game_mode;
    vector<AgentType> agents;
    vector<SnakeType> snakes;
    Map map;
    default_random_engine random;

public:
    DecreteSnake(Config config);
    bool init_snake(SnakeHandle snake_handle, pos head, Turn turn);
    bool add_wall(vector<pos> list, AgentType &wall);
    bool random_add_wall(int number, AgentType &wall);

    bool add_food(vector<pos> list, AgentType &food);
    bool random_add_food(int number, AgentType &food);

    Map &get_map() { return this->map; }

    bool step();
};

bool DecreteSnake::init_snake(SnakeHandle snake_handle, pos head, Turn turn)
{
    int x, y;
    int x_affect, y_affect;
    int i, j;
    for (i = 0; i < list_head.size(); i++)
    {
        x = list_head[i].first;
        y = list_head[i].second;
        x_affect = Turn_Xaffect[int(list_turn[i])];
        y_affect = Turn_Yaffect[int(list_turn[i])];
        for (j = 0; j < snakes[snake_handles[i]].orignLength; j++)
        {
            if (map.can_visit(x + j * x_affect, y + j * y_affect) == false)
            {
                return false;
            }
        }
        for (j = 0; j < snakes[snake_handles[i]].orignLength; j++)
        {
            map.add_body(x + j * x_affect, y + j * y_affect, snakes[snake_handles[i]]);
        }
    }
}

bool DecreteSnake::step()
{
}

DecreteSnake::DecreteSnake(Config config) : map(config.length, config.width)
{
    this->length = config.length;
    this->width = config.width;
    this->game_mode = config.game_mode;
    this->agents = config.agents;
    this->snakes = config.snakes;

    random.seed(time(0));
    map.set_random(random);
}

bool DecreteSnake::random_add_food(int number, AgentType &food)
{
    for (int i = 0; i < number; i++)
    {
        map.random_add_food(food);
    }
    return true;
}

bool DecreteSnake::add_food(vector<pos> list, AgentType &food)
{
    int len = list.size();
    for (int i = 0; i < len; i++)
    {
        map.add_food(list[i].first, list[i].second, food);
    }
    return true;
}

bool DecreteSnake::add_wall(vector<pos> list, AgentType &wall)
{
    int len = list.size();
    for (int i = 0; i < len; i++)
    {
        map.add_wall(list[i].first, list[i].second, wall);
    }
    return true;
}
bool DecreteSnake::random_add_wall(int number, AgentType &wall)
{
    for (int i = 0; i < number; i++)
    {
        map.random_add_wall(wall);
    }
    return true;
}

#endif
