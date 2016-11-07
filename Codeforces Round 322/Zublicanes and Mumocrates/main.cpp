#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
vector<int> G[5001];
int f[5001][5001][2];
int dfs(int u, int fa)
{
	if (G[u].size() == 1)
	{
		f[u][1][1] = f[u][0][0] = 0;
		return 1;
	}
	f[u][0][0] = f[u][0][1] = 0;
	int sum = 0;
	for (int v : G[u])
		if (v != fa)
		{
			int cnt = dfs(v, u);
			sum += cnt;
			for (int i = sum; i >= 0; i--)
			{
				int t0 = INF, t1 = INF;
				for (int j = 0; j <= i && j <= cnt; j++)
				{
					t0 = min(t0, f[u][i - j][0] + min(f[v][j][0], f[v][j][1] + 1));
					t1 = min(t1, f[u][i - j][1] + min(f[v][j][1], f[v][j][0] + 1));
				}
				f[u][i][0] = t0;
				f[u][i][1] = t1;
			}
		}
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	if (n == 2) return cout << 1, 0;
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	int root = 0, maxcnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (G[i].size() > 1) root = i;
		else maxcnt++;
	}
	maxcnt /= 2;
	memset(f, 0x3f, sizeof f);
	dfs(root, 0);
	cout << min(f[root][maxcnt][0], f[root][maxcnt][1]);
}
