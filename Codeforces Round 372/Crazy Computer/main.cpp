#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, c;
	cin >> n >> c;
	int cnt = 0, last = -c;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		if (x - last <= c) cnt++;
		else cnt = 0;
		last = x;
	}
	cout << cnt << endl;
}