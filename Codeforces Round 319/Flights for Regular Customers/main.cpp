#include <iostream>
#include <algorithm>
#include <bitset>
#include <climits>
using namespace std;
const int N = 150;
template<int n, int m> struct matrix
{
	bitset<m> a[n];
	bitset<m> &operator [](int x) { return a[x]; }
	template<int x> matrix<n, x> operator *(matrix<m, x> &b)
	{
		static matrix<n, x> c;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < x; j++)
				c[i][j] = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < x; j++)
				if (a[i][j]) c[i] |= b[j];
		return c;
	}
	matrix<n, m> multi(int k)
	{
		static matrix<n, m> ret, t;
		t = *this;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ret[i][j] = i == j;
		while (k > 0)
		{
			if (k & 1) ret = ret*t;
			t = t*t;
			k >>= 1;
		}
		return ret;
	}
};
struct flight { int a, b, d; } f[N];
matrix<N, N> adj, tmp;
matrix<1, N> cur;
int dis[N][N];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> f[i].a >> f[i].b >> f[i].d;
	sort(f, f + m, [](const flight &a, const flight &b) { return a.d < b.d; });
	if (f[0].d > 0)
	{
		cout << "Impossible" << endl;
		return 0;
	}
	cur[0] = 1;
	int ans = INT_MAX;
	for (int i = 0; i < m; i++)
	{
		adj[f[i].a - 1][f[i].b - 1] = 1;
		if (i < m - 1 && f[i].d == f[i + 1].d) continue;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (i == j) dis[i][j] = 0;
				else if (adj[i][j]) dis[i][j] = 1;
				else dis[i][j] = INT_MAX;
			}
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (dis[i][k] < INT_MAX&&dis[k][j] < INT_MAX)
						dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		for (int j = 0; j < n; j++)
			if (cur[0][j] && dis[j][n - 1] < INT_MAX)
				ans = min(ans, f[i].d + dis[j][n - 1]);
		if (i < m - 1)
		{
			tmp = adj.multi(f[i + 1].d - f[i].d);
			cur = cur*tmp;
		}
	}
	if (ans < INT_MAX) cout << ans << endl;
	else cout << "Impossible" << endl;
}
