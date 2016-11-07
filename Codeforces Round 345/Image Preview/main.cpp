#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, a, b, t;
	string s;
	cin >> n >> a >> b >> t >> s;
	auto solve = [=](int *sum)
	{
		int ans = 0;
		int k = n + 1;
		while (k > 1 && sum[0] + a*(n - k + 1) + sum[n - 1] - sum[k - 2] <= t) k--;
		if (k <= n) ans = n - k + 1;
		for (int i = 1; i < n; i++)
		{
			k = max(k, i + 1);
			while (k <= n&&sum[i] + a*(n - k + i * 2) + sum[n - 1] - sum[k - 1]>t) k++;
			if (k <= n) ans = max(ans, n - k + i + 1);
		}
		return ans;
	};
	auto sum = new int[n];
	auto calc = [=](char x) {return x == 'h' ? 1 : b + 1; };
	sum[0] = calc(s[0]);
	for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + calc(s[i]);
	int ans = solve(sum);
	reverse(s.begin() + 1, s.end());
	for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + calc(s[i]);
	ans = max(ans, solve(sum));
	cout << ans;
}
