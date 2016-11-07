#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5e5;
template<typename data> struct splay_node
{
	static splay_node *nul;
	struct constructor
	{
		constructor()
		{
			nul = new splay_node();
			nul->l = nul->r = nul->p = nul;
			nul->val = new data(0);
		}
	};
	static constructor ctor;
	splay_node *l, *r, *p;
	data *val;
	splay_node()
	{
		ctor;
		l = r = p = nul;
		val = new data(1);
	}
	void push_down() { val->push_down(l->val, r->val); }
	void maintain() { val->maintain(l->val, r->val); }
	void rotate(bool flag)
	{
		auto l = &splay_node::l, r = &splay_node::r;
		if (flag) swap(l, r);
		auto x = this->*r;
		this->*r = x->*l;
		(this->*r)->p = this;
		x->p = this->p;
		if (this->p->l == this) this->p->l = x;
		else if (this->p->r == this) this->p->r = x;
		x->*l = this;
		this->p = x;
		this->maintain();
		x->maintain();
	}
	void splay()
	{
		static splay_node *s[N];
		int k = 0;
		s[k++] = this;
		for (; s[k - 1]->p != nul; k++) s[k] = s[k - 1]->p;
		while (k > 0) s[--k]->push_down();
		while (p != nul)
		{
			auto x = p->p;
			if (x == nul)
				if (p->l == this) p->rotate(true);
				else p->rotate(false);
			else
				if (p->l == this)
					if (x->l == p) x->rotate(true), p->rotate(true);
					else p->rotate(true), x->rotate(false);
				else
					if (x->r == p) x->rotate(false), p->rotate(false);
					else p->rotate(false), x->rotate(true);
		}
	}
	splay_node *find_last() { return r == nul ? this : r->find_last(); }
};
struct data_reset
{
	int val;
	bool flag;
	data_reset(int s) :val(0), flag(false) {}
	void push_down(data_reset *l, data_reset *r)
	{
		if (flag)
		{
			l->val = r->val = val;
			l->flag = r->flag = true;
			flag = false;
		}
	}
	void maintain(const data_reset *l, const data_reset *r) {}
	void update(int x)
	{
		val = x;
		flag = true;
	}
};
struct data_add
{
	long long val, add;
	int size;
	data_add(int s) :val(0), add(0), size(s) {}
	void push_down(data_add *l, data_add *r)
	{
		l->val += add;
		l->add += add;
		r->val += add;
		r->add += add;
		add = 0;
	}
	void maintain(const data_add *l, const data_add *r) { size = l->size + r->size + 1; }
	void update(int x)
	{
		val += x;
		add += x;
	}
};
template<typename data> splay_node<data> *splay_node<data>::nul;
template<typename data> typename splay_node<data>::constructor splay_node<data>::ctor;
splay_node<data_reset> *a[N];
splay_node<data_add> *b[N];
vector<int> c[N];
long long d[N];
struct query
{
	char t;
	int x, y;
} q[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> q[i].t >> q[i].x;
		q[i].x--;
		if (q[i].t == 'U' || q[i].t == 'M')
		{
			cin >> q[i].y;
			q[i].y--;
		}
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = new splay_node<data_reset>;
		b[i] = new splay_node<data_add>;
	}
	for (int i = 0; i < m; i++)
	{
		if (q[i].t == 'M')
		{
			auto x = a[q[i].x], y = a[q[i].y];
			x->splay();
			x = x->find_last();
			x->splay();
			y->splay();
			x->r = y;
			y->p = x;
		}
		else if (q[i].t == 'Z')
		{
			auto x = a[q[i].x];
			x->splay();
			x->val->update(i);
		}
		else if (q[i].t == 'Q')
		{
			auto x = a[q[i].x];
			x->splay();
			c[x->val->val].push_back(i);
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int k : c[i])
		{
			auto x = b[q[k].x];
			x->splay();
			d[k] = x->val->val;
		}
		if (q[i].t == 'U')
		{
			auto x = b[q[i].x], y = b[q[i].y];
			x->splay();
			x = x->find_last();
			x->splay();
			y->splay();
			x->r = y;
			y->p = x;
			x->maintain();
		}
		else if (q[i].t == 'A')
		{
			auto x = b[q[i].x];
			x->splay();
			x->val->update(x->val->size);
		}
		else if (q[i].t == 'Q')
		{
			auto x = b[q[i].x];
			x->splay();
			cout << x->val->val - d[i] << endl;
		}
	}
}
