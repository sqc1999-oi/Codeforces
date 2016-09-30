#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int x, y;
	for (int i = 0; i < n - 1; i++) cin >> x;
	cin >> y;
	if (y == 0) cout << "UP";
	else if (y == 15) cout << "DOWN";
	else if (n == 1) cout << -1;
	else if (y > x) cout << "UP";
	else cout << "DOWN";
	cout << endl;
}
