#include <iostream>

int trie[400010][2] = { 0 }, sum[800010] = { 0 };
int cnt = 2;

void add(int nr, int diff)
{
    int i = 1;
    for (int j = 30; j >= 0; --j)
    {
        int val = ((nr & (1 << j)) > 0);
        if (trie[i][val] == 0)
        {
            trie[i][val] = cnt;
            ++cnt;
        }

        ++sum[trie[i][val]];
        i = trie[i][val];
    }
}

int main()
{

}
