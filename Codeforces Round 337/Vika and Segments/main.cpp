#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 1e5;
struct seg
{
	int a, b0, b1;
};
struct op
{
	seg s;
	int t;
};
void sort_and_unite(vector<seg> &v)
{
	if (v.empty()) return;
	sort(v.begin(), v.end(), [](const seg &a, const seg &b) { return a.a < b.a || a.a == b.a&&a.b0 < b.b0; });
	int i = 0;
	for (int j = 1; j < v.size(); j++)
	{
		if (v[j].a == v[i].a&&v[j].b0 <= v[i].b1) v[i].b1 = max(v[i].b1, v[j].b1);
		else v[++i] = v[j];
	}
	v.resize(i + 1);
}
long long calc_total(const vector<seg> &v)
{
	long long ret = 0;
	for (seg s : v) ret += s.b1 - s.b0 + 1;
	return ret;
}
void discrete(vector<seg> &r, vector<seg> &c)
{
	vector<int> v;
	for (seg s : r)
	{
		v.push_back(s.b0);
		v.push_back(s.b1);
	}
	for (seg s : c) v.push_back(s.a);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	auto update = [&v](int &x) { x = lower_bound(v.begin(), v.end(), x) - v.begin() + 1; };
	for (int i = 0; i < r.size(); i++)
	{
		update(r[i].b0);
		update(r[i].b1);
	}
	for (int i = 0; i < c.size(); i++) update(c[i].a);
}
long long calc_intersection(const vector<seg> &r, const vector<seg> &c)
{
	static int t[3 * N + 3];
	auto lowbit = [](int x) { return x&-x; };
	auto update = [&lowbit](int pos, int val)
	{
		while (pos <= N)
		{
			t[pos] += val;
			pos += lowbit(pos);
		}
	};
	auto query = [&lowbit](int pos)
	{
		int ret = 0;
		while (pos > 0)
		{
			ret += t[pos];
			pos -= lowbit(pos);
		}
		return ret;
	};
	memset(t, 0x00, sizeof t);
	long long ret = 0;
	vector<op> v;
	for (seg s : r) v.push_back({ s,1 });
	for (seg s : c)
	{
		v.push_back({ s,0 });
		v.push_back({ s,2 });
	}
	sort(v.begin(), v.end(), [](const op &a, const op &b)
	{
		static auto get = [](const op &x)
		{
			if (x.t == 0) return x.s.b0;
			if (x.t == 1) return x.s.a;
			return x.s.b1;
		};
		int x = get(a), y = get(b);
		return x < y || x == y&&a.t < b.t;
	});
	for (op x : v)
	{
		if (x.t == 0) update(x.s.a, 1);
		else if (x.t == 2) update(x.s.a, -1);
		else ret += query(x.s.b1) - query(x.s.b0 - 1);
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<seg> r, c;
	for (int i = 0; i < n;i++)
	{
		int x0, y0, x1, y1;
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 > x1) swap(x0, x1);
		if (y0 > y1) swap(y0, y1);
		if (y0 == y1) r.push_back({ y0,x0,x1 });
		else c.push_back({ x0,y0,y1 });
	}
	sort_and_unite(r);
	sort_and_unite(c);
	long long ans = calc_total(r) + calc_total(c);
	discrete(r, c);
	ans -= calc_intersection(r, c);
	cout << ans;
}
