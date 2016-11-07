#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <functional>
using namespace std;
void push(const list<int> &v, const string &s, list<list<int>> &ll, list<list<int>> &lr, list<list<int>> &rl, list<list<int>> &rr)
{
	if (s[v.front()] == 'L')
		if (s[v.back()] == 'L') ll.push_back(v);
		else lr.push_back(v);
	else
		if (s[v.back()] == 'L') rl.push_back(v);
		else rr.push_back(v);
}
void combine_llrr(const string &s, list<list<int>> &ll, list<list<int>> &lr, list<list<int>> &rl, list<list<int>> &rr)
{
	if (ll.size() < rr.size()) swap(ll, rr);
	list<int> t;
	for (; !ll.empty(); swap(ll, rr))
	{
		t.splice(t.end(), move(ll.front()));
		ll.pop_front();
	}
	push(t, s, ll, lr, rl, rr);
}
void combine_lr_rl(list<list<int>> &li)
{
	if (!li.empty())
	{
		auto t = move(li.front());
		li.pop_front();
		for (auto &&x : li) t.splice(t.end(), x);
		li.clear();
		li.push_back(move(t));
	}
}
list<int> combine_all(list<list<int>> &ll, list<list<int>> &lr, list<list<int>> &rl, list<list<int>> &rr)
{
	list<int> t;
	if (!lr.empty() && !rl.empty())
	{
		t = move(lr.front());
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
		t.splice(t.end(), move(rl.front()));
	}
	else if (!lr.empty()) t = move(lr.back());
	else if (!rl.empty())
	{
		t = move(rl.back());
		swap(ll, rr);
	}
	if (!ll.empty()) t.splice(t.end(), move(ll.front()));
	else if (!rr.empty()) t.splice(t.begin(), move(rr.front()));
	ll.clear();
	lr.clear();
	rl.clear();
	rr.clear();
	return t;
}
void generate(const string &s, list<list<int>> &ll, list<list<int>> &lr, list<list<int>> &rl, list<list<int>> &rr)
{
	const int N = 1e5;
	static int l[N], r[N], f[N + 1];
	int n = s.size();
	l[n - 1] = r[n - 1] = n;
	for (int i = n - 2; i >= 0; i--)
	{
		l[i] = s[i + 1] == 'L' ? i + 1 : l[i + 1];
		r[i] = s[i + 1] == 'R' ? i + 1 : r[i + 1];
	}
	for (int i = 0; i <= n; i++) f[i] = i;
	function<int(int)> find = [&find](int x) { return x == f[x] ? x : f[x] = find(f[x]); };
	for (int i = 0; i < n; i++)
		if (find(i) == i)
		{
			list<int> t;
			int j = i;
			while (true)
			{
				t.push_back(j);
				int k = find(s[j] == 'L' ? r[j] : l[j]);
				if (k == n) break;
				f[k] = find(s[j] == 'L' ? r[k] : l[k]);
				j = k;
			}
			push(t, s, ll, lr, rl, rr);
		}
}
int main()
{
	ios::sync_with_stdio(false);
	string s;
	cin >> s;
	list<list<int>> ll, lr, rl, rr;
	generate(s, ll, lr, rl, rr);
	int sum = ll.size() + lr.size() + rl.size() + rr.size() - 1;
	combine_llrr(s, ll, lr, rl, rr);
	combine_lr_rl(lr);
	combine_lr_rl(rl);
	cout << sum << endl;
	for (int x : combine_all(ll, lr, rl, rr)) cout << x + 1 << ' ';
	cout << endl;
}
