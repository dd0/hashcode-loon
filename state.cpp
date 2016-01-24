#include "state.h"
#include <algorithm>
#include <cstring>
using namespace std;

int state :: get_score_change(int x,int y,int t,int action,int make_change)
{
    int ret=0;
    for (int cx=max(0,x-rad); cx<=min(n-1,x+rad); cx++)
        for (int cy=y-rad; cy<=y+rad; cy++)
            if ((cx-x)*(cx-x)+(cy-y)*(cy-y)<=rad*rad)
            {
                int i=cx;
                int j=cy;
                if (j<0)
                    j+=m;
                if (j>=m)
                    j-=m;

                if (action==1)
                {
                    if (times_covered[i][j][t]==0)
                        ret+=score_per_visit[i][j];
                    if (make_change==1)
                        times_covered[i][j][t]++;
                }
                else
                {
                    if (times_covered[i][j][t]==0)
                        printf("ERROR: Deleting non-existing loons!\n");
                    if (times_covered[i][j][t]==1)
                        ret-=score_per_visit[i][j];
                    if (make_change)
                        times_covered[i][j][t]--;
                }
            }
    return ret;
}

state :: state (inputData const &in)
{
    n=in.n;
    m=in.m;
    h=in.h;
    rad=in.rad;
    memset(times_covered,0,sizeof(times_covered));
    memset(score_per_visit,0,sizeof(score_per_visit));
    for (unsigned int i=0; i<in.targets.size(); i++)
        score_per_visit[in.targets[i].i][in.targets[i].j]=1;
}
