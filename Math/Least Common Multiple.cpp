#include <iostream>

long long int gcd(long long int a, long long int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main()
{
    long long int a, b;
    std::cin >> a >> b;

    long long int answer = (a*b) / gcd(a, b);
    std::cout << answer;
}
