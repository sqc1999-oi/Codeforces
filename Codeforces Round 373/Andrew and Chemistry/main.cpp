#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
const int N = 1e5, K = 4;
vector<int> g[N];
set<int> s;
int a[N];
int get_index(const vector<int> x)
{
	static map<vector<int>, int> m;
	static int cnt;
	if (m.find(x) == m.end()) m[x] = cnt++;
	return m[x];
}
void dfs_pre(int u, int fa)
{
	vector<int> x;
	for (int v : g[u])
		if (v != fa)
		{
			dfs_pre(v, u);
			x.push_back(a[v]);
		}
	sort(x.begin(), x.end());
	a[u] = get_index(x);
}
void dfs(int u, int fa)
{
	vector<int> x;
	if (g[u].size() < K)
	{
		for (int v : g[u]) x.push_back(a[v]);
		sort(x.begin(), x.end());
		s.insert(get_index(x));
	}
	sort(g[u].begin(), g[u].end(), [](int x, int y) { return a[x] < a[y]; });
	x.clear();
	for (int i = 1; i < g[u].size(); i++) x.push_back(a[g[u][i]]);
	int t = a[u];
	for (int i = 0; i < g[u].size(); i++)
	{
		if (g[u][i] != fa)
		{
			a[u] = get_index(x);
			dfs(g[u][i], u);
		}
		if (i < g[u].size() - 1) x[i] = a[g[u][i]];
	}
	a[u] = t;
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
	dfs_pre(0, -1);
	dfs(0, -1);
	cout << s.size() << endl;
}
