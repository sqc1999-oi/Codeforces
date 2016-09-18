#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int mp = INT_MAX, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int a, p;
		cin >> a >> p;
		mp = min(mp, p);
		ans += mp*a;
	}
	cout << ans;
}
