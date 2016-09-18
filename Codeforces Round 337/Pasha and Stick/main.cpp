#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	if (n % 2 == 1) cout << 0;
	else
	{
		n /= 2;
		cout << n / 2 - (n % 2 == 0);
	}
}
