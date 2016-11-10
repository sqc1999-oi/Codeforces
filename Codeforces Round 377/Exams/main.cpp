#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5;
int d[N], a[N], p[N], id[N], cnt[N];
bool check(int mid, int n, int m)
{
	memset(p, 0xff, sizeof p);
	for (int i = 0; i < mid; i++)
		if (d[i] >= 0) p[d[i]] = i;
	for (int i = 0; i < m; i++) id[i] = i;
	sort(id, id + m, [](int x, int y) { return p[x] < p[y]; });
	if (p[id[0]] == -1) return false;
	memset(cnt, 0x00, sizeof cnt);
	for (int i = 0, j = 0; i < mid; i++)
	{
		if (d[i] >= 0 && p[d[i]] == i) { if (cnt[d[i]] < a[d[i]]) return false; }
		else if (j < m)
		{
			cnt[id[j]]++;
			if (cnt[id[j]] == a[id[j]]) j++;
		}
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> d[i];
		d[i]--;
	}
	for (int i = 0; i < m; i++) cin >> a[i];
	int l = 1, r = n, ans = -1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (check(mid, n, m))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans << endl;
}
