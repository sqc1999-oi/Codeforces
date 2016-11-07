#include <iostream>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int main()
{
	ios::sync_with_stdio(false);
	int l, p, q;
	cin >> l >> p >> q;
	double fp = ((double)l / (p + q)) * p;
	
	double sp;
	if (q > p)
	{
		sp = fp - (((l - fp) * 2) / (q - p))*p;
		if (fp - sp > eps&&sp > eps)
		{
			cout << sp;
			return 0;
		}
	}
	if (p > q)
	{
		sp = fp + ((fp * 2.0) / (p - q))*q;
		if (sp - fp > eps&&l - sp > eps)
		{
			cout << sp;
			return 0;
		}
	}
	sp = ((double)(l * 2) / (p + q))*p - fp;
	cout << sp;
}
