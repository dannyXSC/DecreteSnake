#ifndef SYMBOL_AGENTTYPE
#define SYMBOL_AGENTTYPE

#include <bits/stdc++.h>
using namespace std;

#include "ColorType.h"
#include "RewardType.h"

/*define*/
typedef int AgentHandle;

class AgentType
{
public:
    ColorType color;

    RewardType reward;

    //if eatable
    bool if_eatable;

    AgentType(ColorType color, RewardType reward, bool if_eatable)
        : color(color), reward(reward), if_eatable(if_eatable) {}

    AgentType(AgentType &a)
    {
        this->duplicate(a);
    }

    AgentType &operator=(AgentType &a)
    {
        this->duplicate(a);
        return *this;
    }

private:
    void duplicate(AgentType &a)
    {
        this->color = a.color;
        this->reward = a.reward;
        this->if_eatable = a.if_eatable;
    }
};

#endif
