#ifndef SYMBOL_SERVER
#define SYMBOL_SERVER

#include <bits/stdc++.h>
using namespace std;

class Server{
private:
    int length,width;

    Map map;

    SnakeType snake; 
public:
    //init
    Server();
    //destory
    ~Server();
    
    //if key down
    void KeyDown();
    //if mouse click
    void MouseClick();
    
    //if the snake can exist
    bool if_resurgence();
    //maintain die
    void MaintainDie();
    
    //maintain the info when the latest step down
    void Step();
    
    //end
    void End();

};

#endif