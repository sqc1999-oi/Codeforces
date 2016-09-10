#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
struct edge
{
	int to, w;
};
const int N = 100000;
vector<edge> g[N];
bool flag[N];
int sz[N], dep[N], t[N + 2], depw[N];
void get_nodes(int u, int fa, vector<int> &v)
{
	v.push_back(u);
	for (edge e : g[u])
		if (e.to != fa && !flag[e.to])
			get_nodes(e.to, u, v);
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (edge e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			calc_size(e.to, u);
			sz[u] += sz[e.to];
		}
}
void calc_dep(int u, int fa)
{
	for (edge e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			dep[e.to] = dep[u] + 1;
			calc_dep(e.to, u);
		}
}
void calc_depw(int u, int fa)
{
	for (edge e : g[u])
		if (e.to != fa && !flag[e.to])
		{
			depw[e.to] = depw[u] + e.w;
			calc_depw(e.to, u);
		}
}
void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (edge e : g[u])
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
void update(int pos, int val)
{
	pos++;
	while (pos <= N + 1)
	{
		t[pos] += val;
		pos += pos&-pos;
	}
}
int query(int pos)
{
	pos++;
	int res = 0;
	while (pos > 0)
	{
		res += t[pos];
		pos -= pos&-pos;
	}
	return res;
}
long long calc_ans(int u, int L, int W)
{
	vector<int> v;
	get_nodes(u, -1, v);
	sort(v.begin(), v.end(), [](int a, int b) { return depw[a] < depw[b]; });
	for (int x : v) update(dep[x], 1);
	long long ans = 0;
	int j = v.size() - 1;
	for (int i = 0; i < v.size(); i++)
	{
		while (i <= j && depw[v[i]] + depw[v[j]] > W)
			update(dep[v[j--]], -1);
		if (j < i) break;
		update(dep[v[i]], -1);
		ans += query(L - dep[v[i]]);
	}
	return ans;
}
long long solve(int u, int L, int W)
{
	calc_size(u, -1);
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	flag[u] = true;
	dep[u] = depw[u] = 0;
	calc_dep(u, -1);
	calc_depw(u, -1);
	long long ans = calc_ans(u, L, W);
	for (edge e : g[u]) if (!flag[e.to]) ans -= calc_ans(e.to, L, W);
	for (edge e : g[u]) if (!flag[e.to]) ans += solve(e.to, L, W);
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, L, W;
	cin >> n >> L >> W;
	for (int i = 1; i < n; i++)
	{
		int p, w;
		cin >> p >> w;
		p--;
		g[i].push_back(edge{ p,w });
		g[p].push_back(edge{ i,w });
	}
	cout << solve(0, L, W);
}
