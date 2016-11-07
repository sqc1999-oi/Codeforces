#include <iostream>
#include <algorithm>
using namespace std;
const int P = 1e6 + 3;
int flag_count(long long x)
{
	int cnt = 0;
	for (; x > 0; x >>= 1) cnt += x & 1;
	return cnt;
}
long long power(long long a, long long b)
{
	long long ret = 1;
	while (b > 0)
	{
		if (b & 1) ret = ret*a%P;
		a = a*a%P;
		b >>= 1;
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	long long n, k;
	cin >> n >> k;
	if (n <= 63 && (1ll << n) < k) cout << "1 1" << endl;
	else
	{
		long long g = (k - 1 - flag_count(k - 1)) % (P - 1);
		n %= P - 1;
		long long denom = power(2, ((n*(k % (P - 1) - 1) - g) % (P - 1) + P - 1) % (P - 1)), num = 0;
		if (k - 1 < P)
		{
			num = power(power(2, g), P - 2);
			long long p = power(2, n);
			for (int i = 1; i <= k - 1; i++) num = num*(p - i) % P;
		}
		num = ((denom - num) % P + P) % P;
		cout << num << ' ' << denom << endl;
	}
}
