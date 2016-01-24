#ifndef _DATA_H
#define _DATA_H

#include <vector>
#include <fstream>

using namespace std;

struct tile
{
	int i, j;
} ;

struct windGrid
{
	static const int N = 1005;
	int di[N][N], dj[N][N]; // delta-i, delta-j
} ;

// data from the input
struct inputData
{
	int n, m, h; // rows, cols, height
	int rad; // coverage radius
	int baloons, time; // number of baloons, simulation length
	vector<tile> targets; // tiles we want to hit
	tile start; // tile where the baloons start
	vector<windGrid> wind; // wind movement grids
	tile get_next_tile (tile curr,int h);
} ;

extern inputData data;

void loadData(const char*);

#endif
