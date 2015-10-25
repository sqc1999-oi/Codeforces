#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int map[26];
int main()
{
	ios::sync_with_stdio(false);
	for (int i = 0; i < 26; i++)
		map[i] = i;
	int n, m;
	string s;
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++)
	{
		char x, y;
		cin >> x >> y;
		int px, py;
		for (int i = 0; i < 26; i++)
		{
			if (map[i] == x - 'a') px = i;
			if (map[i] == y - 'a') py = i;
		}
		swap(map[px], map[py]);
	}
	for (int i = 0; i < n; i++)
		cout << char(map[s[i] - 'a'] + 'a');
}
