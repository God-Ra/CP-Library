#include <iostream>
#include <vector>

std::vector< std::vector<int> > g(100010);
int binary[100010][20] = { 0 };

void dfs(int index, int parent)
{
    if (parent != 0)
    {
        binary[index][0] = parent;
        for (int i = 0; i < 19; ++i)
        {
            binary[index][i] = binary[binary[index][i - 1]][i - 1];
        }
    }
    else
    {
        for (int i = 0; i < 19; ++i)
        {
            binary[index][i] = index;
        }
    }

    for (int i = 0; i < g[index].size(); ++i)
    {
        int next = g[index][i];

        if (next != parent)
            dfs(next, index);
    }
}

int main()
{
    int n;
    std::cin >> n;

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
}
