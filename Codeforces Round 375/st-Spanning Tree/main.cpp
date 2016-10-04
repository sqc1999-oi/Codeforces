#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2e5, M = 4e5;
pair<int, int> e[M], es[N], et[N];
int f[N];
bool cs[N], ct[N];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> e[i].first >> e[i].second;
		e[i].first--;
		e[i].second--;
	}
	int s, t, ds, dt;
	cin >> s >> t >> ds >> dt;
	s--;
	t--;
	for (int i = 0; i < n; i++) f[i] = i;
	vector<pair<int, int>> ans;
	bool flag = false;
	for (int i = 0; i < m; i++)
	{
		int u = e[i].first, v = e[i].second;
		if (u == s&&v == t || u == t&&v == s) flag = true;
		if (u != s&&u != t&&v != s&&v != t)
		{
			int x = find(u), y = find(v);
			if (x != y)
			{
				f[x] = y;
				ans.push_back({ u,v });
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		int u = e[i].first, v = e[i].second;
		if (v == s) swap(u, v);
		if (u == s&&v != t)
		{
			int x = find(v);
			cs[x] = true;
			es[x] = { u,v };
		}
		if (v == t) swap(u, v);
		if (u == t&&v != s)
		{
			int x = find(v);
			ct[x] = true;
			et[x] = { u,v };
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (cs[i] && ct[i]) cnt++;
		else if (cs[i])
		{
			if (--ds == 0) break;
			ans.push_back(es[i]);
		}
		else if (ct[i])
		{
			if (--dt == 0) break;
			ans.push_back(et[i]);
		}
	}
	if (ds <= 0 || dt <= 0) cout << "No" << endl;
	else if (ds + dt - 2 >= cnt&&flag)
	{
		ans.push_back({ s,t });
		for (int i = 0; i < n; i++)
			if (cs[i] && ct[i])
			{
				if (ds > 0)
				{
					ds--;
					ans.push_back(es[i]);
				}
				else ans.push_back(et[i]);
			}
		cout << "Yes" << endl;
		for (const auto &p : ans)
			cout << p.first + 1 << ' ' << p.second + 1 << endl;
	}
	else if (ds + dt >= cnt + 1)
	{
		bool flag = true;
		for (int i = 0; i < n; i++)
			if (cs[i] && ct[i])
			{
				if (flag)
				{
					ds--;
					flag = false;
					ans.push_back(es[i]);
					ans.push_back(et[i]);
				}
				else if (ds > 0)
				{
					ds--;
					ans.push_back(es[i]);
				}
				else ans.push_back(et[i]);
			}
		cout << "Yes" << endl;
		for (const auto &p : ans)
			cout << p.first + 1 << ' ' << p.second + 1 << endl;
	}
	else cout << "No" << endl;
}
