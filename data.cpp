#include "data.h"

inputData data;

void loadData(const char *fname)
{
	ifstream fin(fname);

	fin >> data.n >> data.m >> data.h;
	int n_targets;
	fin >> n_targets >> data.rad >> data.baloons >> data.time;
	fin >> data.start.i >> data.start.j;
	for(int i = 0; i < n_targets; i++)
	{
		tile x;
		fin >> x.i >> x.j;
		data.targets.push_back(x);
	}
	for(int ii = 0; ii < data.h; ii++)
	{
		windGrid *g = new windGrid;
		for(int i = 0; i < data.n; i++)
			for(int j = 0; j < data.m; j++)
				fin >> g->di[i][j] >> g->dj[i][j];
		data.wind.push_back(*g);
		delete g;
	}
}
