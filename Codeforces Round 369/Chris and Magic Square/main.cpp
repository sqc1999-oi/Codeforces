#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500;
long long a[N][N];
bool check(int n)
{
	long long sum = 0;
	for (int i = 0; i < n; i++) sum += a[0][i];
	long long cur;
	for (int i = 1; i < n; i++)
	{
		cur = 0;
		for (int j = 0; j < n; j++) cur += a[i][j];
		if (cur != sum) return false;
	}
	for (int i = 0; i < n; i++)
	{
		cur = 0;
		for (int j = 0; j < n; j++) cur += a[j][i];
		if (cur != sum) return false;
	}
	cur = 0;
	for (int i = 0; i < n; i++) cur += a[i][i];
	if (cur != sum) return false;
	cur = 0;
	for (int i = 0; i < n; i++) cur += a[i][n - i - 1];
	if (cur != sum) return false;
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	if (n == 1) cout << 1 << endl;
	else
	{
		int x = 0, y = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				cin >> a[i][j];
				if (a[i][j] == 0)
				{
					x = i;
					y = j;
				}
			}
		int k = x != 0 ? 0 : 1;
		long long v = 0;
		for (int i = 0; i < n; i++) v = v + a[k][i] - a[x][i];
		a[x][y] = v;
		cout << (v > 0 && check(n) ? v : -1) << endl;
	}
}
