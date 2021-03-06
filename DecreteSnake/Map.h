#ifndef SYMBOL_MAP
#define SYMBOL_MAP

#include <bits/stdc++.h>
using namespace std;

#include "./AgentType.h"
#include "./SnakeType.h"

enum class SlotType
{
    BLANK,
    OBSTACLE,
    BUFF
};
enum class OccupyType
{
    OCC_NONE,
    OCC_BODY,
    OCC_FOOD
};

class MapSlot
{
public:
    SlotType slot_type;
    OccupyType occ_type;
    void *occupier;
    void *container;
    MapSlot() : slot_type(SlotType::BLANK), occ_type(OccupyType::OCC_NONE), occupier(NULL), container(NULL) {}
};

class Map
{
private:
    MapSlot **slots;
    int width, length;
    default_random_engine random;

    void duplicate(Map &m)
    {
        this->slots = m.slots;
        this->width = m.width;
        this->length = m.length;
        this->random = m.random;
    }

public:
    Map(int length, int width);
    Map(Map &m) { duplicate(m); }
    ~Map()
    {
        delete[] slots;
    }
    Map &operator=(Map &m)
    {
        duplicate(m);
        return *this;
    }

    void set_random(default_random_engine &random) { this->random = random; };

    bool add_wall(int x, int y, AgentType &wall);
    bool add_buff(int x, int y, AgentType &buff);
    bool add_food(int x, int y, AgentType &food);
    bool add_body(int x, int y, SnakeType &body);

    //delete
    AgentType *delete_wall(int x, int y);
    AgentType *delete_buff(int x, int y);
    AgentType *delete_food(int x, int y);
    SnakeType *delete_body(int x, int y);

    //random
    bool random_add_wall(AgentType &wall);
    bool random_add_buff(AgentType &buff);
    bool random_add_food(AgentType &food);

    inline bool can_visit(int x, int y);
};

bool Map::random_add_food(AgentType &food)
{
    for (int i = 0; i < length * width; i++)
    {
        int x = this->random() % this->length;
        int y = this->random() % this->width;
        if (slots[x][y].slot_type != SlotType::OBSTACLE && slots[x][y].occ_type == OccupyType::OCC_NONE)
        {
            slots[x][y].occ_type = OccupyType::OCC_FOOD;
            slots[x][y].occupier = &food;
            return true;
        }
    }
    return false;
}

bool Map::random_add_buff(AgentType &buff)
{
    for (int i = 0; i < length * width; i++)
    {
        int x = this->random() % this->length;
        int y = this->random() % this->width;
        if (slots[x][y].slot_type == SlotType::BLANK)
        {
            slots[x][y].slot_type = SlotType::BUFF;
            slots[x][y].container = &buff;
            return true;
        }
    }
    return false;
}

bool Map::random_add_wall(AgentType &wall)
{
    while (1)
    {
        int x = this->random() % this->length;
        int y = this->random() % this->width;
        if (slots[x][y].slot_type != SlotType::OBSTACLE)
        {
            slots[x][y].slot_type = SlotType::OBSTACLE;
            slots[x][y].occ_type = OccupyType::OCC_NONE;
            slots[x][y].occupier = NULL;
            slots[x][y].container = &wall;
            return true;
        }
    }
    return false;
}

AgentType *Map::delete_buff(int x, int y)
{
    if (slots[x][y].slot_type == SlotType::BUFF)
    {
        AgentType *p = (AgentType *)slots[x][y].container;
        slots[x][y].slot_type = SlotType::BLANK;
        slots[x][y].container = NULL;
        return p;
    }
    return NULL;
}

AgentType *Map::delete_wall(int x, int y)
{
    if (!can_visit(x, y))
    {
        AgentType *p = (AgentType *)slots[x][y].container;
        slots[x][y].slot_type = SlotType::BLANK;
        slots[x][y].occ_type = OccupyType::OCC_NONE;
        slots[x][y].occupier = NULL;
        slots[x][y].container = NULL;
        return p;
    }
    return NULL;
}

SnakeType *Map::delete_body(int x, int y)
{
    if (can_visit(x, y) && slots[x][y].occ_type == OccupyType::OCC_BODY)
    {
        SnakeType *p = (SnakeType *)slots[x][y].occupier;
        slots[x][y].occ_type = OccupyType::OCC_NONE;
        slots[x][y].occupier = NULL;
        return p;
    }
    return NULL;
}

AgentType *Map::delete_food(int x, int y)
{
    if (can_visit(x, y) && slots[x][y].occ_type == OccupyType::OCC_FOOD)
    {
        AgentType *p = (AgentType *)slots[x][y].occupier;
        slots[x][y].occ_type = OccupyType::OCC_NONE;
        slots[x][y].occupier = NULL;
        return p;
    }
    return NULL;
}

bool Map::add_buff(int x, int y, AgentType &buff)
{
    if (!can_visit(x, y))
    {
        return false;
    }
    slots[x][y].slot_type = SlotType::BUFF;
    slots[x][y].container = &buff;
    return true;
}

bool Map::add_body(int x, int y, SnakeType &body)
{
    if (!can_visit(x, y))
    {
        return false;
    }
    slots[x][y].occ_type = OccupyType::OCC_BODY;
    slots[x][y].occupier = &body;
    return true;
}

bool Map::add_food(int x, int y, AgentType &food)
{
    if (!can_visit(x, y))
    {
        return false;
    }
    slots[x][y].occ_type = OccupyType::OCC_FOOD;
    slots[x][y].occupier = &food;
    return true;
}

bool Map::add_wall(int x, int y, AgentType &wall)
{
    if (can_visit(x, y))
    {
        return false;
    }
    slots[x][y].slot_type = SlotType::OBSTACLE;
    slots[x][y].occ_type = OccupyType::OCC_NONE;
    slots[x][y].container = &wall;
    return true;
}

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