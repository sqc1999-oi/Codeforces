#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
const double EPS = 1e-10;
const int P = 1e6 + 3;
using namespace std;
long long power(long long a, long long b)
{
	long long ret = 1;
	while (b > 0)
	{
		if (b & 1) ret = ret*a%P;
		b >>= 1;
		a = a*a%P;
	}
	return ret;
}
int main()
{
	long long n, k;
	cin >> n >> k;
	if (n <= 60 && (1ll << n) < k) cout << "1 1" << endl;
	else
	{
		long long fm = power(power(2, n), k - 1), fz = 1, ny = power(2, P - 2), s = 0;
		int tmp = (power(2, n) + P - 1) % P;
		k--;
		if (tmp >= k)
		{
			while (k)
			{
				int t = ++s;
				while (t % 2 == 0)
				{
					t >>= 1;
					fm = (long long)fm*ny%P;
					fz = (long long)fz*ny%P;
				}
				fz = (long long)tmp*fz%P;
				tmp--;
				k--;
			}
			fz = fm - fz;
			if (fz < 0) fz += P;
			cout << fz << ' ' << fm << endl;
		}
		else
		{
			while (k)
			{
				s += k / 2;
				k /= 2;
			}
			fm = (long long)fm*power(ny, s) % P;
			cout << fm << ' ' << fm << endl;
		}
	}
}
