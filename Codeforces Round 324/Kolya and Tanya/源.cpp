#include <iostream>
#include <algorithm>
using namespace std;
const int P = 1e9 + 7;
int fact[100001], factie[100001];
int pow(int a, int k)
{
	int ret = 1;
	while (k > 0)
	{
		if (k % 2 == 1) ret = (long long)ret * a % P;
		k /= 2;
		a = (long long)a * a % P;
	}
	return ret;
}
int c(int n, int m)
{
	return (long long)fact[n] * factie[n - m] % P * factie[m] % P;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	fact[0] = factie[0] = fact[1] = factie[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		fact[i] = (long long)fact[i - 1] * i % P;
		factie[i] = pow(fact[i], P - 2);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
		(ans += (long long)pow(7, i) * pow(20, n - i) % P * c(n, i) % P) %= P;
	cout << ans;
}