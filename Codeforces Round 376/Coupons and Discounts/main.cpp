#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int flag = 0;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		if (flag && !x)
		{
			cout << "NO" << endl;
			return 0;
		}
		flag = (x^flag) & 1;
	}
	cout << (flag ? "NO" : "YES") << endl;
}
