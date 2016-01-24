#include "didi.h"
#include "file.h"

#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    vector <int> val;
    int n;
    scanf("%d",&n);
    for (int i=0; i<n; i++)
    {
        int x;
        scanf("%d",&x);
        val.push_back(x);
    }
    val=merge_sort(val);
    for (int i=0; i<n; i++)
        printf("%d ",val[i]);
    return 0;
}
