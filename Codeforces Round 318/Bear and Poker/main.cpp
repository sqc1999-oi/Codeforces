#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, g = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		while (x % 2 == 0)
			x /= 2;
		while (x % 3 == 0)
			x /= 3;
		if (g == 0)
			g = x;
		else
			if (g != x)
			{
				cout << "No";
				return 0;
			}
	}
	cout << "Yes";
}
