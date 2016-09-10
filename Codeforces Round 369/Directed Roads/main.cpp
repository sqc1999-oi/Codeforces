#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2e5, P = 1e9 + 7;
int a[N], stat[N], dep[N], sum;
vector<int> v;
void dfs(int u)
{
	stat[u] = 1;
	if (stat[a[u]] == 0)
	{
		dep[a[u]] = dep[u] + 1;
		dfs(a[u]);
	}
	else if (stat[a[u]] == 1)
	{
		sum += dep[u] + 1 - dep[a[u]];
		v.push_back(dep[u] + 1 - dep[a[u]]);
	}
	stat[u] = 2;
}
int pow(int a, int b)
{
	long long ret = 1, t = a; 
	while (b > 0)
	{
		if (b & 1) ret = ret*t%P;
		b >>= 1;
		t = t*t%P;
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i]--;
	}
	for (int i = 0; i < n; i++)
		if (stat[i] == 0) dfs(i);
	int ans = pow(2, n - sum);
	for (int x : v) ans = ((long long)ans*(pow(2, x) + P - 2) % P) % P;
	cout << ans << endl;
}
