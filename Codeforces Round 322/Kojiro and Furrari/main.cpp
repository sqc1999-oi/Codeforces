#include <cstdio>
#include <algorithm>
#include <vector>
#include <cctype>
#include <cstdarg>
using namespace std;
int f[3][200001];
void Read(int cnt, ...)
{
	va_list li;
	va_start(li, cnt);
	for (int i = 0; i < cnt; i++)
	{
		int &x = *va_arg(li, int*);
		x = 0;
		char ch = 0;
		int flag = 1;
		do
		{
			if (ch == '-') flag = -1;
			else flag = 1;
			ch = getchar();
		}
		while (!isdigit(ch));
		do
		{
			(x *= 10) += ch - '0';
			ch = getchar();
		}
		while (isdigit(ch));
		x *= flag;
	}
	va_end(li);
}
int main()
{
	vector<int> v[3];
	int e, s, n, m;
	Read(4, &e, &s, &n, &m);
	for (int i = 0; i < 3; i++)
		v[i].push_back(e);
	for (int i = 0; i < n; i++)
	{
		int t, p;
		Read(2, &t, &p);
		if (p >= e) continue;
		for (int j = 0; j < t; j++)
			v[j].push_back(p);
	}
	for (int i = 0; i < 3; i++)
	{
		sort(v[i].begin(), v[i].end());
		for (int j = v[i].size() - 2; j >= 0; j--)
			f[i][j] = f[i][j + 1] + max(0, v[i][j + 1] - v[i][j] - s);
	}
	auto calc = [s](int st, vector<int> &v, int *f)
	{
		int x = lower_bound(v.begin(), v.end(), st) - v.begin();
		return f[x] + max(0, v[x] - st - s);
	};
	for (int i = 0; i < m; i++)
	{
		int fi;
		Read(1, &fi);
		int ans[3];
		for (int i = 0; i < 3; i++)
			ans[i] = calc(fi, v[i], f[i]);
		if (ans[0] > 0) printf("-1 -1\n");
		else printf("%d %d\n", ans[1], ans[2] - ans[1]);
	}
}
