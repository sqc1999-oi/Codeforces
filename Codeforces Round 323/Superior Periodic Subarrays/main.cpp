#include <iostream>
#include <algorithm>
#include <cstring>
#include <array>
using namespace std;
array<int, 200000> a, m, sum, g;
int gcd(int a, int b)
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
	for (int i = 1; i < n; i++)
		g[i] = gcd(i, n);
	long long ans = 0;
	for (int i = 1; i < n; i++)
		if (n%i == 0)
		{
			m.fill(0);
			for (int j = 0; j < n; j++)
				m[j%i] = max(m[j%i], a[j]);
			int l = 0;
			while (l < n && a[l] == m[l%i]) l++;
			sum.fill(0);
			if (l == n)
				for (int j = 1; j < n; j++)
					sum[j] += n;
			while (l < n)
			{
				while (l < n && a[l] != m[l%i]) l++; 
				int r = l;
				while (a[r%n] == m[r%i]) r++;
				for (int j = l; j < r; j++)
					sum[j - l + 1] += r - j;
				l = r;
			}
			for (int j = 1; j < n; j++)
				if (g[j] == i)
					ans += sum[j];
		}
	cout << ans;
}
