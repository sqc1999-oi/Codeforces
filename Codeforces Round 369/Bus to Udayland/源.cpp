#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	bool flag = false;
	string ans;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		if (!flag)
		{
			if (s[0] == 'O'&&s[1] == 'O')
			{
				s[0] = s[1] = '+';
				flag = true;
			}
			else if (s[3] == 'O'&&s[4] == 'O')
			{
				s[3] = s[4] = '+';
				flag = true;
			}
		}
		ans = ans + s + '\n';
	}
	if (flag) cout << "YES" << endl << ans;
	else cout << "NO" << endl;
}