#ifndef SYMBOL_RENDER
#define SYMBOL_RENDER

#include <bits/stdc++.h>
using namespace std;

#include "./Server.h"

#ifdef _WIN32
#include <conio.h>
#elif __APPLE__
#include "./MyConio.h"
#endif

#ifdef _WIN32
#include <Windows.h>
#elif __APPLE__
#include <unistd.h>
#define Sleep(t) usleep(t * 1000)
#endif

class SnakeRender
{
private:
    Map map;

public:
    //init
    SnakeRender() {}
    //start
    void Start(Server *server);
    void update(int l, int w);
};

void SnakeRender::update(int length, int width)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            MapSlot map_slot = map.get_info(i, j);
            if (map_slot.slot_type == SlotType::OBSTACLE)
            {
                cout << "* ";
            }
            else if (map_slot.occ_type == OccupyType::OCC_FOOD)
            {
                cout << "0 ";
            }
            else if (map_slot.occ_type == OccupyType::OCC_BODY)
            {
                cout << "1 ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

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
        update(length, width);

        for (int i = 0; i < 10; i++)
        {
            //get command
            if (kbhit())
            {
                //adjust the turn
                char ch = getch();
                server->KeyDown(ch);
            }
            Sleep(100);
        }
        server->Step();
    }
}

#endif