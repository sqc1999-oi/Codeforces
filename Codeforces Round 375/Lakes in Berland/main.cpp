#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 50;
char a[N][N + 1];
int g[N][N];
bool flag[N*N];
pair<int, int> cnt[N*N], pos[N*N];
bool dfs(int x, int y, int id, int n, int m)
{
	if (x == -1 || x == n || y == -1 || y == m) return false;
	if (a[x][y] == '*' || g[x][y] != -1) return true;
	g[x][y] = id;
	cnt[id].first++;
	bool flag = true;
	flag &= dfs(x + 1, y, id, n, m);
	flag &= dfs(x - 1, y, id, n, m);
	flag &= dfs(x, y + 1, id, n, m);
	flag &= dfs(x, y - 1, id, n, m);
	return flag;
}
void dfs_fill(int x, int y, int n, int m)
{
	if (x == -1 || x == n || y == -1 || y == m || a[x][y] == '*') return;
	a[x][y] = '*';
	dfs_fill(x + 1, y, n, m);
	dfs_fill(x - 1, y, n, m);
	dfs_fill(x, y + 1, n, m);
	dfs_fill(x, y - 1, n, m);
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	memset(g, 0xff, sizeof g);
	int id = 0, sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (a[i][j] != '*' && g[i][j] == -1)
			{
				if (flag[id] = dfs(i, j, id, n, m)) sum++;
				pos[id] = { i,j };
				cnt[id].second = id;
				id++;
			}
	sort(cnt, cnt + id);
	int ans = 0;
	for (int i = 0; i < id&&sum > k; i++)
		if (flag[cnt[i].second])
		{
			ans += cnt[i].first;
			dfs_fill(pos[cnt[i].second].first, pos[cnt[i].second].second, n, m);
			sum--;
		}
	cout << ans << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) cout << a[i][j];
		cout << endl;
	}
}
