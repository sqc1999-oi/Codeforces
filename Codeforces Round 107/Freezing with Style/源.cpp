#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <climits>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 100000;
typedef pair<int, int> pii;
struct edge
{
	int to, w, next;
	edge(int to, int w, int next) :to(to), w(w), next(next) { }
	edge() { }
} e[N * 2];
int g[N];
bool flag[N], vis[N];
int sz[N], dep[N], depw[N], Ans = -1, U, V;
void get_nodes(int u, int fa, int *vi)
{
	vi[++vi[0]] = u;
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if (v != fa && !flag[v])
			get_nodes(v, u, vi);
	}
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if (v != fa && !flag[v])
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
	}
}
void calc_dep(int u, int fa)
{
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if (v != fa && !flag[v])
		{
			dep[v] = dep[u] + 1;
			calc_dep(v, u);
		}
	}
}
void calc_depw(int u, int fa, int mid)
{
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if (v != fa && !flag[v])
		{
			depw[v] = depw[u];
			if (e[i].w < mid) depw[v]--;
			else depw[v]++;
			calc_depw(v, u, mid);
		}
	}
}
void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = e[i].to;
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
bool check(int u, int L, int R, int mid, int &U, int &V)
{
	static int f[N], g[N], gp[N], fp[N], qp[N];
	static pii q[N];
	static int vi[N + 1];
	for (int i = 0; i <= sz[u]; i++) f[i] = INT_MIN / 3;
	f[0] = 0, fp[0] = u;
	for (int i = ::g[u]; i != -1; i = e[i].next)
	{
		int v = ::e[i].to;
		if (flag[v]) continue;
		for (int i = 0; i <= sz[v]; i++) g[i] = INT_MIN / 3;
		vi[0] = 0;
		get_nodes(v, u, vi);
		if (e[i].w < mid) depw[v] = -1;
		else depw[v] = 1;
		calc_depw(v, u, mid);
		for (int i = 1; i <= vi[0]; i++)
			if (g[dep[vi[i]]] < depw[vi[i]])
			{
				g[dep[vi[i]]] = depw[vi[i]];
				gp[dep[vi[i]]] = vi[i];
			}
		int a = sz[v], b = 0, c = 0, h = 0, t = 0;
		int max = INT_MIN / 3;
		while (a >= 0)
		{
			while (b < sz[u] && a + b < L) b++;
			if (c < b) c = b;
			while (c < sz[u] && a + c <= R)
			{
				while (h != t && (q[t - 1].second < b || q[t - 1].first <= f[c])) t--;
				q[t].first = f[c];
				q[t].second = c;
				qp[t] = fp[c];
				t++;
				c++;
			}
			while (h != t && q[h].second < b) h++;
			if (h != t && max < q[h].first + g[a])
			{
				max = q[h].first + g[a];
				U = qp[h];
				V = gp[a];
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
	int l = Ans, r = 1e9, ans = 0, _U, _V;
	while (l <= r)
	{
		int mid = (l * 9 + r) / 10, _u, _v;
		if (check(u, L, R, mid, _u, _v))
		{
			ans = mid;
			_U = _u;
			_V = _v;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	if (Ans < ans)
	{
		Ans = ans;
		U = _U;
		V = _V;
	}
}
void solve(int u, int L, int R)
{
	calc_size(u, -1);
	if (sz[u] == 1 || sz[u] <= L) return;
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	calc_size(u, -1);
	flag[u] = true;
	dep[u] = 0;
	calc_dep(u, -1);
	calc_ans(u, L, R);
	for (int i = g[u]; i != -1; i = e[i].next)
		if (!flag[e[i].to]) solve(e[i].to, L, R);
}
void read(int n, ...)
{
	va_list li;
	va_start(li, n);
	for (int i = 0; i < n; i++)
	{
		int &x = *va_arg(li, int *);
		x = 0;
		char ch;
		do ch = getchar();
		while (!isdigit(ch));
		do
		{
			(x *= 10) += ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
int main()
{
	memset(g, 0xff, sizeof g);
	int n, L, R;
	read(3, &n, &L, &R);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		read(3, &a, &b, &c);
		a--;
		b--;
		e[i] = edge(b, c, g[a]);
		g[a] = i;
		e[i + n - 1] = edge(a, c, g[b]);
		g[b] = i + n - 1;
	}
	solve(0, L, R);
	printf("%d %d", U + 1, V + 1);
}
