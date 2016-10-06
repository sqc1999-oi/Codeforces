#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
using namespace std;
const int N = 1e5, T = 100;
const double EPS = 1e-8;
struct line { long long a, b, c; } l[N];
vector<pair<int, int>> ans;
int rand(int l, int r)
{
	static mt19937 gen;
	uniform_int_distribution<> dist(l, r);
	return dist(gen);
}
bool dfs(const vector<int> &v, int k)
{
	if (v.size() <= k)
	{
		for (int x : v) ans.push_back({ x + 1,-1 });
		return true;
	}
	if (k == 0) return false;
	if (v.size() > k*k * 30)
	{
		for (int t = 0; t < T; t++)
		{
			int i = rand(0, v.size() - 1), j = rand(0, v.size() - 2);
			if (l[v[i]].a*l[v[j]].b == l[v[j]].a*l[v[i]].b) continue;
			if (j >= i) j++;
			if (l[v[i]].b == 0) swap(i, j);
			double x = (double)(l[v[j]].c*l[v[i]].b - l[v[i]].c*l[v[j]].b) / (l[v[i]].a*l[v[j]].b - l[v[j]].a*l[v[i]].b),
				y = -(l[v[i]].a*x + l[v[i]].c) / l[v[i]].b;
			vector<int> n;
			for (int id : v)
				if (fabs(l[id].a*x + l[id].b*y + l[id].c) > EPS)
					n.push_back(id);
			if (v.size() - n.size() > k)
			{
				ans.push_back({ v[i] + 1,v[j] + 1 });
				if (dfs(n, k - 1)) return true;
				ans.pop_back();
				return false;
			}
		}
		return false;
	}
	for (int i = 0; i <= k; i++)
		for (int j = i + 1; j <= k; j++)
		{
			if (l[v[i]].a*l[v[j]].b == l[v[j]].a*l[v[i]].b) continue;
			ans.push_back({ v[i] + 1,v[j] + 1 });
			int t = l[v[i]].b == 0 ? j : i;
			double x = (double)(l[v[j]].c*l[v[i]].b - l[v[i]].c*l[v[j]].b) / (l[v[i]].a*l[v[j]].b - l[v[j]].a*l[v[i]].b),
				y = -(l[v[t]].a*x + l[v[t]].c) / l[v[t]].b;
			vector<int> n;
			for (int id : v)
				if (fabs(l[id].a*x + l[id].b*y + l[id].c) > EPS)
					n.push_back(id);
			if (dfs(n, k - 1)) return true;
			ans.pop_back();
		}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	vector<int> v;
	for (int i = 0; i < n; i++)
	{
		cin >> l[i].a >> l[i].b >> l[i].c;
		v.push_back(i);
	}
	if (dfs(v, k))
	{
		cout << "YES" << endl << ans.size() << endl;
		for (const auto &x : ans)
			cout << x.first << ' ' << x.second << endl;
	}
	else cout << "NO" << endl;
}
