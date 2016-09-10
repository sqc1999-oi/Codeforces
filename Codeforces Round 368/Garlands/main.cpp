#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
void read(int n,...)
{
	va_list li;
	va_start(li, n);
	while (n--)
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
const int N = 2000, Q = 1e6;
struct bulb { int x, y, w; };
vector<bulb> gl[N];
struct query
{
	int t, id, x1, y1, x2, y2;
} a[Q], *q[N];
long long sum[N][N];
long long t[N + 1][N + 1];
bool flag[Q];
int lowbit(int x) { return x&-x; }
void update(int x, int y, int v, int n, int m)
{
	for (; x <= n; x += lowbit(x))
		for (int k = y; k <= m; k += lowbit(k))
			t[x][k] += v;
}
long long query(int x, int y)
{
	long long ans = 0;
	for (; x > 0; x -= lowbit(x))
		for (int k = y; k > 0; k -= lowbit(k))
			ans += t[x][k];
	return ans;
}
int main()
{
	int n, m, k;
	read(3, &n, &m, &k);
	for (int i = 0; i < k; i++)
	{
		int len;
		read(1, &len);
		gl[i].resize(len);
		for (int j = 0; j < len; j++) read(3, &gl[i][j].x, &gl[i][j].y, &gl[i][j].w);
	}
	int q, qcnt = 0;
	read(1, &q);
	for (int i = 0; i < q; i++)
	{
		char ch = getchar();
		if (ch == 'S')
		{
			a[i].t = 0;
			read(1, &a[i].id);
		}
		else if (ch == 'A')
		{
			a[i].t = 1;
			a[i].id = qcnt;
			read(4, &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
			::q[qcnt++] = &a[i];
		}
	}
	for (int i = 0; i < k; i++)
	{
		for (bulb &b : gl[i]) update(b.x, b.y, b.w, n, m);
		for (int j = 0; j < qcnt; j++)
		{
			sum[j][i] = query(::q[j]->x2, ::q[j]->y2)
				- query(::q[j]->x1 - 1, ::q[j]->y2)
				- query(::q[j]->x2, ::q[j]->y1 - 1)
				+ query(::q[j]->x1 - 1, ::q[j]->y1 - 1);
		}
		for (bulb &b : gl[i]) update(b.x, b.y, -b.w, n, m);
	}
	fill(flag, flag + k, true);
	for (int i = 0; i < q; i++)
	{
		if (a[i].t == 0) flag[a[i].id - 1] ^= 1;
		else if (a[i].t == 1)
		{
			long long ans = 0;
			for (int j = 0; j < k; j++) ans += flag[j] * sum[a[i].id][j];
			printf("%I64d\n", ans);
		}
	}
}