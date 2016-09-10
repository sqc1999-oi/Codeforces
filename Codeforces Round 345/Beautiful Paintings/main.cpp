#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int *a = new int[1000];
	memset(a, 0x00, sizeof(int) * 1000);
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		a[x - 1]++;
	}
	bool flag;
	int ans = 0;
	do
	{
		flag = false;
		for (int i = 0; i < 1000; i++)
		{
			if (a[i] > 0)
			{
				if (!flag) flag = true;
				else ans++;
				a[i]--;
			}
		}
	} while (flag);
	cout << ans;
}