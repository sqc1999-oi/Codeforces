#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
using namespace std;
int a[102], f[2][101];
int main()
{
	ios::sync_with_stdio(false);
	int n, t;
	cin >> n >> t;
	map<int, int> cnt;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		cnt[a[i]]++;
	}
	for (int i = 1; i <= n; i++)
		f[0][i] = f[1][i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (a[j] >= a[i])
				f[0][j] = max(f[0][j], f[0][i] + 1);
	if (t == 1) return cout << f[0][n], 0;
	for (int i = n; i > 0; i--)
		for (int j = i - 1; j > 0; j--)
			if (a[j] <= a[i])
				f[1][j] = max(f[1][j], f[1][i] + 1);
	int ans = 0;
	a[n + 1] = INT_MAX;
	for (int i = 0; i <= n; i++)
		for (int j = 1; j < n + 1; j++)
			if (a[i] <= a[j])
				ans = max(ans, f[0][i] + f[1][j]);
				/*
				for (int k = 1; k <= n; k++)
					if (a[i] <= a[k] && a[k] <= a[j])
						ans = max(ans, f[0][i] + (t - 2)*cnt[a[k]] + f[1][j]);
				*/
	cout << ans;
}