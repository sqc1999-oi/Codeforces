#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		int x = max(0, k - a[i - 1] - a[i]);
		ans += x;
		a[i] += x;
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++) cout << a[i] << ' ';
}
