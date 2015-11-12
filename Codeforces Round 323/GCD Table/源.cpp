#include <iostream>
#include <algorithm>
#include <map>
#include <functional>
using namespace std;
int a[501];
int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	map<int, int, greater<int> > m;
	for (int i = 1; i <= n*n; i++)
	{
		int x;
		cin >> x;
		m[x]++;
	}
	for (int i = 1; i <= n; i++)
	{
		a[i] = m.begin()->first;
		for (int j = 1; j <= i; j++)
		{
			map<int, int, greater<int> >::iterator it = m.find(gcd(a[i], a[j]));
			if ((it->second -= 1 + (i != j)) == 0) m.erase(it);
		}
		cout << a[i] << ' ';
	}
}