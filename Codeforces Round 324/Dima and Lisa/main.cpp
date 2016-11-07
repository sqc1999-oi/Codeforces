#include <iostream>
#include <algorithm>
using namespace std;
bool isprime(int x)
{
	if (x == 1)
		return false;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
			return false;
	return true;
}
int main()
{
	int m;
	cin >> m;
	if (isprime(m))
		cout << 1 << endl << m << endl;
	else if (isprime(m - 2))
		cout << 2 << endl << 2 << " " << m - 2 << endl;
	else
		for (int i = 3; i <= m; i += 2)
			for (int j = 3; j <= m; j += 2)
				if (isprime(i) && isprime(j) && isprime(m - i - j))
				{
					cout<<	3<<endl << i << " " << j << " " << m - i - j << endl;
					return 0;
				}
}
