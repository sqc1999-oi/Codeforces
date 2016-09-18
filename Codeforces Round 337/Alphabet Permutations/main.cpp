#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
const int K = 10;
struct segment_tree
{
	struct node
	{
		int l, r, lv, rv;
		node *lc, *rc;
		bool flag;
		int d[K][K];
	private:
		void _update(int val)
		{
			memset(d, 0x00, sizeof d);
			d[val][val] = r - l - 1;
			flag = true;
			lv = rv = val;
		}
	public:
		void maintain()
		{
			for (int i = 0; i < K; i++)
				for (int j = 0; j < K; j++)
					d[i][j] = lc->d[i][j] + rc->d[i][j];
			d[lc->rv][rc->lv]++;
			lv = lc->lv;
			rv = rc->rv;
		}
		void push_down()
		{
			if (!flag) return;
			flag = false;
			lc->_update(lv);
			rc->_update(lv);
		}
		void update(int l, int r, int val)
		{
			if (l == this->l&&r == this->r) _update(val);
			else
			{
				push_down();
				if (r <= lc->r) lc->update(l, r, val);
				else if (l >= rc->l) rc->update(l, r, val);
				else
				{
					lc->update(l, lc->r, val);
					rc->update(rc->l, r, val);
				}
				maintain();
			}
		}
	};
private:
	node *r;
public:
	segment_tree(int n) { r = build(0, n); }
	node *build(int l, int r) const
	{
		if (l + 1 == r) return new node{ l,r,0,0,nullptr,nullptr };
		int mid = (l + r) / 2;
		node *x = new node{ l,r,0,0,build(l,mid),build(mid,r) };
		x->d[0][0] = r - l - 1;
		return x;
	}
	void update(int l, int r, int val) const { this->r->update(l, r, val); }
	int query(string s) const
	{
		int ret = 0;
		for (int i = 0; i < s.size(); i++)
			for (int j = 0; j <= i; j++)
				ret += r->d[s[i] - 'a'][s[j] - 'a'];
		return ret;
	}
};
int main()
{
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	segment_tree t(n);
	string s;
	cin >> s;
	for (int i = 0; i < n; i++)
		t.update(i, i + 1, s[i] - 'a');
	for (int i = 0; i < m; i++)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int l, r;
			char c;
			cin >> l >> r >> c;
			t.update(l - 1, r, c - 'a');
		}
		else
		{
			string p;
			cin >> p;
			cout << t.query(p) + 1 << endl;
		}
	}
}
