#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int a[500001];
int tmp[3];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	vector<pair<int, int> > v;
	int cnt = 0, last, m = 0;
	for (int i = 2; i < n; i++)
	{
		if (a[i] != a[i - 1] && a[i] != a[i + 1])
		{
			if (cnt++ == 0) last = i;
		}
		else if (cnt > 0)
		{
			v.push_back(make_pair(last, i));
			m = max(m, cnt);
			cnt = 0;
		}
	}
	m = max(m, cnt);
	if (cnt > 0) v.push_back(make_pair(last, n));
	cout << (m + 1) / 2 << endl;
	for (auto p : v)
	{
		for (int i = p.first; i < (p.first + p.second) / 2; i++)
			a[i] = a[p.first - 1];
		for (int i = (p.first + p.second + 1) / 2; i < p.second; i++)
			a[i] = a[p.second];
		if ((p.second - p.first) % 2 == 1)
		{
			int x = (p.first + p.second) / 2;
			for (int i = 0; i < 3; i++)
				tmp[i] = a[x - 1 + i];
			sort(tmp, tmp + 3);
			a[x] = tmp[1];
		}
	}
	for (int i = 1; i <= n; i++)
		cout << a[i] << ' ';
}
