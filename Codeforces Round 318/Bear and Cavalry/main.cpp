#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;
const int N = 3e4;
pair<long long, int> w[N], h[N];
int pos_w[N], pos_h[N], p[N];
struct seg_node
{
	long long f[3][3];
	seg_node *l, *r;
	seg_node(seg_node *l, seg_node *r) :l(l), r(r) {}
	void calc(int x)
	{
		memset(f, 0xff, sizeof f);
		if (p[x] != x) f[0][0] = w[x].first*h[x].first;
		f[0][1] = f[1][0] = 0;
	}
	void maintain(int l, int r)
	{
		memset(f, 0xff, sizeof f);
		int mid = (l + r) / 2;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (this->l->f[i][0] >= 0 && this->r->f[0][j] >= 0) f[i][j] = this->l->f[i][0] + this->r->f[0][j];
				if (this->l->f[i][1] >= 0 && this->r->f[1][j] >= 0 && p[mid - 1] != mid && p[mid] != mid - 1)
					f[i][j] = max(f[i][j], this->l->f[i][1] + w[mid - 1].first*h[mid].first + w[mid].first*h[mid - 1].first + this->r->f[1][j]);
				if (this->l->f[i][1] >= 0 && this->r->f[2][j] >= 0)
				{
					if (p[mid - 1] != mid && p[mid] != mid + 1 && p[mid + 1] != mid - 1)
						f[i][j] = max(f[i][j], this->l->f[i][1] + w[mid - 1].first*h[mid].first + w[mid].first*h[mid + 1].first + w[mid + 1].first*h[mid - 1].first + this->r->f[2][j]);
					if (p[mid - 1] != mid + 1 && p[mid] != mid - 1 && p[mid + 1] != mid)
						f[i][j] = max(f[i][j], this->l->f[i][1] + w[mid - 1].first*h[mid + 1].first + w[mid].first*h[mid - 1].first + w[mid + 1].first*h[mid].first + this->r->f[2][j]);
				}
				if (this->l->f[i][2] >= 0 && this->r->f[1][j] >= 0)
				{
					if (p[mid - 2] != mid - 1 && p[mid - 1] != mid && p[mid] != mid - 2)
						f[i][j] = max(f[i][j], this->l->f[i][2] + w[mid - 2].first*h[mid - 1].first + w[mid - 1].first*h[mid].first + w[mid].first*h[mid - 2].first + this->r->f[1][j]);
					if (p[mid - 2] != mid && p[mid - 1] != mid - 2 && p[mid] != mid - 1)
						f[i][j] = max(f[i][j], this->l->f[i][2] + w[mid - 2].first*h[mid].first + w[mid - 1].first*h[mid - 2].first + w[mid].first*h[mid - 1].first + this->r->f[1][j]);
				}
				if (j == 2 && r - mid == 1 && this->l->f[i][1] >= 0) f[i][j] = max(f[i][j], this->l->f[i][1]);
				if (i == 2 && mid - l == 1 && this->r->f[1][j] >= 0) f[i][j] = max(f[i][j], this->r->f[1][j]);
			}
		
	}
	static seg_node *build(int l, int r)
	{
		if (l == r - 1)
		{
			auto x = new seg_node(NULL, NULL);
			x->calc(l);
			return x;
		}
		int mid = (l + r) / 2;
		auto x = new seg_node(build(l, mid), build(mid, r));
		x->maintain(l, r);
		return x;
	}
	long long query() { return f[0][0]; }
	void update(int x, int l, int r)
	{
		if (l == r - 1) calc(x);
		else
		{
			int mid = (l + r) / 2;
			if (x < mid) this->l->update(x, l, mid);
			else this->r->update(x, mid, r);
			maintain(l, r);
		}
	}
} *a[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++) cin >> w[i].first;
	for (int i = 0; i < n; i++) cin >> h[i].first;
	for (int i = 0; i < n; i++) w[i].second = h[i].second = i;
	sort(w, w + n, greater<pair<long long, int>>());
	sort(h, h + n, greater<pair<long long, int>>());
	for (int i = 0; i < n; i++)
		pos_w[w[i].second] = pos_h[h[i].second] = i;
	for (int i = 0; i < n; i++) p[pos_w[i]] = pos_h[i];
	auto tree = seg_node::build(0, n);
	for (int i = 0; i < q; i++)
	{
		int x, y;
		cin >> x >> y;
		swap(p[pos_w[x - 1]], p[pos_w[y - 1]]);
		tree->update(pos_w[x - 1], 0, n);
		tree->update(pos_w[y - 1], 0, n);
		cout << tree->query() << endl;
	}
}
