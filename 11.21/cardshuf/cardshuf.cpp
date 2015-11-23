#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstdarg>
using namespace std;
struct node
{
	node *ls, *rs, *fa;
	bool rev;
	int size, val;
	bool is_empty()
	{ return size == 0; }
	void maintain()
	{ size = ls->size + rs->size + 1; }
	void push_down()
	{
		rev ^= 1;
		ls->rev ^= 1;
		rs->rev ^= 1;
		swap(ls, rs);
	}
	void zag()
	{
		node *y = fa;
		node *z = y->fa;
		y->rs = ls;
		if (!y->rs->is_empty())
			y->rs->fa = y;
		fa = z;
		y->fa = this;
		ls = y;
		if (!z->is_empty())
		{
			if (z->ls == y) z->ls = this;
			else z->rs = this;
		}
		y->maintain();
		maintain();
	}
	void zig()
	{
		node *y = fa;
		node *z = y->fa;
		y->ls = rs;
		if (!y->ls->is_empty()) y->ls->fa = y;
		fa = z;
		y->fa = this;
		rs = y;
		if (!z->is_empty())
		{
			if (z->ls == y) z->ls = this;
			else z->rs = this;
		}
		y->maintain();
		maintain();
	}
	void splay()
	{
		while (!fa->is_empty())
		{
			node *y = fa;
			node *z = y->fa;
			if (z->is_empty())
			{
				if (y->ls == this) zig();
				else zag();
				break;
			}
			if (z->ls == y)
			{
				if (y->ls == this) zig(), zig();
				else zag(), zig();
			}
			else
			{
				if (y->ls == this) zig(), zag();
				else zag(), zag();
			}
		}
	}
	node *find(int x)
	{
		if (rev) push_down();
		if (ls->size >= x)
			return ls->find(x);
		else if (ls->size + 1 == x)
		{
			splay();
			return this;
		}
		else return rs->find(x - ls->size - 1);
	}
	void display(FILE *f, int n)
	{
		if (rev) push_down();
		if (!ls->is_empty()) ls->display(f, n);
		if (val <= n) fprintf(f, "%d ", val);
		if (!rs->is_empty()) rs->display(f, n);
	}
	static node *get_empty()
	{
		static node empty;
		return &empty;
	}
	static node *build(int l, int r)
	{
		if (l > r) return get_empty();
		int mid = (l + r) / 2;
		node *x = new node();
		x->ls = build(l, mid - 1);
		x->rs = build(mid + 1, r);
		x->ls->fa = x->rs->fa = x;
		x->rev = false;
		x->maintain();
		x->val = mid;
		return x;
	}
};
void read(FILE *f, int cnt, ...)
{
	va_list li;
	va_start(li, cnt);
	for (int i = 0; i < cnt; i++)
	{
		int &x = *va_arg(li, int *);
		x = 0;
		char ch;
		do ch = getc(f);
		while (!isdigit(ch));
		do
		{
			(x *= 10) += ch - '0';
			ch = getc(f);
		}
		while (isdigit(ch));
	}
	va_end(li);
}
int main()
{
	FILE *in, *out;
#ifndef DEBUG
	in = fopen("cardshuf.in", "r");
	out = fopen("cardshuf.out", "w");
#else
	in = stdin;
	out = stdout;
#endif
	int n, m;
	read(in, 2, &n, &m);
	node *root = node::build(1, n + 1);
	root->fa = node::get_empty();
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		read(in, 3, &a, &b, &c);

		root = root->find(a + 1);
		node *A = root->ls;
		root->ls = A->fa = node::get_empty();
		root->maintain();

		root = root->find(b + 1);
		node *B = root->ls;
		root->ls = B->fa = node::get_empty();
		root->maintain();

		root = root->find(1);
		root->ls = A;
		A->fa = root;
		root->maintain();

		root = root->find(c + 1);
		node *C = root->ls;
		root->ls = C->fa = node::get_empty();
		root->maintain();

		B->rev ^= 1;
		root = root->find(1);
		root->ls = B;
		B->fa = root;
		root->maintain();

		root = root->find(1);
		root->ls = C;
		C->fa = root;
		root->maintain();
	}
	root->display(out, n);
}
