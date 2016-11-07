#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 200;
struct edge
{
	int to, id;
	bool f;
};
vector<edge> g[N];
int deg[N], gid[N];
bool vis_v[N], vis_e[N*(N - 1) / 2 + N / 2];
vector<pair<int, int>> ans;
void dfs_fill(int u, int id)
{
	gid[u] = id;
	for (const edge &e : g[u])
		if (gid[e.to] == -1)
			dfs_fill(e.to, id);
}
void dfs(int u, int x)
{
	vis_v[u] = true;
	for (const edge &e : g[u])
		if (!vis_e[e.id])
		{
			vis_e[e.id] = true;
			deg[u]--;
			deg[e.to]--;
			if (!e.f) ans.push_back({ u + 1,e.to + 1 });
			if (e.to != x) dfs(e.to, x);
			break;
		}
}
int solve(int id, int n, int m)
{
	memset(deg, 0x00, sizeof deg);
	for (int i = 0; i < n; i++)
		if (gid[i] == id)
			for (const edge &e : g[i])
			{
				deg[i]++;
				deg[e.to]++;
			}
	for (int i = 0; i < n; i++) deg[i] /= 2;
	vector<int> odd;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (gid[i] == id)
			if (deg[i] % 2 == 1) odd.push_back(i);
			else sum++;
	}
	for (int i = 0; i < odd.size(); i += 2)
	{
		g[odd[i]].push_back({ odd[i + 1],m + i / 2,true });
		g[odd[i + 1]].push_back({ odd[i],m + i / 2,true });
		deg[odd[i]]++;
		deg[odd[i + 1]]++;
	}
	memset(vis_v, 0x00, sizeof vis_v);
	memset(vis_e, 0x00, sizeof vis_e);
	for (int i = 0; i < n; i++)
		if (gid[i] == id)
		{
			dfs(i, i);
			break;
		}
	while (true)
	{
		bool flag = false;
		for (int i = 0; i < n; i++)
			if (gid[i] == id && vis_v[i] && deg[i] > 0)
			{
				dfs(i, i);
				flag = true;
				break;
			}
		if (!flag) break;
	}
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) g[i].clear();
		memset(deg, 0x00, sizeof deg);
		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			u--, v--;
			g[u].push_back({ v,i,false });
			g[v].push_back({ u,i,false });
		}
		memset(gid, 0xff, sizeof gid);
		int cnt = 0, sum = 0;
		ans.clear();
		for (int i = 0; i < n; i++)
			if (gid[i] == -1)
			{
				dfs_fill(i, cnt);
				sum += solve(cnt++, n, m);
			}
		cout << sum << endl;
		for (const auto &p : ans) cout << p.first << ' ' << p.second << endl;
	}
}
