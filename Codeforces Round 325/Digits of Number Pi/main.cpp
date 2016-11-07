#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1000, D = 50, P = 1e9 + 7;
struct node
{
	node *ch[10], *f;
	bool flag;
} pool[N*D / 2 + 1];
int f[D + 1][N*D / 2 + 1][2][2], cnt;
node *new_node() { return &pool[cnt++]; }
void update(int &x, int y) { x = (x + y) % P; }
int calc(const string &s)
{
	memset(f, 0x00, sizeof f);
	f[0][0][1][0] = 1;
	int d = s.size();
	for (int i = 0; i < d; i++)
		for (int j = 0; j < cnt; j++)
			for (int k = 0; k < 10; k++)
			{
				auto x = pool[j].ch[k];
				update(f[i + 1][x - pool][0][x->flag], f[i][j][0][0]);
				update(f[i + 1][x - pool][0][1], f[i][j][0][1]);
				if (k <= s[i] - '0')
				{
					update(f[i + 1][x - pool][k == s[i] - '0'][x->flag], f[i][j][1][0]);
					update(f[i + 1][x - pool][k == s[i] - '0'][1], f[i][j][1][1]);
				}
			}
	int ans = 0;
	for (int i = 0; i < cnt; i++)
	{
		update(ans, f[d][i][0][1]);
		update(ans, f[d][i][1][1]);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	string s, x, y;
	cin >> s >> x >> y;
	int d = x.size();
	auto rt = new_node();
	for (int i = 0; i + d / 2 <= s.size(); i++)
	{
		auto c = rt;
		for (int j = i; j < i + d / 2; j++)
		{
			auto &x = c->ch[s[j] - '0'];
			if (x == nullptr) x = new_node();
			c = x;
		}
		c->flag = true;
	}
	rt->f = rt;
	queue<node *> q;
	for (int i = 0; i < 10; i++)
	{
		auto &x = rt->ch[i];
		if (x == nullptr) x = rt;
		else
		{
			x->f = rt;
			q.push(x);
		}
	}
	while (!q.empty())
	{
		auto u = q.front();
		q.pop();
		for (int i = 0; i < 10; i++)
		{
			auto &v = u->ch[i];
			if (v == nullptr) v = u->f->ch[i];
			else
			{
				v->f = u->f->ch[i];
				v->flag |= v->f->flag;
				q.push(v);
			}
		}
	}
	int pos = d - 1;
	for (; x[pos] == '0'; pos--) x[pos] = '9';
	x[pos]--;
	cout << (calc(y) - calc(x) + P) % P << endl;
}
