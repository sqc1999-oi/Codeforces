#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 2e5;
int c[N], cnt[N], l[N], r[N];
bool vis[N * 2];
vector<int> g[N * 2];
void add_edge(int u, int v)
{
	g[u].push_back(v);
	g[v].push_back(u);
}
vector<int> bfs(int x)
{
	vector<int> nodes;
	queue<int> q;
	q.push(x);
	vis[x] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		nodes.push_back(u);
		for (int v : g[u])
			if (!vis[v])
			{
				vis[v] = true;
				q.push(v);
			}
	}
	return nodes;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
		c[i]--;
	}
	for (int i = 0; i < m; i++)
	{
		cin >> l[i] >> r[i];
		l[i]--, r[i]--;
		add_edge(l[i], n + i);
		add_edge(r[i], n + i);
	}
	int ans = 0;
	for (int i = n; i < n + m; i++)
		if (!vis[i])
		{
			auto v = bfs(i);
			int t = 0;
			for (int x : v)
				if (x < n) t = max(t, ++cnt[c[x]]);
			ans += count_if(v.begin(), v.end(), [n](int x) { return x < n; }) - t;
			for (int x : v)
				if (x < n) cnt[c[x]]--;
		}
	cout << ans << endl;
}
