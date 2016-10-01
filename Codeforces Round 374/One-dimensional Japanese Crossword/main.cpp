#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	string s;
	cin >> s;
	s += 'W';
	int cnt = 0;
	vector<int> v;
	for (int i = 0; i <= n; i++)
	{
		if (s[i] == 'B') cnt++;
		else
		{
			if (cnt > 0) v.push_back(cnt);
			cnt = 0;
		}
	}
	cout << v.size() << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}
