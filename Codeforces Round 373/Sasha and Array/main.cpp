#include <iostream>
#include <algorithm>
using namespace std;
const int P = 1e9 + 7;
struct matrix1 { int a, b; };
struct matrix2 { int a, b, c, d; };
matrix1 operator +(const matrix1 &x, const matrix1 &y)
{
	matrix1 ret;
	ret.a = (x.a + y.a) % P;
	ret.b = (x.b + y.b) % P;
	return ret;
}
matrix1 operator *(const matrix1 &x, const matrix2 &y)
{
	matrix1 ret;
	ret.a = ((long long)x.a*y.a + (long long)x.b*y.c) % P;
	ret.b = ((long long)x.a*y.b + (long long)x.b*y.d) % P;
	return ret;
}
matrix2 operator *(const matrix2 &x, const matrix2 &y)
{
	matrix2 ret;
	ret.a = ((long long)x.a*y.a + (long long)x.b*y.c) % P;
	ret.b = ((long long)x.a*y.b + (long long)x.b*y.d) % P;
	ret.c = ((long long)x.c*y.a + (long long)x.d*y.c) % P;
	ret.d = ((long long)x.c*y.b + (long long)x.d*y.d) % P;
	return ret;
}
matrix2 power(const matrix2 &x, int k)
{
	matrix2 t = x, ret;
	ret.a = ret.d = 1;
	ret.b = ret.c = 0;
	while (k > 0)
	{
		if (k & 1) ret = ret*t;
		t = t*t;
		k >>= 1;
	}
	return ret;
}
struct seg_node
{
	matrix1 sum;
	matrix2 mul;
	seg_node *l, *r;
	seg_node(seg_node *l, seg_node *r) :l(l), r(r)
	{
		sum = l->sum + r->sum;
		mul.a = mul.d = 1;
		mul.b = mul.c = 0;
	}
	seg_node(): l(NULL), r(NULL)
	{
		sum.a = 0;
		sum.b = 1;
		mul.a = mul.d = 1;
		mul.b = mul.c = 0;
	}
	static seg_node *build(int l, int r)
	{
		if (l == r - 1) return new seg_node;
		int mid = (l + r) / 2;
		return new seg_node(build(l, mid), build(mid, r));
	}
	void push_down()
	{
		if (mul.a == 1 && mul.b == 0 && mul.c == 0 && mul.d == 1) return;
		l->sum = l->sum*mul;
		l->mul = l->mul*mul;
		r->sum = r->sum*mul;
		r->mul = r->mul*mul;
		mul.a = mul.d = 1;
		mul.b = mul.c = 0;
	}
	void update(const matrix2 v, int ql, int qr, int l, int r)
	{
		if (l == ql&&r == qr)
		{
			sum = sum*v;
			mul = mul*v;
		}
		else
		{
			push_down();
			int mid = (l + r) / 2;
			if (qr <= mid) this->l->update(v, ql, qr, l, mid);
			else if (ql >= mid) this->r->update(v, ql, qr, mid, r);
			else
			{
				this->l->update(v, ql, mid, l, mid);
				this->r->update(v, mid, qr, mid, r);
			}
			sum = this->l->sum + this->r->sum;
		}
	}
	long long query(int ql, int qr, int l, int r)
	{
		if (l == ql&&r == qr) return sum.a;
		push_down();
		int mid = (l + r) / 2;
		if (qr <= mid) return this->l->query(ql, qr, l, mid);
		if (ql >= mid) return this->r->query(ql, qr, mid, r);
		return this->l->query(ql, mid, l, mid) + this->r->query(mid, qr, mid, r);
	}
};
int main()
{
	ios::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	seg_node *seg = seg_node::build(0, n);
	matrix2 m;
	m.a = m.b = m.c = 1;
	m.d = 0;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		seg->update(power(m, x), i, i + 1, 0, n);
	}
	for (int i = 0; i < q; i++)
	{
		int t, l, r;
		cin >> t >> l >> r;
		if (t == 1)
		{
			int x;
			cin >> x;
			seg->update(power(m, x), l - 1, r, 0, n);
		}
		else cout << seg->query(l - 1, r, 0, n) % P << endl;
	}
}
