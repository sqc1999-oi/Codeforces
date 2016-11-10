#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
const int N = 2e5;
pair<int, int> s[N];
int a[N], b[N];
struct cmp { bool operator ()(const pair<int, int> &a, const pair<int, int> &b) const { return a.first < b.first; } };
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	multiset<pair<int, int>, cmp> p;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		p.insert({ x,i });
	}
	for (int i = 0; i < m; i++)
	{
		cin >> s[i].first;
		s[i].second = i;
	}
	sort(s, s + m);
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0, x = s[i].first;; j++, x = (x + 1) / 2)
		{
			auto it = p.find({ x,-1 });
			if (it != p.end())
			{
				a[s[i].second] = j;
				cnt += j;
				b[it->second] = s[i].second + 1;
				p.erase(it);
				break;
			}
			if (x == 1) break;
		}
	}
	cout << n - p.size() << ' ' << cnt << endl;
	for (int i = 0; i < m; i++) cout << a[i] << ' ';
	cout << endl;
	for (int i = 0; i < n; i++) cout << b[i] << ' ';
	cout << endl;
}
