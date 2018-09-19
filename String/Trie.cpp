#include <iostream>

int trie[1000010][26] = { 0 }, cnt = 2, sum[1000010] = { 0 };
int ans;

void trieadd(std::string &str)
{
    int n = str.length();
    int index = 1;

    for (int i = 0; i < n; ++i)
    {
        int val = str[i] - 'a';

        if (trie[index][val] == 0)
        {
            trie[index][val] = cnt;
            ++cnt;
        }

        index = trie[index][val];
        ++sum[index];

        if (i == n - 1)
        {
            ans = sum[index] - 1;
        }
    }
}


int main()
{
    int n;
    std::cin >> n;

    std::string str;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> str;

        trieadd(str);

        std::cout << ans << "\n";
    }
}
