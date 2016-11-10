#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
const int N = 4e5;
struct edge
{
	int to, id;
} e[N * 2];
vector<edge> g[N];
pair<int, int> res[N];
int ans = 0, pos = 0;
void tarjan(int u, int fa, int fe)
{
	static int ts[N], low[N], time = 1;
	static bool ins[N];
	static stack<int> s;
	ts[u] = low[u] = time++;
	s.push(u);
	ins[u] = true;
	for (const edge &e : g[u])
	{
		int v = e.to, x = e.id;
		if (ts[v] == 0)
		{
			tarjan(v, u, x);
			low[u] = min(low[u], low[v]);
		}
		else if (ins[v] && x != fe) low[u] = min(low[u], ts[v]);
	}
	if (low[u] >= ts[u])
	{
		int cnt = 0, v;
		do
		{
			v = s.top();
			ins[v] = false;
			s.pop();
			cnt++;
		} while (v != u);
		if (cnt > ans)
		{
			ans = cnt;
			pos = u;
		}
	}
}
void dfs(int u, int fa)
{
	static int st[N];
	st[u] = 1;
	for (const edge &e : g[u])
		if (e.id != fa)
		{
			if (st[e.to] != 2) res[e.id] = { e.to,u };
			if (st[e.to] == 0) dfs(e.to, e.id);
		}
	st[u] = 2;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back({ v,i });
		g[v].push_back({ u,i });
	}
	tarjan(0, -1, -1);
	cout << ans << endl;
	dfs(pos, -1);
	for (int i = 0; i < m; i++)
		cout << res[i].first + 1 << ' ' << res[i].second + 1 << endl;
}
