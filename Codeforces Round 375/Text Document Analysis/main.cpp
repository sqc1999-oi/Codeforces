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
	s += '_';
	int max = 0, cnt = 0, cur = 0;
	bool flag = false;
	for (int i = 0; i <= n; i++)
	{
		if (s[i] == '_' || s[i] == '(' || s[i] == ')')
		{
			if (cur > 0)
			{
				if (flag) cnt++;
				else max = ::max(max, cur);
			}
			if (s[i] == '(') flag = true;
			else if (s[i] == ')') flag = false;
			cur = 0;
		}
		else cur++;
	}
	cout << max << ' ' << cnt << endl;
}
