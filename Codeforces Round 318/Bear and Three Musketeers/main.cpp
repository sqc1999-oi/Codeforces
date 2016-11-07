#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
bool G[4001][4001];
int deg[4001];
struct
{
	int a, b;
} e[4001];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> e[i].a >> e[i].b;
		G[e[i].a][e[i].b] = G[e[i].b][e[i].a] = true;
		deg[e[i].a]++;
		deg[e[i].b]++;
	}
	int ans = INT_MAX;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (G[e[i].a][j] && G[e[i].b][j])
				ans = min(ans, deg[e[i].a] + deg[e[i].b] + deg[j] - 6);
	if (ans == INT_MAX)
		cout << -1;
	else
		cout << ans;
}
