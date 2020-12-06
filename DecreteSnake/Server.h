#ifndef SYMBOL_SERVER
#define SYMBOL_SERVER

#include <bits/stdc++.h>
using namespace std;

#include "./Map.h"
#include "./Config.h"
#include "./DecreteSnake.h"

typedef int Server_State;

class Server
{
protected:
    GameHandle game;

    GameMode game_mode;

    int length, width;

    Map map;

    vector<SnakeType> snakes;

    //state
    //we return int for the moment
    Server_State state;

public:
    //init
    Server();
    //destory
    ~Server();

    //tools
    Map &get_map() { return this->map; }
    int get_width() { return this->width; }
    int get_length() { return this->length; }

    //initial
    virtual bool initial() = 0;

    //if key down
    virtual void KeyDown() = 0;
    //if mouse click
    virtual void MouseClick() = 0;

    //if the snake can exist
    virtual bool if_resurgence() = 0;
    //maintain die
    virtual void MaintainDie() = 0;

    //maintain the info when the latest step down
    virtual void Step() = 0;

    //end
    virtual void End() = 0;
};

#endif