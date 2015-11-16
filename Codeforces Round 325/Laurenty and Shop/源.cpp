#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int a[2][51], b[51];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < 2; i++)
		for (int j = 2; j <= n; j++)
		{
			int x;
			cin >> x;
			a[i][j] = a[i][j - 1] + x;
		}
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	int ans = INT_MAX;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j)
				ans = min(ans, a[0][i] + b[i] + a[1][n] - a[1][i] + a[0][j] + b[j] + a[1][n] - a[1][j]);
	cout << ans;
}
