#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
int p[2001], s[2001];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		s[x] = i;
	}
	int ans = 0, cnt = 0;
	stringstream ss;
	for (int i = n; i > 0; i--)
	{
		int j = 0;
		while (s[p[j]] != i) j++;
		for (int k = j + 1; k <= i; k++)
		{
			if (s[p[k]] <= j)
			{
				ss << j << ' ' << k << endl;
				swap(p[j], p[k]);
				ans += k - j;
				j = k;
				cnt++;
			}
		}
	}
	cout << ans << endl << cnt << endl << ss.str();
}
