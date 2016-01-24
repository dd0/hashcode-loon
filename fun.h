#ifndef _FUN_H
#define _FUN_H

#include "didi.cpp"
#include "file.cpp"
#include <vector>
#include <algorithm>

using namespace std;

vector <int> spoji (vector <int> const &a, vector <int> const &b) const;
pair <vector <int> , vector <int> > podeli (vector <int> const &a) const;
vector <int> merge_sort(vector <int> const &a) const;

#endif // _FUN_H
