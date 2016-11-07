#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	int n, t;
	string s;
	cin >> n >> t >> s;
	bool flag = false;
	int x = -1;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.') flag = true;
		if (flag&&s[i] >= '5')
		{
			x = i;
			break;
		}
	}
	if (x != -1)
	{
		if (s[x - 1] == '.')
		{
			s[x - 2]++;
			s = s.substr(0, x - 1);
			for (int i = x - 2; i >= 0 && s[i] == ':'; i--)
			{
				s[i] = '0';
				if (i > 0) s[i - 1]++;
				else s = '1' + s;
			}
			cout << s;
		}
		else
		{
			x--;
			if (t > 1)
				for (; s[x] >= '4'; x--)
					if (--t == 1)
					{
						x--;
						break;
					}
			if (s[x] == '.')
			{
				s = s.substr(0, x);
				s[x - 1]++;
				for (int i = x - 1; i >= 0 && s[i] == ':'; i--)
				{
					s[i] = '0';
					if (i > 0) s[i - 1]++;
					else s = '1' + s;
				}
				cout << s;
			}
			else
			{
				s[x]++;
				cout << s.substr(0, x + 1);
			}
		}
	}
	else cout << s;
	cout << endl;
}
