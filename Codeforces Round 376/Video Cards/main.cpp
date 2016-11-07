#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int a[N], b[N + 1];
long long f[N + 1];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[a[i]]++;
	}
	for (int i = 2; i <= N; i++) b[i] += b[i - 1];
	sort(a, a + n);
	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j += i)
			f[i] += (long long)(b[min(j + i - 1, N)] - b[j - 1])*j;
	long long ans = 0;
	for (int i = 0; i < n; i++) ans = max(ans, f[a[i]]);
	cout << ans << endl;
}
