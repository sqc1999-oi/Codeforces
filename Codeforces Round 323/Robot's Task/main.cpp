#include <iostream>
#include <algorithm>
using namespace std;
int a[1000];
bool vis[1000];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int cnt = 0;
	for (int i = 0;; i++)
	{
		bool flag = false;
		auto solve = [&](int j)
		{
			if (!vis[j] && cnt >= a[j])
			{
				vis[j] = true;
				cnt++;
				flag = true;
			}
		};
		if (i % 2 == 0)
			for (int j = 0; j < n; j++)
				solve(j);
		else
			for (int j = n - 1; j >= 0; j--)
				solve(j);
		if (!flag)
		{
			cout << i - 1;
			return 0;
		}
	}
}
