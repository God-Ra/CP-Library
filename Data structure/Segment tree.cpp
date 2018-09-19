#include <iostream>
#include <algorithm>

int a[100010], segTree[400010];

void construct(int low, int high, int pos)
{
    if (low == high)
    {
        segTree[pos] = a[low];
        return;
    }

    int mid = low + (high - low) / 2;

    construct(low, mid, pos * 2 + 1);
    construct(mid + 1, high, pos * 2 + 2);

    segTree[pos] = std::min(segTree[pos * 2 + 1], segTree[pos * 2 + 2]);
}

int query(int qlow, int qhigh, int low, int high, int pos)
{
    if (low > qhigh || high < qlow)
        return 1e8;

    if (qlow <= low && high <= qhigh)
    {
        return segTree[pos];
    }

    int mid = low + (high - low) / 2;

    return std::min(query(qlow, qhigh, low, mid, pos * 2 + 1), query(qlow, qhigh, mid + 1, high, pos * 2 + 2));
}

void update(int node, int value, int low, int high, int pos)
{
    if (low > node || high < node)
        return;

    if (low == high && low == node)
    {
        segTree[pos] = value;
        return;
    }

    int mid = low + (high - low) / 2;

    update(node, value, low, mid, pos * 2 + 1);
    update(node, value, mid + 1, high, pos *2 + 2);

    segTree[pos] = std::min(segTree[pos * 2 + 1], segTree[pos * 2 + 2]);
}

int main()
{
    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }

    construct(0, n - 1, 0);

    while (q--)
    {
        int x, one, two;
        std::cin >> x >> one >> two;
        --one;

        if (x == 1)
        {
            update(one, two, 0, n - 1, 0);
        }
        else
        {
            --two;
            std::cout << query(one, two, 0, n - 1, 0) << "\n";
        }
    }
}
