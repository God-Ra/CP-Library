#include <iostream>

using ull = unsigned long long int;
using ll = long long int;

ll mulmod(ull a, ull b, ull mod)
{
    ull res = 0;
    a %= mod;
    for (; b > 0; b >>= 1)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
    }

    return res;
}

ll powmod(ll a, ll b, ll mod)
{
    a %= mod;
    ll res = 1;
    for (; b > 0; b >>= 1)
    {
        if (b & 1)
            res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
    }

    return res;
}

bool check_composite(ll n, ll r, ll d, ll a)
{
    ll x = powmod(a, d, n);
    if (x == 1 || x == n - 1)
        return false;

    for (int i = 1; i < r; ++i)
    {
        x = mulmod(x, x, n);
        if (x == n - 1)
            return false;
    }

    return true;
}

//returns 1 if prime, otherwise 0
bool MillerRabin(ull n)
{
    if (n < 2)
        return false;
    //for a 32 bit integer, it is enough to check 2, 3, 5, 7
    //for a 64 bit integer, first 12 primes

    int r = 0;
    ull d = n - 1;
    while (!(d & 1))
    {
        d >>= 1;
        ++r;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n == a)
            return true;
        else if (check_composite(n, r, d, a))
            return false;
    }

    return true;
}

int main()
{
    int t;
    std::cin >> t;

    while (t--)
    {
        ull n;
        std::cin >> n;

        std::cout << (MillerRabin(n) ? "YES\n" : "NO\n");
    }
}
