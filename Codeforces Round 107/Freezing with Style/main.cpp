#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <climits>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int N = 1e5, M = INT_MIN / 3, C = 1e9;
typedef pair<int, int> pii;
bool flag[N];
int sz[N], dep[N], depw[N], depm[N], ans = -1, u, v;
struct edge
{
	int to, w, next;
	bool operator <(const edge & e) const
	{
		return depm[to] < depm[e.to];
	}
};
vector<edge> g[N];
void get_nodes(int u, int fa, int *vi)
{
	vi[++vi[0]] = u;
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v]) get_nodes(v, u, vi);
	}
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v])
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
	}
}
void calc_dep(int u, int fa)
{
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v])
		{
			dep[v] = dep[u] + 1;
			calc_dep(v, u);
		}
	}
}
void calc_dep_max(int u, int fa)
{
	depm[u] = 0;
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v])
		{
			calc_dep_max(v, u);
			depm[u] = max(depm[u], depm[v]);
		}
	}
	depm[u]++;
}
void calc_depw(int u, int fa, int x)
{
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v])
		{
			depw[v] = depw[u];
			if (e.w < x) depw[v]--;
			else depw[v]++;
			calc_depw(v, u, x);
		}
	}
}
void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (edge &e : g[u])
	{
		int v = e.to;
		if (v != fa && !flag[v])
		{
			max = ::max(max, sz[v]);
			get_focus(v, u, n, ans, min);
		}
	}
	if (max < min)
	{
		min = max;
		ans = u;
	}
}
bool check(int u, int L, int R, int x, int &bu, int &bv)
{
	static int f[N], g[N], gp[N], fp[N];
	static int vi[N + 1];
	fill(f, f + depm[u], M);
	f[0] = 0, fp[0] = u;
	for (edge &e : ::g[u])
	{
		int v = e.to;
		if (flag[v]) continue;
		fill(g, g + depm[v] + 1, M);
		vi[0] = 0;
		get_nodes(v, u, vi);
		if (e.w < x) depw[v] = -1;
		else depw[v] = 1;
		calc_depw(v, u, x);
		for (int i = 1; i <= vi[0]; i++)
			if (g[dep[vi[i]]] < depw[vi[i]])
			{
				g[dep[vi[i]]] = depw[vi[i]];
				gp[dep[vi[i]]] = vi[i];
			}
		int a = depm[v], b = 0, c = 0;
		struct data { int t, v, p; };
		deque<data> q;
		int max = M;
		while (a >= 0)
		{
			while (b <= depm[v] && a + b < L) b++;
			c = ::max(c, b);
			while (c <= depm[v] && a + c <= R)
			{
				while (!q.empty() && (q.back().t < b || q.back().v <= f[c])) q.pop_back();
				q.push_back(data{ c,f[c],fp[c] });
				c++;
			}
			while (!q.empty() && q.front().t < b) q.pop_front();
			if (!q.empty() && max < q.front().v + g[a])
			{
				max = q.front().v + g[a];
				bu = q.front().p;
				bv = gp[a];
			}
			if (max >= 0) return true;
			a--;
		}
		for (int i = 1; i <= vi[0]; i++)
			if (f[dep[vi[i]]] < g[dep[vi[i]]])
			{
				f[dep[vi[i]]] = g[dep[vi[i]]];
				fp[dep[vi[i]]] = gp[dep[vi[i]]];
			}
	}
	return false;
}
void calc_ans(int u, int L, int R)
{
	sort(g[u].begin(), g[u].end());
	int l = 0, r = C, ans = 0, bu, bv;
	while (l <= r)
	{
		int mid = (l + r) / 2, cu, cv;
		if (check(u, L, R, mid, cu, cv))
		{
			ans = mid;
			bu = cu;
			bv = cv;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	if (::ans < ans)
	{
		::ans = ans;
		::u = bu;
		::v = bv;
	}
}
void solve(int u, int L, int R)
{
	calc_size(u, -1);
	if (sz[u] == 1 || sz[u] < L) return;
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	calc_dep_max(u, -1);
	dep[u] = 0;
	calc_dep(u, -1);
	calc_ans(u, L, R);
	flag[u] = true;
	for (edge &e : g[u]) if (!flag[e.to]) solve(e.to, L, R);
}
void read(int n, ...)
{
	va_list li;
	va_start(li, n);
	for (int i = 0; i < n; i++)
	{
		int &x = *va_arg(li, int *), ch;
		x = 0;
		do ch = getchar();
		while (!isdigit(ch));
		do
		{
			x = x * 10 + ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
int main()
{
	int n, L, R;
	read(3, &n, &L, &R);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		read(3, &a, &b, &c);
		a--, b--;
		g[a].push_back(edge{ b,c });
		g[b].push_back(edge{ a,c });
	}
	solve(0, L, R);
	printf("%d %d", u + 1, v + 1);
}
