#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, x;
	cin >> n >> x;
	priority_queue<int> q;
	for (int i = 2; i <= n; i++)
	{
		int a;
		cin >> a;
		q.push(a);
	}
	int cnt = 0;
	while (q.top() >= x)
	{
		cnt++;
		x++;
		int t = q.top();
		q.pop();
		q.push(t - 1);
	}
	cout << cnt;
}
