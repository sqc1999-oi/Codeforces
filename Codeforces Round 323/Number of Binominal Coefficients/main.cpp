#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <cstring>
#include <string>
#include <iterator>
using namespace std;
const int N = 4000, P = 1e9 + 7;
vector<int> a, b;
int f[N][N][2][2];
int calc(int x, int p)
{
	if (x < p) return (long long)(x + 2)*(x + 1) / 2 % P;
	x -= p - 1;
	return ((long long)(p + 1)*p / 2 + (long long)(p - x + p - 1)*x / 2) % P;
}
int calc(int l, int r, int p) { return (calc(r, p) - calc(l - 1, p) + P) % P; }
int dp(int i, int cnt, bool up, bool carry, int p)
{
	int &x = f[i][cnt][up][carry];
	if (x == -1)
	{
		if (i == a.size()) x = !carry&&cnt <= 0;
		else
		{
			x = 0;
			if (up)
			{
				if (!carry || a[i] < p - 1) x = (x + (long long)dp(i + 1, cnt, true, false, p)*calc(a[i] + carry*p, a[i] + carry*p, p)) % P;
				if (carry || a[i] > 0) x = (x + (long long)dp(i + 1, cnt - 1, true, true, p)*calc(a[i] - 1 + carry*p, a[i] - 1 + carry*p, p)) % P;
			}
			x = (x + (long long)dp(i + 1, cnt, false, false, p)*calc(carry*p, (up ? a[i] : p) - 1 + carry*p, p)) % P;
			x = (x + (long long)dp(i + 1, cnt - 1, false, true, p)*calc(carry*(p - 1), (up ? a[i] : p) - 2 + carry*p, p)) % P;
		}
	}
	return x;
}
int main()
{
	ios::sync_with_stdio(false);
	int p, al;
	string s;
	cin >> p >> al >> s;
	transform(s.begin(), s.end(), inserter(b, b.begin()), [](char ch) { return ch - '0'; });
	reverse(b.begin(), b.end());
	while (!b.empty())
	{
		long long c = 0;
		for (int i = b.size() - 1; i >= 0; i--)
		{
			long long t = (b[i] + c * 10) % p;
			b[i] = (b[i] + c * 10) / p;
			c = t;
			if (b[i] == 0 && i == b.size() - 1) b.pop_back();
		}
		a.push_back(c);
	}
	reverse(a.begin(), a.end());
	if (al >= a.size()) cout << 0 << endl;
	else
	{
		memset(f, 0xff, sizeof f);
		cout << dp(0, al, true, false, p) << endl;
	}
}
