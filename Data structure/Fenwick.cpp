#include <iostream>
#include <string>

int fenwick[200010];

void update(int n, int index, int value)
{
	while (index <= n)
	{
		fenwick[index] += value;
		index += index & -index;
	}
}

int sum(int fenwick[], int index)
{
	int sum = 0;
	while (index > 0)
	{
		sum += fenwick[index];
		index -= index & -index;
	}

	return sum;
}

int main()
{

}
