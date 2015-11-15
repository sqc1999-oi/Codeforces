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
		int from, to, c, t;
	};
	vector<edge> e;
	vector<int> g[50000];
	void add_edge(int u, int v, int c, int t)
	{
		g[u].push_back(e.size());
		e.push_back({ u,v,c,t });
		g[v].push_back(e.size());
		e.push_back({ v,u,c,t });
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
namespace tarjan
{
	int dfn[200000], low[200000], index, com[200000], cnt;
	bool vis[200000], ins[200000];
	stack<int> s;
	vector<int> ch[200000];
	void _init()
	{
		memset(vis, 0x00, sizeof vis);
		index = cnt = 0;
	}
	void dfs(int u, vector<int> *g)
	{
		dfn[u] = low[u] = ++index;
		vis[u] = ins[u] = true;
		s.push(u);
		for (int v : g[u])
		{
			if (!vis[v])
			{
				dfs(v, g);
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
	void solve(int n, vector<int> *g)
	{
		_init();
		for (int i = 0; i < n; i++)
			if (!vis[i])
				dfs(i, g);
	}
}
namespace two_sat
{
	vector<int> g[200000], ng[200000], op[200000];
	int in[200000], res[200000];
	void add_edge(int u, int v, bool fu, bool fv)
	{
		g[u * 2 + 1 - fu].push_back(v * 2 + 1 - fv);
	}
	void init(int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			bool flag = false;
			add_edge(graph::g[i][0], graph::g[i][0] + m, true, true);
			add_edge(graph::g[i][0] + m, graph::g[i][0], false, false);
			for (int j = 1; j < graph::g[i].size(); j++)
			{
				int x = graph::g[i][j], y = graph::g[i][j - 1];
				if (graph::e[x].c == graph::e[y].c)
					if (flag) common::exit();
					else
					{
						flag = true;
						add_edge(x, y, false, true);
						add_edge(y, x, false, true);
					}
				add_edge(x, x + m, true, true);
				add_edge(x + m, x, false, false);
				add_edge(x + m - 1, x + m, true, true);
				add_edge(x + m, x + m - 1, false, false);
				add_edge(x + m - 1, x, true, false);
				add_edge(x, x + m - 1, true, false);
			}
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
			while (!g[i].empty() && g[i].back() == i)
				two_sat::g[i].pop_back();
	}
	bool check(int n, int mid)
	{
		using namespace tarjan;
		_init(n, mid);
		solve(n, g);
		for (int i = 0; i < n / 2; i++)
			if (com[i * 2] == com[i * 2 + 1])
			{
				_clean(n);
				return false;
			}
		for (int u = 0; u < n; u++)
			for (int v : g[u])
			{
				ng[com[v]].push_back(com[u]);
				in[com[u]]++;
			}
		queue<int> q, nq;
		for (int i = 0; i < cnt; i++)
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
			int x = q.front();
			q.pop();
			if (res[x] != -1) continue;
			for (int i : ch[com[x]]) res[i] = 1;
			x ^= 1;
			for (int i : ch[com[x]]) res[i] = 0;
			q.push(com[x]);
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
	int l = 1, r = 1e9, ans = -1;
	vector<int> v;
	while (l < r)
	{
		int mid = (l + r) / 2;
		if (two_sat::check(m * 4, mid))
		{
			r = ans = mid - 1;
			v.clear();
			for (int i = 0; i < m; i++)
				if (two_sat::res[i * 2])
					v.push_back(i);
		}
		else l = mid + 1;
	}
	if (ans == -1) common::exit();
	cout << ans << ' ' << v.size() << endl;
	for (int i : v) cout << i << ' ';
}