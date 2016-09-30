#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	string s;
	cin >> n >> s;
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0 && s[i] != 'r') cnt1++;
		if (i % 2 == 1 && s[i] != 'b') cnt2++;
	}
	int ans = max(cnt1, cnt2);
	cnt1 = cnt2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0 && s[i] != 'b') cnt1++;
		if (i % 2 == 1 && s[i] != 'r') cnt2++;
	}
	ans = min(ans, max(cnt1, cnt2));
	cout << ans << endl;
}
