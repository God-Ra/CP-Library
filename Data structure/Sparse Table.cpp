#include <iostream>
#include <algorithm>

#define NMAX 50010

int sparse[NMAX][17];
int logtu[NMAX];
int n, m;
int a[NMAX];

void calcLog2()
{
    logtu[1] = 0;
    for (int i = 2; i <= NMAX - 2; ++i)
        logtu[i] = logtu[i/2] + 1;

}

void calcSparse()
{
    for (int i = 0; i < n; ++i)
        sparse[i][0] = a[i];

    for (int j = 1; j < 17; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            sparse[i][j] = std::max(sparse[i][j - 1], sparse[std::min(n - 1, i + (1 << (j - 1)))][j - 1]);
        }
    }
}

int querySparse(int l, int r)
{
    int log = logtu[r - l + 1];

    return std::max(sparse[l][log], sparse[r - (1 << log)][log]);
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    calcLog2();

    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];

    calcSparse();

    int cnt = 0;
    while (m--)
    {
        int l, r;
        std::cin >> l >> r;
        --l;
        --r;

        std::cout << querySparse(l, r) << " ";
    }
}
