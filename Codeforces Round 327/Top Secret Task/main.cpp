#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;
const int N = 150;
int q[N], f[2][N + 1][N*(N - 1) / 2 + 1];
int main()
{
	ios::sync_with_stdio(false);
	int n, k, s;
	cin >> n >> k >> s;
	for (int i = 0; i < n; i++) cin >> q[i];
	if (s >= (n*2 - k - 1)*k / 2)
	{
		sort(q, q + n);
		int sum = 0;
		for (int i = 0; i < k; i++) sum += q[i];
		cout << sum;
	}
	else
	{
		memset(f[1], 0x3f, sizeof f[1]);
		f[1][0][0] = 0;
		int cu = 0;
		for (int i = 0; i < n; i++)
		{
			memset(f[cu], 0x3f, sizeof f[cu]);
			for (int j = 0; j <= k && j <= i; j++)
				for (int l = 0; l <= s && l <= (i*2 - j - 1)*j / 2; l++)
				{
					if (l + i - j <= s && j < k) f[cu][j + 1][l + i - j] = min(f[cu][j + 1][l + i - j], f[cu ^ 1][j][l] + q[i]);
					f[cu][j][l] = min(f[cu][j][l], f[cu ^ 1][j][l]);
				}
			cu ^= 1;
		}
		int ans = INT_MAX;
		for (int i = 0; i <= s; i++) ans = min(ans, f[cu ^ 1][k][i]);
		cout << ans;
	}
}
