#include <iostream>
#include <algorithm>
using namespace std;
const int MOD = 1e9 + 7;
long long c[4001][4001], b[4000][4000];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
	}
	b[0][0] = b[1][1] = 1;
	for (int i = 2; i < n; i++)
	{
		b[i][1] = b[i - 1][i - 1];
		for (int j = 2; j <= i; j++)
			b[i][j] = (b[i][j - 1] + b[i - 1][j - 1]) % MOD;
	}
	long long ans = 0;
	for (int i = 0; i < n; i++)
		ans = (ans + c[n][i] * b[i][i]) % MOD;
	cout << ans;
}
