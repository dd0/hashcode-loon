#include "didi.h"
#include "file.h"
#include "data.h"
<<<<<<< cae46c492f792786cf38d79e535a575bb4017824
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
<<<<<<< cae46c492f792786cf38d79e535a575bb4017824
	cout << data.n << " " << data.m << endl;
	cout << data.time << endl;
	cout << data.baloons;

    state *stanje=new state(data);



    pair <int,walker> balon;
    balon.second.life;

    balon=balon.second.generate_random_walker(10,10,-1,400,*stanje);
    delete stanje;

    return 0;
}
