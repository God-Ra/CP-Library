#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

int mini[100010], curi[100010], cnt = 0;
int component[100010];
bool in_stack[100010] = { 0 };

std::stack<int> st;
std::vector< std::vector<int> > scc;

void dfs(int index)
{
    curi[index] = cnt;
    mini[index] = cnt;
    in_stack[index] = true;
    ++cnt;

    st.push_back(index);
    int next, sz = g[index].size();
    for (int i = 0; i < sz; ++i)
    {
        next = g[index][i];
        if (curi[next] != -1)
        {
            dfs(next);

            mini[index] = std::min(mini[index], mini[next]);
        }
        else if (in_stack[next])
            mini[index] = std::min(mini[index], curi[next]);
    }

    if (mini[index] == curi[index])
    {
        scc.push_back(std::vector<int> ());

        while (st.top() != index)
        {
            scc[scc.size() - 1].push_back(st.top());
            in_stack[st.top()] = false;
            st.pop();
        }

        scc[scc.size() - 1].push_back(index);
        in_stack[index] = false;
        st.pop();
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        mini[i] = -1;
        curi[i] = -1;
    }

    while (m--)
    {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;

        g[x].push_back(y);
    }

    for (int i = 0; i < n; ++i)
    {
        if (curi[i] == -1)
        {
            dfs(i);
        }
    }

    for (int i = 0; i < scc.size(); ++i)
    {
        for (int j = 0; j < scc[i].size(); ++j)
        {
            component[scc[i][j]] = i;
        }
    }
}
