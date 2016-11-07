#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5;
int l[N], r[N];
typedef pair<int, int> pii;
pair<int, int> f[N], g[N];
bool cmp(const pii &a, const pii &b) { return a.first<b.first || a.first == b.first&&a.second>b.second; }
int main()
{
	ios::sync_with_stdio(false);
	int n, p, t;
	cin >> n >> n >> p >> t;
	for (int i = 0; i < n; i++)
		cin >> l[i] >> r[i];
	for (int i = 0; i < n; i++)
	{
		if (i > 0) g[i] = max(g[i], g[i - 1], cmp);
		f[i] = max(f[i], { g[i].first + (r[i] - l[i]) / p,r[i] - (r[i] - l[i]) % p }, cmp);
		int x = f[i].second + t, j = lower_bound(r, r + n, x) - r;
		if (j < n)
		{
			if (l[j] >= x) g[j] = max(g[j], { f[i].first,x }, cmp);
			else
			{
				f[j] = max(f[j], { f[i].first + (r[j] - x) / p,r[j] - (r[j] - x) % p }, cmp);
				if (j < n - 1) g[j + 1] = max(g[j + 1], { f[i].first,x }, cmp);
			}
		}
	}
	cout << max_element(f, f + n)->first << endl;
}
