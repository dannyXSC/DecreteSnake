#ifndef SYMBOL_DECRETESNAKE
#define SYMBOL_DECRETESNAKE

#include <bits/stdc++.h>
using namespace std;

#include "./Config.h"
#include "./Map.h"
#include "./CleanMode.h"

typedef DecreteSnake* GameHandle;

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

    bool clean_dead(SnakeHandle snake_handle,CleanMode mode);

    bool step(SnakeHandle snake_handle,CleanMode mode);

    bool if_end(SnakeHandle snake_handle,Turn turn);
};

bool DecreteSnake::step(SnakeHandle snake_handle,CleanMode mode)
{
    SnakeType snake = snakes[snake_handle];
    SlotType slot;
    int head_x, head_y;
    int x_affect, y_affect;
    int next_x, next_y;

    head_x = snake.bodys[0].first;
    head_y = snake.bodys[0].second;
    x_affect = Turn_Xaffect[int(snake.turn)];
    y_affect = Turn_Yaffect[int(snake.turn)];
    next_x = head_x + x_affect;
    next_y = head_y + y_affect;

    if (map.can_visit(next_x, next_y) == false)
    {
        //wall
        clean_dead(snake_handle,mode);
    }
}

bool DecreteSnake::init_snake(SnakeHandle snake_handle, pos head, Turn turn)
{
    int x, y;
    int x_affect, y_affect;
    int i, j;

    x = head.first;
    y = head.second;
    x_affect = Turn_Xaffect[int(turn)];
    y_affect = Turn_Yaffect[int(turn)];
    for (j = 0; j < snakes[snake_handle].orignLength; j++)
    {
        if (map.can_visit(x + j * x_affect, y + j * y_affect) == false)
        {
            return false;
        }
    }
    for (j = 0; j < snakes[snake_handle].orignLength; j++)
    {
        map.add_body(x + j * x_affect, y + j * y_affect, snakes[snake_handle]);
        snakes[snake_handle].bodys.push_back(pos(x + j * x_affect, y + j * y_affect));
    }
    snakes[snake_handle].turn = turn;
    return true;
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
