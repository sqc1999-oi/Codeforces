#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int a[200000], m[200000], cnt[200000];
int gcd(int a,int b)
{
	return b == 0 ? a : gcd(b, a%b);
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		if (n%i == 0)
		{
			memset(m, 0x00, sizeof m);
			for (int j = 0; j < n; j++)
				m[j%i] = max(m[j%i], a[j]);
			int l = 0;
			while (l < n)
			{
				int r = l;
				while (r < n && a[r] == m[r%i]) r++;
				int x = r - l;
				cnt[i] += x*(x - 1) / 2;
				l = r + 1;
			}
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += cnt[gcd(i, n)];
	cout << ans;
}