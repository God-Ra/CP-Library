#include <iostream>
#include <algorithm>

int sums[100010], roots[100010];

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

bool checkConnectivity(int a, int b)
{
    if (root(a) != root(b))
        return 1;
    else
        return 0;
}

int makeUnion(int a, int b)
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

        if (checkConnectivity(x, y))
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
