#include "didi.h"
#include "file.h"
#include "data.h"
#include "walker.h"
#include "state.h"

#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int main()
{
    freopen("out.txt","w",stdout);
    srand(time(0));
    printf("MAIN\n"); fflush(stdout);
	loadData("loon.small.in");
	cout << data.n << " " << data.m << endl;
	cout << data.time << endl;
	cout << data.baloons << endl;

    state *stanje=new state(data);


    int total=0;
    pair <int,walker> balon[53];
    for (int it=0; it<53; it++)
    {
        balon[it]=balon[0].second.generate_better_walker(10,10,-1,0,400,*stanje);
        (*stanje).implement_walker(balon[it].second,1);
        total+=balon[it].first;
        printf("%d %d\n",total,balon[it].first);
        fflush(stdout);
    }
    printf("%d\n",53);
    for (int it=0; it<53; it++)
    {
        printf("%d\n",balon[it].second.life);
        for (int i=0; i<balon[it].second.life; i++)
            printf("%d %d\n",balon[it].second.pos[i].first.i,balon[it].second.pos[i].first.j);
        fflush(stdout);
        /*
        for (int i=0; i<balon.second.life; i++)
            printf("[%d] %d %d %d\n",i,balon.second.pos[i].first.i,balon.second.pos[i].first.j,balon.second.pos[i].second);
        */
    }
    delete stanje;

    return 0;
}
