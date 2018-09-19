#include <iostream>
#include <algorithm>
#include <vector>

int rootSize = 0;
int cnt = 1, ans = 0;
int startTime[100010], minTime[100010];

std::vector< std::vector<int> > g(100010);

void dfs(int index, int parent)
{
    startTime[index] = cnt;
    minTime[index] = cnt;
    ++cnt;
    bool flag = false;

    for (int i = 0; i < g[index].size(); ++i)
    {
        int next = g[index][i];
        if (startTime[next] == 0)
        {
            if (index == 0)
                ++rootSize;

            dfs(next, index);

            minTime[index] = std::min(minTime[index], minTime[next]);

            if (minTime[next] >= startTime[index] && !flag && index != 0)
            {
                flag = true;
                ++ans;
            }
        }
        else if (index != parent)
        {
            minTime[index] = std::min(minTime[index], startTime[next]);
        }
    }
}

int main()
{
    int n, m;

    std::cin >> n >> m;
    cnt = 1;
    rootSize = 0;
    ans = 0;

    for (int i = 0; i < m; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;

        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(0, -1);

    if (rootSize > 1)
        ++ans;

    std::cout << ans;
}
