#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct edge
{
	int to, pow;
	edge(int to, int pow) :to(to), pow(pow) {}
};
const int N = 1e5;
vector<edge> g[N];
bool flag[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back(edge(v, w));
		g[v].push_back(edge(u, w));
	}
	for (int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		flag[x - 1] = true;
	}
	int ans = INT_MAX;
	for (int i = 0; i < n; i++)
		if (!flag[i])
			for (int j = 0; j < g[i].size(); j++)
				if (flag[g[i][j].to]) ans = min(ans, g[i][j].pow);
	cout << (ans == INT_MAX ? -1 : ans) << endl;
}