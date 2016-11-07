#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<int> G[100001], f[100001][18];
int d[100001], p[100001][18];
void dfs(int u)
{
	int lg = log2(d[u] + 1);
	for (int i = 1; i <= lg; i++)
	{
		p[u][i] = p[p[u][i - 1]][i - 1];
		f[u][i].resize(f[u][i - 1].size() + f[p[u][i - 1]][i - 1].size());
		set_union(f[u][i - 1].begin(), f[u][i - 1].end(), f[p[u][i - 1]][i - 1].begin(), f[p[u][i - 1]][i - 1].end(), f[u][i].begin());
		if (f[u][i].size() > 10) f[u][i].resize(10);
	}
	for (int v : G[u])
		if (v != p[u][0])
		{
			p[v][0] = u;
			d[v] = d[u] + 1;
			dfs(v);
		}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;
		f[x][0].push_back(i);
	}
	for (int i = 1; i <= n; i++)
	{
		sort(f[i][0].begin(), f[i][0].end());
		if (f[i][0].size() > 10) f[i][0].resize(10);
	}
	dfs(1);
	for (int i = 1; i <= q; i++)
	{
		int u, v, a;
		cin >> u >> v >> a;
		if (d[u] > d[v]) swap(u, v);
		int lg = log2(d[v] - d[u]);
		vector<int> ans, tmp;
		auto up = [&](int &u, int i)
		{
			tmp.resize(ans.size() + f[u][i].size());
			set_union(ans.begin(), ans.end(), f[u][i].begin(), f[u][i].end(), tmp.begin());
			if (tmp.size() > a) tmp.resize(a);
			ans = tmp;
			u = p[u][i];
		};
		auto output = [&]()
		{
			cout << ans.size() << ' ';
			for (int x : ans) cout << x << ' ';
			cout << endl;
		};
		for (int i = lg; i >= 0; i--)
		{
			if (d[v] - (1 << i) < d[u]) continue;
			if (d[u] == d[v]) break;
			up(v, i);
		}
		if (u == v)
		{
			up(u, 0);
			output();
			continue;
		}
		lg = log2(d[u]);
		for (int i = lg; i >= 0; i--)
		{
			if (p[u][i] == p[v][i]) continue;
			up(u, i);
			up(v, i);
		}
		up(u, 1);
		up(v, 0);
		output();
	}
}
