#include "file.h"

vector <int> spoji (vector <int> &a,vector <int> &b)
{
    vector <int> ret;
    auto ita=a.begin(), itb=b.begin();
    while (ita!=a.end() || itb!=b.end())
    {
        if (ita==a.end() || (ita!=a.end() && (*ita)>(*itb)))
            ret.push_back(*itb), itb++;
        else
            ret.push_back(*ita), ita++;
    }
    return ret;
}
