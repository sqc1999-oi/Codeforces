#include <iostream>
#include <algorithm>
#include <array>
using namespace std;
array<int, 2000001> a;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int w;
		cin >> w;
		a[w]++;
	}
	int ans = 0;
	for (int i = 0; i < 2e6; i++)
	{
		ans += a[i] % 2;
		a[i + 1] += a[i] / 2;
	}
	cout << ans;
}
