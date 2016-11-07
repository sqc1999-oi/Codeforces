#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <iterator>
using namespace std;
struct edge { int to, t; };
const int N = 5000;
vector<edge> g[N];
vector<int> rg[N];
int in[N], f[N][N + 1][2];
int main()
{
	ios::sync_with_stdio(false);
	int n, m, T;
	cin >> n >> m >> T;
	for (int i = 0; i < m; i++)
	{
		int u, v, t;
		cin >> u >> v >> t;
		u--, v--;
		g[u].push_back({ v,t });
		in[v]++;
		rg[v].push_back(u);
	}
	memset(f, 0xff, sizeof f);
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (in[i] == 0) q.push(i);
	f[0][1][0] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (const edge &e : g[u])
		{
			int v = e.to;
			if (--in[v] == 0) q.push(v);
			for (int i = 1; i < n; i++)
				if (f[u][i][0] > -1 && f[u][i][0] + e.t <= T &&
					(f[v][i + 1][0] == -1 || f[u][i][0] + e.t < f[v][i + 1][0]))
				{
					f[v][i + 1][0] = f[u][i][0] + e.t;
					f[v][i + 1][1] = u;
				}
		}
	}
	int x = N;
	while (f[n - 1][x][0] == -1) x--;
	cout << x << endl;
	vector<int> ans;
	int u = n - 1;
	while (true)
	{
		ans.push_back(u + 1);
		if (u == 0) break;
		u = f[u][x--][1];
	}
	copy(ans.rbegin(), ans.rend(), ostream_iterator<int>(cout, " "));
}
