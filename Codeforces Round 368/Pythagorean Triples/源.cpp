#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	if (n <= 2) cout << -1 << endl;
	else
	{
		int x = 1;
		while (!(n & 1) && n != 4)
		{
			n /= 2;
			x *= 2;
		}
		if (n == 4) cout << (long long)x * 3 << ' ' << (long long)x * 5 << endl;
		else cout << ((long long)n*n - 1) / 2 * x << ' ' << ((long long)n*n + 1) / 2 * x << endl;
	}
}