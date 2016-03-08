#include <iostream>
#include <map>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	auto a = new pair<int, int>[n];
	for (int i = 0; i < n; i++)
		cin >> a[i].first >> a[i].second;
	int ans = 0;
	map<int, int> mx, my;
	map<pair<int, int>, int> mz;
	for (int i = 0; i < n; i++)
	{
		ans += mx[a[i].first];
		mx[a[i].first]++;
		ans += my[a[i].second];
		my[a[i].second]++;
		ans -= mz[a[i]];
		mz[a[i]]++;
	}
	cout << ans;
}