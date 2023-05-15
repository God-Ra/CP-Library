#include <iostream>

bool is_prime[100010] = { 0 };

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i <= n; ++i)
    {
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;

    for (int i = 2; i <= n; ++i)
    {
        if (is_prime[i] == 1)
        {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = 0;
        }
    }
}
