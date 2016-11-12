#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e5;
int l[N], r[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, ls = 0, rs = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> l[i] >> r[i];
		ls += l[i];
		rs += r[i];
	}
	int max = abs(ls - rs), ans = -1;
	for (int i = 0; i < n; i++)
	{
		int x = abs((ls - l[i] + r[i]) - (rs - r[i] + l[i]));
		if (x > max)
		{
			max = x;
			ans = i;
		}
	}
	cout << ans + 1 << endl;
}