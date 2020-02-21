#include <iostream>

char a[510][510];
int n, m, q;
int log2[510];

//i1, ilog, j1, jlog
int sparse[510][10][510][10];

void calcLog2()
{
    log2[1] = 0;
    for (int i = 2; i < 505; ++i)
        log2[i] = log2[i / 2] + 1;
}

void calcSparse()
{
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = m - 1; j >= 0; --j)
        {
            sparse[i][0][j][0] = val[i][j];
            for (int k = 0; k < 10; ++k)
            {
                if (k != 0)
                    sparse[i][k][j][0] = std::max(sparse[i][k - 1][j][0],
                                              sparse[std::min(n-1, i + (1 << (k - 1)))][k-1][j][0]);

                for (int l = 1; l < 10; ++l)
                {
                    sparse[i][k][j][l] = std::max(sparse[i][k][j][l - 1],
                                                  sparse[i][k][std::min(m-1, j + (1 << l - 1))][l - 1]);
                }
            }
        }
    }
}

int querySparse(int i1, int j1, int i2, int j2)
{
    int maxi = 0;
    int ilength = i2 - i1 + 1;
    int jlength = j2 - j1 + 1;
    int ilog = log2[ilength];
    int jlog = log2[jlength];

    maxi = std::max(maxi, sparse[i1][ilog][j1][jlog]);
    maxi = std::max(maxi, sparse[i2 + 1 - (1 << ilog)][ilog][j1][jlog]);
    maxi = std::max(maxi, sparse[i1][ilog][j2 + 1 - (1 << jlog)][jlog]);
    maxi = std::max(maxi, sparse[i2 + 1 - (1 << ilog)][ilog][j2 + 1 - (1 << jlog)][jlog]);

    return maxi;
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n >> m >> q;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            std::cin >> a[i][j];

    calcLog2();
}
