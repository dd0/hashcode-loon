#include "didi.h"
#include "file.h"
#include "data.h"

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	loadData("loon.in");
	cout << data.n << " " << data.m << endl;
    return 0;
}
