#ifndef _STATE_H

#define _STATE_H

#include "walker.h"
#include "data.h"
#include <vector>
using namespace std;

struct walker;

struct state
{
    state () {};
    state (inputData const &in);

    int n,m,t; //rows, cols, #of ticks
    int rad; //coverage radius
    int h; //height

    int times_covered [80][305][405];
    int score_per_visit [80][305];
  //  vector <walker> loons;

    int get_score_change(int x,int y,int time,int action,int make_change);
    void implement_walker (walker balon,int action);
};

#endif // _STATE_H
