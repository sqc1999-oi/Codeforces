#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int a[N], f[N];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	long long sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	long long max = sum;
	for (int i = n - 2; i >= 0; i--)
	{
		f[i] = max;
		sum -= a[i + 1];
		max = ::max(max, sum - f[i]);
	}
	cout << f[0] << endl;
}
