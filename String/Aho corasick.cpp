#include <iostream>
#include <string>
#include <map>
#include <queue>

const int MAXN = 2e6 + 10;

struct aho_corasick
{
    std::map<char, int> to[MAXN];
    int link[MAXN], ptr;
    int last[MAXN];
    int seen[MAXN];
    std::vector< int > which[MAXN];

    void initialize()
    {
        for (int i = 0; i < ptr; ++i)
        {
            link[i] = 0;
            last[i] = 0;
            seen[i] = 0;
            to[i].clear();
        }

        ptr = 1;
    }

    aho_corasick(){ptr = MAXN - 2; initialize();}

    void add_word(std::string &str, int j)
    {
        int cur = 0;

        for (char c : str)
        {
            if (!to[cur].count(c))
                to[cur][c] = ptr++;

            cur = to[cur][c];
        }

        last[cur] = 1;
        which[cur].push_back(j);
    }

    void fillLinks()
    {
        std::queue<int> q;
        q.push(0);
        int nxt;
        char c;

        link[0] = -1;

        while (q.empty() == false)
        {
            int f = q.front();
            q.pop();

            for (auto it : to[f])
            {
                nxt = it.second;
                c = it.first;
                int j = link[f];

                while (j != -1 && !to[j].count(c)) j = link[j];
                if (j != -1)
                    link[nxt] = to[j][c];
                else
                    link[nxt] = 0;

                q.push(nxt);
            }
        }
    }
};

aho_corasick aho;

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::string str;
    std::cin >> str;

    int q;
    std::cin >> q;

    for (int j = 0; j < q; ++j)
    {
        std::string temp;
        std::cin >> temp;

        aho.add_word(temp, j);
    }
    aho.fillLinks();

    bool good[1010] = { 0 };
    int cur = 0;
    int linked = -1;
    for (int i = 0; i < str.length(); ++i)
    {
        if (!aho.to[cur].count(str[i]))
        {
            while (cur != -1 && !aho.to[cur].count(str[i]))
                cur = aho.link[cur];

            if (cur != -1)
                cur = aho.to[cur][str[i]];
            else
                cur = 0;
        }
        else
            cur = aho.to[cur][str[i]];

        linked = cur;
        while (linked != -1 && !aho.seen[linked])
        {
            aho.seen[linked] = true;
            if (aho.last[linked] == 1)
            {
                for (auto i : aho.which[linked])
                    good[i] = 1;

                aho.which[linked].clear();
            }

            linked = aho.link[linked];
        }
    }

    int ans = 0;
    for (int i = 0; i < q; ++i)
        std::cout << (good[i] == 0 ? "N\n" : "Y\n");
}
