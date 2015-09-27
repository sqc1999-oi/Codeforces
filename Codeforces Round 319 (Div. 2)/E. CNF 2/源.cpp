#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef pair<bool, bool> pbb;
bool vis[200001], ans[200001];
vector<pbb> clause[200001];
int var[200001][3];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		int k;
		cin >> k;
		for (int j = 1; j <= k; j++)
		{
			int v;
			cin >> v;
			clause[i].push_back(pbb{ v > 0,abs(v) });
			var[abs(v)][v > 0] = i;
			var[abs(v)][2]++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= m; i++)
		if (var[i].size == 1)
		{
			q.push(var[i][0]);
			vis[var[i][0]] = true;
			ans[i] = true;
		}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int x : clause[u])
		{
			int xx = abs(x);
			
		}
	}
}