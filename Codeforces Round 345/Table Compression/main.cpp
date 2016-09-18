#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>
#include <cstring>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	auto a = new int *[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
		for (int j = 0; j < m; j++) cin >> a[i][j];
	}
	int *f = new int[n*m];
	for (int i = 0; i < n*m; i++) f[i] = i;
	function<int(int)> getf = [=, &getf](int x) { return x == f[x] ? x : f[x] = getf(f[x]); };
	auto t = new int[max(n, m)];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) t[j] = j;
		sort(t, t + m, [=](int x, int y) { return a[i][x] < a[i][y]; });
		for (int j = 1; j < m; j++)
			if (a[i][t[j]] == a[i][t[j - 1]])
				f[getf(i*m + t[j])] = getf(i*m + t[j - 1]);
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) t[j] = j;
		sort(t, t + n, [=](int x, int y) { return a[x][i] < a[y][i]; });
		for (int j = 1; j < n; j++)
			if (a[t[j]][i] == a[t[j - 1]][i])
				f[getf(t[j] * m + i)] = getf(t[j - 1] * m + i);
	}
	auto g = new vector<int>[n*m];
	auto in = new int[n*m];
	memset(in, 0x00, sizeof(int)*n*m);
	auto add_edge = [=](int x, int y)
	{
		if (x == y) return;
		g[x].push_back(y);
		in[y]++;
	};
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) t[j] = j;
		sort(t, t + m, [=](int x, int y) { return a[i][x] < a[i][y]; });
		for (int j = 1; j < m; j++) add_edge(getf(i*m + t[j - 1]), getf(i*m + t[j]));
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) t[j] = j;
		sort(t, t + n, [=](int x, int y) { return a[x][i] < a[y][i]; });
		for (int j = 1; j < n; j++) add_edge(getf(t[j - 1] * m + i), getf(t[j] * m + i));
	}
	auto ans = new int[n*m];
	memset(ans, 0x00, sizeof(int)*n*m);
	queue<int> q;
	for (int i = 0; i < n*m; i++)
		if (in[i] == 0)
		{
			q.push(i);
			ans[i] = 1;
		}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v : g[u])
		{
			ans[v] = max(ans[v], ans[u] + 1);
			if (--in[v] == 0) q.push(v);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << ans[getf(i*m + j)] << ' ';
		cout << endl;
	}
}
