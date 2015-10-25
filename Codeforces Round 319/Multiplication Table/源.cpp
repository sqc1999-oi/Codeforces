#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, x;
	cin >> n >> x;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (x % i == 0 && x / i <= n) cnt++;
	cout << cnt;
}
