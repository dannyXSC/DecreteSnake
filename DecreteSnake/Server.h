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

    vector<SnakeHandle> snake_handles;

    vector<AgentHandle> agent_handles;

    //state
    //we return int for the moment
    Server_State state;

public:
    //init
    Server();
    //destory
    ~Server();

    //tools
    virtual Map &get_map() = 0;
    virtual int get_width() = 0;
    virtual int get_length() = 0;

    //initial
    virtual bool initial() = 0;

    //if key down
    virtual void KeyDown(char c) = 0;
    //if mouse click
    //virtual void MouseClick() = 0;

    //maintain the info when the latest step down
    virtual void Step() = 0;

    //end
    virtual void End() = 0;
};

#endif