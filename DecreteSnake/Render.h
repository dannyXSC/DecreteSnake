#ifndef SYMBOL_RENDER
#define SYMBOL_RENDER

#include <bits/stdc++.h>
using namespace std;

#include "./Server.h"

class SnakeRender
{
private:
    Map map;
public:
    //init
    SnakeRender() {}
    //start
    void Start(Server *server);
    void update();
};

void SnakeRender::Start(Server *server)
{
    int length = server->get_length();
    int width = server->get_width();
    while (1)
    {
        if (server->initial() == false)
        {
            //end
            server->End();
            return;
        }
        //else

        map = server->get_map();
        update();

        
    }
}

#endif