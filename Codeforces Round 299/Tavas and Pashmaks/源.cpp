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
	vector<pll> hull;
	if (v.size() <= 3) hull = v;
	else
	{
		hull.push_back(v[0]);
		hull.push_back(v[1]);
		for (int i = 2; i < v.size(); i++)
		{
			while (hull.size() > 2)
			{
				pll &a = hull[hull.size() - 1], &b = hull[hull.size() - 2];
				if ((b.x - a.x)*(b.y - v[i].y)*a.y*v[i].x < (b.y - a.y)*(b.x - v[i].x)*a.x*v[i].y)
					hull.pop_back();
				else break;
			}
			hull.push_back(v[i]);
		}
	}
	vector<int> res;
	auto l = min_element(hull.begin(), hull.end(), [](const pll &a, const pll &b)
	{
		return a.x > b.x || a.x == b.x&&a.y > b.y;
	});
	res.insert(res.end(), m[hull[0]].begin(), m[hull[0]].end());
	if (l != hull.begin()) for (auto it = l; it != hull.end(); it++) res.insert(res.end(), m[*it].begin(), m[*it].end());
	sort(res.begin(), res.end());
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
}