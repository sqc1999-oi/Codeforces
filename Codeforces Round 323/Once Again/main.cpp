#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;
int a[101], g[101], f[301][301], F[101][301], G[101][301];
const int oo = (1 << 30) - 1;
int main()
{
	ios::sync_with_stdio(false);
	int n, t;
	cin >> n >> t;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	memset(f, 0xc0, sizeof f);
	for (int i = 1; i <= n; i++)
	{
		memset(g, 0xc0, sizeof g);
		g[i] = 1;
		for (int j = i + 1; j <= n; j++)
			for (int k = i; k < j; k++)
				if (a[k] <= a[j])
					g[j] = max(g[j], g[k] + 1);
		for (int j = 1; j <= n; j++)
			if (a[i] <= a[j])
				f[a[i]][a[j]] = max(f[a[i]][a[j]], g[j]);
	}
	memset(F, 0xc0, sizeof F);
	memset(F[0], 0, sizeof F[0]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 300; j++)
		{
			int tmp = -oo;
			for (int k = 1; k <= 300; k++)
			{
				tmp = max(tmp, F[i - 1][k]);
				F[i][j] = max(F[i][j], tmp + f[k][j]);
			}
		}
	memset(G, 0xc0, sizeof G);
	memset(G[0], 0, sizeof G[0]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 300; j++)
		{
			int tmp = -oo;
			for (int k = 300; k >= 1; k--)
			{
				tmp = max(tmp, G[i - 1][k]);
				G[i][j] = max(G[i][j], tmp + f[j][k]);
			}
		}
	int ans = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 1; k <= 300; k++)
				if (i + j <= t && f[k][k] >= 0)
					ans = max(ans, F[i][k] + f[k][k] * (t - i - j) + G[j][k]);
	cout << ans;
}
