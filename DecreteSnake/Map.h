#ifndef SYMBOL_MAP
#define SYMBOL_MAP

#include <bits/stdc++.h>
using namespace std;

enum class SlotType
{
    BLANK,
    OBSTACLE,
    BUFF
};
enum class OccupyType
{
    OCC_BODY,
    OCC_FOOD
};

class MapSlot
{
public:
    SlotType slot_type;
    OccupyType occ_type;
    void *occupier;
    MapSlot() : slot_type(SlotType::BLANK), occupier(NULL) {}
};

class Map
{
private:
    MapSlot **slots;
    int width, length;

public:
    Map(int length, int width);
    ~Map()
    {
        delete[] slots;
    }

    int add_wall(int x, int y);

    inline bool can_visit(int x, int y);
};

Map::Map(int length, int width)
{
    this->length = length;
    this->width = width;
    this->slots = new MapSlot *[length];
    if (this->slots == NULL)
    {
        //error
        cout << "overflow!" << endl;
        exit(-1);
    }
    for (int i = 0; i < length; i++)
    {
        this->slots[i] = new MapSlot[width];
        if (this->slots[i] == NULL)
        {
            cout << "overflow" << endl;
            exit(-1);
        }
    }
}

inline bool Map::can_visit(int x, int y)
{
    if (x < 0 || y < 0 || x >= length || y >= width)
    {
        return false;
    }
    if (slots[x][y].slot_type == SlotType::BLANK || slots[x][y].slot_type == SlotType::BUFF)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif