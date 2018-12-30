#include <iostream>
#include <map>

std::map<int, int> primes;

int main()
{
    int n;

    std::cin >> n;

    int tempn = n;

    for (int i = 2; i * i <= n && n != 1; ++i)
    {
        while (n % i == 0 && n != 1)
        {
            ++primes[i];
            n /= i;
        }
    }

    if (n != 1)
        ++primes[n];
}