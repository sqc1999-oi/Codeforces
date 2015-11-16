#include <iostream>
#include <algorithm>
using namespace std;
bool vh[51], vv[51];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n*n; i++)
	{
		int h, v;
		cin >> h >> v;
		if (!vh[h] && !vv[v])
		{
			vh[h] = vv[v] = true;
			cout << i << ' ';
		}
	}
}