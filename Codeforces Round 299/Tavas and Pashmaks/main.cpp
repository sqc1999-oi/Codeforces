#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
using namespace std;
struct pll
{
	long long x, y;
};
bool operator <(const pll &a, const pll &b)
{
	return a.x < b.x || a.x == b.x&&a.y < b.y;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<pll> v;
	map<pll, vector<int>> m;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		auto p = pll{ x,y };
		if (m[p].size() == 0) v.push_back(p);
		m[p].push_back(i + 1);
	}
	swap(v[0], *min_element(v.begin(), v.end(), [](const pll &a, const pll &b)
	{
		return a.y > b.y || a.y == b.y&&a.x > b.x;
	}));
	sort(v.begin() + 1, v.end(), [&v](const pll &a, const pll &b)
	{
		long long t = (v[0].x - a.x)*(v[0].y - b.y)*a.y*b.x - (v[0].y - a.y)*(v[0].x - b.x)*a.x*b.y;
		return t == 0
			? pow(1.0 / a.x - 1.0 / v[0].x, 2) + pow(1.0 / a.y - 1.0 / v[0].y, 2)
				> pow(1.0 / b.x - 1.0 / v[0].x, 2) + pow(1.0 / b.y - 1.0 / v[0].y, 2)
			: t > 0;
	});
	vector<pll> p;
	auto l = min_element(v.begin(), v.end(), [](const pll &a, const pll &b)
	{
		return a.x > b.x || a.x == b.x&&a.y > b.y;
	});
	p.push_back(v[0]);
	if (l != v.begin()) copy(l, v.end(), back_insert_iterator<vector<pll>>(p));
	vector<pll> hull;
	if (p.size() <= 3) hull = p;
	else
	{
		hull.push_back(p[0]);
		hull.push_back(p[1]);
		for (int i = 2; i < p.size(); i++)
		{
			while (hull.size() > 2)
			{
				pll &a = hull[hull.size() - 1], &b = hull[hull.size() - 2];
				if ((b.x - a.x)*(b.y - p[i].y)*a.y*p[i].x < (b.y - a.y)*(b.x - p[i].x)*a.x*p[i].y)
					hull.pop_back();
				else break;
			}
			hull.push_back(p[i]);
		}
	}
	vector<int> res;
	for (auto it = hull.begin(); it != hull.end(); it++)
		copy(m[*it].begin(), m[*it].end(), back_insert_iterator<vector<int>>(res));
	sort(res.begin(), res.end());
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
}