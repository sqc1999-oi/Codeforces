#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
const int N = 750, M = 1e7, K = 2;
struct node
{
	node *link[K], *fail, *last;
	int id;
	node() :id(-1) {}
} pool[M + 1];
node *get_node()
{
	static int cnt;
	return &pool[cnt++];
}
string s[N];
bool f[N][N];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	auto tree = new node;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		node *&x = tree;
		for (int j = 0; j < s[i].size(); j++)
		{
			x = x->link[s[i][j] - 'a'];
			if (x == nullptr) x = new node;
		}
		x->id = i;
	}
	queue<node *> q;
	for (int i = 0; i < K; i++)
	{
		node *&x = tree->link[i];
		if (x != nullptr)
		{
			q.push(x);
			x->last = x->fail = x;
		}
	}
	while (!q.empty())
	{
		node *u = q.front();
		q.pop();
		for (int i = 0; i < K; i++)
		{
			node *&v = u->link[i];
			if (v != nullptr)
			{
				q.push(v);
				v->fail = u->fail->link[i];
				v->last = v->fail->id >= 0 ? v->fail : v->fail->last;
			}
			else v = u->fail->link[i];
		}
	}
	for (int i = 0; i < n; i++)
	{
		node *x = tree;
		for (int j = 0; j < s[i].size(); i++)
		{
			x = x->link[s[i][j]];
			if (x->last != tree) f[i][x->id] = true;
		}
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				f[i][j] = f[i][k] && f[k][j];

}
