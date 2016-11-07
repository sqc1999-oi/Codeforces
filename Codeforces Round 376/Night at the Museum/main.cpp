#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	string s;
	cin >> s;
	char x = 'a';
	int ans = 0;
	for (char c : s)
	{
		char a = x, b = c;
		if (a > b) swap(a, b);
		ans += min(b - a, a + 26 - b);
		x = c;
	}
	cout << ans << endl;
}
