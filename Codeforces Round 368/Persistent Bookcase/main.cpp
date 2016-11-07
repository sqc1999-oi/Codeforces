#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
const int N = 1000, Q = 1e5;
struct node
{
	int t, x, y, ans;
} tree[Q + 1];
vector<int> g[Q + 1];
bitset<N> bs[N];
int cnt[N];
void dfs(int u, int ans, int m)
{
	node &n = tree[u];
	bool flag = false;
	if (u > 0)
	{
		if (tree[u].t == 1)
		{
			flag = !bs[n.x][n.y];
			ans += flag;
			cnt[n.x] += flag;
			bs[n.x][n.y] = 1;
		}
		else if (tree[u].t == 2)
		{
			flag = bs[n.x][n.y];
			ans -= flag;
			cnt[n.x] -= flag;
			bs[n.x][n.y] = 0;
		}
		else if (tree[u].t == 3)
		{
			ans = ans - cnt[n.x] + m - cnt[n.x];
			cnt[n.x] = m - cnt[n.x];
			bs[n.x].flip();
		}
	}
	n.ans = ans;
	for (int i = 0; i < g[u].size(); i++) dfs(g[u][i], ans, m);
	if (u > 0)
	{
		if (tree[u].t == 1)
		{
			cnt[n.x] -= flag;
			if (flag) bs[n.x][n.y] = 0;
		}
		else if (tree[u].t == 2)
		{
			cnt[n.x] += flag;
			if (flag) bs[n.x][n.y] = 1;
		}
		else if (tree[u].t == 3)
		{
			cnt[n.x] = m - cnt[n.x];
			bs[n.x].flip();
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= q; i++)
	{
		cin >> tree[i].t >> tree[i].x;
		if (tree[i].t != 4)
		{
			g[i - 1].push_back(i);
			tree[i].x--;
		}
		if (tree[i].t <= 2)
		{
			cin >> tree[i].y;
			tree[i].y--;
		}
		else if (tree[i].t == 4) g[tree[i].x].push_back(i);
	}
	dfs(0, 0, m);
	for (int i = 1; i <= q; i++) cout << tree[i].ans << endl;
}
