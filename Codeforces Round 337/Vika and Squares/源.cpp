#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int a[N * 2];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i + n] = a[i];
	}
	int min = *min_element(a, a + n), ans = 0, cnt = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		if (a[i] == min) cnt = 0;
		else cnt++;
		if (cnt > ans) ans = cnt;
	}
	cout << (long long)min*n + ans;
}
