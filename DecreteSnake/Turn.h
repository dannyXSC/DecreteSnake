#ifndef SYMBOL_TURN
#define SYMBOL_TURN

enum class Turn
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const int Turn_Xaffect[] = {0, 0, -1, 1};
const int Turn_Yaffect[] = {-1, 1, 0, 0};

#endif