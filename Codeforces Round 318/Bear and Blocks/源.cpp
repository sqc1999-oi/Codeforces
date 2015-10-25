#include <iostream>
#include <algorithm>
using namespace std;
int h[100001], res[100001];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> h[i];
	int x = 0;
	for (int i = 1; i <= n; i++)
	{
		x = min(x, h[i] - i);
		res[i] = x + i;
	}
	x = n + 1;
	for (int i = n; i > 0; i--)
	{
		x = min(x, h[i] + i);
		res[i] = min(res[i], x - i);
	}
	cout << *max_element(res + 1, res + 1 + n);
}
