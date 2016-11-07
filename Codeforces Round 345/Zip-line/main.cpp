#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 4e5, P = 1e9 + 7;
int t[N * 2 + 1], c[N * 2 + 1], a[N], b[N * 2], l[N], r[N], p[N];
pair<int, int> lc[N], rc[N];
struct q { int x, id; };
vector<q> v[N];
int lowbit(int x) { return x&-x; }
void update(int v, int cnt, int k, int n)
{
	for (; k <= n; k += lowbit(k))
	{
		if (v > t[k])
		{
			t[k] = v;
			c[k] = cnt;
		}
		else if (v == t[k]) c[k] = (c[k] + cnt) % P;
	}
}
pair<int, int> query(int k)
{
	int ans = 0, cnt = 1;
	for (; k > 0; k -= lowbit(k))
	{
		if (t[k] > ans)
		{
			ans = t[k];
			cnt = c[k];
		}
		else if (t[k] == ans) cnt = (cnt + c[k]) % P;
	}
	return { ans,cnt };
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		v[x - 1].push_back({ y,i });
		p[i] = x - 1;
		b[i + n] = y;
	}
	sort(b, b + n + m);
	int *e = unique(b, b + n + m);
	for (int i = 0; i < n; i++)
	{
		a[i] = lower_bound(b, e, a[i]) - b + 1;
		for (auto &x : v[i]) x.x = lower_bound(b, e, x.x) - b + 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (auto x : v[i]) l[x.id] = query(x.x - 1).first;
		auto res = lc[i] = query(a[i] - 1);
		update(res.first + 1, res.second, a[i], n + m);
	}
	memset(t, 0x00, sizeof t);
	memset(c, 0x00, sizeof c);
	for (int i = n - 1; i >= 0; i--)
	{
		for (auto x : v[i]) r[x.id] = query(n + m - x.x).first;
		auto res = rc[i] = query(n + m - a[i]);
		update(res.first + 1, res.second, n + m - a[i] + 1, n + m);
	}
	auto ans = query(n + m);
	for (int i = 0; i < m; i++)
	{
		if (l[i] + 1 + r[i] >= ans.first) cout << l[i] + 1 + r[i];
		else if (lc[p[i]].first + rc[p[i]].first + 1 < ans.first) cout << ans.first;
		else if (((long long)lc[p[i]].second*rc[p[i]].second) % P == ans.second) cout << ans.first - 1;
		else cout << ans.first;
		cout << endl;
	}
}
