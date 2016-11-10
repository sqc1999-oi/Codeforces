#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long long a[3];
	for (int i = 0; i < 3; i++) cin >> a[i];
	long long m = max({ a[0],a[1],a[2] });
	long long ans = 0;
	for (int i = 0; i < 3; i++)
		if (a[i] < m) ans += m - a[i] - 1;
	cout << ans << endl;
}
