#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
const int N = 1e5;
struct seg
{
	int x0, y0, x1, y1;
};
vector<seg> r, c;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x0, y0, x1, y1;
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 == x1) c.push_back({ x0,y0,x1,y1 });
		else r.push_back({ x0,y0,x1,y1 });
	}
	sort(r.begin(), r.end(), [](const seg &a, const seg &b) { return a.y0 < b.y0 || (a.y0 == b.y0 && a.x0 < b.x0); });
	for (int i = 0; i < r.size(); i++)
	{
		while (r[i].y0 == r[i + 1].y0)
		{
			if ()
		}
	}
}