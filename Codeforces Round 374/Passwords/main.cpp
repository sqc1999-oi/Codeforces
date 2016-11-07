#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;
const int N = 100;
string a[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	copy_n(istream_iterator<string>(cin), n, a);
	string p;
	cin >> p;
	sort(a, a + n, [&p](const string &a, const string &b)
	{
		if (a.size() == b.size()) return a == p;
		return a.size() < b.size();
	});
	int cnt = 0, ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans++;
		if (a[i] == p) break;
		if ((++cnt %= k) == 0) ans += 5;
	}
	cout << ans << ' ';
	sort(a, a + n, [&p](const string &a, const string &b)
	{
		if (a.size() == b.size()) return b == p;
		return a.size() < b.size();
	});
	cnt = ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans++;
		if (a[i] == p) break;
		if ((++cnt %= k) == 0) ans += 5;
	}
	cout << ans << endl;
}
