#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
struct Segment
{
	int Left, Right;
	bool operator <(const Segment &other) const
	{
		return Right < other.Right;
	}
};
int main()
{
	ios::sync_with_stdio(false);
	int n, k, a, m;
	cin >> n >> k >> a >> m;
	auto Set = set<Segment>();
	Set.insert(Segment{ 1,n });
	int Count = (n + 1) / (a + 1);
	auto Visisted = new bool[n + 1];
	memset(Visisted, 0, sizeof(bool)*n + 1);
	for (int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;
		if (Visisted[x]) continue;
		Visisted[x] = true;
		auto SegIt = Set.lower_bound({ 0,x });
		auto Seg = *SegIt;
		Set.erase(SegIt);
		Count -= (Seg.Right - Seg.Left + 2) / (a + 1);
		if (x != Seg.Left)
		{
			auto l = Segment{ Seg.Left,x - 1 };
			Count += (l.Right - l.Left + 2) / (a + 1);
			Set.insert(l);
		}
		if (x != Seg.Right)
		{
			auto r = Segment{ x + 1,Seg.Right };
			Count += (r.Right - r.Left + 2) / (a + 1);
			Set.insert(r);
		}
		if (Count < k)
		{
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}
