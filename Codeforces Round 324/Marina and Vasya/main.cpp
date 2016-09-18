#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
char get(char a, char b)
{
	char ret = 'a';
	while (ret == a || ret == b) ret++;
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, t;
	cin >> n >> t;
	t = n - t;
	string s1, s2;
	cin >> s1 >> s2;
	string s3;
	s3.resize(n);
	for (int i = 0; i < n; i++)
		if (s1[i] == s2[i] && t > 0)
		{
			s3[i] = s1[i];
			t--;
		}
	t *= 2;
	for (int i = 0; i < n; i++)
		if (s1[i] != s2[i] && t > 0)
		{
			s3[i] = t % 2 == 0 ? s1[i] : s2[i];
			t--;
		}
	if (t > 0) return cout << -1, 0;
	for (int i = 0; i < n; i++)
		if (s3[i] == 0)
			s3[i] = get(s1[i], s2[i]);
	cout << s3;
}
