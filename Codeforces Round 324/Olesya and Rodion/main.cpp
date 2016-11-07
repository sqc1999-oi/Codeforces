#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, t;
	cin >> n >> t;
	if (t == 10)
	{
		if (n == 1) return cout << -1, 0;
		t = 1;
	}
	cout << t;
	for (int i = 1; i < n; i++) cout << 0;
}
