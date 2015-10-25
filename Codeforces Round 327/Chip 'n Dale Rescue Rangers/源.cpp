#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
const long double eps = 1e-9l;
int main()
{
	ios::sync_with_stdio(false);
	int x1, y1, x2, y2, v, t, vx, vy, wx, wy;
	cin >> x1 >> y1 >> x2 >> y2 >> v >> t >> vx >> vy >> wx >> wy;
	long double l = 0.0l, r = 1e8l;
	while (r - l > eps)
	{
		long double mid = l + (r - l) / 2;
		long double t1 = fmin((long double)t, mid), t2 = fmax(mid - t, 0.0l);
		long double nx = x1 + vx*t1 + wx*t2 - x2, ny = y1 + vy*t1 + wy*t2 - y2;
		if (sqrt(nx*nx + ny*ny) / v - mid > eps) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(18) << l;
}