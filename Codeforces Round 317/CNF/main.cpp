#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;
int sign(int a)
{
	return a < 0 ? -1 : 1;
}
int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<set<int> > terms(n + 1);
	vector<int> ans(m + 1, 0);
	auto bySize = [&terms](int a, int b)
	{
		return make_pair(terms[a].size(), a) < make_pair(terms[b].size(), b);
	};
	set<int, decltype(bySize)> undecided_terms(bySize);
	vector<vector<int>> positions(m + 1);
	for (int i = 1; i <= n; ++i)
	{
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j)
		{
			int p;
			cin >> p;
			terms[i].insert(p);
			positions[abs(p)].push_back(i * sign(p));
		}
		undecided_terms.insert(i);
	}
	while (!undecided_terms.empty())
	{
		int id = *undecided_terms.begin();
		if (terms[id].empty())
		{
			cout << "NO";
			return 0;
		}
		int val = *terms[id].begin();
		if (val > 0)
			ans[val] = 1;
		for (int to : positions[abs(val)])
		{
			if (sign(val) == sign(to))
				undecided_terms.erase(abs(to));
			else
			{
				if (undecided_terms.erase(abs(to)))
				{
					terms[abs(to)].erase(-val);
					undecided_terms.insert(abs(to));
				}
			}
		}

	}
	cout << "YES" << endl;
	for (int i = 1; i <= m; ++i)
		cout << ans[i];
}
