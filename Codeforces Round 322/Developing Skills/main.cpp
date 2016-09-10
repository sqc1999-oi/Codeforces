#include <iostream>
#include <algorithm>
using namespace std;
int a[100001];
bool cmp(int a, int b) { return a % 10 > b % 10; }
int main()
{
	ios::sync_with_stdio(false);
	int n, k, sum = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i] / 10;
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < 100 && k >= 10 - a[i] % 10)
		{
			k -= 10 - a[i] % 10;
			a[i] = a[i] / 10 * 10 + 10;
			sum++;
		}
		else break;
	}
	for (int i = 1; i <= n; i++)
	{
		if (k >= 10)
		{
			int x = min(100 - a[i], k / 10 * 10);
			k -= x;
			sum += x / 10;
		}
		else break;
	}
	cout << sum;
}
