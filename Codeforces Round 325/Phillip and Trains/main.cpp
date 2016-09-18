#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
char map[3][101];
bool cache[3][100];
bool f(int i, int j, int n)
{
	if (i < 0 || i >= 3) return false;
	if (j > n - 1) return true;
	if (map[i][j] != 's' && map[i][j - 2] != '.') return false;
	if (map[i][j] != '.' && map[i][j] != 's') return false;
	if (j == n - 1) return true;
	bool &ret = cache[i][j];
	if (int(ret) != 255) return ret;
	ret = false;
	if (map[i][j + 1] == '.')
	{
		ret |= f(i, j + 3, n);
		ret |= f(i - 1, j + 3, n);
		ret |= f(i + 1, j + 3, n);
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int n, k;
		cin >> n >> k;
		cin.get();
		for (int i = 0; i < 3; i++)
			cin >> map[i];
		memset(cache, 0xff, sizeof cache);
		for (int i = 0; i < 3; i++)
			if (map[i][0] == 's')
				cout << (f(i, 0, n) ? "YES" : "NO") << endl;
	}
}
