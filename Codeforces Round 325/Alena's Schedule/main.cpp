#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int ans = 0, cnt = 0;
	bool l;
	for (int i = 0; i < n; i++)
	{
		bool a;
		cin >> a;
		if (a)
		{
			if (cnt == 1 && ans > 0) ans++;
			ans++;
			cnt = 0;
		}
		else cnt++;
		l = a;
	}
	cout << ans;
}
