#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	string s;
	cin >> s;
	int last = -1, ans = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' || s[i] == 'Y')
		{
			ans = max(ans, i - last);
			last = i;
		}
	cout << max(ans, (int)s.size() - last) << endl;
}