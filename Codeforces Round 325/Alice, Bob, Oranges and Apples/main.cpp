#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<long long> v;
long long gcd(long long a, long long b)
{
	if (a%b != 0)
	{
		v.push_back(a / b);
		return gcd(b, a%b);
	}
	else
	{
		v.push_back(a / b - 1);
		return b;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	long long x, y;
	cin >> x >> y;
	if (gcd(max(x, y), min(x, y)) != 1)
		cout << "Impossible";
	else
		for (int i = 0; i < v.size(); i++)
			cout << v[i] << ((i + (x < y)) % 2 == 0 ? 'A' : 'B');
}
