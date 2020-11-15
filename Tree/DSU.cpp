#include <iostream>
#include <algorithm>

#define MAXN 1000010

int sums[MAXN], roots[MAXN];

void initialize(int n)
{
    for (int i = 0; i < n; ++i)
    {
        sums[i] = 1;
        roots[i] = i;
    }
}

int root(int index)
{
    while (index != roots[index])
    {
        roots[index] = roots[roots[index]];
        index = roots[index];
    }

    return index;
}

bool areConnected(int a, int b)
{
    return root(a) == root(b);
}

void makeUnion(int a, int b)
{
    a = root(a);
    b = root(b);

    if (sums[a] > sums[b])
        std::swap(a, b);

    roots[a] = b;
    sums[b] += sums[a];
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    initialize(n);

    for (int i = 0; i < m; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;

        if (!areConnected(x, y))
        {
            makeUnion(x, y);
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
    }
}
