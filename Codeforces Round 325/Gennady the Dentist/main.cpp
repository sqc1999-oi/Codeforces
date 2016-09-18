#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;
struct child
{
	int id, v, d;
	long long p;
};
int main()
{
	typedef list<child>::iterator it;
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	list<child> li;
	for (int i = 1; i <= n; i++)
	{
		int v, d, p;
		cin >> v >> d >> p;
		li.push_back(child{ i,v,d,p });
	}
	queue<int> q;
	while (!li.empty())
	{
		child cu = li.front();
		li.pop_front();
		q.push(cu.id);
		long long cv = cu.v, cd = 0;
		for (it i = li.begin(); i != li.end();)
		{
			i->p -= cv + cd;
			cv = max(cv - 1, 0ll);
			if (i->p < 0)
			{
				cd += i->d;
				i = li.erase(i);
			}
			else i++;
		}
	}
	cout << q.size() << endl;
	while (!q.empty())
	{
		cout << q.front() << ' ';
		q.pop();
	}
}
