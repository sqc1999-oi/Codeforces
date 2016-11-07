#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6;
int a[N], b[N], f[N + 1];
int main()
{
	ios::sync_with_stdio(false);
	int n, c, cnt = 0;
	cin >> n >> c;
	for (int i = 0, x = 0; i < n; i++)
	{
		int y;
		cin >> y;
		for (int j = 0; j < y; j++)
		{
			cin >> b[j];
			b[j]--;
		}
		for (int j = 0; j < y; j++)
		{
			if (j == x) break;
			if (b[j] != a[j])
			{
				cnt++;
				if (b[j] < a[j])
				{
					f[c - a[j]]++;
					f[c - b[j]]--;
				}
				else
				{
					f[c - a[j]]++;
					f[c]--;
					f[0]++;
					f[c - b[j]]--;
				}
				break;
			}
			if (j == y - 1 && y < x)
			{
				cout << -1 << endl;
				return 0;
			}
		}
		memcpy(a, b, sizeof(int)*y);
		x = y;
	}
	int t = 0, ans = -1;
	for (int i = 0; i < c; i++)
	{
		t += f[i];
		if (t == cnt&&ans == -1)
		{
			ans = i;
			break;
		}
	}
	cout << ans << endl;
}
