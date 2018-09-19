#include <iostream>
#include <algorithm>
#include <vector>

int start[100010], who[200010], segTree[800010];
int cnt = 0;
std::vector< std::vector<int> > g(100010);

void dfs(int index, int parent)
{
    start[index] = cnt;
    who[cnt] = index;
    ++cnt;

    for (int i = 0; i < g[index].size(); ++i)
    {
        int next = g[index][i];

        if (next != parent)
        {
            dfs(next, index);

            who[cnt] = index;
            ++cnt;
        }
    }
}

void construct(int low, int high, int pos)
{
    if (low == high)
    {
        segTree[pos] = start[who[low]];
        return;
    }

    int mid = low + (high - low) / 2;

    construct(low, mid, pos * 2 + 1);
    construct(mid + 1, high, pos * 2 + 2);

    segTree[pos] = std::min(segTree[pos * 2 + 1], segTree[pos * 2 + 2]);
}

int query(int qlow, int qhigh, int low, int high, int pos)
{
    if (high < qlow || low > qhigh)
        return 1e8;

    if (qlow <= low && high <= qhigh)
    {
        return segTree[pos];
    }

    int mid = low + (high - low) / 2;

    return std::min(query(qlow, qhigh, low, mid, pos * 2 + 1), query(qlow, qhigh, mid + 1, high, pos * 2 + 2));
}

int main()
{
    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i < n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;

        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(0, -1);
    construct(0, cnt - 1, 0);

    while(q--)
    {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;

        if (start[x] > start[y])
            std::swap(x, y);

        std::cout << who[query(start[x], start[y], 0, cnt - 1, 0)] + 1;
    }
}
