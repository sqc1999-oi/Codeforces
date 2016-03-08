#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int map[1000][1000];
int f(int a, int b)
{
	int &x = map[a][b];
	if (x != -1) return x;
	if (a == 0 || b == 0) x = 0;
	else if (a == 1 && b > 1) x = f(a + 1, b - 2) + 1;
	else if (a > 1 && b == 1) x = f(a - 2, b + 1) + 1;
	else if (a == 1 || b == 1) return 0;
	else x = max(f(a + 1, b - 2), f(a - 2, b + 1)) + 1;
	return x;
}
int main()
{
	ios::sync_with_stdio(false);
	memset(map, 0xff, sizeof map);
	int a, b;
	cin >> a >> b;
	cout << f(a, b);
}