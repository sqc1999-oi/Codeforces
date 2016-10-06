#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
using namespace std;
const int N = 1e5;
int l[N], r[N];
bool flag[N];
void push(const list<int> &v, const string &s, list<list<int>> &ll, list<list<int>> &lr, list<list<int>> &rl, list<list<int>> &rr)
{
	if (s[v.front()] == 'L')
		if (s[v.back()] == 'L') ll.push_back(v);
		else lr.push_back(v);
	else
		if (s[v.back()] == 'L') rl.push_back(v);
		else rr.push_back(v);
}
int main()
{
	ios::sync_with_stdio(false);
	string s;
	cin >> s;
	int n = s.size();
	l[n - 1] = r[n - 1] = n;
	for (int i = n - 2; i >= 0; i--)
	{
		l[i] = s[i + 1] == 'L' ? i + 1 : l[i + 1];
		r[i] = s[i + 1] == 'R' ? i + 1 : r[i + 1];
	}
	list<list<int>> ll, rr, lr, rl;
	list<int> t;
	for (int i = 0; i < n; i++)
		if (!flag[i])
		{
			t.clear();
			for (int j = i; j < n;)
			{
				flag[j] = true;
				t.push_back(j);
				j = s[j] == 'L' ? r[j] : l[j];
			}
			push(t, s, ll, lr, rl, rr);
		}
	int sum = ll.size() + lr.size() + rl.size() + rr.size() - 1;
	auto &t1 = ll.size() > rr.size() ? ll : rr, t2 = ll.size() > rr.size() ? rr : ll;
	if (!t1.empty())
	{
		t = t1.front();
		t1.pop_back();
		while (ll.size() > 0)
		{
			t.splice(t.end(), t2.front());
			t2.pop_front();
			t.splice(t.end(), t1.front());
			t1.pop_front();
		}
		push(t, s, ll, lr, rl, rr);
	}
	if (!lr.empty())
	{
		t = lr.front();
		lr.pop_front();
		for (auto &&x : lr) t.splice(t.begin(), x);
		lr.clear();
		lr.push_back(t);
	}
	if (!rl.empty())
	{
		t = rl.front();
		rl.pop_front();
		for (auto &&x : rl) t.splice(t.begin(), x);
		rl.clear();
		rl.push_back(t);
	}
	if (!lr.empty() && !rl.empty())
	{
		t = lr.front();
		if (t.back() < rl.front().back())
		{
			t.push_back(rl.front().back());
			rl.front().pop_back();
		}
		else
		{
			rl.front().push_back(t.back());
			t.pop_back();
		}
		t.splice(t.end(), rl.back());
	}
	else if (!lr.empty()) t = lr.back();
	else if (!rl.empty()) t = rl.back();
	if (!ll.empty()) t.splice(t.end(), ll.front());
	else if (!rr.empty()) t.splice(t.end(), rl.front());
	cout << sum << endl;
	for (int x : t) cout << x << ' ';
	cout << endl;
}
