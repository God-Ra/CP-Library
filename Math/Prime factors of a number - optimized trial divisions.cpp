#include <iostream>
#include <vector>
#include <map>

std::vector<int> findPrimes(int n) {
    bool composite[100010] = { 0 };
    std::vector<int> primes;

    for (int i = 2; i <= n; ++i)
    {
        if (!composite[i])
        {
            primes.push_back(i);
            for (int j = i * i; j <= n; j += i) {
                composite[j] = true;
            }
        }
    }

    return primes;
}

std::map<int, int> factorize(int n, std::vector<int>& primes) {
    std::map<int, int> factors;
    int i = 0;

    while (primes[i] * primes[i] <= n && n > 1) {
        while (n % primes[i] == 0 && n > 1) {
            n /= primes[i];
            ++factors[primes[i]];
        }

        ++i;
    }

    if (n > 1)
        ++factors[n];
    
    return factors;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> primes = findPrimes(n);
    std::map<int, int> factors = factorize(n, primes);
    for (auto it : factors) {
        std::cout << it.first << " " << it.second << "\n";
    }
}
