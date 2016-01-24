#ifndef _WALKER_H

#define _WALKER_H
#include <vector>
#include "data.h"
#include "state.h"
using namespace std;

struct state;

struct walker
{
    int life;
    vector < pair <tile,int> > pos;
    vector <int> moves;
    pair <int,walker> generate_random_walker (int sx,int sy,int sh,int ttl,state &curr);
};

#endif // _RANDOM_WALKER_H
