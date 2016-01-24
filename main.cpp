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
    srand(time(0));
    printf("MAIN\n"); fflush(stdout);
	loadData("loon.in");
	cout << data.n << " " << data.m << endl;
	cout << data.time << endl;
	cout << data.baloons << endl;

    state *stanje=new state(data);



    pair <int,walker> balon;

    balon=balon.second.generate_better_walker(10,10,-1,0,400,*stanje);
    printf("DID GENERATE\n");
    for (int i=0; i<balon.second.life; i++)
        printf("[%d] %d %d %d\n",i,balon.second.pos[i].first.i,balon.second.pos[i].first.j,balon.second.pos[i].second);
    printf("%d\n",balon.first);
    delete stanje;
    return 0;
}
