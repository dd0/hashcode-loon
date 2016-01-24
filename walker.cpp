#include "walker.h"
#include "data.h"
#include <algorithm>


pair <int,walker> walker :: generate_random_walker(int sx,int sy,int sh,int ttl,state &curr)
{
        walker ret;
        int cscore=0;
        ret.life=0;
        tile cpos={sx,sy};
        int ch=sh;
        while (cpos.i!=-1 && ret.life<ttl)
        {
            printf("%d %d %d %d\n",cpos.i,cpos.j,ch,ret.life);
            int pmove[3];
            int pcnt=0;
            if (ch>0)
                pmove[pcnt++]=-1;
            pmove[pcnt++]=0;
            if (ch<curr.h-1)
                pmove[pcnt++]=1;
            ret.moves.push_back(pmove[rand()%pcnt]);
            ch+=ret.moves[ret.life];
            //printf("H DH %d %d\n",ch,ret.moves[ret.life]);
            ret.pos.push_back({cpos,ch});

            if (ch>=0)
                cscore+=curr.get_score_change(cpos.i,cpos.j,ret.life,1,0);

            ret.life++;
            cpos=data.get_next_tile(cpos,ch);
        }

        return {cscore,ret};
}
