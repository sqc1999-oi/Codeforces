#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int a, b, c, ans = INT_MAX;
	cin >> a >> b >> c;
	for (int i = 1; i <= 100; i++)
		ans = min(ans, abs(i - a) + abs(i - b) + abs(i - c));
	cout << ans << endl;
}
