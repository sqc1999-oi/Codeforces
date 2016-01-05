#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
typedef pair<int, int> pii;
const int N = 1e5;

struct edge
{
	int to, w;
};

struct info
{
	int d, c, t;

	bool operator <(info &other) const
	{
		return d < other.d;
	}
};

vector<edge> g[N];
vector<pii> p[N];
vector<info> c[N];
int sz[N], dep[N];
bool flag[N];

void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (auto e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			calc_size(e.to, u);
			sz[u] += sz[e.to];
		}
}

void calc_dep(int u, int fa)
{
	for (auto e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			dep[e.to] = dep[u] + e.w;
			calc_dep(e.to, u);
		}
}

void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (auto e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			max = ::max(max, sz[e.to]);
			get_focus(e.to, u, n, ans, min);
		}
	if (max < min)
	{
		min = max;
		ans = u;
	}
}

void get_nodes(int u, int fa, vector<int> &v)
{
	v.push_back(u);
	for (auto e : g[u])
		if (e.to != fa && !flag[e.to])
			get_nodes(e.to, u, v);
}

void solve(int u)
{
	calc_size(u, -1);
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	flag[u] = true;
	dep[u] = 0;
	calc_dep(u, -1);
	vector<int> vi;
	get_nodes(u, -1, vi);
	for (auto v : vi) p[v].push_back(pii(u, dep[v]));
	for (auto e : g[u]) if (!flag[e.to]) solve(e.to);
}

void update(int u, int d, int val, int t)
{
	for (auto x : p[u])
	{
		int v = x.first, dis = d - x.second;
		while (c[v].back().d <= dis) c[v].pop_back();
		c[v].push_back(info{ dis,val,t });
	}
}

info binary_search(vector<info> &v, int val)
{
	int l = 0, r = v.size() - 1, x = 0;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (v[mid].d >= val)
		{
			x = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return v[x];
}

int query(int u)
{
	info ret{ 0,0,-2 };
	for (auto x : p[u])
	{
		int v = x.first, dis = x.second;
		auto cu = binary_search(c[v], dis);
		if (cu.t > ret.t) ret = cu;
	}
	return ret.c;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		a--, b--;
		g[a].push_back(edge{ b,w });
		g[b].push_back(edge{ a,w });
	}
	solve(0);
	for (int i = 0; i < n; i++) c[i].push_back(info{ INT_MAX ,0,-1 });
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int v, d, c;
			scanf("%d%d%d", &v, &d, &c);
			update(v - 1, d, c, i);
		}
		else
		{
			int v;
			scanf("%d", &v);
			printf("%d\n", query(v - 1));
		}
	}
}
