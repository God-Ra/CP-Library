#include <iostream>

long long int mod = 1e9 + 7;

long long int modpow(long long int a, long long int b)
{
    a %= mod;
    long long int res = 1;

    for (; b > 0; b >>= 1)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
    }

    return res;
}

int main()
{
    long long int a, b;
    std::cin >> a >> b;

    std::cout << modpow(a, b);
}
