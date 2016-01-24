#include "walker.h"
#include "data.h"
#include <algorithm>


pair <int,walker> walker :: generate_random_walker(int sx,int sy,int sh,int st,int ttl,state &curr)
{
    //printf("RUN for %d %d %d %d %d\n",sx,sy,sh,st,ttl);
    walker ret;
    int cscore=0;
    ret.life=0;
    tile cpos= {sx,sy};
    int ch=sh;
    while (cpos.i!=-1 && ret.life<ttl)
    {
        int pmove[3];
        int pcnt=0;
        if (ch>0)
            pmove[pcnt++]=-1;
        pmove[pcnt++]=0;
        if (ch<curr.h-1)
            pmove[pcnt++]=1;
        ret.moves.push_back(pmove[rand()%pcnt]);
        ret.pos.push_back({cpos,ch});
        ch+=ret.moves[ret.life];
        if (ch>=0)
            cscore+=curr.get_score_change(cpos.i,cpos.j,ret.life+st,1,0);

        ret.life++;
        if (ttl==1)
            printf("in\n");
        cpos=data.get_next_tile(cpos,ch);
        if (ttl==1)
            printf("OUT\n");
    }
    if (ttl==1)
        printf("Really out\n");
    return {cscore,ret};
}

pair <int,walker> walker :: generate_better_walker(int sx,int sy,int sh,int st,int ttl,state &curr)
{
    walker ret;
    int cscore=0;
    ret.life=0;
    tile cpos= {sx,sy};
    int ch=sh;
    pair <int,walker> cand,cand2;
    while (cpos.i!=-1 && ret.life+1<ttl)
    {
        cand=generate_random_walker(cpos.i,cpos.j,ch,ret.life,ttl-ret.life,curr);
        for (int it=1; it<MAX_BETTER_ATT; it++)
        {
            cand2=generate_random_walker(cpos.i,cpos.j,ch,ret.life,ttl-ret.life,curr);
            if (cand2.first>cand.first)
                cand=cand2;
        }
        cpos=cand.second.pos[1].first;
        ch=cand.second.pos[1].second;
        ret.moves.push_back(cand.second.moves[0]);
        ret.pos.push_back(cand.second.pos[1]);
        ret.life++;
        cscore+=curr.get_score_change(cpos.i,cpos.j,ret.life+st,1,0);
    }
    return {cscore,ret};
}
