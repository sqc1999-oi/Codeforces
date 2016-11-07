#include <iostream>
#include <algorithm>
#include <cmath>
#include <bitset>
using namespace std;
const int N = 512;
char a[N][N];
int main()
{
	ios::sync_with_stdio(false);
	int k;
	cin >> k;
	int n = round(pow(2, k));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) cout << (bitset<32>(i | j).count() & 1 ? '+' : '*');
		cout << endl;
	}
}
