#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int, int> pii;
int l[26], m[26], w[26];
map<pii, pii> M;
pair<int, pii> ans;
void upd(pii &a, pii b)
{
	a = max(a, b);
}
void dfs(int i, int a, int b, int c, int s, int z)
{
	if (i < z)
	{
		upd(M[pii(a - b, a - c)], pii(a, s));
		return;
	}
	dfs(i - 1, a, b + m[i], c + w[i], s * 3 + 0, z);
	dfs(i - 1, a + l[i], b, c + w[i], s * 3 + 1, z);
	dfs(i - 1, a + l[i], b + m[i], c, s * 3 + 2, z);
}
void dfs2(int i, int a, int b, int c, int s, int z)
{
	if (i < z)
	{
		auto tmp = M.find(pii(b - a, c - a));
		if (tmp != M.end())
			ans = max(ans, make_pair(a + tmp->second.first, pii(tmp->second.second, s)));
		return;
	}
	dfs2(i - 1, a, b + m[i], c + w[i], s * 3 + 0, z);
	dfs2(i - 1, a + l[i], b, c + w[i], s * 3 + 1, z);
	dfs2(i - 1, a + l[i], b + m[i], c, s * 3 + 2, z);
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> l[i] >> m[i] >> w[i];
	dfs(n / 2, 1e9, 1e9, 1e9, 0, 1);
	dfs2(n, 1e9, 1e9, 1e9, 0, n / 2 + 1);
	if (ans.first != 0)
	{
		for (int i = 1; i <= n / 2; i++)
		{
			switch (ans.second.first % 3)
			{
			case 0: cout << "MW"; break;
			case 1: cout << "LW"; break;
			case 2: cout << "LM"; break;
			}
			cout << endl;
			ans.second.first /= 3;
		}
		for (int i = n / 2 + 1; i <= n; i++)
		{
			switch (ans.second.second % 3)
			{
			case 0: cout << "MW"; break;
			case 1: cout << "LW"; break;
			case 2: cout << "LM"; break;
			}
			cout << endl;
			ans.second.second /= 3;
		}
	}
	else cout << "Impossible";
}
