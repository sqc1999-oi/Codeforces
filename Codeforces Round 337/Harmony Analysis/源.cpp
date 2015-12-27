#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 512;
char a[N][N];
int main()
{
	ios::sync_with_stdio(false);
	int k;
	cin >> k;
	if (k == 0) cout << '+';
	else if (k == 1) cout << "++++\n++**";
	else
	{
		int n = round(pow(2, k));
		for (int i = 0; i < n / 2; i++)
		{
			cout << '+';
			a[0][i] = '+';
		}
		for (int i = n / 2; i < n; i++)
		{
			cout << '*';
			a[0][i] = '*';
		}
		cout << endl;
		for (int i = 0; i < n / 4; i++)
		{
			cout << '+';
			a[1][i] = '+';
		}
		for (int i = n / 4; i < n / 2; i++)
		{
			cout << '*';
			a[1][i] = '*';
		}
		for (int i = n / 2; i < 3 * n / 4; i++)
		{
			cout << '+';
			a[1][i] = '+';
		}
		for (int i = 3 * n / 4; i < n; i++)
		{
			cout << '*';
			a[1][i] = '*';
		}
		for (int i = 2; i < n; i++)
		{

		}
	}
}