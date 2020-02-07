#include <iostream>

int gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    y = x1 - (a / b) * y1;
    x = y1;
    return d;
}

int main()
{
    int x, y;
    std::cout << gcd(589, 5111, x, y);
    std::cout <<  " " << x << " " << y;
}
