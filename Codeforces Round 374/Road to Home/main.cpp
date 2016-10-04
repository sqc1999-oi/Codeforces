#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5;
int l[N], r[N];
typedef pair<int, int> pii;
pair<int, int> f[N];
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
		f[i] = max(f[i], { r[i] - l[i] / p,r[i] - (r[i] - l[i]) % p }, cmp);
	}
}
