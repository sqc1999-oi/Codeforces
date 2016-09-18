#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
namespace common
{
	void exit()
	{
		cout << "No";
		::exit(0);
	}
}
namespace graph
{
	struct edge
	{
		int u, v, c, t;
	};
	vector<edge> e;
	vector<int> g[50000];
	void add_edge(int u, int v, int c, int t)
	{
		g[u].push_back(e.size());
		g[v].push_back(e.size());
		e.push_back({ u,v,c,t });
	}
	void init(int n, int m)
	{
		for (int i = 0; i < m; i++)
		{
			int u, v, c, t;
			cin >> u >> v >> c >> t;
			add_edge(u - 1, v - 1, c - 1, t);
		}
		for (int i = 0; i < n; i++)
			sort(g[i].begin(), g[i].end(), [](int a, int b) { return e[a].c < e[b].c; });
	}
}
namespace two_sat
{
	vector<int> g[300000];
}
namespace tarjan
{
	int dfn[300000], low[300000], index, com[300000], cnt;
	bool vis[300000], ins[300000];
	stack<int> s;
	vector<int> ch[300000];
	void _init()
	{
		memset(vis, 0x00, sizeof vis);
		index = cnt = 0;
	}
	void dfs(int u)
	{
		dfn[u] = low[u] = index++;
		vis[u] = ins[u] = true;
		s.push(u);
		for (int v : two_sat::g[u])
		{
			if (!vis[v])
			{
				dfs(v);
				low[u] = min(low[u], low[v]);
			}
			else if (ins[v]) low[u] = min(low[u], dfn[v]);
		}
		if (dfn[u] == low[u])
		{
			int v;
			ch[cnt].clear();
			do
			{
				v = s.top();
				s.pop();
				ins[v] = false;
				com[v] = cnt;
				ch[cnt].push_back(v);
			}
			while (u != v);
			cnt++;
		}
	}
	void solve(int n)
	{
		_init();
		for (int i = 0; i < n; i++)
			if (!vis[i])
				dfs(i);
	}
}
namespace two_sat
{
	vector<int> ng[300000];
	int in[300000], res[300000];
	bool vis[50000];
	void add_edge(int u, int v, bool fu, bool fv)
	{
		g[u * 2 + 1 - fu].push_back(v * 2 + 1 - fv);
	}
	void init(int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			bool flag = false;
			if (graph::g[i].empty()) continue;
			for (int j = 0; j < graph::g[i].size(); j++)
			{
				int x = graph::g[i][j];
				int xx = vis[x] ? x + 2 * m : x + m;
				add_edge(x, xx, true, true);
				add_edge(xx, x, false, false);
				if (j == 0) continue;
				int y = graph::g[i][j - 1];
				int yy = vis[y] ? y + 2 * m : y + m;
				vis[xx] = vis[yy] = true;
				if (graph::e[x].c == graph::e[y].c)
					if (flag) common::exit();
					else
					{
						flag = true;
						add_edge(x, y, false, true);
						add_edge(y, x, false, true);
					}
				add_edge(yy, xx, true, true);
				add_edge(xx, yy, false, false);
				add_edge(yy, x, true, false);
				add_edge(x, yy, true, false);
			}
			for (int j : graph::g[i])
				vis[j] = true;
		}
	}
	void _init(int n, int mid)
	{
		for (int i = 0; i < n; i++)
			ng[i].clear();
		memset(in, 0x00, sizeof in);
		memset(res, 0xff, sizeof res);
		for (int i = 0; i < graph::e.size(); i++)
			if (graph::e[i].t > mid)
				two_sat::add_edge(i, i, true, false);
	}
	void _clean(int n)
	{
		for (int i = 0; i < n; i++)
			while (!g[i].empty() && g[i].back() == (i ^ 1))
				two_sat::g[i].pop_back();
	}
	bool check(int n, int mid)
	{
		using tarjan::com;
		using tarjan::ch;
		_init(n, mid);
		tarjan::solve(n);
		for (int i = 0; i < n / 2; i++)
			if (com[i * 2] == com[i * 2 + 1])
			{
				_clean(n);
				return false;
			}
		for (int u = 0; u < n; u++)
			for (int v : g[u])
				if (com[u] != com[v])
				{
					ng[com[v]].push_back(com[u]);
					in[com[u]]++;
				}
		queue<int> q, nq;
		for (int i = 0; i < tarjan::cnt; i++)
			if (in[i] == 0)
			{
				q.push(i);
				for (int j : ch[i]) nq.push(j);
			}
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int v : ng[u])
				if (--in[v] == 0)
				{
					q.push(v);
					for (int i : ch[v]) nq.push(i);
				}
		}
		while (!nq.empty())
		{
			int x = nq.front();
			nq.pop();
			if (res[x] != -1) continue;
			for (int i : ch[com[x]]) res[i] = 1;
			x ^= 1;
			for (int i : ch[com[x]]) res[i] = 0;
			nq.push(com[x]);
			while (!q.empty())
			{
				int u = q.front();
				q.pop();
				for (int v : ng[u])
					if (res[ch[v][0]] == -1)
					{
						for (int i : ch[v])	res[i] = 0;
						q.push(v);
					}
			}
		}
		_clean(n);
		return true;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	graph::init(n, m);
	two_sat::init(n, m);
	int l = 0, r = 1e9, ans = -1;
	vector<int> v;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (two_sat::check(m * 6, mid))
		{
			ans = mid;
			r = mid - 1;
			v.clear();
			for (int i = 0; i < m; i++)
				if (two_sat::res[i * 2])
					v.push_back(i);
		}
		else l = mid + 1;
	}
	if (ans == -1) common::exit();
	cout << "Yes" << endl << ans << ' ' << v.size() << endl;
	for (int i : v) cout << i + 1 << ' ';
}
