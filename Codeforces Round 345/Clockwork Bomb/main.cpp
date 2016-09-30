#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5e5;
vector<int> g[N], t[N];
int fg[N], ft[N], f[N];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void dfs_fa(int u, int fa, const vector<int> *g, int *f)
{
	for (int v : g[u])
		if (v != fa)
		{
			f[v] = u;
			dfs_fa(v, u, g, f);
		}
}
void dfs(int u, int fa)
{
	for (int v : g[u])
		if (v != fa)
		{
			dfs(v, u);
			if (find(u) != find(v))
				cout << u + 1 << ' ' << v + 1 << ' ' << find(v) + 1 << " " << ft[find(v)] + 1 << endl;
		}
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		int x, y;
		cin >> x >> y;
		x--, y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 0; i < n - 1; i++)
	{
		int x, y;
		cin >> x >> y;
		x--, y--;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	dfs_fa(0, -1, g, fg);
	dfs_fa(0, -1, t, ft);
	for (int i = 0; i < n; i++) f[i] = i;
	int cnt = 0;
	for (int v = 1; v < n; v++)
	{
		int u = ft[v];
		if (fg[v] == u || fg[u] == v) f[find(v)] = find(u);
		else cnt++;
	}
	cout << cnt << endl;
	dfs(0, -1);
}
