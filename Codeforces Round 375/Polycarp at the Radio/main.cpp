#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 2000;
int a[N], cnt[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i]--;
		if (a[i] < m) cnt[a[i]]++;
	}
	queue<int> q;
	for (int i = 0; i < m; i++)
		if (cnt[i] < n / m) q.push(i);
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		if (!q.empty() && (a[i] >= m || cnt[a[i]] > n / m))
		{
			c++;
			if (a[i] < m) cnt[a[i]]--;
			a[i] = q.front();
			if (++cnt[a[i]] == n / m) q.pop();
		}
	}
	cout << n / m << ' ' << c << endl;
	for (int i = 0; i < n; i++) cout << a[i] + 1 << ' ';
	cout << endl;
}
