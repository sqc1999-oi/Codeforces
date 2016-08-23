#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	bool flag = false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			char ch;
			cin >> ch;
			if (ch != 'B'&&ch != 'W'&&ch != 'G') flag = true;
		}
	cout << (flag ? "#Color" : "#Black&White") << endl;
}
