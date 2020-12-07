#ifndef SYMBOL_DECRETESNAKE
#define SYMBOL_DECRETESNAKE

#include <bits/stdc++.h>
using namespace std;

#include "./Config.h"
#include "./Map.h"
#include "./CleanMode.h"

class DecreteSnake
{
private:
    int length, width;
    GameMode game_mode;
    vector<AgentType> agents;
    vector<SnakeType> snakes;
    Map map;
    int score;

public:
    DecreteSnake(Config config);
    bool init_snake(SnakeHandle snake_handle, pos head, Turn turn);
    bool adjust_snake(SnakeHandle snake_handel, Turn turn);

    int get_speed(SnakeHandle snake_handle) { return snakes[snake_handle].Speed; }

    bool add_wall(pos p, AgentHandle wall_handle);
    bool random_add_wall(int number, AgentHandle wall_handle);

    bool add_food(pos p, AgentHandle food_handle);
    bool random_add_food(int number, AgentHandle food_handle);

    Map &get_map() { return this->map; }

    bool clean_dead(SnakeHandle snake_handle, CleanMode mode);

    bool step(SnakeHandle snake_handle, CleanMode mode);

    bool if_end(SnakeHandle snake_handle, Turn turn);
};

typedef DecreteSnake *GameHandle;

bool DecreteSnake::adjust_snake(SnakeHandle snake_handle, Turn turn)
{
    this->snakes[snake_handle].turn = turn;
    return true;
}

bool DecreteSnake::clean_dead(SnakeHandle snake_handle, CleanMode mode)
{
    SnakeType snake = snakes[snake_handle];
    snake.state = 0;
    int len = snake.bodys.size();
    for (int i = 0; i < len; i++)
    {
        map.delete_body(snake.bodys[i].first, snake.bodys[i].second);
    }
    return true;
}

bool DecreteSnake::step(SnakeHandle snake_handle, CleanMode mode)
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

    MapSlot map_slot = map.get_info(next_x, next_y);
    if (map_slot.slot_type == SlotType::OBSTACLE)
    {
        //wall
        AgentType *wall = (AgentType *)map_slot.container;

        if (wall->reward.add_life < 0)
        {
            clean_dead(snake_handle, mode);
        }
        else
        {
            //do not consider it now
        }
    }
    else if (map_slot.slot_type == SlotType::BUFF)
    {
        //do not consider it now
    }
    else
    {
        OccupyType occ_type = map_slot.occ_type;
        if (occ_type == OccupyType::OCC_NONE)
        {
            //error
            cout << "error" << endl;
            return false;
        }
        else if (occ_type == OccupyType::OCC_FOOD)
        {
            AgentType *food = (AgentType *)map_slot.occupier;
            RewardType re_food = food->reward;
            vector<pos>::iterator it = snakes[snake_handle].bodys.begin();
            map.delete_food(next_x, next_y);
            snakes[snake_handle].bodys.insert(it, pos(next_x, next_y));
            snakes[snake_handle].bodys.pop_back();

            snakes[snake_handle].Length = (snakes[snake_handle].Length + re_food.Length_change) * re_food.Length_multiply;
            snakes[snake_handle].Speed = (snakes[snake_handle].Speed + re_food.Speed_change) * re_food.Speed_multiply;
            snakes[snake_handle].health += re_food.add_life;
            this->score += re_food.add_score;
        }
        else
        {
            //do not consider it;
        }
    }

    return true;
}

bool DecreteSnake::init_snake(SnakeHandle snake_handle, pos head, Turn turn)
{
    int x, y;
    int x_affect, y_affect;
    int i, j;

    if (snakes[snake_handle].state == 0)
    {
        snakes[snake_handle].state = 1;
        snakes[snake_handle].health--;
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
    }
    return true;
}

DecreteSnake::DecreteSnake(Config config) : map(config.length, config.width)
{
    this->length = config.length;
    this->width = config.width;
    this->game_mode = config.game_mode;
    this->agents = config.agents;
    this->snakes = config.snakes;
    this->score = 0;

    srand(time(0));
}

bool DecreteSnake::random_add_food(int number, AgentHandle food_handle)
{
    for (int i = 0; i < number; i++)
    {
        if (map.random_add_food(agents[food_handle]) == false)
            return false;
    }
    return true;
}

bool DecreteSnake::add_food(pos p, AgentHandle food_handle)
{
    return map.add_food(p.first, p.second, agents[food_handle]);
}

bool DecreteSnake::add_wall(pos p, AgentHandle wall_handle)
{
    return map.add_wall(p.first, p.second, agents[wall_handle]);
}
bool DecreteSnake::random_add_wall(int number, AgentHandle wall_handle)
{
    for (int i = 0; i < number; i++)
    {
        if (map.random_add_wall(agents[wall_handle]) == false)
            return false;
    }
    return true;
}

#endif
