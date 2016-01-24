#include "didi.h"

pair<vector<int>, vector<int>> podeli(vector<int> &a)
{
	vector<int> x, y;
	for(int i = 0; i < (int)a.size(); i++)
		if(i % 2 == 0)
			x.push_back(a[i]);
		else
			y.push_back(a[i]);
	return pair<vector<int>, vector<int>>(x,y);
}

vector<int> merge_sort(vector<int> &a)
{
	if(a.size() <= 1) return a;
	auto x = podeli(a);
	x.first=merge_sort(x.first);
	x.second=merge_sort(x.second);
	return spoji(x.first, x.second);
}
