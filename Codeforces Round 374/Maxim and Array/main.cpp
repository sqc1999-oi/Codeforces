#include <iostream>
#include <algorithm>
#include <iterator>
#include <climits>
#include <cmath>
using namespace std;
const int N = 2e5;
long long a[N];
typedef pair<long long, int> pli;
pli h[N];
int main()
{
	ios::sync_with_stdio(false);
	int n, k, x, f = 1, min = INT_MAX, p = 0;
	cin >> n >> k >> x;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		if (a[i] < 0) f *= -1;
		if (abs(a[i]) < abs(min))
		{
			min = a[i];
			p = i;
		}
	}
	if (f == 1 && abs(a[p]) >= (long long)k*x)
	{
		if (a[p] >= 0) a[p] -= k*x;
		else a[p] += k*x;
		copy(a, a + n, ostream_iterator<long long>(cout, " "));
	}
	else
	{
		if (f == 1)
		{
			if (a[p] >= 0)
				for (; a[p] >= 0; k--) a[p] -= x;
			else
				for (; a[p] <= 0; k--) a[p] += x;
		}
		for (int i = 0; i < n; i++) h[i] = { a[i],i };
		auto cmp = [](const pli &a, const pli &b) { return abs(a.first) > abs(b.first); };
		make_heap(h, h + n, cmp);
		for (int i = 0; i < k; i++)
		{
			pop_heap(h, h + n, cmp);
			long long &t = h[n - 1].first;
			if (t >= 0) t += x;
			else t -= x;
			push_heap(h, h + n, cmp);
		}
		sort(h, h + n, [](const pli &a, const pli &b) { return a.second < b.second; });
		for (int i = 0; i < n; i++) cout << h[i].first << ' ';
	}
}
